// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#include "qlangassistwidget.h"

#include <QLabel>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>


QLangAssistWidget::QLangAssistWidget(QWidget* parent) :
  ParentT(parent)
{
  // Label
  iPhrase = new QLabel("betydor");
  

  iChoices = new QGroupBox(tr("Choose correct translation:"));

  QRadioButton *radio1 = new QRadioButton(tr("&Radio button 1"));
  QRadioButton *radio2 = new QRadioButton(tr("R&adio button 2"));
  QRadioButton *radio3 = new QRadioButton(tr("<font color=green>Ra&dio button 3</font>"));

  radio1->setChecked(true);

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(radio1);
  vbox->addWidget(radio2);
  vbox->addWidget(radio3);
  vbox->addStretch(1);
  iChoices->setLayout(vbox);

  iNextButton = new QPushButton(tr("Next"));
  
  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget(iPhrase);
  layout->addWidget(iChoices);
  layout->addWidget(iNextButton);
  setLayout(layout);
}

QLangAssistWidget::~QLangAssistWidget()
{
}
