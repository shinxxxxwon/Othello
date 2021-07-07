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

	int m_nBoard[10][10]; //���� ���� �˻��ϱ� ���� 2���� �迭
	int m_nType;	//�÷��̾�� AI�� ������ Ÿ��
	int m_nPlayerScore;	//�÷��̾� ����
	int m_nAIScore;	//AI����
	int m_nStep; //�������� ���� ��


	BOOL m_Playing;	//������������ �Ǵ��ϴ� Flag

	void InitGame();	//���� �ʱ�ȭ
	void GameOver();	//���� ����
	void Skip();		//���� ���� �� ���� ��� ������ �ڵ����� �ѱ��.

	int GetOtherType(int type);	//������ Ÿ�� ������ �����´�.
	int GetNext(int type);	//����� �� ������ �����´�.

	BOOL CheckGameOver();	//������ �������� �Ǵ��Ѵ�.
	BOOL CheckArea(int type); //���� �˻�
	BOOL LegalMove(int y, int x, int type, BOOL bFlip);	//������ ��Ģ�� ������ ��Ʈ�ѷ�
};

#endif
