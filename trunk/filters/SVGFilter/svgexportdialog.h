// $Id$
/* @@tag:xara-cn@@ DO NOT MODIFY THIS LINE
================================XARAHEADERSTART===========================
 
               SVGFilter, XAR <--> SVG plugin filter for XaraLX
                    Copyright (C) 2006 Xara Group Ltd.
       Copyright on certain contributions may be held in joint with their
              respective authors. See AUTHORS file for details.

LICENSE TO USE AND MODIFY SOFTWARE
----------------------------------

This file is part of Xara LX.

Xara LX is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as published
by the Free Software Foundation.

Xara LX and its component source files are distributed in the hope
that it will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with Xara LX (see the file GPL in the root directory of the
distribution); if not, write to the Free Software Foundation, Inc., 51
Franklin St, Fifth Floor, Boston, MA  02110-1301 USA


ADDITIONAL RIGHTS
-----------------

Conditional upon your continuing compliance with the GNU General Public
License described above, Xara Group Ltd grants to you certain additional
rights. 

The additional rights are to use, modify, and distribute the software
together with the wxWidgets library, the wxXtra library, and the "CDraw"
library and any other such library that any version of Xara LX relased
by Xara Group Ltd requires in order to compile and execute, including
the static linking of that library to XaraLX. In the case of the
"CDraw" library, you may satisfy obligation under the GNU General Public
License to provide source code by providing a binary copy of the library
concerned and a copy of the license accompanying it.

Nothing in this section restricts any of the rights you have under
the GNU General Public License.


SCOPE OF LICENSE
----------------

This license applies to this program (XaraLX) and its constituent source
files only, and does not necessarily apply to other Xara products which may
in part share the same code base, and are subject to their own licensing
terms.

This license does not apply to files in the wxXtra directory, which
are built into a separate library, and are subject to the wxWindows
license contained within that directory in the file "WXXTRA-LICENSE".

This license does not apply to the binary libraries (if any) within
the "libs" directory, which are subject to a separate license contained
within that directory in the file "LIBS-LICENSE".


ARRANGEMENTS FOR CONTRIBUTION OF MODIFICATIONS
----------------------------------------------

Subject to the terms of the GNU Public License (see above), you are
free to do whatever you like with your modifications. However, you may
(at your option) wish contribute them to Xara's source tree. You can
find details of how to do this at:
  http://www.xaraxtreme.org/developers/

Prior to contributing your modifications, you will need to complete our
contributor agreement. This can be found at:
  http://www.xaraxtreme.org/developers/contribute/

Please note that Xara will not accept modifications which modify any of
the text between the start and end of this header (marked
XARAHEADERSTART and XARAHEADEREND).


MARKS
-----

Xara, Xara LX, Xara X, Xara X/Xtreme, Xara Xtreme, the Xtreme and Xara
designs are registered or unregistered trademarks, design-marks, and/or
service marks of Xara Group Ltd. All rights in these marks are reserved.


      Xara Group Ltd, Gaddesden Place, Hemel Hempstead, HP2 6EX, UK.
                        http://www.xara.com/

=================================XARAHEADEREND============================
 */
// svgexportdialog.h: This defines the XAR --> SVG export dialogbox

#ifndef SVGEXPORTDIALOG_H
#define SVGEXPORTDIALOG_H

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG 10000
#define SYMBOL_SVGEXPORTDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxDIALOG_MODAL
#define SYMBOL_SVGEXPORTDIALOG_TITLE _("SVG Export Settings")
#define SYMBOL_SVGEXPORTDIALOG_IDNAME ID_DIALOG
#define SYMBOL_SVGEXPORTDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_SVGEXPORTDIALOG_POSITION wxDefaultPosition
#define ID_SPECIFICATION_COMBOBOX 10001
#define ID_CHECKBOX 10002
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/***************************************************************************************************

>	class SVGExportDialog

	Author:		Sandro Sigala <sandro@sigala.it>
	Created:	20 June 2006
	Purpose:	Export (SVG --> XAR) dialogbox with the common user settings.

***************************************************************************************************/

class SVGExportDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS(SVGExportDialog)
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    SVGExportDialog();
    SVGExportDialog(wxWindow* parent, wxWindowID id = SYMBOL_SVGEXPORTDIALOG_IDNAME, const wxString& caption = SYMBOL_SVGEXPORTDIALOG_TITLE, const wxPoint& pos = SYMBOL_SVGEXPORTDIALOG_POSITION, const wxSize& size = SYMBOL_SVGEXPORTDIALOG_SIZE, long style = SYMBOL_SVGEXPORTDIALOG_STYLE);

    /// Creation
    bool Create(wxWindow* parent, wxWindowID id = SYMBOL_SVGEXPORTDIALOG_IDNAME, const wxString& caption = SYMBOL_SVGEXPORTDIALOG_TITLE, const wxPoint& pos = SYMBOL_SVGEXPORTDIALOG_POSITION, const wxSize& size = SYMBOL_SVGEXPORTDIALOG_SIZE, long style = SYMBOL_SVGEXPORTDIALOG_STYLE);

    /// Creates the controls and sizers
    void CreateControls();

////@begin SVGExportDialog event handler declarations

////@end SVGExportDialog event handler declarations

////@begin SVGExportDialog member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end SVGExportDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin SVGExportDialog member variables
    wxComboBox* m_SVGVersionComboBox;
    wxCheckBox* m_VerboseCheckBox;
////@end SVGExportDialog member variables
};

#endif // !SVGEXPORTDIALOG_H
