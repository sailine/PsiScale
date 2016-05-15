#pragma once
#include <memory>
#include <map>

class CUser;

class CUserManager
{
public:
	CUserManager();
	virtual ~CUserManager();

	std::shared_ptr<CUser> CreateUser(const CString& name, const CString& password);
	std::shared_ptr<CUser> GetUser(const CString& name, const CString& password);

	bool Load();
	bool Save();

	std::map<CString, std::shared_ptr<CUser>> _users;
	std::multimap<CString, CString> _user_name_to_uid;	
};

