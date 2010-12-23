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

#include "qlangassistmodel.h"
#include "qlangassistwidget.h"


QLangAssistWindow::QLangAssistWindow()
  : QMainWindow(0,Qt::Dialog|Qt::WindowContextHelpButtonHint)
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


