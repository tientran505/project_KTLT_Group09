#include "function.h"
#include "staff.h"
#include "student.h"

void menu_Course_Staff();
void staff_Menu(string username, _Student*& headStu);

void textcolor(int color) {
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, color);
	return;
}
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}

void GotoXY(int x, int y) {

	COORD coord;

	coord.X = x;

	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}
void FixConsoleWindow() {

	HWND consoleWindow = GetConsoleWindow();

	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);

	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);

	SetWindowLong(consoleWindow, GWL_STYLE, style);
	return;

}
void Exit_Box(int a, int b) {
	int y;
	int x;
	x = a + 15;
	y = b + 6;
	GotoXY(8 + x, 2 + y); cout << "EXIT";
	GotoXY(x, y);
	for (int i = x; i < x + 20; i++) {
		cout << char(196);
	}
	GotoXY(x, y);
	for (int i = y; i < y + 5; i++) {
		GotoXY(x, i);
		cout << char(179);
	}
	GotoXY(x, y + 4);
	for (int i = x; i < x + 20; i++) {
		cout << char(196);
	}
	for (int i = 1; i < 4; i++) {
		GotoXY(20 + x, y + i);
		cout << char(179);
	}
	GotoXY(x, y);	cout << char(218);
	GotoXY(x, 4 + y);	cout << char(192);
	GotoXY(20 + x, y);	cout << char(191);
	GotoXY(20 + x, 4 + y);	cout << char(217);
}
void Choose_Exit(int a, int b) {
	int x;
	int y;
	x = a + 15;
	y = b + 6;
	textcolor(3);
	GotoXY(8 + x, 2 + y); cout << "EXIT";
	GotoXY(x, y);	cout << char(201);
	for (int i = x + 1; i < x + 20; i++) {
		cout << char(205);
	}
	for (int i = y + 1; i < y + 4; i++) {
		GotoXY(x, i);
		cout << char(186);
	}
	GotoXY(x, 4 + y);	cout << char(200);
	for (int i = x + 1; i < x + 20; i++) {
		cout << char(205);
	}
	GotoXY(20 + x, y);	cout << char(187);
	for (int i = y + 1; i < y + 4; i++) {
		GotoXY(20 + x, i);
		cout << char(186);
	}
	GotoXY(20 + x, 4 + y);	cout << char(188);
	textcolor(15);
}
void ChoosedStaff(int x, int y) {
	textcolor(3);
	GotoXY(3 + x, 2 + y); cout << "LOGIN AS STAFF";
	GotoXY(x, y);	cout << char(201);
	for (int i = x + 1; i < x + 20; i++) {
		cout << char(205);
	}
	for (int i = y + 1; i < y + 4; i++) {
		GotoXY(x, i);
		cout << char(186);
	}
	GotoXY(x, 4 + y);	cout << char(200);
	for (int i = x + 1; i < x + 20; i++) {
		cout << char(205);
	}
	GotoXY(20 + x, y);	cout << char(187);
	for (int i = y + 1; i < y + 4; i++) {
		GotoXY(20 + x, i);
		cout << char(186);
	}
	GotoXY(20 + x, 4 + y);	cout << char(188);
	textcolor(15);
}

void StaffChoose(int x, int y) {
	GotoXY(3 + x, 2 + y); cout << "LOGIN AS STAFF";
	GotoXY(x, y);
	for (int i = x; i < x + 20; i++) {
		cout << char(196);
	}
	GotoXY(x, y);
	for (int i = y; i < y + 5; i++) {
		GotoXY(x, i);
		cout << char(179);
	}
	GotoXY(x, y + 4);
	for (int i = x; i < x + 20; i++) {
		cout << char(196);
	}
	for (int i = 1; i < 4; i++) {
		GotoXY(20 + x, y + i);
		cout << char(179);
	}
	GotoXY(x, y);	cout << char(218);
	GotoXY(x, 4 + y);	cout << char(192);
	GotoXY(20 + x, y);	cout << char(191);
	GotoXY(20 + x, 4 + y);	cout << char(217);
}

