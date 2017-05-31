// puzzle_gameDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ChatClient.h"
#include "puzzle_gameDlg.h"
#include "afxdialogex.h"
#include "ChatClientDlg.h"
#include "OmokWnd.h"
#include <stdio.h>
#pragma warning(disable:4996)
using namespace std;

// puzzle_gameDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(puzzle_gameDlg, CDialogEx)

puzzle_gameDlg::puzzle_gameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
	
	CChatClientDlg *cchatclientdlg = (CChatClientDlg*)CWnd::FindWindow(L"#32770", L"Chatserver"); // ��ư ���� ���� ��������
	getStateNum = cchatclientdlg->ButtonState;

}

puzzle_gameDlg::~puzzle_gameDlg()
{
}

void puzzle_gameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(puzzle_gameDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_START, &puzzle_gameDlg::OnBnClickedStart)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_END, &puzzle_gameDlg::OnBnClickedEnd)
END_MESSAGE_MAP()




// puzzle_gameDlg �޽��� ó�����Դϴ�.

void puzzle_gameDlg::InitGame() {

	int k = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m_iGame[i][j] = k++;
		}
	}
	//���ӿ� ����� �׸� �ε��� �ʱ�ȭ. 1���� 25���� ���ʴ�� �־��ش�.
	//��, ��׵��� �� �׸������� �ε����� iNum�̴�
	//��ĭ �ε����� -1
	m_iGame[4][4] = -1; //��ĭ(=������ĭ)�� -1��

						//���̾�α� ȭ���� �ʱ�ȭ���ش�.
						//��ü�׸��� �׷��ش�.
	CClientDC pDC(this);//���� ���̾�α��� Ÿ��Ʋ�ٸ� ������ ������ ��´�.
	CPen pen;
	CBrush brush;
	pen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DFACE));
	brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));

	CPen *p = pDC.SelectObject(&pen);
	CBrush *b = pDC.SelectObject(&brush);

	pDC.Rectangle(15, 20, 15 + 5 * 61, 20 + 5 * 61);
	pDC.SelectObject(p);
	pDC.SelectObject(b);

	CDC memDC;

	memDC.CreateCompatibleDC(&pDC);//CDC�� CClinetDC�� �������ִ� ����

	CBitmap *oldbm = memDC.SelectObject(&m_hint);
	pDC.BitBlt(340, 30, 160, 160, &memDC, 0, 0, SRCCOPY);

	for (int j = 0; j < 5; j++) {
		for (int k = 0; k < 5; k++) {
			ViewPic(j, k, m_iGame[j][k]);
		}
	}
}

void puzzle_gameDlg::ViewPic(int iRow, int iCol, int iNum) {

	//25���� �׸� ������ �׷��ִ� �Լ�
	//iRow, iCol��ġ�� iNum��° �׸������� �׷��ش�.

	if (iNum == -1) {
		//�ش� ������ ��ĭ�ϰ��
		return;
	}

	int iSize = 60;
	// 300/5
	int iX = (iNum % 5);
	int iY = (iNum / 5);

	CClientDC pDC(this);
	CDC memDC;

	memDC.CreateCompatibleDC(&pDC);

	CBitmap *oldbm = memDC.SelectObject(&m_bitMain);
	pDC.BitBlt(15 + (iCol*(iSize + 1)), 20 + (iRow*(iSize + 1)), iSize, iSize, &memDC, (iX*iSize), (iY*iSize), SRCCOPY);
	memDC.SelectObject(&oldbm);
}

bool puzzle_gameDlg::FindEmptyIndex(int iRow, int iCol, int &iEmptyRow, int &iEmptyCol) {

	//�ش� �ε����� �����¿� 4������ �˻��ؼ�
	//�׸��� ������ �� �ִ� ��ĭ�� ã�´�.
	//��ã���� false ����

	if (m_iGame[iRow][iCol] == -1) {
		return false;
	}
	if (m_iGame[iRow + 1][iCol] == -1) {
		iEmptyRow = iRow + 1;
		iEmptyCol = iCol;
		return true;
	}
	if (m_iGame[iRow][iCol + 1] == -1) {
		iEmptyCol = iCol + 1;
		iEmptyRow = iRow;
		return true;
	}
	if (m_iGame[iRow - 1][iCol] == -1) {
		iEmptyRow = iRow - 1;
		iEmptyCol = iCol;
		return true;
	}
	if (m_iGame[iRow][iCol - 1] == -1) {
		iEmptyRow = iRow;
		iEmptyCol = iCol - 1;
		return true;
	}
	return false;


}

