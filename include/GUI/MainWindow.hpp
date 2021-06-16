/*#include <gtkmm/window.h>
#include <gtkmm/textview.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/entry.h>*/
#include <gtkmm.h>
#include <glibmm/ustring.h>
#include <string>
#include "LoginManager.hpp"

class MainWindow:public Gtk::Window{
//	friend LoginManager::LoginManager();
	public:
		MainWindow();
		LoginManager loginManager = LoginManager::getInstance();

	private:
		Gtk::Grid mainGrid,firstGrid,secondGrid;
		Gtk::Button button1, button2, button3, btn4;
	
};
