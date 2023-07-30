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
    char id[10];
    LibStudent stu;
	int detail, source;
    int choice;
    bool stop = false;
        ReadFile(STUDENT_INFO_FILE, &studentList);
        do {
            choice = menu();
            switch (choice) {
            case 1:
                if (ReadFile(STUDENT_INFO_FILE, &studentList)) {
                    cout << "Data successfully read and stored in the list." << endl;
                    cout << studentList.count << " records have been successfully read." << endl;
                }
                else {
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
                    cout <<"Total Books: "<< stu.totalbook;
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
    bool isDuplicate(List * list, LibStudent & student) {

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
    LibStudent stu;

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
	Node* cur = list->head;
	LibBook book;
	LibStudent student;
	char author[256], temp[256];
	char name[256];
	char borrow[256], due[256];
	char line[50];
	char day[20], month[20], year[20];
	int x = 0, y = 0, i = 0;
	int a = 0, b = 0;
	char readID[10];
	int current = 0;
	int dueDate;
	Date date;
	
	if (!in)
	{
		cout << "Cannot open the " << filename << endl;
		return false;
	}
	else
	{
		while (!in.eof())
		{
			in >> readID;
			in >> author;
			in >> book.title;
			in >> book.publisher;
            in >> book.ISBN;
            in >> book.yearPublished;   
			in >> book.callNum;
			in >> borrow;
			in >> due;
			book.fine = 0;
			x = 0; y = 0;
			char* ptr = author;
			while (*ptr != '\0') {
				if (*ptr == '_') {
					*ptr = ' ';
				}
				ptr++;
			}
			char* ptr1 = book.title;
			while (*ptr1 != '\0') {
				if (*ptr1 == '_') {
					*ptr1 = ' ';
				}
				ptr1++;
			}
			char* ptr3 = book.publisher;
			while (*ptr3 != '\0') {
				if (*ptr3 == '_') {
					*ptr3 = ' ';
				}
				ptr3++;
			}
			while (author[i] != '\0') {
				book.author[y] = new char[256];
				strcpy(book.author[y], " ");

				if (author[i] != '/') {
					temp[x] = author[i];
					x++;
				}

				if (author[i] == '/' || author[i + 1] == '\0') {
					temp[x] = '\0';
					x = 0;
					book.author[y] = temp;
					y++;
					strcpy(temp, "");
				}

				i++;
			}

			i = 0;
			a = 0;
			b = 0;

			// Loop to extract day, month, and year from the 'borrow' string
			while (borrow[i] != '\0') {
				if (borrow[i] != '/') {
					if (a == 0) {
						day[b] = borrow[i];
						b++;
					}
					if (a == 1) {
						month[b] = borrow[i];
						b++;
					}
					if (a == 2) {
						year[b] = borrow[i];
						b++;
					}
				}

				if (borrow[i] == '/' || borrow[i + 1] == '\0') {
					if (a == 0) {
						day[b] = '\0';
						book.borrow.day = atoi(day);
						strcpy(day, "");
					}
					if (a == 1) {
						month[b] = '\0';
						book.borrow.month = atoi(month);
						strcpy(month, "");
					}
					if (a == 2) {
						year[b] = '\0';
						book.borrow.year = atoi(year);
						strcpy(year, "");
					}
					b = 0;
					a++;
				}

				i++;
			}

			i = 0;
			a = 0;
			b = 0;

			// Loop to extract day, month, and year from the 'due' string
			while (due[i] != '\0') {
				if (due[i] != '/') {
					if (a == 0) {
						day[b] = due[i];
						b++;
					}
					if (a == 1) {
						month[b] = due[i];
						b++;
					}
					if (a == 2) {
						year[b] = due[i];
						b++;
					}
				}

				if (due[i] == '/' || due[i + 1] == '\0') {
					if (a == 0) {
						day[b] = '\0';
						book.due.day = atoi(day);
						strcpy(day, "");
					}
					if (a == 1) {
						month[b] = '\0';
						book.due.month = atoi(month);
						strcpy(month, "");
					}
					if (a == 2) {
						year[b] = '\0';
						book.due.year = atoi(year);
						strcpy(year, "");
					}
					b = 0;
					a++;
				}

				i++;
			}

			dueDate = book.due.year, book.due.month,book.due.day;
			if ((current - dueDate) * 0.5 > 0)
			{
				book.fine = ((current - dueDate) * 0.5);
			}
			for (int i = 1; i <= list->count + 1; i++)
			{
				list->get(i, student);
				if (strcmp(student.id, readID) == 0)
				{
					//insert book to student
					student.book[student.totalbook] = book;
					student.totalbook++;
					student.calculateTotalFine(); //calcute total fine
					list->set(i, student);
				}
				else
					continue;
			}
		}
		in.close();
		return true;
	}
}


//*************************************************************(6)****************************************************
bool computeAndDisplayStatistics(List* list) {
    const string STUDENT_INFO_FILE = "student.txt";
    const string STUDENT_BOOK_LIST_FILE = "student_booklist.txt";

    ifstream inStudent(STUDENT_INFO_FILE);
    ifstream inBook(STUDENT_BOOK_LIST_FILE);
    char text[256];
    LibStudent newStudent;
    LibBook book;
    int bookCount = 0;

    if (!inStudent || !inBook) {
        cout << "Failed to open one or both of the files." << endl;
        return false;
    }

    if (list == NULL || list->empty()) {
        cout << "Empty list. Unable to compute statistics." << endl;
        return false;
    }

    // Initialize variables to hold statistics for each course
    int numStudentsCS = 0, numStudentsIA = 0, numStudentsIB = 0, numStudentsCN = 0, numStudentsCT = 0;
    int totalBooksBorrowedCS = 0, totalBooksBorrowedIA = 0, totalBooksBorrowedIB = 0, totalBooksBorrowedCN = 0, totalBooksBorrowedCT = 0;
    int totalOverdueBooksCS = 0, totalOverdueBooksIA = 0, totalOverdueBooksIB = 0, totalOverdueBooksCN = 0, totalOverdueBooksCT = 0;
    float totalOverdueFineCS = 0.00, totalOverdueFineIA = 0.00, totalOverdueFineIB = 0.00, totalOverdueFineCN = 0.00, totalOverdueFineCT = 0.00;


    Node* cur = list->head;
    while (cur != NULL) {

        // Compute statistics for each course based on the data in the current node
        if (strcmp(cur->item.course, "CS") == 0) {
            numStudentsCS++;
            totalBooksBorrowedCS += cur->item.totalbook;
            totalOverdueBooksCS += cur->item.totalbook; // Accumulate total overdue books for CS
            totalOverdueFineCS += cur->item.total_fine; // Accumulate total overdue fine for CS
        }
        else if (strcmp(cur->item.course, "IA") == 0) {
            numStudentsIA++;
            totalBooksBorrowedIA += cur->item.totalbook;
            totalOverdueBooksIA += cur->item.totalbook; // Accumulate total overdue books for IA
            totalOverdueFineIA += cur->item.total_fine; // Accumulate total overdue fine for IA
        }
        else if (strcmp(cur->item.course, "IB") == 0) {
            // Similar calculations for other courses (IB, CN, CT) can be added here
        }
        // Move to the next node in the list
        cur = cur->next;
    }

    // Display computed statistics for each course in the specified table format
    cout << "Course\tNumber of Students\tTotal Books Borrowed\tTotal Overdue Books\tTotal Overdue Fine (RM)" << endl;
    cout << "CS\t" << numStudentsCS << "\t\t\t" << totalBooksBorrowedCS << "\t\t\t" << totalOverdueBooksCS << "\t\t\t" << fixed << setprecision(2) << totalOverdueFineCS << endl;
    cout << "IA\t" << numStudentsIA << "\t\t\t" << totalBooksBorrowedIA << "\t\t\t" << totalOverdueBooksIA << "\t\t\t" << fixed << setprecision(2) << totalOverdueFineIA << endl;
    // Similar lines for other courses (IB, CN, CT) can be added here


    return true;
}

//**************************************************(7)*******************************************************
bool printStuWithSameBook(List* list, char* callNum) {
    const string STUDENT_INFO_FILE = "student.txt";
    const string STUDENT_BOOK_LIST_FILE = "student_booklist.txt";

    //The struct to defined for LibStudent and LibBook
    struct Date {
        int day;
        int month;
        int year;
    };

    ifstream in(STUDENT_BOOK_LIST_FILE);
    Node* cur = list->head;
    bool found = false;

    if (!in) {
        cout << "Cannot open the " << STUDENT_BOOK_LIST_FILE << endl;
        return false;
    }


    int count = 0;

    while (cur != NULL) {
        for (int i = 0; i < cur->item.totalbook; i++) {
            if (strcmp(cur->item.book[i].callNum, callNum) == 0) {
                count++;
                if (count == 1) {
                    cout << "There are " << count << " student(s) that borrow the book with call number " << callNum << " as shown below:" << endl;
                }
                cout << endl;
                cout << "Student Id = " << cur->item.id << endl;
                cout << "Name = " << cur->item.name << endl;
                cout << "Course = " << cur->item.course << endl;
                cout << "Phone Number = " << cur->item.phone_no << endl;
                cout << "Borrow Date: " << cur->item.book[i].borrow.day << "/" << cur->item.book[i].borrow.month << "/" << cur->item.book[i].borrow.year << endl;
                cout << "Due Date: " << cur->item.book[i].due.day << "/" << cur->item.book[i].due.month << "/" << cur->item.book[i].due.year << endl;
            }
        }
        cur = cur->next;
    }

    if (count == 0) {
        cout << "No students found who borrowed the book with call number " << callNum << "." << endl;
        return false;
    }

    return true;

}




<<<<<<< HEAD
//*********************************************(9)**************************************************//
=======
//*********************************************(9)**************************************************
>>>>>>> 485904772b31a9fc50f9f4d7e77b55aed5ee5314
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