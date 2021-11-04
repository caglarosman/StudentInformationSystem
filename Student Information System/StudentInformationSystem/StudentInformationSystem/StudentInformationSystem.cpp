#include<iostream>
#include<stdlib.h>
#include<string>
#include<conio.h>
#include<iomanip>

#define SIZE 100

int totalStudent = 0;

using namespace std;

void mainMenu();
void printStudent(int);
void printSettings();
void addStudent();
void deleteStudent();
void updateStudent();
void listStudents();
string letterGrade(float);

struct studentInfo {
	unsigned long long int studentID;
	string nameSurname;
	string takenCourses;
	unsigned int midtermGrade;
	unsigned int finalGrade;
	float averageGrade;
	string letterGrade;
	string address;
	string mobilePhone;
	string eMail;
};

studentInfo student[SIZE];

float calculateAverage(unsigned int, unsigned int, int);

void main() {
	
	mainMenu();

	system("pause");
}

void mainMenu() {

	char choice;

	while (true) {

		cout << endl << "\t\t\t--- Warning: Put the program in full screen mode for the program view to work properly! ---" << endl;
		cout << endl << "\t\t\t\t--- Student Information System ---" << endl;
		cout << "\t\t\t\t- ADD NEW STUDENT [A]" << endl;
		cout << "\t\t\t\t- DELETE STUDENT [D]" << endl;
		cout << "\t\t\t\t- UPDATE STUDENT INFORMATION [U]" << endl;
		cout << "\t\t\t\t- LIST STUDENTS [L]" << endl;
		cout << "\t\t\t\t- EXIT [Q]" << endl;

		cout << endl << "\t\t\t\t- Please type a character for the action you want to do: ";
		cin >> choice;
		cin.ignore();

		if (choice == 'A' || choice == 'a')
			addStudent();
		else if (choice == 'D' || choice == 'd')
			deleteStudent();
		else if (choice == 'U' || choice == 'u')
			updateStudent();
		else if (choice == 'L' || choice == 'l')
			listStudents();
		else if (choice == 'Q' || choice == 'q')
			exit(0);

		if (choice == 'Q' || choice == 'q')
			break;
	}

}

void printStudent(int i) {
	cout << "- " << left << setw(18) << student[i].studentID;
	cout << left << setw(30) << student[i].nameSurname;
	cout << left << setw(20) << student[i].takenCourses;
	cout << left << setw(4) << student[i].midtermGrade << "/ ";
	cout << left << setw(4) << student[i].finalGrade << "/ ";
	cout << left << setw(4) << student[i].averageGrade << " / ";
	cout << student[i].letterGrade << left << setw(6) << "";
	cout << left << setw(30) << student[i].address;
	cout << left << setw(15) << student[i].mobilePhone;
	cout << left << setw(25) << student[i].eMail;
}

void printSettings() {
	cout << left << setw(20) << "  Student ID";
	cout << left << setw(30) << "Name Surname";//NameSurname=max(25) char should be.
	cout << left << setw(20) << "Taken Courses";
	cout << left << setw(27) << "M - F - A - L Grades";
	cout << left << setw(30) << "Address";//Address=max(25) char should be.
	cout << left << setw(15) << "Mobile Phone";
	cout << left << setw(25) << "e-Mail Address" << endl;//e-Mail Address=max(15) char should be.
	cout << left << setw(20) << "  ------------";
	cout << left << setw(30) << "-------------------------";
	cout << left << setw(20) << "-------------";
	cout << left << setw(27) << "----------------------";
	cout << left << setw(30) << "-------------------------";//Address=max(25) char should be.
	cout << left << setw(15) << "------------";
	cout << left << setw(25) << "----------------------" << endl;//e-Mail Address=max(15) char should be.

}

