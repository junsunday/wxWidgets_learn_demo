//#include <wx/wxprec.h>
//
//#ifndef WX_PRECOMP
//#include <wx/wx.h>
//#endif
//
//class MyFrame : public wxFrame
//{
//public:
//    explicit MyFrame(const wxString& title)
//        : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150))
//    {
//        /*菜单创建*/
//        wxMenu* testmenu = new wxMenu;
//        testmenu->Append(wxID_AUTO_LOWEST, wxT("&this is test\tF2"));
//        wxMenu* helpmenu = new wxMenu;
//        helpmenu->Append(wxID_ABOUT, wxT("&About\tF1"));
//        helpmenu->Append(wxID_DOWN, wxT("&this is next\tF2"));
//        wxMenuBar* menubar = new wxMenuBar();
//        menubar->Append(helpmenu, wxT("&Help"));
//        menubar->Append(testmenu, wxT("&Test"));
//        SetMenuBar(menubar);
//        // 实例化一个面板
//        auto* panel = new wxPanel(this, wxID_ANY);
//        // 创建一个按钮
//        auto* button = new wxButton(panel, wxID_ANY, wxT("Click me now! "),
//            wxPoint(60, 40), wxSize(100, 50));
//        // 绑定按钮点击事件
//        button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClicked, this);
//    }
//    ~MyFrame() = default;
//private:
//    void OnButtonClicked(wxCommandEvent& event)
//    {
//        wxUnusedVar(event);
//        wxMessageBox(wxT("Hello, wxWidgets!"), wxT("Hello"), wxOK | wxICON_INFORMATION);
//    }
//    /*声明 事件表*/
//    wxDECLARE_EVENT_TABLE();
//};
//void OnAbout(wxCommandEvent& event)
//{
//    wxMessageBox(wxT("&okok!"));
//}
//wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
///*事件和ID绑定*/
//EVT_BUTTON(wxID_ANY, MyFrame::OnButtonClicked)
////EVT_MENU(wxID_ABOUT,OnAbout)
//wxEND_EVENT_TABLE()
//
//class MyApp : public wxApp
//{
//public:
//    /* 重定义App启动的初始化虚函数*/
//    virtual bool OnInit()
//    {
//        /*调用基类初始化，失败则退出*/
//        if (!wxApp::OnInit())
//            return false;
//
//        /* 创建一个名为Hello wxWidgets的实例化窗口*/
//        auto* frame = new MyFrame(wxT("Hello wxWidgets!"));
//        /*窗口显示为ture*/
//        frame->Show(true);
//        return true;
//    }
//};
///*跨平台封装的宏，程序入口（main函数）*/
//wxIMPLEMENT_APP(MyApp); // NOLINT
//


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/artprov.h"
#include "wx/bookctrl.h"
#include "wx/sysopt.h"
#include "wx/wupdlock.h"
#include "wx/display.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};


class MyFrame : public wxFrame
{
public:
    //
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
            long style = wxDEFAULT_FRAME_STYLE);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnFromPoint(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

#if wxUSE_DISPLAY
    void OnChangeMode(wxCommandEvent& event);
    void OnResetMode(wxCommandEvent& event);

    void OnDisplayChanged(wxDisplayChangedEvent& event);
#endif // wxUSE_DISPLAY

    void OnDPIChanged(wxDPIChangedEvent& event);

    void OnLeftClick(wxMouseEvent& event);

private:
    //选项卡界面填充信息
    void Bookctrl_Info();

#if wxUSE_DISPLAY
    // convert video mode to textual description
    wxString VideoModeToText(const wxVideoMode& mode);
#endif // wxUSE_DISPLAY

    // GUI controls
    wxBookCtrl *m_book;

    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};

#if wxUSE_DISPLAY
// Client data class for the choice control containing the video modes
class MyVideoModeClientData : public wxClientData
{
public:
    MyVideoModeClientData(const wxVideoMode& m) : mode(m) { }

