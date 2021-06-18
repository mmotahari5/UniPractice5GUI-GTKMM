#include "GUI/MainWindow.hpp"
//#include "GUI/LoginPage.hpp"
#include "all_include_files.hpp"
#include <iostream>
#include <string>
#include "GUI/Handler.hpp"

using namespace std;
 
MainWindow::MainWindow(Handler& copyHandler){
	set_size_request(500,500);
	set_title("Samane Darsi");

	handler = copyHandler;
//	set_border_width(200);
	loginPage.handler = handler;
	loginPage.mainWindow = this;
	firstPage_master.mainWindow = this;
	addExamPage.mainWindow = this;
	registerStudentPage.mainWindow = this;

	add(loginPage);
	
	show_all();
}

void MainWindow::goToCourseMasterPage(){
	handler = loginPage.handler;
	remove();
	firstPage_master.handler = handler;
	add(firstPage_master);
	firstPage_master.show();
	show_all();
}

void MainWindow::goFromAddExamPageToFirstPage_masterDenyBtn(){
	handler = addExamPage.handler;
	remove();
	firstPage_master.handler = handler;
	add(firstPage_master);
	firstPage_master.show();
	show_all();

}
void MainWindow::goFromAddExamPageToFirstPage_masterAcceptBtn(Exam& exam,int courseNumber){
	handler = addExamPage.handler;
	remove();
	firstPage_master.handler = handler;
	add(firstPage_master);
	firstPage_master.show();
	show_all();

	addExamPage.handler.get_course_element(courseNumber).addExam(loginManager,exam);

}


/*
template <class Origin,class Destinatio>
void MainWindow::goToPage(Origin& A,Destinatio& B){
	handler = A.handler;
	remove();

	B.handler = handler;

	add(B);
	B.show();

	show_all();
}
*/
void MainWindow::goToAddExamPage(int courseNumber){
	handler = firstPage_master.handler;
	addExamPage.courseNumber = courseNumber;
	remove();
	addExamPage.handler = handler;
	add(addExamPage);
	addExamPage.show();
	show_all();
}
