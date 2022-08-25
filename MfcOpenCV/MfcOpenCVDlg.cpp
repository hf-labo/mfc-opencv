#include "pch.h"
#include "framework.h"
#include "MfcOpenCV.h"
#include "MfcOpenCVDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMfcOpenCVDlg::CMfcOpenCVDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCOPENCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcOpenCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMfcOpenCVDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

BOOL CMfcOpenCVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	mat = ::imread("C:\\Users\\furuta\\Pictures\\cat.jpg");

	return TRUE;
}

void CMfcOpenCVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

    // 生成後
    if (this->GetSafeHwnd())
    {
        // デバイスコンテキスト
        CDC* pDC = this->GetDC();
        // 矩形
        CRect rc;
        // 矩形を取得
        this->GetClientRect(rc);
        // 描画
        this->Render(pDC, rc, &this->mat);
        // デバイスコンテキスト解放
        this->ReleaseDC(pDC);
    }
}

HCURSOR CMfcOpenCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMfcOpenCVDlg::Render(CDC* pDC, const CRect& rc, Mat* src)
{
    // 入力データをクローン
    Mat img = src->clone();
    // 画像サイズを4の倍数に変更
    Size size(img.cols & ~0x03, img.rows & ~0x03);
    ::resize(img, img, size);
    // 上下反転
    ::flip(img, img, 0);

    struct MYBITMAPINFO
    {
        BITMAPINFOHEADER bmiHeader = {};
        RGBQUAD bmiColors[256] = { 0 };
        MYBITMAPINFO()
        {
            for (int i = 0; i < 256; i++)
            {
                bmiColors[i].rgbRed = bmiColors[i].rgbGreen = bmiColors[i].rgbBlue = (BYTE)i;
                bmiColors[i].rgbReserved = 0;
            }
        }
    };
    MYBITMAPINFO info = {};
    LPBITMAPINFO pInfo = reinterpret_cast<LPBITMAPINFO>(&info);
    pInfo->bmiHeader.biBitCount = (img.channels() == 1 ? 8 : 24);
    pInfo->bmiHeader.biWidth = size.width;
    pInfo->bmiHeader.biHeight = size.height;
    pInfo->bmiHeader.biPlanes = 1;
    pInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pInfo->bmiHeader.biCompression = BI_RGB;

    // 描画
    ::StretchDIBits(pDC->GetSafeHdc(),
        0, 0, size.width, size.height,
        0, 0, size.width, size.height,
        img.data, pInfo, DIB_RGB_COLORS, SRCCOPY);
}
