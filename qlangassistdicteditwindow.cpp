#include "qlangassistdicteditwindow.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QMessageBox>
#include <QTableWidget>

QLangAssistDictEditWindow::QLangAssistDictEditWindow(const QLangAssistModel::DictionaryT& dict, QWidget* parent)
  : Parent(parent),iDict(dict)
{
  iTable = new QTableView(dict.size(),2);
  iTable->setShowGrid(true);
  
  QPushButton* okButton = new QPushButton();
  
  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(iTable);
  layout->addWidget(okButton);
  
  setLayout(layout);

  connect(okButton,SIGNAL(released()),this,SLOT(okButtonPressed()));
}


void QLangAssistDictEditWindow::okButtonPressed()
{
  // TODO: do processing here
  accept();
}

QLangAssistDictEditWindow::reloadView()
{
  QStringList labels;
  labels << tr("Word")  << tr("Translation");
  iTable->setHorizontalHeaderLabels(labels);
  QLangAssistModel::DictionaryT::const_iterator it = iDict.begin(),
    end = iDict.end();
  for ( ; it != end; ++ it)
    
}

