// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#ifndef _QLANGASSISTWIDGET_H_
#define _QLANGASSISTWIDGET_H_

#include <QWidget>
#include <QList>
#include "qlangassistmodel.h"

class QLabel;

class QRadioButton;
class QGroupBox;
class QPushButton;

class QLangAssistWidget : public QWidget, public IChoices
{
  Q_OBJECT;
public:
  typedef QWidget ParentT;
  typedef QList<QRadioButton*> ButtonsListT;
public:
  QLangAssistWidget(QLangAssistModel& model);
  ~QLangAssistWidget();
  void reloadWindow();
  
  virtual void fillChoices(const QString& word, const QStringList& choices);

signals:
    
public slots:
  void next();
  void finish();
private:
  static QString createResults(const QLangAssistModel::WrongAnswersListT& wrongAnswers,
    int numberOfQuestions);
  void updateChoicesCount();
private:
  
  QLangAssistModel& iModel;
  QLabel* iQuestionNumber;
  QLabel* iPhrase;
  QGroupBox* iChoices;
  ButtonsListT* iRadioButtons;
  QPushButton* iNextButton;
  QPushButton* iFinishButton;
};

#endif /* _QLANGASSISTWIDGET_H_ */
