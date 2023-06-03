/* 
------------------------------ READ ME -----------------------------------------

This code requires <sqlite3.h> library. It can be installed by the command: 
$ sudo apt install libsqlite3-dev

This code can be compiled as follows:
$ g++ miniaims.cpp -l sqlite3 -o miniaims.out

When starting without a database a "Root Admin" is automatically generated:
userid: "admin001"
password: "default"

In the sample database provided, the password is kept the same. 

------------------------ SUBMISSION DETAILS -------------------------------------

Assignment: Mini AIMS
Name: Rajiv Shailesh Chitale
Roll No: CS21BTECH11051

------------------------ OVERVIEW OF CLASSES ------------------------------------
This file is a combination of the following classes:

GradeSheet - manages a list of registered students and their grades. It has methods to load grades, store and delete entries from a database.
SheetEntry - contains data in an entry in the gradesheet. GradeSheet is its friend.
Course - contains details of a course. It has methods to load, store, update and delete data from a database

UserData - contains the details of a user. It has methods to load, store, update and delete data from a database
AdminData, FacultyData, StudentData are derived classes of UserData. 

CommonPowers - contains methods to carry out actions common to different types of users.
AdminPowers, FacultyPowers and StudentPowers are its derived classes. Their methods carry out actions specific to user type.

UserInterface - implements a text based UI. It has methods for login and menus depending on the type of user.

------------------------------------ ABOUT SAMPLE DATABASE -----------------------
There are 20 students, 5 faculty and 1 admin.

some accounts are:
userid: "admin001" 	password: "default"
userid: "cse002f" 	password: "aiaiaiai"
userid: "phy001f" 	password: "appleaday"

userid: "phy001" 	password: "firstpass"
userid: "phy002"	password: "secondpass"
etc
userid: "cse001" 	password: "passfirst"
userid: "cse002" 	password: "passsecond"
etc
*/

#include <iostream>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#define dbname "database.db"
#define BUFFLEN 1000
#define MIN_PASS_LEN 6
#define GAP " : "

#define DOWN 1 	//course which is down is not available for registration
#define FLOATED 2  //floated course is available for registration
#define GRADED 3 //course which is completed and graded
#define DONE 0
#define FAIL 1

using namespace std;

//waits till user presses enter
void wait()
{
	cout << "Press enter to return to menu.\n";
	char temp = getchar();
	while(temp != '\n') {temp = getchar();}
	return;
}

//prints whether the task was completed or not
int message(int outcome)
{
	if(outcome == DONE) { cout << "Task completed.\n"; }
	else {cout << "Task interrupted.\n"; }
	return outcome;
}

//converts integer status to corresponding string
string status_to_string(int status)
{
	if(status==DOWN) {return "Down";}
	else if(status==FLOATED) {return "Floated";}
	else if(status==GRADED) {return "Graded";}
	else {return "error";}
}

//can be used for implementing hash function
string hasher(string inpstr)
{
	return inpstr;
}



//----------------GRADESHEET AND COURSE-----------------


//attributes stored in the row of a gradesheet
class SheetEntry
{
	public:
	SheetEntry(string userid, string grade)
	{
		this->userid = userid;
		this->grade = grade;	
	}
	private:
	string userid;
	string grade;
	friend class GradeSheet;
};

//Contains useful functions for managing gradesheet: get_grade, store_entry, update_entry, delete_entry, delete_table
class GradeSheet
{
	private:
	string courseid;
	
	public:
	GradeSheet(string courseid)
	{
		this->courseid = courseid;
	}
	
	//1.takes a string userid corresponding to a student. Returns their grade
	string get_grade(string userid)
	{
		string grade;
		sqlite3* db;
		sqlite3_open(dbname, &db);
		sqlite3_stmt* stmt;		
		
		char sqlcommand1[1000];
		snprintf(sqlcommand1, BUFFLEN, "SELECT * FROM %s WHERE(userid='%s')", courseid.c_str(), userid.c_str() );	

		int outcome1 = sqlite3_prepare_v2(db, sqlcommand1, BUFFLEN, &stmt, NULL);
		if( (sqlite3_step(stmt) == SQLITE_ROW)  && (outcome1 == SQLITE_OK) )
		{
			grade = (const char*) sqlite3_column_text(stmt, 1); //typecast from unsigned to signed const char. Then create c++ string from it
		}
		else {grade = "error";}
		sqlite3_finalize(stmt);	
		sqlite3_close(db);
		return grade;
	}
	
	//overloaded. "SheetEntry" objects can be useful when dealing with many entries.
	string get_grade(SheetEntry the_entry)
	{
		the_entry.grade = get_grade(the_entry.userid); //also stores grade in the Entry object
		return the_entry.grade;
	}
	
	//2.takes strings userid and grade corresponding to a student. Stores them in the database. Cannot overwrite existing entry
	int store_entry(string userid, string grade)
	{
		if(userid == "") {return FAIL;}
		sqlite3* db;
		sqlite3_open(dbname, &db);
		char* errmsg;
		
		char sqlcommand1[BUFFLEN];
		snprintf(sqlcommand1, BUFFLEN, 
				"CREATE TABLE IF NOT EXISTS %s (userid CHAR(20) PRIMARY KEY, grade CHAR(5) );", courseid.c_str() );
				
		char sqlcommand2[BUFFLEN];
		snprintf(sqlcommand2, BUFFLEN, 
				"INSERT INTO %s VALUES('%s', '%s');",  courseid.c_str(), userid.c_str(),  grade.c_str() );		
		
		int outcome1 = sqlite3_exec(db, sqlcommand1, NULL, 0, &errmsg); //make table if not existing
		int outcome2 = sqlite3_exec(db, sqlcommand2, NULL, 0, &errmsg);	//makes row if not existing
		
		sqlite3_close(db)	;
		if(outcome1 == SQLITE_OK && outcome2 == SQLITE_OK ) {return DONE;}
		else {return FAIL;}	
	}	
	
	//overloaded
	int store_entry(SheetEntry the_entry)
	{
		return store_entry(the_entry.userid, the_entry.grade);
	}
	
