#pragma once
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "user.h"  // 引入 User 类头文件（根据实际路径调整）
#include <QMessageBox>
#include "UserRegisterDialog.h"
#ifndef USERLOGINDIALOG_H
#define USERLOGINDIALOG_H

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class UserLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserLoginDialog(QWidget* parent = nullptr);
    User::Role getLoggedInRole() const { return m_loggedRole; } // 获取登录角色

private slots:
    void onLoginClicked();   // 原登录逻辑
    void onRegisterClicked();// 注册按钮槽函数
    void onLogoutClicked();  // 注销按钮槽函数

private:
    User::Role m_loggedRole = User::ROLE_UNKNOWN; // 记录登录角色
    QLineEdit* editUsername = nullptr;            // 用户名输入框
    QLineEdit* editPassword = nullptr;            // 密码输入框
    QPushButton* btnRegister = nullptr;           // 注册按钮
    QPushButton* btnLogout = nullptr;             // 注销按钮
};

#endif // USERLOGINDIALOG_H