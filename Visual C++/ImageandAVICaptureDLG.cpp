// ImageandAVICaptureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageandAVICapture.h"
#include "ImageandAVICaptureDlg.h"
#include ".\ImageandAVICapturedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Save some typing...
using namespace DShowLib;


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CImageandAVICaptureDlg dialog



CImageandAVICaptureDlg::CImageandAVICaptureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageandAVICaptureDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iImageCounter = 0;
}


CImageandAVICaptureDlg::~CImageandAVICaptureDlg()
{
}

void CImageandAVICaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTONIMAGESETTINGS, m_cButtonSettings);
	DDX_Control(pDX, IDC_BUTTONLIVEVIDEO, m_cButtonLive);
	DDX_Control(pDX, IDC_STATICVIDEO, m_cStaticVideoWindow);
	DDX_Control(pDX, IDC_BUTTONSNAPIMAGE, m_cButtonSnapImage);
	DDX_Control(pDX, IDC_COMBOCODECS, m_ComboCodecs);
	DDX_Control(pDX, IDC_BUTTONCODECPROPERTIES, m_cButtonCodecProperties);
	DDX_Control(pDX, IDC_EDITAVIFILENAME, m_cEditAVIName);
	DDX_Control(pDX, IDC_CHECKAVIPAUSE, m_cCheckAVIPause);
}

// CImageandAVICaptureDlg message handlers

BEGIN_MESSAGE_MAP(CImageandAVICaptureDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTONDEVICE, OnBnClickedButtondevice)
	ON_BN_CLICKED(IDC_BUTTONIMAGESETTINGS, OnBnClickedButtonimagesettings)
	ON_BN_CLICKED(IDC_BUTTONLIVEVIDEO, OnBnClickedButtonlivevideo)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTONSNAPIMAGE, OnBnClickedButtonsnapimage)
	ON_BN_CLICKED(IDC_BUTTONCODECPROPERTIES, OnBnClickedButtoncodecproperties)
	ON_CBN_SELCHANGE(IDC_COMBOCODECS, OnCbnSelchangeCombocodecs)
	ON_BN_CLICKED(IDC_CHECKAVIPAUSE, OnBnClickedCheckavipause)
END_MESSAGE_MAP()



BOOL CImageandAVICaptureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon



	// Assign this window to the Grabber object for live video display.
	m_cGrabber.setHWND(m_cStaticVideoWindow.m_hWnd);

	// Adjust the live video to the size of the window.
//<<resizelive
	CRect rect;
	m_cStaticVideoWindow.GetClientRect( &rect);
	m_cGrabber.setDefaultWindowPosition(false);
	m_cGrabber.setWindowSize(rect.Width(), rect.Height());
//>>

//<<loadfilter	
	// Try to load the "Save Image" frame filter.
	m_pSaveImageFilter = FilterLoader::createFilter("Save Image");
	// Check wether the filter could be loaded successfully.
	if( m_pSaveImageFilter == NULL)
	{
		MessageBox("Failed to load the \"Save Image\" frame filter!","Error",MB_OK|MB_ICONEXCLAMATION);
	}
	else
	{
		// The frame filter has been loaded successfully. Now it should be added
		// to the Grabber object.
		if( !m_cGrabber.setDeviceFrameFilters( m_pSaveImageFilter.get()) )
		{
			MessageBox("Failed to add the \"Save Image\" frame filter to the grabber!","Error",MB_OK|MB_ICONEXCLAMATION);
		}
	}
//>>
	FillCodecComboBox();

	// Preset the avi file name. The AVI sink has been created in FillCodecComboBox();
	m_cEditAVIName.SetWindowText("Test.avi");
	m_pAVISink->setFilename("Test.avi");


	// The sink is initially paused, so that no video data is written to the file.
	m_pAVISink->setSinkMode( GrabberSinkType::ePAUSE );
	m_cCheckAVIPause.SetCheck(1);

	// The AVI sink must be assigned to the Grabber object.
	m_cGrabber.setSinkType( m_pAVISink );

	// Try to load the previously used video capture device.
	//<<reloaddevice
	if( m_cGrabber.loadDeviceStateFromFile( "device.xml"))
	{
		// Display the device's name in the caption bar of the application.
		SetWindowText( "Image and AVI Capture " + CString(m_cGrabber.getDev().c_str()));
	}
	//>>
	SetButtonStates();

	return TRUE;  // return TRUE unless you set the focus to a control.
}


