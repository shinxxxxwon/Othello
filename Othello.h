
// Othello.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// COthelloApp:
// �� Ŭ������ ������ ���ؼ��� Othello.cpp�� �����Ͻʽÿ�.
//

class COthelloApp : public CWinApp
{
public:
	COthelloApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern COthelloApp theApp;