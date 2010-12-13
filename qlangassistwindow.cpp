// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#include "qlangassistwindow.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QFileDialog>
#include <QTimer>
#include <QSettings>

#include "qlangassistmodel.h"
#include "qlangassistwidget.h"


QLangAssistWindow::QLangAssistWindow()
  : QMainWindow()
{
  // setTitle("QSdict");
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
    QTimer::singleShot(10, this, SLOT(openFile()));
}

QLangAssistWindow::~QLangAssistWindow()
{
}

void QLangAssistWindow::createMenus()
{
  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
  iOpenAct = new QAction(tr("&Open..."),this);
  fileMenu->addAction(iOpenAct);

  connect(iOpenAct,SIGNAL(triggered(bool)),this,SLOT(openFile()));
}


void QLangAssistWindow::openFile()  
{
  QString fileName = QFileDialog::getOpenFileName(this,
                                                  tr("Open Dictionary"), "", tr("Dictionaries (*.txt)"));
  if (iModel->readFile(fileName))
    iWidget->reloadWindow();
  // iWidget->setDictionary(fileName);
  // QSettings settings("TxMSoft", "QSdict");
  // settings.setValue(lastDictionaryFile,fileName);
}


