/***************************************************************************
               cclasstooldlg.cpp  -  description

                             -------------------

    begin                : Fri Mar 19 1999

    copyright            : (C) 1999 by Jonas Nordin
    email                : jonas.nordin@cenacle.se

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "cclasstooldlg.h"
#include <kmsgbox.h>
#include <kapp.h>
#include <qtooltip.h>
#include <assert.h>
#include <qlistbox.h>

/*********************************************************************
 *                                                                   *
 *                     CREATION RELATED METHODS                      *
 *                                                                   *
 ********************************************************************/

CClassToolDlg::CClassToolDlg( QWidget *parent, const char *name )
  : QDialog( parent, name, true ),
    classLbl( this, "classLbl" ),
    classCombo( false, this, "classCombo" ),
    parentsBtn( this, "parentsBtn" ),
    childrenBtn( this, "childrenBtn" ),
    clientsBtn( this, "clientsBtn" ),
    suppliersBtn( this, "suppliersBtn" ),
    attributesBtn( this, "attributesBtn" ),
    methodsBtn( this, "methodsBtn" ),
    virtualsBtn( this, "virtualsBtn" ),
    exportCombo( false, this, "exportCombo" ),
    classTree( this, "classTree" )
{
  currentOperation = CTNONE;
  comboExport = CTHALL;
  onlyVirtual = false;
  store = NULL;

  setCaption( "Class Tool" );

  treeH.setTree( &classTree );

  setWidgetValues();
  readIcons();
  setCallbacks();
  setTooltips();
}


/*********************************************************************
 *                                                                   *
 *                          PRIVATE METHODS                          *
 *                                                                   *
 ********************************************************************/

