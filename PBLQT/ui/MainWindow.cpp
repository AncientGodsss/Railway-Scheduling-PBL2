#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "StyleSheet.h"
#include "dialogs/TrainDialog.h"
#include "dialogs/StationDialog.h"
#include "dialogs/RouteDialog.h"
#include "dialogs/ScheduleDialog.h"
#include "dialogs/StopDialog.h"
#include <QApplication>
#include <QComboBox>
#include <QDate>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QTextEdit>
#include <sstream>
#include <iostream>
using namespace std;

static void setupTable(QTableWidget* table, const QStringList& headers)
{
    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);
    table->verticalHeader()->setVisible(false);
    table->verticalHeader()->setDefaultSectionSize(38);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qApp->setStyleSheet(appStyleSheet());
    connect(ui->navigationList, &QListWidget::currentRowChanged, ui->stackedWidget, &QStackedWidget::setCurrentIndex);
    setupTable(ui->trainTable, {"Mã tàu", "Tên tàu", "Loại", "Sức chứa", "Tốc độ", "Trạng thái", "Ghi chú"});
    setupTable(ui->stationTable, {"Mã ga", "Tên ga", "Vị trí", "Số đường ray"});
    setupTable(ui->routeTable, {"Mã tuyến", "Ga đầu", "Ga cuối", "Khoảng cách", "Thời gian", "Trạng thái"});
    setupTable(ui->scheduleTable,
               {"Mã lịch", "Mã tàu", "Ga đi", "Ga đến", "Ngày", "Giờ đi", "Giờ đến", "Ưu tiên", "Trạng thái"});
    setupTable(ui->stopTable, {"Thứ tự", "Mã ga", "Giờ đến", "Giờ rời"});
    connect(ui->btnAddTrain, &QPushButton::clicked, this, &MainWindow::onAddTrain);
    connect(ui->btnEditTrain, &QPushButton::clicked, this, &MainWindow::onEditTrain);
    connect(ui->btnDeleteTrain, &QPushButton::clicked, this, &MainWindow::onDeleteTrain);
    connect(ui->btnRefreshTrain, &QPushButton::clicked, this, &MainWindow::refreshTrainTable);
    connect(ui->btnAddStation, &QPushButton::clicked, this, &MainWindow::onAddStation);
    connect(ui->btnEditStation, &QPushButton::clicked, this, &MainWindow::onEditStation);
    connect(ui->btnDeleteStation, &QPushButton::clicked, this, &MainWindow::onDeleteStation);
    connect(ui->btnRefreshStation, &QPushButton::clicked, this, &MainWindow::refreshStationTable);
    connect(ui->btnAddRoute, &QPushButton::clicked, this, &MainWindow::onAddRoute);
    connect(ui->btnEditRoute, &QPushButton::clicked, this, &MainWindow::onEditRoute);
    connect(ui->btnDeleteRoute, &QPushButton::clicked, this, &MainWindow::onDeleteRoute);
    connect(ui->btnRefreshRoute, &QPushButton::clicked, this, &MainWindow::refreshRouteTable);
    connect(ui->btnAddSchedule, &QPushButton::clicked, this, &MainWindow::onAddSchedule);
    connect(ui->btnEditSchedule, &QPushButton::clicked, this, &MainWindow::onEditSchedule);
    connect(ui->btnDeleteSchedule, &QPushButton::clicked, this, &MainWindow::onDeleteSchedule);
    connect(ui->btnRefreshSchedule, &QPushButton::clicked, this, &MainWindow::refreshScheduleTable);
    connect(ui->btnViewStops, &QPushButton::clicked, this, &MainWindow::onViewStops);
    connect(ui->btnAddStop, &QPushButton::clicked, this, &MainWindow::onAddStop);
    connect(ui->btnEditStop, &QPushButton::clicked, this, &MainWindow::onEditStop);
    connect(ui->btnDeleteStop, &QPushButton::clicked, this, &MainWindow::onDeleteStop);
    connect(ui->btnSortTime, &QPushButton::clicked, this, &MainWindow::onSortByTime);
    connect(ui->btnSortPriority, &QPushButton::clicked, this, &MainWindow::onSortByPriority);
    connect(ui->btnRefreshSchedules, &QPushButton::clicked, this, &MainWindow::refreshScheduleSelectors);
    connect(ui->btnCheckConflict, &QPushButton::clicked, this, &MainWindow::onCheckConflict);
    connect(ui->btnDispatch, &QPushButton::clicked, this, &MainWindow::onDispatch);
    connect(ui->strategyCombo, qOverload<int>(&QComboBox::currentIndexChanged), this, &MainWindow::onChangeStrategy);
    connect(ui->btnShowQueue, &QPushButton::clicked, this, &MainWindow::onShowQueue);
    connect(ui->btnAddQueue, &QPushButton::clicked, this, &MainWindow::onAddToQueue);
    connect(ui->btnNextTrain, &QPushButton::clicked, this, &MainWindow::onNextTrain);
    connect(ui->btnShowHistory, &QPushButton::clicked, this, &MainWindow::onShowHistory);
    connect(ui->btnClearQueue, &QPushButton::clicked, this, &MainWindow::onClearQueue);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onLoad);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSave);
    connect(ui->actionQuit, &QAction::triggered, this, &QWidget::close);
    system.loadAllData();
    refreshTrainTable();
    refreshStationTable();
    refreshRouteTable();
    refreshScheduleTable();
    refreshScheduleSelectors();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshScheduleSelectors()
{
    QComboBox* boxes[] = {ui->cbConflictA, ui->cbConflictB};
    int boxCount = 2;

    for (int i = 0; i < boxCount; ++i)
        boxes[i]->clear();

    int total = system.getScheduleCount();
    if (total == 0)
        return;

    ScheduleBST bst;
    for (int i = 0; i < total; ++i)
    {
        Schedule* s = system.getScheduleAt(i);
        if (!s)
            continue;
        string sid = s->getScheduleId();
        int num = 0;
        for (char c : sid)
            if (isdigit(static_cast<unsigned char>(c)))
                num = num * 10 + (c - '0');
        bst.insert(num, s);
    }

    Schedule** sortedSchedules = new Schedule*[total];
    int count = bst.getAscending(sortedSchedules, total);

    for (int i = 0; i < count; ++i)
    {
        Schedule* schedule = sortedSchedules[i];
        if (!schedule)
            continue;

        QString id = QString::fromStdString(schedule->getScheduleId());
        QString trainId = QString::fromStdString(schedule->getTrainId());
        QString depStation = QString::fromStdString(schedule->getDepartureStationId());
        QString destStation = QString::fromStdString(schedule->getDestinationStationId());
        QString depTime = QString::fromStdString(TimeUtils::minutesToDisplay(schedule->getDepartureTime()));
        QString arrTime = QString::fromStdString(TimeUtils::minutesToDisplay(schedule->getArrivalTime()));
        QString text = QString("[%1] Tàu %2: %3 -> %4 (%5 - %6)")
                           .arg(id, trainId, depStation, destStation, depTime, arrTime);

        for (int j = 0; j < boxCount; ++j)
        {
            boxes[j]->addItem(text, id);
        }
    }
    delete[] sortedSchedules;
}

