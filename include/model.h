#pragma once
#include <iostream>
#include "formatter.h"

using namespace std;

class Node {
public:
    virtual ~Node() {}
    virtual string type() const = 0;
    virtual void print(Formatter& f, string pad = "") const = 0;
};

class BinaryExpression : public Node {
public:
    BinaryExpression(Node* l, string opr, Node* r);

    ~BinaryExpression();

    string type() const;

    void print(Formatter& f, string pad = "") const;

    Node* getLeft() const;

    Node* getRight() const;

    char getOperator() const;

private:
    Node* left, * right;
    string op;
};

class Number : public Node {
public:
    Number(int v);

    ~Number();

    string type() const;

    void print(Formatter& f, string pad = "") const;

    int getValue() const;

private:
    int value;
};
