#include "MainWindow.hpp"
#include "LoginPage.hpp"
#include "all_include_files.hpp"
#include <iostream>
#include <string>
#include "GUI/Handler.hpp"

using namespace std;
 
MainWindow::MainWindow(){
	set_size_request(500,500);
	set_title("Samane Darsi");

	Handler handler;

//	set_border_width(200);
	LoginPage loginPage(handler);

	add(loginPage.getResult());

	show_all();
}
