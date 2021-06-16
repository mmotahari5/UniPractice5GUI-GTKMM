#include "GUI/Handler.hpp"
#include "LoginManager.hpp"

Handler::Handler(){
	loginManager->login("391010","EYLpFVZSEaNtA2V3LSy");
}

void Handler::push_course(Course course){
	vector_course.push_back(course);
}

Course Handler::get_course_element(int element){
	return vector_course[element];
}

size_t Handler::get_course_size(){
	return vector_course.size();
}

LoginManager& Handler::get_loginManager() {
	return LoginManager::getInstance();
}