void addStudent() {
	cout << endl << "- ADD NEW STUDENT" << endl;

	if (totalStudent > SIZE)
		cout << "The maximum number of students has been reached!";
	else {
		while (true) {
			cout << "Student Name and Surname (Max: 30 Characters): ";
			getline(cin, student[totalStudent].nameSurname);
			if (student[totalStudent].nameSurname.length() > 30)
				cout << "Please enter a name with a maximum of 30 characters!" << endl;
			else
				break;
		}
		cout << "Student ID: ";
		cin >> student[totalStudent].studentID;
		cin.ignore();
		cout << "Taken Course: ";
		getline(cin, student[totalStudent].takenCourses);
		cout << "Midterm Grade: ";
		cin >> student[totalStudent].midtermGrade;
		cout << "Final Grade: ";
		cin >> student[totalStudent].finalGrade;
		cin.ignore();
		while (true) {
			cout << "Address (Max: 25 Characters): ";
			getline(cin, student[totalStudent].address);
			if (student[totalStudent].address.length() > 25)
				cout << "Please enter a address with a maximum of 25 characters!" << endl;
			else
				break;
		}
		cout << "Mobile Phone: ";
		getline(cin, student[totalStudent].mobilePhone);
		cout << "e-Mail Adress: ";
		getline(cin, student[totalStudent].eMail);

		student[totalStudent].averageGrade = calculateAverage(student[totalStudent].midtermGrade, student[totalStudent].finalGrade, totalStudent);
		student[totalStudent].letterGrade = letterGrade(student[totalStudent].averageGrade);

		totalStudent++;
	}

	cout << endl << "Press a button to return to the main menu." << endl;
	_getch();
	system("cls");

}

void deleteStudent() {
	int choice, i, newFlag[SIZE], deletedStudentCounter = 0;
	unsigned long long int deleteID;
	string deleteName;

	for (i = 0; i < totalStudent; i++)
		newFlag[i] = -1;

	cout << endl << "- DELETE STUDENT" << endl;
	cout << "Please type -[1] by using 'Student ID' or type -[2] by using 'Student Name and Surname' to delete student: ";
	cin >> choice;
	cin.ignore();

	if (choice == 1) {
		cout << "Student ID: ";
		cin >> deleteID;
		for (i = 0; i < totalStudent; i++) {
			if (deleteID == student[i].studentID) {
				newFlag[i] = i;
				break;
			}
		}
	}
	else if (choice == 2) {
		cout << "Student Name and Surname: ";
		getline(cin, deleteName);
		for (i = 0; i < totalStudent; i++) {
			if (deleteName.compare(student[i].nameSurname) == 0) {
				newFlag[i] = i;
			}

		}
	}

	for (i = 0; i < totalStudent; i++) {
		if (newFlag[i] != -1) {
			student[i].nameSurname = "xxxxxx xxxxxx";
			student[i].studentID = 111111111111;
			student[i].takenCourses = "CENGxxx";
			student[i].midtermGrade = 0;
			student[i].finalGrade = 0;
			student[i].averageGrade = 0;
			student[i].letterGrade = "xx";
			student[i].address = "xxxxxxxxxxxxxxxxxxxxxxxxx";
			student[i].mobilePhone = "0(...).....";
			student[i].eMail = "xxxxxxxxxxxx@xxxxx.xxx";

			deletedStudentCounter++;
		}
	}
	if (deletedStudentCounter == 1)
		cout << "Student has been successfully deleted!" << endl;
	else if (deletedStudentCounter > 1)
		cout << "Students has been successfully deleted!" << endl;
	else
		cout << "The student could not be found!";

	cout << endl << "Press a button to return to the main menu." << endl;
	_getch();
	system("cls");
}

void updateStudent() {
	int i, flag = -1;
	unsigned long long int updateID;

	cout << endl << "- UPDATE STUDENT" << endl;
	cout << "Student ID: ";
	cin >> updateID;
	cin.ignore();
	for (i = 0; i < totalStudent; i++) {
		if (updateID == student[i].studentID) {
			flag = i;
			break;
		}
	}
	if (flag == -1)
		cout << "The student could not be found!" << endl;
	else {
		while (true) {
			cout << "Student Name and Surname (Max: 30 Characters): ";
			getline(cin, student[flag].nameSurname);
			if (student[flag].nameSurname.length() > 30)
				cout << "Please enter a name with a maximum of 30 characters!" << endl;
			else
				break;
		}
		cout << "Student ID: ";
		cin >> student[flag].studentID;
		cin.ignore();
		cout << "Taken Course: ";
		getline(cin, student[flag].takenCourses);
		cout << "Midterm Grade: ";
		cin >> student[flag].midtermGrade;
		cout << "Final Grade: ";
		cin >> student[flag].finalGrade;
		cin.ignore();
		while (true) {
			cout << "Address (Max: 25 Characters): ";
			getline(cin, student[flag].address);
			if (student[flag].address.length() > 25)
				cout << "Please enter a address with a maximum of 25 characters!" << endl;
			else
				break;
		}
		cout << "Mobile Phone: ";
		getline(cin, student[flag].mobilePhone);
		cout << "e-Mail Adress: ";
		getline(cin, student[flag].eMail);

		student[flag].averageGrade = calculateAverage(student[flag].midtermGrade, student[flag].finalGrade, flag);
		student[flag].letterGrade = letterGrade(student[flag].averageGrade);
	}



	cout << endl << "Press a button to return to the main menu." << endl;
	_getch();
	system("cls");
}

