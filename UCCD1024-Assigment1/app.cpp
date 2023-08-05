#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include    <iomanip>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"


using namespace std;

//constant
const string STUDENT_INFO_FILE = "student.txt";
const string BOOK_FILE = "book.txt";

//function prototype
bool isDuplicate(List* list, LibStudent& student);
void center(string);
int calculateJulianDate(int year, int month, int day);
bool printList(List);
bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool SearchStudent(List*, char* id, LibStudent&);
bool InsertBook(string, List*);    
bool Display(List*, int, int);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu();

int main() {
    List studentList; // Create an instance of the List class
    List type1, type2;
    char id[10];
    LibStudent stu;
    int detail = 0, source = 0;
    int choice;
    bool stop = false;
    do {
        choice = menu();
        switch (choice) {
        case 1:

            if (ReadFile(STUDENT_INFO_FILE, &studentList))
            {
                cout << studentList.size() << " records have been successfully read." << endl;
            }
            else
            {
                cout << "Failed to read data or encountered an error." << endl;
            }

            system("pause");
            break;

        case 2:

            if (DeleteRecord(&studentList, id)) {
                cout << "Student Record has been removed...." << endl;;
            }
            else {
                cout << "Failed to remove student record!!" << endl;
            }

            system("pause");
            break;

        case 3:

            if (SearchStudent(&studentList, id, stu)) {
                cout << "Student Found" << endl;
                cout << "Student Information:" << endl;
                stu.print(cout);
                cout << "Total Books: " << stu.totalbook;
                cout << endl;
            }
            else {
                cout << "Student Not Found." << endl;
            }
            system("pause");
            break;

        case 4:

            if (InsertBook(BOOK_FILE, &studentList)) {
                cout << "Books inserted successfully to student list" << endl;
            }
            else {
                cout << "An error has occured" << endl;
            }
            system("pause");
            break;

        case 5:

            if (Display(&studentList, source, detail)) {

            }
            system("pause");
            break;

        case 6:

            if (computeAndDisplayStatistics(&studentList)) {
                cout << "Statistics computed and displayed successfully." << endl;
            }
            else {
                cout << "Empty list. Unable to compute statistics." << endl;
            }
            system("pause");
            break;
            {
                computeAndDisplayStatistics(&studentList);
            }

            break;

        case 7:

            char callNum[20];
            cout << "Enter the call number of the book: ";
            cin >> callNum;

            printStuWithSameBook(&studentList, callNum);

            system("pause");
            break;

        case 8:

            if (displayWarnedStudent(&studentList, &type1, &type2))
            {
                cout << "Type 1 warning student list" << endl;
                cout << "****************************************************************************" << endl;
                printList(type1);
                cout << endl;

                cout << "Type 2 warning student list" << endl;
                cout << "****************************************************************************" << endl;
                printList(type2);
            }
            else
            {
                cout << "Student list is empty." << endl;
            }

            system("pause");
            break;

        case 9:

            stop = true;
            break;

        default:

            cout << "Invalid Input!\a" << endl;
            system("pause");

        }

        cin.clear();
        cin.ignore();
        cout << endl;

    } while (!stop);

	cout << "\n\n";
    system("pause");
    return 0;
}
//******************************************************(Additional Functions)************************************************
//function to place words in the center of output
void center(string string) {
    const int WIDTH = 115;
    int space = (WIDTH - string.length()) / 2;
    cout << setw(space + string.length()) << string << endl;
}

// function to check if a student record is a duplicate in the list
bool isDuplicate(List* list, LibStudent& student) {

    Node* cur;

    //list will not duplicate if it is empty
    if (list->empty())
    {
        return false;
    }

    cur = list->head; //start traversing from the first node

    while (cur != NULL)
    {
        if (cur->item.compareName2(student))
            return true;
        else
            cur = cur->next; //move to next node in the list
    }
    return false;
}
    
