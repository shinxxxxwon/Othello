
#pragma once
#ifndef _OTHELLODLG_H_
#define _OTHELLODLG_H_
// OthelloDlg.h : ��� ����
#include "Controller.h"
#include "OthelloHistory.h"
#include <vector>


// COthelloDlg ��ȭ ����
class COthelloDlg : public CDialogEx
{
// �����Դϴ�.
public:
	COthelloDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_OTHELLO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CBitmap m_bmpBack;	//��� ��Ʈ��
	CBitmap m_bmpB[8];  //�� ��Ʈ��
	CBitmap m_bmpU[8];	//�Ʒ� �򸮴� �׸���?
	CBitmap m_bmpH[8];	//��Ʈ ��Ʈ��
	CBitmap m_bmpE1[8];	//��Ʈ ����� ��Ʈ��
	CBitmap m_bmpE2[8];	//��Ʈ ����� ��Ʈ��

	HACCEL m_hAccelTable; //����������

	Controller m_controller; //Controller Ŭ���� Ÿ�� ����
	OthelloHistory m_history;

	std::vector<CString> m_Score;

	BOOL m_bChange;
	BOOL m_bFlag;
	BOOL m_bhistory;

	int m_nBit[10][10];
	int m_nTime;

	void DrawBoard();	//����� �׸��� �޼���
	void RealDraw(int y, int x);	//���� �׸��� �޼���
	void ChangeStone();		//���� �ٲٴ� �޼���
	void DrawHint(int y, int x);	//��Ʈ�� �׸��� �޼���

	virtual BOOL PreTranslateMessage(MSG* pMsg);	//�޼����� ó���ϴ� ���� �޼���

	BOOL AIWork();
	BOOL PlayerWork(int n);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	//���콺 ��Ŭ�� ó��
	afx_msg void OnTimer(UINT_PTR nIDEvent);		
	afx_msg void OnStart();		//���� ���� �޼���
	afx_msg void OnDestroy();	//���� �޼���
	afx_msg void OnHistory();	//��� ���̾�α׸� ���� �޼���
	afx_msg void OnAcceleratorHistory();	//����Ű Ŭ���� ����(���ӽ���)  Ctrl + H
	afx_msg void OnAcceleratorStrat();		//����� Ŭ���� ����(��� â)	Ctrl + S
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};



#endif