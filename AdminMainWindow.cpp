#include "AdminMainWindow.h"
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QColor>
#include <QMessageBox>
#include <QGroupBox>

AdminMainWindow::AdminMainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    // 1. 创建基础表格（含用户表格扩展“状态”列、新增订单表格）
    stationTable = createTable({ "ID", "名称" });
    trainTable = createTable({ "ID", "名称", "类型", "出发站", "终点站" });
    scheduleTable = createTable({ "ID", "列车ID", "车站ID", "stop_order", "出发时间", "到达时间" });
    seatTable = createTable({ "座位ID", "列车ID", "座位号", "座位模板" });
    // 用户表格扩展：新增“状态”列（normal/locked）
    userTable = createTable({ "ID", "用户真名", "用户昵称", "密码", "手机号", "角色", "身份证号", "状态" });
    // 新增订单表格（对应order.txt字段）
    orderTable = createTable({ "订单ID", "用户ID", "列车ID", "座位ID", "出发站ID", "到达站ID", "出行日期", "下单时间", "状态" });

    // 2. 创建所有按钮（含用户管理扩展按钮、订单退改签按钮）
    // 基础功能按钮
    addStationBtn = new QPushButton("新增车站", this);
    delStationBtn = new QPushButton("删除车站", this);
    addTrainBtn = new QPushButton("新增列车", this);
    delTrainBtn = new QPushButton("删除列车", this);
    addScheduleBtn = new QPushButton("新增时刻表", this);
    delScheduleBtn = new QPushButton("删除时刻表", this);
    addSeatBtn = new QPushButton("新增座位模板", this);
    delSeatBtn = new QPushButton("删除座位模板", this);
    addUserBtn = new QPushButton("新增用户", this);
    delUserBtn = new QPushButton("删除用户", this);
    // 用户管理扩展按钮
    resetPwdBtn = new QPushButton("重置密码", this);
    lockUserBtn = new QPushButton("锁定/解锁用户", this);
    // 订单退改签按钮
    refundOrderBtn = new QPushButton("订单退票", this);
    changeOrderBtn = new QPushButton("订单改签", this);

    // 3. 创建分组框（含用户管理扩展按钮布局、新增订单分组框）
    // 基础分组框
    QGroupBox* stationGroup = createGroupBox("车站管理", stationTable, addStationBtn, delStationBtn);
    QGroupBox* trainGroup = createGroupBox("列车管理", trainTable, addTrainBtn, delTrainBtn);
    QGroupBox* scheduleGroup = createGroupBox("时刻表管理", scheduleTable, addScheduleBtn, delScheduleBtn);
    QGroupBox* seatGroup = createGroupBox("座位模板管理", seatTable, addSeatBtn, delSeatBtn);
    // 用户分组框（自定义按钮布局：新增+删除+重置密码+锁定解锁）
    QHBoxLayout* userBtnLayout = new QHBoxLayout();
    userBtnLayout->addWidget(addUserBtn);
    userBtnLayout->addWidget(delUserBtn);
    userBtnLayout->addWidget(resetPwdBtn);
    userBtnLayout->addWidget(lockUserBtn);
    QGroupBox* userGroup = createGroupBox("用户管理", userTable, userBtnLayout);
    // 订单分组框（自定义按钮布局：退票+改签）
    QHBoxLayout* orderBtnLayout = new QHBoxLayout();
    orderBtnLayout->addWidget(refundOrderBtn);
    orderBtnLayout->addWidget(changeOrderBtn);
    QGroupBox* orderGroup = createGroupBox("订单管理（手工退改签）", orderTable, orderBtnLayout);

    // 4. 设置主布局
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // 分组框样式（边框可视化）
    QList<QGroupBox*> groups = { stationGroup, trainGroup, scheduleGroup, seatGroup, userGroup, orderGroup };
    for (QGroupBox* group : groups) {
        group->setStyleSheet("QGroupBox { border: 1px solid #AAA; border-radius: 5px; margin-top: 10px; }");
    }

    // 添加分组框到主布局并设置拉伸因子
    mainLayout->addWidget(stationGroup);
    mainLayout->addWidget(trainGroup);
    mainLayout->addWidget(scheduleGroup);
    mainLayout->addWidget(seatGroup);
    mainLayout->addWidget(userGroup);
    mainLayout->addWidget(orderGroup);
    mainLayout->setStretchFactor(stationGroup, 1);
    mainLayout->setStretchFactor(trainGroup, 1);
    mainLayout->setStretchFactor(scheduleGroup, 1);
    mainLayout->setStretchFactor(seatGroup, 1);
    mainLayout->setStretchFactor(userGroup, 1);
    mainLayout->setStretchFactor(orderGroup, 1);

    setCentralWidget(centralWidget);
    setMinimumSize(1200, 900);
    setWindowTitle("管理员主界面");

    // 5. 加载所有数据（含用户状态、订单数据）
    loadStations();
    loadTrains();
    loadSchedules();
    loadSeats();
    loadUsers();
    loadOrders();

    // 6. 绑定基础功能按钮信号槽（原功能保留）
    // 车站管理
    connect(addStationBtn, &QPushButton::clicked, this, [=]() {
        int newRow = stationTable->rowCount();
        stationTable->insertRow(newRow);
        for (int col = 0; col < stationTable->columnCount(); col++) {
            stationTable->setItem(newRow, col, new QTableWidgetItem(""));
        }
        stationTable->scrollToBottom();
        connect(stationTable, &QTableWidget::cellChanged, this, [=](int row, int col) {
            if (row == newRow) {
                QStringList data = getTableCurrentRowData(stationTable);
                if (!data.isEmpty()) {
                    writeToFile("D:/qt/QtWidgetsApplication99/x64/Debug/stations.txt", data);
                    disconnect(stationTable, &QTableWidget::cellChanged, this, nullptr);
                }
            }
            });
        });
    connect(delStationBtn, &QPushButton::clicked, this, [=]() {
        int currentRow = stationTable->currentRow();
        if (currentRow < 0) { QMessageBox::warning(this, "提示", "请先选中要删除的车站行！"); return; }
        deleteFromFile("D:/qt/QtWidgetsApplication99/x64/Debug/stations.txt", currentRow);
        stationTable->removeRow(currentRow);
        QMessageBox::information(this, "提示", "车站删除成功！");
        });

    // 列车管理
    connect(addTrainBtn, &QPushButton::clicked, this, [=]() {
        int newRow = trainTable->rowCount();
        trainTable->insertRow(newRow);
        for (int col = 0; col < trainTable->columnCount(); col++) {
            trainTable->setItem(newRow, col, new QTableWidgetItem(""));
        }
        trainTable->scrollToBottom();
        connect(trainTable, &QTableWidget::cellChanged, this, [=](int row, int col) {
            if (row == newRow) {
                QStringList data = getTableCurrentRowData(trainTable);
                if (!data.isEmpty()) {
                    writeToFile("D:/qt/QtWidgetsApplication99/x64/Debug/trains.txt", data);
                    disconnect(trainTable, &QTableWidget::cellChanged, this, nullptr);
                }
            }
            });
        });
    connect(delTrainBtn, &QPushButton::clicked, this, [=]() {
        int currentRow = trainTable->currentRow();
        if (currentRow < 0) { QMessageBox::warning(this, "提示", "请先选中要删除的列车行！"); return; }
        deleteFromFile("D:/qt/QtWidgetsApplication99/x64/Debug/trains.txt", currentRow);
        trainTable->removeRow(currentRow);
        QMessageBox::information(this, "提示", "列车删除成功！");
        });

    // 时刻表管理
    connect(addScheduleBtn, &QPushButton::clicked, this, [=]() {
        int newRow = scheduleTable->rowCount();
        scheduleTable->insertRow(newRow);
        for (int col = 0; col < scheduleTable->columnCount(); col++) {
            scheduleTable->setItem(newRow, col, new QTableWidgetItem(""));
        }
        scheduleTable->scrollToBottom();
        connect(scheduleTable, &QTableWidget::cellChanged, this, [=](int row, int col) {
            if (row == newRow) {
                QStringList data = getTableCurrentRowData(scheduleTable);
                if (!data.isEmpty()) {
                    writeToFile("D:/qt/QtWidgetsApplication99/x64/Debug/train_schedule.txt", data);
                    disconnect(scheduleTable, &QTableWidget::cellChanged, this, nullptr);
                }
            }
            });
        });
    connect(delScheduleBtn, &QPushButton::clicked, this, [=]() {
        int currentRow = scheduleTable->currentRow();
        if (currentRow < 0) { QMessageBox::warning(this, "提示", "请先选中要删除的时刻表行！"); return; }
        deleteFromFile("D:/qt/QtWidgetsApplication99/x64/Debug/train_schedule.txt", currentRow);
        scheduleTable->removeRow(currentRow);
        QMessageBox::information(this, "提示", "时刻表删除成功！");
        });

    // 座位模板管理
    connect(addSeatBtn, &QPushButton::clicked, this, [=]() {
        int newRow = seatTable->rowCount();
        seatTable->insertRow(newRow);
        for (int col = 0; col < seatTable->columnCount(); col++) {
            seatTable->setItem(newRow, col, new QTableWidgetItem(""));
        }
        seatTable->scrollToBottom();
        connect(seatTable, &QTableWidget::cellChanged, this, [=](int row, int col) {
            if (row == newRow) {
                QStringList data = getTableCurrentRowData(seatTable);
                if (!data.isEmpty()) {
                    writeToFile("D:/qt/QtWidgetsApplication99/x64/Debug/seats.txt", data);
                    disconnect(seatTable, &QTableWidget::cellChanged, this, nullptr);
                }
            }
            });
        });
    connect(delSeatBtn, &QPushButton::clicked, this, [=]() {
        int currentRow = seatTable->currentRow();
        if (currentRow < 0) { QMessageBox::warning(this, "提示", "请先选中要删除的座位模板行！"); return; }
        deleteFromFile("D:/qt/QtWidgetsApplication99/x64/Debug/seats.txt", currentRow);
        seatTable->removeRow(currentRow);
        QMessageBox::information(this, "提示", "座位模板删除成功！");
        });

    // 用户管理（原新增/删除功能）
    connect(addUserBtn, &QPushButton::clicked, this, [=]() {
        int newRow = userTable->rowCount();
        userTable->insertRow(newRow);
        for (int col = 0; col < userTable->columnCount(); col++) {
            userTable->setItem(newRow, col, new QTableWidgetItem(col == 7 ? "normal" : "")); // 状态默认normal
        }
        userTable->scrollToBottom();
        connect(userTable, &QTableWidget::cellChanged, this, [=](int row, int col) {
            if (row == newRow) {
                QStringList data = getTableCurrentRowData(userTable);
                if (!data.isEmpty()) {
                    writeToFile("D:/qt/QtWidgetsApplication99/x64/Debug/users.txt", data);
                    disconnect(userTable, &QTableWidget::cellChanged, this, nullptr);
                }
            }
            });
        });
    connect(delUserBtn, &QPushButton::clicked, this, [=]() {
        int currentRow = userTable->currentRow();
        if (currentRow < 0) { QMessageBox::warning(this, "提示", "请先选中要删除的用户行！"); return; }
        deleteFromFile("D:/qt/QtWidgetsApplication99/x64/Debug/users.txt", currentRow);
        userTable->removeRow(currentRow);
        QMessageBox::information(this, "提示", "用户删除成功！");
        });

    // 7. 绑定扩展功能按钮信号槽（用户重置密码/锁定解锁、订单退改签）
    connect(resetPwdBtn, &QPushButton::clicked, this, &AdminMainWindow::resetUserPassword);
    connect(lockUserBtn, &QPushButton::clicked, this, &AdminMainWindow::toggleUserLock);
    connect(refundOrderBtn, &QPushButton::clicked, this, &AdminMainWindow::refundOrder);
    connect(changeOrderBtn, &QPushButton::clicked, this, &AdminMainWindow::changeOrder);
}

