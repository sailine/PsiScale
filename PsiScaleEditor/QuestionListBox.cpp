// QuestionListBox.cpp : implementation file
//

#include "stdafx.h"
#include "PsiScaleEditor.h"
#include "QuestionListBox.h"
#include <stdexcept>


// CQuestionListBox

IMPLEMENT_DYNAMIC(CQuestionListBox, CVSListBox)

CQuestionListBox::CQuestionListBox()
{

}

CQuestionListBox::~CQuestionListBox()
{
}


void CQuestionListBox::OnEndEditLabel(LPCTSTR lpszLabel)
{
	throw std::logic_error("The method or operation is not implemented.");
}

BOOL CQuestionListBox::OnBeforeRemoveItem(int)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CQuestionListBox::OnAfterAddItem(int)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CQuestionListBox::OnAfterMoveItemUp(int)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CQuestionListBox::OnAfterMoveItemDown(int)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CQuestionListBox::CreateNewItem()
{
	throw std::logic_error("The method or operation is not implemented.");
}

BEGIN_MESSAGE_MAP(CQuestionListBox, CVSListBox)
END_MESSAGE_MAP()



// CQuestionListBox message handlers


