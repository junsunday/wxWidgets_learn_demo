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
        /*菜单创建*/
        wxMenu* testmenu = new wxMenu;
        testmenu->Append(wxID_AUTO_LOWEST, wxT("&this is test\tF2"));
        wxMenu* helpmenu = new wxMenu;
        helpmenu->Append(wxID_ABOUT, wxT("&About\tF1"));
        helpmenu->Append(wxID_DOWN, wxT("&this is next\tF2"));
        wxMenuBar* menubar = new wxMenuBar();
        menubar->Append(helpmenu, wxT("&Help"));
        menubar->Append(testmenu, wxT("&Test"));
        SetMenuBar(menubar);
        // 实例化一个面板
        auto* panel = new wxPanel(this, wxID_ANY);
        // 创建一个按钮
        auto* button = new wxButton(panel, wxID_ANY, wxT("Click me now! "),
            wxPoint(60, 40), wxSize(100, 50));
        // 绑定按钮点击事件
        button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClicked, this);
    }
    ~MyFrame() = default;
private:
    void OnButtonClicked(wxCommandEvent& event)
    {
        wxUnusedVar(event);
        wxMessageBox(wxT("Hello, wxWidgets!"), wxT("Hello"), wxOK | wxICON_INFORMATION);
    }
    /*声明 事件表*/
    wxDECLARE_EVENT_TABLE();
};
void OnAbout(wxCommandEvent& event)
{
    wxMessageBox(wxT("&okok!"));
}
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
/*事件和ID绑定*/
EVT_BUTTON(wxID_ANY, MyFrame::OnButtonClicked)
//EVT_MENU(wxID_ABOUT,OnAbout)
wxEND_EVENT_TABLE()

class MyApp : public wxApp
{
public:
    /* 重定义App启动的初始化虚函数*/
    virtual bool OnInit()
    {
        /*调用基类初始化，失败则退出*/
        if (!wxApp::OnInit())
            return false;

        /* 创建一个名为Hello wxWidgets的实例化窗口*/
        auto* frame = new MyFrame(wxT("Hello wxWidgets!"));
        /*窗口显示为ture*/
        frame->Show(true);
        return true;
    }
};
/*跨平台封装的宏，程序入口（main函数）*/
wxIMPLEMENT_APP(MyApp); // NOLINT
