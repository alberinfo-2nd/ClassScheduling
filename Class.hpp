#ifndef CLASS_HPP
#define CLASS_HPP

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

const int DAY_START  = 7 * 60;  // Day starts at 7:00AM
const int DAY_END    = 18 * 60; // Day ends at 6:00PM
const int BLOCK_SIZE = 15;      // Each block is 15 minutes long

enum MeetingPattern {
    M   = 0b00001,
    T   = 0b00010,
    W   = 0b00100,
    R   = 0b01000,
    F   = 0b10000,
    MW  = 0b00101,
    TR  = 0b01010,
    MWF = 0b10101
};

std::ostream& operator<<(std::ostream& out, const MeetingPattern value);

static const std::vector<MeetingPattern> getPossiblePatterns(int frequency) {
    switch (frequency) {
        case 1:
            return {M, T, W, R, F};

        case 2:
            return {MW, TR};

        case 3:
            return {MWF};

        default:
            return {};
    }
}

class Class {
public:
    int CRN;
    std::string courseCode;
    std::string title;
    int length; // In minutes
    int frequency; // Times x week

    Class() {
        this->CRN = 0;
        this->courseCode = std::string("");
        this->title = std::string("");
        this->length = 0;
        this->frequency = -1;
    }

    Class(int CRN, std::string courseCode, std::string title, int length, int frequency) {
        this->CRN = CRN;
        this->courseCode = courseCode;
        this->title = title;
        this->length = length;
        this->frequency = frequency;
    }
};

std::vector<Class> readClasses(std::string filename);

#endif