static QString translateStatus(const string& st)
{
    if (st == "ACTIVE" || st == "Hoạt động")
        return QStringLiteral(u"Hoạt động");
    if (st == "INACTIVE" || st == "Tạm ngưng")
        return QStringLiteral(u"Tạm ngưng");
    if (st == "MAINTENANCE" || st == "Bảo trì")
        return QStringLiteral(u"Bảo trì");
    if (st == "SCHEDULED" || st == "Đã lên lịch")
        return QStringLiteral(u"Đã lên lịch");
    if (st == "RUNNING" || st == "Đang chạy")
        return QStringLiteral(u"Đang chạy");
    if (st == "COMPLETED" || st == "Hoàn thành")
        return QStringLiteral(u"Hoàn thành");
    if (st == "CANCELLED" || st == "Đã hủy")
        return QStringLiteral(u"Đã hủy");
    return QString::fromStdString(st);
}

static QString translateTrainType(const string& tt)
{
    if (tt == "express" || tt == "Passenger" || tt == "Tàu khách")
        return QStringLiteral(u"Tàu khách");
    if (tt == "local")
        return QStringLiteral(u"Tàu khách (Địa phương)");
    if (tt == "freight" || tt == "Freight" || tt == "Tàu hàng")
        return QStringLiteral(u"Tàu chở hàng");
    return QString::fromStdString(tt);
}

static QString formatDayOfWeek(const string& dateStr)
{
    QString qstr = QString::fromStdString(dateStr);
    QDate d = QDate::fromString(qstr, "dd/MM/yyyy");
    if (!d.isValid())
        return qstr;
    QString dow;
    switch (d.dayOfWeek())
    {
    case 1:
        dow = "T2";
        break;
    case 2:
        dow = "T3";
        break;
    case 3:
        dow = "T4";
        break;
    case 4:
        dow = "T5";
        break;
    case 5:
        dow = "T6";
        break;
    case 6:
        dow = "T7";
        break;
    case 7:
        dow = "CN";
        break;
    }
    return dow + ", " + qstr;
}

void MainWindow::fillScheduleRow(QTableWidget* t, Schedule* s)
{
    if (!s)
        return;
    int row = t->rowCount();
    t->insertRow(row);
    t->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(s->getScheduleId())));
    t->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(s->getTrainId())));
    t->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(s->getDepartureStationId())));
    t->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(s->getDestinationStationId())));
    t->setItem(row, 4, new QTableWidgetItem(formatDayOfWeek(s->getDepartureDate())));
    t->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(TimeUtils::minutesToDisplay(s->getDepartureTime()))));
    t->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(TimeUtils::minutesToDisplay(s->getArrivalTime()))));
    t->setItem(row, 7, new QTableWidgetItem(QString::number(s->getPriority())));
    t->setItem(row, 8, new QTableWidgetItem(translateStatus(s->getStatus())));

    Train* train = system.findTrain(s->getTrainId());
    bool trainProblem = false;
    QString trainWarning;
    if (!train)
    {
        trainProblem = true;
        trainWarning = QStringLiteral(u"⚠ Tàu không tồn tại");
    }
    else
    {
        QString trainStatus = translateStatus(train->getStatus());
        if (trainStatus == QStringLiteral(u"Tạm ngưng") || train->getStatus() == "INACTIVE")
        {
            trainProblem = true;
            trainWarning = QStringLiteral(u"⚠ Tàu tạm ngưng");
        }
        else if (trainStatus == QStringLiteral(u"Bảo trì") || train->getStatus() == "MAINTENANCE")
        {
            trainProblem = true;
            trainWarning = QStringLiteral(u"⚠ Tàu đang bảo trì");
        }
    }

    if (trainProblem)
    {
        QColor warnBg(255, 235, 235);   // nền đỏ nhạt
        QColor warnFg(180, 30, 30);     // chữ đỏ đậm
        for (int c = 0; c < t->columnCount(); ++c)
        {
            QTableWidgetItem* item = t->item(row, c);
            if (item)
                item->setBackground(warnBg);
        }
        QTableWidgetItem* statusItem = t->item(row, 8);
        if (statusItem)
        {
            statusItem->setText(statusItem->text() + " " + trainWarning);
            statusItem->setForeground(warnFg);
        }
        QTableWidgetItem* trainItem = t->item(row, 1);
        if (trainItem)
            trainItem->setForeground(warnFg);
    }
}

