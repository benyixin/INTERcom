#include "stdafx.h"
#include "MySocket.h"
#include "Serverone.h"
#include "ServeroneDlg.h"
MySocket::MySocket()
{
}


MySocket::~MySocket()
{
}


void MySocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CServeroneDlg* dig = (CServeroneDlg*)theApp.m_pMainWnd; //��ȡ�Ի�����
	TCHAR buff[4096];
	CString GetIP;
	UINT GetPort;
	ReceiveFrom(buff, 4096, GetIP, GetPort);
	CString data(buff);
	CString temp = data;

	dig->update_date_and_time(dig->m_date, dig->m_time);

	CString Answer = _T("��������");
	data.MakeLower();

	if (data == "time")
		Answer = dig->m_time;
	if (data == "date")
		Answer = dig->m_date;

	//��Ӧ�ͻ��˳���
	SendToEx(Answer.GetBuffer(), (Answer.GetLength() + 1) * sizeof(WCHAR), GetPort, GetIP);
	CString record;
	record.Format(L":�յ�IP=%s Port=%u����%s��,��Ӧ��%s��", GetIP, GetPort, temp, Answer);
	dig->m_con_list.AddString(dig->m_date + _T(" ") + dig->m_time + record);

	CAsyncSocket::OnReceive(nErrorCode);
}
