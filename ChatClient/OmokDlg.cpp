#include "OmokDlg.h"
#include "OmokWnd.h"


BEGIN_MESSAGE_MAP(OmokDlg, CDialog)
	ON_BN_CLICKED(IDC_STARTGAME, OnStartButtonClicked)

	ON_WM_CLOSE()
END_MESSAGE_MAP()





OmokDlg::OmokDlg(CWnd *parent)
	:CDialog(OmokDlg::IDD10, parent) {

}

BOOL OmokDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	// 메모리 할당하기
	this->omokWnd = new OmokWnd;

	this->omokWnd->Create(NULL, _T("오목"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 750, 650),this,10000);

	return FALSE;
}

//버튼 눌렀을때 재시작
void OmokDlg::OnStartButtonClicked() {


	this->omokWnd->Reset();
	this->Invalidate();
}

void OmokDlg::OnClose() {
	if (this->omokWnd != NULL) {
		this->omokWnd->DestroyWindow();
		delete this->omokWnd;
	}
	EndDialog(0);
}