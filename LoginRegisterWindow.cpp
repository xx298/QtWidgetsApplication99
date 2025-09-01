#include "LoginRegisterWindow.h"
// 包含子窗口头文件（需单独创建这三个对话框）
#include "UserLoginDialog.h"
#include "UserRegisterDialog.h"
#include "AdminLoginDialog.h"
#include "QtWidgetsApplication99.h"
#include "AdminMainWindow.h" // 新增头文件

// 构造函数：初始化窗口与UI
LoginRegisterWindow::LoginRegisterWindow(QWidget* parent)
	: QMainWindow(parent)
{
	// 1. 初始化窗口基础属性
	this->setWindowTitle("高铁订票系统 - 登录入口");  // 窗口标题
	this->setFixedSize(500, 400);                   // 固定窗口大小（避免缩放混乱）
	this->setWindowIcon(QIcon(":/icon/train.ico")); // 可选：设置窗口图标（需添加资源文件）

	// 2. 创建中央部件与主布局（QMainWindow必须通过centralWidget承载布局）
	centralWidget = new QWidget(this);
	this->setCentralWidget(centralWidget);
	mainLayout = new QVBoxLayout(centralWidget);
	mainLayout->setSpacing(30);          // 控件间距30px
	mainLayout->setContentsMargins(80, 60, 80, 60); // 布局边距（上下左右）

	// 3. 创建并初始化标题标签（按UI设计：字体24号加粗，居中）
	lblTitle = new QLabel("高铁订票系统", this);
	QFont titleFont = lblTitle->font();
	titleFont.setPointSize(24);          // 字体大小24
	titleFont.setBold(true);             // 加粗
	lblTitle->setFont(titleFont);
	lblTitle->setAlignment(Qt::AlignCenter); // 文本居中
	mainLayout->addWidget(lblTitle);      // 将标签添加到主布局

	// 4. 创建普通用户登录按钮（属性：180x40px，12号字体）
	btnUserLogin = new QPushButton("普通用户登录", this);
	QFont btnFont = btnUserLogin->font();
	btnFont.setPointSize(12);            // 字体大小12
	btnUserLogin->setFont(btnFont);
	btnUserLogin->setFixedSize(180, 40); // 固定按钮大小
	mainLayout->addWidget(btnUserLogin, 0, Qt::AlignCenter); // 按钮居中

	// 5. 创建普通用户注册按钮（属性与登录按钮一致）
	btnUserRegister = new QPushButton("普通用户注册", this);
	btnUserRegister->setFont(btnFont);
	btnUserRegister->setFixedSize(180, 40);
	mainLayout->addWidget(btnUserRegister, 0, Qt::AlignCenter);

	// 6. 创建管理员登录按钮（属性：180x40px，12号字体，浅灰色背景）
	btnAdminLogin = new QPushButton("管理员登录", this);
	btnAdminLogin->setFont(btnFont);
	btnAdminLogin->setFixedSize(180, 40);
	btnAdminLogin->setStyleSheet("background-color: #f0f0f0;"); // 浅灰色背景
	mainLayout->addWidget(btnAdminLogin, 0, Qt::AlignCenter);

	// 7. 初始化子窗口指针（避免空指针异常）
	userLoginDlg = new UserLoginDialog(this);
	userRegisterDlg = new UserRegisterDialog(this);
	adminLoginDlg = new AdminLoginDialog(this);

	// 8. 绑定按钮信号与槽函数（核心：点击按钮触发对应逻辑）
	connect(btnUserLogin, &QPushButton::clicked, this, &LoginRegisterWindow::on_btnUserLogin_clicked);
	connect(btnUserRegister, &QPushButton::clicked, this, &LoginRegisterWindow::on_btnUserRegister_clicked);
	connect(btnAdminLogin, &QPushButton::clicked, this, &LoginRegisterWindow::on_btnAdminLogin_clicked);
}

// 析构函数：释放控件内存（避免内存泄漏）
LoginRegisterWindow::~LoginRegisterWindow()
{
	// 手动释放动态创建的UI控件（Qt父子对象机制可自动释放，但显式释放更安全）
	delete lblTitle;
	delete btnUserLogin;
	delete btnUserRegister;
	delete btnAdminLogin;
	delete mainLayout;
	delete centralWidget;
	// 释放子窗口
	delete userLoginDlg;
	delete userRegisterDlg;
	delete adminLoginDlg;
}

// 用户登录成功后跳转
void LoginRegisterWindow::on_btnUserLogin_clicked()
{
	userLoginDlg->setModal(true);
	if (userLoginDlg->exec() == QDialog::Accepted) {
		this->close(); // 关闭登录注册窗口
		QtWidgetsApplication99* userWin = new QtWidgetsApplication99();
		userWin->show();
	}
}

// 管理员登录成功后跳转
void LoginRegisterWindow::on_btnAdminLogin_clicked()
{
	adminLoginDlg->setModal(true);
	if (adminLoginDlg->exec() == QDialog::Accepted) {
		this->close(); // 关闭登录注册窗口
		AdminMainWindow* adminWin = new AdminMainWindow();
		adminWin->show();
	}
}

// 用户注册成功后跳转（可根据需求调整：注册后直接进主界面或登录）
void LoginRegisterWindow::on_btnUserRegister_clicked()
{
	userRegisterDlg->setModal(true);
	if (userRegisterDlg->exec() == QDialog::Accepted) {
		this->close(); // 关闭登录注册窗口
		QtWidgetsApplication99* userWin = new QtWidgetsApplication99();
		userWin->show();
	}
}