void MainWindow::refreshTrainTable()
{
    ui->trainTable->setRowCount(0);
    int total = system.getTrainCount();
    if (total == 0)
    {
        updateStats();
        return;
    }

    TrainBST bst;
    for (int i = 0; i < total; ++i)
    {
        Train* t = system.getTrainAt(i);
        if (!t)
            continue;
        string tid = t->getTrainId();
        int num = 0;
        int base = 0;
        if (tid.rfind("SE", 0) == 0)
        {
            base = 1000;
            for (char c : tid)
                if (isdigit(static_cast<unsigned char>(c)))
                    num = num * 10 + (c - '0');
        }
        else if (tid.rfind("HH", 0) == 0)
        {
            base = 2000;
            for (char c : tid)
                if (isdigit(static_cast<unsigned char>(c)))
                    num = num * 10 + (c - '0');
        }
        else
        {
            base = 3000;
            for (char c : tid)
                if (isdigit(static_cast<unsigned char>(c)))
                    num = num * 10 + (c - '0');
        }
        bst.insert(base + num, t);
    }

    Train** sortedTrains = new Train*[total];
    int count = bst.getAscending(sortedTrains, total);

    for (int i = 0; i < count; ++i)
    {
        Train* t = sortedTrains[i];
        if (!t)
            continue;

        int row = ui->trainTable->rowCount();
        ui->trainTable->insertRow(row);
        ui->trainTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(t->getTrainId())));
        ui->trainTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(t->getTrainName())));
        ui->trainTable->setItem(row, 2, new QTableWidgetItem(translateTrainType(t->getTrainType())));
        ui->trainTable->setItem(row, 3, new QTableWidgetItem(QString::number(t->getCapacity())));
        ui->trainTable->setItem(row, 4, new QTableWidgetItem(QString::number(t->getMaxSpeed())));

        QTableWidgetItem* status = new QTableWidgetItem(translateStatus(t->getStatus()));
        ui->trainTable->setItem(row, 5, status);
        ui->trainTable->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(t->getNote())));
    }
    delete[] sortedTrains;
    updateStats();
}

void MainWindow::refreshStationTable()
{
    ui->stationTable->setRowCount(0);
    for (int i = 0; i < system.getStationCount(); ++i)
    {
        Station* s = system.getStationAt(i);
        if (!s)
            continue;

        int row = ui->stationTable->rowCount();
        ui->stationTable->insertRow(row);
        ui->stationTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(s->getStationId())));
        ui->stationTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(s->getStationName())));
        ui->stationTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(s->getLocation())));
        ui->stationTable->setItem(row, 3, new QTableWidgetItem(QString::number(s->getNumberOfTracks())));
    }
    updateStats();
}

void MainWindow::refreshRouteTable()
{
    ui->routeTable->setRowCount(0);
    for (int i = 0; i < system.getRouteCount(); ++i)
    {
        Route* r = system.getRouteAt(i);
        if (!r)
            continue;

        int row = ui->routeTable->rowCount();
        ui->routeTable->insertRow(row);
        ui->routeTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(r->getRouteId())));
        ui->routeTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(r->getFromStationId())));
        ui->routeTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(r->getToStationId())));
        ui->routeTable->setItem(row, 3, new QTableWidgetItem(QString::number(r->getDistance())));
        ui->routeTable->setItem(row, 4, new QTableWidgetItem(QString::number(r->getTravelTime())));
        ui->routeTable->setItem(row, 5, new QTableWidgetItem(translateStatus(r->getStatus())));
    }
    updateStats();
}

void MainWindow::refreshScheduleTable()
{
    ui->scheduleTable->setRowCount(0);
    int total = system.getScheduleCount();
    if (total == 0)
    {
        updateStats();
        return;
    }

    ScheduleBST bst;
    for (int i = 0; i < total; ++i)
    {
        Schedule* s = system.getScheduleAt(i);
        if (!s)
            continue;
        string sid = s->getScheduleId();
        int num = 0;
        for (char c : sid)
            if (isdigit(static_cast<unsigned char>(c)))
                num = num * 10 + (c - '0');
        bst.insert(num, s);
    }

    Schedule** sortedSchedules = new Schedule*[total];
    int count = bst.getAscending(sortedSchedules, total);

    for (int i = 0; i < count; ++i)
    {
        fillScheduleRow(ui->scheduleTable, sortedSchedules[i]);
    }
    delete[] sortedSchedules;
    updateStats();
    refreshScheduleSelectors();
}