// 基础表格创建函数（原功能保留）
QTableWidget* AdminMainWindow::createTable(const QStringList& headers)
{
    QTableWidget* table = new QTableWidget(this);
    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QTableWidget::AllEditTriggers);
    return table;
}

// 分组框创建函数（重载：支持默认双按钮/自定义按钮布局）
QGroupBox* AdminMainWindow::createGroupBox(const QString& title, QTableWidget* table, QPushButton* addBtn, QPushButton* delBtn)
{
    QGroupBox* group = new QGroupBox(title, this);
    QVBoxLayout* layout = new QVBoxLayout(group);
    layout->addWidget(table);
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(addBtn);
    btnLayout->addWidget(delBtn);
    layout->addLayout(btnLayout);
    return group;
}

QGroupBox* AdminMainWindow::createGroupBox(const QString& title, QTableWidget* table, QHBoxLayout* customBtnLayout)
{
    QGroupBox* group = new QGroupBox(title, this);
    QVBoxLayout* layout = new QVBoxLayout(group);
    layout->addWidget(table);
    layout->addLayout(customBtnLayout);
    return group;
}

// 表格行数据获取函数（原功能优化：空值校验+红色提示）
QStringList AdminMainWindow::getTableCurrentRowData(QTableWidget* table)
{
    QStringList data;
    int row = table->currentRow();
    if (row == -1) { QMessageBox::warning(this, "错误", "无选中行，无法获取数据！"); return {}; }

    bool hasEmpty = false;
    for (int col = 0; col < table->columnCount(); col++) {
        QTableWidgetItem* item = table->item(row, col);
        if (!item || item->text().trimmed().isEmpty()) {
            hasEmpty = true;
            item->setBackground(QColor(255, 200, 200));
            continue;
        }
        data << item->text().trimmed();
        item->setBackground(QColor(255, 255, 255)); // 清除之前的红色提示
    }

    if (hasEmpty) { QMessageBox::warning(this, "提示", "存在空字段，请填写完整（标红字段为空）！"); return {}; }
    return data;
}

