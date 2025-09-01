#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QVBoxLayout>

#include <QStringList>
using namespace Qt;

class AdminMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    AdminMainWindow(QWidget* parent = nullptr);
    ~AdminMainWindow(); // 析构函数声明

private:
    // 1. 表格控件（含新增的订单表格）
    QTableWidget* stationTable;
    QTableWidget* trainTable;
    QTableWidget* scheduleTable;
    QTableWidget* seatTable;
    QTableWidget* userTable;
    QTableWidget* orderTable;

    // 2. 按钮控件（含扩展功能按钮）
    QPushButton* addStationBtn;
    QPushButton* delStationBtn;
    QPushButton* addTrainBtn;
    QPushButton* delTrainBtn;
    QPushButton* addScheduleBtn;
    QPushButton* delScheduleBtn;
    QPushButton* addSeatBtn;
    QPushButton* delSeatBtn;
    QPushButton* addUserBtn;
    QPushButton* delUserBtn;
    QPushButton* resetPwdBtn;   // 新增：重置密码按钮
    QPushButton* lockUserBtn;   // 新增：锁定/解锁用户按钮
    QPushButton* refundOrderBtn;// 新增：订单退票按钮
    QPushButton* changeOrderBtn;// 新增：订单改签按钮

    // 3. 工具函数（表格/分组框创建）
    QTableWidget* createTable(const QStringList& headers);
    QGroupBox* createGroupBox(const QString& title, QTableWidget* table, QPushButton* addBtn, QPushButton* delBtn);
    QGroupBox* createGroupBox(const QString& title, QTableWidget* table, QHBoxLayout* customBtnLayout); // 重载：自定义按钮布局

    // 4. 数据处理函数（含扩展功能）
    QStringList getTableCurrentRowData(QTableWidget* table);
    void loadTableData(const QString& fileName, QTableWidget* table);
    void writeToFile(const QString& fileName, const QStringList& newData);
    void deleteFromFile(const QString& fileName, int row);

    // 5. 数据加载函数（含新增的用户状态加载、订单加载）
    void loadStations();
    void loadTrains();
    void loadSchedules();
    void loadSeats();
    void loadUsers();   // 扩展：加载用户（含状态列）
    void loadOrders();  // 新增：加载订单数据

    // 6. 扩展功能函数（用户管理+退改签）
    void resetUserPassword();  // 重置用户密码
    void toggleUserLock();     // 锁定/解锁用户
    void refundOrder();        // 订单退票
    void changeOrder();        // 订单改签
};

#endif // ADMINMAINWINDOW_H