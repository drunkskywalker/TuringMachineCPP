#include "Tape.hpp"
#include "TuringLog.hpp"

void Tape::p_initTapes(std::string initial) {
    if (initial == "") {
        this->rightTape = {};
        this->rightTape.push_back(this->emptyChar);
    }
    else {
        for (size_t i = 0; i < initial.size(); i ++) {
            this->rightTape.push_back(initial[i]);
        }
    }
    LOG("initial string is " + initial, ALL);
    this->leftTape = {};
}

void Tape::moveLeft() {
    if (this->pos <= 0) {
        if (size_t(-this->pos) == this->leftTape.size()) {
            LOG("exceeding left tape range", ALL);
            this->leftTape.push_back(this->emptyChar);
        }
    }
    pos --;
}


void Tape::moveRight() {
    if (this->pos >= 0) {
        if (size_t(this->pos + 1) == this->rightTape.size()) {
             LOG("exceeding right tape range", ALL);
            this->rightTape.push_back(this->emptyChar);
        }
    }
    pos ++;
}

char Tape::read() {
    if (this->pos < 0) {
        return this->leftTape[-(this->pos) - 1];
    }
    else {
        return this->rightTape[this->pos];
    }
}

void Tape::write(char toWrite) {
    if (this->pos < 0) {
        this->leftTape[-this->pos - 1] = toWrite;
    }
    else {
        this->rightTape[this->pos] = toWrite;
    }
    std::string message = "new tape: " + this->readAll();
    LOG(message, ALL);
}


int Tape::length() {
    return this->rightTape.size() + this->leftTape.size();
}

int Tape::getPosition() {
    return this->pos;
}

std::string Tape::readAll() {
    std::string res = "";
    for (std::vector<char>::reverse_iterator it = this->leftTape.rbegin(); it != this->leftTape.rend(); ++ it) {
        res += *it;
    }
    for (std::vector<char>::iterator it = this->rightTape.begin(); it != this->rightTape.end(); ++it) {
        res += *it;
    }
    return res;
}

