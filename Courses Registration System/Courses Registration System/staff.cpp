#include "staff.h"
#include "student.h"
#include "function.h"
#include<conio.h>
string getSchoolYear(string path) {
	ifstream fileIn;
	fileIn.open(path, ios_base::in);

	string line;
	getline(fileIn, line, '-');
	fileIn.close();
	return line;
}

void loadStudentList(string path, _Student*& head) {
	wifstream fileIn;
	fileIn.open(path, ios_base::in);
	ifstream read;
	if (!fileIn.is_open()) {
		cout << "File is not existed!" << endl;
		fileIn.close();
		return;
	}

	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	wchar_t a = ',', b = '/';
	_Student* pCur = head;
	path.erase(path.end() - 4, path.end());
	path.erase(path.begin(), path.begin() + dirClass.length());
	while (!fileIn.eof()) {
		if (head == nullptr) {
			head = new _Student;
			pCur = head;
		}
		else {
			pCur->pNext = new _Student;
			pCur = pCur->pNext;
		}
		fileIn >> pCur->data.Number_In_Class >> a;
		fileIn >> pCur->data.ID_Student >> a;
		getline(fileIn, pCur->data.firstName, a);
		getline(fileIn, pCur->data.lastName, a);
		getline(fileIn, pCur->data.gender, a);
		fileIn >> pCur->data.Date_Of_Birth.day >> b;
		fileIn >> pCur->data.Date_Of_Birth.month >> b;
		fileIn >> pCur->data.Date_Of_Birth.year >> a;
		fileIn >> pCur->data.Social_ID;
		pCur->data.class_Of_Student = path;
		pCur->subregis = nullptr;
		pCur->pNext = nullptr;
	}

	fileIn.close();
}

void loadStudentList_changedPassword(string path,string path_Course ,_Student*& head) {
	head = nullptr;
	wifstream fileIn;
	wifstream readCourse;

	fileIn.open(path, ios_base::in);
	readCourse.open(path_Course, ios_base::in);

	if (!fileIn.is_open()) {
		cout << "File is not found!" << endl;
		fileIn.close();
		return;
	}

	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	readCourse.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	wchar_t a = ',', b = '/', c = '|';
	_Student* pCur = head;
	path.erase(path.end() - 4, path.end());
	path.erase(path.begin(), path.begin() + dirClass.length());

	ifstream read;
	read.open(dirClass_Save + "save_Account_" + path + ".txt", ios_base::in);

	int stuID, numOfCourse;
	wstring line;

	while (!fileIn.eof()) {
		if (head == nullptr) {
			head = new _Student;
			pCur = head;
		}
		else {
			pCur->pNext = new _Student;
			pCur = pCur->pNext;
		}
		fileIn >> pCur->data.Number_In_Class >> a;
		fileIn >> pCur->data.ID_Student >> a;
		getline(fileIn, pCur->data.firstName, a);
		getline(fileIn, pCur->data.lastName, a);
		getline(fileIn, pCur->data.gender, a);
		fileIn >> pCur->data.Date_Of_Birth.day >> b;
		fileIn >> pCur->data.Date_Of_Birth.month >> b;
		fileIn >> pCur->data.Date_Of_Birth.year >> a;
		fileIn >> pCur->data.Social_ID;

		getline(read, pCur->data.student_Account.ID, ',');
		getline(read, pCur->data.student_Account.password);

		readCourse >> stuID >> a >> numOfCourse;
		getline(readCourse, line);

		pCur->subregis = nullptr;
		_Subjects* subCur = pCur->subregis;

		for (int i = 1; i <= numOfCourse; i++) {
			if (pCur->subregis == nullptr) {
				pCur->subregis = new _Subjects;
				subCur = pCur->subregis;
				subCur->data_Prev = nullptr;
			}
			else {
				subCur->data_Next = new _Subjects;
				subCur->data_Next->data_Prev = subCur;
				subCur = subCur->data_Next;
			}
			getline(readCourse, line, a);
			subCur->subjects_Data.course_Data.course_ID = WStringToString(line);
			getline(readCourse, line, a);
			subCur->subjects_Data.course_Data.course_Name = WStringToString(line);
			getline(readCourse, subCur->subjects_Data.course_Data.Name_of_Teacher, a);
			readCourse >> subCur->subjects_Data.course_Data.credit >> a;
			getline(readCourse, line, a);
			subCur->subjects_Data.course_Data.first_Session.dayOfWeek = WStringToString(line);
			getline(readCourse, line, a);
			subCur->subjects_Data.course_Data.first_Session.session = WStringToString(line);
			getline(readCourse, line, a);
			subCur->subjects_Data.course_Data.second_Session.dayOfWeek = WStringToString(line);
			getline(readCourse, line, c);
			subCur->subjects_Data.course_Data.second_Session.session = WStringToString(line);
			getline(readCourse, line, a);
			subCur->subjects_Data.course_Data.schoolYear = WStringToString(line);
			readCourse >> subCur->subjects_Data.course_Data.semNo;
			getline(readCourse, line);
			subCur->data_Next = nullptr;
		}
		pCur->data.class_Of_Student = path;
		pCur->pNext = nullptr;
	}
	fileIn.close();
	read.close();
}

void loadScoreboardStudentList(string path, _Student* head) {
	ifstream read;
	read.open(path, ios::in);
	if (!read.is_open()) return;

	while (!read.eof()) {
		string nameCourse;
		getline(read, nameCourse);
		wifstream fin;
		fin.open(dirCourse_Student + nameCourse + ".csv", ios::in);

		fin.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

		int no, stuIDTmp;
		wstring line;
		wchar_t a = ',';
		while (!fin.eof()) {
			fin >> no >> a;
			fin >> stuIDTmp >> a;
			_Student* pCur = head;
			while (pCur->data.ID_Student != stuIDTmp) {
				pCur = pCur->pNext;
			}
			_Subjects* subCur = pCur->subregis;
			while (subCur->subjects_Data.course_Data.course_Name != nameCourse) subCur = subCur->data_Next;
			for (int i = 0; i < 3; i++) getline(fin, line, a);
			fin >> subCur->subjects_Data.course_Data.score.finalMark >> a;
			fin >> subCur->subjects_Data.course_Data.score.totalMark >> a;
			fin >> subCur->subjects_Data.course_Data.score.midtermMark >> a;
			fin >> subCur->subjects_Data.course_Data.score.otherMark;
			subCur->subjects_Data.course_Data.score.isScore = true;
			getline(fin, line);
		}
		fin.close();
	}

	read.close();
}

void displayStudentList(string path, _Student* head) {
	wofstream fileOut;
	fileOut.open(path, ios_base::out);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	if (!fileOut.is_open()) {
		cout << "Cant creat file!" << endl;
		fileOut.close();
		return;
	}

	wstring strTmp;
	while (head->pNext != nullptr) {
		fileOut << head->data.Number_In_Class << ",";
		fileOut << head->data.ID_Student << ",";
		fileOut << head->data.firstName << ",";
		fileOut << head->data.lastName << ",";
		fileOut << head->data.gender << ",";
		fileOut << head->data.Date_Of_Birth.day << "/" << head->data.Date_Of_Birth.month << "/" << head->data.Date_Of_Birth.year << ",";
		fileOut << head->data.Social_ID << ",";
		wstring tmp = stringToWString(head->data.class_Of_Student);
		fileOut << tmp << endl;
		head = head->pNext;
	}

	fileOut.close();
}

void convertAccountOfStudent(string path, _Student* head) {
	ofstream fileOut;
	fileOut.open(path, ios_base::out);
	if (!fileOut.is_open()) {
		cout << "Can't creat file" << endl;
		fileOut.close();
		return;
	}

	_Student* pCur = head;
	while (pCur->pNext != nullptr) {
		pCur->data.student_Account.ID = to_string(pCur->data.ID_Student);
		string dayTmp = to_string(pCur->data.Date_Of_Birth.day);
		string monthTmp = to_string(pCur->data.Date_Of_Birth.month);
		string yearTmp = to_string(pCur->data.Date_Of_Birth.year);
		if (pCur->data.Date_Of_Birth.day < 10) {
			dayTmp = "0" + to_string(pCur->data.Date_Of_Birth.day);
		}
		if (pCur->data.Date_Of_Birth.month < 10) {
			monthTmp = "0" + to_string(pCur->data.Date_Of_Birth.month);
		}
		pCur->data.student_Account.password = dayTmp + monthTmp + yearTmp;
		fileOut << pCur->data.student_Account.ID << ",";
		fileOut << pCur->data.student_Account.password << endl;
		pCur = pCur->pNext;
	}

	fileOut.close();
}

