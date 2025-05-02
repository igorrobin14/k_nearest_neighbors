#include "KNearestNeighbors.hpp"

bool KNearestNeighbors::OnInit()
{
	MyFrame * frame = new MyFrame("Hello world", wxDefaultPosition, wxDefaultSize);
	frame->Show(true);
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint &pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
	auto button = new wxButton(this, wxID_ANY, "ShowDialog");

	button->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) { wxMessageBox("Hello world", "Messsage", wxOK | wxICON_INFORMATION); });
}