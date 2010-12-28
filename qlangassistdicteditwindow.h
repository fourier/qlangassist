// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#ifndef _QLANGASSISTDICTEDITWINDOW_H_
#define _QLANGASSISTDICTEDITWINDOW_H_

#include <QDialog>


#include "qlangassistmodel.h"

class QTableView;



class QLangAssistDictEditWindow : public QDialog
{
  Q_OBJECT;
public:
  typedef QDialog Parent;
public:
  QLangAssistDictEditWindow(const QLangAssistModel::DictionaryT& dict, QWidget* parent = 0);
  const QLangAssistModel::DictionaryT& dict() const { return iDict; }
public slots:
  void okButtonPressed();
private:
  QLangAssistModel::DictionaryT iDict;
  QTableView* iTable;
};

#endif /* _QLANGASSISTDICTEDITWINDOW_H_ */