#include <wx-3.0/wx/wx.h>
#include <wx-3.0/wx/string.h>
#include <wx-3.0/wx/menu.h>
#include <wx-3.0/wx/textctrl.h>
#include <wx-3.0/wx/frame.h>
#include <wx-3.0/wx/event.h>
#include <wx-3.0/wx/window.h>
#include <wx-3.0/wx/app.h>

// MainApp is the class for our application, it just acts
// as a container for the window or frame in MainFrame.
class KNearestNeighbors : public wxApp
{
    public:
	virtual bool OnInit();
};

// MainFrame is the class for our window, it
// contains the window and all objects in it.
class MainFrame : public wxFrame
{
    public:
	MainFrame( const wxString &title, const wxPoint &pos, const wxSize &size );

	void Quit( wxCommandEvent& event );
	void NewFile( wxCommandEvent& event );
	void OpenFile( wxCommandEvent& event );
	void SaveFile( wxCommandEvent& event );
	void SaveFileAs( wxCommandEvent& event );
	void CloseFile( wxCommandEvent& event );

	wxTextCtrl *MainEditBox;
	wxMenuBar *MainMenu;
	// The Path to the file we have open
	wxString CurrentDocPath;

	DECLARE_EVENT_TABLE()
};

enum
{
	// declares an id which will be used to call our button
	TEXT_Main = wxID_HIGHEST + 1,
	MENU_New,
	MENU_Open,
	MENU_Close,
	MENU_Save,
	MENU_SaveAs,
	MENU_Quit
};

BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
	EVT_MENU(MENU_New, MainFrame::NewFile)
	EVT_MENU(MENU_Open, MainFrame::OpenFile) 
	EVT_MENU(MENU_Close, MainFrame::CloseFile)
	EVT_MENU(MENU_Save, MainFrame::SaveFile)
	EVT_MENU(MENU_SaveAs, MainFrame::SaveFileAs)
	EVT_MENU(MENU_Quit, MainFrame::Quit)
END_EVENT_TABLE()