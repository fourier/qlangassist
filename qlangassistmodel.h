// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#ifndef _QLANGASSISTMODEL_H_
#define _QLANGASSISTMODEL_H_

#include <QHash>
#include <QString>


class QLangAssistModel : public QObject
{
  Q_OBJECT;
  typedef QHash<QString,QString> DictionaryT;
public:
  QLangAssistModel();
  ~QLangAssistModel();
  void readFile(const QString& fileName);

private:
  DictionaryT iDict;
};

#endif /* _QLANGASSISTMODEL_H_ */
