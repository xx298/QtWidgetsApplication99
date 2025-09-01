#include "QtWidgetsApplication99.h"
// 7. 按需包含其他头文件（如提示框、日期处理）
#include <QMessageBox>
#include <QDate>
#include <QPushButton>

// 8. 无参构造函数实现（直接运行时用）
QtWidgetsApplication99::QtWidgetsApplication99(QWidget* parent)
    : QMainWindow(parent)
    // , currentUser(User())  // 如果需要初始化用户，取消注释
{
    ui.setupUi(this); // 加载 UI 设计
    initUI();         // 初始化界面逻辑
}

// 9. 带用户信息的构造函数实现（登录后传用户信息用）
QtWidgetsApplication99::QtWidgetsApplication99(User user, QWidget* parent)
    : QMainWindow(parent)
    , currentUser(user)
{
    ui.setupUi(this); // 加载 UI 设计
    initUI();         // 初始化界面逻辑
}

// 10. 核心：初始化 UI 逻辑（验证控件、绑定事件）
void QtWidgetsApplication99::initUI() {
    // === 验证控件是否存在 ===
    // 检查工具栏（adminToolBar）
    if (ui.adminToolBar) {
        qDebug() << "找到 adminToolBar";
    }
    else {
        qDebug() << "警告：未找到 adminToolBar！";
    }

    // 检查查询按钮（pushButton）
    if (ui.pushButton) {
        qDebug() << "找到 pushButton";
    }
    else {
        qDebug() << "警告：未找到 pushButton！";
    }

    // === 绑定事件：查询按钮点击 ===
    connect(ui.pushButton, &QPushButton::clicked, this, [=]() {
        QString from = ui.fromStationEdit->text().trimmed();
        QString to = ui.toStationEdit->text().trimmed();
        QDate date = ui.dateEdit->date();

        // 简单校验
        if (from.isEmpty() || to.isEmpty()) {
            QMessageBox::warning(this, "错误", "出发站/到达站不能为空！");
            return;
        }

        // 模拟查询成功
        QMessageBox::information(this, "查询结果",
            QString("查询 %1 → %2（%3）的车票成功！")
            .arg(from).arg(to).arg(date.toString("yyyy-MM-dd")));
        });

    // === 绑定事件：工具栏“车站管理”（假设 Action 名是 actionStationManage）===
    if (ui.actionStationManage) {
        connect(ui.actionStationManage, &QAction::triggered, this, [=]() {
            QMessageBox::information(this, "提示", "进入车站管理界面（功能待开发）");
            });
    }
    else {
        qDebug() << "警告：未找到 actionStationManage！";
    }

    // === 初始化用户信息显示（如果有 userInfoLabel）===
    if (ui.userInfoLabel) {
        // 假设 User 类有 getDisplayName()、getRole() 方法
        QString userInfo = QString("用户名：%1（角色：%2）")
            .arg(currentUser.getDisplayName())
            .arg(currentUser.getRole());
        ui.userInfoLabel->setText(userInfo);
    }
}
