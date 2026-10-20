
// Exercise7aView.h: CExercise7aView 클래스의 인터페이스
//

#pragma once
#include <math.h>

class CExercise7aView : public CView
{
protected: // serialization에서만 만들어집니다.
	CExercise7aView() noexcept;
	DECLARE_DYNCREATE(CExercise7aView)

// 특성입니다.
public:
	CExercise7aDoc* GetDocument() const;

// 작업입니다.
public:
	void ComputeCircle(); // 추가: 원의 좌표를 계산하는 함수

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CExercise7aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRectangle();
	afx_msg void OnCircle();
	afx_msg void OnIncrease();
	afx_msg void OnDecrease();
	int m_nDrawMode;
	CPoint m_ptStart;
	CPoint m_ptPrev;
	bool m_bLButtonDown;
	CRect m_rtRect;
	CPoint m_ptCircle[1025];   // 원의 좌표
	int m_nResolution;             // 원의 해상도
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Exercise7aView.cpp의 디버그 버전
inline CExercise7aDoc* CExercise7aView::GetDocument() const
   { return reinterpret_cast<CExercise7aDoc*>(m_pDocument); }
#endif

