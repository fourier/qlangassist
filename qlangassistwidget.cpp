// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#include "qlangassistwidget.h"

#include <QLabel>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextBrowser>


const char* kQuestionText = "Question number 1";

QLangAssistWidget::QLangAssistWidget(QLangAssistModel& model, int numOfChoices) :
  ParentT(),
  iModel(model),
  iNumOfChoices(numOfChoices)
{
  // Label
  iQuestionNumber = new QLabel(kQuestionText);
  iPhrase = new QLabel();
  iPhrase->setStyleSheet("QLabel {font-size: 18pt; font-weight: bold; color: darkgreen}");
  iRadioButtons = new ButtonsListT(); 
  iChoices = new QGroupBox(tr("Choose the correct translation:"));

  for (int i = 0; i < numOfChoices; ++ i)
    iRadioButtons->append(new QRadioButton());
  iRadioButtons->at(0)->setChecked(true);
// radio3->setStyleSheet("QRadioButton{color:red}");

  QVBoxLayout *vbox = new QVBoxLayout;
  for (int i = 0; i < numOfChoices; ++ i)
    vbox->addWidget(iRadioButtons->at(i));

  vbox->addStretch(1);
  iChoices->setLayout(vbox);

  QHBoxLayout* hbox = new QHBoxLayout;
  iFinishButton = new QPushButton(tr("Finish"));
  iNextButton = new QPushButton(tr("Next"));
  hbox->addWidget(iFinishButton);
  hbox->addWidget(iNextButton);
  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget(iQuestionNumber);
  layout->addWidget(iPhrase);
  layout->addWidget(iChoices);
  layout->addLayout(hbox);
  setLayout(layout);


  connect(iFinishButton,SIGNAL(released ()),
          this,SLOT(finish()));
  connect(iNextButton,SIGNAL(released ()),
          this,SLOT(next()));
}

QLangAssistWidget::~QLangAssistWidget()
{
}

void QLangAssistWidget::reloadWindow()
{
  iQuestionNumber->setText(kQuestionText);
  iModel.start();
  iModel.fillChoices(*this,iNumOfChoices);
}

void QLangAssistWidget::next()
{
  for ( int i = 0; i < iNumOfChoices; ++ i)
    if (iRadioButtons->at(i)->isChecked())
    {
      int number = iModel.answer(iPhrase->text(),iRadioButtons->at(i)->text());
      iQuestionNumber->setText(tr("Question number ") + QString::number(number+1));
    }
  iModel.fillChoices(*this,iNumOfChoices);
}

void QLangAssistWidget::finish()
{
  iQuestionNumber->setText(kQuestionText);
  QLangAssistModel::WrongAnswersListT wrongAnswers;
  int numberOfQuestionsTotal = 0;
  iModel.stop(wrongAnswers,numberOfQuestionsTotal);
  QString report = createResults(wrongAnswers,numberOfQuestionsTotal);
  QTextBrowser* browser = new QTextBrowser();
  browser->setHtml(report);
  browser->show();
}

void QLangAssistWidget::fillChoices(const QString& word, const QStringList& choices)
{
  iPhrase->setText(word);
  int count = std::min(choices.size(),iRadioButtons->size());
  for ( int i = 0; i < count ; ++i )
    iRadioButtons->at(i)->setText(choices[i]);
}

QString QLangAssistWidget::createResults(const QLangAssistModel::WrongAnswersListT& wrongAnswers, int numberOfQuestions)
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
  return result;
}
