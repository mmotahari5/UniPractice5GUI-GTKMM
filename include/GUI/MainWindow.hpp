#include <gtkmm.h>
#include <glibmm/ustring.h>
#include <string>
#include "LoginManager.hpp"
#include "GUI/Handler.hpp"
#include <vector>

class MainWindow;
class LoginPage:public Gtk::Grid{
	public:
		LoginPage();
		Handler handler;
//		Gtk::Grid getResult();
		MainWindow* mainWindow;	
	private:
		void click_loginButton();
		//	Login page
//		Gtk::Grid loginGrid;
		Gtk::Button loginButton;
		Gtk::Entry Entry_Username, Entry_Password;
		Gtk::CheckButton CheckButton_password_invisible;

};

class FirstPage_master:public Gtk::Grid{ 
	public:
		FirstPage_master();
		Handler handler;
		void show();
		MainWindow* mainWindow;

	private:
		void click_addExam(int);
		void click_removeExam(int);
		void click_registerStudent(int);
		void click_removeStudent(int);


		std::array<Gtk::Grid,5> arrayGrid;
		std::array<Gtk::Button,20> arrayButton;
		std::array<Gtk::Label,5> arrayLabel;
		std::array<Gtk::Frame,5> arrayFrame;
};

class AddExamPage:public Gtk::Grid{ 
	public:
		AddExamPage();
		Handler handler;
		void show();
		MainWindow* mainWindow;
		
		int courseNumber;
	private:
		
		Gtk::Grid mainGrid,topGrid;
		//	widgets for four choices questions --------
		Gtk::Button acceptBtn{"Accept"},denyBtn{"Deny"}, addQuestionBtn{"Add Question"}, submitQuestion{"Submit"};
		Gtk::RadioButton textualAnswerRadioBtn{"textual answer"}, blankFillingAnswerRadioBtn{"blank filling answer"}, fourChoicesAnswerRadioBtn{"four choices answer"};
		Gtk::RadioButtonGroup radioButtonGroup;
		std::array<Gtk::Entry,6> arrayEntry;
		size_t numberElementEntry=0;

		void click_addQuestion(ExamMasterAccess&);
		void submitQuestionButtonClicked(ExamMasterAccess&);
// widget for textual questions -----------------
		std::array<Gtk::Entry,3> arrayEntryTextual;
		Gtk::Button submitBtnTextual{"Submit"};
		void submitQuestionTextualButtonClicked(ExamMasterAccess&);
		//	widgets for blankFilling questions --------
		std::array<Gtk::Entry,3> arrayEntryBlankFilling;
		Gtk::Button submitBtnBlankFilling{"Submit"};
		void submitQuestionBlankFillingButtonClicked(ExamMasterAccess&);

};

class RegisterStudentPage:public Gtk::Grid{
	public:
		RegisterStudentPage();
		Handler handler;
		void show();
		MainWindow* mainWindow;
		
	private:
		Gtk::Entry StudentCode;
		Gtk::Button RegisterButton{"Register"},BackButton{"Back"};
		Gtk::Label StatusLabel;
};
class MainWindow:public Gtk::Window{
	public:
		MainWindow(Handler&);
		LoginManager loginManager = LoginManager::getInstance();

		void goToCourseMasterPage();
		void goToAddExamPage(int);
		void goFromAddExamPageToFirstPage_masterDenyBtn();
		void goFromAddExamPageToFirstPage_masterAcceptBtn(Exam&,int);

		LoginPage loginPage;
		Handler handler;
		FirstPage_master firstPage_master;
		AddExamPage addExamPage;
		RegisterStudentPage registerStudentPage;

	private:
		Gtk::Grid mainGrid,firstGrid,secondGrid;
		Gtk::Button button1, button2, button3, btn4{"btn4"};
};