//*****************************************************************(1)*******************************************************
// Read student information from the file "student.txt" and store it in the linked list
bool ReadFile(string filename, List* list) {
    
    ifstream in;

    char text[256];

    LibStudent newStudent;

    in.open(filename);

    //return false if the file is not found
    if (!in)
    {
        return false;
    }
    
    while (!in.eof())
    {
        //ignore "Student Id ="
        for (int j = 0; j < 3; j++)
            in >> text;

        //assign student id
        in >> newStudent.id;

        //ignore "Name ="
        for (int j = 0; j < 2; j++)
            in >> text;

        //assign student name
        in >> newStudent.name;
        in.getline(text, 256);
        strcat_s(newStudent.name, text);

        //ignore "course ="
        for (int j = 0; j < 2; j++)
            in >> text;

        //assign course
        in >> newStudent.course;

        //ignore "Phone Number ="
        for (int j = 0; j < 3; j++)
            in >> text;

        //assign phone number
        in >> newStudent.phone_no;


        // Check if the student is a duplicate, if not then insert student into the list
        if (!isDuplicate(list, newStudent)) 
        {
            list->insert(newStudent);
        }
    }

    in.close();
    return true;
}

//*****************************************************************(2)***************************************************
//Delete record for existing student through input of student ID
bool DeleteRecord(List* list, char* id) {
    char del[10];
    cout << "Please Enter the Student ID you would like to delete: ";//Prompt user to input student id
    cin >> del;

    int position = 1;
    Node* cur = list->head;//Start traversing from first node
    type temp;

    while (cur != NULL) {
        if (strcmp(cur->item.id, del) == 0) { //Compare student ID with user input
            if (list->get(position, temp)) {//Use the get function to obtain intended linked list
                list->remove(position);//Use function to remove link list
                return true;
            }
        }
        else {  // Move to the next node in the list
            cur = cur->next;
            position++;
        }
    }

    return false;
}

//*************************************************************(3)****************************************************
//Search for student through input of student ID
bool SearchStudent(List* list, char* id, LibStudent& stu) {
    char code[10];
    cout << "Please Enter the Student ID you would like to search: ";//prompt user to input student ID
    cin >> code;

    Node* cur = list->head;// Start traversing from first node

    while (cur != NULL)
    {
        if (strcmp(cur->item.id, code) == 0) // Compare student ID in linked list with input of user
        {
            stu = cur->item; // Copy the found student data to the 'stu' reference
            return true;
        }
        else
            cur = cur->next; // Move to the next node in the list
    }
    return false;
}

//*********************************************(4)*************************************************
bool InsertBook(string filename, List* list) {
    ifstream in(filename);
    if (!in) {
        cout << "Cannot open the " << filename << endl;
        return false;
    }

    int current = calculateJulianDate(2020, 3, 29);
    int componentValue = 0;

    while (!in.eof()) {
        LibBook book;
        LibStudent student;
        char readID[10], author[256], temp[256], borrow[256], due[256];
        int x = 0, y = 0, i = 0, a = 0, b = 0;
        book.fine = 0;

        in >> readID >> author >> book.title >> book.publisher >> book.ISBN >> book.yearPublished >> book.callNum >> borrow >> due;
        
        // Ignore the character '_'
        for (char* ptr = author; *ptr != '\0'; ptr++) {
            if (*ptr == '_') *ptr = ' ';
        }
        for (char* ptr1 = book.title; *ptr1 != '\0'; ptr1++) {
            if (*ptr1 == '_') *ptr1 = ' ';
        }
        for (char* ptr3 = book.publisher; *ptr3 != '\0'; ptr3++) {
            if (*ptr3 == '_') *ptr3 = ' ';
        }

        // Loop to extract authors from the 'author' string
        while (author[i] != '\0') {
            if (author[i] != '/') {
                temp[x] = author[i];
                x++;
            } else {
                temp[x] = ' ';
                x++;
                for (int j = 0; j < 5; j++) {
                    temp[x] = ' ';
                    x++;
                }
                while (author[i] == '/') {
                    i++;
                }
                i--;
            }

            if (author[i + 1] == '\0') {
                temp[x] = '\0';
                book.author[y] = new char[256];
                strcpy(book.author[y], temp);
                x = 0;
                y++;
            }
            i++;
        }

        // Loop to extract day, month, and year from the 'borrow' string
        for (int i = 0; borrow[i] != '\0'; i++) {
            if (borrow[i] != '/') {
                componentValue = componentValue * 10 + (borrow[i] - '0');
            }

            if (borrow[i] == '/' || borrow[i + 1] == '\0') {
                if (a == 0) {
                    book.borrow.day = componentValue;
                } else if (a == 1) {
                    book.borrow.month = componentValue;
                } else if (a == 2) {
                    book.borrow.year = componentValue;
                }
                componentValue = 0;
                a++;
            }
        }

        // Loop to extract day, month, and year from the 'due' string
        for (int i = 0; due[i] != '\0'; i++) {
            if (due[i] != '/') {
                componentValue = componentValue * 10 + (due[i] - '0');
            }
            if (due[i] == '/' || due[i + 1] == '\0') {
                if (b == 0) {
                    book.due.day = componentValue;
                } else if (b == 1) {
                    book.due.month = componentValue;
                } else if (b == 2) {
                    book.due.year = componentValue;
                }
                componentValue = 0;
                b++;
            }
        }

        int dueDate = calculateJulianDate(book.due.year, book.due.month, book.due.day);
        if ((current - dueDate) * 0.5 > 0) {
            book.fine = ((current - dueDate) * 0.5);
        }

        for (int i = 1; i <= list->count + 1; i++) {
            list->get(i, student);
            if (strcmp(student.id, readID) == 0) {
                //insert book to student
                student.book[student.totalbook] = book;
                student.totalbook++;
                //calculate total fine
                student.calculateTotalFine(); // Call the function to calculate total fine
                list->set(i, student);
            }
        }
    }

    in.close();
    return true;
}

