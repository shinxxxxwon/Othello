// OthelloHistory.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Othello.h"
#include "OthelloHistory.h"
#include "afxdialogex.h"


// OthelloHistory ��ȭ �����Դϴ�.

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

// OthelloHistory �޽��� ó�����Դϴ�.

void OthelloHistory::ScoreHistory(const std::vector<CString> &v)
{
	m_Score = v;

}

void OthelloHistory::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	m_ListBox.ResetContent();
	for(auto s : m_Score)
	{
		m_ListBox.InsertString(-1, s);
	}
}