void MainWindow::updateStats()
{
    ui->statTrain->setText(QString("Tổng số tàu\n%1").arg(system.getTrainCount()));
    ui->statStation->setText(QString("Nhà ga\n%1").arg(system.getStationCount()));
    ui->statRoute->setText(QString("Tuyến đường\n%1").arg(system.getRouteCount()));
    ui->statSchedule->setText(QString("Lịch chạy\n%1").arg(system.getScheduleCount()));
}

QString MainWindow::selectedId(QTableWidget* table, int col) const
{
    int row = table->currentRow();
    if (row < 0 || !table->item(row, col))
        return "";
    return table->item(row, col)->text();
}

void MainWindow::onAddTrain()
{
    TrainDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted)
    {
        Train* t = dlg.getTrain();
        if (system.addTrain(t))
            refreshTrainTable();
        else
        {
            delete t;
            QMessageBox::warning(this, "Lỗi", "Thêm tàu thất bại!\nMã tàu đã tồn tại hoặc dữ liệu không hợp lệ.");
        }
    }
}
void MainWindow::onEditTrain()
{
    QString id = selectedId(ui->trainTable);
    if (id.isEmpty())
    {
        QMessageBox::information(this, "Thông báo", "Chọn tàu cần sửa.");
        return;
    }
    Train* t = system.findTrain(id.toStdString());
    if (!t)
        return;
    TrainDialog dlg(this, t);
    if (dlg.exec() == QDialog::Accepted)
    {
        TrainData d = dlg.getData();
        system.updateTrain(id.toStdString(), d.name, d.type, d.capacity, d.maxSpeed, d.status, d.note);
        refreshTrainTable();
    }
}
void MainWindow::onDeleteTrain()
{
    QString id = selectedId(ui->trainTable);
    if (id.isEmpty())
    {
        QMessageBox::information(this, "Thông báo", "Chọn tàu cần xóa.");
        return;
    }
    if (QMessageBox::question(this, "Xác nhận", QString("Xóa tàu [%1]?").arg(id)) == QMessageBox::Yes)
    {
        if (!system.removeTrain(id.toStdString()))
            QMessageBox::warning(this, "Lỗi", "Không thể xóa — tàu đang có lịch chạy.");
        else
            refreshTrainTable();
    }
}

void MainWindow::onAddStation()
{
    StationDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted)
    {
        Station* s = dlg.getStation();
        if (system.addStation(s))
            refreshStationTable();
        else
        {
            delete s;
            QMessageBox::warning(this, "Lỗi", "Mã ga đã tồn tại.");
        }
    }
}
void MainWindow::onEditStation()
{
    QString id = selectedId(ui->stationTable);
    if (id.isEmpty())
    {
        QMessageBox::information(this, "Thông báo", "Chọn ga cần sửa.");
        return;
    }
    Station* s = system.findStation(id.toStdString());
    if (!s)
        return;
    StationDialog dlg(this, s);
    if (dlg.exec() == QDialog::Accepted)
    {
        StationData d = dlg.getData();
        system.updateStation(id.toStdString(), d.name, d.location, d.tracks);
        refreshStationTable();
    }
}
void MainWindow::onDeleteStation()
{
    QString id = selectedId(ui->stationTable);
    if (id.isEmpty())
    {
        QMessageBox::information(this, "Thông báo", "Chọn ga cần xóa.");
        return;
    }
    if (QMessageBox::question(this, "Xác nhận", QString("Xóa ga [%1]?").arg(id)) == QMessageBox::Yes)
    {
        if (!system.removeStation(id.toStdString()))
            QMessageBox::warning(this, "Lỗi", "Không thể xóa — ga đang được sử dụng.");
        else
            refreshStationTable();
    }
}

void MainWindow::onAddRoute()
{
    RouteDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted)
    {
        Route* r = dlg.getRoute();
        if (system.addRoute(r))
            refreshRouteTable();
        else
        {
            delete r;
            QMessageBox::warning(this, "Lỗi",
                                 "Thêm tuyến thất bại!\nKiểm tra mã trùng, ga không tồn tại, hoặc 2 ga giống nhau.");
        }
    }
}
void MainWindow::onEditRoute()
{
    QString id = selectedId(ui->routeTable);
    if (id.isEmpty())
    {
        QMessageBox::information(this, "Thông báo", "Chọn tuyến cần sửa.");
        return;
    }
    Route* r = system.findRoute(id.toStdString());
    if (!r)
        return;
    RouteDialog dlg(this, r);
    if (dlg.exec() == QDialog::Accepted)
    {
        RouteData d = dlg.getData();
        system.updateRoute(id.toStdString(), d.distance, d.travelTime, d.status);
        refreshRouteTable();
    }
}
void MainWindow::onDeleteRoute()
{
    QString id = selectedId(ui->routeTable);
    if (id.isEmpty())
    {
        QMessageBox::information(this, "Thông báo", "Chọn tuyến cần xóa.");
        return;
    }
    if (QMessageBox::question(this, "Xác nhận", QString("Xóa tuyến [%1]?").arg(id)) == QMessageBox::Yes)
    {
        if (!system.removeRoute(id.toStdString()))
            QMessageBox::warning(this, "Lỗi", "Xóa tuyến thất bại.");
        else
            refreshRouteTable();
    }
}

void MainWindow::onAddSchedule()
{
    ScheduleDialog dlg(this, &system);
    if (dlg.exec() == QDialog::Accepted)
    {
        Schedule* s = dlg.getSchedule();
        if (system.addSchedule(s))
            refreshScheduleTable();
        else
        {
            delete s;
            QMessageBox::warning(
                this, "Lỗi",
                "Thêm lịch thất bại!\n• Mã lịch trùng\n• Tàu/ga không tồn tại\n• Giờ đến ≤ giờ đi\n• Ga đi = ga đến");
        }
    }
}