    const wxVideoMode mode;
};
#endif // wxUSE_DISPLAY

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

//分配事件ID
enum
{
    //一级菜单项
    Display_FromPoint = wxID_HIGHEST + 1,  //6000
    //二级菜单项
    wxID_Submenu,
    wxID_Sub_first,
    wxID_Sub_second,


    //命令项
    Display_ChangeMode,                    //6004
    Display_ResetMode,
    Display_CurrentMode,
    Display_Update,

   //特定项
    Display_Quit = wxID_EXIT,
    Display_About = wxID_ABOUT

};


//事件表(事件ID与处理函数相匹配)
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Display_Quit,  MyFrame::OnQuit)
    EVT_MENU(Display_FromPoint,  MyFrame::OnFromPoint)
    EVT_MENU(Display_About, MyFrame::OnAbout)

#if wxUSE_DISPLAY
    EVT_CHOICE(Display_ChangeMode, MyFrame::OnChangeMode)
    EVT_BUTTON(Display_ResetMode, MyFrame::OnResetMode)

    EVT_DISPLAY_CHANGED(MyFrame::OnDisplayChanged)
#endif // wxUSE_DISPLAY

    EVT_DPI_CHANGED(MyFrame::OnDPIChanged)

    EVT_LEFT_UP(MyFrame::OnLeftClick)
wxEND_EVENT_TABLE()

/*调用跨平台封装的宏，mian主程序入口*/
wxIMPLEMENT_APP(MyApp);


/*--------------------*/
/*程序需求及函数实现区*/
/*--------------------*/

//窗口初始化
bool MyApp::OnInit()
{
    //预判断
    if (!wxApp::OnInit())
        return false;
    //创建一个窗口实例
    MyFrame* display_frame = new MyFrame(wxT("This is a Window"), wxDefaultPosition, wxDefaultSize);
    //显示窗口
    display_frame->Show(true);
    //返回true后，进入wxAPP::OnRun(),应用跑起来了
    return true;
}

//窗口功能
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, long style)
       : wxFrame(NULL, wxID_ANY, title, pos, size, style)
{
    //设置图标
    wxImage::AddHandler(new wxPNGHandler);
    SetIcon(wxICON("testSheep.png", wxBitmapType_png));
    //SetIcon(wxICON(sample));

#if wxUSE_MENUS
    //创建菜单
    wxMenu *MyMenu = new wxMenu;
    MyMenu->Append(Display_FromPoint,wxT("Display&Point"));
    //添加分隔线
    MyMenu->AppendSeparator();
    //创建下级菜单
    wxMenu* MySubMenu = new wxMenu();
    //添加菜单项
    MySubMenu->Append(wxID_Sub_first, wxT("this is first!\tF&1"));
    MySubMenu->Append(wxID_Sub_second, wxT("this is second!\tF&2"));
    //上下级菜单衔接
    MyMenu->Append(wxID_Submenu, wxT("&Next Content"), MySubMenu);

    //分隔线
    MyMenu->AppendSeparator();
    //添加退出事件
    MyMenu->Append(Display_Quit, _("E&xit\tAlt-X"), _("Quit this program"));

    //创建help菜单
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Display_About, _("&About\tF1"), _("Show about dialog"));
    helpMenu->Append(Display_Update, wxT("&Update\tF2"));
    //创建菜单栏
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(MyMenu, _("&Display"));
    menuBar->Append(helpMenu, _("&Help"));


    //设置菜单栏
    SetMenuBar(menuBar);
#endif //是否使用菜单

#if wxUSE_STATUSBAR
    //创建状态栏
    CreateStatusBar();
#endif // 是否使用状态栏

    //创建选项卡界面布局
    m_book = new wxBookCtrl(this, wxID_ANY);
    Bookctrl_Info();
}

