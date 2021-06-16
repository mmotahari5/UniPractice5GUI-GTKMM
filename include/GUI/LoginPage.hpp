#ifndef _LOGINP
#define _LOGINP

#include <gtkmm.h>
#include <glibmm/ustring.h>
#include <string>
#include "GUI/Handler.hpp"

class LoginPage:public Gtk::Grid{
	public:
		LoginPage(Handler&);
		Gtk::Grid getResult();
	private:
		Gtk::Grid mainGrid;
		
		//	Login page
		Gtk::Grid loginGrid;
		Gtk::Button LoginButton;
		Gtk::Entry Entry_Username, Entry_Password;
		Gtk::CheckButton CheckButton_password_invisible;

};

#endif
