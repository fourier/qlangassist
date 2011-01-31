#include "qlangassistdicteditwindow.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableView>
#include <QTableWidgetItem>

QLangAssistDictEditWindow::QLangAssistDictEditWindow(const QLangAssistModel::DictionaryT& dict, QWidget* parent)
  : Parent(parent),iDict(dict)
{
  iTable = new QTableWidget(dict.size(),2);
  iTable->setShowGrid(true);
  
  QPushButton* okButton = new QPushButton(tr("Ok"));
  
  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(iTable);
  layout->addWidget(okButton);
  
  setLayout(layout);

  connect(okButton,SIGNAL(released()),this,SLOT(okButtonPressed()));
  reloadView();
}


void QLangAssistDictEditWindow::okButtonPressed()
{
  // TODO: do processing here
  accept();
}

void QLangAssistDictEditWindow::reloadView()
{
  QStringList labels;
  labels << tr("Word")  << tr("Translation");
  iTable->setHorizontalHeaderLabels(labels);
  QLangAssistModel::DictionaryT::const_iterator it = iDict.begin(),
    end = iDict.end();
  for ( int count = 0; it != end; ++ it, ++ count)
  {
    iTable->setItem(count,0,new QTableWidgetItem(iDict.key(*it)));
    iTable->setItem(count,1,new QTableWidgetItem(*it));
  }
}

