// ChildView.h

// lasy
// 2011.12.06

#pragma once

class CChildView: public CWnd
{
public:
	CChildView();
	virtual ~CChildView();

protected:
	DECLARE_MESSAGE_MAP()

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	afx_msg void OnPaint();
};