void convertCourseOfStudent(string path, _Student* head) {
	ofstream fileOut;
	fileOut.open(path, ios_base::out);
	if (!fileOut.is_open()) {
		return;
	}

	_Student* pCur = head;
	while (pCur->pNext != nullptr) {
		if (pCur != head) fileOut << endl;
		fileOut << pCur->data.ID_Student << "," << list_Len(pCur->subregis);
		pCur = pCur->pNext;
	}
	fileOut.close();
}

void changePassword_Staff(string username) {
	ifstream read;
	ofstream write;
}

void deleteStudentList(_Student*& head) {
	if (head == nullptr) return;
	_Student* cur = head;
	while (head != nullptr) {
		head = head->pNext;
		delete cur;
		cur = head;
	}
}

void listPush(_Student*& listStack, _Student* classPush) {
	if (classPush == nullptr) return;
	if (listStack == nullptr) {
		listStack = classPush;
		return;
	}
	_Student* pTmp = listStack;
	while (pTmp->pNext->pNext != nullptr) pTmp = pTmp->pNext;
	_Student* pJunk = pTmp->pNext;
	pTmp->pNext = classPush;
	delete pJunk;
}

bool is_Class_In_System(string path, string input) {
	ifstream line;
	line.open(path, ios_base::app);
	if (!line.is_open()) return true;
	string tmp;
	while (!line.eof()) {
		getline(line, tmp);
		if (input == tmp) {
			line.close();
			return false;
		}
	}
	line.close();
	return true;
}

void listStudents(_Student*& head) {
	string path;
	int i = 0;
	int temp;
	int n = 0;
	string menu[2] = { "Add First-year Student class", "Back" };
	_Student* headClass = nullptr;
	do {
		while (true) {
			system("cls");
			for (int j = 0; j < 2; j++) {
				if (n == j) {
					textcolor(12);
					GotoXY(39, 12 + j);
					cout << " > " << menu[j] << " < " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(40, 12 + j);
					cout << " " << menu[j] << " " << endl;
				}
			}
			temp = _getch();
			if (temp == 's' || temp == 'S' || temp == 80) {
				n++;
				if (n == 2) n = 0;
			}
			if (temp == 'w' || temp == 'W' || temp == 72) {
				n--;
				if (n == -1) n = 1;
			}
			if (temp == 13 || temp == 32) break;
		}
		system("cls");
		if (n != 1) {
			cout << "Input name of Class to add into the system: ";
			cin >> path;
			ofstream fileOut;
			fileOut.open(dirClass_Save + "classes_In_System.txt", ios_base::app);

			if (!is_Class_In_System(dirClass_Save + "classes_In_System.txt", path)) {
				cout << path << " is already in system. Pls add another class" << endl;
				cout << " enter to continue";
				temp = _getch();
				continue;
			}

			loadStudentList(dirClass + path + ".csv", headClass);
			displayStudentList(dirClass + path + "_Info" + ".csv", headClass);
			listPush(head, headClass);
			fileOut << path << endl;
			fileOut.close();
			convertAccountOfStudent(dirClass_Save + "save_Account_" + path + ".txt", headClass);
			convertCourseOfStudent(dirCourse_Student + "Registered_Course_" + path + ".txt", headClass);
		}
	} while (n != 1);
}

void loadStu_Save(_Student*& pHead) {
	_Student* headClass = nullptr;
	ifstream read;
	read.open(dirClass_Save + "classes_In_System.txt", ios_base::in);
	if (!read.is_open()) return;
	int line = check_Line(dirClass_Save + "classes_In_System.txt");
	for (int i = 1; i <= line; i++)  {
		string path;
		getline(read, path);
		loadStudentList_changedPassword(dirClass + path + ".csv", dirCourse_Student + "Registered_Course_" + path + ".txt",headClass);
		listPush(pHead, headClass);
		loadScoreboardStudentList(dirCourse_Student + "listOfCourses.txt", pHead);
	}
	read.close();
}

void staff_Login(string& username,int& n) {
	ifstream fileIn;
	int running = true;
	string password;
	int temp;
	string userTmp, passTmp;
	while (running) {
		GotoXY(37, 11);
		cout << "Username: ";
		cin >> username;
		GotoXY(37, 13);
		cout << "Password: ";
		cin >> password;

		fileIn.open(dirStaff + "Staff_Account.txt", ios_base::in);
		while (!fileIn.eof()) {
			string userTmp, passTmp;
			getline(fileIn, userTmp, ',');
			getline(fileIn, passTmp);
			if (username == userTmp && passTmp == password) {
				running = false;
				break;
			}
		}
		if (!running) {
			system("cls");
			GotoXY(45, 13);
			cin.ignore(1000, '\n');
			GotoXY(43, 12);
			cout << "Login Successfully!" << endl;
			Sleep(200);
			system("cls");
		}
		else {
			system("cls");
			GotoXY(40, 12);
			cout << "Invalid login, please try again" << endl;
			GotoXY(45, 13);
			cout << " Enter to Try Again."<<endl;
			GotoXY(50, 14);
			cout << " e to Exit." << endl;
			temp = _getch();
			
			system("cls");
			if (temp == 'e') { n = 0; return; }
		}
		fileIn.close();
	}
}

void turnOnVietText() {
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
}

void turnOffVietText() {
	_setmode(_fileno(stdin), _O_TEXT);
	_setmode(_fileno(stdout), _O_TEXT);
}

int check_Line(string path) {
	ifstream f;
	f.open(path, ios_base::in);
	int lineCount = 0;
	string line;
	while (getline(f, line)) {
		lineCount++;
	}
	f.close();
	return lineCount;
}

void createCourseList(string path) {
	int running = true;
	wofstream fileOut;
	char* courseID, * courseName;
	wchar_t* teacherName;
	int credits;
	int maxStu;
	char* day1, * session1;
	char* day2, * session2;
	int choose;
	char sTmp[101];

	fileOut.open(path, ios_base::app);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	if (!fileOut.is_open()) {
		cout << "Can't create file" << endl;
		return;
	}

	int no = check_Line(path); 

	do {
		cout << "INFORMATION OF COURSE!" << endl;
		cout << "Course ID: ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		courseID = new char[strlen(sTmp) + 1];
		strcpy_s(courseID, strlen(sTmp) + 1, sTmp);

		
		cout << "Course Name: ";
		cin.ignore(1000, '\n');
		
		cin.get(sTmp, 101, '\n');
		courseName = new char[strlen(sTmp) + 1];
		strcpy_s(courseName, strlen(sTmp) + 1, sTmp);

		cout << "Teacher Name: ";
		turnOnVietText();
		cin.ignore(1000, '\n');
		wchar_t wsTmp[101];
		wcin.get(wsTmp, 101, '\n');
		teacherName = new wchar_t[wcslen(wsTmp) + 1];
		wcscpy_s(teacherName, wcslen(wsTmp) + 1, wsTmp);
		wcin.ignore(1000, '\n');
		turnOffVietText();

		cout << "Number of credits: ";
		cin >> credits;

		cout << "Maximum number of students in the course: ";
		cin >> maxStu;

		cout << "Day in week (MON / TUE / WED / THU / FRI / SAT): ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		day1 = new char[strlen(sTmp) + 1];
		strcpy_s(day1, strlen(sTmp) + 1, sTmp);
		
		cout << "The session of course (S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)): ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		session1 = new char[strlen(sTmp) + 1];
		strcpy_s(session1, strlen(sTmp) + 1, sTmp);
		
		cout << "Day in week (MON / TUE / WED / THU / FRI / SAT): ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		day2 = new char[strlen(sTmp) + 1];
		strcpy_s(day2, strlen(sTmp) + 1, sTmp);
		

		cout << "The session of course (S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)): ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		session2 = new char[strlen(sTmp) + 1];
		strcpy_s(session2, strlen(sTmp) + 1, sTmp);
		cin.ignore(1000, '\n');

		if (no != 0) fileOut << endl;
		fileOut << no + 1 << ",";
		fileOut << courseID << ",";
		_setmode(_fileno(stdout), _O_U16TEXT);
		fileOut << courseName << ",";
		fileOut << teacherName << ",";
		_setmode(_fileno(stdout), _O_TEXT);
		
		fileOut << credits << ",";
		fileOut << maxStu << ",";
		fileOut << day1 << "," << session1 << ",";
		fileOut << day2 << "," << session2;

		delete[] courseID;
		delete[] courseName;
		delete[] teacherName;
		delete[] day1;
		delete[] day2;
		delete[] session1;
		delete[] session2;
		
		cout << "Successfully! Course is created" << endl;

		cout << "-------------------\n1. Continue to create course." << endl;
		cout << "2. Exit" << endl;

		cin >> choose;
		if (choose == 1) {
			++no;
		}
		else running = false;
	} while (running);
	fileOut.close();
}

