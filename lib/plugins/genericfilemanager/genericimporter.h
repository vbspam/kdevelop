/* This file is part of KDevelop
    Copyright (C) 2004,2005 Roberto Raggi <roberto@kdevelop.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/
#ifndef KDEVGENERICIMPORTER_H
#define KDEVGENERICIMPORTER_H

#include "iprojectfilemanager.h"
#include "iplugin.h"

class QFileInfo;
class QStringList;
class KUrl;
template <typename T> class QList;
namespace KDevelop
{
class ProjectBaseItem;
class ProjectFolderItem;
class ProjectFileItem;
}

class KDialogBase;

class GenericImporter: public KDevelop::IPlugin, public KDevelop::IProjectFileManager
{
    Q_OBJECT
    Q_INTERFACES( KDevelop::IProjectFileManager )
public:
    GenericImporter( QObject *parent = 0,
                     const QStringList &args = QStringList() );
    virtual ~GenericImporter();

//
// IProjectFileManager interface
//
    virtual Features features() const
    {
        return Features( Folders | Files );
    }

    virtual KDevelop::ProjectFolderItem* addFolder( const KUrl& folder, KDevelop::ProjectFolderItem *parent );
    virtual KDevelop::ProjectFileItem* addFile( const KUrl& file, KDevelop::ProjectFolderItem *parent );
    virtual bool removeFolder( KDevelop::ProjectFolderItem *folder );
    virtual bool removeFile( KDevelop::ProjectFileItem *file );
    virtual bool renameFolder( KDevelop::ProjectFolderItem *folder, const KUrl& url );
    virtual bool renameFile( KDevelop::ProjectFileItem *file, const KUrl& url );

    virtual QList<KDevelop::ProjectFolderItem*> parse( KDevelop::ProjectFolderItem *item );
    virtual KDevelop::ProjectItem *import( KDevelop::IProject *project );

    void registerExtensions();
    void unregisterExtensions();
    QStringList extensions() const;

Q_SIGNALS:
    void projectItemConfigWidget(const QList<KDevelop::ProjectBaseItem*> &dom, KDialogBase *dialog);

    void folderAdded( KDevelop::ProjectFolderItem* folder );
    void folderRemoved( KDevelop::ProjectFolderItem* folder );
    void folderRenamed( const KUrl& oldFolder,
                        KDevelop::ProjectFolderItem* newFolder );

    void fileAdded(KDevelop::ProjectFileItem* file);
    void fileRemoved(KDevelop::ProjectFileItem* file);
    void fileRenamed(const KUrl& oldFile,
                     KDevelop::ProjectFileItem* newFile);

private:
    bool isValid( const QFileInfo &fileName ) const;

private:
    struct GenericImporterPrivate* const d;
};

#endif // KDEVGENERICIMPORTER_H
//kate: space-indent on; indent-width 4; replace-tabs on; auto-insert-doxygen on; indent-mode cstyle;
