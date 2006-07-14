/* This file is part of KDevelop
    Copyright (C) 2006 Hamish Rodda <rodda@kde.org>

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

#include "identifier.h"

Identifier::Identifier(const QString id)
  : m_unique(0)
  , m_identifier(id)
{
}

Identifier::Identifier()
  : m_unique(0)
{
}

Identifier Identifier::unique(int token)
{
  Identifier ret;
  ret.setUnique(token);
  return ret;
}

bool Identifier::isUnique() const
{
  return m_unique;
}

int Identifier::uniqueToken() const
{
  return m_unique;
}

void Identifier::setUnique(int token)
{
  m_unique = token;
}

const QString& Identifier::identifier() const
{
  return m_identifier;
}

void Identifier::setIdentifier(const QString& identifier)
{
  m_identifier = identifier;
}

const QList<QualifiedIdentifier>& Identifier::templateIdentifiers() const
{
  return m_templateIdentifiers;
}

void Identifier::appendTemplateIdentifier(const QualifiedIdentifier& identifier)
{
  m_templateIdentifiers.append(identifier);
}

void Identifier::clearTemplateIdentifiers()
{
  m_templateIdentifiers.clear();
}

void Identifier::setTemplateIdentifiers(const QList<QualifiedIdentifier>& templateIdentifiers)
{
  m_templateIdentifiers = templateIdentifiers;
}

QString Identifier::toString() const
{
  if (!this) {
    return "(null identifier)";
  }

  QString ret = identifier();

  if (templateIdentifiers().count()) {
    ret.append("< ");
    for (int i = 0; i < templateIdentifiers().count(); ++i) {
      ret.append(templateIdentifiers()[i].toString());
      if (i != templateIdentifiers().count() - 1)
        ret.append(", ");
    }
    ret.append(" >");
  }

  return ret;
}

bool Identifier::operator==(const Identifier& rhs) const
{
  if (isUnique() || rhs.isUnique())
    if (uniqueToken() == rhs.uniqueToken())
      return true;
    else
      return false;

  if (identifier() != rhs.identifier())
    return false;

  if (templateIdentifiers() != rhs.templateIdentifiers())
    return false;

  return true;
}

bool Identifier::operator!=(const Identifier& rhs) const
{
  return !operator==(rhs);
}

QualifiedIdentifier::QualifiedIdentifier(const QString id)
{
  foreach (const QString& unqualified, id.split("::"))
    push(Identifier(unqualified));
}

QualifiedIdentifier::QualifiedIdentifier(const Identifier& id)
{
  push(id);
}

QualifiedIdentifier::QualifiedIdentifier()
{
}

QStringList QualifiedIdentifier::toStringList() const
{
  QStringList ret;
  foreach (const Identifier& id, *this)
    ret.append(id.toString());

  return ret;
}

QString QualifiedIdentifier::toString() const
{
  if (!this) {
    return "(null qualified identifier)";
  }

  QString ret;
  bool preceedingId = false;
  if (isEmpty()) {
    return "<anonymous>";

  } else for (int i = 0; i < count(); ++i) {
    const QString& id = at(i).toString();
    if (id.isEmpty()) {
      if (i == 0)
        ret.append("::");

    } else {
      if (preceedingId)
        ret.append("::");

      ret.append(id);
      preceedingId = true;
    }
  }

  return ret;
}

void QualifiedIdentifier::merge(const QualifiedIdentifier& base)
{
  if (explicitlyGlobal())
    return;

  for (int i = base.count() - 1; i >= 0; --i)
    prepend(base.at(i));

  return;
}

bool QualifiedIdentifier::explicitlyGlobal() const
{
  // True if starts with "::"
  return !isEmpty() && at(0).identifier().isEmpty();
}

bool QualifiedIdentifier::operator==(const QualifiedIdentifier& rhs) const
{
  int l = 0, r = 0;
  if (explicitlyGlobal()) l++;
  if (rhs.explicitlyGlobal()) r++;
  if (count() - l != rhs.count() - r)
    return false;

  for (int i = 0; i < count() - l; ++i)
    if (at(i - l) != rhs.at(i - r))
      return false;

  return true;
}

bool QualifiedIdentifier::operator!=(const QualifiedIdentifier& rhs) const
{
  return !operator==(rhs);
}

uint qHash(const QualifiedIdentifier& id)
{
  // FIXME
  return reinterpret_cast<uint>(&id);
}

QualifiedIdentifier QualifiedIdentifier::merge(const QStack<QualifiedIdentifier>& idStack)
{
  QualifiedIdentifier ret;
  foreach (const QualifiedIdentifier& id, idStack)
    ret << id;
    /*foreach (const Identifier& id2, id)
      if (!id2.identifier.isEmpty())
        ret << id2;*/

  return ret;
}

// kate: indent-width 2;