void viewCourseList(string path) {
	wifstream fileIn;
	fileIn.open(dirCourse + "CoursesRegistration.txt", ios_base::in);

	if (!fileIn.is_open() || check_Line(path) == 0) {
		cout << "You haven't created any course yet. Please create the course first" << endl;
		fileIn.close();
		return;
	}

	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	cout << "VIEW LIST SYSTEM" << endl;
	while (!fileIn.eof()) {
		int no, credits, max;
		wstring d1, s1, d2, s2;
		wstring courseID, courseName;
		wstring teacherName;
		wchar_t a = ',';
		wstring junk;
		turnOnVietText();
		fileIn >> no >> a;
		getline(fileIn, courseID, a);
		getline(fileIn, courseName, a);
		getline(fileIn, teacherName, a);
		fileIn >> credits >> a;
		fileIn >> max >> a;
		getline(fileIn, d1, a);
		getline(fileIn, s1, a);
		getline(fileIn, d2, a);
		getline(fileIn, s2);
		turnOffVietText();
		_setmode(_fileno(stdout), _O_U8TEXT);
		wcout << no << " - " << courseID << " - " << courseName << endl;
		wcout << "Lecturer: " << teacherName << endl;
		wcout << "Credits: " << credits << endl;
		wcout << "Num of students: " << max << endl;
		wcout << "Schedule: " << d1 << " - " << s1 << ", " << d2 << " - " << s2 << endl;
		_setmode(_fileno(stdout), _O_TEXT);
		wcout << endl;
	}
	cout <<  "TOTAL OF COURSES: " << check_Line(path) << endl;
	cout << "=============================" << endl;
	
}

void update_Course_Info() {
	wifstream fileOld;
	wofstream fileNew;

	string dirOld = dirCourse + "CoursesRegistration.txt";
	string dirNew = dirCourse + "change.txt";

	fileOld.open(dirOld, ios_base::in);
	fileNew.open(dirNew, ios_base::out);

	fileOld.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	fileNew.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	viewCourseList(dirOld);
	wchar_t a = ',';
	cout << "Choose course to update (0 to exit): " << endl;
	int choose;
	cin >> choose;
	if (choose == 0) {
		fileOld.close();
		fileNew.close();
		return;
	}
	while (!fileOld.eof()) {
		int tmp;
		
		wstring junk;
		fileOld >> tmp >> a;
		

		if (tmp == choose) {
			fileNew << tmp << ",";
			break;
		}

		getline(fileOld, junk);
		fileNew << tmp << "," << junk << endl;
	}

	cout << "Choose the infomation of course to update" << endl;
	cout << "1. Course ID" << endl;
	cout << "2. Course Name" << endl;
	cout << "3. Teacher's name" << endl;
	cout << "4. Number of credits" << endl;
	cout << "5. Maximum number of students in course" << endl;
	cout << "6. Date and session" << endl;

	int change;
	cin >> change;
	switch (change)
	{
	case 1: {
		char sTmp[101];
		cout << "Enter new Course ID: ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		char* courseID = new char[strlen(sTmp) + 1];
		strcpy_s(courseID, strlen(sTmp) + 1, sTmp);
		fileNew << courseID << ",";
		wstring tmp, junk;
		getline(fileOld, tmp, a);
		while (!fileOld.eof()) {
			getline(fileOld, junk);
			fileNew << junk;
			if (!fileOld.eof()) fileNew << endl;
		}
		delete[] courseID;
		break;
	}

	case 2: {
		char sTmp[101];
		cout << "Enter new Course Name: ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		char* courseName = new char[strlen(sTmp) + 1];
		strcpy_s(courseName, strlen(sTmp) + 1, sTmp);
		wstring tmp;
		getline(fileOld, tmp, a);
		fileNew << tmp << "," << courseName << ",";
		wstring junk;
		getline(fileOld, tmp, a);
		while (!fileOld.eof()) {
			getline(fileOld, junk);
			fileNew << junk;
			if (!fileOld.eof()) fileNew << endl;
		}
		delete[] courseName;
		break;
	}

	case 3: {
		wchar_t sTmp[101];
		cout << "Enter new Teacher's name: ";
		turnOnVietText();
		cin.ignore(1000, '\n');
		wcin.get(sTmp, 101, '\n');
		wchar_t* teacherName = new wchar_t[wcslen(sTmp) + 1];
		wcscpy_s(teacherName, wcslen(sTmp) + 1, sTmp);
		wcin.ignore(1000, '\n');
		turnOffVietText();
		wstring tmp;
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		_setmode(_fileno(stdout), _O_U16TEXT);
		fileNew << tmp << "," << teacherName << ",";
		_setmode(_fileno(stdout), _O_TEXT);
		wstring junk;
		getline(fileOld, tmp, a);
		while (!fileOld.eof()) {
			getline(fileOld, junk);
			fileNew << junk;
			if (!fileOld.eof()) fileNew << endl;
		}
		delete[] teacherName;
		break;
	}

	case 4: {
		int credit;
		cout << "Enter new credits of course: ";
		cin >> credit;
		wstring tmp;
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		fileNew << tmp << "," << credit << ",";
		wstring junk;
		getline(fileOld, tmp, a);
		while (!fileOld.eof()) {
			getline(fileOld, junk);
			fileNew << junk;
			if (!fileOld.eof()) fileNew << endl;
		}
		break;
	}

	case 5: {
		cout << "Enter new maximum number of students in course: ";
		int num;
		cin >> num;
		wstring tmp;
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		int intTmp;
		fileOld >> intTmp >> a;
		fileNew << intTmp << "," << num << ",";
		wstring junk;
		getline(fileOld, tmp, a);
		while (!fileOld.eof()) {
			getline(fileOld, junk);
			fileNew << junk;
			if (!fileOld.eof()) fileNew << endl;
		}
		break;
	}

	case 6: {
		wstring d1, ss1, d2, ss2;
		cout << "Enter new date and session of this course" << endl;
		cout << "Day in week (MON / TUE / WED / THU / FRI / SAT): ";
		wcin >> d1;
		cout << "The session of course (S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)): ";
		wcin >> ss1;
		cout << "Day in week (MON / TUE / WED / THU / FRI / SAT): ";
		wcin >> d2;
		cout << "The session of course (S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)): ";
		wcin >> ss2;
		wstring tmp;
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		int intTmp;
		fileOld >> intTmp >> a;
		fileNew << intTmp << ",";
		fileOld >> intTmp >> a;
		fileNew << intTmp << "," << d1 << "," << ss1 << "," << d2 << "," << ss2 << endl;
		wstring junk;
		getline(fileOld, junk);
		while (!fileOld.eof()) {
			getline(fileOld, junk);
			fileNew << junk;
			if (!fileOld.eof()) fileNew << endl;
		}
		
		break;
	}
	default:
		break;
	}
	cout << "Infomation updated!" << endl;
	fileOld.close();
	fileNew.close();
	remove(dirOld.c_str());
	rename(dirNew.c_str(), dirOld.c_str());
}

void delete_Courses() {
	wifstream fileOld;

	string dirFileOld = dirCourse + "CoursesRegistration.txt";
	fileOld.open(dirFileOld, ios_base::in);
	int line = check_Line(dirCourse + "CoursesRegistration.txt");

	if (!fileOld.is_open() || line == 0) {
		cout << "NOTHING TO DELETE!\n" << "================================================" << endl;
		fileOld.close();
		return;
	}

	wofstream fileNew;
	string dirFileNew = dirCourse + "change.txt";
	fileNew.open(dirFileNew, ios_base::out);

	fileOld.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	fileNew.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	viewCourseList(dirCourse + "CoursesRegistration.txt");
	wchar_t a = ',';
	cout << "TOTAL OF COURSES: " << line << endl;
	cout << "Choose course to delete: " << endl;
	int choose, count;
	cin >> choose;
	if (choose > line) {
		cout << "Your chosen course is exceed the number of courses! Please try again!" << endl << "===================================" << endl;
		fileOld.close();
		fileNew.close();
		return;
	}
	wstring junk;
	_setmode(_fileno(stdout), _O_U16TEXT);
	
	while (!fileOld.eof()) {
		fileOld >> count >> a;

		if (count == choose) break;

		getline(fileOld, junk);
		if (count != 1) fileNew << endl;
		fileNew << count << "," << junk;
	}

	getline(fileOld, junk);
	while (!fileOld.eof()) {
		fileOld >> count >> a;
		getline(fileOld, junk);
		if (count != 2) fileNew << endl;
		fileNew << count - 1 << "," << junk;
	}
	_setmode(_fileno(stdout), _O_TEXT);
	cout << "Successfully deleted the course!" << endl;

	fileOld.close();
	fileNew.close();
	remove(dirFileOld.c_str());
	rename(dirFileNew.c_str(), dirFileOld.c_str());
}

