#pragma once

#include <vector>
#include <map>


struct PsiScaleGroup
{
	CString id;
	CString description;
};

struct PsiScaleQuestion
{
	CString id;
	CString text;
	unsigned short level_count;
	bool reverse_score;
	unsigned short group_id;
};

struct PsiScalePrologue
{
	CString text;
};

struct PsiScale
{
	CString id;
	CString name;
	CString description;

	PsiScalePrologue prologue;
	
	std::vector<PsiScaleGroup> groups;
	std::vector<PsiScaleQuestion> questions;
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
	const PsiScale & GetPsiScale(const CString& id) const;
protected:
	std::map<CString, PsiScale> _scales;
};

