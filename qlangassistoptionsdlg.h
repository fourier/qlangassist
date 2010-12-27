// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#ifndef _QLANGASSISTOPTIONSDLG_H_
#define _QLANGASSISTOPTIONSDLG_H_

#include <QDialog>

class QRadioButton;
class QSlider;
class QLabel;

class QLangAssistOptionsDlg : public QDialog
{
  Q_OBJECT;
public:
  QLangAssistOptionsDlg(QWidget * parent = 0);
  bool execute(bool& doReread);
                                     
private slots:
  int exec ();
  void sliderMoved ( int value );
private:
  QRadioButton* iTranslationRadioButton;
  QRadioButton* iWordRadioButton;
  QSlider* iNumOfChoicesSelector;
  QLabel* iNumOfChoicesLabel;
};


#endif /* _QLANGASSISTOPTIONSDLG_H_ */