// 基础数据加载函数（原功能保留，用户加载新增状态列处理）
void AdminMainWindow::loadStations()
{
    loadTableData("D:/qt/QtWidgetsApplication99/x64/Debug/stations.txt", stationTable);
}

void AdminMainWindow::loadTrains()
{
    loadTableData("D:/qt/QtWidgetsApplication99/x64/Debug/trains.txt", trainTable);
}

void AdminMainWindow::loadSchedules()
{
    loadTableData("D:/qt/QtWidgetsApplication99/x64/Debug/train_schedule.txt", scheduleTable);
}

void AdminMainWindow::loadSeats()
{
    loadTableData("D:/qt/QtWidgetsApplication99/x64/Debug/seats.txt", seatTable);
}

// 用户加载：处理“状态”列（补全默认值normal）
void AdminMainWindow::loadUsers()
{
    loadTableData("D:/qt/QtWidgetsApplication99/x64/Debug/users.txt", userTable);
   
}

// 订单加载：跳过order.txt表头，加载订单数据
void AdminMainWindow::loadOrders()
{
    loadTableData("D:/qt/QtWidgetsApplication99/x64/Debug/orders.txt", orderTable);
   
}

// 通用表格数据加载函数（原功能保留，适配基础表格）
void AdminMainWindow::loadTableData(const QString& fileName, QTableWidget* table)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件：" << fileName;
        QMessageBox::critical(this, "错误", "无法加载数据，文件打开失败！");
        return;
    }

    QTextStream in(&file);
    table->setRowCount(0); // 清空原有数据
    QString line;
    int rowCount = 0;

    while (in.readLineInto(&line)) {
        line = line.trimmed();
        if (line.isEmpty()) continue;

        QStringList fields = line.split(",");
        int row = table->rowCount();
        table->insertRow(row);
        for (int col = 0; col < fields.size(); ++col) {
            table->setItem(row, col, new QTableWidgetItem(fields[col].trimmed()));
        }
        rowCount++;
    }
    file.close();

    // 空文件时插入一行空行
    if (rowCount == 0) {
        table->insertRow(0);
        for (int col = 0; col < table->columnCount(); col++) {
            table->setItem(0, col, new QTableWidgetItem(""));
        }
    }
}

