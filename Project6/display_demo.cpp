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
//        /*�˵�����*/
//        wxMenu* testmenu = new wxMenu;
//        testmenu->Append(wxID_AUTO_LOWEST, wxT("&this is test\tF2"));
//        wxMenu* helpmenu = new wxMenu;
//        helpmenu->Append(wxID_ABOUT, wxT("&About\tF1"));
//        helpmenu->Append(wxID_DOWN, wxT("&this is next\tF2"));
//        wxMenuBar* menubar = new wxMenuBar();
//        menubar->Append(helpmenu, wxT("&Help"));
//        menubar->Append(testmenu, wxT("&Test"));
//        SetMenuBar(menubar);
//        // ʵ����һ�����
//        auto* panel = new wxPanel(this, wxID_ANY);
//        // ����һ����ť
//        auto* button = new wxButton(panel, wxID_ANY, wxT("Click me now! "),
//            wxPoint(60, 40), wxSize(100, 50));
//        // �󶨰�ť����¼�
//        button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClicked, this);
//    }
//    ~MyFrame() = default;
//private:
//    void OnButtonClicked(wxCommandEvent& event)
//    {
//        wxUnusedVar(event);
//        wxMessageBox(wxT("Hello, wxWidgets!"), wxT("Hello"), wxOK | wxICON_INFORMATION);
//    }
//    /*���� �¼���*/
//    wxDECLARE_EVENT_TABLE();
//};
//void OnAbout(wxCommandEvent& event)
//{
//    wxMessageBox(wxT("&okok!"));
//}
//wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
///*�¼���ID��*/
//EVT_BUTTON(wxID_ANY, MyFrame::OnButtonClicked)
////EVT_MENU(wxID_ABOUT,OnAbout)
//wxEND_EVENT_TABLE()
//
//class MyApp : public wxApp
//{
//public:
//    /* �ض���App�����ĳ�ʼ���麯��*/
//    virtual bool OnInit()
//    {
//        /*���û����ʼ����ʧ�����˳�*/
//        if (!wxApp::OnInit())
//            return false;
//
//        /* ����һ����ΪHello wxWidgets��ʵ��������*/
//        auto* frame = new MyFrame(wxT("Hello wxWidgets!"));
//        /*������ʾΪture*/
//        frame->Show(true);
//        return true;
//    }
//};
///*��ƽ̨��װ�ĺ꣬������ڣ�main������*/
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

    
    void OnQuit(wxCommandEvent& event);
    void OnFromPoint(wxCommandEvent& event);
    void OnFirstEvent(wxCommandEvent& event);
    void OnSecondEvent(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnUpdate(wxCommandEvent& event);

#if wxUSE_DISPLAY
    void OnChangeMode(wxCommandEvent& event);
    void OnResetMode(wxCommandEvent& event);

    void OnDisplayChanged(wxDisplayChangedEvent& event);
#endif 

    void OnDPIChanged(wxDPIChangedEvent& event);

    void OnLeftClick(wxMouseEvent& event);

private:
    //ѡ����������Ϣ
    void Bookctrl_Info();

#if wxUSE_DISPLAY
    wxString VideoModeToText(const wxVideoMode& mode);
#endif 
    wxBookCtrl *m_book;
    wxDECLARE_EVENT_TABLE();
};

#if wxUSE_DISPLAY

class MyVideoModeClientData : public wxClientData
{
public:
    MyVideoModeClientData(const wxVideoMode& m) : mode(m) { }

    const wxVideoMode mode;
};
#endif 

//�����¼�ID
enum
{
    //һ���˵���
    Display_FromPoint = wxID_HIGHEST + 1,  //6000
    //�����˵���
    wxID_Submenu,
    wxID_Sub_first,
    wxID_Sub_second,


    //������
    Display_ChangeMode,                    //6004
    Display_ResetMode,
    Display_CurrentMode,
    Display_Update,

   //�ض���
    Display_Quit = wxID_EXIT,
    Display_About = wxID_ABOUT

};


//�¼���(�¼�ID�봦������ƥ��)
wxBEGIN_EVENT_TABLE(MyFrame,wxFrame)
    EVT_MENU(Display_Quit,MyFrame::OnQuit)
    EVT_MENU(Display_FromPoint,MyFrame::OnFromPoint)
    EVT_MENU(wxID_Sub_first,MyFrame::OnFirstEvent)
    EVT_MENU(wxID_Sub_second,MyFrame::OnSecondEvent)
    EVT_MENU(Display_About,MyFrame::OnAbout)
    EVT_MENU(Display_Update,MyFrame::OnUpdate)
#if wxUSE_DISPLAY
    EVT_CHOICE(Display_ChangeMode,MyFrame::OnChangeMode)
    EVT_BUTTON(Display_ResetMode,MyFrame::OnResetMode)

    EVT_DISPLAY_CHANGED(MyFrame::OnDisplayChanged)