bool puzzle_gameDlg::PosToIndex(CPoint pnt, int &iRow, int &iCol) {
	//���� Ŀ���� Ŭ���� ��ġ�� �޾ƿͼ�(OnLBUttonDown)
	//iRow�� iCol�� �����ش�.
	int i = 0;
	int j = 0;

	for (j = 0; j < 5; j++) {
		if ((pnt.x > 15 + j * 61 - 1) && (pnt.x < 15 + (j + 1) * 61 - 1))
			break;
	}
	//iCol����
	for (i = 0; i < 5; i++) {
		if ((pnt.y > 20 + i * 61 - 1) && (pnt.y < 20 + (i + 1) * 61 - 1))
			break;
	}
	//iRow����


	if (i == 5 || j == 5) return false;
	//�׸� �ٱ����� Ŭ���Ѱ��
	else {
		iCol = j;
		iRow = i;
		return true;
	}

}

void puzzle_gameDlg::MovePic(int iRow, int iCol, int iEmptyRow, int iEmptyCol) {

	//emptyRow, emptyCol�� �׸������� �Ű��ش�.
	m_iGame[iEmptyRow][iEmptyCol] = m_iGame[iRow][iCol];
	ViewPic(iEmptyRow, iEmptyCol, m_iGame[iRow][iCol]);
	m_iGame[iRow][iCol] = -1;
	ClearPic(iRow, iCol);
}

void puzzle_gameDlg::ClearPic(int iRow, int iCol) {

	//�ش� ��ġ�� �׸��� �����.
	//��, ���̾�α׿� ���� ����� �ش���ġ�� 60*60ũ���� �簢���� �׷��ش�.

	CClientDC dc(this);

	CPen pen;
	CBrush brush;
	pen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DFACE));
	brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));

	CPen *p = dc.SelectObject(&pen);
	CBrush *b = dc.SelectObject(&brush);

	dc.Rectangle(15 + iCol * 61, 20 + iRow * 61, 15 + iCol * 61 + 60, 20 + iRow * 61 + 60);
	//dc handler, left, top, right, bottom ��, ���� �� �������� ������ �Ʒ� ������ ��ǥ�� �־��ش�.
	dc.SelectObject(p);
	dc.SelectObject(b);

}

void puzzle_gameDlg::EndingView() {

	//��ü�׸��� �׷��ش�.
	CClientDC pDC(this);//���� ���̾�α��� Ÿ��Ʋ�ٸ� ������ ������ ��´�.
	CDC memDC;
	CPen pen;
	CBrush brush;
	pen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DFACE));
	brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));

	CPen *p = pDC.SelectObject(&pen);
	CBrush *b = pDC.SelectObject(&brush);

	pDC.Rectangle(15, 20, 15 + 5 * 61, 20 + 5 * 61);
	pDC.SelectObject(p);
	pDC.SelectObject(b);

	memDC.CreateCompatibleDC(&pDC);//CDC�� CClinetDC�� �������ִ� ����

	CBitmap *oldbm = memDC.SelectObject(&m_bitMain);
	pDC.BitBlt(17, 23, 300, 300, &memDC, 0, 0, SRCCOPY);
	//bitblt�Լ��� ����Ͽ� ���� bmp�׸������� ȭ�鿡 ����Ѵ�.
	//��ǥ 10,10��ġ�� 300*300�� ũ��� �׸��� �׸���.
	//�����׸��� ���� �� ����Ʈ�� 0,0���� �����Ѵ�.
	//bmp������ ����ϹǷ� ��� ����� �ȼ��� �������� �Ѵ�.
}

void puzzle_gameDlg::Shuffle() {


	int iRow = -1;
	int iCol = -1;
	int iEmptyRow = -1;
	int iEmptyCol = -1;

	int count = 1000;
	//1000�� ���´�

	srand((unsigned)time(NULL));
	while (count--) {
		bool b = false;
		iRow = rand() % 5;
		iCol = rand() % 5;
		//�ε����� iRow�� iCol�� �����ϰ� �����Ѵ�.
		b = FindEmptyIndex(iRow, iCol, iEmptyRow, iEmptyCol);
		if (iRow < 0 || iCol < 0 || iEmptyCol < 0 || iEmptyRow < 0) continue;
		if (iRow > 4 || iCol > 4 || iEmptyCol > 4 || iEmptyRow > 4) continue;
		//�߸��� �ε����� ���õǴ� ��� continue;
		if (b == true) {
			MovePic(iRow, iCol, iEmptyRow, iEmptyCol);
			//			Sleep(10); //���̴� ������ �����ش�.
		}
	}

}

