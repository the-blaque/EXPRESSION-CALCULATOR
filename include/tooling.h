#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "model.h"

using namespace std;

#pragma once

class Error {
public:
    Error(string msg);

    const string what() const;

private:
    string message;
};

class Parser {
public:
    Parser(vector<string> toks);

    Node* parse();

private:
    Node* parseGroupExpression();

    Node* parseBinaryExpression();

    Node* parseNumber();

    bool isOperator(string s);

    bool isAtEnd();

    void advanceIndex();

    string peek();

    vector<string> tokens; // track all tokens
    int current;           // track index of current token
};

class Interpreter {
public:
    int interpret(Node* root);

private:
    int beginInterpretation(Node* n);

    int performCalc(int l, int r, char op);
};

// tokenizer
vector<string> tokenizeInput(string input);