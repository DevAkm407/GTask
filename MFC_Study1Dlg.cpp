
// MFC_Study1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Windows.h"
#include "process.h"
#include "algorithm"
#include "MFC_Study1.h"
#include "MFC_Study1Dlg.h"
#include "afxdialogex.h"
#include "string"
#include "iostream"
#include "math.h"
#include "random"
#include "vector"
#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCStudy1Dlg 대화 상자



CMFCStudy1Dlg::CMFCStudy1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_STUDY1_DIALOG, pParent)
	, m_nx1(0)
	, m_ny1(0)
	, m_nx2(0)
	, m_ny2(0)
	, m_nImgNum(0)
	, m_nradius(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCStudy1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*DDX_Control(pDX, IDC_EDIT1,snx1.Format(_T("%d"),m_nx1));
	DDX_Control(pDX, IDC_EDIT2, _T(m_ny1));*/
	DDX_Text(pDX, IDC_EDIT3_X2, m_nx2);
	DDX_Text(pDX, IDC_EDIT4_Y2, m_ny2);
	DDV_MinMaxInt(pDX, m_ny2, 30, 600);
	DDX_Text(pDX, IDC_EDIT3_X2, m_nx2);
	DDV_MinMaxInt(pDX, m_nx2, 0, 900);
	DDX_Text(pDX, IDC_EDIT2_Y1, m_ny1);
	DDV_MinMaxInt(pDX, m_ny1, 30, 600);
	DDX_Text(pDX, IDC_EDIT1_X1, m_nx1);
	DDV_MinMaxInt(pDX, m_nx1, 0, 900);
}

BEGIN_MESSAGE_MAP(CMFCStudy1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_IMAGE, &CMFCStudy1Dlg::OnBnClickedButtonImage)
	ON_BN_CLICKED(IDC_BUT_LOAD, &CMFCStudy1Dlg::OnBnClickedButLoad)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMFCStudy1Dlg::OnBnClickedBtnAction)
END_MESSAGE_MAP()


// CMFCStudy1Dlg 메시지 처리기

BOOL CMFCStudy1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCStudy1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCStudy1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCStudy1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CMFCStudy1Dlg::OnBnClickedButtonImage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CreateCircleImage();
	//UpdateData(FALSE);
	//어떤 윈도우에 그림을 그릴 것인지 그런대 CClinetDC는 Client Area 전체를 그림
	//만약 this가 아니라 다른 Dlg와 연결되어있고 그 Dlg를 숨겨 놓았다면 그곳에도 그림을 그리기 때문에
	// 잘못 사용할 경우 리소스가 낭비될 수 있음 
	//m_image.Draw(dc, 0, 0);
	
	//m_image.Save(_T("C:\\Users\\angha\\source\\repos\\MFC_Study1\\image\\save3.bmp"));
}

void CMFCStudy1Dlg::CreateCircleImage()
{
	if (m_nx1 == 0 || m_nx2 == 0 || m_ny1 == 0 || m_ny2 == 0)
	{
		MessageBox(L"범위에 맞는 값을 모두 입력해주세요.", L"알림", MB_OKCANCEL | MB_ICONINFORMATION);
		return;
	}
	int nwidth = 1000;
	int nHeight = 700;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<int> dis(100, 500);
	int nrandomnum = dis(gen);
	m_nradius = nrandomnum % 100 <= 3 ? 25 : nrandomnum % 100;
	int nGray = 80;
	int nBpp = 8;
	int nSttx = m_nx1;
	int nStty = m_ny1;
	if (!m_image.IsNull())
		m_image.Destroy();
	m_image.Create(nwidth, -nHeight, nBpp);
	if (nBpp == 8)
	{
		static RGBQUAD rgb[256]; //RGBQUAD는 바이트 타입 멤버변수 rgbBlue,rgbGreen,rgbRed,rgbReserved를 가지는 구조체이다.
		//각각 이름에 맞는 색상을 담당하고 있으며 rgbResrved는 사용되지 않는다.
		//실제로 저장되는 순서는 BGR이니 조심하자.
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}
	int nPitch = m_image.GetPitch();//현재 이미지의 피치를 바이트 단위로 검색합니다.
	std::cout << nPitch << std::endl;
	UCHAR* fm = (UCHAR*)m_image.GetBits(); //이미지가 시작되는 첫번째 좌표를 반환함
	printf("메모리주소:%p\n", fm);
	memset(fm, 0xff, nwidth * nHeight);
	UpdateDisplay();
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nwidth; j++)
		{
			fm[i * nPitch + j] = CreateCircle(j, i, m_nx1, m_ny1, m_nradius) == TRUE ? nGray : 0xff; //i증가시 열 1칸 이동 j 증가시 행 1칸이동

		}
	}
	UpdateDisplay();
	CString sImgName;
}

