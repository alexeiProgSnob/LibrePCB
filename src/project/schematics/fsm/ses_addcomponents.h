/*
 * EDA4U - Professional EDA for everyone!
 * Copyright (C) 2013 Urban Bruhin
 * http://eda4u.ubruhin.ch/
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

#ifndef PROJECT_SES_ADDCOMPONENTS_H
#define PROJECT_SES_ADDCOMPONENTS_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/

#include <QtCore>
#include "ses_base.h"

/*****************************************************************************************
 *  Forward Declarations
 ****************************************************************************************/

namespace library {
class GenericComponent;
class GenCompSymbVar;
class GenCompSymbVarItem;
}

namespace project {
class GenericComponentInstance;
class SymbolInstance;
class CmdSymbolInstanceMove;
}

/*****************************************************************************************
 *  Class SES_AddComponents
 ****************************************************************************************/

namespace project {


/**
 * @brief The SES_AddComponents class
 */
class SES_AddComponents final : public SES_Base
{
        Q_OBJECT

    public:

        // Constructors / Destructor
        explicit SES_AddComponents(SchematicEditor& editor, Ui::SchematicEditor& editorUi);
        ~SES_AddComponents();

        // General Methods
        ProcRetVal process(SEE_Base* event) noexcept override;
        bool entry(SEE_Base* event) noexcept override;
        bool exit(SEE_Base* event) noexcept override;


    private:

        // Private Methods
        ProcRetVal processSceneEvent(SEE_Base* event) noexcept;
        bool abortCommand(bool showErrMsgBox) noexcept;


        // Attributes
        bool mIsUndoCmdActive;

        // information about the current symbol to place
        const library::GenericComponent* mGenComp;
        const library::GenCompSymbVar* mGenCompSymbVar;
        const library::GenCompSymbVarItem* mCurrentSymbVarItem;
        SymbolInstance* mCurrentSymbolToPlace;
        CmdSymbolInstanceMove* mCurrentSymboleMoveCommand;
};

} // namespace project

#endif // PROJECT_SES_ADDCOMPONENTS_H
