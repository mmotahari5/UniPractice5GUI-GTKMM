#include <gtkmm.h>
#include <glibmm/ustring.h>

class Test{
	public:
		Test();
		Gtk::Grid get_grid();
	private:
		Gtk::Button btn{"btn: Test"};
		Gtk::Grid igrid;
};
