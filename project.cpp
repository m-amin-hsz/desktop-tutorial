#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>    // baraye barresi (y/n)
#include <cstdlib>   // baraye system(cls0 va system(clear)
#ifdef _WIN32 // code baraaye windows ro sharti mikone
    #include <conio.h>  // karbar har kelidi zad console refresh beshe
#endif
#include <limits>    // jelo  giri az khoroj verodi ha az mahdode mojaz

using namespace std;

const int MAX_STUDENTS = 20;  // hadeaksr tedad daneshjo
const int MAX_COURSES = 7;    //hadeaksar tedad dars hayii ke mishe bardasht

// sakhtar dars
struct Course {
    string courseName; // esm dars
    float grade;       // nomre dars
    int credits;       //  vahed dars
};

// sakhtar daneshjo
struct Student {
    string fullName;      // esm kamel
    int studentID;        // ID daneshjo
    string major;         // reshte tahsili daneshjo
    Course courses[MAX_COURSES]; // araye dars ha
    int courseCount;      // tedad dars haye sabt shode
};

// tabe baraye mohasebe moadel
float calculateAverage(const Student &student) {
    float totalScore = 0;
    int totalCredits = 0;
    for (int i = 0; i < student.courseCount; i++) {
        totalScore += student.courses[i].grade * student.courses[i].credits;
        totalCredits += student.courses[i].credits;
    }
    if (totalCredits > 0)
        return totalScore / totalCredits;
    else
        return 0;
}

// refresh kardan console
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// tabeii ke montazer mimanad karbar kelidi ra feshr dahad
void waitForKeyPress() {
    cout << "\nPress any key to continue...";
    #ifdef _WIN32
        _getch();
    #else
        cin.get();
    #endif
}

// çbara chap karnameh
void printReportCard(const Student &student) {
    float avg = calculateAverage(student);
    
    cout << "\n================= Report Card =================\n";
    cout << "Full Name       : " << student.fullName << endl;
    cout << "Student ID      : " << student.studentID << endl;
    cout << "Major           : " << student.major << endl;
    cout << "Average         : " << fixed << setprecision(2) << avg << endl;
    cout << "-----------------------------------------------\n";
    
    cout << left << setw(30) << "Course Name" 
         << setw(10) << "Unit" 
         << setw(10) << "Grade" << endl;
    cout << "-----------------------------------------------\n";
    
    for (int i = 0; i < student.courseCount; i++) {
        cout << left << setw(30) << student.courses[i].courseName 
             << setw(10) << student.courses[i].credits 
             << setw(10) << student.courses[i].grade << endl;
    }
    cout << "===============================================\n";
}

// baraye ezafe kardan daneshjo
void addStudent(Student students[], int &studentCount) {
    if(studentCount >= MAX_STUDENTS) {
        cout << "The student registration capacity is full.\n";
        return;
    }
    
    Student &student = students[studentCount];
    student.courseCount = 0;  // meghdar avalieh dars aye daneshjo
    
    cout << "\n--- Enter Student Data ---\n";
    cout << "Full name: ";
    getline(cin, student.fullName);
    
    cout << "Student ID: ";
    cin >> student.studentID;
    cin.ignore(); // jelo giri az verod araye khali
    
    cout << "Major: ";
    getline(cin, student.major);
    
    // ezafe kardan dars
    char addCourse;
    do {
        if (student.courseCount >= MAX_COURSES) {
            cout << "The course registration capacity is full!\n";
            break;
        }
        
        Course &course = student.courses[student.courseCount];
        cout << "\nCourse name: ";
        getline(cin, course.courseName);
        
        cout << "Course grade: ";
        cin >> course.grade;
        
        cout << "Course credit: ";
        cin >> course.credits;
        cin.ignore();
        
        student.courseCount++;  // «›“«Ì‘  ⁄œ«œ œ—”ùÂ«
        
        cout << "\nWant to add more courses? (Y/N): ";
        cin >> addCourse;
        cin.ignore();
    } while(toupper(addCourse) == 'Y');
    
    studentCount++;
    cout << "\nStudent added.\n";
}