	//3.takes strings userid and a new grade corresponding to a student. Updates the grade in the database
	int update_entry(string userid, string grade)
	{
		if(userid == "") {return FAIL;}
		sqlite3* db;
		sqlite3_open(dbname, &db);
		char* errmsg;

		char sqlcommand3[BUFFLEN];
		snprintf(sqlcommand3, BUFFLEN, 
				"UPDATE %s SET grade ='%s' WHERE(userid='%s');", 
				courseid.c_str(), grade.c_str(), userid.c_str() );			
		
		int outcome3 = sqlite3_exec(db, sqlcommand3, NULL, 0, &errmsg);	//updates data in a row	
		sqlite3_close(db)	;
		if(outcome3 == SQLITE_OK ) {return DONE;}
		else {return FAIL;}		
	}
	
	//overloaded
	int update_entry(SheetEntry the_entry)
	{
		return update_entry(the_entry.userid, the_entry.grade);
	}
	
	//4. takes a string userid of a student. Deletes the corresponding entry from the database
	int delete_entry(string userid)
	{
		if(userid == "") {return FAIL;}
		sqlite3* db;
		sqlite3_open(dbname, &db);
		char* errmsg;
		
		char sqlcommand1[BUFFLEN];
		snprintf(sqlcommand1, BUFFLEN, 
				"DELETE FROM %s WHERE(userid = '%s');",  courseid.c_str(), userid.c_str() );				
		
		int outcome1 = sqlite3_exec(db, sqlcommand1, NULL, 0, &errmsg); 
		sqlite3_close(db);
		
		if(outcome1 == SQLITE_OK) {return DONE;}
		else {return FAIL;}
		
	}
	
	//overloaded
	int delete_entry(SheetEntry the_entry)
	{
		return delete_entry(the_entry.userid);
	}
	
	//5. delete the entire gradesheet from the database
	int delete_table()
	{
		sqlite3* db;
		sqlite3_open(dbname, &db);
		char* errmsg;
		
		char sqlcommand1[BUFFLEN];
		snprintf(sqlcommand1, BUFFLEN, "DROP TABLE %s;",  courseid.c_str() );				
		
		int outcome1 = sqlite3_exec(db, sqlcommand1, NULL, 0, &errmsg); 
		sqlite3_close(db);
		
		if(outcome1 == SQLITE_OK) {return DONE;}
		else {return FAIL;}		
	}
	
};

//contains details of the course, but not the student list or grades. 
//Contains methods to load, store, update, delete this data to/from the database.
class Course
{
	private:
	string courseid;
	string title;
	string incharge;	
	int status;
	int headcount;
	
	public:
	Course(string courseid, string title, string incharge)
	{
		this->courseid = courseid;
		this->title = title;
		this->incharge = incharge;
		this->status = DOWN; //default status down
		this->headcount = 0;
	}
	Course(string courseid)
	{
		this->courseid = courseid;
	}
	
	//1. loads data of the course from the database to the object
	int load_data()
	{	
		if(courseid == "") {return FAIL;}
		int retvalue= DONE;
		sqlite3* db;
		sqlite3_open(dbname, &db);
		sqlite3_stmt* stmt;		
		
		char sqlcommand1[1000];
		snprintf(sqlcommand1, BUFFLEN, "SELECT * FROM courses WHERE(courseid='%s')", courseid.c_str() );	

		int outcome1 = sqlite3_prepare_v2(db, sqlcommand1, BUFFLEN, &stmt, NULL);
		if( (sqlite3_step(stmt) == SQLITE_ROW)  && (outcome1 == SQLITE_OK) )
		{
			title = (const char*) sqlite3_column_text(stmt, 1); 
			incharge = (const char*) sqlite3_column_text(stmt, 2);
			status = sqlite3_column_int(stmt, 3);
			headcount = sqlite3_column_int(stmt, 4);	
		}
		else {retvalue= FAIL;}
		sqlite3_finalize(stmt);	
		sqlite3_close(db);
		return retvalue;
	}
	
	//2. stores data of the course from the object to the database. Note: this does not update data if it already exists.
	int store_data()
	{
		if( (courseid == "") || (title == "") || (incharge == "") ) {return FAIL;}
		sqlite3* db;
		sqlite3_open(dbname, &db);
		char* errmsg;
		
		char sqlcommand1[BUFFLEN] = "CREATE TABLE IF NOT EXISTS "
									"courses (courseid CHAR(20) PRIMARY KEY, title CHAR(50), incharge CHAR(20), status INT, headcount INT );" ;
		char sqlcommand2[BUFFLEN];
		snprintf(sqlcommand2, BUFFLEN, "INSERT INTO courses VALUES('%s', '%s', '%s', %d, %d);", 
				 courseid.c_str(), title.c_str(), incharge.c_str(), status, headcount );
				 
		int outcome1 = sqlite3_exec(db, sqlcommand1, NULL, 0, &errmsg); //make table if not existing
		int outcome2 = sqlite3_exec(db, sqlcommand2, NULL, 0, &errmsg);	//makes row if it doesn't exist
		sqlite3_close(db)	;	
		
		if(outcome2 == SQLITE_OK ) {return DONE;} //
		else {return FAIL;}	
	}
	
	//3. changes existing data in the database to that present in the object	
	int update_data()
	{
		if( (courseid == "") || (title == "") || (incharge == "") ) {return FAIL;}
		sqlite3* db;
		sqlite3_open(dbname, &db);
		char* errmsg;

		char sqlcommand3[BUFFLEN];
		snprintf(sqlcommand3, BUFFLEN, 
				"UPDATE courses SET title='%s', incharge='%s', status='%d', headcount='%d' WHERE(courseid='%s');", 
				title.c_str(), incharge.c_str(), status, headcount, courseid.c_str() );
		
		int outcome3 = sqlite3_exec(db, sqlcommand3, NULL, 0, &errmsg);	//update data in row
		sqlite3_close(db)	;		
		if(outcome3 == SQLITE_OK ) {return DONE;} 
		else {return FAIL;}			
	}
	
