/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * https://librepcb.org/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************************
 *  Includes
 ******************************************************************************/
#include "attrtypecurrent.h"

#include "attributeunit.h"

#include <QtCore>

/*******************************************************************************
 *  Namespace
 ******************************************************************************/
namespace librepcb {

/*******************************************************************************
 *  Constructors / Destructor
 ******************************************************************************/

AttrTypeCurrent::AttrTypeCurrent() noexcept
  : AttributeType(Type_t::Current, "current", tr("Current")) {
  mDefaultUnit = new AttributeUnit("ampere", tr("A"));

  mAvailableUnits.append(new AttributeUnit("picoampere", tr("pA")));
  mAvailableUnits.append(new AttributeUnit("nanoampere", tr("nA")));
  mAvailableUnits.append(new AttributeUnit("microampere", tr("μA")));
  mAvailableUnits.append(new AttributeUnit("milliampere", tr("mA")));
  mAvailableUnits.append(mDefaultUnit);
  mAvailableUnits.append(new AttributeUnit("kiloampere", tr("kA")));
  mAvailableUnits.append(new AttributeUnit("megaampere", tr("MA")));
}

AttrTypeCurrent::~AttrTypeCurrent() noexcept {
}

/*******************************************************************************
 *  Getters
 ******************************************************************************/

bool AttrTypeCurrent::isValueValid(const QString& value) const noexcept {
  bool ok = false;
  value.toFloat(&ok);
  return (ok || value.isEmpty());
}

QString AttrTypeCurrent::valueFromTr(const QString& value) const noexcept {
  bool  ok = false;
  float v  = QLocale().toFloat(value, &ok);
  if (ok)
    return QString::number(v);
  else
    return QString();
}

QString AttrTypeCurrent::printableValueTr(const QString&       value,
                                          const AttributeUnit* unit) const
    noexcept {
  bool  ok = false;
  float v  = value.toFloat(&ok);
  if (ok && unit)
    return QString(tr("%1%2")).arg(QLocale().toString(v), unit->getSymbolTr());
  else if (ok)
    return QLocale().toString(v);
  else
    return QString();
}

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace librepcb
