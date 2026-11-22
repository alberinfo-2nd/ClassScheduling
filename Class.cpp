#include "Class.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::vector<Class> readClasses(std::string filename) {
    std::ifstream classes(filename); //For now assume the filename exists
    std::vector<Class> ClassList;
    std::string line;
    getline(classes, line);

    while(getline(classes, line)) {
        std::stringstream ss(line);
        std::vector<std::string> fields;
        std::string field = "";
        while(getline(ss, field, ',')) { //Separate by tabs
            if(field.length() == 0) continue;
            fields.push_back(field);
        }

        Class newClass = Class(std::stoi(fields[0]), fields[1], fields[2], std::stoi(fields[3]), std::stoi(fields[4]));
        ClassList.push_back(newClass);
    }

    return ClassList;
}

std::ostream& operator<<(std::ostream& out, const MeetingPattern value){
    #define PROCESS_VAL(p) case(p): return out << #p;
    switch(value){
        PROCESS_VAL(M);
        PROCESS_VAL(T);
        PROCESS_VAL(W);
        PROCESS_VAL(R);
        PROCESS_VAL(F);
        PROCESS_VAL(MW);
        PROCESS_VAL(TR);
        PROCESS_VAL(MWF);
    }
    #undef PROCESS_VAL

    return out;
}