	//4. removes the data of the course from the database
	int delete_data()
	{
		if(courseid == "") {return FAIL;}
		sqlite3* db;
		sqlite3_open(dbname, &db);
		char* errmsg;
		
		char sqlcommand1[BUFFLEN];
		snprintf(sqlcommand1, BUFFLEN, 
				"DELETE FROM courses WHERE(courseid = '%s');", courseid.c_str() );
		int outcome1 = sqlite3_exec(db, sqlcommand1, NULL, 0, &errmsg); 
		sqlite3_close(db);	
		
		if(outcome1 == SQLITE_OK) {return DONE;}
		else {return FAIL;}
	}
	
	//5. basic functions for get, set
	
	string get_courseid() {return this->courseid;}
	string get_title() {return this->title;}
	string get_incharge() {return this->incharge;}
	void set_incharge(string new_incharge) {this->incharge = new_incharge;}
	int get_status() {return this->status;}	
	void set_status(int new_status) {this->status = new_status;}
	int get_headcount() {return this->headcount;}
	
	//6. changes to headcount
	void increment_headcount() {headcount++;}
	void decrement_headcount() {headcount--;}
	
};





//-------------------------USERDATA-----------------------

//contains basic information about a user.
//Contains methods to load, store, update, delete this data to/from the database.
class UserData
{	
	protected:
	string userid;
	string name;
	string hashed_password;
	string type; //admin, faculty, student. 
	
	public:
	UserData()
	{
		this->type = "unknown";
	}	
	//creating a user without knowing type, for purpose of searching and loading 
	UserData(string userid)
	{
		this->userid = userid;
		this->type = "unknown";
	}		

	//1. loads data from the database into an object of this class
	int load_data()	//check table based on type.
	{
		if(userid == "") {return FAIL;}
	
		//when type is not known, search all possible tables
		if(type == "unknown")
		{
			type = "admin";
			if (load_data() == DONE) return DONE;
			type = "faculty";
			if (load_data() == DONE) return DONE;
			type = "student";
			if (load_data() == DONE) return DONE;
			return FAIL;
		}
	
		int retvalue= DONE;
		sqlite3* db;
		sqlite3_open(dbname, &db);
		sqlite3_stmt* stmt;		
		
		char sqlcommand1[1000];
		snprintf(sqlcommand1, BUFFLEN, "SELECT * FROM %s WHERE(userid='%s')", type.c_str(), userid.c_str() );	

		int outcome1 = sqlite3_prepare_v2(db, sqlcommand1, BUFFLEN, &stmt, NULL);
		if( (sqlite3_step(stmt) == SQLITE_ROW)  && (outcome1 == SQLITE_OK) )
		{
			name = (const char*) sqlite3_column_text(stmt, 1);
			hashed_password = (const char*) sqlite3_column_text(stmt, 2);
		}
		else {retvalue= FAIL;}
		sqlite3_finalize(stmt);	
		sqlite3_close(db);
		return retvalue;		
	}
	
	//2. stores data from the object into the database. Note: this does not update data if it already exists.
	int store_data() 	//if matching id rewrite, otherwise write on new line
	{
		if( (userid == "") || (name == "") || (hashed_password == "") ) {return FAIL;}
		
		sqlite3* db;
		sqlite3_open(dbname, &db);
		char* errmsg;
		
		char sqlcommand1[BUFFLEN];
		snprintf(sqlcommand1, BUFFLEN, 
		"CREATE TABLE IF NOT EXISTS %s (userid CHAR(20) PRIMARY KEY, name CHAR(50), hashed_password CHAR(50), type CHAR(20) ) ;",
		type.c_str() );
		//name of table is based on type of user
		
		char sqlcommand2[BUFFLEN];
		snprintf(sqlcommand2, BUFFLEN, 
				"INSERT INTO %s VALUES('%s', '%s', '%s', '%s');", type.c_str(), userid.c_str(), name.c_str(), hashed_password.c_str(), type.c_str() );

		int outcome1 = sqlite3_exec(db, sqlcommand1, NULL, 0, &errmsg); //make table if not existing
		int outcome2 = sqlite3_exec(db, sqlcommand2, NULL, 0, &errmsg);	//will make a row if it doesn't exist. In that case command3 is unnecesary 
		sqlite3_close(db);
		
		if(outcome2 == SQLITE_OK ) {return DONE;}
		else {return FAIL;}	
	}
	
	//3. changes existing data in the database to that present in the object
	int update_data()
	{
		if( (userid == "") || (name == "") || (hashed_password == "") ) {return FAIL;}
		
		sqlite3* db;
		sqlite3_open(dbname, &db);
		char* errmsg;
		
		char sqlcommand3[BUFFLEN];
		snprintf(sqlcommand3, BUFFLEN, 
				"UPDATE %s SET name='%s', hashed_password='%s', type='%s' WHERE(userid='%s') ;", 
				type.c_str(), name.c_str(), hashed_password.c_str(), type.c_str(), userid.c_str() );
		
		int outcome3 = sqlite3_exec(db, sqlcommand3, NULL, 0, &errmsg);	//update data in a row
		sqlite3_close(db);
		if(outcome3 == SQLITE_OK ) {return DONE;}
		else {return FAIL;}		
	}
	
	//4. deletes data of a user from the database
	int delete_data()
	{
		if(userid == "") {return FAIL;}
		sqlite3* db;
		sqlite3_open(dbname, &db);
		char* errmsg;
		
		char sqlcommand1[BUFFLEN];
		snprintf(sqlcommand1, BUFFLEN, 
				"DELETE FROM %s WHERE(userid= '%s');", type.c_str(), userid.c_str());
		int outcome1 = sqlite3_exec(db, sqlcommand1, NULL, 0, &errmsg); 
		sqlite3_close(db);
		
		if(outcome1 == SQLITE_OK) {return DONE;}
		else {return FAIL;}	
	}
	
	//5. to set basic attributes present in all users
	void set_basic_data(string userid, string name, string hashed_password)
	{
		this->userid = userid;
		this->name = name;
		this->hashed_password = hashed_password;
	}
	
