#pragma once
#include "SocCom.h"
#include "SocServer.h"
#include "afxwin.h"


// CMyDialog ��ȭ �����Դϴ�.
class OmokWnd;
class CMyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialog)

public:
	CMyDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMyDialog();
	CSocCom *m_socCom;
	CSocServer m_socServer;
	bool m_gameTurn;
	//����� �������� Ȯ��
	//���ư��� ���� �����Ѵ�.

	//��������� ���� ������ ������Դϴ�.
	int m_time;
	CBitmap m_bitMain;
	CBitmap m_hint;
	bool start_game;
	void EndingView();
	void Shuffle();
	bool isGameEnd();
	void solve();
	//	BOOL OnInitDialog();
	void InitGame();
	void ViewPic(int iRow, int iCol, int iNum);
	bool FindEmptyIndex(int iRow, int iCol, int &iEmptyRow, int &iEmptyCol);
	bool PosToIndex(CPoint pnt, int & iRow, int & iCol);
	void MovePic(int iRow, int iCol, int iEmptyRow, int iEmptyCol);
	void ClearPic(int iRow, int iCol);
	int m_iGame[7][7];

	int getStateNum; // ���� â ��ư ���� ��������
					 // ��ȭ ���� �������Դϴ�.

	OmokWnd *omokWnd;


// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg LPARAM OnAccept(UINT wParam, LPARAM lParam);
	void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void SendData(int type, CString strTmp);
	void NumToIndex(int iNum, int & iRow, int & iCol);
	CListBox m_list;
	afx_msg void OnBnClickedButton2();
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM lParam);
	CString m_strSend;
	virtual void OnOK();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	
};
