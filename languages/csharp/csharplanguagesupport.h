/* This file is part of KDevelop
Copyright (C) 2006 Adam Treat <treat@kde.org>

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

#ifndef KDEVCSHARPLANGUAGESUPPORT_H
#define KDEVCSHARPLANGUAGESUPPORT_H

#include <kdevlanguagesupport.h>

using namespace csharp;

// class CodeModel;
// class CodeProxy;
// class CodeDelegate;
// class CodeAggregate;

class CSharpLanguageSupport : public KDevLanguageSupport
{
Q_OBJECT
public:
    CSharpLanguageSupport( QObject* parent, const QStringList& args = QStringList() );
    virtual ~CSharpLanguageSupport();

    //KDevLanguageSupport implementation
    virtual KDevCodeModel *codeModel( const KUrl& url ) const;
    virtual KDevCodeProxy *codeProxy() const;
    virtual KDevCodeDelegate *codeDelegate() const;
    virtual KDevCodeRepository *codeRepository() const;
    virtual KDevParseJob *createParseJob( const KUrl &url );
    virtual KDevParseJob *createParseJob( KDevDocument *document );
    virtual QStringList mimeTypes() const;

    virtual void read( KDevAST * ast, std::ifstream &in );
    virtual void write( KDevAST * ast, std::ofstream &out );

private slots:
    void documentLoaded( KDevDocument *document );
    void documentClosed( KDevDocument *document );
    void documentActivated( KDevDocument *document );
    void projectOpened();
    void projectClosed();

private:
    QStringList m_mimetypes;
//     CodeProxy *m_codeProxy;
//     CodeDelegate *m_codeDelegate;
//     CSharpHighlighting *m_highlights;
};

#endif

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
