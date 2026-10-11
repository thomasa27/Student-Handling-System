#include "prof.h"
#include "course.h"
#include <iostream>
#include <cstring>
#include <exception>
#include <curses.h>
#include <locale.h>

using namespace std;


    Professor::Professor(const char* code, std::string name, std::string gender, std::string specialization) : Member(code, name, gender)
    {
        this->specialization = specialization;
    }

    void Professor::assigncourse (Course* newcourse)
    {
        taughtcourses.push_back(newcourse);
    }

    void Professor::editDetails()
{

    keypad(stdscr, TRUE);

    const char *list[] =
    {
        "1. Αλλαγή Ονόματος",
        "2. Αλλαγή Φύλου",
        "3. Αλλαγή Ειδικότητας",
        "Έξοδος"
    };

    int highlight = 0;
    int choice;
    int n = 4;

    while (true) 
    {
        clear();

        printw("Αλλαγή Στοιχείων Καθηγητή\n\n");

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
                    printw("Πληκτρολογήστε την νέα ειδικότητα: ");
                    
                    char newspec [50];
                    getnstr(newspec, 49);
                    setspec(string(newspec));

                    clear();
                    printw("Η ειδικότητα ενημερώθηκε επιτυχώς\nΠατήστε οποιοδήποτε κουμπί για επιστροφή\n");
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

    std::string Professor::getspecialization() const
    {
        return specialization;
    }

    void Professor::setspec(std::string newspec)
    {
        this -> specialization = newspec;
    }

