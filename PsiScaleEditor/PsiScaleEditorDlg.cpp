
// PsiScaleEditorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PsiScaleEditor.h"
#include "PsiScaleEditorDlg.h"
#include "afxdialogex.h"
#include "../PsiCommon/TestManager.h"
#include "InputStringDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CPsiScaleEditorDlg 对话框



CPsiScaleEditorDlg::CPsiScaleEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PSISCALEEDITOR_DIALOG, pParent)
	, _scale_id(0)
	, _scale_name(_T(""))
	, _prologue_text(_T(""))
	, _question_text(_T(""))
	, _use_same_choices(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPsiScaleEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ID, _scale_id);
	DDX_Text(pDX, IDC_NAME, _scale_name);
	DDX_Text(pDX, IDC_EDIT_PROLOGUE, _prologue_text);
	DDX_Text(pDX, IDC_EDIT_QUESTION, _question_text);
	DDX_Check(pDX, IDC_CHECK_SAME_CHOICE, _use_same_choices);
	DDX_Control(pDX, IDC_LIST_QUESTIONS, _question_list);
	DDX_Control(pDX, IDC_LIST_CHOICES, _choice_list);
	DDX_Control(pDX, IDC_LIST_GROUP, _group_list);
}

BEGIN_MESSAGE_MAP(CPsiScaleEditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_SAME_CHOICE, &CPsiScaleEditorDlg::OnBnClickedCheckSameChoice)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CPsiScaleEditorDlg::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_ADD_QUESTION, &CPsiScaleEditorDlg::OnBnClickedButtonAddQuestion)
	ON_BN_CLICKED(IDC_BUTTON_ADD_GROUP, &CPsiScaleEditorDlg::OnBnClickedButtonAddGroup)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CHOICE, &CPsiScaleEditorDlg::OnBnClickedButtonAddChoice)
	ON_EN_CHANGE(IDC_EDIT_QUESTION, &CPsiScaleEditorDlg::OnEnChangeEditQuestion)
	ON_LBN_SELCHANGE(IDC_LIST_QUESTIONS, &CPsiScaleEditorDlg::OnLbnSelchangeListQuestions)
	ON_BN_CLICKED(ID_BUTTON_SAVE, &CPsiScaleEditorDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CPsiScaleEditorDlg 消息处理程序

BOOL CPsiScaleEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	_scale = shared_ptr<PsiScale>(new PsiScale);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPsiScaleEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPsiScaleEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPsiScaleEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPsiScaleEditorDlg::OnBnClickedCheckSameChoice()
{

	// TODO: Add your control notification handler code 
	
	_use_same_choices = !_use_same_choices;
	UpdateData(FALSE);

}


void CPsiScaleEditorDlg::OnBnClickedButtonNew()
{
	if (_scale)
	{
		CString file_path;
		_scale->Save(file_path);
	}
	_scale = shared_ptr<PsiScale>(new PsiScale);

	UpdateData(FALSE);
}


void CPsiScaleEditorDlg::OnBnClickedButtonAddQuestion()
{
	ASSERT(_scale);

	PsiScaleQuestion new_question;
	_scale->AddQuestion(new_question);
	_current_question = _scale->GetQuestionCount() - 1;
	_question_list.AddString(_T("新题目"));

	UpdateUi();
}

void CPsiScaleEditorDlg::UpdateUi()
{
	UpdateData();

	_scale->SetId(_scale_id);
	_scale->SetName(_scale_name);
	_scale->SetPrologue(_prologue_text);
	_scale->SetSameChoice(_use_same_choices);

	if (!_scale)
		return;

	_question_list.SetCurSel(_current_question);
	auto question = _scale->GetQuestion(_current_question);

	_question_text = question.GetText();
	if (_use_same_choices == FALSE)
	{
		// 更新当前问题的选择。
	}

	_group_list.SetCurSel(question.GetGroupId() - 1);

	UpdateData(FALSE);
}

void CPsiScaleEditorDlg::OnBnClickedButtonAddGroup()
{
	CInputStringDialog dlg(_T("新增分组"), _T("输入分组的名称"));
	if (dlg.DoModal() == IDOK)
	{
		PsiScaleGroup group;
		group.description = dlg.GetText();
		if (!_scale)
		{
			_scale = shared_ptr<PsiScale>(new PsiScale);
		}
		group.id = _scale->GetGroupCount();
		_scale->AddGroup(group);

		_group_list.AddString(group.description);
	}

	UpdateUi();
}


void CPsiScaleEditorDlg::OnBnClickedButtonAddChoice()
{
	UpdateData();

	CInputStringDialog dlg(_T("增加题目的选项"), _T("输入选项的内容："));

	if (dlg.DoModal() == IDOK)
	{
		if (!_scale)
		{
			_scale = shared_ptr<PsiScale>(new PsiScale);
		}

		if (_use_same_choices)
		{
			QuestionChoice choice;
			choice.id = _scale->Choices().size() + 1;
			choice.text = dlg.GetText();

			_scale->Choices().push_back(choice);
		}
		else
		{
			QuestionChoice choice;
			auto& question = _scale->Question(_current_question);
			choice.id = question.Choices().size() + 1;
			choice.text = dlg.GetText();

			question.Choices().push_back(choice);
		}
		_choice_list.AddString(dlg.GetText());
	}
}


void CPsiScaleEditorDlg::OnEnChangeEditQuestion()
{
	ASSERT(_scale);
	ASSERT(_current_question < int(_scale->GetQuestionCount()) && _current_question >= 0);
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData();

	_scale->Question(_current_question).SetText(_question_text);

	CString new_text;
	new_text.Format(_T("%d. %s"), _current_question + 1,
		(_question_text.GetLength() > 10) ? (_question_text.Left(10) + _T("...")) : _question_text);

	_question_list.InsertString(_current_question, new_text);
	_question_list.DeleteString(_current_question + 1);
}


void CPsiScaleEditorDlg::OnLbnSelchangeListQuestions()
{
	if (_question_list.GetCurSel() == LB_ERR)
		return;

	_current_question = _question_list.GetCurSel();

	UpdateUi();
}


void CPsiScaleEditorDlg::OnBnClickedButtonSave()
{
	UpdateUi();
	_test_manager.SavePsiScale(_T("..\\PsycologyTest\\TestTemplate1.xml"), *_scale);
}
