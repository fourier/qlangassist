// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#include <QApplication>
#include "qlangassistwindow.h"
#include "version.h"


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  // Setting the Application version
  app.setApplicationVersion(INTERNALVERSTR);
  app.setApplicationName(APPLICATION_NAME);

  QLangAssistWindow w;
  w.show();
  
  return app.exec();

}