#endif // wxUSE_DISPLAY

    EVT_DPI_CHANGED(MyFrame::OnDPIChanged)

    EVT_LEFT_UP(MyFrame::OnLeftClick)
wxEND_EVENT_TABLE()

/*���ÿ�ƽ̨��װ�ĺ꣬mian���������*/
wxIMPLEMENT_APP(MyApp);


/*--------------------*/
/*�������󼰺���ʵ����*/
/*--------------------*/

//���ڳ�ʼ��
bool MyApp::OnInit()
{
    //Ԥ�ж�
    if (!wxApp::OnInit())
        return false;
    //����һ������ʵ��
    MyFrame* display_frame = new MyFrame(wxT("This is a Window"), wxDefaultPosition, wxDefaultSize);
    //��ʾ����
    display_frame->Show(true);
    //����true�󣬽���wxAPP::OnRun(),Ӧ����������
    return true;
}

//���ڹ���
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, long style)
       : wxFrame(NULL, wxID_ANY, title, pos, size, style)
{
    //����ͼ��
    wxImage::AddHandler(new wxPNGHandler);
    SetIcon(wxICON("testSheep.png", wxBitmapType_png));
    //SetIcon(wxICON(sample));

#if wxUSE_MENUS
    //�����˵�
    wxMenu *MyMenu = new wxMenu;
    MyMenu->Append(Display_FromPoint,wxT("Display&Point"));
    //��ӷָ���
    MyMenu->AppendSeparator();
    //�����¼��˵�
    wxMenu* MySubMenu = new wxMenu();
    //��Ӳ˵���
    MySubMenu->Append(wxID_Sub_first, wxT("this is first!\tF&1"));
    MySubMenu->Append(wxID_Sub_second, wxT("this is second!\tF&2"));
    //���¼��˵��ν�
    MyMenu->Append(wxID_Submenu, wxT("&Next Content"), MySubMenu);

    //�ָ���
    MyMenu->AppendSeparator();
    //����˳��¼�
    MyMenu->Append(Display_Quit, _("E&xit\tAlt-X"), _("Quit this program"));

    //����help�˵�
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Display_About, _("&About\tF1"), _("Show about dialog"));
    helpMenu->Append(Display_Update, wxT("&Update\tF2"),wxT("Show more detail"));
    //�����˵���
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(MyMenu, _("&Display"));
    menuBar->Append(helpMenu, _("&Help"));


    //���ò˵���
    SetMenuBar(menuBar);
#endif //�Ƿ�ʹ�ò˵�

#if wxUSE_STATUSBAR
    //����״̬��
    CreateStatusBar();
#endif // �Ƿ�ʹ��״̬��

    //����ѡ����沼��
    m_book = new wxBookCtrl(this, wxID_ANY);
    Bookctrl_Info();
}

