#ifndef COURSE_H
#define COURSE_H

#include <string>

class Professor;

class Course
{
    private:
    std::string code;
    std::string description;
    int semester;
    Professor* mainprof;

    public:
    Course(std::string code, std::string description, int semester, Professor* mainprof);

    std::string getcode();
    std::string getname();
    void setname(std::string n);
    void setsemester(int s);
    void setprof(Professor* mp);
    int getsemester() const;
    Professor* getprof() const;
};
#endif