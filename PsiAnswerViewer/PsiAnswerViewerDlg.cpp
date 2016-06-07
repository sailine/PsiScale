// PsiAnswerViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PsiAnswerViewer.h"
#include "PsiAnswerViewerDlg.h"
#include "afxdialogex.h"
#include "..\Utilities\FileSystem.h"
#include <afxstr.h>
#include <vector>
#include <algorithm>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EASYSIZE_MAP(CPsiAnswerViewerDlg)
	EASYSIZE(IDC_EDIT_WORKING_FOLDER, ES_BORDER, ES_BORDER, ES_KEEPSIZE, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_COMBO_SCALE, ES_BORDER, ES_BORDER, ES_KEEPSIZE, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_ANSWER_TABLE, ES_BORDER, ES_BORDER, ES_BORDER, ES_BORDER, 0)
END_EASYSIZE_MAP

using namespace std;

bool IsShort(const CString& s1, const CString& s2)
{
	return (_ttoi(s1.Left(s1.Find(_T("."))).GetBuffer()) < _ttoi(s2.Left(s2.Find(_T("."))).GetBuffer()));
}
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

														// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPsiAnswerViewerDlg dialog



CPsiAnswerViewerDlg::CPsiAnswerViewerDlg(CWnd* pParent /*=NULL*/)
	: CEasySizeDialog(IDD_PSIANSWERVIEWER_DIALOG, L"PsiAnswerViewer", pParent, true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	_working_folder.Format(_T("../Scales"));
}

void CPsiAnswerViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ANSWER_TABLE, answer_table);
	DDX_Control(pDX, IDC_COMBO_SCALE, _combo_scale);
}

BEGIN_MESSAGE_MAP(CPsiAnswerViewerDlg, CEasySizeDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_SCALE, &CPsiAnswerViewerDlg::OnCbnSelchangeComboScale)
END_MESSAGE_MAP()


// CPsiAnswerViewerDlg message handlers

BOOL CPsiAnswerViewerDlg::OnInitDialog()
{
	__super::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

									// TODO: Add extra initialization here
	InitialScaleList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPsiAnswerViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		__super::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPsiAnswerViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
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
		__super::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPsiAnswerViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CPsiAnswerViewerDlg::InitialScaleList()
{
	std::vector<CString> files;
	FileSystem::ForEachFile(_working_folder, _T("*.scale"), false, [&](const CString& file) {
		CString filename = FileSystem::GetFileNameFromPath(file);
		files.push_back(filename);
	});

	std::sort(files.begin(), files.end(), IsShort);

	for (auto iter = files.begin(); iter != files.end(); ++iter)
	{
		_combo_scale.AddString(*iter);
	}

	return true;
}


void CPsiAnswerViewerDlg::UpdateAnswerScale()
{
	int num_columns = answer_table.GetHeaderCtrl()->GetItemCount();
	for (unsigned int i = 0; i < num_columns; ++i)
	{
		answer_table.DeleteColumn(0);
	}

	CRect mRect;
	answer_table.GetWindowRect(&mRect);     //获取控件矩形区域
	int kuan = mRect.Width();
	answer_table.InsertColumn(0, _T("编号"), LVCFMT_LEFT, 60, -1);
	answer_table.InsertColumn(1, _T("出生年月"), LVCFMT_CENTER, 120, -1);
	answer_table.InsertColumn(2, _T("性别"), LVCFMT_CENTER, 60, -1);
	answer_table.InsertColumn(3, _T("民族"), LVCFMT_CENTER, 60, -1);
	answer_table.InsertColumn(4, _T("体重"), LVCFMT_CENTER, 60, -1);
	answer_table.InsertColumn(5, _T("填表日期"), LVCFMT_CENTER, 120, -1);
	answer_table.InsertColumn(6, _T("填表时间"), LVCFMT_CENTER, 120, -1);
	DWORD dwStyle = answer_table.GetExtendedStyle(); //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES; //网格线（report风格时）
	dwStyle |= LVS_EX_CHECKBOXES; //item前生成checkbox控件
	answer_table.SetExtendedStyle(dwStyle); //设置扩展风格

	for (unsigned int i = 0; i < _scale->GetQuestionCount(); ++i)
	{
		CString str; 
		str.Format(_T("No.%d"), i + 1);
		answer_table.InsertColumn(i + 7,str, LVCFMT_LEFT, 60, -1);
	}

	for (unsigned int i = 0; i < _scale->GetGroupCount(); ++i)
	{
		CString str;
		str.Format(_T("Group.%d"), i + 1);
		answer_table.InsertColumn(i + 7 + _scale->GetQuestionCount(), str, LVCFMT_LEFT, 120, -1);
	}

	answer_table.InsertColumn(7 + _scale->GetQuestionCount() + _scale->GetGroupCount(), _T("Total"), LVCFMT_LEFT, 120, -1);
	
}

void CPsiAnswerViewerDlg::OnCbnSelchangeComboScale()
{
	int nIndex = _combo_scale.GetCurSel();
	CString scale_name;
	_combo_scale.GetLBText(nIndex, scale_name);

	CString file_path = _working_folder + _T("/") + scale_name + _T(".scale");
	
	if (!_scale)
	{
		try
		{
			_scale = shared_ptr<CPsiScale>(new CPsiScale);
		}
		catch (CMemoryException*)
		{
			return;
		}
	}

	if (!_scale->Load(file_path))
	{
		AfxMessageBox(_T("无法打开量表文件。"));
	}
	else
	{
		UpdateAnswerScale();
	}
}
