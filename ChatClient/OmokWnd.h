#pragma once

#ifndef _OMOKWND_H
#define _OMOKWND_H

#include<afxwin.h>


class OmokWnd : public CWnd {
public:
	OmokWnd();
	int x, y;
	int getDoll[11][11];
	int turn;
	int whoWin; // ������ �������� Ȯ��
public:
	void OmokInner();
	void Reset();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags,CPoint point);

	DECLARE_MESSAGE_MAP()

};

#endif