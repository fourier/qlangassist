######################################################################
# Automatically generated by qmake (2.01a) Tue Dec 7 20:54:47 2010
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
RESOURCES += qlangassist.qrc
RC_FILE = qlangassist.rc
ICON = qlangassist.icns

# Input
HEADERS += qlangassistmodel.h \
           qlangassistoptionsdlg.h \
           qlangassistsettings.h \
           qlangassistwidget.h \
           qlangassistwindow.h \
           qlangassistresultswindow.h \
           version.h \
           qlangassistdicteditwindow.h
SOURCES += main.cpp \
           qlangassistmodel.cpp \
           qlangassistoptionsdlg.cpp \
           qlangassistsettings.cpp \
           qlangassistwidget.cpp \
           qlangassistwindow.cpp \
           qlangassistresultswindow.cpp \
           qlangassistdicteditwindow.cpp

macx {
  QMAKE_POST_LINK += $${QMAKE_MKDIR} ./qlangassist.app/Contents/Frameworks;
  QMAKE_POST_LINK += $${QMAKE_COPY} -R /opt/local/libexec/qt4-mac//lib/QtGui.framework/Versions/4/Resources/qt_menu.nib ./qlangassist.app/Contents/Resources/qt_menu.nib;
  QMAKE_POST_LINK += $${QMAKE_COPY} /opt/local/libexec/qt4-mac/lib/QtGui.framework/Versions/4/QtGui ./qlangassist.app/Contents/Frameworks/QtGui;
  QMAKE_POST_LINK += $${QMAKE_COPY} /opt/local/libexec/qt4-mac/lib/QtCore.framework/Versions/4/QtCore ./qlangassist.app/Contents/Frameworks/QtCore;
  QMAKE_POST_LINK += install_name_tool -change /opt/local/libexec/qt4-mac/lib/QtGui.framework/Versions/4/QtGui @executable_path/../Frameworks/QtGui qlangassist.app/Contents/MacOS/qlangassist;
  QMAKE_POST_LINK += install_name_tool -change /opt/local/libexec/qt4-mac/lib/QtCore.framework/Versions/4/QtCore @executable_path/../Frameworks/QtCore qlangassist.app/Contents/MacOS/qlangassist;
}
  