void showInfo_Staff(string username,int x,int y) {
	ifstream fileIn;
	fileIn.open(dirStaff + "Staff_Info.txt", ios_base::in);
	while (!fileIn.eof()) {
		string tmp, name;
		getline(fileIn, tmp, ',');
		getline(fileIn, name);
		if (tmp == username) {
			GotoXY(x, y);
			cout << "Infomartion of staff" << endl;
			GotoXY(x, y+1);
			cout << "Name: " << name << endl;
			GotoXY(x, y+2);
			cout << "Department: Academic Staff" << endl;
			GotoXY(x, y+3);
			fileIn.close();
			
			return;
		}
	}
	cout << "Infomation of this staff is currently not existed in the system " << endl;
	fileIn.close();
}

void create_Course_Registration() {
	ofstream fileOut;
	bool running = true;

	fileOut.open(dirRegis + "Registration.txt", ios_base::out);

	if (!fileOut.is_open()) {
		GotoXY(25, 12);
		cout << "Can't create Courese Registration. Pls try again!" << endl;
		fileOut.close();
		return;
	}

	Date dayStart, dayEnd;
	int hourStart, hourEnd, minuteStart, minuteEnd;

	do {
		GotoXY(20,12);
		cout << "Input Date Course registration session is open (DD/MM/YYYY): ";
		cin >> dayStart.day;
		cin.ignore(10, '/');
		cin >> dayStart.month;
		cin.ignore(10, '/');
		cin >> dayStart.year;
		GotoXY(20, 13);
		cout << "Time (24 Clock - HH:MM): ";
		cin >> hourStart;
		cin.ignore(10, ':');
		cin >> minuteStart;
		GotoXY(20, 14);
		cout << "Input Date Course registration seesion is close (DD/MM/YYYY): ";
		cin >> dayEnd.day;
		cin.ignore(10, '/');
		cin >> dayEnd.month;
		cin.ignore(10, '/');
		cin >> dayEnd.year;
		GotoXY(20, 15);
		cout << "Time (24h Clock - HH:MM): ";
		cin >> hourEnd;
		cin.ignore(10, ':');
		cin >> minuteEnd;

		string minuteTmp = to_string(minuteStart);
		if (minuteStart < 10) minuteTmp = "0" + minuteTmp;

		cout << "Pls confirm before creating registration session (Press Y to confirm, N to type again!" << endl;
		cout << "Start Date: " << dayStart.day << "/" << dayStart.month << "/" << dayStart.year << endl;
		cout << "Time: " << hourStart << ":" << minuteTmp << endl;

		string minuteTmp_End = to_string(minuteEnd);
		if (minuteEnd < 10) minuteTmp_End = "0" + minuteTmp_End;

		cout << "End Date: " << dayEnd.day << "/" << dayEnd.month << "/" << dayEnd.year << endl;
		cout << "Time: " << hourEnd << ":" << minuteTmp_End << endl;

		string choose;
		GotoXY(40, 21);
		cout << "Confirm? ";
		cin >> choose;

		if (choose == "Y" || choose == "y") {
			GotoXY(27, 22);
			cout << "Course Registration completely created!" << endl;

			fileOut << dayStart.day << "/" << dayStart.month << "/" << dayStart.year << ",";
			fileOut << hourStart << ":" << minuteTmp << endl;
			fileOut << dayEnd.day << "/" << dayEnd.month << "/" << dayEnd.year << ",";
			fileOut << hourEnd << ":" << minuteTmp_End;

			running = false;
		}
	} while (running);
	

	fileOut.close();
}

bool is_Created_Schoolyear_Before(string line) {
	ifstream read;
	read.open(dirSchoolYear + "School_Year.txt", ios_base::in);

	if (!read.is_open()) return true;

	string check;

	while (!read.eof()) {
		getline(read, check, '-');
		if (check == line) {
			read.close();
			return false;
		}
		getline(read, check);
	}
	read.close();
	return true;
}

bool is_Created_Sem_Before(string line, string schoolyear) {
	ifstream read;
	read.open(dirSchoolYear + schoolyear + ".txt", ios_base::out);

	string check;
	while (!read.eof()) {
		getline(read, check);
		if (line == check) {
			read.close();
			return false;
		}
		for (int i = 0; i < 2; i++) getline(read, check);
	}

	read.close();
	return true;
}

int list_Len_Available_Score(_Subjects* Node, string schoolyear, int semCur) {
	if (Node == nullptr) return 0;
	int count = 0;
	while (Node != nullptr) {
		if (Node->subjects_Data.course_Data.schoolYear == schoolyear && Node->subjects_Data.course_Data.semNo == semCur && Node->subjects_Data.course_Data.score.isScore) ++count;
		Node = Node->data_Next;
	}
	return count;
}

void arrange_Sem(string schoolyear, string sem) {
	ifstream read;
	ofstream fileNew;
	
	string oldName = dirSchoolYear + schoolyear + ".txt";
	string newName = dirSchoolYear + "tmp.txt";

	read.open(oldName, ios_base::in);
	fileNew.open(newName, ios_base::out);

	string check, line;
	while (!read.eof()) {
		getline(read, check);
		if (check == sem) {
			Date startDate, endDate;
			GotoXY(39, 16);
			cout << "Enter start date of " << sem << " (DD/MM/YYYY): ";
			cin >> startDate.day;
			cin.ignore(10, '/');
			cin >> startDate.month;
			cin.ignore(10, '/');
			cin >> startDate.year;
			GotoXY(39, 18);
			cout << "Enter end date of " << sem << " (DD/MM/YYYY): ";
			cin >> endDate.day;
			cin.ignore(10, '/');
			cin >> endDate.month;
			cin.ignore(10, '/');
			cin >> endDate.year;
			if (check_Line(newName) != 0) fileNew << endl;
			fileNew << sem << endl;
			fileNew << startDate.day << "/" << startDate.month << "/" << startDate.year << endl;
			fileNew << endDate.day << "/" << endDate.month << "/" << endDate.year;
			for (int i = 0; i < 2; i++) getline(read, line);
		}
		else {
			if (check_Line(newName) != 0) fileNew << endl;
			fileNew << check;
			for (int i = 0; i < 2; i++) {
				getline(read, line);
				fileNew << endl << line;
			}
		}
	}
	read.close();
	fileNew.close();
	remove(oldName.c_str());
	rename(newName.c_str(), oldName.c_str());
}

void add_Schoolyear(Date& schoolyear) {
	bool running = true;
	do {
		system("cls");
		GotoXY(40, 11);
		cout << "Input the schoolyear: ";
		int year;
		cin >> year;
		if (!is_Created_Schoolyear_Before(to_string(year))) {
			GotoXY(40, 12);
			cout << "You have created school year " << to_string(year) << " before!" << endl;
			GotoXY(40, 13);
			cout << "Press any key to continue or Esc to exit" << endl;
			int choose = _getch();
			if (choose == 27) return;
		}
		else {
			GotoXY(42, 12);
			cout << "You mean " << year << "-" << year + 1 << "?";
			GotoXY(42, 13);
			cout << "Y. Yes \t N. No" << endl;
			string choose;
			GotoXY(44, 14);
			cin >> choose;
			if (choose == "Y" || choose == "y") {
				ofstream out;
				ofstream outFile;
				outFile.open(dirSchoolYear + "School_Year.txt", ios_base::app);
				out.open(dirSchoolYear + to_string(year) + "-" + to_string(year + 1) + ".txt", ios_base::out);
				if (!out.is_open()) {
					GotoXY(40, 12);
					cout << "Can't create School year!" << endl;
				}
				if (check_Line(dirSchoolYear + "School_Year.txt") != 0) outFile << endl;
				outFile << year << "-" << year + 1;
				outFile.close();
				out.close();
				schoolyear.year = year;
				running = false;
			}
		}
	} while (running);
}

