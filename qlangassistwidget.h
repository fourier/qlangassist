// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#ifndef _QLANGASSISTWIDGET_H_
#define _QLANGASSISTWIDGET_H_

#include <QWidget>

class QLabel;
class QRadioButton;
class QGroupBox;
class QPushButton;

class QLangAssistWidget : public QWidget
{
  Q_OBJECT;
public:
  typedef QWidget ParentT;
public:
  QLangAssistWidget(QWidget* parent = NULL);
  ~QLangAssistWidget();  
  
signals:
    
public slots:
private:
  QLabel* iPhrase;
  QGroupBox* iChoices;
  QPushButton* iNextButton;
};

#endif /* _QLANGASSISTWIDGET_H_ */
