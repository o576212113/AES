
// AESDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "MyAesEn.h"
#include "afxcmn.h"

// CAESDlg �Ի���
class CAESDlg : public CDialogEx
{
// ����
public:
	CAESDlg(CWnd* pParent = NULL);	// ��׼���캯��
    CMyAesEn test;
// �Ի�������
	enum { IDD = IDD_AES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
    HANDLE g_hThread;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