//void studentRegisterSub(_Student* head) {
//	string sub;
//	string cl;
//	_Student* cur = head;
//	cout << "Input the subject title: ";
//	cin.ignore(1000, '\n');
//	getline(cin, sub);
//	cout << endl << "Input the class: ";
//	cin.ignore(1000, '\n');
//	getline(cin, cl);
//	wifstream fileIn;
//	wofstream fileOut;
//	int count = 0;
//	wchar_t a = ',';
//	wstring dob;
//	fileIn.open(cl + ".csv", ios_base::in);
//	if (!fileIn.is_open()) return;
//	fileOut.open(cl + "_" + sub + ".csv", ios_base::out);
//	if (!fileOut.is_open()) return;
//	fileOut << "No" << a << "ID" << a << "First Name" << a << "Last Name" << a << "Gender" << a << "Social ID" << endl;
//	while (!fileIn.eof()) {
//		while (cur != nullptr) {
//			fileIn >> cur->data.Number_In_Class >> a >> cur->data.ID_Student >> a >> cur->data.firstName >> a >> cur->data.lastName >> a >> cur->data.gender >> a >> dob >> a >> cur->data.Social_ID >> a;
//			while (cur->subregis != nullptr) {
//				if (cur->subregis->subjects_Data.course_Data.course_Name == sub) {
//					count++;
//					fileOut<<count<<a<<cur->data.ID_Student << a << cur->data.firstName << a << cur->data.lastName << a << cur->data.gender << a << dob << a << cur->data.Social_ID << a <<endl;
//				}
//				cur->subregis = cur->subregis->data_Next;
//			}
//			cur = cur->pNext;
//		}
//	}
//	fileIn.close();
//	fileOut.close();
//}


//void viewScoreClass(_Student* head) {
//	string cl;
//	string sub;
//	_Student* cur = head;
//	wchar_t a = ',';
//	wstring dob;
//	wifstream fileIn;
//	wofstream fileOut;
//	cout << "Please inter name of class: ";
//	cin >> cl;
//	cout << endl << "Please inter subject: ";
//	cin >> sub;
//	fileIn.open(cl + ".csv", ios_base::in);
//	if (!fileIn.is_open()) return;
//	fileOut.open(cl + "_" + sub + ".csv", ios_base::out);
//	if (!fileOut.is_open()) return;
//	fileOut << "No" << a << "ID" << a << "Full name" << a << "Total mark" << a << "Final mark" << a << "Midterm mark" << a << "Other mark" << a;
//	while (!fileIn.eof()) {
//		while (cur != nullptr) {
//			fileIn >> cur->data.Number_In_Class >> a >> cur->data.ID_Student >> a >> cur->data.firstName >> a >> cur->data.lastName >> a >> cur->data.gender >> a >> dob >> a >> cur->data.Social_ID >> a;
//			fileOut << cur->data.Number_In_Class << a << cur->data.ID_Student << a << cur->data.firstName << " " << cur->data.lastName << a;
//			while (cur->data.stu_Score.data_ScoreBoard.course_Data.course_Name != sub ) {
//				/*cur->data.stu_Score = cur->data.stu_Score.dataNext;*/
//			}
//			cur = cur->pNext;
//		}
//	}
//	fileIn.close();
//	fileOut.close();
//}

//void viewScoreClass(_Student* head) {
//	string cl;
//	string sub;
//	_Student* cur;
//	wchar_t a = ',';
//	wstring dob;
//	wifstream fileIn;
//	wofstream fileOut;
//	cout << "Please inter name of class: ";
//	cin >> cl;
//	cout << endl << "Please inter subject: ";
//	cin >> sub;
//	fileIn.open(cl + ".csv", ios_base::in);
//	if (!fileIn.is_open()) return;
//	fileOut.open(cl + "_" + sub + ".csv", ios_base::out);
//	if (!fileOut.is_open()) return;
//	fileOut << "No" << a << "ID" << a << "Full name" << a << "Total mark" << a << "Final mark" << a << "Midterm mark" << a << "Other mark" << a;
//	while (!fileIn.eof()) {
//		fileIn >> cur->data.Number_In_Class >> a >> cur->data.ID_Student >> a >> cur->data.firstName >> a >> cur->data.lastName >> a >> cur->data.gender >> a >> dob >> a >> cur->data.Social_ID >> a;
//		while (cur->subregis->subjects_Data.course_Data.course_Name != sub) cur->subregis = cur->subregis->data_Next;
//		if (cur->subregis) {
//			fileOut << cur->data.Number_In_Class << a << cur->data.ID_Student << a << cur->data.firstName << " " << cur->data.lastName << a << cur->subregis->subjects_Data.course_Data.score.totalMark << a;
//			fileOut << cur->subregis->subjects_Data.course_Data.score.midtermMark << a << cur->subregis->subjects_Data.course_Data.score.finalMark << a;
//		}
//		cur = cur->pNext;
//	}
//	fileIn.close();
//	fileOut.close();
//}

void importResult(_Student* head) {
	if (head == nullptr) {
		cout << "There is not student in system" << endl;
		cout << "Press any key to continue..." << endl;
		int sth = _getch();
		return;
	}
	string nameCourse;
	cout << "Input name of course to import score: ";
	getline(cin, nameCourse, '\n');
	wifstream readFile;
	readFile.open(dirCourse_Student + nameCourse + ".csv", ios_base::in);

	readFile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	if (!readFile.is_open()) {
		cout << nameCourse << " is not found!" << endl;
		cout << "Press any key to continue...." << endl;
		int sth = _getch();
		return;
	}

	else {
		ofstream save;
		save.open(dirCourse_Student + "listOfCourses.txt", ios::app);
		if (check_Line(dirCourse_Student + "listOfCourses.txt") != 0) save << endl;
		save << nameCourse;
		save.close();
	}

	int no, stuIDTmp;
	wstring line;
	wchar_t a = ',';
	while (!readFile.eof()) {
		readFile >> no >> a;
		readFile >> stuIDTmp >> a;
		_Student* pCur = head;
		while (pCur->data.ID_Student != stuIDTmp) {
			pCur = pCur->pNext;
		}
		_Subjects* subCur = pCur->subregis;
		while (subCur->subjects_Data.course_Data.course_Name != nameCourse) subCur = subCur->data_Next;
		for (int i = 0; i < 3; i++) getline(readFile, line, a);
		readFile >> subCur->subjects_Data.course_Data.score.finalMark >> a;
		readFile >> subCur->subjects_Data.course_Data.score.totalMark >> a;
		readFile >> subCur->subjects_Data.course_Data.score.midtermMark >> a;
		readFile >> subCur->subjects_Data.course_Data.score.otherMark;
		subCur->subjects_Data.course_Data.score.isScore = true;	
		getline(readFile, line);
	}

	cout << "Import score of " << nameCourse << " succesfully" << endl;
	readFile.close();
}

void viewScoreboard_Course_Display(string nameCourse) {
	wifstream read;
	read.open(dirCourse_Student + nameCourse + ".csv", ios::in);
	if (!read.is_open()) {
		cout << nameCourse << " is not found!" << endl;
		return;
	}

	read.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	int no, stuID;
	wchar_t a = ',';
	int numLine = check_Line(dirCourse_Student + nameCourse + ".csv");
	wstring fullName, tmp;
	float score;

	system("cls");
	GotoXY(17, 2);
	cout << char(218); for (int i = 0; i < 78; i++) {
		GotoXY(18 + i, 2);
		if (i == 2 || i == 15 || i == 50 || i == 56 || i == 64 || i == 70) cout << char(194);
		else cout << char(196);
	}
	cout << char(191) << endl;
	GotoXY(17, 3); cout << char(179);
	GotoXY(18, 3); cout << "No";
	GotoXY(20, 3); cout << char(179) << " Student ID";
	GotoXY(33, 3); cout << char(179); GotoXY(47, 3); cout << "Full Name";
	GotoXY(68, 3); cout << char(179) << "Total";
	GotoXY(74, 3); cout << char(179) << " Final";
	GotoXY(82, 3); cout << char(179) << " Mid";
	GotoXY(88, 3); cout << char(179) << " Other";
	GotoXY(96, 3); cout << char(179);

	GotoXY(17, 4); cout << char(195);
	for (int i = 0; i < 78; i++) {
		if (i == 2 || i == 15 || i == 50 || i == 56 || i == 64 || i == 70) cout << char(197);
		else cout << char(196);
	}
	cout << char(180) << endl;
	for (int i = 0; i <= 2 * numLine - 1; i++) {
		if (i % 2 == 0) {
			read >> no >> a;
			GotoXY(17, 5 + i); cout << char(179) << no;
			GotoXY(20, 5 + i); cout << char(179);
			read >> stuID >> a;
			GotoXY(23, 5 + i); cout << stuID;
			GotoXY(33, 5 + i); cout << char(179);
			turnOnVietText();
			getline(read, fullName, a);
			GotoXY(34, 5 + i); wcout << fullName;
			turnOffVietText();
			GotoXY(68, 5 + i); cout << char(179);
			for (int q = 0; q < 2; q++) getline(read, tmp, a);
			read >> score >> a;
			GotoXY(70, 5 + i); cout << score;
			GotoXY(74, 5 + i); cout << char(179);
			read >> score >> a;
			GotoXY(77, 5 + i); cout << score;
			GotoXY(82, 5 + i); cout << char(179);
			read >> score >> a;
			GotoXY(84, 5 + i); cout << score;
			GotoXY(88, 5 + i); cout << char(179);
			read >> score;
			GotoXY(91, 5 + i); cout << score;
			GotoXY(96, 5 + i); cout << char(179);
			getline(read, tmp);
		}
		else {
			GotoXY(17, 5 + i);
			if (i == 2 * numLine - 1) cout << char(192);
			else cout << char(195);
			for (int k = 0; k < 78; k++) {
				GotoXY(18 + k, 5 + i);
				if (k == 2 || k == 15 || k == 50 || k == 56 || k == 64 || k == 70) {
					if (i == 2 * numLine - 1) cout << char(193);
					else cout << char(197);
				}
				else cout << char(196);
			}
			if (i == 2 * numLine - 1) cout << char(217);
			else cout << char(180);
		}
	}

	read.close();
}

