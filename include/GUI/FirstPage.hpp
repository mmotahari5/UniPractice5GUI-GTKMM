#ifndef _FIRSTPAGE
#define _FIRSTPAGE

#include <gtkmm.h>

class FirstPage: public Gtk::Window{
	public:
		FirstPage();
//		~FirstPage() = delete;
		
	private:
		Gtk::Grid grid;
		Gtk::Button button{"bu"};
};

#endif