// 基础文件写入函数（原功能保留，适配新增用户状态列）
void AdminMainWindow::writeToFile(const QString& fileName, const QStringList& newData)
{
    QFile file(fileName);
    // 以“追加”模式打开，新增数据写入文件末尾
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qDebug() << "[错误] 写入失败：" << fileName << "，原因：" << file.errorString();
        QMessageBox::critical(this, "错误", "数据写入失败，文件打开失败！");
        return;
    }

    QTextStream out(&file);
    out << newData.join(",") << "\n"; // 数据以逗号分隔，换行存储
    file.close();

    // 写入后重新加载对应表格，更新UI
    if (fileName.contains("stations.txt")) loadStations();
    else if (fileName.contains("trains.txt")) loadTrains();
    else if (fileName.contains("train_schedule.txt")) loadSchedules();
    else if (fileName.contains("seats.txt")) loadSeats();
    else if (fileName.contains("users.txt")) loadUsers();
    QMessageBox::information(this, "成功", "数据新增成功！");
}

// 基础文件删除函数（原功能保留，适配用户/订单表格）
void AdminMainWindow::deleteFromFile(const QString& fileName, int row)
{
    // 校验行号有效性
    if (row < 0) {
        qDebug() << "错误：行号无效（" << row << "）";
        QMessageBox::warning(this, "错误", "无效行号，删除失败！");
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法读取文件：" << fileName;
        QMessageBox::critical(this, "错误", "无法读取数据，删除失败！");
        return;
    }

    // 读取所有行，排除要删除的行
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) lines << line;
    }
    file.close();

    // 校验行号是否超出文件行数
    if (row >= lines.size()) {
        qDebug() << "错误：行号超出范围（文件共" << lines.size() << "行，尝试删除第" << row << "行）";
        QMessageBox::warning(this, "错误", "行号超出范围，删除失败！");
        return;
    }

    // 移除目标行，重新写入文件
    lines.removeAt(row);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法写入文件：" << fileName;
        QMessageBox::critical(this, "错误", "无法写入数据，删除失败！");
        return;
    }

    QTextStream out(&file);
    for (const QString& line : lines) out << line << "\n";
    file.close();

    // 删除后重新加载对应表格，更新UI
    if (fileName.contains("stations.txt")) loadStations();
    else if (fileName.contains("trains.txt")) loadTrains();
    else if (fileName.contains("train_schedule.txt")) loadSchedules();
    else if (fileName.contains("seats.txt")) loadSeats();
    else if (fileName.contains("users.txt")) loadUsers();
}

