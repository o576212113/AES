
// AESDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CAESDlg �Ի���



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


// CAESDlg ��Ϣ�������

BOOL CAESDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
   
    m_EditPlain.LimitText(16);
    m_EditIv.LimitText(16);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAESDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAESDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAESDlg::OnBnClickedOk()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
   // CDialogEx::OnOK();
}

//����
void CAESDlg::OnBnClickedButtonEn()
{
    GetDlgItemText(IDC_EDIT_KEY, m_Key);
    GetDlgItemText(IDC_EDIT_PLAINTEXT, m_PlainText);
    GetDlgItemText(IDC_EDIT_IV, m_IV);

    if (m_Key.GetLength() < 16)
    {
        AfxMessageBox("��Կֻ֧��16�ֽ�");
        return;
    }
    else if (m_IV.GetLength() < 16)
    {
        AfxMessageBox("IV����ֻ֧��16�ֽ�");
        return;
    }
    else if (m_PlainText.GetLength() == 0)
    {
        AfxMessageBox("���Ĳ���Ϊ��");
        return;
    }
    //AES����
    char szEnText[MAXBYTE] = { 0 };

    TagEnCodeInfo enCodeInfo = { 0 };
    enCodeInfo.pPlainText = (char*)m_PlainText.GetBuffer(0);
    enCodeInfo.nPlainTextLength = m_PlainText.GetLength();
    enCodeInfo.pKey = (char*)m_Key.GetBuffer(0);
    enCodeInfo.nKeyLength = m_Key.GetLength();
    enCodeInfo.pIv = (char*)m_IV.GetBuffer(0);

    CMyAesEn enCode;
    DWORD dwLen = enCode.EnCode(enCodeInfo, szEnText);
  
    //AES���ܽ������base64����
    char szTempbuffer[256] = { 0 };
    Base64_EnStr(base64char, (unsigned char *)szEnText, dwLen, (unsigned char *)szTempbuffer);

    //��ʾ
    SetDlgItemText(IDC_EDIT_ENRET, szTempbuffer);

}

//����
void CAESDlg::OnBnClickedButtonDec()
{
    GetDlgItemText(IDC_EDIT_ENRET, m_EnRet);
    GetDlgItemText(IDC_EDIT_KEY, m_Key);
    GetDlgItemText(IDC_EDIT_IV, m_IV);

    if (m_Key.GetLength() != 16)
    {
        AfxMessageBox("��Կֻ֧��16�ֽ�");
        return;
    }
    else if (m_IV.GetLength() != 16)
    {
        AfxMessageBox("IV����ֻ֧��16�ֽ�");
        return;
    }
    else if (m_EnRet.GetLength() == 0)
    {
        AfxMessageBox("���Ĳ���Ϊ��");
        return;
    }

    char szDecText[MAXBYTE] = { 0 };
    CMyAesDec decCode;

    //��base64����
    char szTempbuffer[MAXBYTE] = { 0 };
    DWORD dwLen = Base64_DecStr(base64char, m_EnRet.GetBuffer(0), m_EnRet.GetLength(), (unsigned char *)szTempbuffer);

    TagDecCodeInfo decCodeInfo = { 0 };
    decCodeInfo.pEnText = szTempbuffer;
    decCodeInfo.pEnTextLength = dwLen;
    decCodeInfo.pKey = (char*)m_Key.GetBuffer(0);
    decCodeInfo.nKeyLength = m_Key.GetLength();
    decCodeInfo.pIv = (char*)m_IV.GetBuffer(0);

    //AES����
    decCode.DecCode(decCodeInfo, szDecText);

    //��ʾ
    SetDlgItemText(IDC_EDIT_DECRET, szDecText);
}

//�ļ�·��
void CAESDlg::OnBnClickedButton1()
{
    CFileDialog m_FileDialog(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, "All Files (*.*)|*.*||");

    if (m_FileDialog.DoModal() != IDOK) return;
    m_FilePath = m_FileDialog.GetPathName();
    csSrcFilePath = m_FilePath;
    csSrcFileName = m_FileDialog.GetFileName();
    SetDlgItemText(IDC_EDIT_FILEPATH, csSrcFilePath);
}

//�ļ�����·��
void CAESDlg::OnBnClickedButton2()
{
    char szPath[MAX_PATH];     //���ѡ���Ŀ¼·�� 
    CString str;

    ZeroMemory(szPath, sizeof(szPath));

    BROWSEINFO bi;
    bi.hwndOwner = m_hWnd;
    bi.pidlRoot = NULL;
    bi.pszDisplayName = szPath;
    bi.lpszTitle = "��ѡ����Ҫ��ŵ�Ŀ¼��";
    bi.ulFlags = 0;
    bi.lpfn = NULL;
    bi.lParam = 0;
    bi.iImage = 0;
    //����ѡ��Ŀ¼�Ի���
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);

    if (lp && SHGetPathFromIDList(lp, szPath))
    {
        m_TagFilePath = szPath; 
        csTagFilePath = m_TagFilePath;
        SetDlgItemText(IDC_EDIT_TAGFILEPATH, m_TagFilePath);
    }
}

