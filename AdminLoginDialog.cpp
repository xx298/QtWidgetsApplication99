#include "AdminLoginDialog.h"

AdminLoginDialog::AdminLoginDialog(QWidget* parent)
    : QDialog(parent)
{
    // 1. 窗口基础设置
    setWindowTitle("管理员登录");
    setFixedSize(300, 200);

    // 2. 创建控件
    QLabel* lblAdminUsername = new QLabel("管理员账号:", this);
    QLabel* lblAdminPassword = new QLabel("管理员密码:", this);
    editAdminUsername = new QLineEdit(this);
    editAdminPassword = new QLineEdit(this);
    editAdminPassword->setEchoMode(QLineEdit::Password);
    QPushButton* btnAdminLogin = new QPushButton("管理员登录", this);

    // 3. 布局（垂直排列）
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(lblAdminUsername);
    layout->addWidget(editAdminUsername);
    layout->addWidget(lblAdminPassword);
    layout->addWidget(editAdminPassword);
    layout->addWidget(btnAdminLogin);

    // 4. 信号槽绑定
    connect(btnAdminLogin, &QPushButton::clicked, this, &AdminLoginDialog::onAdminLoginClicked);
}

void AdminLoginDialog::onAdminLoginClicked()
{
    // 示例：获取管理员输入（可扩展：与数据库/配置文件校验）
    QString adminUser = editAdminUsername->text();
    QString adminPwd = editAdminPassword->text();

    // 这里可添加：实际校验逻辑（比如固定管理员账号密码）
    accept();  // 关闭对话框
}