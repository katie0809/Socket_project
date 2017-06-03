#pragma once

#ifndef _SOCSERVER_H
#define _SOCSERVER_H
#include "SocCom.h"
// CSocServer ��� ����Դϴ�.

class CSocServer : public CSocket
{
public:
	CSocServer();
	virtual ~CSocServer();
	virtual void OnAccept(int nErrorCode);

	void Init(HWND hWnd);
	HWND m_hWnd; // ���� ������ �ڵ�
	CSocCom m_socCom; // ���� ��û�� ������ ������ ����
	
	CSocCom *GetAcceptSocCom()
	{
		// ��ż����� �����Ѵ�.
		// ��ȯ�Ǵ� ��� ������ Ŭ���̾�Ʈ�� ����ȴ�.
		return &m_socCom;
	}
};


#endif //_SOCSERVER_H