void CMFCStudy1Dlg::OnBnClickedButLoad()
{
	CheckCircleCenterPoint();
	//CheckCircleCenterAndRadius();
	/*m_image.Load(_T("C:\\Users\\angha\\source\\repos\\MFC_Study1\\image\\save2.bmp"));
	UpdateDisplay();
	m_image.Destroy();*/
}

void CMFCStudy1Dlg::moveCirclePlus()
{
	if(m_image.IsNull())
		CreateCircleImage();

	if (m_nx1 == 0 || m_nx2 == 0 || m_ny1 == 0 || m_ny2 == 0)
	{
		MessageBox(L"범위에 맞는 값을 모두 입력해주세요.", L"알림", MB_OKCANCEL | MB_ICONINFORMATION);
		return;
	}
	
	int nSttx=m_nx1; //static 으로 선언해서 멤버 변수로 만드는 것을 최소화
	int nStty=m_ny1;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<int> dis(100, 500);
	static std::uniform_int_distribution<int> das(100, 500);
	int nmovecirclePoint = 5;
	int nGray = 80;
	int nwidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int ny_distance = (m_ny2 - m_ny1); 
	int nx_distance = (m_nx2 - m_nx1); 
	UCHAR* fm = (UCHAR*)m_image.GetBits();
	CString sImgName;
	sImgName.Format(_T("image\\save%d.bmp"), m_nImgNum);
	m_nImgNum++;
	if (m_image.Save(sImgName) == E_FAIL)
		printf("저장실패");
	memset(fm, 0xff, nwidth * nHeight);
	//x1,y1 에서 x2,y2로가야함 선형 보간 을 사용하는것이 좋을듯?
	
	//x2-x1=x의 길이 y2-y1=y의 길이 x1=0 y1=0; x2=200 y2=400
	
	//(y-y1)/(x-x1)=(y2-y1)/(x2-x1) => y={(y2-y1)*(x-x1)/(x2-x1)}+y1
	
	//y={(400)*(x-0)/(200)}+0 => y = 2x	
	
	//nStty변화량={(도착지점y-시작지점y) * (xStty변화량-시작지점)/(도착지점x-시작지점x)+시작지점y
	
	//일단 x를 10p움직인다는 가정 그러면 위에 예시에 따라 y=2n * 10 씩 증가할 예정 그렇다면 0에서 200씩 20번 갈듯?
	
	//하지만 나머지 값이 남을 수 있음을 주의 일단 예를 y= 2x+10이라면
	
	//x를 10포인트씩 움직일거고 201만큼 가야한다면 %를 이용해서 x는1포인트 움직이고 y는 21point 움직이면 될듯
	
	//nStty = ((ny_distance * (nSttx - m_nx1)) / nx_distance) + m_ny1;
	int remain = m_nx1 != m_nx2 ? m_nx2 % 10 : 0; //일단 나머지 부터 이동
	nSttx += remain;
	//zeroDivide 발생 예외처리
	nStty = nx_distance !=0 ? std::round((( ny_distance * (nSttx - m_nx1) ) / nx_distance) + m_ny1) : m_ny1+m_ny2%10;
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nwidth; j++) 
		{
			fm[i * nPitch + j] = CreateCircle(j, i, nSttx, nStty, m_nradius) == TRUE ? nGray : 0xff;
		}
	}
	UpdateDisplay();
	sImgName.Format(_T("image\\save%d.bmp"), m_nImgNum);
	m_nImgNum++;
	if (m_image.Save(sImgName) == E_FAIL)
		printf("저장실패");
	
	//x1과x2가 다를때
	while (nSttx < m_nx2)
	{
		nSttx +=nmovecirclePoint; //x2보다 x1이 클때를 생각 
		
		//y1 과 y2의 값이 같더라도 수식의 의해 기본 좌표가 됌
		nStty = ((ny_distance * (nSttx - m_nx1)) / nx_distance) + m_ny1;
		//반지름이 0이되어버리면 너무 작음 적당히 키워주기
		for (int i = 0; i < nHeight; i++)
		{
			for (int j = 0; j < nwidth; j++)
			{
				fm[i * nPitch + j] = CreateCircle(j, i, nSttx, nStty, m_nradius) == TRUE ? nGray : 0xff;
			}
		}
		sImgName.Format(_T("image\\save%d.bmp"), m_nImgNum);
		m_nImgNum++;
		UpdateDisplay();
		if (m_image.Save(sImgName) == E_FAIL)
			printf("저장실패");
	}
	
	
	//x2와x1이 같을때
	
	printf("와일문 빠져나감\n");
	//nSttx = das(gen);
	//nStty = dis(gen);
	//printf("x 좌표:%d  y 좌표: %d\n", nSttx, nStty);
	
	//for (int i = 0; i < nHeight; i++)
	//{
	//	for (int j =0; j <nWith; j++) 
	//	{
	//		fm[i * nPitch + j] = CreateCircle(i, j, nSttx, nStty,radius) == TRUE ? nGray : 0xff;
	//	}
	//}
	
	
	
}