void viewScoreboard_Course_Menu() {
	cout << "Input name of Course to view the scoreboard: ";
	string nameCourse;
	getline(cin, nameCourse, '\n');
	viewScoreboard_Course_Display(nameCourse);
}

void update_Stu_Score(string nameCourse, _Subjects* Node, int IDStu) {
	wifstream read;
	wofstream write;

	read.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	write.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	string oldName = dirCourse_Student + nameCourse + ".csv";
	string newName = dirCourse_Student + "Change.csv";
	read.open(oldName, ios::in);
	write.open(newName, ios::out);

	int numLine = check_Line(oldName);

	wstring line;

	wchar_t a = ',';
	int stuID;
	int tmp = 0;
	while(tmp < numLine) {
		if (tmp != 0) write << endl;
		for (int i = 0; i < 2; i++) {
			read >> stuID >> a;
			write << stuID << a;
		}
		for (int i = 0; i < 3; i++) {
			getline(read, line, a);
			write << line << a;
		}
		if (stuID == IDStu) {
			getline(read, line);
			write << Node->subjects_Data.course_Data.score.totalMark << a;
			write << Node->subjects_Data.course_Data.score.finalMark << a;
			write << Node->subjects_Data.course_Data.score.midtermMark << a;
			write << Node->subjects_Data.course_Data.score.otherMark;
		}
		else {
			getline(read, line);
			write << line;
		}
		tmp++;
	}

	read.close();
	write.close();
	remove(oldName.c_str());
	rename(newName.c_str(), oldName.c_str());
}

void update_Student_Result(_Student* Node) {
	cout << "Input Sudent ID: ";
	int stuID;
	cin >> stuID;
	while (Node != nullptr && Node->data.ID_Student != stuID) Node = Node->pNext;
	if (Node == nullptr) {
		cout << stuID << " is not found!" << endl;
		_getch();
		return;
	}

	int numOfCourse = list_Len(Node->subregis);
	string* menu = new string[numOfCourse + 1];
	
	_Subjects* pTmp = Node->subregis;
	for (int i = 0; i < numOfCourse; i++) {
		menu[i] = pTmp->subjects_Data.course_Data.course_ID + " - " + pTmp->subjects_Data.course_Data.course_Name + " - Semester " + to_string(pTmp->subjects_Data.course_Data.semNo) + " " + pTmp->subjects_Data.course_Data.schoolYear;
		pTmp = pTmp->data_Next;
	}
	menu[numOfCourse] = "Back";

	int step = 0, tmp;
	bool running = true;
	while (running) {
		while (true) {
			system("cls");
			GotoXY(44, 9);
			cout << "Choose course to Update";
			for (int k = 0; k < numOfCourse + 1; k++) {
				if (k == step) {
					textcolor(12);
					GotoXY(44, 10 + k);
					cout << " > " << menu[k] << " < " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(45, 10 + k);
					cout << " " << menu[k] << " " << endl;
				}
			}
			tmp = _getch();
			if (tmp == 's' || tmp == 'S' || tmp == 80) {
				step++;
				if (step >= numOfCourse + 1) step = 0;
			}
			if (tmp == 'w' || tmp == 'W' || tmp == 72) {
				step--;
				if (step < 0) step = numOfCourse;
			}
			if (tmp == 13 || tmp == 32) break;
		}
		if (step == numOfCourse) {
			delete[] menu;
			running = false;
			return;
		}
		else {
			string courseIDTmp = menu[step];
			courseIDTmp.erase(courseIDTmp.begin() + 8, courseIDTmp.end());
			pTmp = Node->subregis;
			while (pTmp->subjects_Data.course_Data.course_ID != courseIDTmp) pTmp = pTmp->data_Next;
			cout << "Mid-term Score: ";
			cin >> pTmp->subjects_Data.course_Data.score.midtermMark;
			cout << "Other score: ";
			cin >> pTmp->subjects_Data.course_Data.score.otherMark;
			cout << "Final score: ";
			cin >> pTmp->subjects_Data.course_Data.score.finalMark;
			cout << "Total score: ";
			cin >> pTmp->subjects_Data.course_Data.score.totalMark;

			update_Stu_Score(pTmp->subjects_Data.course_Data.course_Name, pTmp, Node->data.ID_Student);

			cout << "Editted successfully!" << endl;
			cout << endl << "\t\t\t\t\t\tPress any key to exit..." << endl;
			int sth = _getch();
		}
	}
}

