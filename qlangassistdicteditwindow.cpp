#include "qlangassistdicteditwindow.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QMessageBox>
#include <QTableView>

QLangAssistDictEditWindow::QLangAssistDictEditWindow(const QLangAssistModel::DictionaryT& dict, QWidget* parent)
  : Parent(parent),iDict(dict)
{
  iTable = new QTableView;

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
