﻿#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"

class CMfcOpenCVApp : public CWinApp
{
public:
	CMfcOpenCVApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CMfcOpenCVApp theApp;
