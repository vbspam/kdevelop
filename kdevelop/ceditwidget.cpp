/***************************************************************************
               ceditwidget.cpp  -  a abstraction layer for an editwidget   
                             -------------------                                         

    begin                : 23 Aug 1998                                        
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
#include "ceditwidget.h"
#include <iostream.h>
#include "./kwrite/kwdoc.h"
#include "./kwrite/highlight.h"
#include <qpopupmenu.h>
#include <qclipboard.h>
#include <assert.h>

HlManager hlManager; //highlight manager

CEditWidget::CEditWidget(KApplication*,QWidget* parent,char* name)
  : KWrite(new KWriteDoc(&hlManager),parent,name) {
  
  setFocusProxy (kWriteView); 
  pop = new QPopupMenu();
  //  pop->insertItem(i18n("Open: "),this,SLOT(open()),0,6);
  pop->insertItem(i18n("Undo"),this,SLOT(undo()),0,4);
  pop->insertItem(i18n("Redo"),this,SLOT(redo()),0,5);
  pop->insertSeparator();
  pop->insertItem(i18n("Cut"),this,SLOT(cut()),0,1);
  pop->insertItem(i18n("Copy"),this,SLOT(copy()),0,2);
  pop->insertItem(i18n("Paste"),this,SLOT(paste()),0,3);
  pop->setItemEnabled(1,false);
  pop->setItemEnabled(2,false);
  pop->setItemEnabled(3,false);
  pop->insertSeparator();
  pop->insertItem("",this,SLOT(slotLookUp()),0,0);
  bookmarks.setAutoDelete(true);


}

CEditWidget::~CEditWidget() {
  delete doc();
}

void CEditWidget::setName(QString filename){
  // this->filename = filename;
  KWrite::setFileName(filename);
}
QString CEditWidget::getName(){
  //return filename;
  QString s(KWrite::fileName());
  if (s.isNull()) s = "";
  return s;//QString(KWrite::fileName());
}
QString CEditWidget::text(){
  return KWrite::text();
}
void CEditWidget::setText(QString &text){
  KWrite::setText(text);
}
QString CEditWidget::markedText(){
  return KWrite::markedText();
}
int CEditWidget::loadFile(QString filename, int mode) {
  KWrite::loadFile(filename);
  return 0;
}
void CEditWidget::doSave() {
  KWrite::save();
}
void CEditWidget::doSave(QString filename){
  KWrite::writeFile(filename);
}
void CEditWidget::copyText() {
  KWrite::copy();
}
void CEditWidget::setFocus(){
  KWrite::setFocus();
  kWriteView->setFocus();
}
void CEditWidget::gotoPos(int pos,QString text_str){
  
  //  cerr << endl << "POS: " << pos;
  // calculate the line
  QString last_textpart = text_str.right(text_str.size()-pos); // the second part of the next,after the pos
  int line = text_str.contains("\n") - last_textpart.contains("\n");
  //  cerr << endl << "LINE:" << line;
  setCursorPosition(line,0);
  setFocus();
}
void CEditWidget::toggleModified(bool mod){
  KWrite::setModified(mod);
}
void CEditWidget::search(){
  KWrite::search();
}
void CEditWidget::searchAgain(){
  KWrite::searchAgain();
}
void CEditWidget::replace(){
  KWrite::replace();
}
void CEditWidget::gotoLine(){
  KWrite::gotoLine();
}
void CEditWidget::indent(){
  KWrite::indent();
}
void CEditWidget::unIndent(){
  KWrite::unIndent();
}
void CEditWidget::invertSelection(){
  KWrite::invertSelection();
}
void CEditWidget::deselectAll(){
  KWrite::deselectAll();
}


void CEditWidget::spellcheck(){
   kspell= new KSpell (this, "KDevelop: Spellcheck", this,
		   SLOT (spellcheck2 (KSpell *)));	
}

void CEditWidget::spellcheck2(KSpell *){
    if (kspell->isOk())
      {

//	setReadOnly (TRUE);

/*	connect (kspell, SIGNAL (misspelling (char *, QStrList *, unsigned)),
		 this, SLOT (misspelling (char *, QStrList *, unsigned)));
	connect (kspell, SIGNAL (corrected (char *,
						 char *, unsigned)),
		 this, SLOT (corrected (char *,
					char *, unsigned)));

       connect (kspell, SIGNAL (progress (unsigned int)),
                this, SIGNAL (spellcheck_progress (unsigned int)) );

	connect (kspell, SIGNAL (done(char *)),
		 this, SLOT (spellResult (char *)));
	
	kspell->setProgressResolution (2);
*/
	kspell->check (text().data());
	
      }
/*    else
      {
	KMsgBox::message(this,"KEdit: Error","Error starting KSpell.\n"\
			 "Please make sure you have ISpell properly configured and in your PATH.", KMsgBox::STOP);
      }*/
}

/** Insert the string at the supplied line. */
void CEditWidget::insertAtLine( const char *toInsert, uint atLine )
{
  assert( toInsert != NULL );
  assert( atLine >= 0 );
  
  uint line=0;
  int pos=0;
  QString txt;
  
  txt = text();
  while( line < atLine )
    {
    pos++;
    if( txt[ pos ] == '\n' )
      line++;
    }
  
  // Insert the text after the last return.
  txt.insert( pos + 1, toInsert );
  setText( txt );
}

/** Append a text at the end of the file. */
void CEditWidget::append( const char *toAdd )
{
  QString txt;
  
  txt = text();
  txt.append( toAdd );
  setText( txt );
}

/** Returns the number of lines in the text. */
uint CEditWidget::lines()
{
  return (uint)(text().contains('\n', false));
}


void CEditWidget::enterEvent ( QEvent * e){
  setFocus();
}
void CEditWidget::mousePressEvent(QMouseEvent* event){
  if(event->button() == RightButton){
    
    if(event->state() & ControlButton) {
      emit bufferMenu(this->mapToGlobal(event->pos()));
      return;
    }
    
    int state;
    state = undoState();
    //undo
    if(state & 1){
      pop->setItemEnabled(4,true);
    }
    else{
      pop->setItemEnabled(4,false);
    }
    //redo
    if(state & 2){
      pop->setItemEnabled(5,true);
    }
    else{
      pop->setItemEnabled(5,false);
    }
    
    QString str = markedText();
    if(!str.isEmpty()){
      pop->setItemEnabled(1,true);
      pop->setItemEnabled(2,true);
    }
    else{
      pop->setItemEnabled(1,false);
      pop->setItemEnabled(2,false);
    }		


    QClipboard *cb = kapp->clipboard();
    QString text=cb->text();
    if(text.isEmpty())
      pop->setItemEnabled(3,false);
    else
      pop->setItemEnabled(3,true);
    
    if(str == ""){
      str = word(event->x(),event->y());
    }
    searchtext = str;
    if(str.length() > 20 ){
      str = str.left(20) + "...";
    }
    pop->changeItem(i18n("look up: ") + str,0); // the lookup entry


    pop->popup(this->mapToGlobal(event->pos()));
  }
}

void CEditWidget::slotLookUp(){
    emit lookUp(searchtext);
}

