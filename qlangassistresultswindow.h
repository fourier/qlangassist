// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#ifndef _QLANGASSISTRESULTSWINDOW_H_
#define _QLANGASSISTRESULTSWINDOW_H_

#include <QTextBrowser>
#include "qlangassistmodel.h"


class QLangAssistResultsWindow : public QTextBrowser
{
  Q_OBJECT;
public:
  typedef QTextBrowser Parent;
public:
  QLangAssistResultsWindow(QWidget* parent = 0);
  void showResults(const QLangAssistModel::WrongAnswersListT& wrongAnswers, int numberOfQuestions);
protected:
  void keyReleaseEvent ( QKeyEvent * event );
};

#endif /* _QLANGASSISTRESULTSWINDOW_H_ */
