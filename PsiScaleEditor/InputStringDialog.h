#pragma once
#include "afxwin.h"


// CInputStringDialog dialog

class CInputStringDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CInputStringDialog)

public:
	CInputStringDialog(const TCHAR* dialog_title, const TCHAR* field_title, CWnd* pParent = NULL);   // standard constructor
	virtual ~CInputStringDialog();

	const CString& GetText();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_STRING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString _text;
	afx_msg void OnBnClickedOk();
	CString _field_title;
};
