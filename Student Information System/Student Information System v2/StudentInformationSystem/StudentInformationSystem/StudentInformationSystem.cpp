#include<iostream>/////////////EDÝTLEME BASLÝYOR
#include<stdlib.h>
#include<string>
#include<conio.h>
#include<iomanip>
#include<fstream>

#define SIZE 100

int totalStudent = 0;
bool statusPrintSettingsToTxt = false;

using namespace std;

void mainMenu(fstream &, fstream &, fstream &);
void printStudent(int);
void printStudentToTxt(int, fstream &);
void printSettings();
void printSettingsToTxt(fstream &);
int registeredStudents(fstream &);
void loadStudents(fstream &);
void addStudent(fstream &, fstream &, fstream &);
void deleteStudent(fstream &, fstream &);
void updateStudent(fstream &, fstream &);
void listStudents();
string letterGrade(float);

struct studentInfo {
	unsigned long long int studentID;
	char nameSurname[26];
	string takenCourses;
	unsigned int midtermGrade;
	unsigned int finalGrade;
	float averageGrade;
	string letterGrade;
	char address[26];
	string mobilePhone;
	char eMail[51];
};
//yapýlacaklar; eðer dataFile yoksa kayýt alýnamýyor gibi bir uyarý iþlemi gönder!
studentInfo student[SIZE];

float calculateAverage(unsigned int, unsigned int, int);

void main() {

	fstream dataFile, statusDataFile, statusNumberOfRegisteredStudents, newDataFile;
	string status_1="Status 1: No record has been made before. It is the first time that the registration is made.";
	int registeredStudentsNum;

	registeredStudentsNum = registeredStudents(statusNumberOfRegisteredStudents);
	totalStudent = registeredStudentsNum;

	if(registeredStudentsNum==0)
		printSettingsToTxt(dataFile);

	//statusNumberOfRegisteredStudents.open("C:\\Users\\Casper\\Desktop\\StudentInputOutput\\NumberOfRegisteredStudents.txt", ios::in | ios::binary);
	//statusNumberOfRegisteredStudents.write
	//statusNumberOfRegisteredStudents.write((char *)&totalStudent, sizeof(totalStudent));
	
	
			

	mainMenu(dataFile, statusNumberOfRegisteredStudents, newDataFile);

	system("pause");
}

