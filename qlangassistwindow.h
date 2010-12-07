// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#ifndef _QLANGASSISTWINDOW_H_
#define _QLANGASSISTWINDOW_H_


#include <QMainWindow>

class QLangAssistWidget;


class QLangAssistWindow : public QMainWindow
{
  Q_OBJECT;
public:
  QLangAssistWindow();
  virtual ~QLangAssistWindow();
  void createMenus();

public slots:
  void openFile();
                 
private slots:
  
private:  
  QLangAssistWidget* iWidget;
  QAction* iOpenAct;

};


#endif /* _QLANGASSISTWINDOW_H_ */