void CMFCStudy1Dlg::moveCircleMinus()
{
	if (m_image.IsNull())
		CreateCircleImage();

	if (m_nx1 == 0 || m_nx2 == 0 || m_ny1 == 0 || m_ny2 == 0)
	{
		MessageBox(L"범위에 맞는 값을 모두 입력해주세요.", L"알림", MB_OKCANCEL | MB_ICONINFORMATION);
		return;
	}

	int nSttx = m_nx1; //static 으로 선언해서 멤버 변수로 만드는 것을 최소화
	int nStty = m_ny1;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<int> dis(100, 500);
	static std::uniform_int_distribution<int> das(100, 500);
	int nmovecirclePoint = -5;
	int nGray = 80;
	int nwidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int ny_distance = (m_ny2 - m_ny1);
	int nx_distance = (m_nx2 - m_nx1);
	UCHAR* fm = (UCHAR*)m_image.GetBits();
	CString sImgName;
	sImgName.Format(_T("image\\save%d.bmp"), m_nImgNum);
	m_nImgNum++;
	if (m_image.Save(sImgName) == E_FAIL)
		printf("저장실패");
	memset(fm, 0xff, nwidth * nHeight);
	
	int remain = m_nx1 != m_nx2 ? m_nx2 % 10 : 0; //일단 나머지 부터 이동
	nSttx -= remain;
	//zeroDivide 발생 예외처리
	nStty = nx_distance != 0 ? std::round(((ny_distance * (nSttx - m_nx1)) / nx_distance) + m_ny1) : m_ny1 + m_ny2 % 10;
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nwidth; j++)
		{
			fm[i * nPitch + j] = CreateCircle(j, i, nSttx, nStty, m_nradius) == TRUE ? nGray : 0xff;
		}
	}
	UpdateDisplay();
	sImgName.Format(_T("image\\save%d.bmp"), m_nImgNum);
	m_nImgNum++;
	if (m_image.Save(sImgName) == E_FAIL)
		printf("저장실패");

	//x1과x2가 다를때
	while (nSttx > m_nx2)
	{
		nSttx +=  nmovecirclePoint; //x2보다 x1이 클때를 생각 

		//y1 과 y2의 값이 같더라도 수식의 의해 기본 좌표가 됌
		nStty = ((ny_distance * (nSttx - m_nx1)) / nx_distance) + m_ny1;
		for (int i = 0; i < nHeight; i++)
		{
			for (int j = 0; j < nwidth; j++)
			{
				fm[i * nPitch + j] = CreateCircle(j, i, nSttx, nStty, m_nradius) == TRUE ? nGray : 0xff;
			}
		}
		sImgName.Format(_T("image\\save%d.bmp"), m_nImgNum);
		m_nImgNum++;
		UpdateDisplay();
		if (m_image.Save(sImgName) == E_FAIL)
			printf("저장실패");

	}

	//x2와x1이 같을때

	printf("와일문 빠져나감\n");
	
}

