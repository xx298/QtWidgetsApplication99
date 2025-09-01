#include "UserLoginDialog.h"
#include <QMessageBox>
#include "user.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

UserLoginDialog::UserLoginDialog(QWidget* parent)
    : QDialog(parent)
{
    // 1. 窗口基础设置
    setWindowTitle("用户登录");
    setFixedSize(300, 250); // 扩大窗口容纳新按钮

    // 2. 创建控件
    QLabel* lblUsername = new QLabel("用户名:", this);
    QLabel* lblPassword = new QLabel("密码:", this);
    editUsername = new QLineEdit(this);
    editPassword = new QLineEdit(this);
    editPassword->setEchoMode(QLineEdit::Password); // 密码隐藏

    QPushButton* btnLogin = new QPushButton("登录", this);
    btnRegister = new QPushButton("注册", this); // 注册按钮
    btnLogout = new QPushButton("注销", this);   // 注销按钮

    // 3. 布局（垂直布局 + 按钮行）
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // 用户名/密码部分
    mainLayout->addWidget(lblUsername);
    mainLayout->addWidget(editUsername);
    mainLayout->addWidget(lblPassword);
    mainLayout->addWidget(editPassword);

    // 按钮行（注册 + 注销）
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(btnRegister);
    btnLayout->addWidget(btnLogout);
    mainLayout->addLayout(btnLayout);

    // 登录按钮
    mainLayout->addWidget(btnLogin);

    // 4. 信号槽绑定
    connect(btnLogin, &QPushButton::clicked, this, &UserLoginDialog::onLoginClicked);
    connect(btnRegister, &QPushButton::clicked, this, &UserLoginDialog::onRegisterClicked);
    connect(btnLogout, &QPushButton::clicked, this, &UserLoginDialog::onLogoutClicked);
}

void UserLoginDialog::onLoginClicked()
{
    QString username = editUsername->text();
    QString password = editPassword->text();

    // 调用 User 类查询用户
    User user = User::getUserByLogin(username, password);

    if (user.isValid()) {
        // 校验角色并记录
        if (User::roleFromString(user.getRole()) == User::ROLE_USER) {
            m_loggedRole = User::ROLE_USER;
        }
        else if (User::roleFromString(user.getRole()) == User::ROLE_ADMIN) {
            m_loggedRole = User::ROLE_ADMIN;
        }
        accept(); // 跳转主界面
    }
    else {
        QMessageBox::warning(this, "失败", "用户名或密码错误");
    }
}

void UserLoginDialog::onRegisterClicked()
{
    // 打开注册对话框（UserRegisterDialog 是你的注册界面）
    UserRegisterDialog registerDlg(this);
    if (registerDlg.exec() == QDialog::Accepted) {
        // 注册成功后，自动填充用户名（可选优化）
        editUsername->setText(registerDlg.getRegisterUsername());
        editPassword->clear(); // 清空密码框
    }
}

void UserLoginDialog::onLogoutClicked()
{
    // 注销逻辑：清空输入框 + 重置状态
    editUsername->clear();
    editPassword->clear();
    m_loggedRole = User::ROLE_UNKNOWN; // 重置角色
    QMessageBox::information(this, "提示", "已注销登录状态");
}