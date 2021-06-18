#include "GUI/MainWindow.hpp"
#include "all_include_files.hpp"

AddExamPage::AddExamPage(){
}

void AddExamPage::show(){
	Exam exam;
	ExamMasterAccess examMasterAccess(exam);

	mainGrid.attach(topGrid,1,1);

	fourChoicesAnswerRadioBtn.set_active(true);
	addQuestionBtn.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&AddExamPage::click_addQuestion),examMasterAccess));	
	
	attach(textualAnswerRadioBtn,1,2);
	attach(blankFillingAnswerRadioBtn,2,2);
	attach(fourChoicesAnswerRadioBtn,3,2);

	textualAnswerRadioBtn.set_group(radioButtonGroup);
	blankFillingAnswerRadioBtn.set_group(radioButtonGroup);
	fourChoicesAnswerRadioBtn.set_group(radioButtonGroup);

	attach(addQuestionBtn,4,2);

	attach(mainGrid,1,1,4);
	attach(acceptBtn,1,3);
	attach(denyBtn,2,3);

	acceptBtn.signal_clicked().connect([&]{
		mainWindow->goFromAddExamPageToFirstPage_masterAcceptBtn(exam,courseNumber);
	});
	denyBtn.signal_clicked().connect([&]{
		mainWindow->goFromAddExamPageToFirstPage_masterDenyBtn();
	});
	//handler.get_course_element(courseNumber).addExam(handler.get_loginManager,exam);
}
void AddExamPage::click_addQuestion(ExamMasterAccess& examMasterAccess){
	remove(addQuestionBtn);
	remove(textualAnswerRadioBtn);
	remove(blankFillingAnswerRadioBtn);
	remove(fourChoicesAnswerRadioBtn);

	if(fourChoicesAnswerRadioBtn.get_active()){
		attach(mainGrid,1,1);
		arrayEntry.at(0).set_placeholder_text("Question");
		arrayEntry.at(1).set_placeholder_text("Choice one");
		arrayEntry.at(2).set_placeholder_text("Choice two");
		arrayEntry.at(3).set_placeholder_text("Coice three");
		arrayEntry.at(4).set_placeholder_text("Coice four");
		arrayEntry.at(5).set_placeholder_text("Score (number)");
		topGrid.attach(arrayEntry.at(0),1,1,4);
		topGrid.attach(arrayEntry.at(1),1,2);
		topGrid.attach(arrayEntry.at(2),2,2);
		topGrid.attach(arrayEntry.at(3),1,3);
		topGrid.attach(arrayEntry.at(4),2,3);
		topGrid.attach(arrayEntry.at(5),1,4);
		topGrid.attach(submitQuestion,2,4);
	
		show_all();

		submitQuestion.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&AddExamPage::submitQuestionButtonClicked),examMasterAccess));
	}
	if(textualAnswerRadioBtn.get_active()){
		attach(mainGrid,1,1);
		arrayEntryTextual.at(0).set_placeholder_text("Question");
		arrayEntryTextual.at(1).set_placeholder_text("Answer");
		arrayEntryTextual.at(2).set_placeholder_text("Score (number)");

		mainGrid.attach(arrayEntryTextual.at(0),1,1,2);
		mainGrid.attach(arrayEntryTextual.at(1),1,2,2);
		mainGrid.attach(arrayEntryTextual.at(2),1,3,1);
		mainGrid.attach(submitBtnTextual,2,3,1);
		show_all();
		submitBtnTextual.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&AddExamPage::submitQuestionTextualButtonClicked),examMasterAccess));

	}
	if(blankFillingAnswerRadioBtn.get_active()){
		attach(mainGrid,1,1);
		arrayEntryBlankFilling.at(0).set_placeholder_text("Question");
		arrayEntryBlankFilling.at(1).set_placeholder_text("Placeholder");
		arrayEntryBlankFilling.at(2).set_placeholder_text("Score (number)");

		mainGrid.attach(arrayEntryBlankFilling.at(0),1,1,2);
		mainGrid.attach(arrayEntryBlankFilling.at(1),1,2,2);
		mainGrid.attach(arrayEntryBlankFilling.at(2),1,3,1);
		mainGrid.attach(submitBtnBlankFilling,2,3,1);
		show_all();
		submitBtnBlankFilling.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&AddExamPage::submitQuestionTextualButtonClicked),examMasterAccess));

	}
}
void AddExamPage::submitQuestionButtonClicked(ExamMasterAccess& examMasterAccess) {

	std::string questionText;
	std::array<std::string, 4> choice;
	std::string scorestr = arrayEntry.at(5).get_text();
	std::stringstream ss;
	ss << scorestr;
	float score;
	ss >> score;

	questionText = arrayEntry.at(0).get_text();
	choice.at(0)= arrayEntry.at(1).get_text();
	choice.at(1)= arrayEntry.at(2).get_text();
	choice.at(2)= arrayEntry.at(3).get_text();
	choice.at(3)= arrayEntry.at(4).get_text();

	FourChoicesQuestion question(questionText,score,choice);
	examMasterAccess.addQuestion(&question);
	
	topGrid.remove(arrayEntry.at(0));
	topGrid.remove(arrayEntry.at(1));
	topGrid.remove(arrayEntry.at(2));
	topGrid.remove(arrayEntry.at(3));
	topGrid.remove(arrayEntry.at(4));
	topGrid.remove(arrayEntry.at(5));
	topGrid.remove(submitQuestion);
	
	arrayEntry.at(0).set_text("");
	arrayEntry.at(1).set_text("");
	arrayEntry.at(2).set_text("");
	arrayEntry.at(3).set_text("");
	arrayEntry.at(4).set_text("");
	arrayEntry.at(5).set_text("");

	attach(addQuestionBtn,4,2);
	attach(textualAnswerRadioBtn,1,2);
	attach(blankFillingAnswerRadioBtn,2,2);
	attach(fourChoicesAnswerRadioBtn,3,2);
	remove(mainGrid);
	show_all();
}
void AddExamPage::submitQuestionTextualButtonClicked(ExamMasterAccess& examMasterAccess){
	std::string scorestr = arrayEntryTextual.at(2).get_text();
	std::stringstream ss;
	ss << scorestr;
	float score;
	ss >> score;
	TextualQuestion textualQuestion(arrayEntryTextual.at(0).get_text(),score);
	TextualAnswer textualAnswer(arrayEntryTextual.at(1).get_text());
	textualQuestion.setAnswer(&textualAnswer);

	examMasterAccess.addQuestion(&textualQuestion);

	topGrid.remove(arrayEntryTextual.at(0));
	topGrid.remove(arrayEntryTextual.at(1));
	topGrid.remove(arrayEntryTextual.at(2));
	topGrid.remove(submitBtnTextual);
	
	arrayEntry.at(0).set_text("");
	arrayEntry.at(1).set_text("");
	arrayEntry.at(2).set_text("");

	attach(addQuestionBtn,4,2);
	attach(textualAnswerRadioBtn,1,2);
	attach(blankFillingAnswerRadioBtn,2,2);
	attach(fourChoicesAnswerRadioBtn,3,2);
	remove(mainGrid);
	show_all();
}
void AddExamPage::submitQuestionBlankFillingButtonClicked(ExamMasterAccess& examMasterAccess){	
	std::string scorestr = arrayEntryBlankFilling.at(2).get_text();
	std::stringstream ss;
	ss << scorestr;
	float score;
	ss >> score;
	std::string questionText = arrayEntryBlankFilling.at(0).get_text();
	std::string placeholderText = arrayEntryBlankFilling.at(1).get_text();

	BlankFillingQuestion blankFillingQuestion(questionText,placeholderText,score);

	examMasterAccess.addQuestion(&blankFillingQuestion);

	topGrid.remove(arrayEntryBlankFilling.at(0));
	topGrid.remove(arrayEntryBlankFilling.at(1));
	topGrid.remove(arrayEntryBlankFilling.at(2));
	topGrid.remove(submitBtnBlankFilling);
	
	arrayEntryBlankFilling.at(0).set_text("");
	arrayEntryBlankFilling.at(1).set_text("");
	arrayEntryBlankFilling.at(2).set_text("");

	attach(addQuestionBtn,4,2);
	attach(textualAnswerRadioBtn,1,2);
	attach(blankFillingAnswerRadioBtn,2,2);
	attach(fourChoicesAnswerRadioBtn,3,2);
	remove(mainGrid);
	show_all();
}
