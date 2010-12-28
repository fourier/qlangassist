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
#include "qlangassistoptionsdlg.h"
#include "qlangassistsettings.h"


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

  resize(QLangAssistSettings::windowSize());
  move(QLangAssistSettings::windowPosition());

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
  iOptionsAct = new QAction(tr("O&ptions..."),this);
  iQuitAct=  new QAction(tr("&Exit"),this);
  fileMenu->addAction(iOpenAct);
  fileMenu->addAction(iOptionsAct);
  fileMenu->addSeparator();
  fileMenu->addAction(iQuitAct);
  connect(iOpenAct,SIGNAL(triggered()),this,SLOT(openFile()));
  connect(iOptionsAct,SIGNAL(triggered()),this,SLOT(options()));
  connect(iQuitAct,SIGNAL(triggered()),this,SLOT(exitApplication()));
}

void QLangAssistWindow::exitApplication()
{
  QLangAssistSettings::setWindowSize(size());
  QLangAssistSettings::setWindowPosition(pos());
  qApp->quit();
}


void QLangAssistWindow::openFile()  
{
  QString fileName;
  if (iModel->isEmpty()) // first start
    fileName = QLangAssistSettings::lastLoadedFile();
  if (!fileName.length())
    fileName = QFileDialog::getOpenFileName(this,
                                          tr("Open Dictionary"), "", tr("Dictionaries (*.txt)"));
  if (!fileName.length() && iModel->isEmpty())
    qApp->quit();

  if (fileName.length() && iModel->readFile(fileName))
  {
    iWidget->reloadWindow();
    QLangAssistSettings::setLastLoadedFile(fileName);
  }
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
  textMessage = "<p> The <a href=\"http://qlangassist.txmhost.net\">QLangAssist</a> application</p>";
  textMessage += "<p>Copyright (c) <a href=\"mailto:alexey.veretennikov@gmail.com\">Alexey Veretennikov</a>, 2010</p>";
  QMessageBox::about(this, tr("About"),textMessage);
}


void QLangAssistWindow::options()
{
  QLangAssistOptionsDlg dlg;
  bool doRefresh = false;
  bool result = dlg.execute(doRefresh);
  if (result && doRefresh)
  {
    iWidget->reloadWindow();
  }
}
