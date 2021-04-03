#ifndef FUNCTION_H_
#define FUNCTION_H_
#include<string>
#include<iostream> 

using namespace std;

struct Date {
	int day, month, year;
};


//struct cho nam hoc vd: nam 2019, 2020
struct _Schoolyear {
	_Semester data;
	_Schoolyear* pNext, * pPrecious; //di tiep hoac lui lai 1 nam
};


//hoc ki
struct _Semester {        // 1 2 3; bieu dien cho ki
	Date Start_Day;
	Date End_Day;
	_Year data;
	_Semester *pNext, *pPrevious;

};


// hoc sinh nam 1 nam 2 nam 3 nam 4
struct _Year{
	_Course Course_Name;
	_Year* pNext,* pPrevious;
};

//dung cho ca staff va sv
struct _Course {
	bool regist;// 0 khong dang ki, 1// da dang ki -> staff
	wstring Course_ID;    // staff +sv
	wstring Teacher_Name;  //staff+sv
	int Credits;   //staff+sv
	_session Time_of_Session;   //staff+sv

	int Max_Student_in_Class;   //staff 
	Teacher_ScoreBoard NameCourse_ScoreBoard; // cai nay bao gom student_scoreborad // staff
	_Course* pNext, * pPrevious; //qua lai cac mon khac nhau
};


//thoi gian hoc
struct _session {
	string Day; //Mon Tue Wedn ...
	string hour;
	_session* pNext, * pPrevious;
};

struct GPA {
	double GPA_semester;
	double GPA_overall;
};

struct Student {
	wstring FirstName;
	wstring LastName;
	unsigned int Student_ID;
	string Gender;
	unsigned int social_ID;
	Class Name_Of_Class;
	Date dob;
	_Course* Name_Of_Course; //truy cap vo teacher-scoreboard -> studentscoreboard de lay diem thanh phan
	//dung cho class:  lay bang diem cua lop, lay diem cuoi ki cua tat ca cac course trong semester
	GPA gpa; // cai nay thay doi theo hoc ki luon nen khong can thiet lap nam hoc, hoc ki, hoc sinh nam may;
};

struct Class {
	int num; //so thu tu sv trong lop
	_Student* pNext, *pPrevious;
};
//tui lam ho cai nay de lo thay muon co nhieu lop :)) co the khong sai
struct _Class {
	Class data;
	_Class* pNext, * pPrevious;
};
struct _Student {
	Student data;
	_Student* pNext, * pPrevious;
};
struct student_Scoreboard {
	double total_Mark;
	double final_Mark;
	double midterm_Mark;
	Other_Mark other_Mark;
	double gpa;
	string grade; // C->A+
};

struct Other_Mark {
	double data;
	Other_Mark* pNext, * pPrevious;
};
struct _Student_Scoreboard {
	student_Scoreboard student;
	_Student_Scoreboard* pNext, * pPrevious;
};

struct Teacher_ScoreBoard {
	int number;
	Student student;
	_Student_Scoreboard* student_score;
};

struct account {
	string id;
	string password;
};
#endif // !FUNCTION_H_