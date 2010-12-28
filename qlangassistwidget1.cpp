// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#include "qlangassistwidget.h"
#include "qlangassistsettings.h"
#include "qlangassistresultswindow.h"

#include <QLabel>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextBrowser>



const char* kQuestionText = "Question number 1";

QLangAssistWidget::QLangAssistWidget(QLangAssistModel& model) :
  ParentT(),
  iModel(model)
{
  // Label
  iQuestionNumber = new QLabel(kQuestionText);
  iPhrase = new QLabel();
  iPhrase->setStyleSheet("QLabel {font-size: 18pt; font-weight: bold; color: darkgreen}");
  iRadioButtons = new ButtonsListT(); 
  iChoices = new QGroupBox(tr("Choose the correct translation:"));
  int numOfChoices = QLangAssistSettings::maxNumOfChoices();
  for (int i = 0; i < numOfChoices; ++ i)
  {
    QRadioButton* btn = new QRadioButton();
    btn->hide();
    iRadioButtons->append(btn);
  }
  QVBoxLayout *vbox = new QVBoxLayout;
  for (int i = 0; i < numOfChoices; ++ i)
    vbox->addWidget(iRadioButtons->at(i));

  numOfChoices = QLangAssistSettings::numChoices();
  for ( int i = 0; i < numOfChoices; ++ i )
    iRadioButtons->at(i)->show();
  iRadioButtons->at(0)->setChecked(true);

// radio3->setStyleSheet("QRadioButton{color:red}");


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
  updateChoicesCount();
  int numOfChoices = QLangAssistSettings::numChoices();
  iModel.fillChoices(*this,numOfChoices);
}

void QLangAssistWidget::next()
{
  int numOfChoices = QLangAssistSettings::numChoices();
  for ( int i = 0; i < numOfChoices; ++ i)
    if (iRadioButtons->at(i)->isChecked())
    {
      int number = iModel.answer(iPhrase->text(),iRadioButtons->at(i)->text());
      iQuestionNumber->setText(tr("Question number ") + QString::number(number+1));
    }
  iModel.fillChoices(*this,numOfChoices);
}

void QLangAssistWidget::finish()
{
  iQuestionNumber->setText(kQuestionText);
  QLangAssistModel::WrongAnswersListT wrongAnswers;
  int numberOfQuestionsTotal = 0;
  iModel.stop(wrongAnswers,numberOfQuestionsTotal);
  QLangAssistResultsWindow* resultsWindow = new QLangAssistResultsWindow();
  resultsWindow->showResults(wrongAnswers,numberOfQuestionsTotal);
}

void QLangAssistWidget::fillChoices(const QString& word, const QStringList& choices)
{
  iPhrase->setText(word);
  int count = std::min(choices.size(),iRadioButtons->size());
  for ( int i = 0; i < count ; ++i )
    iRadioButtons->at(i)->setText(choices[i]);
}


void QLangAssistWidget::updateChoicesCount()
{
  int numOfChoices = QLangAssistSettings::maxNumOfChoices();
  for (int i = 0; i < numOfChoices; ++ i)
  {
    iRadioButtons->at(i)->hide();
  }
  numOfChoices = QLangAssistSettings::numChoices();
  for ( int i = 0; i < numOfChoices; ++ i )
    iRadioButtons->at(i)->show();
  iRadioButtons->at(0)->setChecked(true);
  resize(sizeHint());
}
