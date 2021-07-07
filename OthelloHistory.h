#pragma once
#include "afxwin.h"
#include <vector>
#include "afxcmn.h"

// OthelloHistory 대화 상자입니다.

class OthelloHistory : public CDialogEx
{
	DECLARE_DYNAMIC(OthelloHistory)

public:
	OthelloHistory(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~OthelloHistory();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HISTROY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	//virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public :
	
	std::vector<CString> m_Score;

	int m_nPlayerScore;
	int m_nAIScore;
	int m_nCount;
	
	CString m_strScore;

	void ScoreHistory(const std::vector<CString> &v);

	//BOOL OnInitDialog();

	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	CListBox m_ListBox;
};
