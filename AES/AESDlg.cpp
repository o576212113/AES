
// AESDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AES.h"
#include "AESDlg.h"
#include "afxdialogex.h"
#include "MyAesEn.h"
#include "MyAesDec.h"
#include < afxdlgs.h>
#include "Command.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_USER_SETPROGRESS WM_USER + 1
#define WM_USER_SETPROGRESSRANGE WM_USER + 2

CString csTagFilePath;
CString csSrcFilePath;
CString csSrcFileName;
CString csKey;
CString csIv;

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


// CAESDlg 对话框



CAESDlg::CAESDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAESDlg::IDD, pParent)
    , m_Key(_T(""))
    , m_IV(_T(""))
    , m_EnRet(_T(""))
    , m_DecRet(_T(""))
    , m_PlainText(_T(""))
    , m_FilePath(_T(""))
    , m_TagFilePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAESDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_KEY, m_Key);
    DDX_Text(pDX, IDC_EDIT_IV, m_IV);
    DDX_Text(pDX, IDC_EDIT_ENRET, m_EnRet);
    DDX_Text(pDX, IDC_EDIT_DECRET, m_DecRet);
    DDX_Text(pDX, IDC_EDIT_PLAINTEXT, m_PlainText);
    DDX_Text(pDX, IDC_EDIT_FILEPATH, m_FilePath);
    DDX_Text(pDX, IDC_EDIT_TAGFILEPATH, m_TagFilePath);
    DDX_Control(pDX, IDC_EDIT_KEY, m_EditPlain);
    DDX_Control(pDX, IDC_EDIT_IV, m_EditIv);
}

BEGIN_MESSAGE_MAP(CAESDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &CAESDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_EN, &CAESDlg::OnBnClickedButtonEn)
    ON_BN_CLICKED(IDC_BUTTON_DEC, &CAESDlg::OnBnClickedButtonDec)
    ON_BN_CLICKED(IDC_BUTTON1, &CAESDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CAESDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON_FILEEN, &CAESDlg::OnBnClickedButtonFileen)
    ON_MESSAGE(WM_USER_SETPROGRESS, OnUserEditProgress)
    ON_MESSAGE(WM_USER_SETPROGRESSRANGE, OnUserEditProgressRange)
    ON_BN_CLICKED(IDC_BUTTON_FILEDEC, &CAESDlg::OnBnClickedButtonFiledec)
END_MESSAGE_MAP()


// CAESDlg 消息处理程序

BOOL CAESDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
   
    m_EditPlain.LimitText(16);
    m_EditIv.LimitText(16);
	// TODO:  在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAESDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAESDlg::OnPaint()
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
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAESDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAESDlg::OnBnClickedOk()
{
    // TODO:  在此添加控件通知处理程序代码
   // CDialogEx::OnOK();
}

//加密
void CAESDlg::OnBnClickedButtonEn()
{
    GetDlgItemText(IDC_EDIT_KEY, m_Key);
    GetDlgItemText(IDC_EDIT_PLAINTEXT, m_PlainText);
    GetDlgItemText(IDC_EDIT_IV, m_IV);

    if (m_Key.GetLength() < 16)
    {
        AfxMessageBox("密钥只支持16字节");
        return;
    }
    else if (m_IV.GetLength() < 16)
    {
        AfxMessageBox("IV向量只支持16字节");
        return;
    }
    else if (m_PlainText.GetLength() == 0)
    {
        AfxMessageBox("明文不能为空");
        return;
    }
    //AES加密
    char szEnText[MAXBYTE] = { 0 };

    TagEnCodeInfo enCodeInfo = { 0 };
    enCodeInfo.pPlainText = (char*)m_PlainText.GetBuffer(0);
    enCodeInfo.nPlainTextLength = m_PlainText.GetLength();
    enCodeInfo.pKey = (char*)m_Key.GetBuffer(0);
    enCodeInfo.nKeyLength = m_Key.GetLength();
    enCodeInfo.pIv = (char*)m_IV.GetBuffer(0);

    CMyAesEn enCode;
    DWORD dwLen = enCode.EnCode(enCodeInfo, szEnText);
  
    //AES加密结果再用base64编码
    char szTempbuffer[256] = { 0 };
    Base64_EnStr(base64char, (unsigned char *)szEnText, dwLen, (unsigned char *)szTempbuffer);

    //显示
    SetDlgItemText(IDC_EDIT_ENRET, szTempbuffer);

}

