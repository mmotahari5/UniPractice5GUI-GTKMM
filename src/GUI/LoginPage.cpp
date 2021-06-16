#include "GUI/LoginPage.hpp"
#include "all_include_files.hpp"
#include <iostream>
#include <string>
#include "GUI/FirstPage_master.hpp"
#include "GUI/FirstPage_student.hpp"
#include "GUI/FirstPage.hpp"
#include "GUI/Handler.hpp"

LoginPage::LoginPage(Handler& handler){
//	set_size_request(500,500);
//	set_title("Login Page");
	handler.WindowEmpty = false;
	
//	add(loginGrid);
//	add(mainGrid);

	Entry_Username.set_max_length(50);
	Entry_Password.set_max_length(50);
	
	Entry_Username.set_placeholder_text("Username");
	Entry_Password.set_placeholder_text("Password");
//	Entry_Username.set_valign(Gtk::Align::ALIGN_CENTER);
//	Entry_Password.set_valign(Gtk::Align::ALIGN_CENTER);
	
	CheckButton_password_invisible.set_label(Glib::ustring("Show password"));

	LoginButton.set_label("Login");
//Username.set_text("Username");
//Password.set_text("Password");

	loginGrid.attach(Entry_Username,1,2);
	loginGrid.attach(Entry_Password,1,3);
	loginGrid.attach(CheckButton_password_invisible,1,4);
	loginGrid.attach(LoginButton,1,5);

//	Username.select_region(100, Username.get_text_length());
	Entry_Password.set_visibility(false);
	CheckButton_password_invisible.signal_toggled().connect([&]{
		Entry_Password.set_visibility(CheckButton_password_invisible.get_active());
	});

	CheckButton_password_invisible.set_active(false);

	LoginButton.set_can_default();
	LoginButton.grab_default();

	mainGrid.attach(loginGrid,2,2);


	LoginButton.signal_clicked().connect([&]{
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
				close();
			/*
				remove();
//				FirstPage_master firstPage_master(handler,username);
				FirstPage firstPage;
				add(firstPage.grid);
//				add(firstPage_master);
				

				show_all();*/
			}
		}
		else if( handler.get_loginManager().login(username,password) == LoginManager::LoginState::USER_NOT_EXISTS){
			std::cout << "user peida nashod" << std::endl;
		}
		else if( handler.get_loginManager().login(username,password) == LoginManager::LoginState::WRONG_PASSWORD){
			std::cout << "Password EshtebaSSS dorostesh ro bezan ....\nplease read more: https://en.wikipedia.org/wiki/Stupidity ;)" << std::endl;
		}
	});

	show_all();
}

Gtk::Grid LoginPage::getResult(){
	return mainGrid;
}