void MyFrame::Bookctrl_Info()
{
    //获取显示器数量
    const size_t display_count = wxDisplay::GetCount();
    for ( size_t n = 0; n < display_count; n++ )
    {
        //实例化对象
        wxDisplay display(n);
        //创建面板
        wxWindow *page = new wxPanel(m_book, wxID_ANY);
        //创建网格布局管理器（4列，15垂直间距，20水平间距）
        wxFlexGridSizer *sizer = new wxFlexGridSizer(4, 15, 20);
        //1行为可增长列，等比例增长（default：0）
        sizer->AddGrowableCol(1);
        //获取显示器的几何信息
        const wxRect r(display.GetGeometry());
        //创建文本并添加至布局管理器
        sizer->Add(new wxStaticText(page, wxID_ANY, wxT("原点: ")));
        sizer->Add(new wxStaticText
                       (
                        page,
                        wxID_ANY,
                        wxString::Format("(%d, %d)",r.x, r.y)
                       )
                  );

        sizer->Add(new wxStaticText(page, wxID_ANY, "尺寸: "));
        sizer->Add(new wxStaticText
                       (
                        page,
                        wxID_ANY,
                        wxString::Format("(%d, %d)",
                                         r.width, r.height)
                       ));
        //获取实际区域并创建对象
        const wxRect rc(display.GetClientArea());
        sizer->Add(new wxStaticText(page, wxID_ANY, "实际区域: "));
        sizer->Add(new wxStaticText
                       (
                        page,
                        wxID_ANY,
                        wxString::Format("(%d, %d)-(%d, %d)",
                                         rc.x, rc.y, rc.width, rc.height)
                       ));
        //获取显示器分辨率并创建对象
        const wxSize ppi = display.GetPPI();
        sizer->Add(new wxStaticText(page, wxID_ANY, "分辨率: "));
        sizer->Add(new wxStaticText(page, wxID_ANY,
                                    wxString::Format("%d*%d", ppi.x, ppi.y)));
        //获取显示器位深并创建对象
        sizer->Add(new wxStaticText(page, wxID_ANY, "位深: "));
        sizer->Add(new wxStaticText(page, wxID_ANY,
                                    wxString::Format("%d", display.GetDepth())));
        //获取缩放并创建对象
        sizer->Add(new wxStaticText(page, wxID_ANY, "缩放: "));
        sizer->Add(new wxStaticText(page, wxID_ANY,
                                    wxString::Format("%.2f",
                                                     display.GetScaleFactor())));
        //获取缩放并创建对象
        sizer->Add(new wxStaticText(page, wxID_ANY, "名称: "));
        sizer->Add(new wxStaticText(page, wxID_ANY, display.GetName()));
        //获取缩放并创建对象
        sizer->Add(new wxStaticText(page, wxID_ANY, "主屏: "));
        sizer->Add(new wxStaticText(page, wxID_ANY,
                                    display.IsPrimary() ? "Yes" : "No"));

        //
        wxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
        sizerTop->Add(sizer, wxSizerFlags(1).Expand().DoubleBorder());

#if wxUSE_DISPLAY
        wxChoice *choiceModes = new wxChoice(page, Display_ChangeMode);

        {
            // Speed up the Append() loop below by foregoing the repeated resizing
            // of the choice dropdown via repeated calls to GetBestSize() which
            // happens deep inside the Append() call chain and executes another
            // inner loop calling SendMessage() to get the control contents.
            //
            // As there can be a couple of hundreds of video modes, this saves
            // many thousands of such calls and so has a very noticeable effect.
            wxWindowUpdateLocker lockUpdates(choiceModes);

            const wxArrayVideoModes modes = display.GetModes();
            const size_t countModes = modes.GetCount();
            for ( size_t nMode = 0; nMode < countModes; nMode++ )
            {
                const wxVideoMode& mode = modes[nMode];

                choiceModes->Append(VideoModeToText(mode),
                    new MyVideoModeClientData(mode));
            }
        } // Destroy wxWindowUpdateLocker to finally resize the window now.

        const wxString currentMode = VideoModeToText(display.GetCurrentMode());
        choiceModes->SetStringSelection(currentMode);

        sizer->Add(new wxStaticText(page, wxID_ANY, "&Modes: "),
                   wxSizerFlags().CentreVertical());
        sizer->Add(choiceModes, wxSizerFlags().Expand());

        sizer->Add(new wxStaticText(page, wxID_ANY, "Current: "));
        sizer->Add(new wxStaticText(page, Display_CurrentMode, currentMode));

        sizerTop->Add(new wxButton(page, Display_ResetMode, "&Reset mode"),
                      wxSizerFlags().Centre().Border());
#endif // wxUSE_DISPLAY

        page->SetSizer(sizerTop);
        page->Layout();

        m_book->AddPage(page, wxString::Format("Display %zu", n + 1));
    }

    SetClientSize(m_book->GetBestSize());
    SetMinSize(GetSize());
}

