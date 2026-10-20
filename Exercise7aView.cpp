
// Exercise7aView.cpp: CExercise7aView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Exercise7a.h"
#endif

#include "Exercise7aDoc.h"
#include "Exercise7aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define RECTANGLE_MODE 1
#define CIRCLE_MODE 2
#define _USE_MATH_DEFINES
#include <math.h>
#include "MainFrm.h"
#endif


// CExercise7aView

IMPLEMENT_DYNCREATE(CExercise7aView, CView)

BEGIN_MESSAGE_MAP(CExercise7aView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CExercise7aView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_RECTANGLE, &CExercise7aView::OnRectangle)
	ON_COMMAND(ID_CIRCLE, &CExercise7aView::OnCircle)
	ON_COMMAND(ID_INCREASE, &CExercise7aView::OnIncrease)
	ON_COMMAND(ID_DECREASE, &CExercise7aView::OnDecrease)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CExercise7aView 생성/소멸

CExercise7aView::CExercise7aView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_bLButtonDown = FALSE;        // 마우스 왼쪽 버튼이 눌리지 않은 상태로 초기화
	m_rtRect = CRect(0, 0, 0, 0);  // 사각형 영역(좌, 상, 우, 하)을 0으로 초기화
	m_nResolution = 64;            // 원의 해상도 기본값을 64로 설정

	// 원의 좌표를 저장할 배열(0~1023번)을 모두 (0,0) 좌표로 초기화
	for (int i = 0; i < 1024; i++)
	{
		m_ptCircle[i] = CPoint(0, 0);
	}

}

CExercise7aView::~CExercise7aView()
{
}

BOOL CExercise7aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CExercise7aView 그리기

void CExercise7aView::OnDraw(CDC* /*pDC*/)
{
	CExercise7aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CExercise7aView 인쇄


void CExercise7aView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CExercise7aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CExercise7aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CExercise7aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CExercise7aView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CExercise7aView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExercise7aView 진단

#ifdef _DEBUG
void CExercise7aView::AssertValid() const
{
	CView::AssertValid();
}

void CExercise7aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExercise7aDoc* CExercise7aView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExercise7aDoc)));
	return (CExercise7aDoc*)m_pDocument;
}
#endif //_DEBUG


// CExercise7aView 메시지 처리기

void CExercise7aView::OnRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = RECTANGLE_MODE;
}

void CExercise7aView::OnCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = CIRCLE_MODE;
}

void CExercise7aView::OnIncrease()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_nResolution >= 1024)
		AfxMessageBox(_T("현재 최대 해상도인 1024입니다."));
	else
		m_nResolution = m_nResolution * 2;
	ComputeCircle(); // 원 좌표 재계산
	Invalidate(); // 화면 갱신
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CString strResol;
	strResol.Format(_T("해상도 : %d"), m_nResolution);
	// 추가한 팬에 마우스 위치 출력
	pFrame->m_wndStatusBar.SetPaneText(1, strResol);
}

void CExercise7aView::OnDecrease()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_nResolution <= 2)
		AfxMessageBox(_T("현재 최소 해상도인 2입니다."));
	else
		m_nResolution = m_nResolution / 2;
	ComputeCircle(); // 원 좌표 재계산
	Invalidate(); // 화면 갱신
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CString strResol;
	strResol.Format(_T("해상도 : %d"), m_nResolution);
	// 추가한 팬에 마우스 위치 출력
	pFrame->m_wndStatusBar.SetPaneText(1, strResol);
}

void CExercise7aView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (m_nDrawMode) {
	case RECTANGLE_MODE:
		m_rtRect = CRect(0, 0, 0, 0); // 사각형 초기화
	case CIRCLE_MODE:
		m_ptStart = m_ptPrev = point;//시작점과 이전점에 현재점 저장
		m_bLButtonDown = true; //왼쪽버튼이 눌림
		for (int i = 0; i < 1024; i++) // 원 초기화
			m_ptCircle[i] = CPoint(0, 0);
		Invalidate(TRUE);
		break;
	}
	RECT rectClient; // 구조체 변수 선언
	SetCapture(); // 마우스 캡쳐           
	GetClientRect(&rectClient); // 클라이언트 영역 얻음
	ClientToScreen(&rectClient); // 스크린 좌표계로 변환 
	::ClipCursor(&rectClient); // 마우스 이동범위를 클라이언트 영역으로 제한
	CView::OnLButtonDown(nFlags, point);
}

void CExercise7aView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this); // 클라이언트 객체 얻음
	int i;
	CPen pen, * oldpen;    // Pen 객체 생성
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // Pen 객체 등록
	oldpen = dc.SelectObject(&pen);
	dc.SetROP2(R2_NOTXORPEN); // R2_NOTXORPEN 으로 설정
	switch (m_nDrawMode)
	{
	case RECTANGLE_MODE:
		if (m_bLButtonDown)
		{
			//이전 사각형을 지움 
			dc.Rectangle(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			//현재 사각형을 그림
			dc.Rectangle(m_ptStart.x, m_ptStart.y, point.x, point.y);
			m_ptPrev = point; //이전 점에 현재점 저장
		}
		break;
	case CIRCLE_MODE:
		if (m_bLButtonDown)
		{
			dc.IntersectClipRect(m_rtRect); // 클리핑 영역 설정
			// 이전 원 지움
			ComputeCircle();
			dc.MoveTo(m_ptCircle[0]);
			for (i = 0; i < m_nResolution; i++) {
				dc.LineTo(m_ptCircle[i]);
			}
			dc.LineTo(m_ptCircle[0]);
			// 현재 원 그림
			m_ptPrev = point; // 이전 점에 현재점을 저장
			ComputeCircle();
			dc.MoveTo(m_ptCircle[0]);
			for (i = 0; i < m_nResolution; i++) {
				dc.LineTo(m_ptCircle[i]);
			}
			dc.LineTo(m_ptCircle[0]);
		}
		break;
	}
	dc.SelectObject(oldpen);
	pen.DeleteObject();
	CView::OnMouseMove(nFlags, point);
}

void CExercise7aView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (m_nDrawMode)
	{
	case RECTANGLE_MODE:
		if (m_bLButtonDown)
		{
			m_bLButtonDown = false;
			m_rtRect = CRect(m_ptStart.x, m_ptStart.y, point.x, point.y);  // 사각형 좌표 저장
		}
		break;
	case CIRCLE_MODE:
		if (m_bLButtonDown)
		{
			m_bLButtonDown = false;
		}
		break;
	}
	ReleaseCapture(); //마우스 캡쳐 해제
	::ClipCursor(NULL); //마우스 클립 해제
	Invalidate(true); //화면갱신

	CView::OnLButtonUp(nFlags, point);
}
void CExercise7aView::ComputeCircle()
{
	// TODO: 여기에 구현 코드 추가
	double x, y, r, radian;

	// 반지름 r 계산[cite: 11]
	r = sqrt((double)((m_ptStart.x - m_ptPrev.x) * (m_ptStart.x - m_ptPrev.x) +
		(m_ptStart.y - m_ptPrev.y) * (m_ptStart.y - m_ptPrev.y)));

	radian = M_PI * 2 / (double)m_nResolution; // radian(라디안) = M_PI * (360/해상도)/180[cite: 11]

	// 해상도에 따른 원의 좌표 계산[cite: 11]
	for (int i = 0; i < m_nResolution; i++)
	{
		x = m_ptStart.x + r * cos(radian * i);
		y = m_ptStart.y + r * sin(radian * i);
		m_ptCircle[i] = CPoint((int)x, (int)y);
	}
}



