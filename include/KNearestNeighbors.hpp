#include <wx/wx.h>

class KNearestNeighbors : public wxApp
{
	public:
	virtual bool OnInit();
};

class MyFrame : public wxFrame
{
	public:
	MyFrame(const wxString& title, const wxPoint &pos, const wxSize& size);
};