#if wxUSE_DISPLAY

wxString MyFrame::VideoModeToText(const wxVideoMode& mode)
{
    wxString s;
    s.Printf("%dx%d", mode.w, mode.h);

    if ( mode.bpp )
    {
        s += wxString::Format(", %dbpp", mode.bpp);
    }

    if ( mode.refresh )
    {
        s += wxString::Format(", %dHz", mode.refresh);
    }

    return s;
}

#endif // wxUSE_DISPLAY

// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox("Hello wxWidgets!\n\n 2024.7.10 Junday",
                 "This is About",
                 wxOK | wxICON_INFORMATION,
                 this);
}

void MyFrame::OnFromPoint(wxCommandEvent& WXUNUSED(event))
{
#if wxUSE_STATUSBAR
    SetStatusText("Now,click somewhere");
#endif 
    CaptureMouse();
}


#if wxUSE_DISPLAY

void MyFrame::OnChangeMode(wxCommandEvent& event)
{
    wxDisplay dpy(m_book->GetSelection());

    // you wouldn't write this in real code, would you?
    if ( !dpy.ChangeMode(((MyVideoModeClientData *)
                wxDynamicCast(event.GetEventObject(), wxChoice)->
                    GetClientObject(event.GetInt()))->mode) )
    {
        wxLogError("Changing video mode failed!");
    }
}

void MyFrame::OnResetMode(wxCommandEvent& WXUNUSED(event))
{
    wxDisplay dpy(m_book->GetSelection());

    dpy.ResetMode();
}

#endif // wxUSE_DISPLAY

void MyFrame::OnDPIChanged(wxDPIChangedEvent& event)
{
    wxLogStatus(this, "DPI changed: was %d*%d, now %d*%d",
                event.GetOldDPI().x, event.GetOldDPI().y,
                event.GetNewDPI().x, event.GetNewDPI().y);

    event.Skip();
}

void MyFrame::OnLeftClick(wxMouseEvent& event)
{
    if ( HasCapture() )
    {
        // mouse events are in client coords, wxDisplay works in screen ones
        const wxPoint ptScreen = ClientToScreen(event.GetPosition());
        int dpy = wxDisplay::GetFromPoint(ptScreen);
        if ( dpy == wxNOT_FOUND )
        {
            wxLogError("Mouse clicked outside of display!?");
        }

        wxLogStatus(this, "Mouse clicked in display %d (at (%d, %d))",
                    dpy, ptScreen.x, ptScreen.y);

        ReleaseMouse();
    }
}

#if wxUSE_DISPLAY

void MyFrame::OnDisplayChanged(wxDisplayChangedEvent& event)
{
    m_book->DeleteAllPages();
    Bookctrl_Info();

    wxLogStatus(this, "Display resolution was changed.");

    event.Skip();
}

#endif // wxUSE_DISPLAY