void puzzle_gameDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int iRow = -1;
	int iCol = -1;
	int iEmptyRow = -1;
	int iEmptyCol = -1;

	bool b = PosToIndex(point, iRow, iCol);

	if (b == true) {
		//Ŭ���ϴ� ���
		b = FindEmptyIndex(iRow, iCol, iEmptyRow, iEmptyCol);
		//�ֺ��� empty index�� ã�´�
		if (b == true) {
			//�ֺ��� ������ �� �ִ� �ε����� �ִ°��
			MovePic(iRow, iCol, iEmptyRow, iEmptyCol);
			//�ش� ��ġ�� �׸��� �ű��.

		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void puzzle_gameDlg::OnBnClickedStart()
{	//�����׸��� �����ش�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (start_game) {
		InitGame();
		Shuffle();
		SetTimer(0, 1000, NULL);
		start_game = false;
	}//start��ư �ι� �̻� ������� �������� �ʵ����Ѵ�.
	else return;
}


void puzzle_gameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CString clock = NULL;
	m_time++;
	clock.Format(_T("%02d:%02d:%02d"), m_time / 3600, m_time / 60 % 60, m_time % 60);
	SetDlgItemText(IDC_TIMER, clock);
	UpdateData(false);
	CDialogEx::OnTimer(nIDEvent);
}


BOOL puzzle_gameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (getStateNum == 1) {
		// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
		// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

		// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
		ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
		ASSERT(IDM_ABOUTBOX < 0xF000);

		CMenu* pSysMenu = GetSystemMenu(FALSE);
		if (pSysMenu != NULL)
		{
			BOOL bNameValid;
			CString strAboutMenu;
			bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
			ASSERT(bNameValid);
			if (!strAboutMenu.IsEmpty())
			{
				pSysMenu->AppendMenu(MF_SEPARATOR);
				pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
			}

			m_bitMain.LoadBitmapW(IDB_MAIN);
			//m_bitMain�̶�� ��Ʈ���� ������ IDB_MAIN�̶�� ���ҽ��� ����ϵ��� �Ѵ�
			m_hint.LoadBitmapW(IDB_HINT);
			//m_hint��� ��Ʈ���� ������ IDB_HINT��� ���ҽ��� ����ϵ����Ѵ�.
		}

		InitGame();
		m_time = 0;
		start_game = true;
		return TRUE;  // return TRUE unless you set the focus to a control
					  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
	}
	else if (getStateNum == 2) {
		// �޸� �Ҵ��ϱ�
		this->omokWnd = new OmokWnd;

		this->omokWnd->Create(NULL, _T("����"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 750, 650), this, 10000);
		return FALSE;
	}

	

	
}


void puzzle_gameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

	EndingView();

}

bool puzzle_gameDlg::isGameEnd() {

	int k = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (m_iGame[i][j] == k) continue;
			else return false;
		}
	}
	return true;
}
void puzzle_gameDlg::solve() {

	/*----------------------------------------------------------------------------*/
	//solve()����� ���� �������� �ʾҽ��ϴ�.
	//���� �����ִ� ����� �ð������� �����ϱ� ����
	//�ӽ� �ڵ��Դϴ�.
	//shuffle�� 500�� �����մϴ�.
	/*----------------------------------------------------------------------------*/

	int iRow = -1;
	int iCol = -1;
	int iEmptyRow = -1;
	int iEmptyCol = -1;

	int count = 500;
	//500�� ���´�

	srand((unsigned)time(NULL));
	while (count--) {
		bool b = false;
		iRow = rand() % 5;
		iCol = rand() % 5;
		//�ε����� iRow�� iCol�� �����ϰ� �����Ѵ�.
		b = FindEmptyIndex(iRow, iCol, iEmptyRow, iEmptyCol);
		if (iRow < 0 || iCol < 0 || iEmptyCol < 0 || iEmptyRow < 0) continue;
		if (iRow > 4 || iCol > 4 || iEmptyCol > 4 || iEmptyRow > 4) continue;
		//�߸��� �ε����� ���õǴ� ��� continue;
		if (b == true) {
			MovePic(iRow, iCol, iEmptyRow, iEmptyCol);
			Sleep(100); //���̴� ������ �����ش�.
		}
	}
	Sleep(1000);
	EndingView();
	Sleep(1000);
	return;
}

void puzzle_gameDlg::OnBnClickedEnd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	/*----------------------------------------------------------------------------------------------------------------------*/
	//
	//��ŷ ����� �߰��ϴ� �ҽ��Դϴ�.
	//
	//FILE *file;
	//file = fopen("ranking.txt", "a+");
	//��ŷ ������ �����ش�.
	//fprintf(file, "%d-%d-%d %d:%d:%d\n", t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond());
	//fclose(file);
	//
	/*----------------------------------------------------------------------------------------------------------------------*/


	CTime t;
	KillTimer(0);

	if (isGameEnd()) {
		//������ Ŭ�����Ѱ��
		AfxMessageBox(L"Congratulation, you clear the game");
	}
	else {
		//������ Ŭ�������� ���Ѱ��
		//AfxMessageBox(L"Game is not cleared=(");
		CString help;
		help.Format(_T("Sorry, you failed to finish the game"));
		SetDlgItemText(IDC_HELP, help);
		Sleep(1600);
		help.Format(_T("Now we'll show you the solution=D"));
		SetDlgItemText(IDC_HELP, help);
		Sleep(1600);
		solve();//�ַ���� �����ش�.
		Sleep(1000);
	}
	CDialogEx::OnOK();
}
