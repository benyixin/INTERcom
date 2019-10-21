#pragma once
#include "afxsock.h"
class MySocket :
	public CAsyncSocket
{
public:
	MySocket();
	~MySocket();
	virtual void OnReceive(int nErrorCode);
public:
	CString GetBuff;
	CString GetIp;
	UINT GetPort;
};

