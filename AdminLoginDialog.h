#pragma once
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class AdminLoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdminLoginDialog(QWidget* parent = nullptr);

private slots:
    void onAdminLoginClicked();  // 管理员登录按钮槽函数

private:
    QLineEdit* editAdminUsername;  // 管理员用户名
    QLineEdit* editAdminPassword;  // 管理员密码
};