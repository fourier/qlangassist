// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#ifndef _QLANGASSISTMODEL_H_
#define _QLANGASSISTMODEL_H_

#include <QHash>
#include <QString>
#include <QStringList>
#include <utility>


class IChoices
{
public:
  virtual ~IChoices(){}
  virtual void fillChoices(const QString& word, const QStringList& choices) = 0;
};

class QLangAssistModel : public QObject
{
  Q_OBJECT;
public:
  typedef QHash<QString,QString> DictionaryT;
  struct WrongAnswer
  {
    WrongAnswer(const QString& word, const QString& answered, const QString& correct)
      : iWord(word), iAnswered(answered), iCorrect(correct) {}
    QString iWord;
    QString iAnswered;
    QString iCorrect;
  };

  typedef QList<WrongAnswer> WrongAnswersListT;
  
public:
  QLangAssistModel();
  ~QLangAssistModel();
  bool readFile(const QString& fileName);
  bool writeFile(const QString& fileName);
  void start();
  void stop(WrongAnswersListT& wrongAnswers, int& numberOfQuestionsTotal);
  void fillChoices(IChoices& choices, int numOfCoices);
  int answer(const QString& word, const QString& translation);
  bool isEmpty() { return iDict.size() == 0; }
  const DictionaryT& dict() const { return iDict;}
  QLangAssistModel& setDictionary(const DictionaryT& dict) { clear(); iDict = dict; return *this; }
private:
  void processLine(const QString& line);
  void clear();
private:
  DictionaryT iDict;
  QList<WrongAnswer> iWrongAnswers;
  int iNumberOfQuestionsAsked;
  int iLastWordId;
};

#endif /* _QLANGASSISTMODEL_H_ */
