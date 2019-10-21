
// ClientoneDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Clientone.h"
#include "ClientoneDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientoneDlg �Ի���



CClientoneDlg::CClientoneDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CLIENTONE_DIALOG, pParent)
	, m_serverIP(_T(""))
	, m_serverPort(2000)
	, m_command(_T(""))
	, m_serverRe(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_serverIP);
	DDX_Text(pDX, IDC_EDIT3, m_serverPort);
	DDX_Text(pDX, IDC_EDIT2, m_command);
	DDX_Text(pDX, IDC_EDIT4, m_serverRe);
}

BEGIN_MESSAGE_MAP(CClientoneDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CClientoneDlg::OnBnClickedSend)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CClientoneDlg ��Ϣ�������

BOOL CClientoneDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if (!AfxSocketInit()) {
		MessageBox(L"��ʼ��ʧ��", L"��ʾ", MB_OK | MB_ICONSTOP);
	}
	
	//
	srand((unsigned)time(NULL));
	int max = RAND_MAX;
	int client_port = (int)(rand()*(5000) / max + 2019);


	if (!m_mysocket.Create(client_port, SOCK_DGRAM, FD_READ)) {
		MessageBox(L"Socket�׽��ִ���ʧ��", L"����", MB_OK | MB_ICONSTOP);
	};
		
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CClientoneDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientoneDlg::OnPaint()
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
HCURSOR CClientoneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientoneDlg::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);	//���¿ؼ���Ӧ�ı���ֵ
	if (m_serverIP.IsEmpty())
	{
		MessageBox(_T("�޷�����Ip��ַ��"), _T("����"), MB_OK | MB_ICONEXCLAMATION); return;
	}
	if (m_serverPort <= 0 || m_serverPort> 65535)
	{
		MessageBox(_T("���������"), _T("����"), MB_OK | MB_ICONEXCLAMATION); return;
	}
	if (m_serverPort <= 0 || m_serverPort> 65535)
	{
		MessageBox(_T("�˿�ֵ����ȷ��"), _T("����"), MB_OK | MB_ICONEXCLAMATION); return;
	}

	//��������������ݱ�  UDP��ʽ
	int flag = m_mysocket.SendToEx(m_command.GetBuffer(), (m_command.GetLength() + 1) * sizeof(WCHAR), m_serverPort, m_serverIP);
	if (flag == SOCKET_ERROR) {
		MessageBox(_T("���������������ʧ�ܣ�"), _T("����"), MB_OK | MB_ICONSTOP); return;
	}
}


void CClientoneDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_mysocket.Close();
	CDialogEx::OnClose();
}
