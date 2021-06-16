#include "GUI/FirstPage_master.hpp"
#include <string>

FirstPage_master::FirstPage_master(Handler handler){
	set_size_request(600,600);
	set_title("FirstPage-master");

	handler.WindowEmpty = false;

//	LoginManager::LoginState loginState = (handler.get_loginManager()).login("389090","RAAdlPq0eA5kp9K32ChQ");
	
	add(mainGrid);

	for(size_t i = 0,j = 1 ; i < handler.get_course_size(); i++){
		if(handler.get_course_element(i).isRegisteredMaster(handler.get_loginManager())){
			arrayButton.at(i*4).set_label("Add Exam");
			arrayButton.at((i*4)+1).set_label("Remove Exam");
			arrayButton.at((i*4)+2).set_label("Register Student");
			arrayButton.at((i*4)+3).set_label("Remove Student");
			
			arrayGrid.at(i).attach(arrayButton.at(i*4),1,1);
			arrayGrid.at(i).attach(arrayButton.at((i*4) + 1),1,2);
			arrayGrid.at(i).attach(arrayButton.at((i*4) + 2),1,3);
			arrayGrid.at(i).attach(arrayButton.at((i*4) + 3),1,4);
			
			arrayGrid.at(i).set_row_spacing(5);

			mainGrid.attach(arrayGrid.at(i),j,1);
			j++;
		}
	}

	mainGrid.set_column_spacing(30);
//	mainGrid.attach(button,1,1);

	show_all();
}
