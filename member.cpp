#include "member.h"
#include <string>
#include <cstring>

    Member::Member(const char* c, std::string name, std::string gender)
    {
        this->code = new char[strlen(c) +1];
        strcpy(this -> code, c);
        this->name = name;
        this->gender = gender;
    }

    Member::~Member()
    {
        delete[] code;
    }

    void Member::setcode(const char* c)
    {
        delete[] this -> code;
        this -> code = new char[strlen(c) + 1];
        strcpy(this -> code, c);
    }

    void Member::setname (std::string n)
    {
        this -> name = n;
    }

    void Member::setgender (std::string g)
    {
        this -> gender = g;
    }

    std::string Member::getgender() const 
    {
        return gender;
    }

    const char* Member::getcode() const 
    {
        return code;
    }

    std::string Member::getname() const 
    {
        return name;
    }