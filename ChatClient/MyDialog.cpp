// MyDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ChatClient.h"
#include "MyDialog.h"
#include "afxdialogex.h"
#include "SocCom.h"
#include "OmokWnd.h"
#include "ChatClientDlg.h"
#pragma warning (disable : 4996)

// CMyDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMyDialog, CDialogEx)

CMyDialog::CMyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_strSend(_T(""))
{
	CChatClientDlg *cchatclientdlg = (CChatClientDlg*)CWnd::FindWindow(L"#32770", L"Chatserver"); // ��ư ���� ���� ��������
	getStateNum = cchatclientdlg->ButtonState;
}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_strSend);
}




// CMyDialog �޽��� ó�����Դϴ�.

LPARAM CMyDialog::OnAccept(UINT wParam, LPARAM lParam)
{
	// ��ſ� ������ �����ѵ�
	m_socCom = new CSocCom;
	// �������ϰ� ��ż����� �����Ѵ�.
	m_socCom = m_socServer.GetAcceptSocCom();
	m_socCom->Init(this->m_hWnd);

	CString str;
	str.Format(L"����� ���� ����");
	SetDlgItemText(IDC_STATIC_CONNECT, str);
	//	m_strConnect = "���Ӽ���";
	//	m_strStatus = "������ �ʱ�ȭ �Ͻʽÿ�";

	//	m_bConnect = TRUE;

	m_gameTurn = true;
	//���� ���� ����

	SetTimer(0, 1000, NULL);
	//Ÿ�̸� ����

	InitGame();
	Shuffle();

	UpdateData(FALSE);
	return TRUE;

	//	GetDlgItem(IDC_STATIC_TURN)->EnableWindow(TRUE);

}

void CMyDialog::OnBnClickedButton1()//����������ư
{
	//������ �����մϴ�
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString str;
	str.Format(L"���� ���� ����");
	SetDlgItemText(IDC_STATIC_CONNECT, str);
	
//	m_socCom = NULL;
	m_socServer.Create(5000);
	m_socServer.Listen();
	m_socServer.Init(this->m_hWnd);

	//	UpdateData(FALSE);
}



/*----------------------------------------------*/
// ��������� ���� �ҽ��Դϴ�.
// ���� ���ϰ� ������ �κ��Դϴ�.
/*----------------------------------------------*/

BOOL CMyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (getStateNum == 1) {
		// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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

			m_bitMain.LoadBitmapW(IDB_350);
			//m_bitMain�̶�� ��Ʈ���� ������ IDB_MAIN�̶�� ���ҽ��� ����ϵ��� �Ѵ�

		}

		if (!AfxSocketInit()) {
			//		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
			return false;
		}
		m_time = 20;
		InitGame();
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


void CMyDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

//	EndingView();		// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


void CMyDialog::InitGame() {

	int k = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			m_iGame[i][j] = k++;
		}
	}
	//���ӿ� ����� �׸� �ε��� �ʱ�ȭ. 1���� 25���� ���ʴ�� �־��ش�.
	//��, ��׵��� �� �׸������� �ε����� iNum�̴�
	//��ĭ �ε����� -1
	m_iGame[6][6] = -1; //��ĭ(=������ĭ)�� -1��

						//���̾�α� ȭ���� �ʱ�ȭ���ش�.
						//��ü�׸��� �׷��ش�.
	CClientDC pDC(this);//���� ���̾�α��� Ÿ��Ʋ�ٸ� ������ ������ ��´�.
	CPen pen;
	CBrush brush;
	pen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DFACE));
	brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));

	CPen *p = pDC.SelectObject(&pen);
	CBrush *b = pDC.SelectObject(&brush);

	pDC.Rectangle(15, 20, 15 + 7 * 50, 20 + 7 * 50);
	pDC.SelectObject(p);
	pDC.SelectObject(b);

	CDC memDC;

	memDC.CreateCompatibleDC(&pDC);//CDC�� CClinetDC�� �������ִ� ����

//	CBitmap *oldbm = memDC.SelectObject(&m_hint);
//	pDC.BitBlt(340, 30, 160, 160, &memDC, 0, 0, SRCCOPY);

	for (int j = 0; j < 7; j++) {
		for (int k = 0; k < 7; k++) {
			ViewPic(j, k, m_iGame[j][k]);
		}
	}
}

