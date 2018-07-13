
// AESDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "MyAesEn.h"
#include "afxcmn.h"

// CAESDlg 对话框
class CAESDlg : public CDialogEx
{
// 构造
public:
	CAESDlg(CWnd* pParent = NULL);	// 标准构造函数
    CMyAesEn test;
// 对话框数据
	enum { IDD = IDD_AES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
    HANDLE g_hThread;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonEn();
    afx_msg void OnBnClickedButtonDec();
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButtonFileen();
    afx_msg void OnBnClickedButtonFiledec();
    afx_msg LRESULT OnUserEditProgress(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnUserEditProgressRange(WPARAM wParam, LPARAM lParam);
    CString m_Key;
    CString m_IV;
    CString m_EnRet;
    CString m_DecRet;
    CString m_PlainText;
    CString m_FilePath;
    CString m_TagFilePath;
    CEdit m_EditPlain;
    CEdit m_EditIv;
};