void ChoosedStudent(int a, int b) {

	int x = a + 30, y = b;
	textcolor(3);
	GotoXY(3 + x, 2 + y); cout << "LOGIN AS STUDENT";
	GotoXY(x, y);	cout << char(201);
	for (int i = x + 1; i < x + 20; i++) {
		cout << char(205);
	}

	for (int i = y + 1; i < y + 4; i++) {
		GotoXY(x, i);
		cout << char(186);
	}
	GotoXY(x, 4 + y);	cout << char(200);
	for (int i = x + 1; i < x + 20; i++) {
		cout << char(205);
	}
	GotoXY(20 + x, y);	cout << char(187);
	for (int i = y + 1; i < y + 4; i++) {
		GotoXY(20 + x, i);
		cout << char(186);
	}
	GotoXY(20 + x, 4 + y);	cout << char(188);
	textcolor(15);
}

void StudentChoose(int a, int y) {
	int x = a + 30;
	GotoXY(3 + x, 2 + y); cout << "LOGIN AS STUDENT";
	GotoXY(x, y);

	for (int i = x; i <= x + 20; i++) {
		cout << char(196);
	}
	GotoXY(x, y);
	for (int i = y + 1; i < y + 5; i++) {
		GotoXY(x, i);
		cout << char(179);
	}
	GotoXY(x, y + 4);
	for (int i = x; i <= x + 20; i++) {
		cout << char(196);
	}
	for (int i = 1; i < 4; i++) {
		GotoXY(20 + x, y + i);
		cout << char(179);
	}
	GotoXY(x, y);	cout << char(218);
	GotoXY(x, 4 + y);	cout << char(192);
	GotoXY(20 + x, y);	cout << char(191);
	GotoXY(20 + x, 4 + y);	cout << char(217);
}

int MainMenu(int x, int y) {
	int temp;
	int i = 0;
	system("cls");
	ShowCur(0);
	
	ifstream read;
	read.open(dirClass_Save + "classes_In_System.txt", ios_base::in);

	if (read.is_open()) {
		int line = check_Line(dirClass_Save + "classes_In_System.txt");

			for (int k = 1; k <= line; k++) {
				string path;
					getline(read, path);
					cout << "Added " << path << " in the system" << endl;
			}
		read.close();
	}
	
	currentDateTime();
	ChoosedStaff(x, y);
	StudentChoose(x, y);
	Exit_Box(x, y);
	while (true) {
		//system("cls");
		ShowCur;
		//currentDateTime();
		if (i == 0) {
			StudentChoose(x, y);
			ChoosedStaff(x, y);
			Exit_Box(x, y);
		}
		if (i == 1) {
			ChoosedStudent(x, y);
			StaffChoose(x, y);
			Exit_Box(x, y);
		}
		if (i == 2) {
			StudentChoose(x, y);
			StaffChoose(x, y);
			Choose_Exit(x, y);
		}
		temp = _getch();
		if (temp == 'a' || temp == 'A' || temp == 75) {
			if (i == 0) i++;
			else i--;
		}
		if (temp == 'd' || temp == 'D' || temp == 77) {
			if (i == 1) i--;
			else i++;
		}
		if (temp == 's' || temp == 'S' || temp == 80) {
			i = 2;
		}
		if (temp == 'w' || temp == 'W' || temp == 72) {
			i = 0;
		}
		else if (temp == 13 || temp == 32) {
			switch (i) {
			case 0: system("cls");
				return 1;
			case 1:system("cls");
				return 2;
			default: system("cls");
				return 0;
			}
		}
	}
}