int calculateJulianDate(int year, int month, int day) {
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    int julianDate = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    return julianDate;
}

//************************************************(5)*************************************************************
bool Display(List* list, int source, int detail) {
    Node* cur = list->head;
    int StuNo = 1;

    if (cur == NULL) {
        cout << "\nNo data to display!" << endl;
        return false;
    }

    cout << "Where do you want to display the output (1 - File / 2 - Screen): ";
    cin >> source;

    cout << "Do you want to display booklist for every student (1 - YES / 2 - NO): ";
    cin >> detail;
    cout << endl;

    if (source == 1) {
        ofstream output;
        string outputFile;

        if (detail == 1)
            outputFile = "student_booklist.txt";
        else if (detail == 2)
            outputFile = "student_info.txt";

        output.open(outputFile);

        if (!output.is_open()) {
            cout << "Failed to open " << outputFile << "!" << endl;
            return false;
        }

        while (cur != NULL) {
            output << "STUDENT " << StuNo << endl;
            cur->item.print(output);
            output << endl;
            if (detail == 1) {
                output << "BOOK LIST:" << endl;
                if (cur->item.totalbook == 0) {
                    output << "No borrowed books yet." << endl;
                }
                else {
                    for (int i = 0; i < cur->item.totalbook; i++) {
                        output << endl;
                        output << "Book " << i + 1 << endl;
                        cur->item.book[i].print(output);
                    }
                }
                output << "****************************************************************************" << endl;
            }
            else if (detail == 2) {
                output << "****************************************************************************" << endl;
            }

            cur = cur->next;
            StuNo++;
        }

        cout << "Successfully display output to " << outputFile << endl;
        cout << endl;
        cout << "Successfully display output" << endl;
        output.close();
        return true;
    }
    else if (source == 2) {
        while (cur != NULL) {
            cout << "STUDENT " << StuNo;
            cur->item.print(cout);
            if (detail == 1) {
                cout << endl;
                cout << "BOOK LIST:" << endl;
                if (cur->item.totalbook == 0) {
                    cout << "No borrowed books yet." << endl;
                }
                else {
                    for (int i = 0; i < cur->item.totalbook; i++) {
                        cout << endl;
                        cout << "Book " << i + 1 << endl;
                        cur->item.book[i].print(cout);
                    }
                }
                cout << "****************************************************************************" <<endl<< endl;
            }
            else if (detail == 2) {
                cout << endl;
                cout << "****************************************************************************" << endl << endl;
            }

            cur = cur->next;
            StuNo++;
        }

        cout << "Successfully display output." << endl;
        return true;
    }
    else {
        cout << "Invalid source value. Use 1 for file or 2 for screen." << endl;
        return false;
    }
}

