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
                    cout << studentList.count <<" records have been successfully read."<< endl;
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

                break;
            case 7:

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
	ifstream file(filename);
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
	char id[20];
	int current = 0;
	int dueDate;
	Date date;
	
	if (!file)
	{
		cout << "Cannot open the " << filename << endl;
		return false;
	}
	else
	{
		while (!file.eof())
		{
			file >> id;
			file >> author;
			file >> book.title;
			file >> book.publisher;
			file >> book.ISBN;
			file >> book.yearPublished;
			file >> book.callNum;
			file >> borrow;
			file >> due;
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
				if (strcmp(student.id, id) == 0)
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
		file.close();
		return true;
	}
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