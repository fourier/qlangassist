// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#include "qlangassistmodel.h"
#include <cmath>
#include <algorithm>
#include <QDebug>
#include <ctime>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include "qlangassistsettings.h"



QLangAssistModel::QLangAssistModel() :
  QObject(), iNumberOfQuestionsAsked(0)
{
}


QLangAssistModel::~QLangAssistModel()
{
}

void QLangAssistModel::start()
{
  srand(time(0));
  iNumberOfQuestionsAsked = 0;
  iWrongAnswers.clear();
}

void QLangAssistModel::clear()
{
  iNumberOfQuestionsAsked = 0;
  iWrongAnswers.clear();
  iDict.clear();
}

void QLangAssistModel::stop(WrongAnswersListT& wrongAnswers, int& numberOfQuestionsTotal)
{
  wrongAnswers = iWrongAnswers;
  numberOfQuestionsTotal = iNumberOfQuestionsAsked;
  
  iNumberOfQuestionsAsked = 0;
  iWrongAnswers.clear();
}

void QLangAssistModel::fillChoices(IChoices& choices, int numOfCoices)
{

  QList<QString> words;
  QList<QString> translations;
  if (QLangAssistSettings::isTranslationInChoices())
  {
    words  = iDict.keys();
    translations = iDict.values();
  }
  else
  {
    words  = iDict.values();
    translations = iDict.keys();
  }
  QStringList answers;
  int wordId = (int) (((double) words.size()) * rand() / (RAND_MAX + 1.0));
  QString word = words[wordId];
  QString wordTranslation = translations[wordId];
  translations.removeAll(wordTranslation);
  std::random_shuffle(words.begin(),words.end());
  for ( ; numOfCoices > 1; --numOfCoices)
  {
    answers.append(translations.first());
    translations.pop_front();
  }
  answers.append(wordTranslation);

  std::random_shuffle(answers.begin(),answers.end());
  qDebug() << word << wordTranslation;
  qDebug() << answers;
  
  choices.fillChoices(word,answers);
}

int QLangAssistModel::answer(const QString& word, const QString& translation)
{
  iNumberOfQuestionsAsked++;
  QString correctTranslation;
  if (QLangAssistSettings::isTranslationInChoices())
    correctTranslation = iDict[word];
  else
    correctTranslation = iDict.key(word);
  if (correctTranslation != translation)
    iWrongAnswers.append(WrongAnswer(word,translation,correctTranslation));
  return iNumberOfQuestionsAsked;
}


bool QLangAssistModel::readFile(const QString& fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return false;
  QTextStream stream(&file);
  stream.setCodec(QTextCodec::codecForName("UTF-8"));
  stream.setAutoDetectUnicode(true);
  clear();
  QString line;
  do
  {
    line = stream.readLine();
    processLine(line);
  } while (!line.isNull());
  if (iDict.size() < 4)
    return false;
  return true;
}


void QLangAssistModel::processLine(const QString& line)
{
  // trim whitespace around the line
  QString textLine = line.simplified();
  // do not process comments
  if (textLine[0] == '#')
    return;
  QString word,translation;
  word = textLine.section("---",0,0).simplified();
  translation = textLine.section("---",1,1).simplified();
  if (word.length() && translation.length())
    iDict[word] = translation;
}


bool QLangAssistModel::writeFile(const QString& fileName)
{
  return false;
}
