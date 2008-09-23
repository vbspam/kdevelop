/* KDevelop xUnit plugin
 *
 * Copyright 2008 Manuel Breugelmans <mbr.nxi@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef CPPUNIT_CPPUNITPLUGIN_H
#define CPPUNIT_CPPUNITPLUGIN_H

#include <interfaces/iplugin.h>
#include <veritas/itestframework.h>
#include <QVariantList>

class CppUnitRunnerViewFactory;
namespace Veritas { class TestToolViewFactory; }

/*! Makes the CppUnit runner available */
class CppUnitPlugin : public KDevelop::IPlugin, public Veritas::ITestFramework
{
Q_OBJECT
Q_INTERFACES(Veritas::ITestFramework)

public:
    explicit CppUnitPlugin(QObject* parent, const QVariantList & = QVariantList());
    virtual ~CppUnitPlugin();
    virtual Veritas::ITestRunner* createRunner();
    virtual QString name() const;

private:
    Veritas::TestToolViewFactory* m_factory;
};

#endif // CPPUNIT_CPPUNITPLUGIN_H
