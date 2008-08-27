/* This file is part of KDevelop
    Copyright 2008 Hamish Rodda <rodda@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef KDEV_CREATECLASS_H
#define KDEV_CREATECLASS_H

#include <QWizard>

#include "../languageexport.h"

class QTableWidget;
class KLineEdit;

namespace KDevelop {

class KDEVPLATFORMLANGUAGE_EXPORT ClassIdentifierPage : public QWizardPage
{
    Q_OBJECT
    Q_PROPERTY(QStringList inheritance READ inheritanceList())

public:
    ClassIdentifierPage(QWidget* parent);
    virtual ~ClassIdentifierPage();

    /// Returns the line edit which contains the new class identifier.
    KLineEdit* identifierLineEdit() const;

    /// Returns the line edit which contains a base class identifier.
    KLineEdit* inheritanceLineEdit() const;

    /// Returns a list of inheritances for the new class
    QStringList inheritanceList() const;

Q_SIGNALS:
    void inheritanceChanged();

public Q_SLOTS:
    /// Called when an inheritance is to be added.  To override in subclasses,
    /// (eg. if there is a problem with the base class proposed),
    /// don't call this implementation.
    virtual void addInheritance();

    /**
     * Called when an inheritance is to be removed.
     *
     * To override in subclasses, don't call this implementation.
     */
    virtual void removeInheritance();

    /**
     * Called when an inheritance is to be moved up.
     *
     * To override in subclasses, don't call this implementation.
     */
    virtual void moveUpInheritance();

    /**
     * Called when an inheritance is to be moved up.
     *
     * To override in subclasses, don't call this implementation.
     */
    virtual void moveDownInheritance();

private:
    void checkMoveButtonState();

    class ClassIdentifierPagePrivate* const d;
};

class KDEVPLATFORMLANGUAGE_EXPORT OverridesPage : public QWizardPage
{
    Q_OBJECT

public:
    OverridesPage(QWidget* parent);
    virtual ~OverridesPage();

    QTableWidget* overrideTable() const;

    QWidget* extraFunctionsContainer() const;

public Q_SLOTS:
    virtual void selectAll();
    virtual void deselectAll();

private:
    class OverridesPagePrivate* const d;
};

class KDEVPLATFORMLANGUAGE_EXPORT LicensePage : public QWizardPage
{
    Q_OBJECT

public:
    LicensePage(QWidget* parent);
    virtual ~LicensePage();

public Q_SLOTS:
    virtual void licenseComboChanged(int license);

private:
    class LicensePagePrivate* const d;
};

class KDEVPLATFORMLANGUAGE_EXPORT OutputPage : public QWizardPage
{
    Q_OBJECT

public:
    OutputPage(QWidget* parent);
    virtual ~OutputPage();

private:
    class OutputPagePrivate* const d;
};

/**
 * Provides a wizard and logic for a new class wizard.
 *
 * \todo add licensing option for generated code
 */
class KDEVPLATFORMLANGUAGE_EXPORT CreateClass : public QWizard
{
    Q_OBJECT

public:
    CreateClass(QWidget* parent);

    /**
     * Creates the generic parts of the new class wizard.
     */
    virtual void setup();

    /**
     * Called when the wizard completes.
     */
    virtual void accept();

    /// \copydoc
    virtual void done ( int r );

    /**
     * Generate the code.
     */
    virtual void generate() = 0;

    virtual ClassIdentifierPage* newIdentifierPage();

    virtual OverridesPage* newOverridesPage();

private:
    class CreateClassPrivate* const d;
};

}

#endif // KDEV_CREATECLASS_H