void create_SemesterMenu(string schoolyear) {
	int i = 0;
	int tmp;
	Date startDate, endDate;
	GotoXY(40, 5);
	string menu[4] = { "Semester 1" , "Semester 2", "Semester 3", "Back" };


	bool running = true;
	
	while (running) {
		system("cls");
		GotoXY(40, 3);
		cout << "Choose a semester to register for the " << schoolyear << " school year!" << endl;
		for (int k = 0; k < 4; k++) {
			if (k == i) {
				textcolor(12);
				GotoXY(39, 5 + k);
				cout << " > " << menu[k] << " < " << endl;
				textcolor(15);
			}
			else {
				textcolor(15);
				GotoXY(40, 5 + k);
				cout << " " << menu[k] << " " << endl;
			}
		}
		tmp = _getch();
		if (tmp == 's' || tmp == 'S' || tmp == 80) {
			i++;
			if (i == 4) i = 0;
		}
		if (tmp == 'w' || tmp == 'W' || tmp == 72) {
			i--;
			if (i == -1) i = 2;
		}
		if (tmp == 13 || tmp == 32) running = false;
	}
	
	if (i == 3) return;
	system("cls");
	if (!is_Created_Sem_Before(menu[i], schoolyear)) {
		GotoXY(45, 14);
		string menu_Tmp[2] = { "Re-register this semester", "Exit" };
		int chooseTmp = 0;
		bool runningTmp = true;
		while (runningTmp) {
			system("cls");
			GotoXY(45, 13);
			cout << "You registered for " << menu[i]<< endl;
			for (int k = 0; k < 2; k++) {
				if (k == chooseTmp) {
					textcolor(12);
					GotoXY(42, 15 + k);
					cout << " > " << menu_Tmp[k] << " < " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(43, 15 + k);
					cout << " " << menu_Tmp[k] << " " << endl;
				}
			}
			tmp = _getch();
			if (tmp == 'w' || tmp == 'W' || tmp == 72) {
				chooseTmp--;
				if (chooseTmp < 0) chooseTmp = 1;
			}
			if (tmp == 's' || tmp == 'S' || tmp == 80) {
				chooseTmp++;
				if (chooseTmp > 1) chooseTmp = 0;
			}
			if (tmp == 13 || tmp == 32) runningTmp = false;
		}
		if (chooseTmp == 0) {
			arrange_Sem(schoolyear, menu[i]);
			GotoXY(39, 23);
			cout << "Re-register the sem succesfully!" << endl;
			int choose = _getch();
		}
		if (chooseTmp == 1) return;
		return;
	}
	GotoXY(39, 10);
	cout << "Enter start date of " << menu[i] << " (DD/MM/YYYY): ";
	cin >> startDate.day;
	cin.ignore(10, '/');
	cin >> startDate.month;
	cin.ignore(10, '/');
	cin >> startDate.year;
	GotoXY(39, 12);
	cout << "Enter end date of " << menu[i] << " (DD/MM/YYYY): ";
	cin >> endDate.day;
	cin.ignore(10, '/');
	cin >> endDate.month;
	cin.ignore(10, '/');
	cin >> endDate.year;

	ofstream fileOut;
	fileOut.open(dirSchoolYear + schoolyear + ".txt", ios_base::app);

	if (check_Line(dirSchoolYear + schoolyear + ".txt") != 0) fileOut << endl;

	fileOut << menu[i] << endl;
	fileOut << startDate.day << "/" << startDate.month << "/" << startDate.year << endl;
	fileOut << endDate.day << "/" << endDate.month << "/" << endDate.year;

	GotoXY(39, 14);
	cout << "Create semester succesfully!" << endl;
	GotoXY(39, 15);
	cout << "Press any key to continue...";
	int choose = _getch();
	fileOut.close();
}

void course_Registration_Result_Menu(_Student* Node) {
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
			view_Reigstration_Results(Node->subregis, schoolyear, sem);
			cout << "Press any key to exit..." << endl;
			tmp = _getch();
		}
	}
}

