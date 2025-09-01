#pragma once
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "user.h"  // 引入 User 类头文件（根据实际路径调整）

class UserRegisterDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UserRegisterDialog(QWidget* parent = nullptr);
    // 返回注册时填写的用户名
    QString getRegisterUsername() const {
        return editUsername->text(); // editUsername 是你注册界面的用户名输入框
    }
private slots:
    void onRegisterClicked();  // 注册按钮槽函数（可扩展：调用 User 类注册逻辑）
   
private:
    QLineEdit* editUsername;  // 用户名输入框
    QLineEdit* editPassword;  // 密码输入框
    QLineEdit* editConfirm;   // 确认密码输入框
};