void CMFCStudy1Dlg::moveCircleVertical()
{
	if (m_image.IsNull())
		CreateCircleImage();

	if (m_nx1 == 0 || m_nx2 == 0 || m_ny1 == 0 || m_ny2 == 0)
	{
		MessageBox(L"범위에 맞는 값을 모두 입력해주세요.", L"알림", MB_OKCANCEL | MB_ICONINFORMATION);
		return;
	}

	int nSttx = m_nx1; //static 으로 선언해서 멤버 변수로 만드는 것을 최소화
	int nStty = m_ny1;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<int> dis(100, 500);
	static std::uniform_int_distribution<int> das(100, 500);
	int nmovecirclePoint = 5;
	int nGray = 80;
	int nwidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	UCHAR* fm = (UCHAR*)m_image.GetBits();
	CString sImgName;
	sImgName.Format(_T("image\\save%d.bmp"), m_nImgNum);
	m_nImgNum++;
	

	if (m_image.Save(sImgName) == E_FAIL)
		printf("저장실패");
	memset(fm, 0xff, nwidth * nHeight);

	int remain = m_ny2 > m_ny1 ? m_ny2 % 10 : -(m_ny2 % 10);
	nStty += remain;
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nwidth; j++)
		{
			fm[i * nPitch + j] = CreateCircle(j, i, nSttx, nStty, m_nradius) == TRUE ? nGray : 0xff;
		}
	}
	UpdateDisplay();
	sImgName.Format(_T("image\\save%d.bmp"), m_nImgNum);
	m_nImgNum++;
	if (m_image.Save(sImgName) == E_FAIL)
		printf("저장실패");

	if (nStty < m_ny2)
	{
		while (nStty != m_ny2)
		{
			nStty += nmovecirclePoint; //y값만 증가 시키면됌
			for (int i = 0; i < nHeight; i++)
			{
				for (int j = 0; j < nwidth; j++)
				{
					fm[i * nPitch + j] = CreateCircle(j, i, nSttx, nStty, m_nradius) == TRUE ? nGray : 0xff;
				}
			}
			sImgName.Format(_T("image\\save%d.bmp"), m_nImgNum);
			m_nImgNum++;
			UpdateDisplay();
			if (m_image.Save(sImgName) == E_FAIL)
				printf("저장실패");

		}
	}
	else
	{
		while (nStty != m_ny2)
		{
			nStty -= nmovecirclePoint; //y값만 증가 시키면됌
			for (int i = 0; i < nHeight; i++)
			{
				for (int j = 0; j < nwidth; j++)
				{
					fm[i * nPitch + j] = CreateCircle(j, i, nSttx, nStty, m_nradius) == TRUE ? nGray : 0xff;
				}
			}
			sImgName.Format(_T("image\\save%d.bmp"), m_nImgNum);
			m_nImgNum++;
			UpdateDisplay();
			if (m_image.Save(sImgName) == E_FAIL)
				printf("저장실패");

		}
	}
}


void CMFCStudy1Dlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 40);
}

void CMFCStudy1Dlg::OnBnClickedBtnAction()
{
	HANDLE hThread;
	unsigned int threadID;
	int param = 5;
	//static 함수로 선언하지 않으면 함수포인터 8바이트보다 훨씬 커져서 static으로 선언해야함
	UpdateData(TRUE);
	hThread = (HANDLE)_beginthreadex(nullptr, 0, CMFCStudy1Dlg::ThreadFUNC,this, 0, nullptr);
}

//(x-원의 중심 x좌표 )^2 +(y -원의 중심 y좌표  )^2 = 반지름 ^2
bool CMFCStudy1Dlg::CreateCircle(int x,int y,int center_a,int center_b,int ra)
{
	int r = pow(ra, 2);
	int x_distance = pow((x - center_a), 2);
	int y_distance = pow((y - center_b), 2);
	if (x_distance + y_distance <= r)
		return true;
	return false;
}

unsigned WINAPI CMFCStudy1Dlg::ThreadFUNC(void *arg)
{
	CMFCStudy1Dlg* csd = (CMFCStudy1Dlg*)(arg); //static으로 선언해서 moveRect를 사용하기위해 자기자신이 필요함
	if (csd->m_nx1 < csd->m_nx2)
		csd->moveCirclePlus();
	else if (csd->m_nx1 > csd->m_nx2)
		csd->moveCircleMinus();
	else
		csd->moveCircleVertical();

	return 0;
}

void CMFCStudy1Dlg::CheckCircleCenterAndRadius()
{
	if(!m_image.IsNull())
		m_image.Destroy();
	/*m_image.Load(_T("C:\\Users\\angha\\source\\repos\\MFC_Study1\\image\\save24.bmp"));*/
	CString strImgPath= OpenFilePath();
	if (strImgPath.GetLength() == NULL || 0)
	{
		MessageBox(L"잘못된 파일 또는 경로입니다.", L"알림", MB_OKCANCEL | MB_ICONINFORMATION);
		return;
	}
	m_image.Load(strImgPath);
	UpdateDisplay();
	int nWith = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	UCHAR* fm = (UCHAR*)m_image.GetBits();
	std::vector<int> position;
	for (int i = 0; i < nHeight; i++)
	{
		for(int j = 0; j < nWith; j++)
		{
			if (fm[i * nPitch + j] == 80)
				position.push_back(i * nPitch + j);
		}
	}
	std::sort(position.begin(), position.end());
	int ntop = position[0];
	int nbottom = position[position.size()-1];
	int nradius = abs(nbottom - ntop) / abs(2*nPitch);
	int z = 0;
	//한줄씩 이동해야하기 때문에 nWith만큼 뺀다(nPitch 때문에)
	for (z; z > (ntop-nbottom)/2; z-=nWith)
		fm[nbottom + z] = 5; //0이나5나 똑같은 검은색 그러나 5는 희미한 불빛이 있음
	
	//가운대 점은 하얀색으로
	fm[nbottom + z] = 0xff;
	fm[nbottom + z+1] = 0xff;
	fm[nbottom + z-1] = 0xff;
	fm[nbottom + z+nWith] = 0xff;
	fm[nbottom + z+nWith+1] = 0xff;
	fm[nbottom + z+nWith-1] = 0xff;
	fm[nbottom + z-nWith] = 0xff;
	fm[nbottom + z-nWith+1] = 0xff;
	fm[nbottom + z-nWith-1] = 0xff;

	//다시 검은 선 긋기
	for ( z=z-(nWith*2); z > ntop-nbottom; z-=nWith)
	{
		fm[nbottom + z] = 5;
	}
	CString sradius;
	sradius.Format(_T("%d"), nradius);
	UpdateDisplay();
	SetDlgItemText(IDC_STATIC_RADIUS, sradius);

}


