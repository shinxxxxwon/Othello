// OthelloHistory.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Othello.h"
#include "OthelloHistory.h"
#include "afxdialogex.h"


// OthelloHistory 대화 상자입니다.

IMPLEMENT_DYNAMIC(OthelloHistory, CDialogEx)

OthelloHistory::OthelloHistory(CWnd* pParent /*=NULL*/)
	: CDialogEx(OthelloHistory::IDD, pParent)
{

}

OthelloHistory::~OthelloHistory()
{
}

void OthelloHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTBOX, m_ListBox);
}


BEGIN_MESSAGE_MAP(OthelloHistory, CDialogEx)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()

//BOOL OthelloHistory::OnInitDialog()
//{
//	m_ListBox.InsertString(-1, "TEST");
//
//	return  TRUE;
//}

// OthelloHistory 메시지 처리기입니다.

void OthelloHistory::ScoreHistory(const std::vector<CString> &v)
{
	m_Score = v;

}

void OthelloHistory::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_ListBox.ResetContent();
	for(auto s : m_Score)
	{
		m_ListBox.InsertString(-1, s);
	}
}
