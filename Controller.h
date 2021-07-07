#pragma once
#ifndef _CONTROLLRT_H_
#define _CONTROLLRT_H_

#define PLAYER 0
#define AI 5

#define EMPTY 10
#define OFFBOARD 11
#define CHANGE 12 
#define HINT 13

#define CHANGESTONE 0

class Controller
{
public:
	Controller(void);
	~Controller(void);

	HWND hWnd;

	int m_nBoard[10][10]; //게임 판을 검사하기 위한 2차원 배열
	int m_nType;	//플레이어와 AI를 나누는 타입
	int m_nPlayerScore;	//플레이어 점수
	int m_nAIScore;	//AI점수
	int m_nStep; //뒤집히는 말의 수


	BOOL m_Playing;	//게임중인지를 판단하는 Flag

	void InitGame();	//게임 초기화
	void GameOver();	//게임 종료
	void Skip();		//말을 놓을 수 없는 경우 순서를 자동으로 넘긴다.

	int GetOtherType(int type);	//상대방의 타입 정보를 가져온다.
	int GetNext(int type);	//상대의 말 정보를 가져온다.

	BOOL CheckGameOver();	//게임이 끝난건지 판단한다.
	BOOL CheckArea(int type); //보드 검사
	BOOL LegalMove(int y, int x, int type, BOOL bFlip);	//오델로 규칙을 적용한 컨트롤러
};

#endif