	//6. more functions for get and set
	void set_hashed_password(string newstr) {this->hashed_password = newstr; return;}
	string get_userid() {return this->userid; }
	string get_name() {return this->name; }
	string get_hashed_password() {return this->hashed_password; }
	string get_type() {return this->type; }

	//7. changes password of a user to string newpass after verifying string oldpass
	int reset_password(string oldpass, string newpass)
	{
		
		if(hasher(oldpass) != get_hashed_password() )			//authenticate again to prevent mischief 
			{cout << "Error: old password was incorrect\n"; return FAIL;}
		else if (newpass.length() < MIN_PASS_LEN)
			{cout << "Error: new password is too short (needs at least) " << MIN_PASS_LEN << " characters)\n"; return FAIL;}	
		else
		{
			set_hashed_password( hasher(newpass) );
			return this->update_data();
		}
	}	
	
};


class AdminData : public UserData
{
	public:
	AdminData()
	{
		this->type = "admin";
	}
	//entry exists, only needs userid to locate
	AdminData(string userid)
	{
		this->userid = userid;
		this->type = "admin";
	}
	//for complete initialization
	AdminData(string userid, string name, string hashed_password)
	{
		set_basic_data(userid, name, hashed_password);
		this->type = "admin";
	}
};

class FacultyData : public UserData
{
	public:
	FacultyData()
	{
		this->type = "faculty";
	}
	//entry exists, only needs userid to locate
	FacultyData(string userid)
	{	
		this->userid = userid;
		this->type = "faculty";
	}
	//for complete initialization
	FacultyData(string userid, string name, string hashed_password)
	{
		set_basic_data(userid, name, hashed_password);
		this->type = "faculty";
	}

};

class StudentData : public UserData
{
	public:
	StudentData()
	{
		this->type = "faculty";
	}
	//entry exists, only needs userid to locate
	StudentData(string userid)
	{
		this->userid = userid;
		this->type = "student";
	}
	//for complete initialization
	StudentData(string userid, string name, string hashed_password)
	{
		set_basic_data(userid, name, hashed_password);
		this->type = "student";
	}
	
};




//--------------------POWERS-------------------

//Can be used for common powers independent of usertype
class CommonPowers
{
	public:
	//1.Displays all courses and their details
	int view_courses()
	{
		string courseid, title, incharge;
		int status, headcount;
		int retvalue= DONE;
		sqlite3* db;
		sqlite3_open(dbname, &db);
		sqlite3_stmt* stmt;		
		
		char sqlcommand1[1000];
		snprintf(sqlcommand1, BUFFLEN, "SELECT * FROM courses");	

		int outcome1 = sqlite3_prepare_v2(db, sqlcommand1, BUFFLEN, &stmt, NULL);
		if(outcome1 != SQLITE_OK) {retvalue = FAIL;}
		else
		{
			cout << "COURSEID : TITLE : INCHARGE : STATUS : HEADCOUNT\n";
			while ( sqlite3_step(stmt) == SQLITE_ROW )
			{
				courseid = (const char*) sqlite3_column_text(stmt, 0); 
				title = (const char*) sqlite3_column_text(stmt, 1); 
				incharge = (const char*) sqlite3_column_text(stmt, 2);
				status = sqlite3_column_int(stmt, 3);
				headcount = sqlite3_column_int(stmt, 4);
				
				FacultyData the_faculty(incharge);
				the_faculty.load_data();	
				
				cout<< courseid << GAP << title << GAP << the_faculty.get_name() << GAP << status_to_string(status) << GAP << headcount << endl;
			}
		}
		sqlite3_finalize(stmt);	
		sqlite3_close(db);
		return retvalue;
	}
	
	//these protected functions are common to some but not all children. 
	//they will be called by public functions of only required children
	protected:
	//2. takes in string courseid. Displays the list of students of the corresponding course (and grades if available) 
	int view_registered_students(string courseid)
	{
		Course the_course(courseid);
		if(the_course.load_data() == FAIL)
			{cout<< "Error: course does not exist\n"; return FAIL;}
		
		string userid, grade, name;
		sqlite3* db;
		sqlite3_open(dbname, &db);
		sqlite3_stmt* stmt;		
		
		char sqlcommand1[1000];
		snprintf(sqlcommand1, BUFFLEN, "SELECT * FROM %s", courseid.c_str());	
		int outcome1 = sqlite3_prepare_v2(db, sqlcommand1, BUFFLEN, &stmt, NULL);
		if (outcome1 != SQLITE_OK) { sqlite3_close(db); return FAIL; }
		
		system("clear"); 
		if( the_course.get_status() == GRADED ) { cout << "USERID : GRADE : NAME\n"; } //Will print grades also if the course is graded
		else {cout << "USERID : NAME\n"; }
		
		while( (sqlite3_step(stmt) == SQLITE_ROW) )
		{
			grade = (const char*) sqlite3_column_text(stmt, 1); //typecast from unsigned to signed const char. Then create c++ string from it
			userid = (const char*) sqlite3_column_text(stmt, 0); 	
			StudentData the_student(userid);
			the_student.load_data();
			name = the_student.get_name();		//retreive name of a student
		
			if( the_course.get_status() == GRADED ) { cout<< userid << GAP << grade << GAP << name <<endl;}
			else {cout<< userid <<GAP << name <<endl;}				
		}
		sqlite3_finalize(stmt);	
		sqlite3_close(db);
		return DONE;
	}	


};

class AdminPowers : public CommonPowers
{
	public:
	//constructor to initialize details of the user who is running commands
	AdminPowers(string userid)
	{
		AdminData details(userid);
		details.load_data();
		this->self = details;
	}
	
	//1. takes in details of a student and stores them in the database
	int add_student(string userid, string name, string password)
	{
		if (password.length() < MIN_PASS_LEN)
			{cout << "Error: new password is too short (needs at least) " << MIN_PASS_LEN << " characters)\n"; return FAIL;}		
		string hashed_password = hasher(password);
		StudentData new_student(userid, name, hashed_password);
		if(new_student.load_data() == DONE) {cout << "Error: User ID is taken.\n"; return FAIL;}
		return new_student.store_data();
	}
	