void create_SchoolyearMenu() {	
	int i = 0;
	int tmp;
	GotoXY(40, 5);
	int line = check_Line(dirSchoolYear + "School_Year.txt");
	if (line == 0) {
		system("cls");
		GotoXY(40, 10);
		cout << "You have not created any school year before!" << endl;
		GotoXY(40, 11);
		cout << "Enter to continue..." << endl;
		int a = _getch();
		return;
	}
	ifstream read;
	bool running = true;
	string* menu = new string[line + 1];
	read.open(dirSchoolYear + "School_Year.txt", ios_base::in);
	for (int j = line - 1; j >= 0; j--) {
		getline(read, menu[j]);
	}
	menu[line] = "Back";
	while (running) {
		system("cls");
		for (int k = 0; k < line + 1; k++) {
			if (k == i) {
				textcolor(12);
				GotoXY(39, 5 + k);
				if (k == line) cout << " > " << menu[k] << " < " << endl;
				else cout << " > " << "Create Semesters for " << menu[k] << " < " << endl;
				textcolor(15);
			}
			else {
				textcolor(15);
				GotoXY(40, 5 + k);
				if (k == line) cout << " " << menu[k] << " " << endl;
				else cout << " " << "Create Semesters for " << menu[k] << " " << endl;
			}
		}
		tmp = _getch();
		if (tmp == 's' || tmp == 'S' || tmp == 80) {
			i++;
			if (i == line + 1) i = 0;
		}
		if (tmp == 'w' || tmp == 'W' || tmp == 72) {
			i--;
			if (i == -1) i = line;
		}
		if (tmp == 13 || tmp == 32) {
			running = false;
			break;
		}
	}
	if (i == line) {
		delete[] menu;
		return;
	}
	system("cls");
	create_SemesterMenu(menu[i]);
	delete[] menu;
}

void menu_Create_SY_Tmp() {
	int i = 0;
	string menu[3] = { "1. Create new School year", "2. Create new semester", "3. Back"};
	bool running = true;
	int tmp;
	while (running) {
		while (running) {
			system("cls");
			for (int k = 0; k < 3; k++) {
				if (k == i) {
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
				i++;
				if (i == 3) i = 0;
			}
			if (tmp == 'w' || tmp == 'W' || tmp == 72) {
				i--;
				if (i == -1) i = 2;
			}
			if (tmp == 13 || tmp == 32) break;
		}
		switch (i) {
		case 0: {
			Date schoolyear;
			add_Schoolyear(schoolyear);
			break;
		}
		case 1: {
			create_SchoolyearMenu();
			break;
		}
		case 2: {
			running = false;
			break;
		}
		}
	}
	

	
}


void menu_View_ScoreBoard_Of_Class(_Student* head) {
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
			cout << "Input Name of class to view the scoreboard: ";
			string nameclass;
			cin >> nameclass;
			viewScoreboard_Class(head, schoolyear, sem, nameclass);
			cout << endl << "\t\t\t\t\t\tPress any key to exit..." << endl;
			int sth = _getch();
		}
	}
}


void staff_Scoreboard_Management(_Student*& headStu) {
	int temp;
	int i = 0;
	bool running = true;
	string menu[5] = { "1. Import the Scoreboard", "2. Update student result", "3. View the Scoreboard of a Course", "4. View the Scoreboard of Class", "5. Back" };
	do {
		while (true) {
			system("cls");
			for (int j = 0; j < 5; j++) {
				if (j == i) {
					textcolor(12);
					GotoXY(37, 9 + j);
					cout << " > " << menu[j] << " > " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(38, 9 + j);
					cout << " " << menu[j] << " " << endl;
				}
			}
			temp = _getch();
			if (temp == 's' || temp == 'S' || temp == 80) {
				i++;
				if (i == 5) i = 0;
			}
			if (temp == 'w' || temp == 'W' || temp == 72) {
				i--;
				if (i == -1) i = 4;
			}
			if (temp == 13 || temp == 32) break;
		}
	
		switch (i) {
		case 0: {
			importResult(headStu);
			cout << "Press any key to continue..." << endl;
			temp = _getch();
			break;
		}
		case 1: {
			update_Student_Result(headStu);
			break;
		}
		case 2: {
			viewScoreboard_Course_Menu();
			cout << endl << "Press any key to continue..." << endl;
			temp = _getch();
			break;
		}
		case 3: {
			menu_View_ScoreBoard_Of_Class(headStu);
			break;
		}
		case 4: {
			running = false;
			break;
		}
		}
	} while (running);
}

