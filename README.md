# Student Handling System

A console-based university management application written in **C++**. It lets you manage students, professors and courses through an interactive, keyboard-driven menu built with **ncurses**. Data is saved to CSV files when you exit and loaded automatically on startup.

The user interface is in Greek.

## Features

- **Add** students, professors and courses
- **Search** for a member (by ID) or a course (by code)
- **Edit** member details (name, gender, semester for students, specialization for professors) and course details (name, semester, responsible professor)
- **Delete** members and courses
- **Duplicate protection**: members and courses with an already existing ID/code are rejected
- **Input validation**: a course's semester must be between 1 and 10, and a course can only be assigned to an existing professor
- **Persistent storage** in `members.csv` and `courses.csv`
- **Simulated email**: compose a message addressed to all students or all professors (displayed on screen, not actually sent)
- Arrow-key navigation (Up/Down + Enter) in all menus

## Main Menu

| # | Option |
|---|--------|
| 1 | Add student |
| 2 | Add professor |
| 3 | Add course |
| 4 | Search member |
| 5 | Search course |
| 6 | Edit member |
| 7 | Edit course |
| 8 | Delete member |
| 9 | Delete course |
| 10 | Send email to students |
| 11 | Send email to professors |
| 12 | Exit (saves data to CSV) |

## Project Structure

```
.
├── main.cpp        # Entry point, ncurses menu and user interaction
├── member.h/.cpp   # Abstract base class for people (ID, name, gender)
├── student.h/.cpp  # Student: derives from Member, adds current semester
├── prof.h/.cpp     # Professor: derives from Member, adds specialization
├── course.h/.cpp   # Course: code, description, semester, responsible professor
├── services.h/.cpp # Core logic: add/search/edit/remove, CSV load/save
├── members.csv     # Stored students and professors
└── courses.csv     # Stored courses
```

## Design Overview

- **`Member`** is an abstract class with a pure virtual `editDetails()`. It stores the ID as a dynamically allocated `char*` (managed in the constructor/destructor) plus name and gender.
- **`Student`** and **`Professor`** inherit from `Member` and implement their own `editDetails()` menu (**polymorphism**).
- **`Course`** holds a pointer to its responsible `Professor`. If that professor is deleted, the course's professor is reset to none.
- **`services`** owns all `Member*` and `Course*` objects in `std::vector`s, frees them in its destructor, and uses `dynamic_cast` to tell students and professors apart when saving to CSV.
- **Error handling** uses C++ exceptions (`std::logic_error`, `std::invalid_argument`, `std::out_of_range`, `std::runtime_error`), which `main` catches and shows to the user.

## Technologies

- C++ (classes, inheritance, polymorphism, STL vectors, exceptions, file I/O)
- ncurses (terminal user interface)

## Requirements

- A C++ compiler (e.g. `g++` or `clang++`)
- The ncurses library
  - **macOS**: included by default
  - **Ubuntu/Debian**: `sudo apt install libncurses-dev`
- A terminal with UTF-8 support (for Greek text)

## Build and Run

Clone the repository and compile all source files:

```bash
git clone https://github.com/thomasa27/Student-Handling-System.git
cd Student-Handling-System

g++ -o student_system main.cpp member.cpp student.cpp prof.cpp course.cpp services.cpp -lncurses
```

Run it **from the project folder**, since the CSV files are read from the current directory:

```bash
./student_system
```

Use the **Up/Down arrow keys** to move and **Enter** to select. Choose option **12** to exit, which saves your changes.

> If you get a "Δεν βρέθηκε αρχείο members.csv" message on first launch, create an empty `members.csv` file in the folder, or use the ones provided in this repository.

## Data Format

**`members.csv`**: one member per line

```
Student,<ID>,<name>,<gender>,<semester>
Professor,<ID>,<name>,<gender>,<specialization>
```

**`courses.csv`**: one course per line (`-` means no assigned professor)

```
<code>,<name>,<semester>,<professor ID>
```

Since the file is comma-separated, avoid commas inside names.

## Possible Improvements

- Enrolling students in courses and assigning courses to professors from the menu
- Real email sending instead of the simulation
- Escaping/quoting in the CSV format
- Unit tests and a build system (Makefile or CMake)

## Author

Thomas A. ([@thomasa27](https://github.com/thomasa27))