	//2.takes in details of a faculty and stores them in the database
	int add_faculty(string userid, string name, string password)
	{
		if (password.length() < MIN_PASS_LEN)
			{cout << "Error: new password is too short (needs at least) " << MIN_PASS_LEN << " characters)\n"; return FAIL;}
		string hashed_password = hasher(password);
		FacultyData new_faculty(userid, name, hashed_password);
		if(new_faculty.load_data() == DONE) {cout << "Error: User ID is taken.\n"; return FAIL;}
		return new_faculty.store_data();
	}
	
	//3. takes in details of a course and stores them in the database
	int add_course(string courseid, string title, string incharge)
	{
		FacultyData the_faculty(incharge);
		if(the_faculty.load_data() == FAIL) {cout << "Error: Incharge does not exist.\n"; return FAIL;} 
		Course new_course(courseid, title, incharge);
		return new_course.store_data();
	}
	
	//4. stores a userid of a student in the list of students of a course
	int add_student_to_course(string userid, string courseid)
	{
		StudentData the_student(userid);
		if(the_student.load_data() == FAIL) {cout << "Error: Student does not exist.\n" ; return FAIL;}
		
		Course the_course(courseid);
		if(the_course.load_data() == FAIL) {cout << "Error: Course does not exist.\n" ; return FAIL;}
		
		GradeSheet the_sheet(courseid);
		if(the_sheet.get_grade(userid) != "error") {cout<<"Note: Student is already registered to this course.\n"; return DONE;}  
		if( the_sheet.store_entry(userid, "NA") == DONE)
		{
			the_course.increment_headcount();
			the_course.update_data();
			return DONE;
		}
		else {return FAIL;}
	}
	
	//5. takes userid of a student and deletes the details of the student from the database
	int del_student(string userid)
	{
		StudentData the_student(userid);
		if(the_student.load_data() == FAIL) {cout << "Note: Student does not exist.\n" ; return FAIL;}
		return the_student.delete_data();
	}
	
	//6. takes userid of a faculty and deletes the  details of the faculty from the database
	int del_faculty(string userid)
	{
		FacultyData the_faculty(userid);
		if(the_faculty.load_data() == FAIL) {cout << "Note: Faculty does not exist.\n" ; return FAIL;}
		return the_faculty.delete_data();
	}
	
	//7. takes courseid and removes its details from the database
	int del_course(string courseid)
	{
		GradeSheet the_sheet(courseid);
		Course the_course(courseid);
		if (the_course.load_data() == FAIL)  {cout << "Note: Course does not exist.\n" ; return FAIL;}
		
		the_sheet.delete_table();
		return the_course.delete_data();
	}
	
	//8. removes a student from the list of students of a course
	int del_student_from_course(string userid, string courseid)
	{	
		StudentData the_student(userid);
		if(the_student.load_data() == FAIL) {cout << "Note: Student does not exist.\n" ; return FAIL;}
		
		Course the_course(courseid);
		if(the_course.load_data() == FAIL) {cout << "Note: Course does not exist.\n" ; return FAIL;}
		
		GradeSheet the_sheet(courseid);
		if(the_sheet.get_grade(userid) == "error") {cout << "Note: Student is not registered to the course.\n" ; return FAIL;} 
	
		if (the_sheet.delete_entry(userid) == DONE)
		{
			the_course.decrement_headcount();
			the_course.update_data();	
			return DONE;
		}
		else {return FAIL;}
	}

	//9. 
	int reset_password(string oldpass, string newpass)
	{
		return self.reset_password(oldpass, newpass);
	}
	
	//10. takes in auth_password to verifhy identity of an admin. Takes in details of a new admin and stores them in the database.
	int add_admin(string auth_password, string userid, string name, string password)
	{		
		if( hasher(auth_password) != self.get_hashed_password() ) 	//avoids mischievous people from creating admin for themselves when admin is afk
			{cout << "Error: authentication failed.\n" ;return FAIL;} 
		else if (password.length() < MIN_PASS_LEN)
			{cout << "Error: new password is too short (needs at least) " << MIN_PASS_LEN << " characters)\n"; return FAIL;}
		else
		{
			string hashed_password = hasher(password);
			AdminData new_admin(userid, name, hashed_password);
			return new_admin.store_data();
		}
	}
	
	
	//11. sets the userid of the incharge of a course to new_incharge
	int change_course_incharge(string courseid, string new_incharge)
	{
		Course the_course(courseid);
		FacultyData the_faculty(new_incharge);
		if(the_course.load_data() == FAIL || the_faculty.load_data() == FAIL) {return FAIL;}  //course or incharge do not exist
		the_course.set_incharge(new_incharge);
		return the_course.update_data();
	}
	
	
	//13. displays students in a course with given courseid
	int view_students(string courseid)
	{
		return view_registered_students(courseid);		
	}
	
	//14. displays users of given type
	void view_users(string type)
	{
		string userid, name;
		sqlite3* db;
		sqlite3_open(dbname, &db);
		sqlite3_stmt* stmt;		
		
		char sqlcommand1[1000];
		snprintf(sqlcommand1, BUFFLEN, "SELECT * FROM %s", type.c_str() );	

		int outcome1 = sqlite3_prepare_v2(db, sqlcommand1, BUFFLEN, &stmt, NULL);
		if(outcome1 != SQLITE_OK) {return;}
		cout << "UserID and name of each " << type << endl;
		while( sqlite3_step(stmt) == SQLITE_ROW )
		{
			userid = (const char*) sqlite3_column_text(stmt, 0);
			name = (const char*) sqlite3_column_text(stmt, 1);
			cout<< userid << GAP << name << endl;
		}
		cout << endl;
		sqlite3_finalize(stmt);	
		sqlite3_close(db);
		return;
	}
	
	//14b. overloaded, displays users of all types
	void view_users()
	{
		view_users("admin");
		view_users("faculty");
		view_users("student");
	}
	
	private:
	AdminData self; //contains data of the current user
};


class FacultyPowers : public CommonPowers
{
	public:
	//constructor to initialize details of the user who is running commands
	FacultyPowers(string userid)
	{
		FacultyData details(userid);
		details.load_data();
		this->self = details;
	}
	

