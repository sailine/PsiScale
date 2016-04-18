#pragma once

#include <vector>
#include <map>


struct PsiScaleGroup
{
	CString id;
	CString description;
};

class PsiScaleQuestion
{
public:
	PsiScaleQuestion(CString id, CString text, unsigned short level_count, bool reverse_score, unsigned short group_id):
		_id(id), _text(text), _level_count(level_count), _reverse_score(reverse_score), _group_id(group_id)
	{}

	void SetId(CString id) { _id = id; }
	CString GetId() { return _id; }
	void SetText(CString text) { _text = text; }
	CString GetText() { return _text; }
	void SetLevelCount(unsigned short level_count) { _level_count = level_count; }
	unsigned short GetLevelCound() { return _level_count; }
	void SetReverseScore(bool reverse_score) {_reverse_score = reverse_score;}
	bool GetReverseScore() { return _reverse_score; }
	void SetGroupId(unsigned short group_id) { _group_id= group_id; }
	unsigned short GetGroupId() { return _group_id; }
private:
	CString _id;
	CString _text;
	unsigned short _level_count;
	bool _reverse_score;
	unsigned short _group_id;
};

class PsiScalePrologue
{
public:
	PsiScalePrologue(CString text = CString(_T(""))) : _text(text) {}

	PsiScalePrologue operator = (PsiScalePrologue prologue) { _text = prologue.GetText(); return *this; }

	void SetText(CString text) { _text = text; }
	CString GetText() {return _text; }

private:
	CString _text;
};

class PsiScale
{
public:
	PsiScale(CString id = CString(_T("1")), CString name = CString(_T("")), CString description = CString(_T(""))):
		_id(id), _name(name), _description(description)
	{}

	void SetId(CString id) { _id = id; }
	CString GetId() { return _id; }
	void SetName(CString name) { _name = name; }
	CString GetName() { return _name; }
	void SetDescription(CString description) { _description = description; }
	CString GetDescription() { return _description; }
	void SetPrologue(PsiScalePrologue prologue) { _prologue = prologue; }
	CString GetPrologue() { return _prologue.GetText(); }

	void AddGroup(PsiScaleGroup group) { _groups.push_back(group); }
	void AddQuestion(PsiScaleQuestion question) { _questions.push_back(question); }
	PsiScaleGroup GetGroup(unsigned int index) { return _groups[index]; }
	PsiScaleQuestion GetQuestion(unsigned int index) { return _questions[index]; }

	unsigned int QuestionSize() { return _questions.size(); }

private:
	CString _id;
	CString _name;
	CString _description;

	PsiScalePrologue _prologue;
	
	std::vector<PsiScaleGroup> _groups;
	std::vector<PsiScaleQuestion> _questions;
};

struct Score
{
	CString id;
	CString answer;
};

class CTestManager
{
public:
	CTestManager();
	~CTestManager();

	bool LoadPsiScale(const CString& file_path);
	PsiScale & GetPsiScale(const CString& id);
protected:
	std::map<CString, PsiScale> _scales;
};

