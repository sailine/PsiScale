#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "..\Utilities\EasySizeDialog.h"
#include <memory>

class CPsiScale;
class CAnswerManager;
class CUser;

	// CPsiAnswerViewerDlg dialog
	class CPsiAnswerViewerDlg : public CEasySizeDialog
{
	// Construction
public:
	CPsiAnswerViewerDlg(CWnd* pParent = NULL);	// standard constructor

												// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PSIANSWERVIEWER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


														// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	DECLARE_EASYSIZE;

	bool InitialScaleList();
	bool InitialPersonCombo();
	void UpdateAnswerScale();
	bool InsertAnswer(CAnswerManager& answer_manager);
	bool InsertInfo(CUser& user);

	CListCtrl _answer_table;
	CComboBox _combo_scale;
	CString _working_folder;
	std::shared_ptr<CPsiScale> _scale;
	
	CComboBox _combo_person;
	unsigned int _row;
public:
	afx_msg void OnCbnSelchangeComboScale();
	
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonRemove();
	};