	//1. inputs grades for each student in a course with given courseid. Stores them in the database in an atomic operation.
	int submit_grades(string courseid)
	{	
		Course the_course(courseid);
		the_course.load_data();
		if( the_course.get_incharge() != self.get_userid() ) 
			{cout << "Error: You are not incharge of this course.\n"; return FAIL;}
		if( the_course.get_status() == GRADED )
			{cout << "Error: This course has already been graded.\n"; return FAIL;}
		
		GradeSheet the_sheet(courseid);
		string userid, grade; 
		int retvalue= DONE;	
		cout<< "Enter grade after each student ID. Enter '.' to quit.\n(incomplete grading will not be saved)\n";	
		
		vector<SheetEntry> entry_vector; //stores all entries temporarily so storing grades to database is atomic
		
		sqlite3* db;
		sqlite3_open(dbname, &db);
		sqlite3_stmt* stmt;			
		char sqlcommand1[1000];
		snprintf(sqlcommand1, BUFFLEN, "SELECT * FROM %s WHERE(grade='NA')", courseid.c_str() );	//finds grades which are Not Assigned (NA)	
		int outcome1 = sqlite3_prepare_v2(db, sqlcommand1, BUFFLEN, &stmt, NULL);

		if(outcome1 != SQLITE_OK) {retvalue = FAIL;}
		else 
		{	
			while(sqlite3_step(stmt) == SQLITE_ROW) 
			{
				userid = (const char*) sqlite3_column_text(stmt, 0); //convert to signed char * then assign to c++ string

				StudentData current_student(userid);
				current_student.load_data();						//loading student name
				cout << userid <<GAP << current_student.get_name() << GAP;
				cin >> grade; //STORE IN VECTOR/LIST
				cin.ignore();
				entry_vector.push_back( SheetEntry(userid, grade) );
				if(grade==".") {cout<<"Aborted grade submission"; retvalue = FAIL;}
			}
		}
		
		if(retvalue == DONE)
		{
			for(int i=0; i < entry_vector.size(); i++)
				{ the_sheet.update_entry(entry_vector[i]); }			
			the_course.set_status(GRADED); // course status as graded
			the_course.update_data();
		}
		
		sqlite3_finalize(stmt);	
		sqlite3_close(db);		
		return retvalue;
	}
	
	//2. changes status of a course to int new_status 
	int set_course_status(string courseid, int new_status)
	{
		if(new_status != DOWN && new_status != FLOATED) {cout << "Error: Invalid status.\n"; return FAIL;}
		Course the_course(courseid);
		the_course.load_data();
		if ( the_course.get_status() == GRADED ) 
			{cout << "Error: Course has already been graded.\nNote: To start a new batch, delete existing course first.\n"; return FAIL;}
		
		if( the_course.get_incharge() == self.get_userid() )
		{
			the_course.set_status(new_status);
			the_course.update_data();
			return DONE;
		}
		else {cout << "You are not incharge of this course.\n"; return FAIL;}
	}
	
	//3. displays the students in a course with given courseid, if the current faculty is the incharge.
	int view_students(string courseid)
	{
		Course the_course(courseid);
		the_course.load_data();
		if( the_course.get_incharge() != self.get_userid() )
			{cout << "You are not incharge of this course.\n"; return FAIL;}
		else return view_registered_students(courseid);		
	}
	
	//4. 
	int reset_password(string oldpass, string newpass)
	{
		return self.reset_password(oldpass, newpass);
	}
	private:
	FacultyData self;
};


class StudentPowers : public CommonPowers
{	
	//constructor to initialize details of the user who is running commands
	public:
	StudentPowers(string userid)
	{
		StudentData details(userid);
		details.load_data();
		this->self = details;
	}
	//--------checks float status and if student is in the list -------//
	//1. adds a student to the list of students in a course with given courseid
	int register_course(string courseid)
	{
		Course the_course(courseid);
		if(	the_course.load_data() == FAIL) {cout<<"Error: this course does not exist.\n" ; return FAIL;}
		if(the_course.get_status() == DOWN) {cout<<"Error: Course is not floated at the moment.\n" ; return FAIL;} 
		else if(the_course.get_status() == GRADED) {cout<<"Error: Course has already been graded.\n" ; return FAIL;} 
		
		GradeSheet the_sheet(courseid);
		if(the_sheet.get_grade( self.get_userid() ) != "error") {cout<<"Note: You are already registered to this course.\n"; return DONE;}   
		if(the_sheet.store_entry(self.get_userid(), "NA") == DONE) 
		{
			the_course.increment_headcount();
			the_course.update_data();
			return DONE;
		}
		else {return FAIL;}
	}
	
	//2. removes a student to the list of students in a course with given courseid
	int deregister_course(string courseid)
	{
		Course the_course(courseid);
		if(	the_course.load_data() == FAIL) {cout<<"Error: this course does not exist.\n" ; return FAIL;}
		if(the_course.get_status() == GRADED) {cout<<"Error: course has already been graded.\n"; return FAIL;}  
		  
		GradeSheet the_sheet(courseid);
		//cout<<"temp:" << the_sheet.get_grade( self.get_userid() ) << "\n";
		if(the_sheet.get_grade( self.get_userid() ) == "error") {cout<<"Note: You are not registered to this course.\n"; return DONE;}   
		if( the_sheet.delete_entry( self.get_userid() )  == DONE )
		{
			the_course.decrement_headcount();
			the_course.update_data();	
			return DONE;
		}
		else {return FAIL;}
	}	
	
