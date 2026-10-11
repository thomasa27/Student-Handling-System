#ifndef SERVICES_H
#define SERVICES_H

#include "member.h"
#include "course.h"
#include <vector>
#include <string>

class services
{
private:
    std::vector<Member*> members; 
    std::vector<Course*> courses;

public:
    ~services();

    void addMember(Member* newMember);
    void addCourse(Course* newCourse);
    void searchMember(std::string codestr);
    void searchCourse(std::string codestr);
    void removeMember(std::string codestr);
    void removeCourse(std::string codestr);
    void editMember(std::string codestr);
    void editCourse(std::string codestr);
    void sendEmail(bool receiver, std::string message);
    void saveToCSV();
    void loadFromCSV();
    Professor* getProfessor(std::string code);
};    

#endif