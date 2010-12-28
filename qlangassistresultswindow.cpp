#include "qlangassistresultswindow.h"
#include <QKeyEvent>

QLangAssistResultsWindow::QLangAssistResultsWindow(QWidget* parent )
  : Parent(parent)
{
  setMinimumSize(400,400);
}

void QLangAssistResultsWindow::showResults(const QLangAssistModel::WrongAnswersListT& wrongAnswers, int numberOfQuestions)
{
  QString result;
  result = "<h2>Total correct " + QString::number(numberOfQuestions-wrongAnswers.size()) + " from " + QString::number(numberOfQuestions)+ "</h2>";
  result += tr("<h3>Mistakes found:</h3>");
  QLangAssistModel::WrongAnswersListT::const_iterator it =
    wrongAnswers.begin(),end = wrongAnswers.end();
  for (; it != end; ++ it)
  {
    result += "<h4>Word: <font color=blue>" + it->iWord + "</font></h4>";
    result += "You've selected: <font color=red>" + it->iAnswered + "</font><br/>";
    result += "Correct answer: <font color=green>" + it->iCorrect + "</font><br/>";
  }
  setHtml(result);
  show();
}

void QLangAssistResultsWindow::keyReleaseEvent ( QKeyEvent * event )
{
  if (event->key() == Qt::Key_Escape)
  {
    close();
    this->deleteLater();
  }
  else
    Parent::keyReleaseEvent(event);
}
