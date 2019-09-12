// CamManager.h

// lasy
// 2011.11.25

#pragma once

class CCamManager
{
public:
	CCamManager(void);
	virtual ~CCamManager(void);

	const list<CCam *> &getCamList();
	CCam *findCamById(int camId);
	CCam *findCamByPath(LPCTSTR path);
	void notifyDevChanged();

protected:
	list<CCam *> m_camList;
	int m_camId;
	bool m_devChanged;

	ICreateDevEnum *m_pCreateDevEnum;

	void clearCamList();
	void initEnumDevices();
	void releaseEnumDevices();
	void enumCams();
};
