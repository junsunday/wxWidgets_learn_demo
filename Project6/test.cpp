#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyFrame : public wxFrame
{
public:
    explicit MyFrame(const wxString& title)
        : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150))
    {
        /*�˵�����*/
        wxMenu* testmenu = new wxMenu;
        testmenu->Append(wxID_AUTO_LOWEST, wxT("&this is test\tF2"));
        wxMenu* helpmenu = new wxMenu;
        helpmenu->Append(wxID_ABOUT, wxT("&About\tF1"));
        helpmenu->Append(wxID_DOWN, wxT("&this is next\tF2"));
        wxMenuBar* menubar = new wxMenuBar();
        menubar->Append(helpmenu, wxT("&Help"));
        menubar->Append(testmenu, wxT("&Test"));
        SetMenuBar(menubar);
        // ʵ����һ�����
        auto* panel = new wxPanel(this, wxID_ANY);
        // ����һ����ť
        auto* button = new wxButton(panel, wxID_ANY, wxT("Click me now! "),
            wxPoint(60, 40), wxSize(100, 50));
        // �󶨰�ť����¼�
        button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClicked, this);
    }
    ~MyFrame() = default;
private:
    void OnButtonClicked(wxCommandEvent& event)
    {
        wxUnusedVar(event);
        wxMessageBox(wxT("Hello, wxWidgets!"), wxT("Hello"), wxOK | wxICON_INFORMATION);
    }
    /*���� �¼���*/
    wxDECLARE_EVENT_TABLE();
};
void OnAbout(wxCommandEvent& event)
{
    wxMessageBox(wxT("&okok!"));
}
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
/*�¼���ID��*/
EVT_BUTTON(wxID_ANY, MyFrame::OnButtonClicked)
//EVT_MENU(wxID_ABOUT,OnAbout)
wxEND_EVENT_TABLE()

class MyApp : public wxApp
{
public:
    /* �ض���App�����ĳ�ʼ���麯��*/
    virtual bool OnInit()
    {
        /*���û����ʼ����ʧ�����˳�*/
        if (!wxApp::OnInit())
            return false;

        /* ����һ����ΪHello wxWidgets��ʵ��������*/
        auto* frame = new MyFrame(wxT("Hello wxWidgets!"));
        /*������ʾΪture*/
        frame->Show(true);
        return true;
    }
};
/*��ƽ̨��װ�ĺ꣬������ڣ�main������*/
wxIMPLEMENT_APP(MyApp); // NOLINT
