// $Id: coldrop.h 1052 2006-05-15 14:19:14Z alex $
/* @@tag:xara-cn@@ DO NOT MODIFY THIS LINE
================================XARAHEADERSTART===========================
 
               Xara LX, a vector drawing and manipulation program.
                    Copyright (C) 1993-2006 Xara Group Ltd.
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

// coldrop.h - The Colour Drop-down list support class

#ifndef BITMAPGRIDDROPDOWN_H
#define BITMAPGRIDDROPDOWN_H

#include "griddropdown.h"
//#include "gbrush.h"
//#include "pump.h"


class LineAttrItem;
class GRenderRegion;


/*************************************************************************
Class         : CBGDDItemInfo
Base Class    : public CGridComboUserData
Author        : Mikhail Tatarnikov
Description   : Items base class for for CBitmapGridDropDown control.
Pure Virtual  : DrawItem - the derived classes has to implement their own drawing.
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBGDDItemInfo : public CGridComboUserData
{
public:
	CBGDDItemInfo(String_256 strLabel = String_256());
	virtual ~CBGDDItemInfo();

	String_256 GetLabel();

	virtual void DrawItem(wxDC& dc, const wxRect& rect, INT32 iFlags) const = 0;

protected:
	String_256 m_strLabel;
};



/*************************************************************************
Class         : CBGDDWxBitmapItem
Base Class    : public CBGDDItemInfo
Author        : Mikhail Tatarnikov
Description   : Item for displaying a wxBitmap.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBGDDWxBitmapItem : public CBGDDItemInfo
{
public:
	CBGDDWxBitmapItem(wxBitmap* pBitmap, BOOL bAutodelete = TRUE,
					  String_256 strLabel = String_256(),
					  BOOL		 bStretch = TRUE);
	virtual ~CBGDDWxBitmapItem();

	virtual void DrawItem(wxDC& dc, const wxRect& rect, INT32 iFlags) const;

protected:
	wxBitmap* m_pBitmap;
	BOOL	  m_bDelete;
	BOOL	  m_bStretch;
};



/*************************************************************************
Class         : CBGDDResourceItem
Base Class    : public CBGDDWxBitmapItem
Author        : Mikhail Tatarnikov
Description   : Item for displaying a resource-stored bitmap.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBGDDResourceItem : public CBGDDWxBitmapItem
{
public:
	CBGDDResourceItem(UINT32 uiBitmapResID,
					  String_256 strLabel = String_256(),
					  BOOL		 bStretch = TRUE);
	virtual ~CBGDDResourceItem();
};


/*************************************************************************
Class         : CBGDDCachedItem
Base Class    : public CBGDDWxBitmapItem
Author        : Mikhail Tatarnikov
Description   : Item for displaying a resource-stored bitmap.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: The derived classes should override either RenderItemToBitmap or
				or GetWxBitmap method - whatever fits best.
**************************************************************************/
class CBGDDCachedItem : public CBGDDItemInfo
{
public:
	CBGDDCachedItem(String_256 strLabel = String_256());
	virtual ~CBGDDCachedItem();

	virtual void DrawItem(wxDC& dc, const wxRect& rect, INT32 iFlags) const;

protected:
	// Get the representation of the item (of the Kernel Bitmap)
	virtual wxBitmap* RenderItemToBitmap(wxSize szBitmap) const;
	virtual void	  RenderItemToGRenderRegion(GRenderRegion* pRenderRegion, DocRect drcItem) const;

private:
	wxBitmap*	GetWxBitmap(wxSize szBitmap) const;
	static BOOL DoesCacheItemSizeMatch(const pair<wxSize, wxBitmap*>* poItem, wxSize szBitmap);

private:
	typedef	std::vector<pair<wxSize, wxBitmap*>*> TDCacheCollection;
	mutable TDCacheCollection m_colCache;
};



