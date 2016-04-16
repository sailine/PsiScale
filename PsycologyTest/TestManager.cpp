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

	PsiScale scale;
	scale.id = xml.GetAttrib(XML_ID);
	scale.name = xml.GetAttrib(XML_NAME);
	scale.description = xml.GetAttrib(XML_DESCRIPTION);

	auto prologue_element = xml.GetElement(XML_PROLOGUE);
	if (prologue_element == nullptr)
		return false;

	scale.prologue.text = prologue_element->GetAttrib(XML_TEXT);

	auto groups_element = xml.GetElement(XML_GROUPS);
	if (groups_element == nullptr)
		return false;

	auto& group_items = groups_element->GetChildElements();
	for (auto item : group_items)
	{
		PsiScaleGroup group;
		group.id = item->GetAttrib(XML_ID);
		group.description = item->GetAttrib(XML_DESCRIPTION);
		scale.groups.push_back(group);
	}

	auto questions_element = xml.GetElement(XML_QUESTIONS);
	if (questions_element == nullptr)
		return false;

	auto& question_items = questions_element->GetChildElements();
	for (auto item : question_items)
	{
		PsiScaleQuestion question;
		question.id = item->GetAttrib(XML_ID);
		question.text = item->GetAttrib(XML_TEXT);
		question.level_count = item->GetIntegerAttrib(XML_LEVEL_COUNT);
		question.reverse_score = item->GetBoolAttrib(XML_REVERSE_SCORE);
		question.group_id = item->GetIntegerAttrib(XML_GROUP_ID);

		scale.questions.push_back(question);
	}

	_scales.insert(make_pair(scale.id, scale));

	return true;
}

const PsiScale & CTestManager::GetPsiScale(const CString& id) const
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
