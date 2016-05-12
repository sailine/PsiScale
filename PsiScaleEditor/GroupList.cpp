// GroupList.cpp : implementation file
//

#include "stdafx.h"
#include "PsiScaleEditor.h"
#include "GroupList.h"
#include <stdexcept>


// CGroupList

IMPLEMENT_DYNAMIC(CGroupList, CVSListBox)

CGroupList::CGroupList()
{

}

CGroupList::~CGroupList()
{
}


void CGroupList::OnEndEditLabel(LPCTSTR lpszLabel)
{
}

void CGroupList::OnSelectionChanged()
{
}

BOOL CGroupList::OnBeforeRemoveItem(int)
{
	return TRUE;
}

void CGroupList::OnAfterAddItem(int)
{
}

void CGroupList::OnAfterRenameItem(int)
{
}

BEGIN_MESSAGE_MAP(CGroupList, CVSListBox)
END_MESSAGE_MAP()



// CGroupList message handlers


