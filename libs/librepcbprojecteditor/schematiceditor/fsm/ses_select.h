/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 Urban Bruhin
 * http://librepcb.org/
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

#ifndef PROJECT_SES_SELECT_H
#define PROJECT_SES_SELECT_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/

#include <QtCore>
#include "ses_base.h"

/*****************************************************************************************
 *  Forward Declarations
 ****************************************************************************************/

class UndoCommand;

namespace project {
class CmdSymbolInstanceEdit;
class CmdSchematicNetPointEdit;
class CmdSchematicNetLabelEdit;
}

/*****************************************************************************************
 *  Class SES_Select
 ****************************************************************************************/

namespace project {


/**
 * @brief The SES_Select class (default state of the schematic editor FSM)
 */
class SES_Select final : public SES_Base
{
        Q_OBJECT

    public:

        // Constructors / Destructor
        explicit SES_Select(SchematicEditor& editor, Ui::SchematicEditor& editorUi,
                            GraphicsView& editorGraphicsView, UndoStack& undoStack);
        ~SES_Select();

        // General Methods
        ProcRetVal process(SEE_Base* event) noexcept override;
        bool entry(SEE_Base* event) noexcept override;
        bool exit(SEE_Base* event) noexcept override;


    private:

        // Private Methods
        ProcRetVal processSubStateIdle(SEE_Base* event) noexcept;
        ProcRetVal processSubStateIdleSceneEvent(SEE_Base* event) noexcept;
        ProcRetVal processSubStateMoving(SEE_Base* event) noexcept;
        ProcRetVal processSubStateMovingSceneEvent(SEE_Base* event) noexcept;
        ProcRetVal proccessIdleSceneLeftClick(QGraphicsSceneMouseEvent* mouseEvent,
                                              Schematic* schematic) noexcept;
        ProcRetVal proccessIdleSceneRightClick(QGraphicsSceneMouseEvent* mouseEvent,
                                               Schematic* schematic) noexcept;
        ProcRetVal proccessIdleSceneDoubleClick(QGraphicsSceneMouseEvent* mouseEvent,
                                                Schematic* schematic) noexcept;
        bool startMovingSelectedItems(Schematic* schematic) noexcept;
        bool rotateSelectedItems(const Angle& angle, Point center = Point(0, 0),
                                 bool centerOfElements = false) noexcept;
        bool removeSelectedItems() noexcept;
        bool cutSelectedItems() noexcept;
        bool copySelectedItems() noexcept;
        bool pasteItems() noexcept;


        // Types
        /// enum for all possible substates
        enum SubState {
            SubState_Idle,      ///< left mouse button is not pressed (default state)
            SubState_Moving     ///< left mouse button is pressed
        };


        // Attributes
        SubState mSubState;     ///< the current substate
        Point mLastMouseMoveDeltaPos;   ///< used in the moving substate (mapped to grid)
        UndoCommand* mParentCommand;    ///< the parent command for all moving commands
                                        ///< (nullptr if no command is active)
        QList<CmdSymbolInstanceEdit*> mSymbolEditCmds; ///< all symbol move commands
        QList<CmdSchematicNetPointEdit*> mNetPointEditCmds; ///< all netpoint edit commands
        QList<CmdSchematicNetLabelEdit*> mNetLabelEditCmds;
};

} // namespace project

#endif // PROJECT_SES_SELECT_H