void MainWindow::onEditSchedule()
{
    QString id = selectedId(ui->scheduleTable);
    if (id.isEmpty())
    {
        QMessageBox::information(this, "Thông báo", "Chọn lịch cần sửa.");
        return;
    }

    Schedule* schedule = system.findSchedule(id.toStdString());
    if (!schedule)
        return;

    ScheduleDialog dlg(this, &system, schedule);
    if (dlg.exec() != QDialog::Accepted)
        return;

    Schedule* data = dlg.getSchedule();
    bool routeChanged = schedule->getDepartureStationId() != data->getDepartureStationId() ||
                        schedule->getDestinationStationId() != data->getDestinationStationId();

    if (routeChanged && schedule->getStopCount() > 0 &&
        QMessageBox::question(this, "Xác nhận", "Đổi ga đi hoặc ga đến sẽ xóa các điểm dừng cũ. Tiếp tục?") !=
            QMessageBox::Yes)
    {
        delete data;
        return;
    }

    if (system.updateSchedule(id.toStdString(), *data))
    {
        refreshScheduleTable();
        onViewStops();
    }
    else
        QMessageBox::warning(this, "Lỗi", "Sửa lịch thất bại. Hãy kiểm tra tàu, tuyến đường và thời gian.");

    delete data;
}

void MainWindow::onDeleteSchedule()
{
    QString id = selectedId(ui->scheduleTable);
    if (id.isEmpty())
    {
        QMessageBox::information(this, "Thông báo", "Chọn lịch cần xóa.");
        return;
    }
    if (QMessageBox::question(this, "Xác nhận", QString("Xóa lịch [%1]?").arg(id)) == QMessageBox::Yes)
    {
        if (!system.removeSchedule(id.toStdString()))
            QMessageBox::warning(this, "Lỗi", "Xóa lịch thất bại.");
        else
        {
            refreshScheduleTable();
            ui->stopTable->setRowCount(0);
        }
    }
}
void MainWindow::onViewStops()
{
    ui->stopTable->setRowCount(0);
    QString id = selectedId(ui->scheduleTable);
    if (id.isEmpty())
        return;
    Schedule* s = system.findSchedule(id.toStdString());
    if (!s)
        return;

    addJourneyRow("Ga đi", QString::fromStdString(s->getDepartureStationId()), "—",
                  QString::fromStdString(TimeUtils::minutesToDisplay(s->getDepartureTime())), 0);

    const StopList& stops = s->getStops();
    for (int i = 0; i < stops.getSize(); ++i)
    {
        const Stop* st = stops.get(i);
        if (!st)
            continue;
        if (st->getStationId() == s->getDepartureStationId() || st->getStationId() == s->getDestinationStationId())
            continue;

        addJourneyRow(QString::number(st->getOrder()), QString::fromStdString(st->getStationId()),
                      QString::fromStdString(TimeUtils::minutesToDisplay(st->getArrivalTime())),
                      QString::fromStdString(TimeUtils::minutesToDisplay(st->getDepartureTime())), st->getOrder());
    }

    addJourneyRow("Ga đến", QString::fromStdString(s->getDestinationStationId()),
                  QString::fromStdString(TimeUtils::minutesToDisplay(s->getArrivalTime())), "—", 0);
}

void MainWindow::addJourneyRow(const QString& orderText, const QString& stationId, const QString& arrival,
                               const QString& departure, int storedOrder)
{
    int row = ui->stopTable->rowCount();
    ui->stopTable->insertRow(row);

    QTableWidgetItem* orderItem = new QTableWidgetItem(orderText);
    if (storedOrder > 0)
        orderItem->setData(Qt::UserRole, storedOrder);

    ui->stopTable->setItem(row, 0, orderItem);
    ui->stopTable->setItem(row, 1, new QTableWidgetItem(stationId));
    ui->stopTable->setItem(row, 2, new QTableWidgetItem(arrival));
    ui->stopTable->setItem(row, 3, new QTableWidgetItem(departure));
}
void MainWindow::onAddStop()
{
    QString id = selectedId(ui->scheduleTable);
    if (id.isEmpty())
    {
        QMessageBox::information(this, "Thông báo", "Chọn lịch trước.");
        return;
    }
    Schedule* s = system.findSchedule(id.toStdString());
    if (!s)
        return;
    StopDialog dlg(this, &system, s);
    if (dlg.exec() == QDialog::Accepted)
    {
        Stop st = dlg.getStop();
        if (system.addStopToSchedule(id.toStdString(), st, true))
        {
            onViewStops();
            refreshScheduleTable();
        }
        else
            QMessageBox::warning(this, "Lỗi", "Kiểm tra mã ga, thứ tự, thời gian và lịch trình.");
    }
}

