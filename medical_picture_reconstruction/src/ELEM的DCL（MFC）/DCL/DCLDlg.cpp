
// DCLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DCL.h"
#include "DCLDlg.h"
#include "afxdialogex.h"
#include "IR.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DLG_FILTER "ALL Files (*.*)|*.*||" 
#define DLG_EXT   "* " 


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDCLDlg 对话框




CDCLDlg::CDCLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDCLDlg::IDD, pParent)
	, ddcishu(0)
	, beishu(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDCLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ddcishu);
	DDX_Text(pDX, IDC_EDIT3, beishu);
}

BEGIN_MESSAGE_MAP(CDCLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDCLDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDCLDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDCLDlg 消息处理程序

BOOL CDCLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	UpdateData(TRUE);
	ddcishu = 10;
	beishu = 1;
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDCLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDCLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	if(pyes!=0){
	int pi=0;
	int x0, y0;
	float fw = 1/beishu;
	float fh = 1/beishu;
	CDC* pdc=GetDC();
	for(int prow=0;prow<int(ImgRow*beishu);prow++)
	{  y0 = int(prow * fh);
	for(int pcol=0;pcol<int(ImgCol*beishu);pcol++)
	{   
		x0 = int(pcol * fw);
		pi++;
		pdc->SetPixel(pcol+20,prow+20,RGB(manypixel[x0][y0],manypixel[x0][y0],manypixel[x0][y0]));

	}

	}
	ReleaseDC(pdc);
	}




}





//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDCLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDCLDlg::OnBnClickedButton1()
{   int beishu1=beishu;
    CDC* pdc=GetDC();
	UpdateData(TRUE);
	if(beishu1!=beishu)
	{
		for(int prow = 0;prow<int(ImgRow*beishu1);prow++)
		{   for(int pcol = 0;pcol<int(ImgRow*beishu1);pcol++){
		   pdc->SetPixel(pcol+20,prow+20,RGB(240,240,240));
		}
		}

	}
	ReleaseDC(pdc);
	if(ddcishu>0)
	{
	ddnumber = ddcishu;
	}
	ImgTmp.Initilize();
	img.Initilize(1.0);
	for(int pia=0;pia<ddnumber;pia++)
	{  float maxvalue;
	int x0, y0;
	float fw = 1/beishu;
	float fh = 1/beishu;
	CDC* pdc=GetDC();
		IR(FileName,filename1,ddnumber,resultvector);


		maxvalue = resultvector.findthemaxvalue();
		int i;
		i=0;
		for(int x1 = 0;x1<128;x1++)
		{   for(int y1 = 0;y1<128;y1++){
			manypixel[y1][x1]=int(255*(resultvector.pdData[i]/maxvalue));
			i++;
		}
		}
		
	
	int pi=0;
	for(int prow=0;prow<int(ImgRow*beishu);prow++)
	{  y0 = int(prow * fh);
	for(int pcol=0;pcol<int(ImgCol*beishu);pcol++)
	{   
		x0 = int(pcol * fw);
		pi++;
		pdc->SetPixel(pcol+20,prow+20,RGB(manypixel[x0][y0],manypixel[x0][y0],manypixel[x0][y0]));

	}

	}
	


	}
	//beishu=beishu1;
	yesshow=1;
}


void CDCLDlg::OnBnClickedButton2()
{

	CFileDialog dlg(TRUE, _T(DLG_EXT), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, _T(DLG_FILTER)); 

	if (dlg.DoModal() == IDOK) 
	{ 
		POSITION pos = dlg.GetStartPosition(); 
		while (pos != 0) 
		{ 
			FileName = dlg.GetNextPathName(pos);

		} 
	} 
	yesshow = 0;
}