// 扩展功能：重置用户密码（默认重置为123456）
void AdminMainWindow::resetUserPassword()
{
    int currentRow = userTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选中要重置密码的用户行！");
        return;
    }

    // 1. 更新表格显示：密码列（索引3）设为123456
    userTable->setItem(currentRow, 3, new QTableWidgetItem("123456"));

    // 2. 更新users.txt文件
    QString filePath = "D:/qt/QtWidgetsApplication99/x64/Debug/users.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法读取用户文件，重置失败！");
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) lines << line;
    }
    file.close();

    // 校验行号有效性
    if (currentRow >= lines.size()) {
        QMessageBox::warning(this, "错误", "用户行号超出范围，重置失败！");
        return;
    }

    // 拆分用户数据，修改密码字段（索引3），补全状态字段（索引7）
    QStringList userData = lines[currentRow].split(",");
    userData.resize(8, "normal"); // 确保至少8列，状态默认normal
    userData[3] = "123456"; // 密码重置为123456
    lines[currentRow] = userData.join(",");

    // 重新写入文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法写入用户文件，重置失败！");
        return;
    }
    QTextStream out(&file);
    for (const QString& line : lines) out << line << "\n";
    file.close();

    QMessageBox::information(this, "成功", "密码重置成功！默认密码：123456");
    loadUsers(); // 重新加载用户数据，刷新UI
}

