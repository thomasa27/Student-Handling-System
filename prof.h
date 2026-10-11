#ifndef PROF_H
#define PROF_H

#include "member.h"
#include "course.h"
#include <string>
#include <vector>
#include <exception>


class Professor : public Member
{
    private:
    std::string specialization;
    std::vector <Course*> taughtcourses;

    public:
    Professor(const char* code, std::string name, std::string gender, std::string specialization);
    void assigncourse (Course*);
    void editDetails();

    std::string getspecialization() const;
    void setspec(std::string newspec);


};

#endif