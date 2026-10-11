#include "course.h"
#include <exception>
#include <stdexcept>

Course::Course(std::string code, std::string description, int semester, Professor* mainprof)
{
    if (semester <= 0 || semester > 10)
    {
        throw std::out_of_range("Το εξάμηνο πρέπει να είναι από 1 έως και 10");
    }
    this->code = code;
    this->description = description;
    this->semester = semester;
    this->mainprof = mainprof;
}

std::string Course::getcode() {
    return code;
}

std::string Course::getname() {
    return description;
}

void Course::setname(std::string n) {
    this->description = n;
}

void Course::setsemester(int s) {
    this->semester = s;
}

void Course::setprof(Professor* mp) {
    this->mainprof = mp;
}

int Course::getsemester() const {
    return semester;
}

Professor* Course::getprof() const { 
    return mainprof; 
}