void listStudents() {
	int i, j, choice, flag, newFlag[SIZE], counterNameSurname, counterCourse, newCounter;
	unsigned long long int listID;
	studentInfo tempStudent;
	string listNameSurname, listCourse, listGrade;

	cout << endl << "- LIST STUDENTS" << endl;
	cout << "Please type -[1] to list 'All Student Informations', -[2] to list a specific student by 'Student ID', -[3] to list one or more specific students by 'Name and Surname', -[4] to list all student by 'Taken a Specific Course', -[5] to list one or more students by 'Letter Grade for a Course': ";
	cin >> choice;
	cout << endl;
	cin.ignore();
	if (choice == 1) {
		for (i = 0; i < totalStudent; i++) {
			for (j = i; j < totalStudent; j++) {
				if (student[i].nameSurname.compare(student[j].nameSurname) > 0) {
					tempStudent = student[i];
					student[i] = student[j];
					student[j] = tempStudent;
				}
			}
		}
		printSettings();
		for (i = 0; i < totalStudent; i++) {
			printStudent(i);
			cout << endl;
		}
	}
	else if (choice == 2) {
		flag = -1;
		cout << "Student ID: ";
		cin >> listID;
		for (i = 0; i < totalStudent; i++) {
			if (listID == student[i].studentID)
				flag = i;
		}
		if (flag == -1)
			cout << "The student could not be found!" << endl;
		else {
			printSettings();
			printStudent(flag);
			cout << endl;
		}
	}
	else if (choice == 3) {
		newCounter = 0;
		counterNameSurname = 0;
		for (i = 0; i < totalStudent; i++) {
			newFlag[i] = -1;
		}
		cout << "Name and Surname: ";
		getline(cin, listNameSurname);
		for (i = 0; i < totalStudent; i++) {
			if (listNameSurname == student[i].nameSurname) {
				newFlag[i] = i;
				counterNameSurname++;
			}
		}
		if (counterNameSurname == 0)
			cout << "The student could not be found!";
		else {
			for (i = 0; i < totalStudent; i++) {
				if (newFlag[i] != -1) {
					if (newCounter == 0) {
						printSettings();
					}
					printStudent(i);
					cout << endl;
					newCounter++;
				}
			}
		}

	}
	else if (choice == 4) {
		counterCourse = 0;
		for (i = 0; i < totalStudent; i++)
			newFlag[i] = -1;

		cout << "Course Name: ";
		getline(cin, listCourse);

		for (i = 0; i < totalStudent; i++) {
			if (listCourse == student[i].takenCourses) {
				newFlag[i] = i;
			}
		}
		for (i = 0; i < totalStudent; i++) {
			if (newFlag[i] != -1) {
				if (counterCourse == 0) {
					printSettings();
				}
				printStudent(i);
				cout << endl;
				counterCourse++;
			}
		}
		if (counterCourse == 0)
			cout << "No students registered for this course!" << endl;

	}
	else if (choice == 5) {
		counterCourse = 0;
		for (i = 0; i < totalStudent; i++)
			newFlag[i] = -1;

		cout << "Course Name: ";
		getline(cin, listCourse);
		cout << "Letter Grade: ";
		getline(cin, listGrade);

		for (i = 0; i < totalStudent; i++) {
			if (listCourse == student[i].takenCourses&&listGrade == student[i].letterGrade) {
				newFlag[i] = i;
			}
		}
		for (i = 0; i < totalStudent; i++) {
			if (newFlag[i] != -1) {
				if (counterCourse == 0) {
					printSettings();
				}

				printStudent(i);
				counterCourse++;
			}
		}
		if (counterCourse == 0)
			cout << "No student belonging to this letter grade was found!" << endl;
	}

	cout << endl;
	cout << endl << "Press a button to return to the main menu." << endl;
	_getch();
	system("cls");
}

float calculateAverage(unsigned int midtermGrade, unsigned int finalGrade, int studentList) {
	float average;
	average = (float)student[studentList].midtermGrade*0.4 + student[studentList].finalGrade*0.6;
	return average;
}

string letterGrade(float average) {
	if (average >= 90)
		return "AA";
	else if (average >= 85)
		return "BB";
	else if (average >= 75)
		return "CC";
	else if (average >= 50)
		return "DD";
	else
		return "FF";
}