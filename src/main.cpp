#include <gtkmm/application.h>
#include "GUI/LoginPage.hpp"
#include "all_include_files.hpp"
#include "GUI/FirstPage_master.hpp"
int main(){
	Handler handler;
	Course Mt(std::string("Math"),std::string("381200"));
	Course DS(std::string("Data Science"),std::string("381200"));
	Course AP(std::string("Advance Programming"),std::string("389090"));
	Course En(std::string("English"),std::string("391010"));
	Course Fr(std::string("French"),std::string("391010"));

	handler.push_course(Fr);
	handler.push_course(DS);
	handler.push_course(AP);
	handler.push_course(En);
	handler.push_course(Mt);
	
	
	const auto &app = Gtk::Application::create();

	MainWindow mainWindow();
/*
	LoginPage loginPage(handler);

	std::cout << handler.WindowEmpty <<"\n"<< (handler.currentLocation == Handler::Location::FIRSTPAGE_MASTER) << std::endl;
	if(handler.WindowEmpty && handler.currentLocation == Handler::Location::FIRSTPAGE_MASTER){
		std::cout << "\nhame chi OK bood va bayad window master biadesh\n" << std::endl;
		FirstPage_master firstPage_master(handler);
	}
*/
	app->run(mainWindow);
	return 0;
}
