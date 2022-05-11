#include "model.h"

BinaryExpression::BinaryExpression(Node* l, string opr, Node* r)
    : left(l), op(opr), right(r) {
}

BinaryExpression::~BinaryExpression() {
    delete left;
    delete right;
}

string BinaryExpression::type() const {
    return "BinaryExpression";
}

void BinaryExpression::print(Formatter& f, string pad) const {
    f.indent();
    left->print(f, "┌──");
    f.dedent();
    f.indentAdd(pad + "[" + op + "]");
    f.indent();
    right->print(f, "└──");
    f.dedent();
}

Node* BinaryExpression::getLeft() const {
    return left;
}

Node* BinaryExpression::getRight() const {
    return right;
}

char BinaryExpression::getOperator() const {
    return op[0];
}


Number::Number(int v) : value(v) {}

Number::~Number() {}

string Number::type() const {
    return "Number";
}

void Number::print(Formatter& f, string pad) const {
    f.indentAdd(pad + "<" + to_string(value) + ">");
}

int Number::getValue() const {
    return value;
}