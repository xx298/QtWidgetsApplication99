#pragma once
// user.h
#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

class User
{
public:
    User();
    User(int id, const QString& username, const QString& password, const QString& displayName, const QString& phone, const QString& role);

    int getId() const;
    QString getUsername() const;
    QString getPassword() const;
    QString getDisplayName() const;
    QString getPhone() const;
    QString getRole() const;

    void setUsername(const QString& username);
    void setPassword(const QString& password);
    void setDisplayName(const QString& displayName);
    void setPhone(const QString& phone);
    void setRole(const QString& role);

    // 4. 新增：用户身份校验相关逻辑（解决编译报错的核心）
    // 4.1 枚举：定义角色常量（替代魔法字符串，让代码更易读）
    enum Role {
        ROLE_USER,    // 普通用户
        ROLE_ADMIN,   // 管理员
        ROLE_EDITOR,  // 编辑（示例扩展，可根据需求增删）
        ROLE_UNKNOWN  // 未知角色（默认/错误场景）
    };

    // 4.2 静态函数：模拟从“数据源”查询用户（实际项目需对接数据库）
    //     输入：用户名、密码；输出：匹配的 User 对象（若未找到，返回空对象/标记无效）
    static User getUserByLogin(const QString& username, const QString& password);

    // 4.3 成员函数：校验用户是否有效（如密码是否匹配、角色是否合法）
    //     返回 true = 有效用户；false = 无效（密码错、无此用户等）
    bool isValid() const;

    // 4.4 辅助函数：将字符串角色（如 "user"）转换为枚举（方便代码判断）
    static Role roleFromString(const QString& roleStr);
    //     辅助函数：将枚举角色转换为字符串（用于界面显示、日志等）
    static QString roleToString(Role role);
private:
    int id;
    QString username;
    QString password;
    QString displayName;
    QString phone;
    QString role;
};

#endif // USER_H