CString CMFCStudy1Dlg::OpenFilePath()
{
	CString str = _T("bmp (*.bmp) |*.bmp;|"); // 모든 파일 표시
	wchar_t wctmpPath[255];
	GetCurrentDirectory(255,wctmpPath); //현재 디렉토리의 경로 가져오기
	CString strPath;
	strPath.Format(_T("%s\\image"), wctmpPath);//결국 절대경로지만 사용할땐 상대경로처럼 사용
	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);
	dlg.m_ofn.lpstrInitialDir = strPath;
	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		return strPathName;
	}
	return NULL;
}

void CMFCStudy1Dlg::CheckCircleCenterPoint()
{
	if (!m_image.IsNull())
		m_image.Destroy();
	
	/*m_image.Load(_T("C:\\Users\\angha\\source\\repos\\MFC_Study1\\image\\save24.bmp"));*/
	CString strImgPath = OpenFilePath();
	if (strImgPath.GetLength() == NULL || 0)
	{
		MessageBox(L"잘못된 파일 또는 경로입니다.", L"알림", MB_OKCANCEL | MB_ICONINFORMATION);
		return;
	}
	m_image.Load(strImgPath);
	UpdateDisplay();
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	UCHAR* fm = (UCHAR*)m_image.GetBits();
	std::vector<int> position;
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			if (fm[i * nPitch + j] == 80)
				position.push_back(i * nPitch + j);
		}
	}
	std::sort(position.begin(), position.end());
	int ntop = position[0];
	int nbottom = position[position.size() - 1];
	int nradius = abs(nbottom - ntop) / abs(2 * nPitch);
	int z = 0;
	int xPoint = 0;
	int yPoint = 0;
	//한줄씩 이동해야하기 때문에 nWith만큼 뺀다(nPitch 때문에)
	for (z; z > (ntop - nbottom) / 2; z -= nWidth); //0이나5나 똑같은 검은색 그러나 5는 희미한 불빛이 있음
	
	//가운대 점을 X자로 만들어주기
	fm[nbottom + z] = 0xff;
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			if ((i * nPitch + j) == nbottom + z)
			{
				xPoint = j;
				yPoint = i;
			}

		}
	}
	printf("x좌표 %d\n", xPoint);
	printf("y좌표 %d\n", yPoint);
	CString sPoint;
	sPoint.Format(_T("좌표(x: %d , y: %d )"),xPoint,yPoint);
	UpdateDisplay();
	SetDlgItemText(IDC_STATIC_POINT, sPoint);
	fm[nbottom + z + nWidth + 1] = 0xff;
	fm[nbottom + z + 2*nWidth + 2] = 0xff;
	
	fm[nbottom + z + nWidth - 1] = 0xff;
	fm[nbottom + z + 2*nWidth - 2] = 0xff;
	
	fm[nbottom + z - nWidth + 1] = 0xff;
	fm[nbottom + z - 2*nWidth + 2] = 0xff;

	fm[nbottom + z - nWidth - 1] = 0xff;
	fm[nbottom + z - 2*nWidth - 2] = 0xff;

	//다시 검은 선 긋기
	/*for (z = z - (nWith * 2); z > ntop - nbottom; z -= nWith)
	{
		fm[nbottom + z] = 5;
	}*/
	//CString sradius;
	//sradius.Format(_T("%d"), nradius);
	UpdateDisplay();
	m_image.Destroy();
	//SetDlgItemText(IDC_STATIC_RADIUS, sradius);
}










