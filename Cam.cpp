// Cam.cpp

// lasy
// 2011.11.25

#include "stdafx.h"

#include <dshow.h>

#include "Cam.h"

CCam::CCam(void)
: id(-1)
, filter(NULL)
, graphBuilder(NULL)
, captureGraphBuilder2(NULL)
, mediaControl(NULL)
, videoWindow(NULL)
, hwnd(NULL)
, running(false)
, width(320)
, height(240)
{
}

CCam::CCam(int i, LPCTSTR n, LPCTSTR d, LPCTSTR p)
: id(i)
, filter(NULL)
, graphBuilder(NULL)
, captureGraphBuilder2(NULL)
, mediaControl(NULL)
, videoWindow(NULL)
, hwnd(NULL)
, running(false)
, name(n)
, desc(d)
, path(p)
{
}

CCam::~CCam(void)
{
	if (filter != NULL) filter->Release();
	endCapture();
	closeWindow();
}

bool CCam::hasWindow() const
{
	return hwnd != NULL;
}

bool CCam::isRunning() const
{
	return running;
}

void CCam::setWindow(HWND h)
{
	hwnd = h;
}

void CCam::setWindowFocus()
{
	if (hwnd != NULL) ::SetFocus(hwnd);
}

void CCam::closeWindow()
{
	if (hwnd != NULL) SendMessage(hwnd, WM_CLOSE, 0, 0);
	hwnd = NULL;
}

void CCam::startCapture()
{
	if (hwnd == NULL) return;
	if (!hasCaptureGraph()) {
		releaseCaptureGraph();
		initCaptureGraph();
		graphBuilder->AddFilter(filter, _T("BaseFilter"));
		captureGraphBuilder2->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, filter, NULL, NULL);
		getMediaInfo();
	}
	videoWindow->put_Owner((OAHWND)hwnd);
	videoWindow->put_WindowStyle(WS_CHILD);
	videoWindow->put_Visible(OATRUE);
	mediaControl->Run();
	running = true;
}

void CCam::ajustWindowPos(int cx, int cy)
{
	if (hasCaptureGraph()) {
		int mx, my;
		if ((width << 10)/cx >= (height << 10)/cy) {
			mx = cx-4;
			my = height*mx/width;
		} else {
			my = cy-4;
			mx = width*my/height;
		}
		videoWindow->SetWindowPosition((cx-mx)/2, (cy-my)/2, mx, my);
	}
}

void CCam::stopCapture()
{
	if (hasCaptureGraph()) {
		mediaControl->Stop();
		videoWindow->put_Owner(NULL);
		videoWindow->put_Visible(OAFALSE);
		running = false;
	}
}

void CCam::endCapture()
{
	stopCapture();
	releaseCaptureGraph();
}

void CCam::initCaptureGraph()
{
	if (FAILED(CoCreateInstance(
		CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder,
		reinterpret_cast<void**>(&graphBuilder)
		)))
	{
		ATLTRACE2("CoCreateInstance(CLSID_FilterGraph) failed.\n");
		return;
	}
	if (FAILED(CoCreateInstance(
		CLSID_CaptureGraphBuilder2,
		NULL,
		CLSCTX_INPROC,
		IID_ICaptureGraphBuilder2,
		reinterpret_cast<void**>(&captureGraphBuilder2)
		)))
	{
		ATLTRACE2("CoCreateInstance(CLSID_CaptureGraphBuilder2) failed.\n");
		return;
	}

	captureGraphBuilder2->SetFiltergraph(graphBuilder);

	if (FAILED(graphBuilder->QueryInterface(
		IID_IMediaControl,
		reinterpret_cast<void**>(&mediaControl)
		)) ||
		FAILED(graphBuilder->QueryInterface(
		IID_IVideoWindow,
		reinterpret_cast<void**>(&videoWindow)
		)))
	{
		ATLTRACE2("QueryInterface(IID_IMediaControl IID_IVideoWindow) failed.\n");
		return;
	}
}

bool CCam::hasCaptureGraph()
{
	return captureGraphBuilder2 != NULL &&
		graphBuilder != NULL &&
		videoWindow != NULL &&
		mediaControl != NULL;
}

void CCam::releaseCaptureGraph()
{
	if (mediaControl != NULL) {
		mediaControl->Release();
		mediaControl = NULL;
	}
	if (videoWindow != NULL) {
		videoWindow->Release();
		videoWindow = NULL;
	}
	if (captureGraphBuilder2 != NULL) {
		captureGraphBuilder2->Release();
		captureGraphBuilder2 = NULL;
	}
	if (graphBuilder != NULL) {
		graphBuilder->Release();
		graphBuilder = NULL;
	}
}

void CCam::getMediaInfo()
{
	if (filter == NULL) return;
	IEnumPins *enumPins;
	filter->EnumPins(&enumPins);
	IPin *pin;
	while (enumPins->Next(1, &pin, NULL) == S_OK) {
		AM_MEDIA_TYPE mt;
		ZeroMemory(&mt, sizeof(mt));
		pin->ConnectionMediaType(&mt);
		if (mt.majortype != MEDIATYPE_Video) {
			pin->Release();
			continue;
		}
		if (mt.cbFormat >= sizeof(VIDEOINFOHEADER)) {
			VIDEOINFOHEADER *pVih = reinterpret_cast<VIDEOINFOHEADER *>(mt.pbFormat);
			width = pVih->bmiHeader.biWidth;
			height = pVih->bmiHeader.biHeight;
		}
		if (mt.cbFormat != 0) CoTaskMemFree((PVOID)mt.pbFormat);
		pin->Release();
	}
	enumPins->Release();
}
