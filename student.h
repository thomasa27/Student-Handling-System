#ifndef STUDENT_H
#define STUDENT_H

#include "member.h"
#include "course.h"
#include <string>
#include <iostream>
#include <vector>
#include <exception>

class Course;
class Student : public Member
{
    private:

    unsigned int currentsemester;
    std::vector <Course*> enrolledcourses;

    public:
    Student(const char* code, std::string name, std::string gender, unsigned int currentsemester);

    Student(const char* code, std::string name);

    Student(const Student& original);

    void StudentsCourse(Course*);
    void editDetails();
    unsigned int getsemester() const;
    
};

#endif