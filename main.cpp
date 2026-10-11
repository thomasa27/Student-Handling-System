#include "member.h"
#include "student.h"
#include "prof.h"
#include "course.h"
#include "services.h"
#include <iostream>
#include <cstring>
#include <curses.h>

using namespace std;

int main(void)
{

    setlocale(LC_ALL, "");

    services uni;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);


    const char* menu[]=
        {
            "1. Προσθήκη Φοιτητή",
            "2. Προσθήκη Καθηγητή",
            "3. Προσθήκη Μαθήματος",
            "4. Αναζήτηση Μέλους",
            "5. Αναζήτηση Μαθήματος",
            "6. Επεξεργασία Μέλους",
            "7. Επεξεργασία Μαθήματος",
            "8. Διαγραφή Μέλους",
            "9. Διαγραφή Μαθήματος",
            "10. Αποστολή email σε φοιτητή",
            "11. Αποστολή email σε καθηγητή",
            "Τερματισμός Προγράμματος"
        };

    try
    {
        uni.loadFromCSV();
    }
    catch (const exception& e)
    {
        clear();
        printw("Αποτυχία!\n");
        printw(e.what());
        printw("Πατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
        getch();
    }

    /*
    Professor* gmele = new Professor("102", "Μελετίου", "αρσενικό","Προγραμματισμός");
    Professor* barlas = new Professor("118", "Μπάρλας", "αρσενικό","Μαθηματικά");
    Professor* voya = new Professor("100", "Βογιατζής", "αρσενικό", "Ψηφιακή Σχεδίαση");

    Student* alpos = new Student("24390001", "Άλπος", "αρσενικό", 3);
    Student* ioannou = new Student("24390002", "Ιωάννου", "αρσενικό", 3);
    Student* dimitriou = new Student("24390003", "Δημητρίου");

    Course* cpp = new Course("20", "'Αντικειμενοστρεφής Προγραμματισμός'", 2, gmele);
    Course* discmath = new Course("13", "Διακριτά Μαθηματικά", 1, barlas);
    Course* sjs = new Course("40", "Σχεδίαση Ψηφιακών Συστημάτων", 4, voya);

    try 
    {
        uni.addMember(gmele);
        uni.addMember(alpos);
        uni.addMember(barlas);
        uni.addMember(ioannou);
        uni.addMember(dimitriou);
        uni.addMember(voya);
        uni.addCourse(cpp);
        uni.addCourse(discmath);
        uni.addCourse(sjs);
    }
    catch (const exception& e)
    {
        clear();
        printw("Αποτυχία! Δεν έγινε εισαγωγή φοιττητών ή/και μαθημάτων στο τμήμα \nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
        printw(e.what());
        getch();
    }

    gmele -> assigncourse(cpp);
    barlas -> assigncourse(discmath);
    alpos -> StudentsCourse(cpp);

    */


    int highlight = 0;
    int choice;
    int n = 12;

    int height = 18;
    int width = 50;
    int starty = (LINES - height) / 2;
    int startx = (COLS -width) / 2;
    WINDOW* menuwin = newwin(height, width, starty, startx);
    keypad(menuwin, TRUE);

    while (true) 
    {
        clear();
        refresh();
        box(menuwin, 0, 0);

        mvwprintw(menuwin, 1, 14, "Αρχικό Μενού Επιλογών\n\n");
        mvwhline(menuwin, 2, 1, ACS_HLINE, width -2);

        for (int i = 0; i < n; i++) 
        {
            if (i == highlight)
                wattron(menuwin, A_REVERSE);

            mvwprintw(menuwin, i + 4, 4, "%s",  menu[i]);

            if (i == highlight)
                wattroff(menuwin, A_REVERSE);
        }

        wrefresh(menuwin);

        choice = wgetch(menuwin);

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
                wclear(menuwin);
                wrefresh(menuwin);
                clear();

            if (highlight == 0)
                {
                    clear();
                    printw("Πληκτρολογήστε τον ΑΜ του νέου φοιτητή: ");
                    char newam [50];
                    getnstr(newam, 49);
                    printw("Πληκτρολογήστε το όνομα του νέου φοιτητή: ");
                    char newname [50];
                    getnstr(newname, 49);
                    printw("Πληκτρολογήστε το φύλο του νέου φοιτητή: ");
                    char newgen [50];
                    getnstr(newgen, 49);
                    printw("Πληκτρολογήστε το εξάμηνο του νέου φοιτητή: ");
                    char newsem [50];
                    getnstr(newsem, 49);


                    Student* test = nullptr;
                    try
                    {
                        test = new Student(newam, newname, newgen, atoi(newsem));
                        uni.addMember(test);

                        printw("Ο φοιτητής προστέθηκε με επιτυχία\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                        refresh();
                        getch();
                        clear();
                    }

                    catch (const exception& e)
                    {
                        delete test;
                        clear();
                        printw("Αποτυχία!\n");
                        printw(e.what());
                        printw("\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                        refresh();
                        getch();
                    }

                    

                }
            else if (highlight == 1)
                {
                    clear();
                    printw("Πληκτρολογήστε τον ΑΜ του νέου καθηγητή: ");
                    char newam [50];
                    getnstr(newam, 49);
                    printw("Πληκτρολογήστε το όνομα του νέου καθηγητή: ");
                    char newname [50];
                    getnstr(newname, 49);
                    printw("Πληκτρολογήστε το φύλο του νέου καθηγητή: ");
                    char newgen [50];
                    getnstr(newgen, 49);
                    printw("Πληκτρολογήστε την ειδικότητα του νέου καθηγητη: ");
                    char newspec [50];
                    getnstr(newspec, 49);


                    Professor* test = nullptr;
                    try
                    {
                        test = new Professor(newam, newname, newgen, newspec);
                        uni.addMember(test);

                        printw("Ο καθηγητής προστέθηκε με επιτυχία\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                        refresh();
                        getch();
                    }

                        catch (const exception& e)
                        {
                            delete test;
                            clear();
                            printw("Αποτυχία!\n");
                            printw(e.what());
                            printw("\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");

                            getch();
                        }
                    
                }

            else if (highlight == 2)
                {
                    clear();
                    printw("Πληκτρολογήστε τον κωδικό του νέου μαθήματος: ");
                    char newcode [50];
                    getnstr(newcode, 49);
                    printw("Πληκτρολογήστε το όνομα του νέου μαθήματος: ");
                    char newname [50];
                    getnstr(newname, 49);
                    printw("Πληκτρολογήστε το εξάμηνο του νέου μαθήματος: ");
                    char newsem [50];
                    getnstr(newsem, 49);
                    printw("Πληκτρολογήστε το ΑΜ του υπεύθηνου καθηγητή του νεου μαθήματος: ");
                    char newprof [50];
                    getnstr(newprof, 49);


                    Course* test = nullptr;
                    try
                    {
                        Professor* prof = uni.getProfessor(string(newprof));
                        if (prof == nullptr)
                        {
                            throw invalid_argument("Δεν υπάρχει καθηγητής με αυτόν τον ΑΜ.");
                        }
                        test = new Course(newcode, newname, atoi(newsem), prof);
                        uni.addCourse(test);

                        printw("Το μάθημα προστέθηκε με επιτυχία\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                        refresh();
                        getch();
                    }

                    catch (const exception& e)
                    {
                        delete test;
                        clear();
                        printw("Αποτυχία!\n");
                        printw(e.what());
                        printw("\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                        getch();
                    }
                    
                }

            else if (highlight == 3)
                {
                    clear();
                    printw("Πληκτρολογίστε το ΑΜ του μέλους που ψάχνετε: ");
                    char search [50];
                    getnstr(search, 50);
                    clear();

                    try
                    {
                        uni.searchMember(string(search));
                        refresh();
                        getch();
                    }
                        catch (const exception& e)
                    {
                        clear();
                        printw("Αποτυχία!\n");
                        printw(e.what());
                        printw("\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                        getch();
                    }
                }

            else if (highlight == 4)
                {
                    clear();
                    printw("Πληκτρολογίστε τον κωδικό του μαθήματος που ψάχνετε: ");
                    char search [50];
                    getnstr(search, 50);
                    clear();

                    try
                    {
                        uni.searchCourse(string(search));
                        refresh();
                        getch();
                    }

                    catch (const exception& e)
                        {
                            clear();
                            printw("Αποτυχία!\n");
                            printw(e.what());
                            printw("\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                            getch();
                        }
                    
                }
            
            else if (highlight == 5)
                {
                    clear();
                    printw("Πληκτρολογίστε το ΑΜ του μέλους που θέλετε να αλλάξετε: ");
                    char am [50];
                    getnstr(am, 49);
                    try
                    {
                    uni.editMember(string(am));
                    }
                    catch (const exception& e)
                    {
                        clear();
                        printw("Αποτυχία!\n");
                        printw(e.what());
                        printw("\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                        getch();
                    }
                }

            else if (highlight == 6)
                {
                    clear();
                    printw("Πληκτρολογίστε τον κωδικό του μαθήματος που θέλετε να αλλάξετε: ");
                    char am [50];
                    getnstr(am, 49);
                    try
                    {
                    uni.editCourse(string(am));
                    }
                    catch (const exception& e)
                    {
                        clear();
                        printw("Αποτυχία!\n");
                        printw(e.what());
                        printw("\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                        getch();
                    }
                }

            else if (highlight == 7)
                {
                    clear();
                    printw("Πληκτρολογήστε τον ΑΜ του μέλους που θέλετε να διαγράψετε: ");
                    char am [50];
                    getnstr(am,49);
                    try
                    {
                    uni.removeMember(string(am));
                    }
                    catch (const exception& e)
                    {
                        clear();
                        printw("Αποτυχία!\n");
                        printw(e.what());
                        printw("\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                        getch();
                    }
                }

            else if (highlight == 8)
                {
                    clear();
                    printw("Πληκτρολογήστε τον κωδικό του μαθήματος που θέλετε να διαγράψετε: ");
                    char code [50];
                    getnstr(code,49);
                    try
                    {
                    uni.removeCourse(string(code));
                    }
                    catch (const exception& e)
                    {
                        clear();
                        printw("Αποτυχία!\n");
                        printw(e.what());
                        printw("\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                        getch();
                    }
                }

            else if (highlight == 9)
                {
                    clear();
                    printw("Πληκτρολογίστε το κείμενο που θέλετε να στείλετε:\n");
                    char msg [500];
                    getnstr(msg, 500);
                    try
                    {
                    uni.sendEmail(true, string(msg));
                    }
                    catch (const exception& e)
                    {
                        clear();
                        printw("Αποτυχία!\n");
                        printw(e.what());
                        printw("\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                        getch();
                    }
                }

            else if (highlight == 10)
                {
                    clear();
                    printw("Πληκτρολογίστε το κείμενο που θέλετε να στείλετε:\n");
                    char msg [500];
                    getnstr(msg, 500);
                    try
                    {
                    uni.sendEmail(false, string(msg));
                    }
                    catch (const exception& e)
                    {
                        clear();
                        printw("Αποτυχία!\n");
                        printw(e.what());
                        printw("\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                        getch();
                    }
                }

            else if (highlight == 11)
            {
                clear();
                refresh();
                    
                try
                {
                    uni.saveToCSV();
                } 
                catch (const exception& e)
                {
                    clear();
                    printw("Αποτυχία!\n");
                    printw(e.what());
                    printw("\nΠατήστε οποιδήποτε κουμπί για να συνεχίσετε\n");
                    getch();
                }
                    endwin();
                    return 0;
            }
            break;
        }         
}
    return 0;
}