#include "all_include_files.hpp"
#include <gtkmm.h>
#include <glibmm/ustring.h>
#include <string>
#include "Window.hpp"
#include "LoginPage.hpp"
#include <iostream>

LoginPage::LoginPage(Window& winn){
	Entry_Username.set_max_length(50);
	Entry_Password.set_max_length(50);
	
	Entry_Username.set_placeholder_text("Username");
	Entry_Password.set_placeholder_text("Password");
//	Entry_Username.set_valign(Gtk::Align::ALIGN_CENTER);
//	Entry_Password.set_valign(Gtk::Align::ALIGN_CENTER);
	
	CheckButton_password_invisible.set_label(Glib::ustring("akkheish"));

//Username.set_text("Username");
//Password.set_text("Password");

	loginGrid.attach(Entry_Username,1,2);
	loginGrid.attach(Entry_Password,1,3);
	loginGrid.attach(CheckButton_password_invisible,1,4);
	loginGrid.attach(LoginButton,1,5);

//	Username.select_region(100, Username.get_text_length());

	CheckButton_password_invisible.signal_toggled().connect(sigc::mem_fun(*this,&LoginPage::on_checkbox_visibility_toggled));

	CheckButton_password_invisible.set_active(true);

	LoginButton.set_can_default();
	LoginButton.grab_default();

	LoginButton.signal_clicked().connect([this,&winn]{
		std::cout << "C*L*I*C*K*E*D" << std::endl;

		std::string username = std::string(Entry_Username.get_buffer()->get_text());
		std::string password = std::string(Entry_Password.get_buffer()->get_text());
		
		if( winn.loginManager.login(username,password) == LoginManager::LoginState::SUCCESS){
			std::cout << "login successfull" << std::endl;
		}
		else if( winn.loginManager.login(username,password) == LoginManager::LoginState::USER_NOT_EXISTS){
			std::cout << "user peida nashod" << std::endl;
		}
		else if( winn.loginManager.login(username,password) == LoginManager::LoginState::WRONG_PASSWORD){
			std::cout << "password eshtebassss dorostesh ro bezan bi shouor" << std::endl;
		}
	});
//LoginButton.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &LoginPage::login_button_click),winn2));

//	sigc::mem_fun(*this, &LoginPage::login_button_click));
	loginGrid.show_all();
}

/*
void LoginPage::login_button_click(winndow& winn3){
	std::cout << "C*L*I*C*K*E*D" << std::endl;

	std::string username = std::string(Entry_Username.get_buffer()->get_text());
	std::string password = std::string(Entry_Password.get_buffer()->get_text());
	
	if( winn3.loginManager.login(username,password) == LoginManager::LoginState::SUCCESS){
		std::cout << "login successfull" << std::endl;
	}
	else if( winn3.loginManager.login(username,password) == LoginManager::LoginState::USER_NOT_EXISTS){
		std::cout << "user peida nashod" << std::endl;
	}
	else if( winn3.loginManager.login(username,password) == LoginManager::LoginState::WRONG_PASSWORD){
		std::cout << "password eshtebassss dorostesh ro bezan bi shouor" << std::endl;
	}
	
}
*/

void LoginPage::on_checkbox_visibility_toggled(){
	Entry_Password.set_visibility(CheckButton_password_invisible.get_active());
}
