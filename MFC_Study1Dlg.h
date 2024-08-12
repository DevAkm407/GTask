
// MFC_Study1Dlg.h: 헤더 파일
//

#pragma once


// CMFCStudy1Dlg 대화 상자
class CMFCStudy1Dlg : public CDialogEx
{
// 생성입니다.
private:
	CImage m_image;
	int m_nmove_width;
	int m_nmove_height;

public:
	CMFCStudy1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_STUDY1_DIALOG };
#endif

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
	void UpdateDisplay();
	void moveCirclePlus();
	void moveCircleMinus();
	void moveCircleVertical();
	bool CreateCircle(int x, int y, int center_a, int center_b,int r);
	static unsigned WINAPI ThreadFUNC(void* arg);
	void CheckCircleCenterAndRadius();
	void CheckCircleCenterPoint();
	void CreateCircleImage();
	CString OpenFilePath();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonImage();
	afx_msg void OnBnClickedButLoad();
	afx_msg void OnBnClickedBtnAction();
	int m_ny2;
	int m_nx2;
	int m_ny1;
	int m_nx1;
	int m_nImgNum;
	int m_nradius;
};