void MyFrame::Bookctrl_Info()
{
    //��ȡ��ʾ������
    const size_t display_count = wxDisplay::GetCount();
    for ( size_t n = 0; n < display_count; n++ )
    {
        //ʵ��������
        wxDisplay display(n);
        //�������
        wxWindow *page = new wxPanel(m_book, wxID_ANY);
        //�������񲼾ֹ�������4�У�15��ֱ��࣬20ˮƽ��ࣩ
        wxFlexGridSizer *sizer = new wxFlexGridSizer(4, 15, 20);
        //1��Ϊ�������У��ȱ���������default��0��
        sizer->AddGrowableCol(1);
        //��ȡ��ʾ���ļ�����Ϣ
        const wxRect r(display.GetGeometry());
        //�����ı�����������ֹ�����
        sizer->Add(new wxStaticText(page, wxID_ANY, wxT("ԭ��: ")));
        sizer->Add(new wxStaticText
                       (
                        page,
                        wxID_ANY,
                        wxString::Format("(%d, %d)",r.x, r.y)
                       )
                  );

        sizer->Add(new wxStaticText(page, wxID_ANY, "�ߴ�: "));
        sizer->Add(new wxStaticText
                       (
                        page,
                        wxID_ANY,
                        wxString::Format("(%d, %d)",
                                         r.width, r.height)
                       ));
        //��ȡʵ�����򲢴�������
        const wxRect rc(display.GetClientArea());
        sizer->Add(new wxStaticText(page, wxID_ANY, "ʵ������: "));
        sizer->Add(new wxStaticText
                       (
                        page,
                        wxID_ANY,
                        wxString::Format("(%d, %d)-(%d, %d)",
                                         rc.x, rc.y, rc.width, rc.height)
                       ));
        //��ȡ��ʾ���ֱ��ʲ���������
        const wxSize ppi = display.GetPPI();
        sizer->Add(new wxStaticText(page, wxID_ANY, "�ֱ���: "));
        sizer->Add(new wxStaticText(page, wxID_ANY,
                                    wxString::Format("%d*%d", ppi.x, ppi.y)));
        //��ȡ��ʾ��λ���������
        sizer->Add(new wxStaticText(page, wxID_ANY, "λ��: "));
        sizer->Add(new wxStaticText(page, wxID_ANY,
                                    wxString::Format("%d", display.GetDepth())));
        //��ȡ���Ų���������
        sizer->Add(new wxStaticText(page, wxID_ANY, "����: "));
        sizer->Add(new wxStaticText(page, wxID_ANY,
                                    wxString::Format("%.2f",
                                                     display.GetScaleFactor())));
        //��ȡ���Ų���������
        sizer->Add(new wxStaticText(page, wxID_ANY, "����: "));
        sizer->Add(new wxStaticText(page, wxID_ANY, display.GetName()));
        //��ȡ���Ų���������
        sizer->Add(new wxStaticText(page, wxID_ANY, "����: "));
        sizer->Add(new wxStaticText(page, wxID_ANY,
                                    display.IsPrimary() ? wxT("��" ):wxT( "��")));

        //���ֹ������
        wxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
        sizerTop->Add(sizer, wxSizerFlags(1).Expand().DoubleBorder());

#if wxUSE_DISPLAY
        //����ʽѡ��
        wxChoice *choiceModes = new wxChoice(page, Display_ChangeMode);
        {
            wxWindowUpdateLocker lockUpdates(choiceModes);
            const wxArrayVideoModes modes = display.GetModes();
            const size_t countModes = modes.GetCount();
            for ( size_t nMode = 0; nMode < countModes; nMode++ )
            {
                const wxVideoMode& mode = modes[nMode];

                choiceModes->Append(VideoModeToText(mode),
                    new MyVideoModeClientData(mode));
            }
        } 

        const wxString currentMode = VideoModeToText(display.GetCurrentMode());
        choiceModes->SetStringSelection(currentMode);

        sizer->Add(new wxStaticText(page, wxID_ANY, wxT("&ģʽ: ")),
                   wxSizerFlags().CentreVertical());
        sizer->Add(choiceModes, wxSizerFlags().Expand());

        sizer->Add(new wxStaticText(page, wxID_ANY, wxT("��ǰ: ")));
        sizer->Add(new wxStaticText(page, Display_CurrentMode, currentMode));

        sizerTop->Add(new wxButton(page, Display_ResetMode, wxT("&Ĭ��ֵ")),
                      wxSizerFlags().Centre().Border());
#endif 
        //ҳ����ʾ
        page->SetSizer(sizerTop);
        page->Layout();

        m_book->AddPage(page, wxString::Format(wxT("��ʾ�� %zu"), n + 1));
    }
    //���óߴ�
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

#endif 

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox("Hello wxWidgets!\n\n 2024.7.10 Junsunday",
                 "This is About",
                 wxOK | wxICON_INFORMATION,
                 this);
}

void MyFrame::OnUpdate(wxCommandEvent& event)
{
    wxMessageBox(wxT("��ȡ����֧�֣���ӭ��ϵJunsunday��"),
                 wxT("This is Update"),
                 wxOK | wxICON_INFORMATION,
                 this);
}
void MyFrame::OnFirstEvent(wxCommandEvent& event)
{
    wxMessageBox(wxT("this is first event!!!"), 
                 wxT("First"), 
                 wxOK | wxICON_INFORMATION,
                 this);
}
void MyFrame::OnSecondEvent(wxCommandEvent& event)
{
    wxMessageBox(wxT("this is second event!!!"),
                 wxT("Second"),
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
    if ( !dpy.ChangeMode(((MyVideoModeClientData *)
                wxDynamicCast(event.GetEventObject(), wxChoice)->
                    GetClientObject(event.GetInt()))->mode) )
    {
        wxLogError(wxT("����ģʽʧ��!"));
    }
}

void MyFrame::OnResetMode(wxCommandEvent& WXUNUSED(event))
{
    wxDisplay dpy(m_book->GetSelection());

    dpy.ResetMode();
}

#endif 

void MyFrame::OnDPIChanged(wxDPIChangedEvent& event)
{
    wxLogStatus(this, wxT("DPI: �� %d*%d, �� %d*%d"),
                event.GetOldDPI().x, event.GetOldDPI().y,
                event.GetNewDPI().x, event.GetNewDPI().y);

    event.Skip();
}

void MyFrame::OnLeftClick(wxMouseEvent& event)
{
    if ( HasCapture() )
    {
        const wxPoint ptScreen = ClientToScreen(event.GetPosition());
        int dpy = wxDisplay::GetFromPoint(ptScreen);
        if ( dpy == wxNOT_FOUND )
        {
            wxLogError(wxT("�����¼�������"));
        }

        wxLogStatus(this, wxT(" �������Ļ%d ( λ��(%d, %d))"),
                    dpy, ptScreen.x, ptScreen.y);

        ReleaseMouse();
    }
}

#if wxUSE_DISPLAY

void MyFrame::OnDisplayChanged(wxDisplayChangedEvent& event)
{
    m_book->DeleteAllPages();
    Bookctrl_Info();

    wxLogStatus(this, wxT("�ֱ����Ѹ��ģ�"));

    event.Skip();
}

#endif 