void CClassToolDlg::setWidgetValues()
{
  classLbl.setGeometry( 10, 10, 40, 30 );
  classLbl.setMinimumSize( 0, 0 );
  classLbl.setMaximumSize( 32767, 32767 );
  classLbl.setFocusPolicy( QWidget::NoFocus );
  classLbl.setBackgroundMode( QWidget::PaletteBackground );
  classLbl.setFontPropagation( QWidget::NoChildren );
  classLbl.setPalettePropagation( QWidget::NoChildren );
  classLbl.setText( "Class:" );
  classLbl.setAlignment( 289 );
  classLbl.setMargin( -1 );

  classCombo.setGeometry( 50, 10, 260, 30 );
  classCombo.setMinimumSize( 0, 0 );
  classCombo.setMaximumSize( 32767, 32767 );
  classCombo.setFocusPolicy( QWidget::StrongFocus );
  classCombo.setBackgroundMode( QWidget::PaletteBackground );
  classCombo.setFontPropagation( QWidget::AllChildren );
  classCombo.setPalettePropagation( QWidget::AllChildren );
  classCombo.setSizeLimit( 10 );
  classCombo.setAutoResize( FALSE );

  parentsBtn.setGeometry( 10, 50, 30, 30 );
  parentsBtn.setMinimumSize( 0, 0 );
  parentsBtn.setMaximumSize( 32767, 32767 );
  parentsBtn.setFocusPolicy( QWidget::TabFocus );
  parentsBtn.setBackgroundMode( QWidget::PaletteBackground );
  parentsBtn.setFontPropagation( QWidget::NoChildren );
  parentsBtn.setPalettePropagation( QWidget::NoChildren );
  parentsBtn.setAutoRepeat( FALSE );
  parentsBtn.setAutoResize( FALSE );

  childrenBtn.setGeometry( 50, 50, 30, 30 );
  childrenBtn.setMinimumSize( 0, 0 );
  childrenBtn.setMaximumSize( 32767, 32767 );
  childrenBtn.setFocusPolicy( QWidget::TabFocus );
  childrenBtn.setBackgroundMode( QWidget::PaletteBackground );
  childrenBtn.setFontPropagation( QWidget::NoChildren );
  childrenBtn.setPalettePropagation( QWidget::NoChildren );
  childrenBtn.setText( "" );
  childrenBtn.setAutoRepeat( FALSE );
  childrenBtn.setAutoResize( FALSE );

  clientsBtn.setGeometry( 90, 50, 30, 30 );
  clientsBtn.setMinimumSize( 0, 0 );
  clientsBtn.setMaximumSize( 32767, 32767 );
  clientsBtn.setFocusPolicy( QWidget::TabFocus );
  clientsBtn.setBackgroundMode( QWidget::PaletteBackground );
  clientsBtn.setFontPropagation( QWidget::NoChildren );
  clientsBtn.setPalettePropagation( QWidget::NoChildren );
  clientsBtn.setText( "" );
  clientsBtn.setAutoRepeat( FALSE );
  clientsBtn.setAutoResize( FALSE );

  suppliersBtn.setGeometry( 130, 50, 30, 30 );
  suppliersBtn.setMinimumSize( 0, 0 );
  suppliersBtn.setMaximumSize( 32767, 32767 );
  suppliersBtn.setFocusPolicy( QWidget::TabFocus );
  suppliersBtn.setBackgroundMode( QWidget::PaletteBackground );
  suppliersBtn.setFontPropagation( QWidget::NoChildren );
  suppliersBtn.setPalettePropagation( QWidget::NoChildren );
  suppliersBtn.setText( "" );
  suppliersBtn.setAutoRepeat( FALSE );
  suppliersBtn.setAutoResize( FALSE );

  attributesBtn.setGeometry( 190, 50, 30, 30 );
  attributesBtn.setMinimumSize( 0, 0 );
  attributesBtn.setMaximumSize( 32767, 32767 );
  attributesBtn.setFocusPolicy( QWidget::TabFocus );
  attributesBtn.setBackgroundMode( QWidget::PaletteBackground );
  attributesBtn.setFontPropagation( QWidget::NoChildren );
  attributesBtn.setPalettePropagation( QWidget::NoChildren );
  attributesBtn.setText( "" );
  attributesBtn.setAutoRepeat( FALSE );
  attributesBtn.setAutoResize( FALSE );

  methodsBtn.setGeometry( 230, 50, 30, 30 );
  methodsBtn.setMinimumSize( 0, 0 );
  methodsBtn.setMaximumSize( 32767, 32767 );
  methodsBtn.setFocusPolicy( QWidget::TabFocus );
  methodsBtn.setBackgroundMode( QWidget::PaletteBackground );
  methodsBtn.setFontPropagation( QWidget::NoChildren );
  methodsBtn.setPalettePropagation( QWidget::NoChildren );
  methodsBtn.setText( "" );
  methodsBtn.setAutoRepeat( FALSE );
  methodsBtn.setAutoResize( FALSE );

  virtualsBtn.setGeometry( 270, 50, 30, 30 );
  virtualsBtn.setMinimumSize( 0, 0 );
  virtualsBtn.setMaximumSize( 32767, 32767 );
  virtualsBtn.setFocusPolicy( QWidget::TabFocus );
  virtualsBtn.setBackgroundMode( QWidget::PaletteBackground );
  virtualsBtn.setFontPropagation( QWidget::NoChildren );
  virtualsBtn.setPalettePropagation( QWidget::NoChildren );
  virtualsBtn.setText( "" );
  virtualsBtn.setAutoRepeat( FALSE );
  virtualsBtn.setAutoResize( FALSE );

  exportCombo.setGeometry( 310, 50, 100, 30 );
  exportCombo.setMinimumSize( 0, 0 );
  exportCombo.setMaximumSize( 32767, 32767 );
  exportCombo.setFocusPolicy( QWidget::StrongFocus );
  exportCombo.setBackgroundMode( QWidget::PaletteBackground );
  exportCombo.setFontPropagation( QWidget::AllChildren );
  exportCombo.setPalettePropagation( QWidget::AllChildren );
  exportCombo.setSizeLimit( 10 );
  exportCombo.setAutoResize( FALSE );
  exportCombo.insertItem( "All" );
  exportCombo.insertItem( "Public" );
  exportCombo.insertItem( "Protected" );
  exportCombo.insertItem( "Private" );

  classTree.setGeometry( 10, 90, 500, 400 );
  classTree.setIndentSpacing(15);
  classTree.setFocusPolicy(QWidget::NoFocus);
}