void CMyDialog::ViewPic(int iRow, int iCol, int iNum) {

	//25���� �׸� ������ �׷��ִ� �Լ�
	//49��
	//iRow, iCol��ġ�� iNum��° �׸������� �׷��ش�.

	if (iNum == -1) {
		//�ش� ������ ��ĭ�ϰ��
		return;
	}

	int iSize = 50;
	// 350/7
	int iX = (iNum % 7);
	int iY = (iNum / 7);

	CClientDC pDC(this);
	CDC memDC;

	memDC.CreateCompatibleDC(&pDC);

	CBitmap *oldbm = memDC.SelectObject(&m_bitMain);
	pDC.BitBlt(15 + (iCol*(iSize + 1)), 20 + (iRow*(iSize + 1)), iSize, iSize, &memDC, (iX*iSize), (iY*iSize), SRCCOPY);
	memDC.SelectObject(&oldbm);
}

bool CMyDialog::FindEmptyIndex(int iRow, int iCol, int &iEmptyRow, int &iEmptyCol) {

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

bool CMyDialog::PosToIndex(CPoint pnt, int &iRow, int &iCol) {
	//���� Ŀ���� Ŭ���� ��ġ�� �޾ƿͼ�(OnLBUttonDown)
	//iRow�� iCol�� �����ش�.
	int i = 0;
	int j = 0;

	for (j = 0; j < 7; j++) {
		if ((pnt.x > 15 + j * 51 - 1) && (pnt.x < 15 + (j + 1) * 51 - 1))
			break;
	}
	//iCol����
	for (i = 0; i < 7; i++) {
		if ((pnt.y > 20 + i * 51 - 1) && (pnt.y < 20 + (i + 1) * 51 - 1))
			break;
	}
	//iRow����


	if (i == 7 || j == 7) return false;
	//�׸� �ٱ����� Ŭ���Ѱ��
	else {
		iCol = j;
		iRow = i;
		return true;
	}

}

void CMyDialog::MovePic(int iRow, int iCol, int iEmptyRow, int iEmptyCol) {

	//emptyRow, emptyCol�� �׸������� �Ű��ش�.
	m_iGame[iEmptyRow][iEmptyCol] = m_iGame[iRow][iCol];
	ViewPic(iEmptyRow, iEmptyCol, m_iGame[iRow][iCol]);
	m_iGame[iRow][iCol] = -1;
	ClearPic(iRow, iCol);
}

void CMyDialog::ClearPic(int iRow, int iCol) {

	//�ش� ��ġ�� �׸��� �����.
	//��, ���̾�α׿� ���� ����� �ش���ġ�� 60*60ũ���� �簢���� �׷��ش�.

	CClientDC dc(this);

	CPen pen;
	CBrush brush;
	pen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DFACE));
	brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));

	CPen *p = dc.SelectObject(&pen);
	CBrush *b = dc.SelectObject(&brush);

	dc.Rectangle(15 + iCol * 51, 20 + iRow * 51, 15 + iCol * 51 + 50, 20 + iRow * 51 + 50);
	//dc handler, left, top, right, bottom ��, ���� �� �������� ������ �Ʒ� ������ ��ǥ�� �־��ش�.
	dc.SelectObject(p);
	dc.SelectObject(b);

}

void CMyDialog::EndingView() {

	//��ü�׸��� �׷��ش�.
	CClientDC pDC(this);//���� ���̾�α��� Ÿ��Ʋ�ٸ� ������ ������ ��´�.
	CDC memDC;
	CPen pen;
	CBrush brush;
	pen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DFACE));
	brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));

	CPen *p = pDC.SelectObject(&pen);
	CBrush *b = pDC.SelectObject(&brush);

	pDC.Rectangle(15, 20, 15 + 7 * 50, 20 + 7 * 50);
	pDC.SelectObject(p);
	pDC.SelectObject(b);

	memDC.CreateCompatibleDC(&pDC);//CDC�� CClinetDC�� �������ִ� ����

	CBitmap *oldbm = memDC.SelectObject(&m_bitMain);
//	pDC.StretchBlt(17, 23, 300, 300, &memDC, 0, 0, 350, 350, SRCCOPY);
	pDC.BitBlt(17, 23, 350, 350, &memDC, 0, 0, SRCCOPY);
	//bitblt�Լ��� ����Ͽ� ���� bmp�׸������� ȭ�鿡 ����Ѵ�.
	//��ǥ 10,10��ġ�� 300*300�� ũ��� �׸��� �׸���.
	//�����׸��� ���� �� ����Ʈ�� 0,0���� �����Ѵ�.
	//bmp������ ����ϹǷ� ��� ����� �ȼ��� �������� �Ѵ�.
}