void MainWindow::onEditStop()
{
    QString id = selectedId(ui->scheduleTable);
    if (id.isEmpty())
    {
        QMessageBox::information(this, "Thông báo", "Chọn lịch trước.");
        return;
    }

    int row = ui->stopTable->currentRow();
    if (row < 0)
    {
        QMessageBox::information(this, "Thông báo", "Chọn điểm dừng cần sửa.");
        return;
    }

    QTableWidgetItem* orderItem = ui->stopTable->item(row, 0);
    if (!orderItem || !orderItem->data(Qt::UserRole).isValid())
    {
        QMessageBox::information(this, "Thông báo", "Chỉ có thể sửa điểm dừng trung gian.");
        return;
    }

    int oldOrder = orderItem->data(Qt::UserRole).toInt();
    Schedule* s = system.findSchedule(id.toStdString());
    if (!s)
        return;

    const Stop* selectedStop = nullptr;
    const StopList& stops = s->getStops();
    for (int i = 0; i < stops.getSize(); ++i)
    {
        const Stop* current = stops.get(i);
        if (current && current->getOrder() == oldOrder)
        {
            selectedStop = current;
            break;
        }
    }
    if (!selectedStop)
        return;

    StopDialog dlg(this, &system, s, selectedStop);
    if (dlg.exec() != QDialog::Accepted)
        return;

    Stop newStop = dlg.getStop();
    if (system.updateStopInSchedule(id.toStdString(), oldOrder, newStop))
    {
        onViewStops();
        refreshScheduleTable();
    }
    else
        QMessageBox::warning(this, "Lỗi", "Sửa điểm dừng thất bại.");
}

void MainWindow::onDeleteStop()
{
    QString id = selectedId(ui->scheduleTable);
    if (id.isEmpty())
    {
        QMessageBox::information(this, "Thông báo", "Chọn lịch trước.");
        return;
    }
    int row = ui->stopTable->currentRow();
    if (row < 0)
    {
        QMessageBox::information(this, "Thông báo", "Chọn điểm dừng cần xóa.");
        return;
    }
    QTableWidgetItem* orderItem = ui->stopTable->item(row, 0);
    if (!orderItem || !orderItem->data(Qt::UserRole).isValid())
    {
        QMessageBox::information(this, "Thông báo", "Ga đi và ga đến không thể xóa khỏi danh sách điểm dừng.");
        return;
    }
    int order = orderItem->data(Qt::UserRole).toInt();
    Schedule* s = system.findSchedule(id.toStdString());
    if (!s)
        return;
    if (QMessageBox::question(this, "Xác nhận", QString("Xóa điểm dừng thứ tự [%1]?").arg(order)) == QMessageBox::Yes)
    {
        if (system.removeStopFromSchedule(id.toStdString(), order, true))
        {
            onViewStops();
            refreshScheduleTable();
        }
        else
            QMessageBox::warning(this, "Lỗi", "Xóa điểm dừng thất bại.");
    }
}
void MainWindow::onSortByTime()
{
    ui->scheduleTable->setRowCount(0);
    ScheduleBST bst;
    for (int i = 0; i < system.getScheduleCount(); ++i)
    {
        Schedule* s = system.getScheduleAt(i);
        if (s)
            bst.insert(s->getDepartureTime(), s);
    }
    int capacity = system.getScheduleCount();
    Schedule** result = new Schedule*[capacity];
    int count = bst.getAscending(result, capacity);
    for (int i = 0; i < count; ++i)
    {
        fillScheduleRow(ui->scheduleTable, result[i]);
    }
    delete[] result;
}
void MainWindow::onSortByPriority()
{
    ui->scheduleTable->setRowCount(0);
    ScheduleBST bst;
    for (int i = 0; i < system.getScheduleCount(); ++i)
    {
        Schedule* s = system.getScheduleAt(i);
        if (s)
            bst.insert(s->getPriority(), s);
    }
    int capacity = system.getScheduleCount();
    Schedule** result = new Schedule*[capacity];
    int count = bst.getDescending(result, capacity);
    for (int i = 0; i < count; ++i)
    {
        fillScheduleRow(ui->scheduleTable, result[i]);
    }
    delete[] result;
}

