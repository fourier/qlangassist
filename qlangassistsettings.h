// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#ifndef _QLANGASSISTSETTINGS_H_
#define _QLANGASSISTSETTINGS_H_

#include <QString>
#include <QSize>
#include <QPoint>

class QLangAssistSettings
{
public:
  static bool isTranslationInChoices();
  static void setTranslationInChoices(bool isTranslation);
  static int  numChoices();
  static int  maxNumOfChoices() { return 10; }
  static void setNumChoices(int numberOfChoices);
  static QString lastLoadedFile();
  static void setLastLoadedFile(const QString& fileName);
  static QSize windowSize();
  static void setWindowSize(const QSize& size);
  static QPoint windowPosition();
  static void setWindowPosition(const QPoint& point);

private:
  static const char* translationInChoicesKey;
  static const char* numChoicesKey;
  static const char* lastLoadedFileKey;
  static const char* sizeKey;
  static const char* positionKey;
};

#endif /* _QLANGASSISTSETTINGS_H_ */
