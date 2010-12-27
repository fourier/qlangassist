// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#include <QSettings>
#include <QGroupBox>
#include <QRadioButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QMessageBox>

#include "qlangassistoptionsdlg.h"
#include "qlangassistsettings.h"


QLangAssistOptionsDlg::QLangAssistOptionsDlg(QWidget * parent )
  : QDialog(parent)
{
  setWindowTitle(tr("Options"));
  // setSizeGripEnabled(false);
  // setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowCloseButtonHint);

  QGroupBox* accountGroup = new QGroupBox(tr("Specify what to show in test window:"));
  iTranslationRadioButton = new QRadioButton(tr("Translation"));
  iWordRadioButton = new QRadioButton(tr("Word"));
  if (QLangAssistSettings::isTranslationInChoices())
    iTranslationRadioButton->setChecked(true);
  else
    iWordRadioButton->setChecked(true);
  
  QVBoxLayout *vbox = new QVBoxLayout;  
  vbox->addWidget(iTranslationRadioButton);
  vbox->addWidget(iWordRadioButton);
  accountGroup->setLayout(vbox);

  QGroupBox* choicesGroup = new QGroupBox(tr("Number of choices:"));
  iNumOfChoicesSelector  = new QSlider(Qt::Horizontal);
  iNumOfChoicesSelector->setRange(2, QLangAssistSettings::maxNumOfChoices());
  iNumOfChoicesSelector->setSingleStep(1);
  iNumOfChoicesSelector->setValue(QLangAssistSettings::numChoices());
  iNumOfChoicesLabel = new QLabel(QString::number(QLangAssistSettings::numChoices()));
  connect(iNumOfChoicesSelector,SIGNAL(sliderMoved(int)),this,SLOT(sliderMoved(int)));
  QHBoxLayout* hbox = new QHBoxLayout();
  hbox->addWidget(iNumOfChoicesSelector);
  hbox->addSpacing(20);
  hbox->addWidget(iNumOfChoicesLabel);
  choicesGroup->setLayout(hbox);
    
  QPushButton* okButton = new QPushButton(tr("Ok"));
  okButton->setDefault(true);
  connect(okButton,SIGNAL(released()),this,SLOT(accept()));
  QVBoxLayout *centralLayout = new QVBoxLayout;
  centralLayout->addWidget(accountGroup);
  centralLayout->addWidget(choicesGroup);
  centralLayout->addWidget(okButton);
  setLayout(centralLayout);
}

void QLangAssistOptionsDlg::sliderMoved ( int value )
{
  iNumOfChoicesLabel->setText(QString::number(value));
}

int QLangAssistOptionsDlg::exec ()
{
  return QDialog::exec();
}

bool QLangAssistOptionsDlg::execute(bool& doReread)
{
  
  bool result = exec() == QDialog::Accepted;
  if (result)
  {
    
    // translation or word
    bool translationInChoicesChecked = iTranslationRadioButton->isChecked();
    doReread = translationInChoicesChecked != QLangAssistSettings::isTranslationInChoices();
    QLangAssistSettings::setTranslationInChoices(translationInChoicesChecked);
    // number of choices
    int numOfChoices = iNumOfChoicesSelector->value();
    doReread |= QLangAssistSettings::numChoices() != numOfChoices;
    QLangAssistSettings::setNumChoices(numOfChoices);
  }
  return result;
}
