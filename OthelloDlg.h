
#pragma once
#ifndef _OTHELLODLG_H_
#define _OTHELLODLG_H_
// OthelloDlg.h : 헤더 파일
#include "Controller.h"
#include "OthelloHistory.h"
#include <vector>


// COthelloDlg 대화 상자
class COthelloDlg : public CDialogEx
{
// 생성입니다.
public:
	COthelloDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OTHELLO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CBitmap m_bmpBack;	//배경 비트맵
	CBitmap m_bmpB[8];  //말 비트맵
	CBitmap m_bmpU[8];	//아래 깔리는 그림자?
	CBitmap m_bmpH[8];	//힌트 비트맵
	CBitmap m_bmpE1[8];	//힌트 지우는 비트맵
	CBitmap m_bmpE2[8];	//힌트 지우는 비트맵

	HACCEL m_hAccelTable; //엑셀레이터

	Controller m_controller; //Controller 클래스 타입 변수
	OthelloHistory m_history;

	std::vector<CString> m_Score;

	BOOL m_bChange;
	BOOL m_bFlag;
	BOOL m_bhistory;

	int m_nBit[10][10];
	int m_nTime;

	void DrawBoard();	//배경을 그리는 메서드
	void RealDraw(int y, int x);	//말을 그리는 메서드
	void ChangeStone();		//말을 바꾸는 메서드
	void DrawHint(int y, int x);	//힌트를 그리는 메서드

	virtual BOOL PreTranslateMessage(MSG* pMsg);	//메세지를 처리하는 가상 메서드

	BOOL AIWork();
	BOOL PlayerWork(int n);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	//마우스 좌클릭 처리
	afx_msg void OnTimer(UINT_PTR nIDEvent);		
	afx_msg void OnStart();		//게임 시작 메서드
	afx_msg void OnDestroy();	//종료 메서드
	afx_msg void OnHistory();	//기록 다이얼로그를 여는 메서드
	afx_msg void OnAcceleratorHistory();	//단축키 클릭시 실행(게임시작)  Ctrl + H
	afx_msg void OnAcceleratorStrat();		//단축기 클릭시 실행(기록 창)	Ctrl + S
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};



#endif