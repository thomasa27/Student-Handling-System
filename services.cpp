#include "services.h"
#include "student.h"
#include "prof.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <curses.h>

using namespace std;

    services::~services()
    {
        for (int i = 0; i < members.size(); i++) delete members[i];
        for (int i = 0; i < courses.size(); i++) delete courses[i];
    }

    void services::addMember(Member* newMember)
    {
        for (int i = 0; i < members.size(); i++)
        {
            if (string(members.at(i)->getcode()) == string(newMember->getcode()))
            {
                throw logic_error("Δεν προστέθηκε αυτό το μέλος! Υπάρχει ήδη κάποιο μέλος με τον ίδιο ΑΜ");
            }
        }
        members.push_back(newMember);
    }

    void services::addCourse(Course* newCourse)
        {
            for (int i = 0; i < courses.size(); i++)
            {
                if (string(courses.at(i) -> getcode()) == string(newCourse -> getcode()))
                {
                    throw logic_error("Δεν προστέθηκε αυτο το μέλος στο τμήμα! Υπαρχει ήδη καποιο μέλος με τον ίδιο ΑΜ");
                }
            }
            courses.push_back(newCourse);
        }

    void services::searchMember(string codestr)
    {
        bool found = false;
        for (int i=0; i < members.size(); i++)
        {
            if (members.at(i)->getcode() == codestr)
            {
                string a = members.at(i) -> getcode();
                string b = members.at(i) -> getname();
                string c = members.at(i) -> getgender();
                printw("ΑΜ Μέλους: %s\n", a.c_str());
                printw("Όνομα Μέλους: %s\n", b.c_str());
                printw("Φύλο μέλους: %s\n", c.c_str());
                refresh();
                found = true;
            }
        }
        if (!found)
            throw invalid_argument("Δεν υπάρχει μέλος με ΑΜ: " + codestr + "\n");
    }
    
    void services::searchCourse(string codestr)
    {
        bool found = false;
        for (int i=0; i < courses.size(); i++)
        {
            if (courses.at(i)->getcode() == codestr)
            {
                string a = courses.at(i) -> getcode();
                string b = courses.at(i) -> getname();
                int c = courses.at(i) ->  getsemester();
                Professor* d = courses.at(i) -> getprof();
                printw("Κωδικός Μαθήματος: %s\n", a.c_str());
                printw("Όνομα μαθήματος: %s\n", b.c_str());
                printw("Εξάμηνο Μαθήματος: %d\n", c);
                if (d != nullptr)
                {
                    printw("Υπεύθηνος καθηγητής: %s\n", d -> getcode());
                }
                
                refresh();
                found = true;
            }
        }
        if (!found)
            throw invalid_argument("Δεν υπάρχει μάθημα με κωδικό: " + codestr + "\n");
    }

    void services::removeMember(string codestr)
    {
        bool found = false;
        for (int i=0; i < members.size(); i++)
        {
            if (Professor* p = dynamic_cast<Professor*>(members.at(i)))
            {
                for (int j = 0; j < courses.size(); j++)
                {
                    if (courses.at(j)->getprof() == p) 
                    {
                    courses.at(j)->setprof(nullptr);
                    }
                }
            }
            if (members.at(i)->getcode() == codestr)
            {
                delete members.at(i);
                members.erase(members.begin() + i);
                found = true;
                clear();
                printw("Το μέλος διαγράφηκε με επιτυχία\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                refresh();
                getch();
            }
        }
        if (!found)
            throw invalid_argument("Δεν υπάρχει μέλος με κωδικό: " + codestr + "\n");
    }

    void services::removeCourse(string codestr)
    {
        bool found = false;
        for (int i=0; i < courses.size(); i++)
        {
            if (courses.at(i)->getcode() == codestr)
            {
                delete courses.at(i);
                courses.erase(courses.begin() + i);
                found = true;
                clear();
                printw("Το μάθημα διαγράφηκε με επιτυχία\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                refresh();
                getch();
            }
        }
        if (!found)
            throw invalid_argument("Δεν υπάρχει μάθημα με κωδικό: " + codestr + "\n");
    }

    void services::editMember(string codestr)
    {
        bool found = false;
        for (int i=0; i < members.size(); i++)
        {
            if (members.at(i)->getcode() == codestr)
            {
                members.at(i)->editDetails();
                found = true;
            }
        }
        if (!found)
            throw invalid_argument("Δεν υπάρχει μέλος με ΑΜ: " + codestr + "\n");
    }

    void services::editCourse(string codestr)
    {
        bool found = false;
        for (int i=0; i < courses.size(); i++)
        {
            if (courses.at(i)->getcode() == codestr)
            {
                const char* list[] =
                {
                    "1. Αλλαγή Ονόματος",
                    "2. Αλλαγή Εξαμήνου",
                    "3. Αλλαγή Υπεύθηνου Καθηγητή",
                    "Έξοδος"
                };

                int highlight = 0;
                int choice;
                int n=4;

                while (true)
                {
                    clear();
                    printw("Αλλαγή Στοχείων Μαθήματος\n\n");

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
                                courses.at(i)->setname(newName);

                                clear();
                                printw("Το όνομα ενημερώθηκε επιτυχώς\nΠατήστε οποιοδήποτε κουμπί για επιστροφή\n");
                                refresh();
                                getch();
                            }

                            else if (highlight == 1)
                            {
                                clear();
                                printw("Πληκτρολογήστε το νέο εξάμηνο: ");
                        
                                char newSem [50];
                                getnstr(newSem, 49);
                                courses.at(i)->setsemester(atoi(newSem));

                                clear();
                                printw("Το εξάμηνο ενημερώθηκε επιτυχώς\nΠατήστε οποιοδήποτε κουμπί για επιστροφή\n");
                                refresh();
                                getch();
                            }

                            else if (highlight == 2)
                            {
                                clear();
                                printw("Πληκτρολογήστε τον ΑΜ του νέου υπεύθηνου καθηγητή: ");
                                Professor* newprof = nullptr;
                                bool found = false;
                                

                                char newcode [50];
                                getnstr(newcode, 49);
                                for (int j=0; j < members.size(); j++)
                                {
                                    if (string(members.at(j)->getcode()) == string(newcode))
                                    {
                                        newprof = dynamic_cast<Professor*>(members.at(j));

                                        if (newprof != nullptr) 
                                        {
                                            courses.at(i)->setprof(newprof);
                                            found = true;

                                            clear();
                                            printw("Ο υπεύθηνος καθηγητής ενημερώθηκε επιτυχώς\nΠατήστε οποιοδήποτε κουμπί για επιστροφή\n");
                                        refresh();
                                        getch();
                                        } 
                                        break;
                                    }
                                }
                                if (!found)
                                {
                                    throw invalid_argument("Δεν βρέθηκε καθηγητής με αυτόν τον ΑΜ!");
                                }
                            }
                            else if (highlight == 3)
                            {
                                return;
                            }
                    }
                }
            }
        }
        if (!found)
            throw invalid_argument("Δεν υπάρχει μάθημα με κωδικό: " + codestr + "\n");
    }

    void services::sendEmail(bool receiver, string message)
    {
            if (receiver == true)
            {
                clear();
                printw("Το email στάλθηκε στους φοιτητες \n");
            }
            else
            {
                clear();
                printw("Το email στάλθηκε στους καθηγητες\n");
            }

            printw("Κείμενο:\n");
            printw("%s\n", message.c_str());
            printw("Πατήστε οποιοδήποτε κουμπί για να συνεχίσετε");
            refresh();
            getch();
    }

    void services::saveToCSV()
    {
        ofstream memb("members.csv");
        if (!memb.is_open())
        {
            throw runtime_error("Αδυναμία δημιουργίας του members.csv");
        }

        for (int i = 0; i < members.size(); i++)
        {
            if (Student* s = dynamic_cast<Student*>(members.at(i)))
            {
                memb << "Student," << s->getcode() << "," << s->getname() << "," << s->getgender() << "," << s->getsemester() << "\n";
            } 
            else if (Professor* p = dynamic_cast<Professor*>(members.at(i)))
            {
                memb << "Professor," << p->getcode() << "," << p->getname() << "," << p->getgender() << "," << p->getspecialization() << "\n";
            }
        }
        memb.close();

        ofstream cour("courses.csv");
        if (!cour.is_open())
        {
            throw runtime_error("Αδυναμία δημιουργίας του courses.csv");
        }

        for (int i = 0; i < courses.size(); i++)
        {
            string profCode;
            if (courses.at(i)->getprof() != nullptr) 
            {
                profCode = string(courses.at(i)->getprof()->getcode());
            } 
            else 
                profCode = "-";
            cour << courses.at(i)->getcode() << "," << courses.at(i)->getname() << "," << courses.at(i)->getsemester() << "," << profCode << "\n";
        }
        cour.close();
    }

    void services::loadFromCSV()
        {
            ifstream memb("members.csv");
            if (!memb.is_open())
            {
                throw runtime_error("Δεν βρέθηκε αρχείο members.csv");
            }

            string line;
            while (getline(memb, line))
            {
                stringstream ss(line);
                string type, code, name, gender, semspec;
                
                getline(ss, type, ',');
                getline(ss, code, ',');
                getline(ss, name, ',');
                getline(ss, gender, ',');
                getline(ss, semspec, ',');

                if (type == "Student")
                {
                    int sem = stoi(semspec);
                    members.push_back(new Student(code.c_str(), name, gender, sem));
                }
                else if (type == "Professor")
                {
                    members.push_back(new Professor(code.c_str(), name, gender, semspec));
                }
            }
            memb.close();

            ifstream cour("courses.csv");
            if (cour.is_open())
            {
                while (getline(cour, line))
                {
                    stringstream ss(line);
                    string code, name, sem, profCode;
                    
                    getline(ss, code, ',');
                    getline(ss, name, ',');
                    getline(ss, sem, ',');
                    getline(ss, profCode, ',');

                    Professor* p = nullptr;
                    if (profCode != "-")
                    {
                        for (int i = 0; i < members.size(); i++)
                        {
                            if (string(members.at(i)->getcode()) == profCode)
                            {
                                p = dynamic_cast<Professor*>(members.at(i));
                                break;
                            }
                        }
                    }
                    
                    int semester = stoi(sem);
                    courses.push_back(new Course(code, name, semester, p));
                    
                }
                cour.close();
                cout << "Επιτυχής φόρτωση δεδομένων από τα CSV" << endl;
            }
        }

    Professor* services::getProfessor(string codestr)
    {
        for (int i = 0; i < members.size(); i++)
        {
            if (members.at(i)->getcode() == codestr)
            {
                Professor* prof = dynamic_cast<Professor*>(members.at(i));
                
                if (prof != nullptr) {
                    return prof;
                }
            }
        }
        return nullptr;
    }