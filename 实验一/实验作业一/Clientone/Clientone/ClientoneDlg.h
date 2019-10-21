
// ClientoneDlg.h : ͷ�ļ�
//

#pragma once
#include "MySocket.h"


// CClientoneDlg �Ի���
class CClientoneDlg : public CDialogEx
{
// ����
public:
	CClientoneDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENTONE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	CString m_serverIP;
	int m_serverPort;
	CString m_command;
	CString m_serverRe;
	MySocket m_mysocket;
	afx_msg void OnBnClickedSend();
	afx_msg void OnClose();
};
