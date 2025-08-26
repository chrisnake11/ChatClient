#include "UserManager.h"

UserManager::UserManager() : _token(""), _uid(0)
{
}

UserManager::~UserManager()
{}

void UserManager::setUid(int uid)
{
	_uid = uid;
}

void UserManager::setToken(QString token)
{
	_token = token;
}

int UserManager::getUid(){
	return _uid;
}
QString UserManager::getToken() {
	return _token;
}
void UserManager::setUserInfo(std::shared_ptr<UserInfo> user_info) {
    _uid_name_map[user_info->uid] = std::move(user_info);
}
std::shared_ptr<UserInfo> UserManager::getUserInfo(int uid) {
	return _uid_name_map[uid];
}

QString UserManager::getUsername()
{
	return _uid_name_map[_uid]->username;
}

QString UserManager::getUsername(const int& uid)
{
	return _uid_name_map[uid]->username;
}

