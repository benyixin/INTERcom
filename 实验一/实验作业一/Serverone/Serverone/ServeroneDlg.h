
// ServeroneDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "MySocket.h"


// CServeroneDlg 对话框
class CServeroneDlg : public CDialogEx
{
// 构造
public:
	CServeroneDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVERONE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


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
	CString m_ip;
	int m_port;
	CComboBox m_con_ip;
	CString m_date;
	CString m_time;
	CListBox m_con_list;
	MySocket m_mysocket;
	void update_date_and_time(CString& date, CString& time);
};