//*************************************************************(6)****************************************************
bool computeAndDisplayStatistics(List* list) {
    if (list->empty()) {
        return false;
    }

    // Initialize variables to hold statistics for each course
    const int CS = 0;
    const int IA = 1;
    const int IB = 2;
    const int CN = 3;
    const int CT = 4;

    int numStudent[5] = { 0,0,0,0,0 };
    int totalBooksBorrowed[5] = { 0,0,0,0,0 };
    int totalOverdueBooks[5] = { 0,0,0,0,0 };
    float totalOverdueFine[5] = { 0.00 ,0.00 ,0.00 ,0.00 ,0.00 };
    
    Node* cur = list->head;
    int current = calculateJulianDate(2020, 3, 29);

    while (cur != nullptr) {
        int overdueBook = 0;

        for (int i = 0; i < cur->item.totalbook; i++)
        {
            
            LibBook book = cur->item.book[i];
            int dueDate = calculateJulianDate(book.due.year, book.due.month, book.due.day);


            if (current > dueDate)
            {
                overdueBook++;
            }
        }

        // Compute statistics for each course based on the data in the current node
        if (strcmp(cur->item.course, "CS") == 0) {
            numStudent[CS]++;
            totalBooksBorrowed[CS] += cur->item.totalbook;
            totalOverdueBooks[CS] += overdueBook; // Accumulate total overdue books for CS
            totalOverdueFine[CS] += cur->item.total_fine; // Accumulate total overdue fine for CS
        }
        else if (strcmp(cur->item.course, "IA") == 0) {
            numStudent[IA]++;
            totalBooksBorrowed[IA] += cur->item.totalbook;
            totalOverdueBooks[IA] += overdueBook; // Accumulate total overdue books for IA
            totalOverdueFine[IA] += cur->item.total_fine; // Accumulate total overdue fine for IA
        }
        else if (strcmp(cur->item.course, "IB") == 0) {
            numStudent[IB]++;
            totalBooksBorrowed[IB] += cur->item.totalbook;
            totalOverdueBooks[IB] += overdueBook; // Accumulate total overdue books for IB
            totalOverdueFine[IB] += cur->item.total_fine; // Accumulate total overdue fine for IB
        }
        else if (strcmp(cur->item.course, "CT") == 0) {
            numStudent[CT]++;
            totalBooksBorrowed[CT] += cur->item.totalbook;
            totalOverdueBooks[CT] += overdueBook; // Accumulate total overdue books for CT
            totalOverdueFine[CT] += cur->item.total_fine; // Accumulate total overdue fine for CT
        }
        else if (strcmp(cur->item.course, "CN") == 0) {
            numStudent[CN]++;
            totalBooksBorrowed[CN] += cur->item.totalbook;
            totalOverdueBooks[CN] += overdueBook; // Accumulate total overdue books for CN
            totalOverdueFine[CN] += cur->item.total_fine; // Accumulate total overdue fine for CN
        }

        // Move to the next node in the list
        cur = cur->next;
    }

    // Display computed statistics for each course in the specified table format
    cout << "Course\tNumber of Students\tTotal Books Borrowed\tTotal Overdue Books\tTotal Overdue Fine (RM)" << endl;
    cout << "CS\t" << numStudent[CS] << "\t\t\t" << totalBooksBorrowed[CS] << "\t\t\t" << totalOverdueBooks[CS] << "\t\t\t" << fixed << setprecision(2) << totalOverdueFine[CS] << endl;
    cout << "IA\t" << numStudent[IA] << "\t\t\t" << totalBooksBorrowed[IA] << "\t\t\t" << totalOverdueBooks[IA] << "\t\t\t" << fixed << setprecision(2) << totalOverdueFine[IA] << endl;
    cout << "IB\t" << numStudent[IB] << "\t\t\t" << totalBooksBorrowed[IB] << "\t\t\t" << totalOverdueBooks[IB] << "\t\t\t" << fixed << setprecision(2) << totalOverdueFine[IB] << endl;
    cout << "CN\t" << numStudent[CN] << "\t\t\t" << totalBooksBorrowed[CN] << "\t\t\t" << totalOverdueBooks[CN] << "\t\t\t" << fixed << setprecision(2) << totalOverdueFine[CN] << endl;
    cout << "CT\t" << numStudent[CT] << "\t\t\t" << totalBooksBorrowed[CT] << "\t\t\t" << totalOverdueBooks[CT] << "\t\t\t" << fixed << setprecision(2) << totalOverdueFine[CT] << endl;
    
    return true;
}

