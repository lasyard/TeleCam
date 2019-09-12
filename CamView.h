// CamView.h

// lasy
// 2011.11.25

#pragma once

class CCamView: public CDockablePane
{
public:
	CCamView();
	virtual ~CCamView();

	void showCamList();
	CCam *getCamFromItem(HTREEITEM h);
	CCam *getCamFromSelected();
	HTREEITEM getItemByCamId(int camId);
	void selectItem(HTREEITEM hItem);
	void setSelectedItemImage(int index);

	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

protected:
	DECLARE_MESSAGE_MAP()

	CTreeCtrl m_wndCamView;
	CImageList m_CamViewImages;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNotifySelChanged(NMHDR *pNotifyStruct, LRESULT *result);
};