// 扩展功能：锁定/解锁用户（切换normal/locked状态）
void AdminMainWindow::toggleUserLock()
{
    int currentRow = userTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选中要操作的用户行！");
        return;
    }

    // 1. 获取当前用户状态（第8列，索引7）
    QTableWidgetItem* statusItem = userTable->item(currentRow, 7);
    if (!statusItem) {
        QMessageBox::warning(this, "错误", "用户状态字段缺失，操作失败！");
        return;
    }
    QString currentStatus = statusItem->text().trimmed();
    QString newStatus = (currentStatus == "locked") ? "normal" : "locked";

    // 2. 更新表格显示
    statusItem->setText(newStatus);

    // 3. 更新users.txt文件
    QString filePath = "D:/qt/QtWidgetsApplication99/x64/Debug/users.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法读取用户文件，操作失败！");
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) lines << line;
    }
    file.close();

    // 校验行号有效性
    if (currentRow >= lines.size()) {
        QMessageBox::warning(this, "错误", "用户行号超出范围，操作失败！");
        return;
    }

    // 拆分用户数据，修改状态字段（索引7）
    QStringList userData = lines[currentRow].split(",");
    userData.resize(8, "normal"); // 确保至少8列
    userData[7] = newStatus;
    lines[currentRow] = userData.join(",");

    // 重新写入文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法写入用户文件，操作失败！");
        return;
    }
    QTextStream out(&file);
    for (const QString& line : lines) out << line << "\n";
    file.close();

    QString info = QString("用户已%1").arg(newStatus == "locked" ? "锁定" : "解锁");
    QMessageBox::information(this, "成功", info);
    //QMessageBox::information(this, "成功", "用户已" + (newStatus == "locked" ? "锁定" : "解锁"));
    loadUsers(); // 重新加载用户数据，刷新UI
}

// 扩展功能：订单退票（修改状态为refunded）
void AdminMainWindow::refundOrder()
{
    int currentRow = orderTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选中要退票的订单行！");
        return;
    }

    // 1. 校验订单当前状态（已取消/退票的不能重复操作）
    QTableWidgetItem* statusItem = orderTable->item(currentRow, 8);
    if (!statusItem) {
        QMessageBox::warning(this, "错误", "订单状态字段缺失，退票失败！");
        return;
    }
    QString currentStatus = statusItem->text().trimmed();
    if (currentStatus == "canceled" || currentStatus == "refunded") {
        QMessageBox::warning(this, "提示", "该订单已取消/退票，无需重复操作！");
        return;
    }

    // 2. 更新表格显示：状态改为refunded
    statusItem->setText("refunded");

    // 3. 更新order.txt文件（注意：订单文件含表头，数据行索引=表格行号+1）
    QString filePath = "D:/qt/QtWidgetsApplication99/x64/Debug/orders.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法读取订单文件，退票失败！");
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        lines << in.readLine().trimmed(); // 保留表头，不跳过（后续需原样写入）
    }
    file.close();

    // 校验数据行号有效性（表头占1行，数据行从索引1开始）
    int dataRow = currentRow + 1;
    if (dataRow >= lines.size()) {
        QMessageBox::warning(this, "错误", "订单行号超出范围，退票失败！");
        return;
    }

    // 拆分订单数据，修改状态字段（索引8）
    QStringList orderData = lines[dataRow].split(",");
    if (orderData.size() < 9) {
        QMessageBox::warning(this, "错误", "订单数据不完整，退票失败！");
        return;
    }
    orderData[8] = "refunded";
    lines[dataRow] = orderData.join(",");

    // 重新写入文件（含表头）
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法写入订单文件，退票失败！");
        return;
    }
    QTextStream out(&file);
    for (const QString& line : lines) out << line << "\n";
    file.close();

    QMessageBox::information(this, "成功", "订单退票成功！");
    loadOrders(); // 重新加载订单数据，刷新UI
}

