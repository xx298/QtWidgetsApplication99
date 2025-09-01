#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include "user.h"  // 引用《main.docx》中的User类

// 前向声明窗口类（避免循环引用）
class UserLoginDialog;
class UserRegisterDialog;
class AdminLoginDialog;

class LoginRegisterWindow : public QMainWindow
{
    Q_OBJECT  // 必须添加，支持Qt信号槽机制

public:
    LoginRegisterWindow(QWidget* parent = nullptr);
    ~LoginRegisterWindow();

private slots:
    // 按钮点击对应的槽函数（绑定信号用）
    void on_btnUserLogin_clicked();    // 普通用户登录按钮
    void on_btnUserRegister_clicked(); // 普通用户注册按钮
    void on_btnAdminLogin_clicked();   // 管理员登录按钮

private:
    // 1. 声明UI控件（按《UI设计指示》的初始窗口布局）
    QLabel* lblTitle;                  // 窗口标题“高铁订票系统”
    QPushButton* btnUserLogin;         // 普通用户登录按钮
    QPushButton* btnUserRegister;      // 普通用户注册按钮
    QPushButton* btnAdminLogin;        // 管理员登录按钮
    QWidget* centralWidget;            // 中央部件（承载布局）
    QVBoxLayout* mainLayout;           // 主布局（垂直排列控件）

    // 2. 声明子窗口指针（登录/注册对话框）
    UserLoginDialog* userLoginDlg;
    UserRegisterDialog* userRegisterDlg;
    AdminLoginDialog* adminLoginDlg;
};