void MainWindow::onCheckConflict()
{
    QComboBox* cbCA = findChild<QComboBox*>("cbConflictA");
    QComboBox* cbCB = findChild<QComboBox*>("cbConflictB");
    if (!cbCA || !cbCB)
        return;

    string idA = cbCA->currentData().toString().trimmed().toStdString();
    string idB = cbCB->currentData().toString().trimmed().toStdString();

    if (idA.empty() || idB.empty())
    {
        QMessageBox::warning(this, QStringLiteral(u"Lỗi"),
                             QStringLiteral(u"Vui lòng chọn cả 2 lịch trình. (Bấm nút Cập nhật nếu danh sách trống)"));
        return;
    }

    string reason;
    if (system.hasConflict(idA, idB, reason))
    {
        QString display;
        QString qReason = QString::fromStdString(reason);
        QStringList parts = qReason.split("|");

        QString type = parts.size() > 0 ? parts[0] : "";
        QString detail = parts.size() > 1 ? parts[1] : "";
        QString schedA = parts.size() > 2 ? parts[2] : "";
        QString tA = parts.size() > 3 ? parts[3] : "";
        QString schedB = parts.size() > 4 ? parts[4] : "";
        QString tB = parts.size() > 5 ? parts[5] : "";

        if (type == "SAME_TRAIN")
        {
            display = QStringLiteral(u"⚠ Xung đột: Cùng tàu %1\n"
                                      u"→ Thời gian chồng lấn!\n"
                                      u"  %2: %3\n"
                                      u"  %4: %5")
                          .arg(detail, schedA, tA, schedB, tB);
        }
        else if (type == "SAME_ROUTE")
        {
            display = QStringLiteral(u"⚠ Xung đột: Cùng tuyến %1\n"
                                      u"→ Thời gian chồng lấn!\n"
                                      u"  %2: %3\n"
                                      u"  %4: %5")
                          .arg(detail, schedA, tA, schedB, tB);
        }
        else if (type == "SEGMENT")
        {
            display = QStringLiteral(u"⚠ Xung đột: Cùng đoạn đường %1\n"
                                      u"→ Thời gian chồng lấn!\n"
                                      u"  %2: %3\n"
                                      u"  %4: %5")
                          .arg(detail, schedA, tA, schedB, tB);
        }
        else if (type == "STATION_STOP")
        {
            display = QStringLiteral(u"⚠ Xung đột: Trùng giờ dừng tại ga %1\n"
                                      u"→ Thời gian chồng lấn!\n"
                                      u"  %2: %3\n"
                                      u"  %4: %5")
                          .arg(detail, schedA, tA, schedB, tB);
        }
        else if (type == "STATION_OVERLOAD")
        {
            QString stationId = detail;
            QString maxTracks = parts.size() > 2 ? parts[2] : "";
            QString trainCount = parts.size() > 3 ? parts[3] : "";
            QString sA = parts.size() > 4 ? parts[4] : "";
            QString timeA = parts.size() > 5 ? parts[5] : "";
            QString sB = parts.size() > 6 ? parts[6] : "";
            QString timeB = parts.size() > 7 ? parts[7] : "";

            display = QStringLiteral(u"⚠ Xung đột quá tải ga: Ga %1 chỉ có %2 đường ray nhưng có %3 tàu đỗ cùng thời điểm!\n"
                                      u"→ Vượt quá sức chứa ga!\n"
                                      u"  %4: %5\n"
                                      u"  %6: %7")
                          .arg(stationId, maxTracks, trainCount, sA, timeA, sB, timeB);
        }
        else
        {
            display = QStringLiteral(u"⚠ Đã phát hiện xung đột.");
        }

        ui->conflictOutput->setText(display);
    }
    else
    {
        if (reason == "NOT_FOUND")
            ui->conflictOutput->setText(QStringLiteral(u"❌ Không tìm thấy lịch trình."));
        else if (reason == "SAME_ID")
            ui->conflictOutput->setText(QStringLiteral(u"❌ Hai mã lịch phải khác nhau."));
        else
            ui->conflictOutput->setText(QStringLiteral(u"✅ Không có xung đột giữa 2 lịch trình này."));
    }
}

void MainWindow::onDispatch()
{
    QComboBox* cbCA = findChild<QComboBox*>("cbConflictA");
    QComboBox* cbCB = findChild<QComboBox*>("cbConflictB");
    if (!cbCA || !cbCB)
        return;

    string idA = cbCA->currentData().toString().trimmed().toStdString();
    string idB = cbCB->currentData().toString().trimmed().toStdString();

    if (idA.empty() || idB.empty())
    {
        QMessageBox::warning(this, QStringLiteral(u"Lỗi"), QStringLiteral(u"Vui lòng chọn cả 2 lịch trình."));
        return;
    }

    string reason;
    if (!system.hasConflict(idA, idB, reason))
    {
        ui->conflictOutput->setText(QStringLiteral(u"Hai lịch không xung đột nên không cần điều phối."));
        return;
    }

    bool resolved = system.dispatch(idA, idB);
    if (resolved)
    {
        ui->conflictOutput->setText(
            QStringLiteral(u"✅ ĐIỀU PHỐI THÀNH CÔNG!\n"
                           u"Lịch trình có mức ưu tiên thấp hơn đã được lùi giờ hợp lý để tránh xung đột."));
    }
    else
    {
        ui->conflictOutput->setText(
            QStringLiteral(u"⚠ KHÔNG THỂ DỜI GIỜ TRONG NGÀY (vượt quá 24:00)!\n"
                           u"Tàu có mức ưu tiên thấp hơn đã được tự động đưa vào HÀNG ĐỢI ƯU TIÊN (MaxHeap).\n"
                           u"👉 Vui lòng mở tab 'Hàng chờ' để xem chi tiết và cấp phép xuất bến khi đường ray trống."));
    }
    refreshScheduleTable();
}

void MainWindow::onChangeStrategy()
{
    int type;
    if (ui->strategyCombo->currentIndex() == 0)
        type = 1;
    else
        type = 2;

    system.setSchedulingStrategy(type);
    if (type == 1)
        ui->conflictOutput->append("💡  Đã đổi sang Chiến lược Theo mức ưu tiên");
    else
        ui->conflictOutput->append("💡  Đã đổi sang Chiến lược Theo giờ xuất phát sớm");
}

