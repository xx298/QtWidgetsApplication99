#include "UserRegisterDialog.h"

UserRegisterDialog::UserRegisterDialog(QWidget* parent)
    : QDialog(parent)
{
    // 1. 窗口基础设置
    setWindowTitle("用户注册");
    setFixedSize(300, 250);

    // 2. 创建控件
    QLabel* lblUsername = new QLabel("用户名:", this);
    QLabel* lblPassword = new QLabel("密码:", this);
    QLabel* lblConfirm = new QLabel("确认密码:", this);
    editUsername = new QLineEdit(this);
    editPassword = new QLineEdit(this);
    editPassword->setEchoMode(QLineEdit::Password);
    editConfirm = new QLineEdit(this);
    editConfirm->setEchoMode(QLineEdit::Password);
    QPushButton* btnRegister = new QPushButton("注册", this);

    // 3. 布局（垂直排列）
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(lblUsername);
    layout->addWidget(editUsername);
    layout->addWidget(lblPassword);
    layout->addWidget(editPassword);
    layout->addWidget(lblConfirm);
    layout->addWidget(editConfirm);
    layout->addWidget(btnRegister);

    // 4. 信号槽绑定
    connect(btnRegister, &QPushButton::clicked, this, &UserRegisterDialog::onRegisterClicked);
}

void UserRegisterDialog::onRegisterClicked()
{
    // 示例：获取输入内容（可扩展：调用 User 类完成注册）
    QString username = editUsername->text();
    QString password = editPassword->text();
    QString confirm = editConfirm->text();

    // 简单校验：密码一致
    if (password == confirm) {
        // 伪代码：User::registerUser(username, password);  // 调用 User 类注册逻辑
        accept();  // 关闭对话框
    }
}