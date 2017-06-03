#pragma once

#ifndef _OMOKDLG_H
#define _OMOKDLG_H

//#include "SocCom.h"
#include "SocServer.h"
#include <afxwin.h>
#include "Resource.h"

class CSocCom;
class OmokWnd;
class OmokDlg : public CDialog {
public:
	enum { IDD10 = IDD_OMOKWND };

	OmokWnd *omokWnd;
	CSocCom *m_socCom;
	CSocServer m_socServer;

	OmokDlg(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	

	void SendData(int type, CString strTmp);

protected:
	//afx_msg void OnStartButtonClicked();
	afx_msg LPARAM OnAccept(UINT wParam, LPARAM lParam);
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM lParam);
	afx_msg void OnCreateButtonClicked();
   // afx_msg void OnClose();
	DECLARE_MESSAGE_MAP();
};

#endif
