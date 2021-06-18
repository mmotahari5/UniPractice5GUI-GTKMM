#include "GUI/Handler.hpp"
#include "LoginManager.hpp"

Handler::Handler(){
	loginManager->login("391010","EYLpFVZSEaNtA2V3LSy");
}

void Handler::push_course(Course course){
	vector_course.push_back(course);
}

Course& Handler::get_course_element(int element){
	return vector_course[element];
}

size_t Handler::get_course_size(){
	return vector_course.size();
}

LoginManager& Handler::get_loginManager() {
	return LoginManager::getInstance();
}

Handler& Handler::operator=(Handler& copyHandler){
	currentLocation = copyHandler.currentLocation;
	WindowEmpty = copyHandler.WindowEmpty;
	userSerializer = copyHandler.userSerializer;
	vector_course = copyHandler.vector_course;
	loginManager = copyHandler.loginManager;

	return *this;
}

void Handler::printCourses(){
	for (size_t i = 0; i < vector_course.size(); i++){
		std::cout << i << ": " << vector_course.at(i).getName() << std::endl;
	}
	std::cout << "vector course size: " << vector_course.size() << std::endl;
}
