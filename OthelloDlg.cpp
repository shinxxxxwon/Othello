
// OthelloDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Othello.h"
#include "OthelloDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

#define CENTER	190
static int GY[] = {5, 53, 101, 149, 197, 245, 293, 341, 389};
static int GX[] = {48, 48, 48, 48, 48, 48, 48, 48};
static int PY[] = {45, 45, 45, 45, 45, 45, 45, 45};
static int PX[] = {48, 48, 48, 48, 48, 48, 48, 48};


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COthelloDlg 대화 상자



COthelloDlg::COthelloDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COthelloDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COthelloDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COthelloDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_START, &COthelloDlg::OnStart)
	ON_WM_DESTROY()
	ON_COMMAND(ID_HISTORY, &COthelloDlg::OnHistory)
	ON_WM_CLOSE()
	ON_COMMAND(ID_ACCELERATOR_HISTORY, &COthelloDlg::OnAcceleratorHistory)
	ON_COMMAND(ID_ACCELERATOR_STRAT, &COthelloDlg::OnAcceleratorStrat)
	ON_WM_ERASEBKGND()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// COthelloDlg 메시지 처리기

BOOL COthelloDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//다이얼로그 크기 재설정
	SetWindowPos(NULL, 0, 0, 400, 443, SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);


	//Accelerator를 연동
	m_hAccelTable = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));

	m_bmpBack.LoadBitmap(IDB_BAKC);
	m_bhistory = FALSE;
	m_controller.m_Playing = FALSE;

	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			m_nBit[i][j] = -1;
		}
	}

	for(int i=0 ; i<8 ; i++)
	{
		//말과 밑에 깔리는 그림자 비트맵 배열에 저장
		m_bmpU[i].LoadBitmap(IDB_UNDER);
		m_bmpB[i].LoadBitmap(IDB_MAR);
		m_bmpH[i].LoadBitmap(IDB_HINT);
		m_bmpE1[i].LoadBitmap(IDB_ERASE1);
		m_bmpE2[i].LoadBitmap(IDB_ERASE2);
	}
	//Controller에 HWND 복사
	m_controller.hWnd = m_hWnd;

	//게임 초기화
	m_controller.InitGame();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUFE를 반환합니다.
}

void COthelloDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void COthelloDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawBoard();
		for(int j=8 ; j>0 ; j--)
		{
			for(int i=1 ; i<9 ; i++)
			{
				RealDraw(j, i);
			}
		}
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR COthelloDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//오델로 판을 그리는 메서드
void COthelloDlg::DrawBoard()
{
	CClientDC dc(this);
	CDC MemDC;
	CBitmap* pOldBitmap;

	MemDC.CreateCompatibleDC(&dc);
	//배경 BitMap연결
	pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_bmpBack);
	//배경 비트맵 출력
	dc.BitBlt(0, 0, 384, 384, &MemDC, 0, 0, SRCCOPY); 
	MemDC.SelectObject(pOldBitmap);
}

