#pragma once

#ifndef _OMOKDLG_H
#define _OMOKDLG_H

#include <afxwin.h>
#include "Resource.h"

class OmokWnd;
class OmokDlg : public CDialog {
public:
	enum { IDD10 = IDD_OMOKWND };

	OmokWnd *omokWnd;

	OmokDlg(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
	


protected:
	afx_msg void OnStartButtonClicked();
    afx_msg void OnClose();
	DECLARE_MESSAGE_MAP();
};

#endif