// 扩展功能：订单改签（允许修改列车ID/座位ID/出发站ID/到达站ID/出行日期）
void AdminMainWindow::changeOrder()
{
    int currentRow = orderTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选中要改签的订单行！");
        return;
    }

    // 1. 校验订单数据完整性（空字段标红提示）
    bool hasEmpty = false;
    for (int col = 0; col < orderTable->columnCount(); col++) {
        QTableWidgetItem* item = orderTable->item(currentRow, col);
        if (!item || item->text().trimmed().isEmpty()) {
            hasEmpty = true;
            item->setBackground(QColor(255, 200, 200)); // 空字段标红提示
        }
        else {
            item->setBackground(QColor(255, 255, 255)); // 清除已填写字段的红色提示
        }
    }
    if (hasEmpty) {
        QMessageBox::warning(this, "提示", "存在空字段，请填写完整（标红字段为空）！");
        return;
    }

    // 2. 获取改签后的完整订单数据
    QStringList newOrderData;
    for (int col = 0; col < orderTable->columnCount(); col++) {
        QTableWidgetItem* item = orderTable->item(currentRow, col);
        newOrderData << item->text().trimmed();
    }

    // 3. 更新order.txt文件（含表头处理：数据行索引=表格行号+1）
    QString filePath = "D:/qt/QtWidgetsApplication99/x64/Debug/orders.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法读取订单文件，改签失败！");
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        lines << in.readLine().trimmed(); // 保留表头
    }
    file.close();

    // 校验数据行号有效性
    int dataRow = currentRow + 1;
    if (dataRow >= lines.size()) {
        QMessageBox::warning(this, "错误", "订单行号超出范围，改签失败！");
        return;
    }

    // 替换原有订单数据（保持订单ID不变，其他字段更新为改签后数据）
    lines[dataRow] = newOrderData.join(",");

    // 重新写入文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法写入订单文件，改签失败！");
        return;
    }
    QTextStream out(&file);
    for (const QString& line : lines) out << line << "\n";
    file.close();

    QMessageBox::information(this, "成功", "订单改签成功！");
    loadOrders(); // 重新加载订单数据，刷新UI
}

// 析构函数（释放动态分配的控件，避免内存泄漏）
AdminMainWindow::~AdminMainWindow()
{
    // 释放表格控件
    delete stationTable;
    delete trainTable;
    delete scheduleTable;
    delete seatTable;
    delete userTable;
    delete orderTable;

    // 释放按钮控件
    delete addStationBtn;
    delete delStationBtn;
    delete addTrainBtn;
    delete delTrainBtn;
    delete addScheduleBtn;
    delete delScheduleBtn;
    delete addSeatBtn;
    delete delSeatBtn;
    delete addUserBtn;
    delete delUserBtn;
    delete resetPwdBtn;
    delete lockUserBtn;
    delete refundOrderBtn;
    delete changeOrderBtn;
}