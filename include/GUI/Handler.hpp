#ifndef _HANDLER
#define _HANDLER

#include <gtkmm.h>
#include <iostream>
#include <vector>
#include "Course.hpp"
#include <stdbool.h>
#include "User/Master.hpp"
#include "User/Student.hpp"
#include "User/UserSerializer.hpp"

class Handler{
	public:
		Handler();
		enum Location {LOGINPAGE, FIRSTPAGE_MASTER, FIRSTPAGE_STUDENT, NONE};
	
		Location currentLocation = Location::NONE;
		
		bool WindowEmpty = true;

		void push_course(Course);
		Course get_course_element(int);
		size_t get_course_size();
		
		LoginManager& get_loginManager() ;
		
		UserSerializer * userSerializer = &UserSerializer::getInstance();

	private:
		std::vector<Course> vector_course;

		LoginManager * loginManager = &LoginManager::getInstance();



};

#endif
