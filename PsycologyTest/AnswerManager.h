#pragma once
#include <map>

class CAnswerManager
{
public:
	CAnswerManager();
	~CAnswerManager();
	bool AddAnswer(unsigned table_id, unsigned question_id, unsigned answer);
	unsigned GetAnswer(unsigned table_id, unsigned question_id);

	void SetSubjectId(const TCHAR* subject_id);
	const CString& GetSubjectId() const;

private:
	std::map<unsigned, std::map<unsigned, unsigned>> _answers;
	CString _subject_id;
};

