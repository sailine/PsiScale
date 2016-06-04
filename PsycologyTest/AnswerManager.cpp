#include "stdafx.h"
#include "AnswerManager.h"
#include "..\PsiCommon\PsiScale.h"
#include <algorithm>
#include "..\Utilities\xml.h"
#include "xml_name_space.h"

CAnswerManager::CAnswerManager()
{
}

CAnswerManager::~CAnswerManager()
{
}

bool CAnswerManager::AddAnswer(const CString& scale_name, 
	unsigned question_id, 
	unsigned answer, 
	unsigned time)
{
	_test_finished_info[scale_name] = false;
	_answers[scale_name][question_id].answer = answer;
	_answers[scale_name][question_id].time = time;
	return true;
}

unsigned CAnswerManager::GetAnswer(const CString& scale_name, unsigned question_id)
{
	auto table = _answers.find(scale_name);
	if (table == _answers.end())
	{
		throw _T("Table not found.");
	}
	auto question = table->second.find(question_id);
	if (question == table->second.end())
	{
		throw _T("Question not found.");
	}

	return question->second.answer;
}

bool CAnswerManager::IsAnswered(const CString& scale_name, unsigned question_id)
{
	auto table = _answers.find(scale_name);
	if (table == _answers.end())
	{
		return false;
	}

	return (table->second.find(question_id) != table->second.end());
}

void CAnswerManager::SetSubjectId(const TCHAR* subject_id)
{
	_subject_uid = subject_id;
}

const CString& CAnswerManager::GetSubjectId() const
{
	return _subject_uid;
}

/**
@return 如果所有的问题都已经回答，返回-1；否则返回第一个没有回答的题目的索引
*/

int CAnswerManager::CheckForUnansweredQuestion(CPsiScale& scale)
{
	auto iter = _answers.find(scale.GetName());
	if (iter == _answers.end())
		return 0;

	auto& answers = iter->second;
	if (answers.size() == scale.GetQuestionCount())
		return -1;

	for (int i = 0; i < int(scale.GetQuestionCount()); ++i)
	{
		if (answers.find(i) == answers.end())
			return i;
	}

	return -1;
}

// 暂时以加法运算进行累加
bool CAnswerManager::SetScore(const CString& scale_name, const CString& sub_scale_name, unsigned score)
{
	_scores[scale_name][sub_scale_name] += score;
	return true;
}

unsigned CAnswerManager::GetTotalScore(const CString& scale_name, const CString& sub_scale_name)
{
	unsigned sum = 0;
	auto iter = _scores.find(scale_name);
	if (iter != _scores.end())
	{
		std::for_each(iter->second.begin(), iter->second.end(), [&](std::pair<CString, unsigned> item) {
			sum = item.second; });
	}
	return sum;
}

// 每个scale绑定一个answermanager，暂时的设计
bool CAnswerManager::LoadScaleItem(Utilities::CXmlElement* scale_xml)
{
	CString scale_name = scale_xml->GetAttrib(TestInfo::XML_NAME);
	auto answers_element = scale_xml->GetElement(TestInfo::XML_ANSWERS);
	auto answer_items = answers_element->GetChildElements();
	std::map<unsigned int, Answer> answer_item;
	for_each(answer_items.begin(), answer_items.end(), [&](Utilities::CXmlElement* item) {
		unsigned id = item->GetIntegerAttrib(TestInfo::XML_ID);
		unsigned answer_name = item->GetIntegerAttrib(TestInfo::XML_ANSWER);
		unsigned time = item->GetIntegerAttrib(TestInfo::XML_TIME);
		Answer answer;
		answer.answer = answer_name;
		answer.time = time;
		answer_item.insert(std::make_pair(id, answer));
	});
	_answers[scale_name] = answer_item;
	auto subscales_element = scale_xml->GetElement(TestInfo::XML_SUBSCALES);
	auto subscales_items = subscales_element->GetChildElements();
	std::map<CString, unsigned int> scores;
	for_each(subscales_items.begin(), subscales_items.end(), [&](Utilities::CXmlElement* item) {
		scores.insert(std::make_pair(item->GetAttrib(TestInfo::XML_NAME), item->GetIntegerAttrib(TestInfo::XML_SCORE))); });
	_scores[scale_name] = scores;
	return true;
}

