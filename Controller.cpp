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
// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

#define CENTER	190

Controller::Controller(void)
{
}


Controller::~Controller(void)
{
}

BOOL Controller::CheckGameOver()
{
	//�Ѵ� ���� ������ ���ٸ� ������ �����Ѵ�.
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
	//m_nBoard[1][1] ~ [8][8]�� �˻��Ͽ� ���� ������ �ִ��� �˻�
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

	// ���� ���� ������ ���캽
	for(int xdir=-1 ; xdir<2 ; xdir++)
	{
		for(int ydir=-1 ; ydir<2 ; ydir++)
		{
			m_nStep = 0;
			// �������� ������ �� �ִ� ���� ���� �ִ��� ��
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
					// �� �ٲٱ�
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
	//����� Ÿ���� �޾ƿ´�
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
	//���� 0���� �ʱ�ȭ
	m_nPlayerScore = 0;
	m_nAIScore = 0;

	//��� Ÿ�̸� ����
	MSG msg;
	while(::PeekMessage(&msg, hWnd, WM_TIMER, WM_TIMER, PM_REMOVE)); 

	int i, j;
	for(i=0; i<10; i++)
	{
		//[1][1] ~ [8][8]�� ���� ���� ����
		//�Ʒ� �迭���� ������ ���� ����Ű�� OFFBOARD���� �־��ش�.
		m_nBoard[i][0] = OFFBOARD;
		m_nBoard[i][9] = OFFBOARD;
		m_nBoard[0][i] = OFFBOARD;
		m_nBoard[9][i] = OFFBOARD;
	}

	for(i=1; i<9; i++)
	{
		for(j=1; j<9; j++)
		{
			//[1][1] ~ [8][8] ���� ��� ���� ���� ��������� �ʱ�ȭ
			m_nBoard[i][j] = EMPTY;
		}
	}
	//���۽� �߾ӿ� ���� ���´�.
	m_nBoard[4][4] = m_nType;
	m_nBoard[5][5] = m_nType;
	m_nBoard[4][5] = GetOtherType(m_nType);
	m_nBoard[5][4] = GetOtherType(m_nType);
}


void Controller::GameOver()
{
	//��� Timer ����
	KillTimer(hWnd, CHANGESTONE);
	MSG msg;
	while(::PeekMessage(&msg, hWnd, WM_TIMER, WM_TIMER, PM_REMOVE));
	MessageBox(hWnd, TEXT("������ ����Ǿ����ϴ�."), "GameOver", MB_OK);

	int x, y;

	for(y=1; y<9; y++)
	{
		for(x=1; x<9; x++)
		{
			//�迭�� ��ȸ�ϸ鼭 Player�� AI�� ���� ������ �������� ���� ���
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
	//������ ���Ͽ� ��, ��, ���� �Ǵ��ϰ� MessageBox�� ���
	if(m_nPlayerScore > m_nAIScore)
	{
		MessageBox(hWnd, TEXT(strScore + "\nPlayer�� �̰���ϴ�."), "GameOVer", MB_OK);
	}
	else if(m_nPlayerScore < m_nAIScore)
	{
		MessageBox(hWnd, TEXT(strScore + "\nAI�� �̰���ϴ�."), "GameOVer", MB_OK);
	}
	else
	{
		MessageBox(hWnd, TEXT(strScore + "\n���º� �Դϴ�."), "GameOVer", MB_OK);
	}
}

void Controller::Skip()
{
	MSG msg;

	while(::PeekMessage(&msg,hWnd, WM_TIMER, WM_TIMER, PM_REMOVE));

	//���濡�� ������ �ѱ��.
	if(m_nType == PLAYER)
	{
		MessageBox(hWnd, TEXT("���� ���� �ڸ��� �����ϴ�.\nAI ������ �Ѿ�ϴ�."), "SKIP", MB_OK);
	}
	else
	{
		MessageBox(hWnd, TEXT("���� ���� �ڸ��� �����ϴ�.\nPlayer ������ �Ѿ�ϴ�."), "SKIP", MB_OK);
	}

	m_nType = GetOtherType(m_nType);
}