
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "SyntaxAnalyzer.h"
#include "StringUtils.h"
#include "Translator.h"

using namespace std;

int main() {
    CheckingResult res;
    auto *syntaxAnalyzer = new SyntaxAnalyzer();
    res = syntaxAnalyzer->isMethodReturningType("rungekutta", 0, TABLE);
    if (res.isSuccessful()) cout << "yes" << endl;
    else cout << "no " << res.getMessage() << " at " << res.getPosition() << endl;

    Translator().translateToCpp("../example.ds");

    string str = "   waaat ";
    cout << str << endl;
    StringUtils::trim(str);
    cout << str << endl;
    return 0;
}