// virayesh dars
void editCourse(Student &student) {
    if (student.courseCount == 0) {
        cout << "No course for this student.\n";
        return;
    }
    
    cout << "\nList of courses:\n";
    for (int i = 0; i < student.courseCount; i++) {
        cout << i+1 << ". " << student.courses[i].courseName 
             << " (Unit: " << student.courses[i].credits 
             << ", Grade: " << student.courses[i].grade << ")\n";
    }
    
    int index;
    cout << "Enter course number to edit: ";
    cin >> index;
    cin.ignore();
    if (index < 1 || index > student.courseCount) {
        cout << "Wrong course number!\n";
        return;
    }
    
    Course &course = student.courses[index - 1];
    cout << "\n--- Edit Course ---\n";
    cout << "Course name (Ex: " << course.courseName << "): ";
    getline(cin, course.courseName);
    
    cout << "Course grade (Ex: " << course.grade << "): ";
    cin >> course.grade;
    
    cout << "Course credit (Ex: " << course.credits << "): ";
    cin >> course.credits;
    cin.ignore();
    
    cout << "Course edited.\n";
}

// hazf dars
void deleteCourse(Student &student) {
    if (student.courseCount == 0) {
        cout << "No courses for this student.\n";
        return;
    }
    
    cout << "\nList of courses:\n";
    for (int i = 0; i < student.courseCount; i++) {
        cout << i+1 << ". " << student.courses[i].courseName 
             << " (Unit: " << student.courses[i].credits 
             << ", Grade: " << student.courses[i].grade << ")\n";
    }
    
    int index;
    cout << "Enter course number to delete: ";
    cin >> index;
    cin.ignore();
    if (index < 1 || index > student.courseCount) {
        cout << "Wrong course number.\n";
        return;
    }
    
    // jabjaii dars 
    for (int i = index - 1; i < student.courseCount - 1; i++) {
        student.courses[i] = student.courses[i+1];
    }
    student.courseCount--;
    
    cout << "Course deleted.\n";
}

// ezafe kardan dars 
void addCourse(Student &student) {
    if (student.courseCount >= MAX_COURSES) {
        cout << "The course registration capacity is full.\n";
        return;
    }
    
    Course &course = student.courses[student.courseCount];
    cout << "\n--- Add New Course ---\n";
    cout << "Course name: ";
    getline(cin, course.courseName);
    
    cout << "Course grade: ";
    cin >> course.grade;
    
    cout << "Course credit: ";
    cin >> course.credits;
    cin.ignore();
    
    student.courseCount++;
    cout << "New course added.\n";
}

// virayesh etekaat daneshjo
void editStudent(Student students[], int studentCount) {
    int selectedID;
    cout << "\nFor editing, enter Student ID: ";
    cin >> selectedID;
    cin.ignore();
    
    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == selectedID) {
            found = true;
            cout << "\n--- Edit Student Data ---\n";
            cout << "Full name (Ex: " << students[i].fullName << "): ";
            getline(cin, students[i].fullName);
            
            cout << "Student ID (Ex: " << students[i].studentID << "): ";
            cin >> students[i].studentID;
            cin.ignore();
            
            cout << "Major (Ex: " << students[i].major << "): ";
            getline(cin, students[i].major);
            
            char courseChoice;
            do {
                cout << "\nWhich course operation do you choose?\n";
                cout << "1. Edit course\n";
                cout << "2. Delete course\n";
                cout << "3. Add course\n";
                cout << "4. Exit course menu\n";
                cout << "Choice: ";
                cin >> courseChoice;
                cin.ignore();
                
                switch(courseChoice) {
                    case '1':
                        editCourse(students[i]);
                        break;
                    case '2':
                        deleteCourse(students[i]);
                        break;
                    case '3':
                        addCourse(students[i]);
                        break;
                    case '4':
                        cout << "Exiting course menu.\n";
                        break;
                    default:
                        cout << "Wrong choice!\n";
                }
            } while(courseChoice != '4');
            
            cout << "\nStudent data edited successfully.\n";
            break;
        }
    }
    
    if (!found)
        cout << "Student with ID " << selectedID << " not found.\n";
}

