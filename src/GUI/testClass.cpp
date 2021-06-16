#include "testClass.hpp"

Test::Test(){
	grid.attach(btn,2,3,10,10);

}

Gtk::Grid Test::get_grid(){
	return this->igrid;
}
