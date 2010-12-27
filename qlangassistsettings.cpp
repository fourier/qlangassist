#include <QSettings>

#include "qlangassistsettings.h"
#include "version.h"

const char* QLangAssistSettings::translationInChoicesKey = "isTranslationInChoices";
const char* QLangAssistSettings::numChoicesKey = "numberOfChoices";
const char* QLangAssistSettings::lastLoadedFileKey = "lastLoadedFile";
const char* QLangAssistSettings::sizeKey = "size";
const char* QLangAssistSettings::positionKey = "position";

bool QLangAssistSettings::isTranslationInChoices()
{
  QSettings settings(ORGANIZATION_NAME,APPLICATION_NAME);
  return settings.value(translationInChoicesKey,QVariant(true)).toBool();
}

int QLangAssistSettings::numChoices()
{
  QSettings settings(ORGANIZATION_NAME,APPLICATION_NAME);
  return settings.value(numChoicesKey,QVariant(3)).toInt();
}

void QLangAssistSettings::setTranslationInChoices(bool isTranslation)
{
  QSettings settings(ORGANIZATION_NAME,APPLICATION_NAME);
  settings.setValue(translationInChoicesKey,isTranslation);
}

void QLangAssistSettings::setNumChoices(int numberOfChoices)
{
  QSettings settings(ORGANIZATION_NAME,APPLICATION_NAME);
  settings.setValue(numChoicesKey,numberOfChoices);
}

QString QLangAssistSettings::lastLoadedFile()
{
  QSettings settings(ORGANIZATION_NAME,APPLICATION_NAME);
  return settings.value(lastLoadedFileKey).toString();
}

void QLangAssistSettings::setLastLoadedFile(const QString& fileName)
{
  QSettings settings(ORGANIZATION_NAME,APPLICATION_NAME);
  settings.setValue(lastLoadedFileKey,fileName);
}

QSize QLangAssistSettings::windowSize()
{
  QSettings settings(ORGANIZATION_NAME,APPLICATION_NAME);
  return settings.value(sizeKey,QSize(200,200)).toSize();
}

void QLangAssistSettings::setWindowSize(const QSize& size)
{
  QSettings settings(ORGANIZATION_NAME,APPLICATION_NAME);
  settings.setValue(sizeKey,size);
}

QPoint QLangAssistSettings::windowPosition()
{
  QSettings settings(ORGANIZATION_NAME,APPLICATION_NAME);
  return settings.value(positionKey,QPoint(200,200)).toPoint();
}

void QLangAssistSettings::setWindowPosition(const QPoint& point)
{
  QSettings settings(ORGANIZATION_NAME,APPLICATION_NAME);
  settings.setValue(positionKey,point);
}
