#include "UserManager.h"
#include <QDebug>

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

std::shared_ptr<UserInfo> UserManager::getFriendInfo(int uid)
{
    if (_uid_friend_map.find(uid) == _uid_friend_map.end()) {
        return nullptr;
    }
    return _uid_friend_map[uid];
}

void UserManager::updateFriendInfoByContactList(std::shared_ptr<std::vector<ContactItemInfo>> contact_list)
{
    qDebug() << "updateFriendInfoMapByContactList";
    // 列表为空，则返回
	if (contact_list == nullptr || (*contact_list).empty()) {
		return;
	}
    // 遍历列表
    for (auto& item : (*contact_list)) {
        // 如果该用户不存在，则添加
        if (_uid_friend_map.find(item.uid) == _uid_friend_map.end()) {
            std::shared_ptr<UserInfo> user_info = std::make_shared<UserInfo>();
            user_info->uid = item.uid;
            user_info->username = item.username;
            user_info->nickname = item.nickname;
            user_info->avatar = item.avatar;
            user_info->sign = item.sign;
            user_info->onlineStatus = item.onlineStatus;
            _uid_friend_map[item.uid] = std::move(user_info);
        }
        // 更新用户信息
        else {
            if (!item.nickname.isEmpty()) {
                _uid_friend_map[item.uid]->nickname = item.nickname;
            }
            if (!item.avatar.isEmpty()) {
                _uid_friend_map[item.uid]->avatar = item.avatar;
            }
            if (!item.sign.isEmpty()) {
                _uid_friend_map[item.uid]->sign = item.sign;
            }
            _uid_friend_map[item.uid]->onlineStatus = item.onlineStatus;
        }
    }
}

QString UserManager::getUsername()
{
	return _uid_name_map[_uid]->username;
}

QString UserManager::getUsername(const int& uid)
{
	return _uid_name_map[uid]->username;
}

