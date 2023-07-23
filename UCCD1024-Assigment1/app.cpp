#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

using namespace std;

//constant
const string STUDENT_INFO_FILE = "student.txt";

//function prototype
bool ReadFile(string, List*);
bool isDuplicate(List* list, LibStudent& student);
bool DeleteRecord(List*, char*);
bool Display(List, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu();


int main() {
    List studentList; // Create an instance of the List class

    if (ReadFile(STUDENT_INFO_FILE, &studentList)) {
        cout << "Data successfully read and stored in the list." << endl;
        cout << studentList.count;
    }
    else {
        cout << "Failed to read data or encountered an error." << endl;
    }

	cout << "\n\n";
    cout << "Hello World"<<endl;
	system("pause");
	return 0;
}

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