void CClassToolDlg::readIcons()
{
  QString PIXPREFIX = "/kdevelop/pics/mini/";
  QString pixDir = KApplication::kde_datadir() + PIXPREFIX;
  QPixmap pm;
  
  pm.load( pixDir + "CTparents.xpm" );
  parentsBtn.setPixmap( pm );
  
  pm.load( pixDir + "CTchildren.xpm" );
  childrenBtn.setPixmap( pm );

  pm.load( pixDir + "CTclients.xpm" );
  clientsBtn.setPixmap( pm );

  pm.load( pixDir + "CTsuppliers.xpm" );
  suppliersBtn.setPixmap( pm );

  pm.load( pixDir + "CVpublic_var.xpm" );
  attributesBtn.setPixmap( pm );

  pm.load( pixDir + "CVpublic_meth.xpm" );
  methodsBtn.setPixmap( pm );

  pm.load( pixDir + "CTvirtuals.xpm" );
  virtualsBtn.setPixmap( pm );
}

void CClassToolDlg::setTooltips()
{
  QToolTip::add( &parentsBtn, "View parents" );
  QToolTip::add( &childrenBtn, "View children" );
  QToolTip::add( &clientsBtn, "View clients" );
  QToolTip::add( &suppliersBtn, "View suppliers" );
  QToolTip::add( &attributesBtn, "View attributes" );
  QToolTip::add( &methodsBtn, "View methods" );
  QToolTip::add( &virtualsBtn, "View virtual methods" );
}

void CClassToolDlg::setCallbacks()
{
  connect( &classCombo, SIGNAL(activated(int)), SLOT(slotClassComboChoice(int)));
  connect( &exportCombo, SIGNAL(activated(int)), SLOT(slotExportComboChoice(int)));
  connect( &parentsBtn, SIGNAL(clicked()), SLOT(slotParents()));
  connect( &childrenBtn, SIGNAL(clicked()), SLOT(slotChildren()));
  connect( &clientsBtn, SIGNAL(clicked()), SLOT(slotClients()));
  connect( &suppliersBtn, SIGNAL(clicked()), SLOT(slotSuppliers()));
  connect( &methodsBtn, SIGNAL(clicked()), SLOT(slotMethods()));
  connect( &attributesBtn, SIGNAL(clicked()), SLOT(slotAttributes()));
  connect( &virtualsBtn, SIGNAL(clicked()), SLOT(slotVirtuals()));
}

void CClassToolDlg::setActiveClass( const char *aName )
{
  QListBox *lb;
  uint i;

  lb = classCombo.listBox();

  for( i=0; i < lb->count() && strcmp( lb->text( i ), aName ) != 0; i++ )
    ;

  classCombo.setCurrentItem( i );
}

/*********************************************************************
 *                                                                   *
 *                    METHODS TO SET ATTRIBUTE VALUES                *
 *                                                                   *
 ********************************************************************/

void CClassToolDlg::setStore( CClassStore *aStore )
{
  assert( aStore != NULL );

  QListBox *lb;

  store = aStore;

  // Set the store in the treehandler as weel.
  treeH.setStore( store );

  lb = classCombo.listBox();

  // Add all classnames in sorted order.
  for( store->classIterator.toFirst();
       store->classIterator.current();
       ++(store->classIterator) )
    lb->inSort( store->classIterator.current()->name );
}

void CClassToolDlg::setClass( const char *aName )
{
  assert( aName != NULL && strlen( aName ) > 0 );
  assert( store != NULL );

  setActiveClass( aName );
  currentClass = store->getClassByName( aName );
}

