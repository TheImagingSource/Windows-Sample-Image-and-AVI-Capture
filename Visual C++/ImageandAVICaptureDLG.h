// ImageandAVICaptureDlg.h : header file
//

#pragma once
#include "afxwin.h"

// CImageandAVICaptureDlg dialog
class CImageandAVICaptureDlg : public CDialog
{
	// Construction
	public:
		CImageandAVICaptureDlg(CWnd* pParent = NULL);	// standard constructor
		~CImageandAVICaptureDlg();

	// Dialog Data
		enum { IDD = IDD_ImageandAVICapture_DIALOG };

		protected:
		virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

		afx_msg void OnBnClickedButtondevice();
		afx_msg void OnBnClickedButtonimagesettings();
		void SetButtonStates(void);
		afx_msg void OnBnClickedButtonlivevideo();


	// Implementation
	protected:
		HICON m_hIcon;

		// Generated message map functions
		virtual BOOL OnInitDialog();
		afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
		afx_msg void OnPaint();
		afx_msg HCURSOR OnQueryDragIcon();
		afx_msg void OnClose();
		afx_msg void OnBnClickedButtonsnapimage();
		DECLARE_MESSAGE_MAP()


	private:
		CButton m_cButtonSettings;
		CButton m_cButtonLive;
		CStatic m_cStaticVideoWindow;
		CButton m_cButtonSnapImage;
		// The instance of the Grabber class.
//<<m_cGrabber
		DShowLib::Grabber		m_cGrabber; 
//>>
		// This will hold the instance of the SaveImage frame filter.
//<<m_pSaveImageFilter
		smart_com<DShowLib::IFrameFilter> m_pSaveImageFilter; 
//>>
		// This counter will be use to create the image file name.
		int		m_iImageCounter;			

		// List is the list of available codecs.
//<<m_CodecListPtr
		DShowLib::tCodecListPtr m_CodecListPtr; 
//>>
		// This combo box will show the list of available codecs.
		CComboBox m_ComboCodecs;			

		// Clicking this button will show a codec's property dialog.
		CButton m_cButtonCodecProperties;	
		
		// The sink for AVI capture.
//<<AVISink
		DShowLib::tMediaStreamSinkPtr m_pAVISink;
//>>
		// This edit box contains the name of the AVI file.
		CEdit m_cEditAVIName;

		// This checkbox enables or disables the AVI Capture pause.
		CButton m_cCheckAVIPause;

		void FillCodecComboBox();
		afx_msg void OnBnClickedButtoncodecproperties();
		afx_msg void OnCbnSelchangeCombocodecs();
		afx_msg void OnBnClickedCheckavipause();
};
