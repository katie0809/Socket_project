#include "stdafx.h"
#include "OmokDlg.h"
#include "OmokWnd.h"
#include "afxdialogex.h"
#include "SocCom.h"



BEGIN_MESSAGE_MAP(OmokDlg, CDialog)
	//ON_BN_CLICKED(IDC_STARTGAME, OnStartButtonClicked)
	ON_BN_CLICKED(IDC_CREATEBUTTON,OnCreateButtonClicked)
	ON_MESSAGE(UM_RECEIVE, OnReceive)
	ON_MESSAGE(UM_ACCEPT, OnAccept)
	ON_WM_CLOSE()
END_MESSAGE_MAP()





OmokDlg::OmokDlg(CWnd *parent)
	:CDialog(OmokDlg::IDD10, parent) {

}

BOOL OmokDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	// �޸� �Ҵ��ϱ�
	this->omokWnd = new OmokWnd;

	this->omokWnd->Create(NULL, _T("����"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 750, 650),this,10000);

	return FALSE;
}



void OmokDlg::OnCreateButtonClicked(){

	CString str;
	str.Format(L"���� ���� ����");
	AfxMessageBox(str, MB_OK);

	m_socServer.Create(5000);
	m_socServer.Listen();
	m_socServer.Init(this->m_hWnd);

}

void OmokDlg::SendData(int type, CString strTmp) {

	//send data
	UpdateData(TRUE);

	int len = strTmp.GetLength() + 1;
	LPTSTR stmp = new TCHAR[len];
	_tcscpy_s(stmp, len, strTmp);

	m_socCom->Send(stmp, 256);
}

LPARAM OmokDlg::OnAccept(UINT wParam, LPARAM lParam){

	// ��ſ� ������ �����ѵ�
	m_socCom = new CSocCom;
	// �������ϰ� ��ż����� �����Ѵ�.
	m_socCom = m_socServer.GetAcceptSocCom();
	m_socCom->Init(this->m_hWnd);

	CString str;
	str.Format(L"����� ���� ����");
	AfxMessageBox(str, MB_OK);

	UpdateData(FALSE);

	return TRUE;

}

LPARAM OmokDlg::OnReceive(UINT wParam, LPARAM lParam)
{
	char pTmp[256];

	// �����͸� pTmp�� �޴´�.
	m_socCom->Receive(pTmp, 256);

	CString temp;
	temp.Format(_T("%s"), pTmp);

	CString x;
	CString y;


	AfxExtractSubString(x, temp, 0, '~');
	AfxExtractSubString(y, temp, 1, '~');


	this->omokWnd->x = _ttoi(x);
	this->omokWnd->y = _ttoi(y);
	this->omokWnd->OmokInner();
	this->Invalidate();

	return LPARAM();
}

void OmokDlg::OnClose() {
	if (this->omokWnd != NULL) {
		this->omokWnd->DestroyWindow();
		delete this->omokWnd;
	}
	EndDialog(0);
}