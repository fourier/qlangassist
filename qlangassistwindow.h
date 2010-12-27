// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#ifndef _QLANGASSISTWINDOW_H_
#define _QLANGASSISTWINDOW_H_


#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QEvent>
#include <QCloseEvent>

class QLangAssistWidget;
class QLangAssistModel;


class QLangAssistWindow : public QMainWindow
{
  Q_OBJECT;
public:
  typedef QMainWindow Parent;
public:
  QLangAssistWindow();
  virtual ~QLangAssistWindow();
  void createMenus();
protected:
  virtual void closeEvent(QCloseEvent* e);
public slots:
  void openFile();
  void showWindow();
  void options();
  void about();
  void exitApplication();
private slots:
  void sysTrayActivated(QSystemTrayIcon::ActivationReason reason);
private:
  QSystemTrayIcon* iSysTrayIcon;
  QLangAssistModel* iModel;
  QLangAssistWidget* iWidget;
  QAction* iAboutAct;
  QAction* iOpenAct;
  QAction* iOptionsAct;
  QAction* iQuitAct;
  QAction* iShowAct;
};


#endif /* _QLANGASSISTWINDOW_H_ */
