#include "formatter.h"

Formatter::Formatter() {
    ind = 4;
}

void Formatter::add(string s) {
    content.push_back(s);
}

void Formatter::indentAdd(string s) {
    string indentSpace(ind, ' ');

    content.push_back(indentSpace + s);
}

void Formatter::indent() {
    ind += 4;
}

void Formatter::dedent() {
    ind -= 4;
}

void Formatter::print() {
    for (auto s : content) {
        cout << s << endl;
    }
    content.clear();
}

void Formatter::clear() {
    content.clear();
}