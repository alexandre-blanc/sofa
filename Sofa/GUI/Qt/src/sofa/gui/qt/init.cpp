/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#include <sofa/gui/qt/init.h>

#include <sofa/gui/common/GUIManager.h>
#include <sofa/gui/qt/RealGUI.h>

#if SOFA_GUI_QT_ENABLE_QGLVIEWER
int QGLViewerGUIClass = sofa::gui::common::GUIManager::RegisterGUI("qglviewer", &sofa::gui::qt::RealGUI::CreateGUI, nullptr, 3);
#endif

#if SOFA_GUI_QT_ENABLE_QTVIEWER
int QtGUIClass = sofa::gui::common::GUIManager::RegisterGUI("qt", &sofa::gui::qt::RealGUI::CreateGUI, nullptr, 2);
#endif

namespace sofa::gui::qt
{

void init()
{
    static bool first = true;
    if (first)
    {
        first = false;
    }
}

} // namespace sofa::gui::qt