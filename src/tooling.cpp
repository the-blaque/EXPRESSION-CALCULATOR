#include "tooling.h"
#include <string>
#include <algorithm>    

Error::Error(string msg) : message(msg) {}

const string Error::what() const {
    return message;
}

Parser::Parser(vector<string> toks) : tokens(toks) {
    current = 0;
}

Node* Parser::parse() {
    return parseBinaryExpression();
}

Node* Parser::parseGroupExpression() {
    advanceIndex(); // skip over (
    auto content = parseBinaryExpression();

    if (peek() != ")") {
        string msg = "Expected ')' but found " + peek() + "\n";
        Error e(msg);
        throw e;
    }
    advanceIndex();
    return content;
}

Node* Parser::parseBinaryExpression() {
    auto e = parseNumber();

    while (!isAtEnd() && isOperator(peek())) {
        string op = peek();
        advanceIndex();
        auto other = parseNumber();
        e = new BinaryExpression(e, op, other);
    }

    return e;
}

Node* Parser::parseNumber() {
    string candidate = peek();
    if (candidate == "(") {
        return parseGroupExpression();
    }
    try {
        int val = stoi(candidate);
        advanceIndex();
        return new Number(val);
    }
    catch (exception& err) {
        string msg = "Trouble converting [" + candidate + "] to integer.\n";
        msg += "Exception: ";
        msg += err.what();
        msg += "\n";
        Error e(msg);
        throw e;
    }
}

bool Parser::isOperator(string s) {
    vector<string> ops{ "+", "-", "/", "*" };
    return find(ops.begin(), ops.end(), s) != ops.end();
}

bool Parser::isAtEnd() {
    return tokens.size() <= current;
}

void Parser::advanceIndex() {
    current++;
}

string Parser::peek() {
    if (!isAtEnd()) {
        return tokens[current];
    }
    return "EOL";
}



int Interpreter::interpret(Node* root) {
    return beginInterpretation(root);
}

int Interpreter::beginInterpretation(Node* n) {
    if (n->type() == "BinaryExpression") {
        auto bin = dynamic_cast<BinaryExpression*>(n);
        int lhs = beginInterpretation(bin->getLeft());
        int rhs = beginInterpretation(bin->getRight());
        return performCalc(lhs, rhs, bin->getOperator());
    }

    auto num = dynamic_cast<Number*>(n);
    return num->getValue();
}

int Interpreter::performCalc(int l, int r, char op) {
    switch (op) {
    case '+':
    {
        return l + r;
    }
    case '-':
    {
        return l - r;
    }
    case '/':
    {
        if (r == 0) {
            string msg = "Cannot perform division by 0 so ";
            msg += to_string(l) + "/ 0 is illegal\n";
            Error e(msg);
            throw e;
        }
        return l / r;
    }
    case '*':
    {
        return l * r;
    }
    default:
    {
        string msg = "Unexpected operator [";
        msg += op;
        msg += "]\n";
        Error e(msg);
        throw e;
    }
    }
}

// tokenizer
vector<string> tokenizeInput(string input) {
    string token = "";
    vector<string> tokens;
    for (int i = 0; input.size() > i; ++i) {
        char c = input[i];
        switch (c) {
            // handle all single character cases
        case '(':
        case ')':
        case '+':
        case '-':
        case '/':
        case '*':
        {
            token += c;
            tokens.push_back(token);
            token = "";
            break;
        }
        case ' ':
        {
            continue;
        }
        default:
        {
            if (isdigit(c)) {
                int start = i;
                while (isdigit(input[i]) && i < input.size()) {
                    token += input[i];
                    i++;
                }

                i--;
                // handle digits¡
                tokens.push_back(token);
                token = "";
            }
            else {
                string msg = "Unexpected character [";
                msg += c;
                msg += "]\n";
                Error e(msg);
                throw e;
            }
        }
        }
    }

    return tokens;
}