#include "stdafx.h"
#include "UserManager.h"
#include "User.h"
#include "..\Utilities\macros.h"

using namespace std;

CUserManager::CUserManager()
{
}


CUserManager::~CUserManager()
{
}

std::shared_ptr<CUser> CUserManager::CreateUser(const CString& name, 
	const CString& password)
{
	shared_ptr<CUser> user(new CUser(name, password));

	_users.insert(make_pair(name, user));
	_user_name_to_uid.insert(make_pair(name, user->GetUid()));

	return user;
}

std::shared_ptr<CUser> CUserManager::GetUser(const CString& name, const CString& password)
{
	NOT_IMPLEMENTED
	return shared_ptr<CUser>();
}

bool CUserManager::Load()
{
	NOT_IMPLEMENTED;
	return true;
}

bool CUserManager::Save()
{
	NOT_IMPLEMENTED;
	return true;
}

