//
// Created by alig0716 on 31.10.17.
//

#include "CheckingResult.h"

bool CheckingResult::isSuccessful() const {
    return successful;
}

void CheckingResult::setSuccessful(bool result) {
    CheckingResult::successful = result;
}

int CheckingResult::getPosition() const {
    return position;
}

void CheckingResult::setPosition(int position) {
    CheckingResult::position = position;
}

const string &CheckingResult::getMessage() const {
    return message;
}

void CheckingResult::setMessage(const string &message) {
    CheckingResult::message = message;
}