//解密
void CAESDlg::OnBnClickedButtonDec()
{
    GetDlgItemText(IDC_EDIT_ENRET, m_EnRet);
    GetDlgItemText(IDC_EDIT_KEY, m_Key);
    GetDlgItemText(IDC_EDIT_IV, m_IV);

    if (m_Key.GetLength() != 16)
    {
        AfxMessageBox("密钥只支持16字节");
        return;
    }
    else if (m_IV.GetLength() != 16)
    {
        AfxMessageBox("IV向量只支持16字节");
        return;
    }
    else if (m_EnRet.GetLength() == 0)
    {
        AfxMessageBox("密文不能为空");
        return;
    }

    char szDecText[MAXBYTE] = { 0 };
    CMyAesDec decCode;

    //先base64解码
    char szTempbuffer[MAXBYTE] = { 0 };
    DWORD dwLen = Base64_DecStr(base64char, m_EnRet.GetBuffer(0), m_EnRet.GetLength(), (unsigned char *)szTempbuffer);

    TagDecCodeInfo decCodeInfo = { 0 };
    decCodeInfo.pEnText = szTempbuffer;
    decCodeInfo.pEnTextLength = dwLen;
    decCodeInfo.pKey = (char*)m_Key.GetBuffer(0);
    decCodeInfo.nKeyLength = m_Key.GetLength();
    decCodeInfo.pIv = (char*)m_IV.GetBuffer(0);

    //AES解密
    decCode.DecCode(decCodeInfo, szDecText);

    //显示
    SetDlgItemText(IDC_EDIT_DECRET, szDecText);
}

//文件路径
void CAESDlg::OnBnClickedButton1()
{
    CFileDialog m_FileDialog(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, "All Files (*.*)|*.*||");

    if (m_FileDialog.DoModal() != IDOK) return;
    m_FilePath = m_FileDialog.GetPathName();
    csSrcFilePath = m_FilePath;
    csSrcFileName = m_FileDialog.GetFileName();
    SetDlgItemText(IDC_EDIT_FILEPATH, csSrcFilePath);
}

//文件生成路径
void CAESDlg::OnBnClickedButton2()
{
    char szPath[MAX_PATH];     //存放选择的目录路径 
    CString str;

    ZeroMemory(szPath, sizeof(szPath));

    BROWSEINFO bi;
    bi.hwndOwner = m_hWnd;
    bi.pidlRoot = NULL;
    bi.pszDisplayName = szPath;
    bi.lpszTitle = "请选择需要存放的目录：";
    bi.ulFlags = 0;
    bi.lpfn = NULL;
    bi.lParam = 0;
    bi.iImage = 0;
    //弹出选择目录对话框
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);

    if (lp && SHGetPathFromIDList(lp, szPath))
    {
        m_TagFilePath = szPath; 
        csTagFilePath = m_TagFilePath;
        SetDlgItemText(IDC_EDIT_TAGFILEPATH, m_TagFilePath);
    }
}

//文件加密线程
DWORD WINAPI FileEncryptThreadProc(LPVOID lpParameter)
{

    //bug-盘符下\\\\问题6
    CString cstemo = csTagFilePath;
    cstemo = cstemo + "\\" + "AES_" + csSrcFileName;
    
    //创建目标文件
    HANDLE hTagFile = CreateFileA(cstemo,
        GENERIC_READ | GENERIC_WRITE, //可读可写
        FILE_SHARE_READ,//共享读
        NULL,
        CREATE_ALWAYS, //总是创建新文件
        FILE_ATTRIBUTE_NORMAL,//正常的文件属性
        NULL);
    if (hTagFile == INVALID_HANDLE_VALUE)
    {
        AfxMessageBox(_T("创建文件失败"));
        return 0;
    }

    //打开源文件
    HANDLE hSrcFile = CreateFileA(csSrcFilePath,
        GENERIC_READ | GENERIC_WRITE, //可读可写
        FILE_SHARE_READ,//共享读
        NULL,
        OPEN_EXISTING, //总是创建新文件
        FILE_ATTRIBUTE_NORMAL,//正常的文件属性
        NULL);
    if (hSrcFile == INVALID_HANDLE_VALUE)
    {
        AfxMessageBox(_T("打开文件失败"));
        return 0;
    }

    //获取原文件大小
    DWORD dwFileSize = GetFileSize(hSrcFile, NULL);
    //::PostMessage(AfxGetApp()->m_pMainWnd->m_hWnd, WM_USER_SETPROGRESSRANGE, 0, dwFileSize);

    CMyAesEn enCode;
    TagEnCodeInfo enCodeInfo = { 0 };
    enCodeInfo.pKey = (char*)csKey.GetBuffer(0); 
    enCodeInfo.pIv = (char*)csIv.GetBuffer(0);
    TagFileInfo fileInfo = { 0 };
    fileInfo.hSrcFile = hSrcFile;
    fileInfo.hTagFile = hTagFile;

    enCode.EnFile(enCodeInfo, fileInfo);

    if (hSrcFile != NULL)
    {
        CloseHandle(hSrcFile);
    }
    if (hTagFile != NULL)
    {
        CloseHandle(hTagFile);
    }

    return 1;
}