bool CAnswerManager::SaveScaleItem(Utilities::CXmlElement* scale_xml, const CString& scale_name)
{
	auto scale_iter = _answers.find(scale_name);

	if (scale_iter != _answers.end())
	{
		auto answers_xml = scale_xml->AddElement(TestInfo::XML_ANSWERS);
		int i = 0; 
		for (auto iter = scale_iter->second.begin(); iter != scale_iter->second.end(); ++iter, ++i)
		{
			auto item = answers_xml->AddElement(TestInfo::XML_ITEM);
			item->SetIntegerAttrib(TestInfo::XML_ID, iter->first);
			item->SetIntegerAttrib(TestInfo::XML_ANSWER, iter->second.answer);
			item->SetIntegerAttrib(TestInfo::XML_TIME, iter->second.time);
		}
	}

	auto subscale_iter = _scores.find(scale_name);
	if (subscale_iter != _scores.end())
	{
		auto subscales_xml = scale_xml->AddElement(TestInfo::XML_SUBSCALES);
		for (auto iter = subscale_iter->second.begin(); iter != subscale_iter->second.end(); ++iter)
		{
			auto item = subscales_xml->AddElement(TestInfo::XML_SUBSCALE);
			item->SetAttrib(TestInfo::XML_NAME, iter->first);
			item->SetIntegerAttrib(TestInfo::XML_SCORE, iter->second);
		}
	}

	return true;
}

bool CAnswerManager::Load(const CString& test_info_path)
{
	Utilities::CXml xml;
	if (!xml.Load(test_info_path))
	{
		return false;
	}
	_subject_uid = xml.GetAttrib(TestInfo::XML_PARTICIPANT_UID);
	auto scales = xml.GetChildElements();
	for (unsigned int i = 0; i < scales.size(); ++i)
	{
		auto scale_xml = scales[i];
		_test_finished_info.insert(std::make_pair(scale_xml->GetAttrib(TestInfo::XML_NAME), (scale_xml->GetIntegerAttrib(TestInfo::XML_FINISHED) == 0) ? false : true));
		LoadScaleItem(scale_xml);
	}

	return true;
}

bool CAnswerManager::Save(const CString& test_info_path, CUser& user)
{
	Utilities::CXml xml(TestInfo::XML_TEST);
	xml.SetAttrib(TestInfo::XML_PARTICIPANT_UID, _subject_uid);

	// 在答案中保存用户信息
	auto user_info_xml = xml.AddElement(UserInfo::XML_USER_INFO);
	user_info_xml->SetAttrib(UserInfo::XML_USERID, user.GetUserId());
	user_info_xml->SetAttrib(UserInfo::XML_PASSWORD, user.GetPassword());
	user_info_xml->SetAttrib(UserInfo::XML_UID, user.GetUid());
	user_info_xml->SetAttrib(UserInfo::XML_NAME, user.GetInfo().name);
	user_info_xml->SetAttrib(UserInfo::XML_PINYIN, user.GetInfo().name_pinyin);
	user_info_xml->SetAttrib(UserInfo::XML_NATIONALITY, user.GetInfo().nationality);
	user_info_xml->SetOleDateTimeAttrib(UserInfo::XML_BIRTHDATE, user.GetInfo().birth_date);
	user_info_xml->SetIntegerAttrib(UserInfo::XML_SEX, user.GetInfo().sex);
	user_info_xml->SetIntegerAttrib(UserInfo::XML_WEIGHT, user.GetInfo().weight);
	user_info_xml->SetAttrib(UserInfo::XML_MOBILE, user.GetInfo().mobile);
	user_info_xml->SetAttrib(UserInfo::XML_EMAIL, user.GetInfo().email);

	for (auto iter = _test_finished_info.begin(); iter != _test_finished_info.end(); ++iter)
	{
		auto scale_xml = xml.AddElement(TestInfo::XML_SCALE);
		scale_xml->SetAttrib(TestInfo::XML_NAME, iter->first);
		scale_xml->SetIntegerAttrib(TestInfo::XML_FINISHED, iter->second);
		this->SaveScaleItem(scale_xml, iter->first);
	}

	return xml.Save(test_info_path);
}

bool CAnswerManager::ScaleFinished(const CString& scale_name)
{
	auto iter = _test_finished_info.find(scale_name);
	if (iter != _test_finished_info.end())
	{
		return iter->second;
	}

	return false;
}

void CAnswerManager::FinishScale(const CString& scale_name)
{
	_test_finished_info[scale_name] = true;
}