//�ļ������߳�
DWORD WINAPI FileEncryptThreadProc(LPVOID lpParameter)
{

    //bug-�̷���\\\\����6
    CString cstemo = csTagFilePath;
    cstemo = cstemo + "\\" + "AES_" + csSrcFileName;
    
    //����Ŀ���ļ�
    HANDLE hTagFile = CreateFileA(cstemo,
        GENERIC_READ | GENERIC_WRITE, //�ɶ���д
        FILE_SHARE_READ,//�����
        NULL,
        CREATE_ALWAYS, //���Ǵ������ļ�
        FILE_ATTRIBUTE_NORMAL,//�������ļ�����
        NULL);
    if (hTagFile == INVALID_HANDLE_VALUE)
    {
        AfxMessageBox(_T("�����ļ�ʧ��"));
        return 0;
    }

    //��Դ�ļ�
    HANDLE hSrcFile = CreateFileA(csSrcFilePath,
        GENERIC_READ | GENERIC_WRITE, //�ɶ���д
        FILE_SHARE_READ,//�����
        NULL,
        OPEN_EXISTING, //���Ǵ������ļ�
        FILE_ATTRIBUTE_NORMAL,//�������ļ�����
        NULL);
    if (hSrcFile == INVALID_HANDLE_VALUE)
    {
        AfxMessageBox(_T("���ļ�ʧ��"));
        return 0;
    }

    //��ȡԭ�ļ���С
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


//�ļ������߳�
DWORD WINAPI FileDecipherThreadProc(LPVOID lpParameter)
{

    //bug-�̷���\\\\����
    CString  Cstemp = csTagFilePath;
    Cstemp = Cstemp + "\\" + "AES_" + csSrcFileName;

    //����Ŀ���ļ�
    HANDLE hTagFile = CreateFileA(Cstemp,
        GENERIC_READ | GENERIC_WRITE, //�ɶ���д
        FILE_SHARE_READ,//�����
        NULL,
        CREATE_ALWAYS, //���Ǵ������ļ�
        FILE_ATTRIBUTE_NORMAL,//�������ļ�����
        NULL);
    if (hTagFile == INVALID_HANDLE_VALUE)
    {
        AfxMessageBox(_T("�����ļ�ʧ��"));
        return 0;
    }

    //��Դ�ļ�
    HANDLE hSrcFile = CreateFileA(csSrcFilePath,
        GENERIC_READ | GENERIC_WRITE, //�ɶ���д
        FILE_SHARE_READ,//�����
        NULL,
        OPEN_EXISTING, //���Ǵ������ļ�
        FILE_ATTRIBUTE_NORMAL,//�������ļ�����
        NULL);
    if (hSrcFile == INVALID_HANDLE_VALUE)
    {
        AfxMessageBox(_T("���ļ�ʧ��"));
        return 0;
    }

    //��ȡԭ�ļ���С
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


//�ļ�����
void CAESDlg::OnBnClickedButtonFileen()
{
    GetDlgItemText(IDC_EDIT_KEY, csKey);
    GetDlgItemText(IDC_EDIT_IV, csIv);
    if (csKey.GetLength() != 16)
    {
        AfxMessageBox("��Կֻ֧��16�ֽ�");
        return;
    }
    else if (csIv.GetLength() != 16)
    {
        AfxMessageBox("IV����ֻ֧��16�ֽ�");
        return;
    }

    //�ļ������߳�
    g_hThread = CreateThread(NULL, 0, FileEncryptThreadProc, NULL, 0, NULL);
    AfxMessageBox("�ļ����ܽ���");
}

LRESULT CAESDlg::OnUserEditProgress(WPARAM wParam, LPARAM lParam)
{
    return 0;
}

LRESULT CAESDlg::OnUserEditProgressRange(WPARAM wParam, LPARAM lParam)
{
    return 0;
}

//�ļ�����
void CAESDlg::OnBnClickedButtonFiledec()
{
    GetDlgItemText(IDC_EDIT_KEY, csKey);
    GetDlgItemText(IDC_EDIT_IV, csIv);
    if (csKey.GetLength() != 16)
    {
        AfxMessageBox("��Կֻ֧��16�ֽ�");
        return;
    }
    else if (csIv.GetLength() != 16)
    {
        AfxMessageBox("IV����ֻ֧��16�ֽ�");
        return;
    }

    //�ļ������߳�
    g_hThread = CreateThread(NULL, 0, FileDecipherThreadProc, NULL, 0, NULL);
    AfxMessageBox("�ļ����ܽ���");
}

