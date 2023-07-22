#include<iostream>
#include<iomanip>

using namespace std;

void MainMenu();
void center(string);

int main() {
	MainMenu();



	return 0;
}
void center(string string) {
	const int WIDTH = 115;
	int space = (WIDTH - string.length()) / 2;
	cout << setw(space + string.length()) << string << endl;
}

void MainMenu() {

	bool stop = false;
	do {
		system("cls");
		int operation;
		center("Faculty of Information and Communication Technology");

		center("UTAR Library System");
		center("Main Menu");
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
		cout << "Enter an operation: ";
		cin >> operation;

		switch (operation) {
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

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
	} while (!stop);

	return;
}
