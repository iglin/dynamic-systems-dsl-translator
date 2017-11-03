#include <iostream>
#include "SyntaxAnalyzer.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    CheckingResult res;
    res = SyntaxAnalyzer::isIdentifier("z2318a__sdasd213", 0);
    if (res.isSuccessful()) cout << "yes";
    else cout << "no " << res.getMessage() << " at " << res.getPosition();
    int _ = 5;
    cout << _;
    return 0;
}