//**************************************************(7)*******************************************************
bool printStuWithSameBook(List* list, char* callNum) {
    Node* cur;
    int count = 0;

    if (list->empty()) {
        cout << "Student list is empty." << endl;
        return false;
    }
        

    cur = list->head;

    while (cur != NULL) {
        for (int i = 0; i < cur->item.totalbook; i++) {
            if (strcmp(cur->item.book[i].callNum, callNum) == 0) {
                count++;
                cout << endl;
                cout << "Student Id = " << cur->item.id << endl;
                cout << "Name = " << cur->item.name << endl;
                cout << "Course = " << cur->item.course << endl;
                cout << "Phone Number = " << cur->item.phone_no << endl;
                cout << "Borrow Date: " << cur->item.book[i].borrow.day << "/" << cur->item.book[i].borrow.month << "/" << cur->item.book[i].borrow.year << endl;
                cout << "Due Date: " << cur->item.book[i].due.day << "/" << cur->item.book[i].due.month << "/" << cur->item.book[i].due.year << endl;
                break;
            }
        }

        cur = cur->next;
    }

    if (count == 0) {
        cout << "No students found who borrowed the book with call number " << callNum << "." << endl;
        return false;
    }
    else {
        cout << "\nThere are "<< count << " students that borrow the book with call number " << callNum << "." << endl;
    }

    return true;

}

//*********************************************(8)**************************************************
bool displayWarnedStudent(List* list, List* type1, List* type2)
{
    Node* cur;
    int current = calculateJulianDate(2020, 3, 29);
    
    if (list->empty())
        return false;

    cur = list->head;

    //tranversing the node
    while (cur != NULL)
    {
        int overdueBook1 = 0;
        int overdueBook2 = 0;

        // Check for type 1 warning condition (more than 2 books overdue for >= 10 days)
        for (int i = 0; i < cur->item.totalbook; i++)
        {
            LibBook book = cur->item.book[i];
            int dueDate = calculateJulianDate(book.due.year, book.due.month, book.due.day);

            if (current - dueDate >= 10)
            {
                overdueBook1++;
            }

            if (current > dueDate)
            {
                overdueBook2++;
            }
        }

        // insert student to the type 1 list if more than 2 books that are overdue for >= 10 days 
        if (overdueBook1 >= 2)
        {
            type1->insert(cur->item);
        }
        
        // insert student to the type 2 list if the total fine is more than RM50.00 and every book are overdue. 
        if (cur->item.total_fine > 50.00 && overdueBook2 == cur->item.totalbook)
        {
            type2->insert(cur->item);
        }

        cur = cur->next;
    }

    return true;
}

bool printList(List list)
{
    Node* cur;

    if (list.empty())
    {
        cout << "No records in the list.\n";
        return false;
    }

    cur = list.head; //start traversing from the first node

    while (cur != NULL) {
        cur->item.print(cout);
        cur = cur->next;
    }

    return true;
}

//*********************************************(9)**************************************************
int menu() {
    int operation;
    system("cls");
    center("UTAR Library System?");
    center("Faculty of Information and Communication Technology");
    center("Menu");
    center("Please select an option:          ");
    center("1. Read File                      ");
    center("2. Delete Record                  ");
    center("3. Search Student                 ");
    center("4. Insert Book                    ");
    center("5. Display Output                 ");
    center("6. Compute and Display Statistics ");
    center("7. Student with Same Book         ");
    center("8. Display Warned Student         ");
    center("9. Exit                           ");
    cout << "Enter your choice: ";
    cin >> operation;

    return operation;
}