	//3. displays grades across all the courses registered
	int view_grades()
	{
	
		string courseid, title, grade;
		int retvalue= DONE;
		sqlite3* db;
		sqlite3_open(dbname, &db);
		sqlite3_stmt* stmt;		
		
		char sqlcommand1[1000];
		snprintf(sqlcommand1, BUFFLEN, "SELECT * FROM courses");	

		int outcome1 = sqlite3_prepare_v2(db, sqlcommand1, BUFFLEN, &stmt, NULL);
		if(outcome1 != SQLITE_OK) {retvalue = FAIL;}
		else
		{
			while ( sqlite3_step(stmt) == SQLITE_ROW )
			{
				courseid = (const char*) sqlite3_column_text(stmt, 0); 
				title = (const char*) sqlite3_column_text(stmt, 1); 
				
				GradeSheet the_sheet(courseid);
				grade = the_sheet.get_grade(self.get_userid());
				
				if(grade != "error") 
			 	  {cout << "Course" << GAP << courseid << GAP << title << endl
						<< "Grade" << GAP << grade << endl << endl; }
			}
		}
		sqlite3_finalize(stmt);	
		sqlite3_close(db);
		return retvalue;
	}
	
	//4.
	int reset_password(string oldpass, string newpass)
	{
		return self.reset_password(oldpass, newpass);
	}
	
	private:
	StudentData self;
};



//------------INTERFACE----------

//implements text based User Interface. Contains method for login, and specific menus for Admin, Faculty, Student
class UserInterface
{
	public:
	//Takes userid and password as input. On authentication summons the menu depending on type of user.
	void login()
	{
		system("clear");  
		string inp_userid;
		string inp_password;
		cout << "Enter user ID for login:\n";
		cin >> inp_userid;
		cin.ignore();
		UserData userdetails(inp_userid);
		if( userdetails.load_data() == FAIL ) 
			{cout<< "This user does not exist.\n"; return;}
		cout << "Enter password:\n";
		getline(cin, inp_password);
		
		if ( userdetails.get_hashed_password() == hasher(inp_password) )
		{
			system("clear");  
			if(userdetails.get_type() == "admin") {this->adminUI(inp_userid);}
			else if(userdetails.get_type() == "faculty") {this->facultyUI(inp_userid);}
			else if(userdetails.get_type() == "student") {this->studentUI(inp_userid);}
		}
		else {cout<< "Incorrect password.\n"; }	
	}
	
	//implements menu seen by admins
	void adminUI(string inp_userid)
	{
	  AdminPowers commands(inp_userid);
	  bool running = true;
	  while(running)
	  {
		system("clear");  

		string options = "0. Exit\n"
							"1. Add student\n"
							"2. Add faculty\n"
							"3. Add course\n"
							"4. Add student to course\n"
							"5. Delete student\n"
							"6. Delete faculty\n"
							"7. Delete course\n"
							"8. Delete student from course\n"
							"9. Reset password\n"
							"10. Add admin\n"
							"11. Change incharge of course\n"
							"12. View courses\n"
							"13. Lookup students in course\n"
							"14. Lookup users\n";
		cout << "Enter corresponding number to perform one of the following:\n" << options; 
		int choice;
		cin >> choice;
		string temp;
		getline(cin, temp);  //clear newline and junk chars from cin
		
		system("clear");  	
		switch(choice)
		{
			case 0: 
			{
				running = false;
				break;
			}
			
			case 1: 
			{
				string userid, name, password;
				cout<<"Enter user ID of student (spaces not allowed):\n";
				getline(cin, userid);
				if (userid.find(' ') != string::npos) 	//only userid cannot have spaces
					{cout<<"Error: userid cannot contain space.\n"; break;}
				cout<<"Enter name of student:\n";
				getline(cin, name); 					//name can have spaces
				cout<<"Enter initial password for student:\n";
				getline(cin, password);
				message( commands.add_student(userid, name, password) );
				break;
			}
				
			case 2: 
			{
				string userid, name, password;
				cout<<"Enter user ID for faculty (spaces not allowed):\n";
				getline(cin, userid);
				if (userid.find(' ') != string::npos) 	//only userid cannot have spaces
					{cout<<"Error: userid cannot contain space.\n"; break;}
				cout<<"Enter name of faculty:\n";
				getline(cin, name); 
				cout<<"Enter initial password for faculty:\n";
				getline(cin, password);
				message( commands.add_faculty(userid, name, password) );
				break;
			}
				
			case 3:
			{
				string courseid, title, incharge;
				cout<< "Enter course ID (spaces not allowed):\n";
				getline(cin, courseid);
				if (courseid.find(' ') != string::npos) 	//only userid cannot have spaces
					{cout<<"Error: course ID cannot contain space.\n"; break;}
				cout<< "Enter title of course:\n";
				getline(cin, title);
				cout<< "Enter ID of faculty in charge:\n";
				getline(cin, incharge);								
				message( commands.add_course(courseid, title, incharge) );
				break;
			}	
			
			case 4:
			{
				string userid, courseid;
				cout<< "Enter ID of student:\n";
				getline(cin, userid);	
				cout<< "Enter ID of course:\n";
				getline(cin, courseid);					
				message( commands.add_student_to_course(userid, courseid) );
				break;
			}
				
			case 5:
			{
				string userid;
				cout<< "Enter ID of student to proceed with deletion.\nEnter '.' otherwise.\n";
				getline(cin, userid);
				if(userid!=".") { message(  commands.del_student(userid) );}
				break;
			}
				
			case 6:
			{
				string userid;
				cout<< "Enter ID of faculty to proceed with deletion.\nEnter '.' otherwise.\n";
				getline(cin, userid);
				if(userid!=".") { message( commands.del_faculty(userid) ); }
				break;		
			}	
				
			case 7:
			{
				string courseid="";
				cout<< "Enter course ID to proceed with deletion.\nEnter '.' otherwise.\n";
				getline(cin, courseid);
				if(courseid!=".") { message( commands.del_course(courseid) );}
				break;
			}
				
			case 8:
			{
				string userid, courseid;
				cout<< "Enter ID of student to be removed from course:\n";
				getline(cin, userid);
				cout<< "Enter ID of course:\n";
				getline(cin, courseid);	
				message( commands.del_student_from_course(userid, courseid) );
				break;
			}
			case 9:
			{
				string oldpass, newpass;
				cout << "Reenter current password first:\n";
				getline(cin, oldpass);
				system("clear"); //not leaving passwords visible after entered
				cout << "Enter new password:\n";
				getline(cin, newpass);
				system("clear");
				message( commands.reset_password(oldpass, newpass) );
				break;
			}
			
			case 10:
			{
				string auth_password, userid, name, password;
				cout<<"Reenter your password for authentication:\n";
				getline(cin, auth_password);
				system("clear");				
				cout<<"Enter user ID of new admin (spaces not allowed):\n";
				getline(cin, userid);
				if (userid.find(' ') != string::npos) 	//only userid cannot have spaces
					{cout<<"Error: userid cannot contain space.\n"; break;}
				cout<<"Enter name of admin:\n";
				getline(cin, name); //name can have spaces
				cout<<"Enter initial password for the admin:\n";
				getline(cin, password);
				message( commands.add_admin(auth_password, userid, name, password) );
				break;				
			}
			
			case 11:
			{
				string courseid, new_incharge;
				cout <<"Enter ID of course:\n";
 				getline(cin, courseid);
				cout <<"Enter ID of new incharge:\n";
				getline(cin, new_incharge);
				message( commands.change_course_incharge(courseid, new_incharge) );
				break;
			}
			case 12:
			{
				commands.view_courses();
				break;
			}
			case 13:
			{
				string courseid;
				cout << "Enter course ID:\n";
				getline(cin, courseid);
				commands.view_students(courseid);
				break;
			}	
			case 14:
			{
				cout << "Enter the type of users to be displayed:\n";
				cout << "1. Student\n" << "2. Faculty\n" << "3. Admin\n" << "4. All\n";
				int opt;
				cin >> opt;
				string temp;
				getline(cin, temp);  //clear newline and junk chars from cin
				
				system("clear"); 
				switch(opt)
				{
				  case 1:
				 	{commands.view_users("student"); break;}
				  case 2:
				 	{commands.view_users("faculty"); break;	}			
				  case 3:
					{commands.view_users("admin"); break; }	
				  case 4:
				 	{commands.view_users(); break; }	
				  default:
				 	{cout<<"Error: Invalid choice.\n"; }	
				}	
		
				break; 				
			}	
			
			default:
			{
				cout<<"Invalid choice. Exiting.\n";
				running = false;
				break;		
			}										
		}
		
		if(running) { wait(); }
	  } //end of while
	}
	
