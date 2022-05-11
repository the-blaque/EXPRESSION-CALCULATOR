#include <iostream>
#include <vector>
#include <string>
#include "tooling.h"

using namespace std;

int main() {
    Interpreter i;
    Formatter f;
    bool showTree = false;

    cout << "Enter .q to quit!" << endl;
    cout << "Enter tree to toggle viewing expression tree!" << endl;
    while (true) {
        cout << "calc -> ";
        string input = "";
        // string input = "(1 + 4) * (5 - 2)";
        getline(cin, input);

        if (input == ".q") {
            break;
        }

        if (input == "tree") {
            showTree = !showTree;
            cout << endl;
            continue;
        }

        try {
            auto tokens = tokenizeInput(input);

            Parser p(tokens);
            auto n = p.parse();
            n->print(f);
            if (showTree) {
                f.print();
            }

            f.clear();

            cout << ">> " << i.interpret(n) << endl
                << endl;

            delete n;
        }
        catch (Error& e) {
            cout << e.what() << endl;
        }
    }
}