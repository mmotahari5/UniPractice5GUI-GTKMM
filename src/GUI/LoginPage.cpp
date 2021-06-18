//#include "GUI/LoginPage.hpp"
#include "GUI/MainWindow.hpp"
#include "all_include_files.hpp"
#include <iostream>
#include <string>
#include "GUI/FirstPage.hpp"
#include "GUI/Handler.hpp"

LoginPage::LoginPage(){
	Entry_Username.set_max_length(50);
	Entry_Password.set_max_length(50);
	
	Entry_Username.set_placeholder_text("Username");
	Entry_Password.set_placeholder_text("Password");
//	Entry_Username.set_valign(Gtk::Align::ALIGN_CENTER);
//	Entry_Password.set_valign(Gtk::Align::ALIGN_CENTER);
	
	CheckButton_password_invisible.set_label(Glib::ustring("Show password"));

	loginButton.set_label("Login");

	attach(Entry_Username,1,2);
	attach(Entry_Password,1,3);
	attach(CheckButton_password_invisible,1,4);
	attach(loginButton,1,5);

//	Username.select_region(100, Username.get_text_length());
	Entry_Password.set_visibility(false);
	CheckButton_password_invisible.signal_toggled().connect([&]{
		Entry_Password.set_visibility(CheckButton_password_invisible.get_active());
	});

	CheckButton_password_invisible.set_active(false);

	loginButton.set_can_default();
	loginButton.grab_default();


	loginButton.signal_clicked().connect(sigc::mem_fun(*this,&LoginPage::click_loginButton));
}

void LoginPage::click_loginButton(){
	std::cout << "Login Button Clicked" << std::endl;

	std::string username = std::string(Entry_Username.get_buffer()->get_text());
	std::string password = std::string(Entry_Password.get_buffer()->get_text());

	if( handler.get_loginManager().login(username,password) == LoginManager::LoginState::SUCCESS){
		std::cout << "Naaa BARIKALLAH!!\nNAAAAAA BIBIN MANOO ..... BARIKALLAH\nlogin successfull\n\n" << std::endl;
		handler.WindowEmpty = true;
		//this->close();
		if(UserSerializer::UserType::MASTER == handler.userSerializer->getType(handler.userSerializer->serialize(handler.get_loginManager().getCurrentUser()))){
			std::cout << "This username is Master!!\n" << std::endl;
			
			handler.currentLocation = Handler::Location::FIRSTPAGE_MASTER;
			
//			mainWindow->goToPage<LoginPage, FirstPage_master>(*this,mainWindow->firstPage_master);
			mainWindow->goToCourseMasterPage();
//			close();
		/*
			remove();
//			FirstPage_master firstPage_master(handler,username);
			FirstPage firstPage;
			add(firstPage.grid);
//			add(firstPage_master);
				show_all();*/
		}
	}
	else if( handler.get_loginManager().login(username,password) == LoginManager::LoginState::USER_NOT_EXISTS){
		std::cout << "user peida nashod" << std::endl;
	}
	else if( handler.get_loginManager().login(username,password) == LoginManager::LoginState::WRONG_PASSWORD){
		std::cout << "Password EshtebaSSS dorostesh ro bezan ....\nplease read more: https://en.wikipedia.org/wiki/Stupidity ;)" << std::endl;
	}
}
