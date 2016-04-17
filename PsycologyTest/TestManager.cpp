#include "stdafx.h"
#include "TestManager.h"

#include "../Utilities/xml.h"

using namespace Utilities;
using namespace std;


const TCHAR * XML_ID = _T("Id");
const TCHAR * XML_NAME = _T("Name");
const TCHAR * XML_DESCRIPTION = _T("Description");
const TCHAR * XML_PROLOGUE = _T("Prologue");
const TCHAR * XML_GROUPS = _T("Groups");
const TCHAR * XML_QUESTIONS = _T("Questions");
const TCHAR * XML_TEXT = _T("Text");
const TCHAR * XML_LEVEL_COUNT = _T("LevelCount");
const TCHAR * XML_REVERSE_SCORE = _T("ReverseScore");
const TCHAR * XML_GROUP_ID = _T("GroupId");


CTestManager::CTestManager()
{
}


CTestManager::~CTestManager()
{
}

bool CTestManager::LoadPsiScale(const CString& file_path)
{
	CXml xml;
	if (!xml.Load(file_path))
		return false;

	PsiScale scale(xml.GetAttrib(XML_ID), xml.GetAttrib(XML_NAME), xml.GetAttrib(XML_DESCRIPTION));

	auto prologue_element = xml.GetElement(XML_PROLOGUE);
	if (prologue_element == nullptr)
		return false;

	PsiScalePrologue prologue(prologue_element->GetAttrib(XML_TEXT));
	scale.SetPrologue(prologue);

	auto groups_element = xml.GetElement(XML_GROUPS);
	if (groups_element == nullptr)
		return false;

	auto& group_items = groups_element->GetChildElements();
	for (auto item : group_items)
	{
		PsiScaleGroup group;
		group.id = item->GetAttrib(XML_ID);
		group.description = item->GetAttrib(XML_DESCRIPTION);
		scale.AddGroup(group);
	}

	auto questions_element = xml.GetElement(XML_QUESTIONS);
	if (questions_element == nullptr)
		return false;

	auto& question_items = questions_element->GetChildElements();
	for (auto item : question_items)
	{
		PsiScaleQuestion question(item->GetAttrib(XML_ID), item->GetAttrib(XML_TEXT), item->GetIntegerAttrib(XML_LEVEL_COUNT), 
			item->GetBoolAttrib(XML_REVERSE_SCORE), item->GetIntegerAttrib(XML_GROUP_ID));

		scale.AddQuestion(question);
	}

	_scales.insert(make_pair(scale.GetId(), scale));

	return true;
}

PsiScale & CTestManager::GetPsiScale(const CString& id)
{
	auto iter = _scales.find(id);
	if (iter != _scales.end())
	{
		return iter->second;
	}
	else
	{
		throw CString(_T("¡ø±ÌŒ¥’“µΩ°£"));
	}
}
