#include "stdafx.h"
#include "Controller.h"
#include "Othello.h"
#include "afxdialogex.h"

#define PLAYER 0
#define AI 5


#define EMPTY 10
#define OFFBOARD 11
#define CHANGE 12 

#define CHANGESTONE 0
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

#define CENTER	190

Controller::Controller(void)
{
}


Controller::~Controller(void)
{
}

BOOL Controller::CheckGameOver()
{
	//둘다 말을 놓을수 없다면 게임을 종료한다.
	int nCount = 0;
	if(CheckArea(AI))
	{
		nCount++;
	}
	if(CheckArea(PLAYER))
	{
		nCount++;
	}
	if(nCount == 2)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL Controller::CheckArea(int type)
{
	//m_nBoard[1][1] ~ [8][8]을 검사하여 말을 놓을수 있는지 검사
	int x, y;
	for(y=1 ; y<9 ; y++)
	{
		for(x=1 ; x<9 ; x++)
		{
			if(LegalMove(y, x, AI, FALSE)) 
			{
				return FALSE;
			}
			if(LegalMove(y, x, PLAYER, FALSE)) 
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL Controller::LegalMove(int y, int x, int type, BOOL bFlip)
{
	int i, j;
	BOOL bLegal = FALSE;
	int nOtherType = GetOtherType(type);
	int nCount = 0;

	if(m_nBoard[y][x] != EMPTY && m_nBoard[y][x] != HINT) 
	{
		return FALSE;
	}

	// 여덟 방향 주위를 살펴봄
	for(int xdir=-1 ; xdir<2 ; xdir++)
	{
		for(int ydir=-1 ; ydir<2 ; ydir++)
		{
			m_nStep = 0;
			// 양쪽으로 포위할 수 있는 상대방 말이 있는지 봄
			do
			{
				m_nStep++;
				i = x+m_nStep*xdir;
				j = y+m_nStep*ydir;
			} while ( i>0 && i<9 && j>0 && j<9 && m_nBoard[j][i] == nOtherType);

			if(i>0 && i<9 && j>0 && j<9 && m_nStep>1 && m_nBoard[j][i]==type)
			{
				bLegal = TRUE;
				if(bFlip)
				{
					// 말 바꾸기
					for(int k=1 ; k<m_nStep ; k++)
					{
						m_nBoard[y+ydir*k][x+xdir*k] = CHANGE;
					}
					SetTimer(hWnd ,CHANGESTONE, 10, NULL);
				}
			}
		}
	}
	return bLegal;
}

int Controller::GetNext(int type)
{
	if(m_nType == AI) return type+1;
	else return type-1;
}

int Controller::GetOtherType(int type)
{
	//상대의 타입을 받아온다
	if(m_nType == PLAYER)
	{
		return AI;
	}
	
	else
	{
		return PLAYER;
	}
}

void Controller::InitGame()
{
	//점수 0으로 초기화
	m_nPlayerScore = 0;
	m_nAIScore = 0;

	//모든 타이머 삭제
	MSG msg;
	while(::PeekMessage(&msg, hWnd, WM_TIMER, WM_TIMER, PM_REMOVE)); 

	int i, j;
	for(i=0; i<10; i++)
	{
		//[1][1] ~ [8][8]은 돌을 놓는 공간
		//아래 배열에는 보드의 끝을 가리키는 OFFBOARD값을 넣어준다.
		m_nBoard[i][0] = OFFBOARD;
		m_nBoard[i][9] = OFFBOARD;
		m_nBoard[0][i] = OFFBOARD;
		m_nBoard[9][i] = OFFBOARD;
	}

	for(i=1; i<9; i++)
	{
		for(j=1; j<9; j++)
		{
			//[1][1] ~ [8][8] 까지 모두 말이 없는 빈공간으로 초기화
			m_nBoard[i][j] = EMPTY;
		}
	}
	//시작시 중앙에 돌을 놓는다.
	m_nBoard[4][4] = m_nType;
	m_nBoard[5][5] = m_nType;
	m_nBoard[4][5] = GetOtherType(m_nType);
	m_nBoard[5][4] = GetOtherType(m_nType);
}


void Controller::GameOver()
{
	//모든 Timer 삭제
	KillTimer(hWnd, CHANGESTONE);
	MSG msg;
	while(::PeekMessage(&msg, hWnd, WM_TIMER, WM_TIMER, PM_REMOVE));
	MessageBox(hWnd, TEXT("게임이 종료되었습니다."), "GameOver", MB_OK);

	int x, y;

	for(y=1; y<9; y++)
	{
		for(x=1; x<9; x++)
		{
			//배열을 순회하면서 Player와 AI의 말의 개수를 증가시켜 점수 계산
			if(m_nBoard[y][x] == PLAYER)
			{
				m_nPlayerScore++;
			}
			else if(m_nBoard[y][x] == AI)
			{
				m_nAIScore++;
			}
		}
	}
	
	m_Playing = FALSE;
	CString strScore;
	strScore.Format("%d : %d\n", m_nPlayerScore, m_nAIScore);
	//점수를 비교하여 승, 패, 무를 판단하고 MessageBox로 출력
	if(m_nPlayerScore > m_nAIScore)
	{
		MessageBox(hWnd, TEXT(strScore + "\nPlayer가 이겼습니다."), "GameOVer", MB_OK);
	}
	else if(m_nPlayerScore < m_nAIScore)
	{
		MessageBox(hWnd, TEXT(strScore + "\nAI가 이겼습니다."), "GameOVer", MB_OK);
	}
	else
	{
		MessageBox(hWnd, TEXT(strScore + "\n무승부 입니다."), "GameOVer", MB_OK);
	}
}

void Controller::Skip()
{
	MSG msg;

	while(::PeekMessage(&msg,hWnd, WM_TIMER, WM_TIMER, PM_REMOVE));

	//상대방에게 순서를 넘긴다.
	if(m_nType == PLAYER)
	{
		MessageBox(hWnd, TEXT("말을 놓을 자리가 없습니다.\nAI 순서로 넘어갑니다."), "SKIP", MB_OK);
	}
	else
	{
		MessageBox(hWnd, TEXT("말을 놓을 자리가 없습니다.\nPlayer 순서로 넘어갑니다."), "SKIP", MB_OK);
	}

	m_nType = GetOtherType(m_nType);
}