void CClassToolDlg::setClass( CParsedClass *aClass )
{
  assert( aClass != NULL );

  setActiveClass( aClass->name );
  currentClass = aClass;
}

void CClassToolDlg::addClasses( QList<CParsedClass> *list )
{
  CParsedClass *aClass;
  KPath classPath;

  // Clear all previous items in the tree.
  classTree.clear();

  // Insert root item(the current class);
  classTree.insertItem( currentClass->name, treeH.getIcon( CVCLASS ) );
  classPath.push( &currentClass->name );

  for( aClass = list->first();
       aClass != NULL;
       aClass = list->next() )
  {
    treeH.addClass( aClass, classPath );
  }

  // View one level deep.
  classTree.setExpandLevel( 1 );
}

void CClassToolDlg::addClassAndAttributes( CParsedClass *aClass )
{
  KPath classPath;
  
  // Insert root item(the current class);
  classTree.insertItem( aClass->name, treeH.getIcon( CVCLASS ) );
  classPath.push( &aClass->name );

  treeH.addAttributesFromClass( aClass, classPath, comboExport );
}

void CClassToolDlg::addClassAndMethods( CParsedClass *aClass )
{
  KPath classPath;
  
  // Insert root item(the current class);
  classTree.insertItem( aClass->name, treeH.getIcon( CVCLASS ) );
  classPath.push( &aClass->name );

  treeH.addMethodsFromClass( aClass, classPath, comboExport );
}

void CClassToolDlg::addAllClassMethods()
{
  CParsedParent *aParent;
  CParsedClass *aClass;

  // Clear all previous items in the tree.
  classTree.clear();

  // First treat all parents.
  for( aParent = currentClass->parents.first();
       aParent != NULL;
       aParent = currentClass->parents.next() )
  {
    aClass = store->getClassByName( aParent->name );
    if( aClass != NULL )
      addClassAndMethods( aClass );
  }

  // Add the current class
  addClassAndMethods( currentClass );

  // View one level deep.
  classTree.setExpandLevel( 1 );
}

void CClassToolDlg::addAllClassAttributes()
{
  CParsedParent *aParent;
  CParsedClass *aClass;

  // Clear all previous items in the tree.
  classTree.clear();
  
  // First treat all parents.
  for( aParent = currentClass->parents.first();
       aParent != NULL;
       aParent = currentClass->parents.next() )
  {
    aClass = store->getClassByName( aParent->name );
    if( aClass != NULL )
      addClassAndAttributes( aClass );
  }

  // Add the current class
  addClassAndAttributes( currentClass );

  classTree.setExpandLevel( 1 );
}

/** Change the caption depending on the current operation. */
void CClassToolDlg::changeCaption()
{
  QString caption;

  switch( currentOperation )
  {
    case CTPARENT:
      caption = "Parents";
      break;
    case CTCHILD:
      caption = "Children";
      break;
    case CTCLIENT:
      caption = "Clients";
      break;
    case CTSUPP:
      caption = "Suppliers";
      break;
    case CTATTR:
      caption = exportCombo.currentText();
      caption += " attributes";
      break;
    case CTMETH:
      caption = exportCombo.currentText();
      caption += " methods";
      break;
    case CTVIRT:
      caption = exportCombo.currentText();
      caption += " virtual methods";
      break;
  }

  caption += " of class ";
  caption += currentClass->name;

  setCaption( caption );
}

/*********************************************************************
 *                                                                   *
 *                          PUBLIC METHODS                           *
 *                                                                   *
 ********************************************************************/

/** View the parents of the current class. */
void CClassToolDlg::viewParents()
{
  CParsedParent *aParent;
  KPath classPath;
  
  currentOperation = CTPARENT;

  changeCaption();

  classTree.clear();
  
  // Insert root item(the current class);
  classTree.insertItem( currentClass->name, treeH.getIcon( CVCLASS ) );
  classPath.push( &currentClass->name );

  for( aParent = currentClass->parents.first();
       aParent != NULL;
       aParent = currentClass->parents.next() )
  {
    classTree.addChildItem( aParent->name, treeH.getIcon( CVCLASS ),
                            &classPath );
  }

  classTree.setExpandLevel( 1 );
}

