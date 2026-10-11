#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <cstring>

class Member 
{
    private:
    char* code;
    std::string name;
    std::string gender;

    public:
    Member(const char* c, std::string name, std::string gender);
    virtual ~Member();
    virtual void editDetails() = 0;
    void setcode(const char* c);
    void setname (std::string n);
    void setgender (std::string g);
    std::string getgender() const;
    const char* getcode() const;
    std::string getname() const ;
};

#endif