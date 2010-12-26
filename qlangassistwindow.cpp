// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#include "qlangassistwindow.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QFileDialog>
#include <QTimer>
#include <QSettings>
#include <QApplication>
#include <QMessageBox>

#include "qlangassistmodel.h"
#include "qlangassistwidget.h"


QLangAssistWindow::QLangAssistWindow()
  : QMainWindow(0,Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
  setWindowIcon(QIcon(":/QLangAssist/icon.png"));
  iSysTrayIcon = new QSystemTrayIcon(QIcon(":/QLangAssist/icon.png"));
  connect(iSysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(sysTrayActivated(QSystemTrayIcon::ActivationReason)));
  
  setMinimumSize(200,200);
  iModel = new QLangAssistModel;
  iWidget = new QLangAssistWidget(*iModel);
  setCentralWidget(iWidget);
  
  
  createMenus();
  setWindowTitle(tr("QLangAssist"));

  QSettings settings("TxMSoft", "QLangAssist");
  // if (settings.contains(lastDictionaryFile))
  // {
  //   iLastFile = settings.value(lastDictionaryFile).toString();
  //   QTimer::singleShot(10, this, SLOT(loadLastFile()));
  // }


  QMenu* trayMenu = new QMenu;
  iShowAct = new QAction(tr("Show"),this);
  connect(iShowAct,SIGNAL(triggered()),this,SLOT(showWindow()));
  trayMenu->addAction(iShowAct);
  trayMenu->addSeparator();
  trayMenu->addAction(iQuitAct);
  iSysTrayIcon->setContextMenu(trayMenu);
  
  iSysTrayIcon->show();
  
  QTimer::singleShot(10, this, SLOT(openFile()));
}

QLangAssistWindow::~QLangAssistWindow()
{
  delete iSysTrayIcon;
}



void QLangAssistWindow::createMenus()
{
  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
  iAboutAct = new QAction(tr("&About"), this);
  iAboutAct->setStatusTip(tr("About the QLangAssist"));
  connect(iAboutAct, SIGNAL(triggered()), this, SLOT(about()));
  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(iAboutAct);
  
  iOpenAct = new QAction(tr("&Open..."),this);
  iQuitAct=  new QAction(tr("&Exit"),this);
  fileMenu->addAction(iOpenAct);
  fileMenu->addSeparator();
  fileMenu->addAction(iQuitAct);
  connect(iOpenAct,SIGNAL(triggered(bool)),this,SLOT(openFile()));
  connect(iQuitAct,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
}


void QLangAssistWindow::openFile()  
{
  QString fileName = QFileDialog::getOpenFileName(this,
                                                  tr("Open Dictionary"), "", tr("Dictionaries (*.txt)"));
  if (!fileName.length())
    qApp->quit();
  if (iModel->readFile(fileName))
    iWidget->reloadWindow();
  // iWidget->setDictionary(fileName);
  // QSettings settings("TxMSoft", "QSdict");
  // settings.setValue(lastDictionaryFile,fileName);
}

void QLangAssistWindow::sysTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
  if ( reason == QSystemTrayIcon::DoubleClick )
    show();
}

void QLangAssistWindow::closeEvent(QCloseEvent* e)
{
  hide();
  e->ignore();
}

void QLangAssistWindow::showWindow()
{
  show();
}


void QLangAssistWindow::about()
{
  QString textMessage;
  textMessage = "<p> The <a href=\"QLangAssist\">QLangAssist</a> application</p>";
  textMessage += "<p>Copyright (c) <a href=\"mailto:alexey.veretennikov@gmail.com\">Alexey Veretennikov</a>, 2010</p>";
  QMessageBox::about(this, tr("About"),textMessage);
}
