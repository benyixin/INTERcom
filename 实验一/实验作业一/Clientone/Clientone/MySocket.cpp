#include "stdafx.h"
#include "MySocket.h"
#include "Clientone.h"
#include "ClientoneDlg.h"
MySocket::MySocket()
	: GetBuff(_T(""))
	, GetIp(_T(""))
	, GetPort(0)
{
}


MySocket::~MySocket()
{
}


void MySocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	TCHAR buff[4096];  //���ڻ����������������ص����ݱ�
	ReceiveFrom(buff, sizeof(buff), GetIp, GetPort);	//��������������
	CString data(buff);
	GetBuff = data;

	CClientoneDlg* dig = (CClientoneDlg*)theApp.m_pMainWnd;
	dig->m_serverRe = GetBuff;
	dig->UpdateData(false);

	CAsyncSocket::OnReceive(nErrorCode);
}