//////////////////////////////////////////////////////////////////////////
// Query the available codecs and list them in the codecs combo box.
//////////////////////////////////////////////////////////////////////////
//<<FillCodecComboBox
void CImageandAVICaptureDlg::FillCodecComboBox()
{
	m_CodecListPtr = Codec::getAvailableCodecs();
	unsigned int i = 0;
	for(  i = 0; i < m_CodecListPtr->size();i++ )
	{
		m_ComboCodecs.AddString( m_CodecListPtr->at(i)->getName().c_str());
		if( i ==  0 ) // Select the first codec. 
		{
			m_ComboCodecs.SetCurSel(i);
			m_pAVISink = MediaStreamSink::create( 	MediaStreamContainer::create( MSC_AviContainer ), m_CodecListPtr->at(i));

			// If the currently selected codec has a dialog, the codec properties button will be enabled.
			if(m_CodecListPtr->at(i)->hasDialog()) 
				m_cButtonCodecProperties.EnableWindow(true);
			else
				m_cButtonCodecProperties.EnableWindow(true);
		}
	}

	// Add the uncompressed formats.
	m_ComboCodecs.AddString("Y800");
	m_ComboCodecs.AddString("RGB24");
	m_ComboCodecs.AddString("RGB32");
}
//>>

void CImageandAVICaptureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}
//////////////////////////////////////////////////////////////////////////
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon. For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//////////////////////////////////////////////////////////////////////////

void CImageandAVICaptureDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}
//////////////////////////////////////////////////////////////////////////
// The system calls this function to obtain the cursor to display while
// the user dragsthe minimized window.
//////////////////////////////////////////////////////////////////////////

HCURSOR CImageandAVICaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
// Show the device select dialog, if the "Device" button has been clicked.
// If live video is displayed, it has to be stopped.
//////////////////////////////////////////////////////////////////////////
//<<devicebutton
void CImageandAVICaptureDlg::OnBnClickedButtondevice()
{
	// If live video is running, stop it.
	if(m_cGrabber.isDevValid() && m_cGrabber.isLive())
	{
		m_cGrabber.stopLive();
	}

	m_cGrabber.showDevicePage(this->m_hWnd);

	// If we have selected a valid device, save it to the file "device.xml", so
	// the application can load it automatically when it is started the next time.
	if( m_cGrabber.isDevValid())
	{
		m_cGrabber.saveDeviceStateToFile("device.xml");
	}

	// Now display the device's name in the caption bar of the application.
	SetWindowText( "Image and AVI Capture " + CString(m_cGrabber.getDev().c_str()));

	SetButtonStates();
}
//>>

//////////////////////////////////////////////////////////////////////////
// Show the image settings dialog of IC Imaging Control. 
//////////////////////////////////////////////////////////////////////////
//<<deviceproperties
void CImageandAVICaptureDlg::OnBnClickedButtonimagesettings()
{
	if( m_cGrabber.isDevValid())
	{
		m_cGrabber.showVCDPropertyPage(this->m_hWnd);
		m_cGrabber.saveDeviceStateToFile("device.xml");
	}
}
//>>

//////////////////////////////////////////////////////////////////////////
// This method sets the states of the dialog's buttons.
//////////////////////////////////////////////////////////////////////////

void CImageandAVICaptureDlg::SetButtonStates(void)
{
	bool bDevValid =  m_cGrabber.isDevValid();
	bool bIsLive   = m_cGrabber.isLive();

	m_cButtonSettings.EnableWindow(bDevValid);
	m_cButtonLive.EnableWindow(bDevValid);
	
	if( !bDevValid )
	{
		m_cButtonLive.SetWindowText("Live Start");
		m_cButtonSnapImage.EnableWindow(false);
	}


	if( bIsLive )
	{
		m_cButtonLive.SetWindowText("Live Stop");
		m_cButtonSnapImage.EnableWindow(true);
	}
	else
	{
		m_cButtonLive.SetWindowText("Live Start");
		m_cButtonSnapImage.EnableWindow(false);
	}


}

