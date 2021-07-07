
// OthelloDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Othello.h"
#include "OthelloDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

#define CENTER	190
static int GY[] = {5, 53, 101, 149, 197, 245, 293, 341, 389};
static int GX[] = {48, 48, 48, 48, 48, 48, 48, 48};
static int PY[] = {45, 45, 45, 45, 45, 45, 45, 45};
static int PX[] = {48, 48, 48, 48, 48, 48, 48, 48};


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// COthelloDlg ��ȭ ����



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


// COthelloDlg �޽��� ó����

BOOL COthelloDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//���̾�α� ũ�� �缳��
	SetWindowPos(NULL, 0, 0, 400, 443, SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);


	//Accelerator�� ����
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
		//���� �ؿ� �򸮴� �׸��� ��Ʈ�� �迭�� ����
		m_bmpU[i].LoadBitmap(IDB_UNDER);
		m_bmpB[i].LoadBitmap(IDB_MAR);
		m_bmpH[i].LoadBitmap(IDB_HINT);
		m_bmpE1[i].LoadBitmap(IDB_ERASE1);
		m_bmpE2[i].LoadBitmap(IDB_ERASE2);
	}
	//Controller�� HWND ����
	m_controller.hWnd = m_hWnd;

	//���� �ʱ�ȭ
	m_controller.InitGame();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUFE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void COthelloDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR COthelloDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//������ ���� �׸��� �޼���
void COthelloDlg::DrawBoard()
{
	CClientDC dc(this);
	CDC MemDC;
	CBitmap* pOldBitmap;

	MemDC.CreateCompatibleDC(&dc);
	//��� BitMap����
	pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_bmpBack);
	//��� ��Ʈ�� ���
	dc.BitBlt(0, 0, 384, 384, &MemDC, 0, 0, SRCCOPY); 
	MemDC.SelectObject(pOldBitmap);
}

//���� �׸��� �޼���
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

		//���� �׸���.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
			//���� �ڸ��� ������ ��ŵ
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//������ �����ϴ� �޼���(����� Ctrl + S)
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

void COthelloDlg::OnHistory()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//���â�� ���� �޼���(����� Ctrl + H)
	if(!m_controller.m_Playing)
	{
		if(m_bhistory)
		{
			CString str1, str2;
			if(m_controller.m_nPlayerScore > m_controller.m_nAIScore)
			{
				str2.Format("%s", "�¸�");
			}
			else if(m_controller.m_nPlayerScore == m_controller.m_nAIScore)
			{
				str2.Format("%s", "���º�");
			}
			else
			{
				str2.Format("%s", "�й�");
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->message == WM_KEYDOWN)
	{
		//Enter. ESC Ű �Է½� ������� �ʵ��� �Ѵ�.
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	//Accelerator�� �̿��Ͽ� ������ ���۰� ���â�� ���� �ְ��Ѵ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	OnHistory();
}

void COthelloDlg::OnAcceleratorStrat()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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

	//// ù��°�� ������ ��ġ�� üũ
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

	// �ι�°�� ������ ��ġ�� üũ
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

	// ����°�� ������ ��ġ�� üũ
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

	// �׹�°�� ������ ��ġ�� üũ
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

	//�ټ���°�� ������ ��ġ�� üũ
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

	// �ְ� �� üũ
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CDialogEx::OnEraseBkgnd(pDC);
	//return FALSE;
}