void mainMenu(fstream &dataFile, fstream &statusNumberOfRegisteredStudents, fstream &newDataFile) {

	char choice;
	int registeredStudentsNum;

	loadStudents(dataFile);

	while (true) {

		cout << endl << "\t\t\t--- Warning: Put the program in full screen mode for the program view to work properly! ---" << endl;
		cout << endl << "\t\t\t\t--- Student Information System ---" << endl;
		cout << "\t\t\t\t- ADD NEW STUDENT [A]" << endl;
		cout << "\t\t\t\t- DELETE STUDENT [D]" << endl;
		cout << "\t\t\t\t- UPDATE STUDENT INFORMATION [U]" << endl;
		cout << "\t\t\t\t- LIST STUDENTS [L]" << endl;
		cout << "\t\t\t\t- NUMBER OF STUDENTS [H]" << endl;
		cout << "\t\t\t\t- EXIT [Q]" << endl;

		cout << endl << "\t\t\t\t- Please type a character for the action you want to do: ";
		cin >> choice;
		cin.ignore();

		if (choice == 'A' || choice == 'a')
			addStudent(dataFile, statusNumberOfRegisteredStudents, newDataFile);
		else if (choice == 'D' || choice == 'd')
			deleteStudent(newDataFile, dataFile);
		else if (choice == 'U' || choice == 'u')
			updateStudent(newDataFile, dataFile);
		else if (choice == 'L' || choice == 'l')
			listStudents();
		else if (choice == 'H' || choice == 'h') {
			registeredStudentsNum = registeredStudents(statusNumberOfRegisteredStudents);
			cout << endl << "- THE NUMBER OF REGISTERED STUDENTS" << endl;
			cout << "The number of users registered in the system right now: " << registeredStudentsNum << endl;

			cout << endl << "Press a button to return to the main menu." << endl;
			_getch();
			system("cls");
		}
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

void printStudentToTxt(int i, fstream &dataFile) {
	dataFile << "- " << left << setw(18) << student[i].studentID;
	dataFile << left << setw(30) << student[i].nameSurname;
	dataFile << left << setw(20) << student[i].takenCourses;
	dataFile << left << setw(4) << student[i].midtermGrade << "/ ";
	dataFile << left << setw(4) << student[i].finalGrade << "/ ";
	dataFile << left << setw(4) << student[i].averageGrade << " / ";
	dataFile << student[i].letterGrade << left << setw(6) << "";
	dataFile << left << setw(30) << student[i].address;
	dataFile << left << setw(15) << student[i].mobilePhone;
	dataFile << left << setw(25) << student[i].eMail;
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

void printSettingsToTxt(fstream &dataFile) {

	dataFile.open("C:\\Users\\Casper\\Desktop\\StudentInputOutput\\StudentInfos.txt", ios::out | ios::app);
	dataFile << left << setw(20) << "  Student ID";
	dataFile << left << setw(30) << "Name Surname";//NameSurname=max(25) char should be.
	dataFile << left << setw(20) << "Taken Courses";
	dataFile << left << setw(27) << "M - F - A - L Grades";
	dataFile << left << setw(30) << "Address";//Address=max(25) char should be.
	dataFile << left << setw(15) << "Mobile Phone";
	dataFile << left << setw(25) << "e-Mail Address" << endl;//e-Mail Address=max(15) char should be.
	dataFile << left << setw(20) << "  ------------";
	dataFile << left << setw(30) << "-------------------------";
	dataFile << left << setw(20) << "-------------";
	dataFile << left << setw(27) << "----------------------";
	dataFile << left << setw(30) << "-------------------------";//Address=max(25) char should be.
	dataFile << left << setw(15) << "------------";
	dataFile << left << setw(25) << "----------------------" << endl;//e-Mail Address=max(15) char should be.

	dataFile.close();

}

int registeredStudents(fstream &statusNumberOfRegisteredStudents) {
	int registeredStudents = 0;

	statusNumberOfRegisteredStudents.open("C:\\Users\\Casper\\Desktop\\StudentInputOutput\\NumberOfRegisteredStudents.dat", ios::in | ios::binary);
	statusNumberOfRegisteredStudents.read((char *)&registeredStudents, sizeof(registeredStudents));
	statusNumberOfRegisteredStudents.close();

	totalStudent = registeredStudents;//yeni eklendi

	/*cout << endl << "- THE NUMBER OF REGISTERED STUDENTS" << endl;
	cout << "The number of users registered in the system right now: " << registeredStudents << endl;

	cout << endl << "Press a button to return to the main menu." << endl;
	_getch();
	system("cls");*/

	return registeredStudents;
}

void loadStudents(fstream &newDataFile) {
	int i;
	newDataFile.open("C:\\Users\\Casper\\Desktop\\StudentInputOutput\\StudentInfos.dat", ios::in | ios::binary);

	
	for (i = 0; i < totalStudent; i++) {
		newDataFile.read((char *)&student[i], sizeof(student[i]));	
	}

	newDataFile.close();
}

void addStudent(fstream &dataFile, fstream &statusNumberOfRegisteredStudents, fstream &newDataFile) {

	int studentFileOrder, registeredStudentsNum;

	registeredStudentsNum = registeredStudents(statusNumberOfRegisteredStudents);

	dataFile.open("C:\\Users\\Casper\\Desktop\\StudentInputOutput\\StudentInfos.txt", ios::out | ios::app);
	statusNumberOfRegisteredStudents.open("C:\\Users\\Casper\\Desktop\\StudentInputOutput\\NumberOfRegisteredStudents.dat", ios::out | ios::binary);
	newDataFile.open("C:\\Users\\Casper\\Desktop\\StudentInputOutput\\StudentInfos.dat", ios::out | ios::binary | ios::app);

	cout << endl << "- ADD NEW STUDENT" << endl;

	studentFileOrder = totalStudent;//DÜZENLEME GELECEK

	if (totalStudent > SIZE)
		cout << "The maximum number of students has been reached!";
	else {
		while (true) {
			cout << "Student Name and Surname (Max: 30 Characters): ";
			cin.getline(student[totalStudent].nameSurname,26);
			if (strlen(student[totalStudent].nameSurname) > 26)
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
			cin.getline(student[totalStudent].address, 26);
			if (strlen(student[totalStudent].address) > 26)
				cout << "Please enter a address with a maximum of 25 characters!" << endl;
			else
				break;
		}
		cout << "Mobile Phone: ";
		getline(cin, student[totalStudent].mobilePhone);
		cout << "e-Mail Adress: ";
		cin.getline(student[totalStudent].eMail, 51);

		student[totalStudent].averageGrade = calculateAverage(student[totalStudent].midtermGrade, student[totalStudent].finalGrade, totalStudent);
		student[totalStudent].letterGrade = letterGrade(student[totalStudent].averageGrade);

		printStudentToTxt(studentFileOrder, dataFile);//DÜZENLEME GELECEK
		dataFile << endl;
		newDataFile.write((char *)&student[totalStudent], sizeof(student[totalStudent]));
		dataFile.close();
		newDataFile.close();


		totalStudent++;
		registeredStudentsNum++;
		statusNumberOfRegisteredStudents.write((char *)&registeredStudentsNum, sizeof(registeredStudentsNum));
		statusNumberOfRegisteredStudents.close();
	}

	cout << endl << "Press a button to return to the main menu." << endl;
	_getch();
	system("cls");

}

void deleteStudent(fstream &newDataFile, fstream &dataFile) {
	int choice, i, newFlag[SIZE], deletedStudentCounter = 0, x = 0;
	unsigned long long int deleteID;
	char deleteName[26];

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
		cin.getline(deleteName, 26);
		for (i = 0; i < totalStudent; i++) {
			if (strcmp(deleteName, student[i].nameSurname) == 0) {
				newFlag[i] = i;
			}

		}
	}

	newDataFile.open("C:\\Users\\Casper\\Desktop\\StudentInputOutput\\StudentInfos.dat", ios::out | ios::in | ios::binary);
	dataFile.open("C:\\Users\\Casper\\Desktop\\StudentInputOutput\\StudentInfos.txt", ios::out | ios::in);

	for (i = 0; i < totalStudent; i++) {		
		if (i == 0) {
			dataFile.seekp((2 * 169 - 1), ios::beg);
		}
		else
			dataFile.seekp(169, ios::cur);

		if (newFlag[i] != -1) {
			strcpy_s(student[i].nameSurname, "xxxxxx xxxxxx");
			student[i].studentID = 111111111111;
			student[i].takenCourses = "CENGxxx";
			student[i].midtermGrade = 0;
			student[i].finalGrade = 0;
			student[i].averageGrade = 0;
			student[i].letterGrade = "xx";
			strcpy_s(student[i].address, "xxxxxxxxxxxxxxxxxxxxxxxxx");
			student[i].mobilePhone = "0(...)......";
			strcpy_s(student[i].eMail, "xxxxxxxxxxxx@xxxxx.xxx");

			newDataFile.write((char *)&student[i], sizeof(student[i]));
			printStudentToTxt(i, dataFile);
			
			deletedStudentCounter++;
		}
		if (i == 0) {
			newDataFile.seekp(sizeof(student[i]), ios::beg);
		}
		else {
			newDataFile.seekp(sizeof(student[i]), ios::cur);
		}
	}
	newDataFile.close();
	dataFile.close();

	loadStudents(newDataFile);
	
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

void updateStudent(fstream &newDataFile, fstream &dataFile) {
	int i, flag = -1;
	unsigned long long int updateID;

	newDataFile.open("C:\\Users\\Casper\\Desktop\\StudentInputOutput\\StudentInfos.dat", ios::out | ios::in | ios::binary);
	dataFile.open("C:\\Users\\Casper\\Desktop\\StudentInputOutput\\StudentInfos.txt", ios::out | ios::in);
	dataFile.seekp((2 * 169 - 1), ios::beg);

	cout << endl << "- UPDATE STUDENT" << endl;
	cout << "Student ID: ";
	cin >> updateID;
	cin.ignore();
	for (i = 0; i < totalStudent; i++) {
		if (i == 0) {
			newDataFile.seekp(sizeof(student[i]), ios::beg);
		}
		else {
			newDataFile.seekp(sizeof(student[i]), ios::cur);
		}
		if (updateID == student[i].studentID) {
			flag = i;
			dataFile.seekp(169, ios::cur);
			break;
		}
	}
	if (flag == -1)
		cout << "The student could not be found!" << endl;
	else {
		while (true) {
			cout << "Student Name and Surname (Max: 30 Characters): ";
			cin.getline(student[flag].nameSurname, 26);
			if (strlen(student[flag].nameSurname) > 26)
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
			cin.getline(student[flag].address, 26);
			if (strlen(student[flag].address) > 26)
				cout << "Please enter a address with a maximum of 25 characters!" << endl;
			else
				break;
		}
		cout << "Mobile Phone: ";
		getline(cin, student[flag].mobilePhone);
		cout << "e-Mail Adress: ";
		cin.getline(student[flag].eMail, 51);

		student[flag].averageGrade = calculateAverage(student[flag].midtermGrade, student[flag].finalGrade, flag);
		student[flag].letterGrade = letterGrade(student[flag].averageGrade);
	}
	
	dataFile.close();
	newDataFile.close();
	cout << endl << "Press a button to return to the main menu." << endl;
	_getch();
	system("cls");
}

void listStudents() {
	int i, j, choice, flag, newFlag[SIZE], counterNameSurname, counterCourse, newCounter;
	unsigned long long int listID;
	studentInfo tempStudent;
	char listNameSurname[26];
	string listCourse, listGrade;

	cout << endl << "- LIST STUDENTS" << endl;
	cout << "Please type -[1] to list 'All Student Informations in Alphabetical Order of Names', -[2] to list a specific student by 'Student ID', -[3] to list one or more specific students by 'Name and Surname', -[4] to list all student by 'Taken a Specific Course', -[5] to list one or more students by 'Letter Grade for a Course': ";
	cin >> choice;
	cout << endl;
	cin.ignore();
	if (choice == 1) {
		/*for (i = 0; i < totalStudent; i++) {
			for (j = i; j < totalStudent; j++) {
				if (student[i].nameSurname.compare(student[j].nameSurname) > 0) {
					tempStudent = student[i];
					student[i] = student[j];
					student[j] = tempStudent;
				}
			}
		}*/
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
		cin.getline(listNameSurname, 26);
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