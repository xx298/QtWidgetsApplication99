#ifndef QTWIDGETSAPPLICATION99_H
#define QTWIDGETSAPPLICATION99_H
// 1. 包含必要的 Qt 头文件
#include <QMainWindow>  // 主窗口基类（如果 UI 是 MainWindow 模板）
// #include <QWidget>   // 如果 UI 是 Widget 模板，用这个替换上面的 QMainWindow
// 2. 引入 UI 生成的头文件（Qt 自动生成，命名规则：ui_ + 你的 UI 文件名）
#include "ui_QtWidgetsApplication99.h"
// 3. （可选）引入用户类（如果有）
#include "user.h"  // 假设你有 User 类管理用户信息，没有则删除


class QtWidgetsApplication99 : public QMainWindow { // 如果是 Widget 模板，继承 QWidget
    Q_OBJECT

public:
    // 构造函数：支持传用户信息（如果需要）
    explicit QtWidgetsApplication99(User user, QWidget* parent = nullptr);
    // 无参构造函数（方便直接运行测试）
    explicit QtWidgetsApplication99(QWidget* parent = nullptr);

private:
    // 4. 关联 UI 设计
    Ui::QtWidgetsApplication99Class ui;
    // 5. （可选）保存当前用户
    User currentUser;

    // 6. 初始化 UI 逻辑（绑定事件、设置初始值等）
    void initUI();
};

#endif // QTWIDGETSAPPLICATION99_H
