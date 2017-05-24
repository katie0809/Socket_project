#include "OmokWnd.h"
#include "OmokWndApp.h"

BOOL OmokWndApp::InitInstance() {
	OmokWnd *omokwnd = new OmokWnd();

	omokwnd->Create(NULL, "¿À¸ñ", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CRect(100, 100, 850, 850));
	m_pMainWnd = omokwnd;
	omokwnd->ShowWindow(SW_SHOW);
	omokwnd->UpdateWindow();

	return TRUE;
};
OmokWndApp theApp;