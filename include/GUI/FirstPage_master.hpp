#ifndef _FIRSTPAGE_MASTER
#define _FIRSTPAGE_MASTER

#include <glibmm/ustring.h>
#include "GUI/FirstPage.hpp"
//#include "User/Master.hpp"
#include "GUI/Handler.hpp"
#include <array>

class FirstPage_master:public FirstPage{ 
	public:
		FirstPage_master(Handler);
	private:
		Gtk::Grid mainGrid;
		std::array<Gtk::Grid,5> arrayGrid;
		std::array<Gtk::Button,20> arrayButton;

		std::array<Gtk::Frame,5> arrayFrame;
};

#endif
