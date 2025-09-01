#include "user.h"
User::User() : id(0) {}

User::User(int id, const QString& username, const QString& password, const QString& displayName, const QString& phone, const QString& role)
    : id(id), username(username), password(password), displayName(displayName), phone(phone), role(role) {
}

int User::getId() const
{
    return id;
}

QString User::getUsername() const
{
    return username;
}

QString User::getPassword() const
{
    return password;
}

QString User::getDisplayName() const
{
    return displayName;
}

QString User::getPhone() const
{
    return phone;
}

QString User::getRole() const
{
    return role;
}

void User::setUsername(const QString& username)
{
    this->username = username;
}

void User::setPassword(const QString& password)
{
    this->password = password;
}

void User::setDisplayName(const QString& displayName)
{
    this->displayName = displayName;
}

void User::setPhone(const QString& phone)
{
    this->phone = phone;
}

void User::setRole(const QString& role)
{
    this->role = role;
}

// --- 新增函数实现（核心逻辑）---
User User::getUserByLogin(const QString& username, const QString& password) {
    // 【示例】模拟数据库查询：这里直接返回固定用户（实际需用 QSqlQuery 查数据库）
    if (username == "admin" && password == "admin123") {
        return User(1, "admin", "admin123", "管理员", "123456", roleToString(ROLE_ADMIN));
    }
    else if (username == "user01" && password == "user001") {
        return User(2, "user01", "user001", "普通用户", "654321", roleToString(ROLE_USER));
    }
    // 未找到用户，返回空对象（可在 isValid 里判断 id==0 等标记无效）
    return User();
}

// 3. 角色转换实现
User::Role User::roleFromString(const QString& roleStr) {
    if (roleStr == "user")      return ROLE_USER;
    if (roleStr == "admin")     return ROLE_ADMIN;
    if (roleStr == "editor")    return ROLE_EDITOR;
    return ROLE_UNKNOWN;
}

QString User::roleToString(Role role) {
    switch (role) {
    case ROLE_USER:   return "user";
    case ROLE_ADMIN:  return "admin";
    case ROLE_EDITOR: return "editor";
    default:          return "unknown";
    }
}

// 4. 有效性校验实现（可扩展复杂逻辑）
bool User::isValid() const {
    // 示例：ID>0 + 用户名非空 + 密码非空
    return id > 0
        && !username.isEmpty()
        && !password.isEmpty();
}