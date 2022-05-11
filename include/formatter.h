#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Formatter {
public:
    Formatter();

    void add(string s);

    void indentAdd(string s);

    void indent();

    void dedent();

    void print();

    void clear();

private:
    int ind;
    vector<string> content;
};
