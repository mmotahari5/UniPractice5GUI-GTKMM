#include <gtkmm.h>
#include <glibmm/ustring.h>
#include <string>

class LoginPage{

	public:
		LoginPage(Window&);

		Gtk::Grid loginGrid;
	private:
//		void login_button_click(Window&);
		void on_checkbox_visibility_toggled();

		Gtk::Entry Entry_Username;
		Gtk::Entry Entry_Password;
		Gtk::CheckButton CheckButton_password_invisible;
		Gtk::Button LoginButton{"Login"};

};
