#ifndef CLASS_HPP
#define CLASS_HPP

#include <string>
#include <vector>

enum MeetingPattern {
    M,
    T,
    W,
    R,
    F,
    MW,
    TR,
    MWF
};

class Class {
public:
    int CRN;
    std::string courseCode;
    std::string title;
    int length; // In minutes
    int frequency; // Times x week

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