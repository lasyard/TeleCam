// Cam.h

// lasy
// 2011.11.25

#pragma once

class CCam
{
public:
	CCam(void);
	CCam(int i, LPCTSTR n, LPCTSTR d = NULL, LPCTSTR p = NULL);
	virtual ~CCam(void);

	int id;
	CString name;
	CString desc;
	CString path;

	bool hasWindow() const;
	bool isRunning() const;
	void setWindow(HWND h);
	void setWindowFocus();
	void closeWindow();
	void startCapture();
	void ajustWindowPos(int cx, int cy);
	void stopCapture();
	void endCapture();

protected:
	bool exist;
	bool running;
	int width;
	int height;

	HWND hwnd;

	IBaseFilter *filter;
	IGraphBuilder *graphBuilder;
	ICaptureGraphBuilder2 *captureGraphBuilder2;
	IMediaControl *mediaControl;
	IVideoWindow *videoWindow;

	void initCaptureGraph();
	bool hasCaptureGraph();
	void releaseCaptureGraph();
	void getMediaInfo();

	friend class CCamManager;
};