	//implements menu seen by faculty
	void facultyUI(string inp_userid)
	{
	  FacultyPowers commands(inp_userid);
	  bool running = true;
	  while(running)
	  {
		system("clear");  

		string options = "0. Exit\n"
							"1. Submit grades\n"
							"2. Set status of course\n"
							"3. Lookup students in course\n"
							"4. Reset password\n"
							"5. View courses\n";
		cout << "Enter corresponding number to perform one of the following:\n" << options; 
		int choice;
		cin >> choice;
		string temp;
		getline(cin, temp);
		
		system("clear");  	
		switch(choice)
		{
			case 0: 
			{
				running = false;
				break;
			}
			case 1: 
			{
				string courseid;
				cout<< "Enter course ID:\n";
				getline(cin, courseid);
				
				message( commands.submit_grades(courseid) );
				break;
			}
			
			case 2: 
			{
				string courseid;
				int status;
				cout << "Enter course ID:\n";
				getline(cin, courseid);
				cout << "Enter number corresponding to new status of course:\n" << "(1) Down  (2) Floated \n";
				cin >> status; 
				cin.ignore(); //consumes \n
				message( commands.set_course_status(courseid, status) );
				break;
			}
						
			case 3: 
			{
				string courseid;
				cout << "Enter course ID:\n";
				getline(cin, courseid);
				commands.view_students(courseid);
				break;
			}	
						
			case 4: 
			{
				string oldpass, newpass;
				cout << "Reenter current password first:\n";
				getline(cin, oldpass);
				system("clear"); //not leaving passwords visible after entered
				cout << "Enter new password:\n";
				getline(cin, newpass);
				system("clear");
				message( commands.reset_password(oldpass, newpass) );
				break;
			}	
			case 5:
			{
				commands.view_courses();
				break;
			}	
			default:
			{
				cout<<"Invalid choice. Exiting.\n";
				running = false;
				break;		
			}		
			
		} //end of switch
		
		if(running) { wait(); }
	    
	  } //end of while
	  		
	}
	
	//implements menu seen by students
	void studentUI(string inp_userid)
	{
	  StudentPowers commands(inp_userid);
	  bool running = true;
	  while(running)
	  {
		system("clear");  

		string options = "0. Exit\n"
							"1. Register to course\n"
							"2. Deregister from course\n"
							"3. View registered courses and grades\n"
							"4. Reset password\n"
							"5. View courses\n";
		cout << "Enter corresponding number to perform one of the following:\n" << options; 
		int choice;
		cin >> choice;
		string temp;
		getline(cin, temp); //clear junk input
		system("clear");  	
		
		switch(choice)
		{
			case 0: 
			{
				running = false;
				break;
			}
			case 1: 
			{
				string courseid;
				cout << "Enter ID of the course to register to:\n";
				getline(cin, courseid);
				message( commands.register_course(courseid) );
				break;
			}
			
			case 2: 
			{
				string courseid;
				cout << "Enter ID of the course to deregister from:\n";
				getline(cin, courseid);
				message( commands.deregister_course(courseid) );
				break;
			}
						
			case 3: 
			{
				commands.view_grades();
				break;
			}	
						
			case 4: 
			{
				string oldpass, newpass;
				cout << "Reenter current password first:\n";
				getline(cin, oldpass);
				cout << "Enter new password:\n";
				getline(cin, newpass);
				message( commands.reset_password(oldpass, newpass) );
				break;
			}		
			case 5:
			{
				commands.view_courses();
				break;
			}	
			default:
			{
				cout<<"Invalid choice. Exiting.\n";
				running = false;
				break;		
			}		
			
		} //end of switch
		
		if(running) { wait(); }
	  } //end of while
	  
	} //end of studentUI
	
};

int main()
{
	AdminData temp("admin001", "Root Admin", "default");
	temp.store_data(); //stores default details of the first admin, if they do not exist

	UserInterface ui;
	ui.login();
	return 0;
}