void viewScoreboard_Class(_Student* head, string schoolyear, int semCur, string nameClass) {
	int numOfCourse = check_Line(dirCourse + "CoursesRegistration_" + schoolyear + "_" + to_string(semCur) + ".txt");
	int numOfStu = check_Line(dirClass + nameClass + ".csv"); // 20CLC have 48 students
	wifstream read;
	read.open(dirCourse + "CoursesRegistration_" + schoolyear + "_" + to_string(semCur) + ".txt", ios::in);

	string* courseID = new string[numOfCourse];
	for (int i = 0; i < numOfCourse; i++) {
		wchar_t a = ',';
		wstring lineTmp;
		for (int k = 0; k < 2; k++) getline(read, lineTmp, a);
		courseID[i] = WStringToString(lineTmp);
		getline(read, lineTmp);
	}

	read.close();

	system("cls");
	
	_Student* cur = head;
	while (cur !=nullptr && cur->data.class_Of_Student != nameClass) cur = cur->pNext;
	if (cur == nullptr) {
		cout << nameClass << " is not found" << endl;
		return;
	}

	GotoXY(2, 3); cout << char(218);
	for (int i = 0; i < 43; i++) {
		if (i == 2 || i == 13 || i == 42) {
			GotoXY(3 + i, 3); cout << char(194);
			GotoXY(3 + i, 5); cout << char(197);
		}
		else {
			GotoXY(3 + i, 3); cout << char(196);
			GotoXY(3 + i, 5); cout << char(196);
		}
	}

	for (int i = 0; i < numOfCourse; i++) {
		GotoXY(46 + 9 * i, 4); cout << courseID[i] << char(179);
		for (int k = 0; k <= 8; k++) {
			if (k == 8) {
				GotoXY(46 + k + 9 * i, 3); cout << char(194);
				GotoXY(46 + k + 9 * i, 5); cout << char(197);
			}
			else {
				GotoXY(46 + k + 9 * i, 3); cout << char(196);
				GotoXY(46 + k + 9 * i, 5); cout << char(196);
			}
		}
	}

	GotoXY(2, 4); cout << char(179) << "No";
	GotoXY(5, 4); cout << char(179) << "Student ID";
	GotoXY(16, 4); cout << char(179); GotoXY(26, 4); cout << "Full Name";
	GotoXY(45, 4); cout << char(179);

	for (int i = 0; i < 20; i++) {
		if (i == 7) {
			GotoXY(46 + 9 * numOfCourse + i, 3); cout << char(194);
			GotoXY(46 + 9 * numOfCourse + i, 5); cout << char(197);
		}
		else if (i == 19) {
			GotoXY(46 + 9 * numOfCourse + i, 3); cout << char(191);
			GotoXY(46 + 9 * numOfCourse + i, 5); cout << char(180);
		}
		else {
			GotoXY(46 + 9 * numOfCourse + i, 3); cout << char(196);
			GotoXY(46 + 9 * numOfCourse + i, 5); cout << char(196);
		}

	}
	GotoXY(46 + 9 * numOfCourse, 4); cout << "GPA Sem" << char(179);
	GotoXY(46 + 9 * numOfCourse + 8, 4); cout << "GPA Overall" << char(179);
	GotoXY(2, 5); cout << char(195);

	
	int count = 0;
	for (int i = 0; i <= 2 * numOfStu - 1; i++) {
		if (i % 2 == 0) {
			// #
			GotoXY(2, 6 + i); cout << char(179) << ++count;
			// Stu ID
			GotoXY(5, 6 + i); cout << char(179) << " " << cur->data.ID_Student;
			// Stu Name
			GotoXY(16, 6 + i); cout << char(179);
			turnOnVietText();
			wcout << cur->data.firstName << " " << cur->data.lastName;
			turnOffVietText();

			GotoXY(45, 6 + i); cout << char(179);


			for (int x = 0; x < numOfCourse; x++) {
				_Subjects* subCur = cur->subregis;
				GotoXY(30, 30);
				while (subCur != nullptr && !(subCur->subjects_Data.course_Data.schoolYear == schoolyear && subCur->subjects_Data.course_Data.semNo == semCur && subCur->subjects_Data.course_Data.course_ID == courseID[x] && subCur->subjects_Data.course_Data.score.isScore)) subCur = subCur->data_Next;

				for (int k = 0; k <= 8; k++) {
					if (k == 8) {
						GotoXY(46 + k + 9 * x, 5 + i); cout << char(197);
						GotoXY(46 + k + 9 * x, 6 + i); cout << char(179);
						if (subCur == nullptr) {
							GotoXY(49 + k + 9 * (x - 1), 6 + i); cout << "NULL";
						}
						// Print Score of x(th) Course ID
						// Final
						else {
							GotoXY(47 + k + 9 * (x - 1), 6 + i); cout << subCur->subjects_Data.course_Data.score.finalMark;
							// Total
							GotoXY(50 + k + 9 * (x - 1), 6 + i); cout << "|" << subCur->subjects_Data.course_Data.score.totalMark;
						}
					}
					else {
						GotoXY(46 + k + 9 * x, 5 + i); cout << char(196);
					}
				}
			}

			// GPA sem - > GPA Overall
			for (int x = 0; x < 20; x++) {
				if (x == 7) {
					GotoXY(46 + 9 * numOfCourse + x, 6 + i); cout << char(179);
					GotoXY(49 + 9 * (numOfCourse - 1) + x, 6 + i); cout << setprecision(3) << calGPA_One_Sem(cur->subregis, schoolyear, semCur);
					GotoXY(46 + 9 * numOfCourse + x, 7 + i); cout << char(197);
				}
				else if (x == 19) {
					GotoXY(46 + 9 * numOfCourse + x, 6 + i); cout << char(179);
					GotoXY(47 + 9 * (numOfCourse - 1) + x, 6 + i); cout << setprecision(3) << total_GPA(cur->subregis, schoolyear, semCur);
					GotoXY(46 + 9 * numOfCourse + x, 7 + i); cout << char(180);
				}
				else {
					GotoXY(46 + 9 * numOfCourse + x, 7 + i); cout << char(196);
				}
			}
			cur = cur->pNext;

		}
		else {
			GotoXY(2, 6 + i);
			if (i == 2 * numOfStu - 1) cout << char(192);
			else cout << char(195);
			for (int k = 0; k < 43; k++) {
				GotoXY(3 + k, 6 + i);
				if (k == 2 || k == 13 || k == 42) {
					if (i == 2 * numOfStu - 1) cout << char(193);
					else cout << char(197);
				}
				else cout << char(196);
			}

			if (i == 2 * numOfStu - 1) {
				for (int k = 0; k < numOfCourse; k++) {
					for (int x = 0; x <= 8; x++) {
						if (x == 8) {
							GotoXY(46 + x + 9 * k, 6 + i); cout << char(193);
						}
						else {
							GotoXY(46 + x + 9 * k, 6 + i); cout << char(196);
						}
					}
				}
				GotoXY(46 + 9 * numOfCourse + 7, 6 + i); cout << char(193);
				GotoXY(46 + 9 * numOfCourse + 19, 6 + i); cout << char(217);
			}

		}
	}
	delete[] courseID;
}

void view_Student_List(_Student* head,string nameOfClass) {
	int line = check_Line(dirClass + nameOfClass + ".csv");


	while (head != nullptr && head->data.class_Of_Student != nameOfClass) head = head->pNext;
	system("cls");
	GotoXY(17, 2);
	cout << char(218); for (int i = 0; i < 75; i++) {
		GotoXY(18 + i, 2);
		if (i == 2 || i == 15 || i == 50 || i == 59) cout << char(194);
		else cout << char(196);
	}
	cout << char(191) << endl;
	GotoXY(17, 3); cout << char(179);
	GotoXY(18, 3); cout << "No";
	GotoXY(20, 3); cout << char(179) << " Student ID";
	GotoXY(33, 3); cout << char(179); GotoXY(47, 3); cout << "Full Name";
	GotoXY(68, 3); cout << char(179) << " Gender";
	GotoXY(77, 3); cout << char(179) << " Date Of Birth";
	GotoXY(93, 3); cout << char(179);

	GotoXY(17, 4); cout << char(195);
	for (int i = 0; i < 75; i++) {
		if (i == 2 || i == 15 || i == 50 || i == 59) cout << char(197);
		else cout << char(196);
	}
	cout << char(180) << endl;


	int no = 0;
	for (int i = 0; i <= 2 * line - 1; i++) {
		if (i % 2 == 0) {
			GotoXY(17, 5 + i); cout << char(179);
			GotoXY(18, 5 + i); cout << ++no;

			GotoXY(20, 5 + i); cout << char(179);
			GotoXY(23, 5 + i); cout << head->data.ID_Student;
			
			GotoXY(33, 5 + i); cout << char(179);
			turnOnVietText();
			GotoXY(34, 5 + i); wcout << head->data.firstName << " " << head->data.lastName;
			turnOffVietText();

			GotoXY(68, 5 + i); cout << char(179);
			GotoXY(70, 5 + i); wcout << head->data.gender;


			GotoXY(77, 5 + i); cout << char(179);
			GotoXY(80, 5 + i);
			if (head->data.Date_Of_Birth.day < 10) cout << "0";
			cout << head->data.Date_Of_Birth.day << "/";
			if (head->data.Date_Of_Birth.month < 10) cout << "0";
			cout << head->data.Date_Of_Birth.month << "/" << head->data.Date_Of_Birth.year;
			GotoXY(93, 5 + i); cout << char(179);
			head = head->pNext;
		}
		else {
			GotoXY(17, 5 + i);
			if (i == 2 * line - 1) cout << char(192);
			else cout << char(195);
			for (int k = 0; k < 75; k++) {
				GotoXY(18 + k, 5 + i);
				if (k == 2 || k == 15 || k == 50 || k == 59) {
					if (i == 2 * line - 1) cout << char(193);
					else cout << char(197);
				}
				else cout << char(196);
			}
			if (i == 2 * line - 1) cout << char(217);
			else cout << char(180);
		}
	}
}

void view_Student_List_Menu(_Student* head) {
	ifstream read;
	read.open(dirClass_Save + "classes_In_System.txt", ios::in);
	if (!read.is_open()) {
		cout << "There is no class in system" << endl;
		return;

	}
	int line = check_Line(dirClass_Save + "classes_In_System.txt");
	string* menu = new string[line + 1];

	for (int i = 0; i < line; i++) {
		string readLine;
		getline(read, readLine);
		menu[i] = readLine;
	}
	menu[line] = "Back";


	int step = 0, tmp;
	bool running = true;
	while (running) {
		while (true) {
			system("cls");
			for (int k = 0; k < line + 1; k++) {
				if (k == step) {
					textcolor(12);
					GotoXY(44, 10 + k);
					cout << " > " << menu[k] << " < " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(45, 10 + k);
					cout << " " << menu[k] << " " << endl;
				}
			}
			tmp = _getch();
			if (tmp == 's' || tmp == 'S' || tmp == 80) {
				step++;
				if (step >= line + 1) step = 0;
			}
			if (tmp == 'w' || tmp == 'W' || tmp == 72) {
				step--;
				if (step < 0) step = line;
			}
			if (tmp == 13 || tmp == 32) break;
		}
		if (step == line) {
			delete[] menu;
			running = false;
			return;
		}
		else {
			view_Student_List(head, menu[step]);
			cout << endl << "\t\t\t\t\t\tPress any key to exit..." << endl;
			int sth = _getch();
		}
	}
	read.close();
	delete[] menu;
}

