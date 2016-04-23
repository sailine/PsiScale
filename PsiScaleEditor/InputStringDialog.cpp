// InputStringDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PsiScaleEditor.h"
#include "InputStringDialog.h"
#include "afxdialogex.h"


// CInputStringDialog dialog

IMPLEMENT_DYNAMIC(CInputStringDialog, CDialogEx)

CInputStringDialog::CInputStringDialog(const TCHAR* dialog_title, 
	const TCHAR* field_title, 
	CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INPUT_STRING, pParent)
	, _text(_T(""))
	, _field_title(field_title)
{
}

CInputStringDialog::~CInputStringDialog()
{
}

const CString& CInputStringDialog::GetText()
{
	return _text;
}

void CInputStringDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, _text);
	DDX_Text(pDX, IDC_STATIC_FIELD_TITLE, _field_title);
}


BEGIN_MESSAGE_MAP(CInputStringDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputStringDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputStringDialog message handlers


void CInputStringDialog::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}
