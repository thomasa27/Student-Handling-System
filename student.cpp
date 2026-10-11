#include "student.h"
#include "course.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <exception>
#include <curses.h>

using namespace std;


    Student::Student(const char* code, std::string name, std::string gender, unsigned int currentsemester) : Member(code, name, gender) 
    {
        this->currentsemester = currentsemester;
    }

    Student::Student(const char* code, std::string name) : Member(code, name, " ")
    {
        this -> currentsemester = 1;
    }

    Student::Student(const Student& original) : Member (original.getcode(), original.getname(), original.getgender())
    {
        this -> currentsemester = original.currentsemester;
        this -> enrolledcourses = original.enrolledcourses;
    }

    void Student::StudentsCourse(Course* newCourse)
    {
        enrolledcourses.push_back(newCourse);
    }

    void Student::editDetails()
{
    keypad(stdscr, TRUE);

    const char *list[] =
    {
        "1. Αλλαγή Ονόματος",
        "2. Αλλαγή Φύλου",
        "3. Αλλαγή Εξαμήνου",
        "Έξοδος"
    };

    int highlight = 0;
    int choice;
    int n = 4;

    while (true) 
    {
        clear();

        printw("Αλλαγή Στοιχείων Φοιτητή\n\n");

        for (int i = 0; i < n; i++) 
        {
            if (i == highlight)
                attron(A_REVERSE);

            printw("%s\n", list[i]);

            if (i == highlight)
                attroff(A_REVERSE);
        }

        refresh();

        choice = getch();

        switch (choice) 
        {
            case KEY_UP:
                highlight--;
                if (highlight < 0) highlight = n - 1;
                break;

            case KEY_DOWN:
                highlight++;
                if (highlight >= n) highlight = 0;
                break;

            case 10:
                clear();

                if (highlight == 0)
                {
                    clear();
                    printw("Πληκτρολογήστε το νέο όνομα: ");
                    
                    char newName [50];
                    getnstr(newName, 49);
                    setname(string(newName));

                    clear();
                    printw("Το όνομα ενημερώθηκε επιτυχώς\nΠατήστε οποιοδήποτε κουμπί για επιστροφή\n");
                    refresh();
                    getch();

                }

                else if (highlight == 1) 
                {
                    clear();
                    string newGender;
                    printw("Πληκτρολογήστε το νέο φύλο: ");
                    
                    char newgender [50];
                    getnstr(newgender, 49);
                    setgender(string(newgender));

                    clear();
                    printw("Το φύλο ενημερώθηκε επιτυχώς\nΠατήστε οποιοδήποτε κουμπί για επιστροφή\n");
                    refresh();
                    getch();
                }

                else if (highlight == 2) 
                {
                    clear();
                    printw("Πληκτρολογήστε το νέο εξάμηνο: ");
                    
                    char newsem [50];
                    getnstr(newsem, 49);
                    this -> currentsemester = (atoi(newsem));

                    clear();
                    printw("Το εξάμηνο ενημερώθηκε επιτυχώς\nΠατήστε οποιοδήποτε κουμπί για επιστροφή\n");
                    refresh();
                    getch();
                }

                else if (highlight == 3) 
                {
                    return;
                }
        }
    }

    endwin();

}



    unsigned int Student::getsemester() const
    {
        return currentsemester; 
    }