void view_List_Of_Course(_Student* head,string nameCourse, string schoolyear, int sem) {
	int line = check_Line(dirCourse_Student + nameCourse + ".csv");
	system("cls");
	cout << "Name course: " << nameCourse << endl;
	cout << "line = " << line << endl;
	system("pause");
	bool checkCourse = false;
	while (head != nullptr && !checkCourse) {
		_Subjects* subCur = head->subregis;
		while (subCur != nullptr && subCur->subjects_Data.course_Data.course_Name != nameCourse && subCur->subjects_Data.course_Data.schoolYear != schoolyear && subCur->subjects_Data.course_Data.semNo != sem) subCur = subCur->data_Next;
		if (subCur == nullptr) {
			checkCourse = false;
			head = head->pNext;
		}
		else checkCourse = true;
	}
	system("cls");
	GotoXY(17, 2);
	cout << char(218); for (int i = 0; i < 75; i++) {
		GotoXY(18 + i, 2);
		if (i == 2 || i == 15 || i == 50 || i == 59) cout << char(194);
		else cout << char(196);
	}
	cout << char(191) << endl;
	GotoXY(17, 3); cout << char(179);
	GotoXY(18, 3); cout << "No";
	GotoXY(20, 3); cout << char(179) << " Student ID";
	GotoXY(33, 3); cout << char(179); GotoXY(47, 3); cout << "Full Name";
	GotoXY(68, 3); cout << char(179) << " Gender";
	GotoXY(77, 3); cout << char(179) << " Date Of Birth";
	GotoXY(93, 3); cout << char(179);

	GotoXY(17, 4); cout << char(195);
	for (int i = 0; i < 75; i++) {
		if (i == 2 || i == 15 || i == 50 || i == 59) cout << char(197);
		else cout << char(196);
	}
	cout << char(180) << endl;


	int no = 0;
	for (int i = 0; i <= 2 * line - 1; i++) {
		if (i % 2 == 0) {
			GotoXY(17, 5 + i); cout << char(179);
			GotoXY(18, 5 + i); cout << ++no;

			GotoXY(20, 5 + i); cout << char(179);
			GotoXY(23, 5 + i); cout << head->data.ID_Student;

			GotoXY(33, 5 + i); cout << char(179);
			turnOnVietText();
			GotoXY(34, 5 + i); wcout << head->data.firstName << " " << head->data.lastName;
			turnOffVietText();

			GotoXY(68, 5 + i); cout << char(179);
			GotoXY(70, 5 + i); wcout << head->data.gender;


			GotoXY(77, 5 + i); cout << char(179);
			GotoXY(80, 5 + i);
			if (head->data.Date_Of_Birth.day < 10) cout << "0";
			cout << head->data.Date_Of_Birth.day << "/";
			if (head->data.Date_Of_Birth.month < 10) cout << "0";
			cout << head->data.Date_Of_Birth.month << "/" << head->data.Date_Of_Birth.year;
			GotoXY(93, 5 + i); cout << char(179);
			head = head->pNext;
			
			checkCourse = false;
			while (head != nullptr && !checkCourse) {
				_Subjects* subCur = head->subregis;
				while (subCur != nullptr && subCur->subjects_Data.course_Data.course_Name != nameCourse && subCur->subjects_Data.course_Data.schoolYear != schoolyear && subCur->subjects_Data.course_Data.semNo != sem) subCur = subCur->data_Next;
				if (subCur == nullptr) {
					checkCourse = false;
					head = head->pNext;
				}
				else checkCourse = true;
			}

		}
		else {
			GotoXY(17, 5 + i);
			if (i == 2 * line - 1) cout << char(192);
			else cout << char(195);
			for (int k = 0; k < 75; k++) {
				GotoXY(18 + k, 5 + i);
				if (k == 2 || k == 15 || k == 50 || k == 59) {
					if (i == 2 * line - 1) cout << char(193);
					else cout << char(197);
				}
				else cout << char(196);
			}
			if (i == 2 * line - 1) cout << char(217);
			else cout << char(180);
		}
	}
}

void view_List_Of_Course_Menu2(_Student* head, string schoolyear, int sem) {
	wifstream read;
	read.open(dirCourse + "CoursesRegistration_" + schoolyear + "_" + to_string(sem) + ".txt", ios::in);

	read.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	int numOfCourse = check_Line(dirCourse + "CoursesRegistration_" + schoolyear + "_" + to_string(sem) + ".txt");

	string* menu = new string[numOfCourse + 1];
	menu[numOfCourse] = "Back";
	for (int i = 0; i < numOfCourse; i++) {
		wstring line, courseName;
		wchar_t a = ',';
		for (int k = 0; k < 2; k++) getline(read, line, a);
		getline(read, courseName, a);
		menu[i] = WStringToString(line) + " - " + WStringToString(courseName);
		getline(read, line);
	}

	int step = 0, tmp;
	bool running = true;
	while (running) {
		while (true) {
			system("cls");
			for (int k = 0; k < numOfCourse + 1; k++) {
				if (k == step) {
					textcolor(12);
					GotoXY(44, 10 + k);
					cout << " > " << menu[k] << " < " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(45, 10 + k);
					cout << " " << menu[k] << " " << endl;
				}
			}
			tmp = _getch();
			if (tmp == 's' || tmp == 'S' || tmp == 80) {
				step++;
				if (step >= numOfCourse + 1) step = 0;
			}
			if (tmp == 'w' || tmp == 'W' || tmp == 72) {
				step--;
				if (step < 0) step = numOfCourse;
			}
			if (tmp == 13 || tmp == 32) break;
		}
		if (step == numOfCourse) {
			delete[] menu;
			running = false;
			return;
		}
		else {
			string tmp = menu[step];
			tmp.erase(tmp.begin(), tmp.begin() + 11);
			string nameOfCourse = tmp;
			view_List_Of_Course(head, nameOfCourse, schoolyear, sem);
			cout << endl << "\t\t\t\t\t\tPress any key to exit..." << endl;
			int sth = _getch();
		}
	}

	read.close();
}

void view_List_Of_Course_Menu(_Student* head) {
	ifstream readSem, readSchoolyear;

	readSchoolyear.open(dirSchoolYear + "School_Year.txt", ios_base::in);

	int numOfLine = check_Line(dirSchoolYear + "School_Year.txt");
	int sumLine = 0;
	string line, schoolyear;

	for (int i = 0; i < numOfLine; i++) {
		getline(readSchoolyear, line);
		sumLine += check_Line(dirSchoolYear + line + ".txt") / 3;
	}

	readSchoolyear.seekg(0, readSchoolyear.beg);

	string* menu = new string[sumLine + 1];

	menu[sumLine] = "Back";
	int i = sumLine - 1;
	for (int k = 0; k < numOfLine; k++) {
		getline(readSchoolyear, schoolyear);
		readSem.open(dirSchoolYear + schoolyear + ".txt", ios_base::in);
		int lineTmp = check_Line(dirSchoolYear + schoolyear + ".txt") / 3;
		for (int k = 0; k < lineTmp; k++) {
			getline(readSem, line);
			menu[i] = line + " " + schoolyear;
			for (int j = 0; j < 2; j++) getline(readSem, line);
			i--;
		}
		readSem.close();
	}

	int step = 0, tmp;
	bool running = true;
	while (running) {
		while (true) {
			system("cls");
			for (int k = 0; k < sumLine + 1; k++) {
				if (k == step) {
					textcolor(12);
					GotoXY(44, 10 + k);
					cout << " > " << menu[k] << " < " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(45, 10 + k);
					cout << " " << menu[k] << " " << endl;
				}
			}
			tmp = _getch();
			if (tmp == 's' || tmp == 'S' || tmp == 80) {
				step++;
				if (step >= sumLine + 1) step = 0;
			}
			if (tmp == 'w' || tmp == 'W' || tmp == 72) {
				step--;
				if (step < 0) step = sumLine;
			}
			if (tmp == 13 || tmp == 32) break;
		}
		if (step == sumLine) {
			delete[] menu;
			running = false;
			return;
		}
		else {
			for (int k = 0; k < 9; k++) schoolyear[k] = menu[step][11 + k];
			int sem = menu[step][9] - 48;
			system("cls");
			view_List_Of_Course_Menu2(head, schoolyear, sem);;
			cout << endl << "\t\t\t\t\t\tPress any key to exit..." << endl;
			int sth = _getch();
		}
	}
}

