/***************************************************************************
                          KDevClassStore.cpp  -  description
                             -------------------
    begin                : Wed Feb 14 2001
    copyright            : (C) 2001 by Omid Givi
    email                : omid@givi.nl
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "KDevClassStore.h"


KDevClassStore::KDevClassStore(QObject *parent, const char *name)
    : KDevComponent(parent, name){
}

KDevClassStore::~KDevClassStore(){
}

void KDevClassStore::wipeout(){
}

#include "KDevClassStore.moc"
