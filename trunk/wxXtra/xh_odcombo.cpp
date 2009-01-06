/////////////////////////////////////////////////////////////////////////////
// Name:        src/xrc/xh_odcombo.cpp
// Purpose:     XRC resource for wxRadioBox
// Author:      Alex Bligh - Based on src/xrc/xh_combo.cpp
// Created:     2006/06/19
// RCS-ID:      $Id: xh_odcombo.cpp,v 1.2 2006/06/20 17:02:26 ABX Exp $
// Copyright:   (c) 2006 Alex Bligh
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/wx.h>

#include "xh_odcombo.h"
// Only compile stuff if this is not already in WX
#if wxXTRA_XH_ODCOMBO
#include "odcombo.h"

IMPLEMENT_DYNAMIC_CLASS(wxOwnerDrawnComboBoxXmlHandler, wxXmlResourceHandler)

wxOwnerDrawnComboBoxXmlHandler::wxOwnerDrawnComboBoxXmlHandler()
                     :wxXmlResourceHandler()
                     ,m_insideBox(false)
{
    XRC_ADD_STYLE(wxCB_SIMPLE);
    XRC_ADD_STYLE(wxCB_SORT);
    XRC_ADD_STYLE(wxCB_READONLY);
    XRC_ADD_STYLE(wxCB_DROPDOWN);
    XRC_ADD_STYLE(wxODCB_STD_CONTROL_PAINT);
    XRC_ADD_STYLE(wxODCB_DCLICK_CYCLES);
    XRC_ADD_STYLE(wxTE_PROCESS_ENTER);
    AddWindowStyles();
}

wxObject *wxOwnerDrawnComboBoxXmlHandler::DoCreateResource()
{
    if( m_class == wxT("wxOwnerDrawnComboBox"))
    {
        // find the selection
        long selection = GetLong( wxT("selection"), -1 );

        // need to build the list of strings from children
        m_insideBox = true;
        CreateChildrenPrivately(NULL, GetParamNode(wxT("content")));
        wxString *strings = (wxString *) NULL;
        if (strList.GetCount() > 0)
        {
            strings = new wxString[strList.GetCount()];
            int count = strList.GetCount();
            for (int i = 0; i < count; i++)
                strings[i]=strList[i];
        }

        XRC_MAKE_INSTANCE(control, wxOwnerDrawnComboBox)

        control->Create(m_parentAsWindow,
                        GetID(),
                        GetText(wxT("value")),
                        GetPosition(), GetSize(),
                        strList.GetCount(),
                        strings,
                        GetStyle(),
                        wxDefaultValidator,
                        GetName());

        wxSize ButtonSize=GetSize(wxT("buttonsize"));

        if (ButtonSize != wxDefaultSize)
        control->SetButtonPosition(ButtonSize.GetWidth(), ButtonSize.GetHeight());

        if (selection != -1)
            control->SetSelection(selection);

        SetupWindow(control);

        if (strings != NULL)
            delete[] strings;
        strList.Clear();    // dump the strings

        return control;
    }
    else
    {
        // on the inside now.
        // handle <item>Label</item>

        // add to the list
        wxString str = GetNodeContent(m_node);
        if (m_resource->GetFlags() & wxXRC_USE_LOCALE)
            str = wxGetTranslation(str);
        strList.Add(str);

        return NULL;
    }
}

bool wxOwnerDrawnComboBoxXmlHandler::CanHandle(wxXmlNode *node)
{
#if wxABI_VERSION >= 20700

    return (IsOfClass(node, wxT("wxOwnerDrawnComboBox")) ||
           (m_insideBox && node->GetName() == wxT("item")));

#else

//  Avoid GCC bug - this fails on certain GCC 3.3 and 3.4 builds for an unknown reason
//  it is believed to be related to the fact IsOfClass is inline, and node->GetPropVal
//  gets passed an invalid "this" pointer. On 2.7, the function is out of line, so the
//  above should work fine. This code is left in here so this file can easily be used
//  in a version backported to 2.6. All we are doing here is expanding the macro

    bool fOurClass = node->GetPropVal(wxT("class"), wxEmptyString) == wxT("wxOwnerDrawnComboBox");
    return (fOurClass ||
          (m_insideBox && node->GetName() == wxT("item")));
#endif
}

#endif // wxUSE_XRC && wxUSE_ODCOMBOBOX
