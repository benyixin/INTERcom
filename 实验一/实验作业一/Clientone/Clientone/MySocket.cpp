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
	// TODO: 在此添加专用代码和/或调用基类

	TCHAR buff[4096];  //用于缓冲区接收主机返回的数据报
	ReceiveFrom(buff, sizeof(buff), GetIp, GetPort);	//从主机接收数据
	CString data(buff);
	GetBuff = data;

	CClientoneDlg* dig = (CClientoneDlg*)theApp.m_pMainWnd;
	dig->m_serverRe = GetBuff;
	dig->UpdateData(false);

	CAsyncSocket::OnReceive(nErrorCode);
}