//말을 그리는 메서드
void COthelloDlg::RealDraw(int y, int x)
{
	CClientDC dc(this);
	CDC MemDC, MemDCTemp;
	CBitmap *pOB1, *pOB2, MemBmp;

	MemDC.CreateCompatibleDC(&dc);
	MemDCTemp.CreateCompatibleDC(&dc);

	MemBmp.CreateCompatibleBitmap(&dc, PX[y-1], PY[y-1]);

	int nDrawX = CENTER + (x-5)*GX[y-1] + GX[y-1]/2 - PX[y-1]/2;
	int nDrawY = (GY[y-1]+GY[y])/2 - PY[y-1]/2 - 6;

	pOB1 = (CBitmap *)MemDCTemp.SelectObject(&m_bmpBack);
	pOB2 = (CBitmap *)MemDC.SelectObject(&MemBmp);

	

	MemDC.BitBlt(0, 0, PX[y-1], 6, &dc, nDrawX, nDrawY, SRCCOPY);
	MemDC.BitBlt(0, 6, PX[y-1], PY[y-1], &MemDCTemp, nDrawX, nDrawY+6, SRCCOPY);

	int nType = m_controller.m_nBoard[y][x];

	if(nType == CHANGE)
	{
		nType = m_controller.m_nType;
	}

	if(nType != OFFBOARD && nType != EMPTY)
	{

		//말을 그린다.
		MemDCTemp.SelectObject(&m_bmpB[y-1]);

		MemDC.TransparentBlt(0, 0, PX[y-1], PY[y-1], &MemDCTemp,  PX[y-1]*nType, 0, PX[y-1], PY[y-1], RGB(0, 0, 255));

	}
	dc.BitBlt(nDrawX, nDrawY, PX[y-1], PY[y-1], &MemDC, 0, 0, SRCCOPY);

	MemDCTemp.SelectObject(pOB1);
	MemDC.SelectObject(pOB2);
}

void COthelloDlg::DrawHint(int y, int x)
{
	CClientDC dc(this);
	CDC MemDC, MemDCTemp;
	CBitmap *pOB, MemBmp;

	MemDC.CreateCompatibleDC(&dc);
	
	MemBmp.CreateCompatibleBitmap(&dc, PX[y-1]-37, PY[y-1]-30);

	int nDrawX = CENTER + (x-5)*GX[y-1] + GX[y-1]/2 - PX[y-1]/2 + 22;
	int nDrawY = (GY[y-1]+GY[y])/2 - PY[y-1]/2+7;

	pOB = (CBitmap *)MemDC.SelectObject(&MemBmp);

	MemDC.BitBlt(0, 0, PX[y-1], 6, &dc, nDrawX, nDrawY, SRCCOPY);

	int nType = m_controller.m_nBoard[y][x];
	
	if(m_controller.m_nType == PLAYER)
	{

		MemDCTemp.SelectObject(&m_bmpH[y-1]);
		MemDC.BitBlt(0, 0, PX[y-1], PY[y-1], &MemDCTemp, PX[y-1]*nType, 0, MERGECOPY);
		dc.BitBlt(nDrawX, nDrawY, PX[y-1], PY[y-1], &MemDC, 0, 0, SRCCOPY);	
	}
	MemDC.SelectObject(pOB);
}

void COthelloDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	int i;
	int nCurX, nCurY;

	if(m_bChange && m_controller.m_nType == PLAYER /*&& m_bFlag == FALSE*/)
	{

		if(point.y >= GY[0])
		{
			for(i=0; i<8; i++)
			{
				if(point.y>=GY[i] && point.y<GY[i+1])
				{
					nCurY = i+1;
				}
			}
			nCurX = (point.x - CENTER)/GX[nCurY-1]+5;

			if(point.x - CENTER < 0)
			{
				nCurX--;
			}

			if(nCurX>=1 && nCurX<=8)
			{

				if(m_controller.LegalMove(nCurY, nCurX, m_controller.m_nType, TRUE))
				{
					m_bFlag = TRUE;
					if(m_bChange)
					{
						m_bChange = FALSE;
						m_controller.m_nBoard[nCurY][nCurX] = m_controller.m_nType;
						RealDraw(nCurY, nCurX);
					}
				}
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}



void COthelloDlg::ChangeStone()
{
	int x, y;
	BOOL bFinish = TRUE;
	BOOL bChange = FALSE;

	for(y=1 ; y<9 ; y++)
	{
		for(x=1 ; x<9 ; x++)
		{
			if(!bChange && m_controller.m_nBoard[y][x] == CHANGE)
			{
				m_controller.m_nBoard[y][x] = m_controller.GetNext(m_controller.GetOtherType(m_controller.m_nType));
				RealDraw(y, x);
				bChange = TRUE;
			}
			if(m_controller.m_nBoard[y][x]>PLAYER && m_controller.m_nBoard[y][x]<AI)
			{
				m_controller.m_nBoard[y][x] = m_controller.GetNext(m_controller.m_nBoard[y][x]);
				RealDraw(y, x);
				bFinish = FALSE;
			}
		}
	}
	if(bFinish) 
	{
		KillTimer(CHANGESTONE);
		m_controller.m_nType = m_controller.GetOtherType(m_controller.m_nType);

		if(m_controller.CheckGameOver())	
		{
			CString strScore;
			m_controller.GameOver();

			m_bhistory = TRUE;

			OnHistory();

			return;
		}

		if(m_controller.m_nType == AI) 
		{
			SetTimer(AI, 100, NULL);
		}
	}
}


void COthelloDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//AIController ai;

	switch(nIDEvent)
	{
	case CHANGESTONE :
		ChangeStone();
		m_bChange = TRUE;
		break;

	case AI :
		KillTimer(AI);
		if(m_controller.CheckGameOver())	
		{
			m_controller.GameOver();
			break;
		}
		/*if(!AIWork())
		{
			m_controller.Skip();
		}*/
		if(m_controller.CheckArea(m_controller.m_nType))
		{
			//놓을 자리가 없으면 스킵
			//m_bChange = TRUE;
			m_controller.Skip();
		}
		AIWork();
		//m_bFlag = FALSE;
		break;

	case HINT :
	/*	if(m_controller.m_nType == PLAYER)
		{
			m_nTime = 1;
		}
		PlayerWork(0);*/	
		if(m_controller.m_nType == PLAYER)
		{
			PlayerWork(0);	
			m_nTime = 1;
		}
		else if(m_controller.m_nType == AI)
		{
			if(m_nTime == 1)
			{
				for(int y=1; y<9; y++)
				{
					for(int x=1; x<9; x++)
					{
						if( m_nBit[y][x] == 99 && m_controller.m_nBoard[y][x] == EMPTY)
						{
							RealDraw(y, x);
						}
					}
				}
				m_nTime--;
			}
		}
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void COthelloDlg::OnStart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//게임을 시작하는 메서드(단축기 Ctrl + S)
	//m_bFlag = FALSE;
	m_controller.m_Playing = TRUE;
	m_controller.m_nType = PLAYER;
	m_controller.InitGame();
	m_bChange = TRUE;
	DrawBoard();
	for(int j=1 ; j<9 ; j++)
	{
		for(int i=1 ; i<9 ; i++)
		{
			RealDraw(j, i);
		}
	}
	SetTimer(HINT, 1, NULL);
}


void COthelloDlg::OnDestroy()
{
	KillTimer(CHANGESTONE);
	KillTimer(AI);
	KillTimer(HINT);

	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void COthelloDlg::OnHistory()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//기록창을 여는 메서드(단축기 Ctrl + H)
	if(!m_controller.m_Playing)
	{
		if(m_bhistory)
		{
			CString str1, str2;
			if(m_controller.m_nPlayerScore > m_controller.m_nAIScore)
			{
				str2.Format("%s", "승리");
			}
			else if(m_controller.m_nPlayerScore == m_controller.m_nAIScore)
			{
				str2.Format("%s", "무승부");
			}
			else
			{
				str2.Format("%s", "패배");
			}
			str1.Format("%2d:%2d         %s", m_controller.m_nPlayerScore, m_controller.m_nAIScore, str2);

			m_Score.push_back(str1);
			m_history.ScoreHistory(m_Score);
		}
		m_bhistory = FALSE;
		m_history.DoModal();
	}
}


BOOL COthelloDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message == WM_KEYDOWN)
	{
		//Enter. ESC 키 입력시 종료되지 않도록 한다.
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	//Accelerator를 이용하여 단축기로 시작과 기록창을 열수 있게한다.
	if(m_hAccelTable != NULL)
	{
		if(TranslateAccelerator(m_hWnd, m_hAccelTable, pMsg))
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void COthelloDlg::OnAcceleratorHistory()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnHistory();
}

void COthelloDlg::OnAcceleratorStrat()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnStart();
}


BOOL COthelloDlg::AIWork()
{
	BOOL bFound = FALSE;
	int x, y;

	int nEvaluation[10][10] = {  
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, 200, 200, 200, 200, 200, 200, 200, 200, -1},
		{-1, 200, 200, 200, 200, 200, 200, 200, 200, -1},
		{-1, 200, 200, 200, 200, 200, 200, 200, 200, -1},
		{-1, 200, 200, 200, 200, 200, 200, 200, 200, -1},
		{-1, 200, 200, 200, 200, 200, 200, 200, 200, -1},
		{-1, 200, 200, 200, 200, 200, 200, 200, 200, -1},
		{-1, 200, 200, 200, 200, 200, 200, 200, 200, -1},
		{-1, 200, 200, 200, 200, 200, 200, 200, 200, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
	};
	int nMaxPosX = 0;
	int nMaxPosY = 0;

	//// 첫번째로 유리한 위치를 체크
	if(m_controller.LegalMove(1, 1, AI, FALSE))
	{
		nEvaluation[1][1] += 100;
		nEvaluation[1][1] += m_controller.m_nStep;
	}
	if(!bFound && m_controller.LegalMove(8, 8, AI, FALSE))
	{
		nEvaluation[8][8] += 100;
		nEvaluation[8][8] += m_controller.m_nStep;
	}
	if(!bFound && m_controller.LegalMove(1, 8, AI, FALSE))
	{
		nEvaluation[1][8] += 100;
		nEvaluation[1][8] += m_controller.m_nStep;
	}
	if(!bFound && m_controller.LegalMove(8, 1, AI, FALSE))
	{
		nEvaluation[8][1] += 100;
		nEvaluation[8][1] += m_controller.m_nStep;
	}

	// 두번째로 유리한 위치를 체크
	x=3;
	while(!bFound && x<7)
	{
		y=3;
		while(!bFound && y<7)
		{
			if(m_controller.LegalMove(y, x, AI, FALSE))
			{
				nEvaluation[y][x] += 80;
				nEvaluation[y][x] += m_controller.m_nStep;
			}
			y++;
		}
		x++;
	}

	// 세번째로 유리한 위치를 체크
	x=3;
	while(!bFound && x<7)
	{
		if(m_controller.LegalMove(1, x, AI, FALSE))
		{
			nEvaluation[1][x] += 60;
			nEvaluation[1][x] += m_controller.m_nStep;
		}
		if(!bFound && m_controller.LegalMove(8, x, AI, FALSE))
		{
			nEvaluation[8][x] += 60;
			nEvaluation[8][x] += m_controller.m_nStep;
		}
		if(!bFound && m_controller.LegalMove(x, 1, AI, FALSE))
		{
			nEvaluation[x][1] += 60;
			nEvaluation[x][1] += m_controller.m_nStep;
		}
		if(!bFound && m_controller.LegalMove(x, 8, AI, FALSE))
		{
			nEvaluation[x][8] += 60;
			nEvaluation[x][8] += m_controller.m_nStep;
		}
		x++;
	}

	// 네번째로 유리한 위치를 체크
	x=3;
	while(!bFound && x<7)
	{
		if(m_controller.LegalMove(2, x, AI, FALSE))
		{
			nEvaluation[2][x] += 40;
			nEvaluation[2][x] += m_controller.m_nStep;
		}
		if(!bFound && m_controller.LegalMove(7, x, AI, FALSE))
		{

			nEvaluation[7][x] += 40;
			nEvaluation[7][x] += m_controller.m_nStep;
		}
		if(!bFound && m_controller.LegalMove(x, 2, AI, FALSE))
		{
			

			nEvaluation[x][2] += 40;
			nEvaluation[x][2] += m_controller.m_nStep;
		}
		if(!bFound && m_controller.LegalMove(x, 7, AI, FALSE))
		{

			nEvaluation[x][7] += 0;
			nEvaluation[x][7] += m_controller.m_nStep;
		}
		x++;
	}

	//다섯번째로 유리한 위치를 체크
	if(!bFound && m_controller.LegalMove(1, 2, AI, FALSE))
	{
		nEvaluation[1][2] += 20;
		nEvaluation[1][2] += m_controller.m_nStep;
	}

	if(!bFound && m_controller.LegalMove(1, 7, AI, FALSE))
	{
		nEvaluation[1][7] += 20;
		nEvaluation[1][7] += m_controller.m_nStep;
	}

	if(!bFound && m_controller.LegalMove(2, 1, AI, FALSE))
	{
		nEvaluation[2][1] += 20;
		nEvaluation[2][1] += m_controller.m_nStep;
	}

	if(!bFound && m_controller.LegalMove(2, 2, AI, FALSE))
	{
		nEvaluation[2][2] += 20;
		nEvaluation[2][2] += m_controller.m_nStep;
	}

	if(!bFound && m_controller.LegalMove(2, 7, AI, FALSE))
	{
		nEvaluation[2][7] += 20;
		nEvaluation[2][7] += m_controller.m_nStep;
	}

	if(!bFound && m_controller.LegalMove(2, 8, AI, FALSE))
	{
		nEvaluation[2][8] += 20;
		nEvaluation[2][8] += m_controller.m_nStep;
	}

	if(!bFound && m_controller.LegalMove(7, 1, AI, FALSE))
	{
		nEvaluation[7][1] += 20;
		nEvaluation[7][2] += m_controller.m_nStep;
	}

	if(!bFound && m_controller.LegalMove(7, 2, AI, FALSE))
	{
		nEvaluation[7][2] += 20;
		nEvaluation[7][2] += m_controller.m_nStep;
	}

	if(!bFound && m_controller.LegalMove(7, 7, AI, FALSE))
	{
		nEvaluation[7][7] += 20;
		nEvaluation[7][7] += m_controller.m_nStep;
	}

	if(!bFound && m_controller.LegalMove(7, 8, AI, FALSE))
	{
		nEvaluation[7][8] += 20;
		nEvaluation[7][8] += m_controller.m_nStep;
	}

	if(!bFound && m_controller.LegalMove(8, 2, AI, FALSE))
	{
		nEvaluation[8][2] += 20;
		nEvaluation[8][2] += m_controller.m_nStep;
	}

	if(!bFound && m_controller.LegalMove(8, 7, AI, FALSE))
	{
		nEvaluation[8][7] += 20;
		nEvaluation[8][7] += m_controller.m_nStep;
	}

	// 최고 평가 체크
	x=1;
	while(!bFound && x<9)
	{
		y=1;
		while(!bFound && y<9)
		{
			if(nEvaluation[y][x] >= nEvaluation[nMaxPosY][nMaxPosX])
			{
				nMaxPosX = x;
				nMaxPosY = y;
			}
			y++;
		}
		x++;
	}

	if(m_controller.LegalMove(nMaxPosY, nMaxPosX, AI, TRUE))
	{
		m_controller.m_nBoard[nMaxPosY][nMaxPosX] = AI;
		RealDraw(nMaxPosY, nMaxPosX);
		bFound = TRUE;
	}
	return bFound;
}

BOOL COthelloDlg::PlayerWork(int n)
{
	int x=1, y=1;

	while(x<9)
	{
		y=1;
		while(y<9)
		{
			if(m_controller.LegalMove(y, x, PLAYER, FALSE))
			{
				DrawHint(y, x);
				m_nBit[y][x] = 99;
			}
			y++;
		}
		x++;
	}
	return TRUE;
}


BOOL COthelloDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
	//return FALSE;
}