// hazf daneshjo
void deleteStudent(Student students[], int &studentCount) {
    int selectedID;
    cout << "\nFor deleting, enter Student ID: ";
    cin >> selectedID;
    cin.ignore();
    
    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == selectedID) {
            found = true;
            //jabejayii daneshjo
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            cout << "Student with ID " << selectedID << " deleted.\n";
            break;
        }
    }
    
    if (!found)
        cout << "Student with ID " << selectedID << " not found.\n";
}

// namayesh karnameh
void showReportCard(Student students[], int studentCount) {
    int selectedID;
    cout << "\nFor report card, enter Student ID: ";
    cin >> selectedID;
    cin.ignore();
    
    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == selectedID) {
            printReportCard(students[i]);
            found = true;
            break;
        }
    }
    
    if (!found)
        cout << "Student with ID " << selectedID << " not found.\n";
}

// tabe namayesh list az bala be payiin
void listStudentsByMajor(Student students[], int studentCount) {
    if(studentCount == 0) {
        cout << "No students!\n";
        return;
    }
    
    string uniqueMajors[MAX_STUDENTS];
    int numMajors = 0;
    
    for (int i = 0; i < studentCount; i++) {
        bool found = false;
        for (int j = 0; j < numMajors; j++) {
            if (students[i].major == uniqueMajors[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            uniqueMajors[numMajors++] = students[i].major;
        }
    }
    
    for (int m = 0; m < numMajors; m++) {
        Student temp[MAX_STUDENTS];
        int count = 0;
        
        for (int i = 0; i < studentCount; i++) {
            if (students[i].major == uniqueMajors[m]) {
                temp[count++] = students[i];
            }
        }
        
        // moratab kardan bala be payin bar asas moadel
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                if (calculateAverage(temp[i]) < calculateAverage(temp[j])) {
                    Student t = temp[i];
                    temp[i] = temp[j];
                    temp[j] = t;
                }
            }
        }
        
        cout << "\n----------------- " << uniqueMajors[m] << " -----------------\n";
        for (int i = 0; i < count; i++) {
            cout << left << setw(25) << temp[i].fullName 
                 << " : " << fixed << setprecision(2) << calculateAverage(temp[i]) << endl;
        }
    }
}

int main() {
    Student students[MAX_STUDENTS];  
    int studentCount = 0;            
    int choice;
    
    do {
        // montazer naraye clear kardan
        waitForKeyPress();
        clearScreen();
        
        cout << "\n================ Main Menu ================\n";
        cout << "1. Add Student\n";
        cout << "2. Report Card\n";
        cout << "3. List of Top Students\n";
        cout << "4. Edit Student Data\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Your choice: ";
        
        // barresi verodi dorost
        if (!(cin >> choice)) {
            cin.clear(); // Åclear kardan vorodi eshteba
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // hazf verodi eshtebah
            cout << "Invalid input. Please enter a number.\n";
            continue;  // bazgasht be halghe
        }
        
        cin.ignore(); 
        
        switch (choice) {
            case 1:
                addStudent(students, studentCount);
                break;
            case 2:
                showReportCard(students, studentCount);
                break;
            case 3:
                listStudentsByMajor(students, studentCount);
                break;
            case 4:
                editStudent(students, studentCount);
                break;
            case 5:
                deleteStudent(students, studentCount);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Wrong number, try again.\n";
        }
    } while(choice != 6);
    
    return 0;
}

