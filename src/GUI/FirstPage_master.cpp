#include "GUI/MainWindow.hpp"
#include <string>

FirstPage_master::FirstPage_master(){
//	LoginManager::LoginState loginState = (handler.get_loginManager()).login("389090","RAAdlPq0eA5kp9K32ChQ");
	set_column_spacing(30);
}

void FirstPage_master::show(){
	for(size_t i = 0,j = 1 ; i < handler.get_course_size(); i++){
		if(handler.get_course_element(i).isRegisteredMaster(handler.get_loginManager())){
			arrayButton.at(i*4).set_label("Add Exam");
			arrayButton.at(i*4).signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &FirstPage_master::click_addExam),i));
			arrayButton.at((i*4)+1).set_label("Remove Exam");
			arrayButton.at((i*4)+1).signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &FirstPage_master::click_removeExam),i));
			arrayButton.at((i*4)+2).set_label("Register Student");
			arrayButton.at((i*4)+2).signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &FirstPage_master::click_registerStudent),i));
			arrayButton.at((i*4)+3).set_label("Remove Student");
			arrayButton.at((i*4)+3).signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &FirstPage_master::click_removeStudent),i));

			arrayLabel.at(i).set_label(handler.get_course_element(i).getName());

			arrayGrid.at(i).attach(arrayLabel.at(i),1,1);
			arrayGrid.at(i).attach(arrayButton.at(i*4),1,2);
			arrayGrid.at(i).attach(arrayButton.at((i*4) + 1),1,3);
			arrayGrid.at(i).attach(arrayButton.at((i*4) + 2),1,4);
			arrayGrid.at(i).attach(arrayButton.at((i*4) + 3),1,5);
			

			arrayGrid.at(i).set_row_spacing(5);

			attach(arrayGrid.at(i),j,1);
			j++;
		}
	}
}

void FirstPage_master::click_addExam(int courseNumber){
	std::cout << "in click_addExam() ------------>" << std::endl;
	mainWindow->goToAddExamPage(courseNumber);
}
void FirstPage_master::click_removeExam(int courseNumber){
//	mainWindow->goToPage<FirstPage_master>();
}
void FirstPage_master::click_registerStudent(int courseNumber){
//	mainWindow->goToPage<FirstPage_master>();
}
void FirstPage_master::click_removeStudent(int courseNumber){
//	mainWindow->goToPage<FirstPage_master>();
}