void CMyDialog::Shuffle() {


	int iRow = -1;
	int iCol = -1;
	int iEmptyRow = -1;
	int iEmptyCol = -1;

	int count = 2000;
	//1000�� ���´�

	srand((unsigned)time(NULL));
	while (count--) {
		bool b = false;
		iRow = rand() % 7;
		iCol = rand() % 7;
		//�ε����� iRow�� iCol�� �����ϰ� �����Ѵ�.
		b = FindEmptyIndex(iRow, iCol, iEmptyRow, iEmptyCol);
		if (iRow < 0 || iCol < 0 || iEmptyCol < 0 || iEmptyRow < 0) continue;
		if (iRow > 6 || iCol > 6 || iEmptyCol > 6 || iEmptyRow > 6) continue;
		//�߸��� �ε����� ���õǴ� ��� continue;
		if (b == true) {
			MovePic(iRow, iCol, iEmptyRow, iEmptyCol);
			//			Sleep(10); //���̴� ������ �����ش�.
		}
	}

}

bool CMyDialog::isGameEnd() {

	int k = 0;

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (i == 6 && j == 6) break;

			if (m_iGame[i][j] == k) continue;
			else return false;
		}
	}
	return true;
}

void CMyDialog::solve() {

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
		iRow = rand() % 7;
		iCol = rand() % 7;
		//�ε����� iRow�� iCol�� �����ϰ� �����Ѵ�.
		b = FindEmptyIndex(iRow, iCol, iEmptyRow, iEmptyCol);
		if (iRow < 0 || iCol < 0 || iEmptyCol < 0 || iEmptyRow < 0) continue;
		if (iRow > 6 || iCol > 6 || iEmptyCol > 6 || iEmptyRow > 6) continue;
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

void CMyDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int iRow = -1;
	int iCol = -1;
	int iEmptyRow = -1;
	int iEmptyCol = -1;

	bool b = PosToIndex(point, iRow, iCol);
	
	if (!isGameEnd() && m_gameTurn) {
		//���� ���� �����̰� ������ ����(���� �� ��������)�������
		if (b == true) {
			//Ŭ���ϴ� ���
			b = FindEmptyIndex(iRow, iCol, iEmptyRow, iEmptyCol);
			//�ֺ��� empty index�� ã�´�
			if (b == true) {
				//�ֺ��� ������ �� �ִ� �ε����� �ִ°��
				CString str;
				str.Format(L"%d", m_iGame[iRow][iCol]);
				SendData(S_click, str);
				//�����͸� ������

				MovePic(iRow, iCol, iEmptyRow, iEmptyCol);
				//�ش� ��ġ�� �׸��� �ű��.

				KillTimer(0);
				m_gameTurn = false;
				SetDlgItemText(IDC_STATIC_CONNECT, L"Another player's turn");

			}
		}
	}
	else if (isGameEnd()) {
		//������ ��������Ǿ��� ���
		CString str;
		SendData(S_gameEnd, str);
		//�������� ��ȣ�� ������.

	}
	else {
		SetDlgItemText(IDC_STATIC_CONNECT, _T("Not your turn"));
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}



//������ �����͸� ������ �Լ��Դϴ�.
void CMyDialog::SendData(int type, CString strTmp) {

	//send data
	UpdateData(TRUE);
	char tmp[256];

	memset(tmp, '\0', 256);
	sprintf(tmp, "%d%s", type, strTmp);

	//strTmp�� ������ ��� S_gameEnd�޽��� ����
	if (strTmp == "The answer is 3") {

		SetDlgItemText(IDC_QUIZ, _T("Congratulation, You Win!"));
		strTmp.Format(_T("%d"), S_gameEnd);
		int len = strTmp.GetLength() + 1;
		LPTSTR stmp = new TCHAR[len];
		_tcscpy_s(stmp, len, strTmp);

		m_socCom->Send(stmp, 256);

		Sleep(1600);
		CDialogEx::OnOK();
		//���̾�α� ����
	}
	else {
		/*-----------------------------------------*/
		//stmp�迭�� type�� strTmp�� �޾� �������ش�.
		/*-----------------------------------------*/
		strTmp.Format(_T("%d$%s"), type, strTmp);
		//strtmp ��Ʈ���� type�� �ٿ��ش�.

		int len = strTmp.GetLength() + 1;
		LPTSTR stmp = new TCHAR[len];
		_tcscpy_s(stmp, len, strTmp);

		m_socCom->Send(stmp, 256);

		if (type == S_gameEnd) {
			Sleep(1000);
			CDialogEx::OnOK();
		}//���̾�α� ����
	}

}

void CMyDialog::NumToIndex(int iNum, int &iRow, int &iCol) {

	//���� ���ڸ� �´� �ε����� ��ȯ
	int i, j;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (iNum == m_iGame[i][j]) {
				iRow = i;
				iCol = j;
				break;
			}
		}
	}

}



