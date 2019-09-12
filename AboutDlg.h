// AboutDlg.h

// lasy
// 2011.12.01

class CAboutDlg: public CDialog
{
public:
	CAboutDlg();
	virtual ~CAboutDlg();

	enum {IDD = IDD_ABOUTBOX};

protected:
	DECLARE_MESSAGE_MAP()
};
