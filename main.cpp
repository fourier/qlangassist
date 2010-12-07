// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#include <QApplication>
#include "qlangassistwindow.h"


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QLangAssistWindow w;
  w.show();
  
  return app.exec();

}