void studentListManage(_Student*& head) {
	int choose;
	int i = 0;
	bool running = true;
	int temp;
	system("cls");
	ShowCur(0);
	GotoXY(40, 5);
	string menu[4] = { "1. Add student","2. View list of classes","3. View list of courses", "4. Back" };
	do {
		while (true) {
			system("cls");
			for (int j = 0; j < 4; j++) {
				if (j == i) {
					textcolor(12);
					GotoXY(37, 9 + j);
					cout << " > " << menu[j] << " < " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(38, 9 + j);
					cout << " " << menu[j] << " " << endl;
				}
			}
			temp = _getch();
			if (temp == 's' || temp == 'S' || temp == 80) {
				i++;
				if (i == 4) i = 0;
			}
			if (temp == 'w' || temp == 'W' || temp == 72) {
				i--;
				if (i == -1) i = 3;
			}
			if (temp == 13 || temp == 32) break;
		}
		system("cls");
		switch (i)
		{
		case 0: {
			listStudents(head);
			cout << endl;
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 1: {
			view_Student_List_Menu(head);
			break;
		}
		case 2: {
			view_List_Of_Course_Menu(head);
			break;
		}
		case 3: {
			running = false;
			break;
		}
		}
	} while (running);
}

void staff_Menu(string username, _Student*& headStu) {
	int choose;
	int i = 0;
	bool running = true;
	int temp;
	system("cls");
	ShowCur(0);
	GotoXY(40, 5);
	string menu[6] = { "1. View info", "2. Create School year/Semester System","3. Course Registration Management System", "4. Students List Management" , "5. Student Scoreboard Management System", "6. Log out" };
	do {
		while (true) {
			system("cls");
			for (int j = 0; j < 6; j++) {
				if (j == i) {
					textcolor(12);
					GotoXY(37, 9 + j);
					cout << " > " << menu[j] << " < " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(38, 9 + j);
					cout << " " << menu[j] << " " << endl;
				}
			}
			temp = _getch();
			if (temp == 's' || temp == 'S' || temp == 80) {
				i++;
				if (i == 6) i = 0;
			}
			if (temp == 'w' || temp == 'W' || temp == 72) {
				i--;
				if (i == -1) i = 5;
			}
			if (temp == 13 || temp == 32) break;
		}
		system("cls");
		switch (i)
		{
		case 0: {
			showInfo_Staff(username, 38,9);
			cout << endl;
			GotoXY(37, 16);
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 1: {
			menu_Create_SY_Tmp();
			break;
		}
		case 2: {
			menu_Course_Staff();
			break;
		}
		case 3: {
			studentListManage(headStu);
			break;
		}
		case 4: {
			staff_Scoreboard_Management(headStu);
			break;
		}
		case 5: {
			running = false;
		}
		}
		
	} while (running);

}



void menu_Course_Staff() {
	int choose;
	int i = 0;
	int temp;
	system("cls");
	ShowCur(0);

	string menu[6] = {"1. Create Course Registration Session" ,"2. Create/Add Course", "3. View list of Course", "4. Update Course infomation", "5. Delete a course", "6. Exit"};
	do {
		while (true) {
			system("cls");
			for (int j = 0; j < 6; j++) {
				if (j == i) {
					textcolor(12);
					GotoXY(40, 10 + j);
					cout << " > " << menu[j] << " < " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(41, 10+ j);
					cout << " " << menu[j] << " " << endl;
				}
			}
			temp = _getch();
			if (temp == 's' || temp == 'S' || temp == 80) {
				i++;
				if (i == 6) i = 0;
			}
			if (temp == 'w' || temp == 'W' || temp == 72) {
				i--;
				if (i == -1) i = 5;
			}
			if (temp == 13 || temp == 32) break;
		}
		system("cls");
		switch (i)
		{
		case 0: {
			create_Course_Registration();
			break;
		}
		case 1: {
			createCourseList(dirCourse + "CoursesRegistration.txt");
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 2: {
			viewCourseList(dirCourse + "CoursesRegistration.txt");
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 3: {
			update_Course_Info();
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 4: {
			delete_Courses();
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		}
	} while (i != 5);
}

void student_Course_Menu(_Student* Node) {
	bool running = true;
	int choose;
	int temp;
	int i = 0;
	string menu[4] = { "1. Register for the Course","2. Remove the Course","3. Courses registration results","4. Exit" };
	do {
		while (true) {
			system("cls");
			for (int j = 0; j < 4; j++) {
				if (j == i) {
					textcolor(12);
					GotoXY(39, 5 + j);
					cout << " > " << menu[j] << " < " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(40, 5 + j);
					cout << " " << menu[j] << " " << endl;
				}
			}
			temp = _getch();
			if (temp == 's' || temp == 'S' || temp == 80) {
				i++;
				if (i == 4) i = 0;
			}
			if (temp == 'w' || temp == 'W' || temp == 72) {
				i--;
				if (i == -1) i = 3;
			}
			if (temp == 13 || temp == 32) break;
		}

		system("cls");

		switch (i) {
		case 0: {
			register_Course(Node);
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 1: {
			remove_Courses(Node);
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 2: {
			course_Registration_Result_Menu(Node);
			break;
		}
		default: {
			running = false;
			break;
		}
		}
	} while (running);
}

void student_Menu(_Student* Node) {
	if (Node == nullptr) {
		GotoXY(34, 12);
		cout << "Press any key to exit..." << endl;
		int sth = _getch();
		return;
	}
	int i = 1;
	int temp;
	system("cls");
	ShowCur(0);
	GotoXY(40, 5);
	string menu[6] = { "Choose your option","[1]. View Info", "[2]. Change password","[3]. Course Registration",  "[4]. View Scoreboard",  "[5]. Logout" };
	do {
		while (true) {
			system("cls");
			for (int j = 0; j < 6; j++) {
				if (j == i) {
					textcolor(12);
					GotoXY(39, 5 + j);
					cout << " > " << menu[j] << " < " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(40, 5 + j);
					cout << " " << menu[j] << " " << endl;
				}
			}
			temp = _getch();
			if (temp == 's' || temp == 'S' || temp == 80) {
				i++;
				if (i == 6) i = 1;
			}
			if (temp == 'w' || temp == 'W' || temp == 72) {
				i--;
				if (i == 0) i = 5;
			}
			if (temp == 13 || temp == 32) break;
		}
		system("cls");
		
		switch (i)
		{
		case 1: {
			showInfo_Student(Node);
			GotoXY(40, 12);
			cout << " enter to continue";
			temp = _getch();
			break;
		}

		case 2: {
			editPassword(Node); GotoXY(40, 12);
			cout << " enter to continue";
			temp = _getch();
			break;
		}

		case 3: {
			student_Course_Menu(Node);
			break;
		}

		case 4: {
			menu_ScoreBoard_Student(Node);
			break;
		}
		}
	} while (i != 5);
}

void log_In_System(int x, int y) {
	_Student* head = nullptr;
	loadStu_Save(head);
	int n;
	cout << "Load success!" << endl;
	int choose;
	string username;

	int running = true;
	do {
		
		choose = MainMenu(x, y);
		
		switch (choose)
		{
		
		case 1: {

			n = 1;
			staff_Login(username, n);
			if (n == 0) break;
			staff_Menu(username, head);
			break;
		}

		case 2: {
			n = 1;
			_Student* Node = logInSystem_Student(head,n);
			if (n == 0) break;
			student_Menu(Node);
			break;
		}
		
		default:
			running = false;
		}
	} while (running);
	deallocateNode(head);
}

