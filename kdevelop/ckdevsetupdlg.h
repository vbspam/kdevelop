/***************************************************************************
                     ckdevsetupdlg.h - the setup dialog for CKDevelop
                             -------------------                                         

    version              :                                   
    begin                : 17 Aug 1998                                        
    copyright            : (C) 1998 by Sandy Meier                         
    email                : smeier@rz.uni-potsdam.de                                     
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   * 
 *                                                                         *
 ***************************************************************************/
#ifndef __CKDEVSETUPDLG_H_
#define __CKDEVSETUPDLG_H_
#include <qlineedit.h>
#include <qbttngrp.h>
#include <qradiobt.h>
#include <qlistbox.h>
#include <qtabdialog.h>
#include <qmlined.h>
#include <kapp.h>
#include <qcombo.h>
#include <qlabel.h>
#include <qpushbt.h>
#include <kmsgbox.h>
#include <kfiledialog.h>
#include <kquickhelp.h>


/** the setup dialog for kdevelop
  *@author Sandy Meier
  */
class CKDevSetupDlg : public QTabDialog
{
    Q_OBJECT
public:
    CKDevSetupDlg( QWidget *parent=0, const char *name=0 );
private:
  KConfig* config;
  QLineEdit* kde_edit;
  
  QLineEdit* qt_edit;
 private slots:
 void        ok();
  void slotQtClicked();
  void slotKDEClicked();
  

};

#endif
