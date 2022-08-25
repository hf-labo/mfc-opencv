#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;

class CMfcOpenCVDlg : public CDialogEx
{
public:
	CMfcOpenCVDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCOPENCV_DIALOG };
#endif

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

protected:
	void Render(CDC* pDC, const CRect& rc, Mat* src);

protected:
	Mat mat;
};