/** View the children of the current class. */
void CClassToolDlg::viewChildren()
{
  assert( currentClass != NULL );

  QList<CParsedClass> *list;
  
  currentOperation = CTCHILD;
  changeCaption();

  list = store->getClassesByParent( currentClass->name );
  addClasses( list );
  delete list;
}

/** View all classes that has this class as an attribute. */
void CClassToolDlg::viewClients()
{
  assert( currentClass != NULL );

  QList<CParsedClass> *list;
  
  currentOperation = CTCLIENT;
  changeCaption();

  list = store->getClassClients( currentClass->name );
  addClasses( list );
  delete list;
}

/** View all classes that this class has as attributes. */
void CClassToolDlg::viewSuppliers()
{
  assert( currentClass != NULL );

  QList<CParsedClass> *list;

  currentOperation = CTSUPP;
  changeCaption();

  list = store->getClassSuppliers( currentClass->name );
  addClasses( list );
  delete list;
}

/** View methods in this class and parents. */
void CClassToolDlg::viewMethods()
{
  assert( currentClass != NULL );

  currentOperation = CTMETH;

  changeCaption();  
  addAllClassMethods();
}

/** View attributes in this class and parents. */
void CClassToolDlg::viewAttributes()
{
  assert( currentClass != NULL );

  currentOperation = CTATTR;

  changeCaption();
  addAllClassAttributes();
}

void CClassToolDlg::viewVirtuals()
{
  assert( currentClass != NULL );

  QString caption;

  currentOperation = CTVIRT;

  changeCaption();

  onlyVirtual = true;
  addAllClassMethods();
  onlyVirtual = false;
}

/*********************************************************************
 *                                                                   *
 *                              SLOTS                                *
 *                                                                   *
 ********************************************************************/

void CClassToolDlg::slotParents()
{
  viewParents();
}
void CClassToolDlg::slotChildren()
{
  viewChildren();
}

void CClassToolDlg::slotClients()
{
  viewClients();
}

void CClassToolDlg::slotSuppliers()
{
  viewSuppliers();
}

void CClassToolDlg::slotAttributes()
{
  viewAttributes();
}

void CClassToolDlg::slotMethods()
{
  viewMethods();
}

void CClassToolDlg::slotVirtuals()
{
  viewVirtuals();
}

void CClassToolDlg::slotExportComboChoice(int idx)
{
  QString str;

  str = exportCombo.currentText();

  //Check exporttype
  if( str == "All" )
    comboExport = CTHALL;
  else if( str == "Public" )
    comboExport = CTHPUBLIC;
  else if( str == "Protected" )
    comboExport = CTHPROTECTED;
  else if( str == "Private" )
    comboExport = CTHPRIVATE;

  // Update the view if the choice affected the data.
  switch( currentOperation )
  {
    case CTATTR:
      viewAttributes();
      break;
    case CTMETH:
      viewMethods();
      break;
    case CTVIRT:
      viewVirtuals();
      break;
  }
}

void CClassToolDlg::slotClassComboChoice(int idx)
{
  setClass( classCombo.currentText() );
  // Update the view if the choice affected the data.
  switch( currentOperation )
  {
    case CTPARENT:
      viewParents();
      break;
    case CTCHILD:
      viewChildren();
      break;
    case CTCLIENT:
      viewClients();
      break;
    case CTSUPP:
      viewSuppliers();
      break;
    case CTATTR:
      viewAttributes();
      break;
    case CTMETH:
      viewMethods();
      break;
    case CTVIRT:
      viewVirtuals();
      break;
  }
}

void CClassToolDlg::OK()
{
  accept();
}
