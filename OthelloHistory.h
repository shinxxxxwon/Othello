#pragma once
#include "afxwin.h"
#include <vector>
#include "afxcmn.h"

// OthelloHistory ��ȭ �����Դϴ�.

class OthelloHistory : public CDialogEx
{
	DECLARE_DYNAMIC(OthelloHistory)

public:
	OthelloHistory(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~OthelloHistory();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_HISTROY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
