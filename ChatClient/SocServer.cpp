// SocServer.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ChatClient.h"
#include "SocServer.h"


// CSocServer

CSocServer::CSocServer()
{
}

CSocServer::~CSocServer()
{
}


// CSocServer ��� �Լ�
void CSocServer::Init(HWND hWnd)
{
	// ���� ������ ������ �ޱ�

	m_hWnd = hWnd;
}

void CSocServer::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	Accept(m_socCom);
	SendMessage(m_hWnd, UM_ACCEPT, 0, 0);

	CSocket::OnAccept(nErrorCode);
}

CSocCom * CSocServer::GetAcceptSocCom()
{
	// ��ż����� �����Ѵ�.
	// ��ȯ�Ǵ� ��� ������ Ŭ���̾�Ʈ�� ����ȴ�.
	return &m_socCom;
}