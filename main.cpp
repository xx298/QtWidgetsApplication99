#include <QApplication>
#include "UserLoginDialog.h"  // 登录对话框
#include "AdminMainWindow.h"  // 管理员主界面
#include "QtWidgetsApplication99.h"// 用户主界面

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // 1. 显示登录对话框
    UserLoginDialog loginDialog;
    // 2. 执行登录校验（阻塞，直到登录窗口关闭）
    int result = loginDialog.exec();

    if (result == QDialog::Accepted) {
        // 3. 登录成功：获取角色并跳转对应主界面
        User::Role loggedRole = loginDialog.getLoggedInRole();

        if (loggedRole == User::ROLE_USER) {
            QtWidgetsApplication99 userWin;
            userWin.show();
            return app.exec();
        }
        else if (loggedRole == User::ROLE_ADMIN) {
            AdminMainWindow adminWindow;
            adminWindow.show();
            return app.exec();
        }
        //test
        qDebug() << "Logged Role:" << loggedRole; // 打印角色
    }

    // 4. 登录失败或取消，直接退出
    return 0;
}