void CMyDialog::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	int len = m_strSend.GetLength() + 1;
	LPTSTR tmp = new TCHAR[len];
	_tcscpy_s(tmp, len, m_strSend);
//	m_strSend.Format(_T(""));

	
	str.Format(_T("%s"), tmp);

	int i = m_list.GetCount();
	m_list.InsertString(i, str);
	// ������ ���뵵 ����Ʈ�ڽ��� �����ش�.

//	str.Format(_T("%s"), "hello");
//	SetDlgItemText(IDC_EDIT1, _T(""));

	SendData(S_chatTxt, str);

}

LPARAM CMyDialog::OnReceive(UINT wParam, LPARAM lParam)
{	
	char pTmp[256];
	CString strTmp, strType;
	int type;
	memset(pTmp, '\0', 256);

	// �����͸� pTmp�� �޴´�.
	m_socCom->Receive(pTmp, 256);

	//��� �и�
	strType.Format(_T("%c"), pTmp[0]);
	type = atoi((CStringA)strType);
	strTmp.Format(_T("%s"), pTmp);

	/*
	//�޾ƿ� ���ڿ��� ���̾�α׿� ǥ��
	CString sstr;
	sstr.Format(_T("%s"), pTmp);
	SetDlgItemText(IDC_QUIZ, sstr);
	Sleep(1000);

	//����� ���ڿ� �и��� ���̾�α׿� ǥ��
	CString token;
	AfxExtractSubString(token, sstr, 1, '$');
	SetDlgItemText(IDC_QUIZ, token);
	*/

	if (type == S_chatTxt) {
		//ä�ù��ڿ��� ���
		CString token;
		AfxExtractSubString(token, strTmp, 1, '$');
		int i = m_list.GetCount();
		m_list.InsertString(i, token);
		//���� ���뵵 ����Ʈ�ڽ��� �����ش�.
	}
	else if (type == S_click) {

		//Ÿ�̸� ����
		m_time = 20;
		SetTimer(0, 1000, NULL);

		//�� ���ʷ� �ٲ��ش�.
		m_gameTurn = true;
		SetDlgItemText(IDC_STATIC_CONNECT, L"Your turn");
		CString strIndex;
		int index;
		int iRow, iCol, iEmptyRow, iEmptyCol = -1;

		AfxExtractSubString(strIndex, strTmp, 1, '$');
		index = atoi((CStringA)strIndex);
		//�ε��� ���������� ��ȯ�Ѵ�.
		if (index != -1) {
			NumToIndex(index, iRow, iCol);
			//���� ���ڿ� �˸´� ��,�� �� ���Ѵ�
			FindEmptyIndex(iRow, iCol, iEmptyRow, iEmptyCol);
			//�ش� ��,������ �˸´� empty index ���Ѵ�
			MovePic(iRow, iCol, iEmptyRow, iEmptyCol);
			//�ش� ��ġ�� �׸����� �ű��
		}

	}
	else if (type == S_gameEnd) {
		//������ ���� ������ �������
		SetDlgItemText(IDC_QUIZ, _T("Sorry, You Lose"));
		Sleep(1000);
		CDialogEx::OnOK();
	}
	else if (type == S_gameStart) {
		//������ ���۵Ǿ���.
	}
	



	return LPARAM();
}


void CMyDialog::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	OnBnClickedButton2();
	//CDialogEx::OnOK();
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDialog::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON2, &CMyDialog::OnBnClickedButton2)
	ON_MESSAGE(UM_RECEIVE, OnReceive)
	ON_MESSAGE(UM_ACCEPT, OnAccept)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CMyDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CString clock = NULL;
	m_time--;
	clock.Format(_T("%02d"), m_time);
	SetDlgItemText(IDC_TIMER, clock);
	if (m_time == 0){
		//�ð� �ʰ��ɰ�� Ÿ�̸� ������ ���� ���ʷ� �Ѿ��.
		KillTimer(0);
		m_gameTurn = false;
		SetDlgItemText(IDC_STATIC_CONNECT, L"Another player's turn");

		CString str; int i = -1;
		str.Format(L"%d", i);
		SendData(S_click, str);
		//�����͸� ������

	}
	UpdateData(false);
	CDialogEx::OnTimer(nIDEvent);
}