/*************************************************************************
Class         : CBGDDKernelBitmapItem
Base Class    : public CBGDDCachedItem
Author        : Mikhail Tatarnikov
Description   : Item for displaying a KernelBitmap.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBGDDKernelBitmapItem : public CBGDDCachedItem
{
public:
	CBGDDKernelBitmapItem(KernelBitmap* pKernelBitmap, BOOL bAutodelete = TRUE,
						  String_256 strLabel = String_256(),
						  BOOL		 bStretch = TRUE);
	virtual ~CBGDDKernelBitmapItem();

protected:
	virtual wxBitmap* RenderItemToBitmap(wxSize szBitmap) const;

protected:
	KernelBitmap* m_pKernelBitmap;
	BOOL		  m_bDeleteKernelBitmap;
	BOOL		  m_bStretch;
};






/*************************************************************************
Class         : CBGDDStrokeItem
Base Class    : public CBGDDCachedItem
Author        : Mikhail Tatarnikov
Description   : Item for displaying a stroke.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBGDDStrokeItem : public CBGDDCachedItem
{
public:
	CBGDDStrokeItem(LineAttrItem* plaiStroke, BOOL bAutodelete = TRUE, String_256 strLabel = String_256());
	virtual ~CBGDDStrokeItem();

protected:
	virtual void RenderItemToGRenderRegion(GRenderRegion* pRenderRegion, DocRect drcItem) const;

protected:
	LineAttrItem* m_plaiStroke;
	BOOL		  m_bDelete;
};





/*************************************************************************
Class         : CBGDDBrushItem
Base Class    : public CBGDDCachedItem
Author        : Mikhail Tatarnikov
Description   : Item for displaying a brush.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBGDDBrushItem : public CBGDDCachedItem
{
public:
	CBGDDBrushItem(AttrBrushType* pabtBrush, BOOL bAutodelete = TRUE, String_256 strLabel = String_256());
	virtual ~CBGDDBrushItem();

protected:
	virtual void RenderItemToGRenderRegion(GRenderRegion* pRenderRegion, DocRect drcItem) const;

protected:
	AttrBrushType* m_pabtBrush;
	BOOL		   m_bDelete;
};












/*************************************************************************
Class         : CBitmapGridDropDown
Base Class    : public CGridDropDown
Author        : Mikhail Tatarnikov
Description   : Control class for wxGridCombo control that stores and displays
				items as images.
Pure Virtual  : None
Known Issues  : None
Usage Notes   : None
Override Notes: None
**************************************************************************/
class CBitmapGridDropDown : public CGridDropDown
{
friend class DialogManager;


public:
	CBitmapGridDropDown();
	virtual ~CBitmapGridDropDown();

	void AddItem(UINT32 uiBitmapResID, String_256 strLabel = String_256(), BOOL bStretch = TRUE);
	void AddItem(wxBitmap* pBitmap, BOOL bDelete = TRUE, String_256 strLabel = String_256(), BOOL bStretch = TRUE);
	void AddItem(KernelBitmap* pBitmap, BOOL bDelete = TRUE, String_256 strLabel = String_256(), BOOL bStretch = TRUE);
	void AddItem(LineAttrItem* plaiStroke, BOOL bDelete = TRUE, String_256 strLabel = String_256());
	void AddItem(AttrBrushType* pabtBrush, BOOL bDelete = TRUE, String_256 strLabel = String_256());

	void SetUnselectedItem(UINT32 uiBitmapResID, String_256 strLabel = String_256());
	void SetUnselectedItem(wxBitmap* pBitmap, String_256 strLabel = String_256());

	void SelectByLabel(String_256 strLabel);

protected:
	CBGDDItemInfo* GetItemData(INT32 iItem);

	virtual void DrawItemCore(wxDC& dc, const wxRect& rect, INT32 iItem, INT32 iFlags);

	wxBitmap*	  PreviewBrush(AttrBrushType* pabtBrush);
	KernelBitmap* PreviewStroke(LineAttrItem* plaiStroke);

protected:
	CBGDDItemInfo* m_poUnselectedItem;
};





#endif	// BITMAPGRIDDROPDOWN_H