void MainWindow::onShowQueue()
{
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    system.getDispatcher().showQueues();
    std::cout.rdbuf(old);
    ui->queueOutput->setPlainText(QString::fromUtf8(oss.str().c_str()));
}
void MainWindow::onAddToQueue()
{
    QStringList scheduleOptions;
    QList<Schedule*> scheduleList;

    for (int i = 0; i < system.getScheduleCount(); ++i)
    {
        Schedule* s = system.getScheduleAt(i);
        if (s)
        {
            scheduleList.append(s);
            QString depTime = QString::fromStdString(TimeUtils::minutesToDisplay(s->getDepartureTime()));
            QString arrTime = QString::fromStdString(TimeUtils::minutesToDisplay(s->getArrivalTime()));
            QString text = QString("[%1] Tàu %2: %3 -> %4 (%5 - %6 | Ưu tiên: %7)")
                               .arg(QString::fromStdString(s->getScheduleId()))
                               .arg(QString::fromStdString(s->getTrainId()))
                               .arg(QString::fromStdString(s->getDepartureStationId()))
                               .arg(QString::fromStdString(s->getDestinationStationId()))
                               .arg(depTime, arrTime)
                               .arg(s->getPriority());
            scheduleOptions.append(text);
        }
    }

    if (scheduleOptions.isEmpty())
    {
        QMessageBox::warning(this, "Thông báo", "Hệ thống chưa có lịch trình nào!");
        return;
    }

    scheduleOptions.append(QString::fromUtf8("➕ Nhập mã tàu thủ công khác..."));

    bool ok = false;
    QString chosenSchedule = QInputDialog::getItem(this, "Chọn lịch trình đưa vào hàng chờ",
                                                   "Chọn lịch trình cần hoãn / đưa vào hàng chờ:",
                                                   scheduleOptions, 0, false, &ok);
    if (!ok || chosenSchedule.isEmpty())
        return;

    QString label;
    int priority = 80;

    if (chosenSchedule.startsWith(QString::fromUtf8("➕")))
    {
        QString id = QInputDialog::getText(this, "Nhập thủ công", "Nhập mã tàu:", QLineEdit::Normal, "", &ok);
        if (!ok || id.trimmed().isEmpty())
            return;
        id = id.trimmed().toUpper();
        Train* t = system.findTrain(id.toStdString());
        if (!t)
        {
            QMessageBox::warning(this, "Lỗi", QString("Không tìm thấy tàu [%1] trong hệ thống.").arg(id));
            return;
        }
        label = id;
    }
    else
    {
        int selectedIndex = scheduleOptions.indexOf(chosenSchedule);
        if (selectedIndex >= 0 && selectedIndex < scheduleList.size())
        {
            Schedule* s = scheduleList[selectedIndex];
            priority = s->getPriority();
            label = QString("%1 (Lịch %2: %3 -> %4)")
                        .arg(QString::fromStdString(s->getTrainId()))
                        .arg(QString::fromStdString(s->getScheduleId()))
                        .arg(QString::fromStdString(s->getDepartureStationId()))
                        .arg(QString::fromStdString(s->getDestinationStationId()));
        }
    }

    if (label.isEmpty())
        return;

    QStringList options;
    options << QString("1. Hàng đợi ưu tiên (MaxHeap) - Mức ưu tiên: %1").arg(priority)
            << "2. Hàng chờ thông thường (Queue FIFO - Vào trước ra trước)";

    QString chosen = QInputDialog::getItem(this, "Chọn loại hàng chờ",
                                          QString("Đối tượng: %1\nChọn loại hàng chờ:").arg(label),
                                          options, 0, false, &ok);
    if (!ok || chosen.isEmpty())
        return;

    if (chosen.startsWith("1"))
    {
        int prio = QInputDialog::getInt(this, "Mức ưu tiên", "Xác nhận mức ưu tiên (1 - 100):", priority, 1, 100, 1, &ok);
        if (!ok)
            return;

        system.getDispatcher().addPriority(label.toStdString(), prio);
        ui->queueOutput->append(QString("⭐ Đã thêm [%1] vào Hàng đợi ưu tiên (Mức: %2).").arg(label).arg(prio));
    }
    else
    {
        system.getDispatcher().addWaiting(label.toStdString());
        ui->queueOutput->append(QString("📋 Đã thêm [%1] vào Hàng chờ thông thường (FIFO).").arg(label));
    }
    onShowQueue();
}

void MainWindow::onNextTrain()
{
    string next = system.getDispatcher().nextTrain();
    if (next.empty())
    {
        QMessageBox::information(this, "Thông báo", "Hàng chờ hiện đang trống, không có tàu nào cần cấp phép!");
        return;
    }

    QMessageBox::information(this, "Cấp phép xuất bến",
                             QString("🚀 ĐÃ CẤP PHÉP XUẤT BẾN!\n\n"
                                     "Tàu [%1] đã được rút khỏi hàng chờ và cấp lệnh xuất phát.\n"
                                     "(Đã lưu vết vào Lịch sử điều phối).").arg(QString::fromStdString(next)));
    onShowQueue();
}

void MainWindow::onClearQueue()
{
    if (QMessageBox::question(this, "Xác nhận", "Bạn có chắc chắn muốn xóa toàn bộ hàng chờ?") == QMessageBox::Yes)
    {
        system.getDispatcher().clearQueues();
        onShowQueue();
    }
}
void MainWindow::onShowHistory()
{
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    system.getDispatcher().showHistory();
    std::cout.rdbuf(old);
    ui->queueOutput->append(QString::fromStdString(oss.str()));
}

void MainWindow::onLoad()
{
    if (system.loadAllData())
    {
        refreshTrainTable();
        refreshStationTable();
        refreshRouteTable();
        refreshScheduleTable();
        refreshScheduleSelectors();
        QMessageBox::information(this, "Thành công", "✅  Đọc dữ liệu thành công!");
    }
    else
        QMessageBox::warning(this, "Lỗi", "Đọc dữ liệu thất bại!");
}
void MainWindow::onSave()
{
    if (system.saveAllData())
        QMessageBox::information(this, "Thành công", "✅  Lưu dữ liệu thành công!");
    else
        QMessageBox::warning(this, "Lỗi", "Lưu dữ liệu thất bại!");
}
