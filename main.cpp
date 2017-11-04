#include <iostream>
#include "SyntaxAnalyzer.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    CheckingResult res;
    res = SyntaxAnalyzer::isIdentifier("_", 0);
    if (res.isSuccessful()) cout << "yes";
    else cout << "no " << res.getMessage() << " at " << res.getPosition();
    double _ = - .2;
    cout << _;
    return 0;
}