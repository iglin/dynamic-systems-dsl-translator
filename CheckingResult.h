//
// Created by alig0716 on 31.10.17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_TRANSLATOR_CHECKINGRESULT_H
#define DYNAMIC_SYSTEMS_DSL_TRANSLATOR_CHECKINGRESULT_H

#include <iostream>
#include <utility>

using namespace std;

class CheckingResult {
private:
    bool successful = false;
    int position = 0;
    string message;
public:
    CheckingResult() = default;

    CheckingResult(bool result, int position, string message) : successful(result), position(position),
                                                                       message(std::move(message)) { }
    explicit CheckingResult(bool result) : successful(result) { }

    bool isSuccessful() const;

    void setSuccessful(bool result);

    int getPosition() const;

    void setPosition(int position);

    const string &getMessage() const;

    void setMessage(const string &message);
};


#endif //DYNAMIC_SYSTEMS_DSL_TRANSLATOR_CHECKINGRESULT_H