//文件解密线程
DWORD WINAPI FileDecipherThreadProc(LPVOID lpParameter)
{

    //bug-盘符下\\\\问题
    CString  Cstemp = csTagFilePath;
    Cstemp = Cstemp + "\\" + "AES_" + csSrcFileName;

    //创建目标文件
    HANDLE hTagFile = CreateFileA(Cstemp,
        GENERIC_READ | GENERIC_WRITE, //可读可写
        FILE_SHARE_READ,//共享读
        NULL,
        CREATE_ALWAYS, //总是创建新文件
        FILE_ATTRIBUTE_NORMAL,//正常的文件属性
        NULL);
    if (hTagFile == INVALID_HANDLE_VALUE)
    {
        AfxMessageBox(_T("创建文件失败"));
        return 0;
    }

    //打开源文件
    HANDLE hSrcFile = CreateFileA(csSrcFilePath,
        GENERIC_READ | GENERIC_WRITE, //可读可写
        FILE_SHARE_READ,//共享读
        NULL,
        OPEN_EXISTING, //总是创建新文件
        FILE_ATTRIBUTE_NORMAL,//正常的文件属性
        NULL);
    if (hSrcFile == INVALID_HANDLE_VALUE)
    {
        AfxMessageBox(_T("打开文件失败"));
        return 0;
    }

    //获取原文件大小
    DWORD dwFileSize = GetFileSize(hSrcFile, NULL);
    //::PostMessage(AfxGetApp()->m_pMainWnd->m_hWnd, WM_USER_SETPROGRESSRANGE, 0, dwFileSize);

    CMyAesDec decCodes;
    TagDecCodeInfo decCodeInfo = { 0 };
    decCodeInfo.pKey = (char*)csKey.GetBuffer(0);
    decCodeInfo.pIv = (char*)csIv.GetBuffer(0);
    TagFileInfo fileInfo = { 0 };
    fileInfo.hSrcFile = hSrcFile;
    fileInfo.hTagFile = hTagFile;

    decCodes.DecFile(decCodeInfo, fileInfo);

    if (hSrcFile != NULL)
    {
        CloseHandle(hSrcFile);
    }
    if (hTagFile != NULL)
    {
        CloseHandle(hTagFile);
    }
    return 1;
}


//文件加密
void CAESDlg::OnBnClickedButtonFileen()
{
    GetDlgItemText(IDC_EDIT_KEY, csKey);
    GetDlgItemText(IDC_EDIT_IV, csIv);
    if (csKey.GetLength() != 16)
    {
        AfxMessageBox("密钥只支持16字节");
        return;
    }
    else if (csIv.GetLength() != 16)
    {
        AfxMessageBox("IV向量只支持16字节");
        return;
    }

    //文件加密线程
    g_hThread = CreateThread(NULL, 0, FileEncryptThreadProc, NULL, 0, NULL);
    AfxMessageBox("文件加密结束");
}

LRESULT CAESDlg::OnUserEditProgress(WPARAM wParam, LPARAM lParam)
{
    return 0;
}

LRESULT CAESDlg::OnUserEditProgressRange(WPARAM wParam, LPARAM lParam)
{
    return 0;
}

//文件解密
void CAESDlg::OnBnClickedButtonFiledec()
{
    GetDlgItemText(IDC_EDIT_KEY, csKey);
    GetDlgItemText(IDC_EDIT_IV, csIv);
    if (csKey.GetLength() != 16)
    {
        AfxMessageBox("密钥只支持16字节");
        return;
    }
    else if (csIv.GetLength() != 16)
    {
        AfxMessageBox("IV向量只支持16字节");
        return;
    }

    //文件加密线程
    g_hThread = CreateThread(NULL, 0, FileDecipherThreadProc, NULL, 0, NULL);
    AfxMessageBox("文件解密结束");
}