//////////////////////////////////////////////////////////////////////////
// This method starts and stops the live video.
//////////////////////////////////////////////////////////////////////////
//<<startstop
void CImageandAVICaptureDlg::OnBnClickedButtonlivevideo()
{
	if( m_cGrabber.isDevValid())
	{
		if (m_cGrabber.isLive())
		{
			m_cGrabber.stopLive();
		}
		else
		{
			m_cGrabber.startLive();
		}
		SetButtonStates();
		m_cCheckAVIPause.SetCheck(1);
		m_pAVISink->setSinkMode( GrabberSinkType::ePAUSE );
	}
}
//>>
//////////////////////////////////////////////////////////////////////////

void CImageandAVICaptureDlg::OnClose()
{
	m_cGrabber.stopLive();

	CDialog::OnClose();
}

//////////////////////////////////////////////////////////////////////////
// Snap and save an image with the "Save Image" frame filter.
//////////////////////////////////////////////////////////////////////////
//<<snapimage
void CImageandAVICaptureDlg::OnBnClickedButtonsnapimage()
{
	if( m_pSaveImageFilter != NULL && m_cGrabber.isDevValid() && m_cGrabber.isLive())
	{
		char szImageFileName[MAX_PATH+1];
		m_iImageCounter++;
		sprintf(szImageFileName,"Image%03d.jpg",m_iImageCounter);

		m_pSaveImageFilter->beginParamTransfer();
		// Setting the parameter "ImageName" of the filter causes the filter to
		// snap the next incoming image and save it to a file.
		m_pSaveImageFilter->setParameter("ImageName",std::string(szImageFileName));
		m_pSaveImageFilter->endParamTransfer();
	}
}
//>>
//////////////////////////////////////////////////////////////////////////
// Show the property dialog of the currently selected codec.
//////////////////////////////////////////////////////////////////////////
void CImageandAVICaptureDlg::OnBnClickedButtoncodecproperties()
{
	if(m_pAVISink->getCodec()->hasDialog())
	{
		m_pAVISink->getCodec()->callDialog();
	}
}

//////////////////////////////////////////////////////////////////////////
// React on the selection change in the codec combo box.
//////////////////////////////////////////////////////////////////////////
//<<selectcodec
void CImageandAVICaptureDlg::OnCbnSelchangeCombocodecs()
{
	int iIndex = m_ComboCodecs.GetCurSel();
	bool bRestartLive = false;
	if( iIndex > -1 )
	{
		CString szCodec;
		m_ComboCodecs.GetLBText(iIndex,szCodec);

		if( m_cGrabber.isLive())
		{
			m_cGrabber.stopLive();
			bRestartLive = true;
		}

		m_pAVISink = NULL;
		GetDlgItem(IDC_BUTTONCODECPROPERTIES)->EnableWindow(false);
		if( szCodec == "Y800")
			m_pAVISink = MediaStreamSink::create( 	MediaStreamContainer::create( MSC_AviContainer ), MEDIASUBTYPE_Y800 );
		else
			if( szCodec == "RGB24")
				m_pAVISink = MediaStreamSink::create( 	MediaStreamContainer::create( MSC_AviContainer ), MEDIASUBTYPE_RGB24 );
			else
				if( szCodec == "RGB32")
					m_pAVISink = MediaStreamSink::create( 	MediaStreamContainer::create( MSC_AviContainer ), MEDIASUBTYPE_RGB32 );
				else
				{
					m_pAVISink = MediaStreamSink::create( 	MediaStreamContainer::create( MSC_AviContainer ), m_CodecListPtr->at(iIndex));
					if(m_pAVISink->getCodec()->hasDialog())
					{
						GetDlgItem(IDC_BUTTONCODECPROPERTIES)->EnableWindow(true);
					}
				}

		CString FileName;
		m_cEditAVIName.GetWindowText(FileName);
		m_pAVISink->setFilename((LPCSTR)FileName);

		m_pAVISink->setSinkMode( GrabberSinkType::ePAUSE );
		m_cCheckAVIPause.SetCheck(1);

		m_cGrabber.setSinkType( m_pAVISink );

		if( bRestartLive)
		{
			m_cGrabber.startLive();
		}
	}
}
//>>
//////////////////////////////////////////////////////////////////////////
// Enable or disable the capture pause in the AVI sing
//////////////////////////////////////////////////////////////////////////
void CImageandAVICaptureDlg::OnBnClickedCheckavipause()
{
	if( m_cCheckAVIPause.GetCheck() == 1)
		m_pAVISink->setSinkMode( GrabberSinkType::ePAUSE );
	else
		m_pAVISink->setSinkMode( GrabberSinkType::eRUN );


}
