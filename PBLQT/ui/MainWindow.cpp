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

static void setupTable(QTableWidget* table, const QStringList& headers) {
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

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    qApp->setStyleSheet(appStyleSheet());
    connect(ui->navigationList, &QListWidget::currentRowChanged,
            ui->stackedWidget, &QStackedWidget::setCurrentIndex);
    setupTable(ui->trainTable, {"Mã tàu","Tên tàu","Loại","Sức chứa","Tốc độ","Trạng thái"});
    setupTable(ui->stationTable, {"Mã ga","Tên ga","Vị trí","Số đường ray"});
    setupTable(ui->routeTable, {"Mã tuyến","Ga đầu","Ga cuối","Khoảng cách","Thời gian","Trạng thái"});
    setupTable(ui->scheduleTable, {"Mã lịch","Mã tàu","Ga đi","Ga đến","Ngày","Giờ đi","Giờ đến","Ưu tiên","Trạng thái"});
    setupTable(ui->stopTable, {"Thứ tự","Mã ga","Giờ đến","Giờ rời"});
    connect(ui->btnAddTrain,&QPushButton::clicked,this,&MainWindow::onAddTrain);
    connect(ui->btnEditTrain,&QPushButton::clicked,this,&MainWindow::onEditTrain);
    connect(ui->btnDeleteTrain,&QPushButton::clicked,this,&MainWindow::onDeleteTrain);
    connect(ui->btnRefreshTrain,&QPushButton::clicked,this,&MainWindow::refreshTrainTable);
    connect(ui->btnAddStation,&QPushButton::clicked,this,&MainWindow::onAddStation);
    connect(ui->btnEditStation,&QPushButton::clicked,this,&MainWindow::onEditStation);
    connect(ui->btnDeleteStation,&QPushButton::clicked,this,&MainWindow::onDeleteStation);
    connect(ui->btnRefreshStation,&QPushButton::clicked,this,&MainWindow::refreshStationTable);
    connect(ui->btnAddRoute,&QPushButton::clicked,this,&MainWindow::onAddRoute);
    connect(ui->btnEditRoute,&QPushButton::clicked,this,&MainWindow::onEditRoute);
    connect(ui->btnDeleteRoute,&QPushButton::clicked,this,&MainWindow::onDeleteRoute);
    connect(ui->btnRefreshRoute,&QPushButton::clicked,this,&MainWindow::refreshRouteTable);
    connect(ui->btnAddSchedule,&QPushButton::clicked,this,&MainWindow::onAddSchedule);
    connect(ui->btnDeleteSchedule,&QPushButton::clicked,this,&MainWindow::onDeleteSchedule);
    connect(ui->btnRefreshSchedule,&QPushButton::clicked,this,&MainWindow::refreshScheduleTable);
    connect(ui->btnViewStops,&QPushButton::clicked,this,&MainWindow::onViewStops);
    connect(ui->btnAddStop,&QPushButton::clicked,this,&MainWindow::onAddStop);
    connect(ui->btnDeleteStop,&QPushButton::clicked,this,&MainWindow::onDeleteStop);
    connect(ui->btnSortTime,&QPushButton::clicked,this,&MainWindow::onSortByTime);
    connect(ui->btnSortPriority,&QPushButton::clicked,this,&MainWindow::onSortByPriority);
    connect(ui->btnRefreshStations,&QPushButton::clicked,this,&MainWindow::refreshStationSelectors);
    connect(ui->btnFindPath,&QPushButton::clicked,this,&MainWindow::onFindPath);
    connect(ui->btnRefreshSchedules,&QPushButton::clicked,this,&MainWindow::refreshScheduleSelectors);
    connect(ui->btnCheckConflict,&QPushButton::clicked,this,&MainWindow::onCheckConflict);
    connect(ui->btnDispatch,&QPushButton::clicked,this,&MainWindow::onDispatch);
    connect(ui->strategyCombo,qOverload<int>(&QComboBox::currentIndexChanged),this,&MainWindow::onChangeStrategy);
    connect(ui->btnShowQueue,&QPushButton::clicked,this,&MainWindow::onShowQueue);
    connect(ui->btnAddQueue,&QPushButton::clicked,this,&MainWindow::onAddToQueue);
    connect(ui->btnShowHistory,&QPushButton::clicked,this,&MainWindow::onShowHistory);
    connect(ui->actionLoad,&QAction::triggered,this,&MainWindow::onLoad);
    connect(ui->actionSave,&QAction::triggered,this,&MainWindow::onSave);
    connect(ui->actionQuit,&QAction::triggered,this,&QWidget::close);
    system.loadAllData();
    refreshTrainTable(); refreshStationTable(); refreshRouteTable(); refreshScheduleTable();
    refreshStationSelectors(); refreshScheduleSelectors();
}
MainWindow::~MainWindow() { delete ui; }

void MainWindow::refreshStationSelectors() {
    ui->cbStart->clear(); ui->cbDest->clear();
    system.forEachStation([this](Station* station) {
        if (!station) return;
        QString id=QString::fromStdString(station->getStationId());
        QString text=id+" - "+QString::fromStdString(station->getStationName());
        ui->cbStart->addItem(text,id); ui->cbDest->addItem(text,id);
    });
}
void MainWindow::refreshScheduleSelectors() {
    QComboBox* boxes[]={ui->cbConflictA,ui->cbConflictB,ui->cbDispA,ui->cbDispB};
    for (QComboBox* box: boxes) box->clear();
    system.forEachSchedule([&boxes](Schedule* schedule) {
        if (!schedule) return;
        QString id=QString::fromStdString(schedule->getScheduleId());
        for (QComboBox* box: boxes) box->addItem(id,id);
    });
}

static QString translateStatus(const string& st) {
    if (st == "ACTIVE" || st == "Hoạt động") return QStringLiteral(u"Hoạt động");
    if (st == "INACTIVE" || st == "Tạm ngưng") return QStringLiteral(u"Tạm ngưng");
    if (st == "MAINTENANCE" || st == "Bảo trì") return QStringLiteral(u"Bảo trì");
    if (st == "SCHEDULED" || st == "Đã lên lịch") return QStringLiteral(u"Đã lên lịch");
    if (st == "RUNNING" || st == "Đang chạy") return QStringLiteral(u"Đang chạy");
    if (st == "COMPLETED" || st == "Hoàn thành") return QStringLiteral(u"Hoàn thành");
    if (st == "CANCELLED" || st == "Đã hủy") return QStringLiteral(u"Đã hủy");
    return QString::fromStdString(st);
}

static QString translateTrainType(const string& tt) {
    if (tt == "express" || tt == "Passenger" || tt == "Tàu khách") return QStringLiteral(u"Tàu khách");
    if (tt == "local") return QStringLiteral(u"Tàu khách (Địa phương)");
    if (tt == "freight" || tt == "Freight" || tt == "Tàu hàng") return QStringLiteral(u"Tàu chở hàng");
    return QString::fromStdString(tt);
}

static QString formatDayOfWeek(const string& dateStr) {
    QString qstr = QString::fromStdString(dateStr);
    QDate d = QDate::fromString(qstr, "dd/MM/yyyy");
    if (!d.isValid()) return qstr;
    QString dow;
    switch (d.dayOfWeek()) {
        case 1: dow = "T2"; break;
        case 2: dow = "T3"; break;
        case 3: dow = "T4"; break;
        case 4: dow = "T5"; break;
        case 5: dow = "T6"; break;
        case 6: dow = "T7"; break;
        case 7: dow = "CN"; break;
    }
    return dow + ", " + qstr;
}

void MainWindow::fillScheduleRow(QTableWidget* t, Schedule* s)
{
    if (!s) return;
    int row = t->rowCount();
    t->insertRow(row);
    t->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(s->getScheduleId())));
    t->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(s->getTrainId())));
    t->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(s->getDepartureStationId())));
    t->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(s->getDestinationStationId())));
    t->setItem(row, 4, new QTableWidgetItem(formatDayOfWeek(s->getDepartureDate())));
    t->setItem(row, 5, new QTableWidgetItem(
        QString::fromStdString(TimeUtils::minutesToTime(s->getDepartureTime()))));
    t->setItem(row, 6, new QTableWidgetItem(
        QString::fromStdString(TimeUtils::minutesToTime(s->getArrivalTime()))));
    t->setItem(row, 7, new QTableWidgetItem(QString::number(s->getPriority())));
    t->setItem(row, 8, new QTableWidgetItem(translateStatus(s->getStatus())));
}

void MainWindow::refreshTrainTable()
{
    ui->trainTable->setRowCount(0);
    system.forEachTrain([this](Train* t) {
        if (!t) return;
        int row = ui->trainTable->rowCount();
        ui->trainTable->insertRow(row);
        ui->trainTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(t->getTrainId())));
        ui->trainTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(t->getTrainName())));
        ui->trainTable->setItem(row, 2, new QTableWidgetItem(translateTrainType(t->getTrainType())));
        ui->trainTable->setItem(row, 3, new QTableWidgetItem(QString::number(t->getCapacity())));
        ui->trainTable->setItem(row, 4, new QTableWidgetItem(QString::number(t->getMaxSpeed())));

        QTableWidgetItem* status = new QTableWidgetItem(translateStatus(t->getStatus()));
        ui->trainTable->setItem(row, 5, status);
    });
    updateStats();
}

void MainWindow::refreshStationTable()
{
    ui->stationTable->setRowCount(0);
    system.forEachStation([this](Station* s) {
        if (!s) return;
        int row = ui->stationTable->rowCount();
        ui->stationTable->insertRow(row);
        ui->stationTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(s->getStationId())));
        ui->stationTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(s->getStationName())));
        ui->stationTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(s->getLocation())));
        ui->stationTable->setItem(row, 3, new QTableWidgetItem(QString::number(s->getNumberOfTracks())));
    });
    updateStats();
}

void MainWindow::refreshRouteTable()
{
    ui->routeTable->setRowCount(0);
    system.forEachRoute([this](Route* r) {
        if (!r) return;
        int row = ui->routeTable->rowCount();
        ui->routeTable->insertRow(row);
        ui->routeTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(r->getRouteId())));
        ui->routeTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(r->getFromStationId())));
        ui->routeTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(r->getToStationId())));
        ui->routeTable->setItem(row, 3, new QTableWidgetItem(QString::number(r->getDistance())));
        ui->routeTable->setItem(row, 4, new QTableWidgetItem(QString::number(r->getTravelTime())));
        ui->routeTable->setItem(row, 5, new QTableWidgetItem(translateStatus(r->getStatus())));
    });
    updateStats();
}

void MainWindow::refreshScheduleTable()
{
    ui->scheduleTable->setRowCount(0);
    system.forEachSchedule([this](Schedule* s) { fillScheduleRow(ui->scheduleTable, s); });
    updateStats();
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
    if (row < 0 || !table->item(row, col)) return "";
    return table->item(row, col)->text();
}

 
 
 

void MainWindow::onAddTrain()
{
    TrainDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        Train* t = dlg.getTrain();
        if (system.addTrain(t)) refreshTrainTable();
        else { delete t; QMessageBox::warning(this, "Lỗi", "Thêm tàu thất bại!\nMã tàu đã tồn tại hoặc dữ liệu không hợp lệ."); }
    }
}
void MainWindow::onEditTrain()
{
    QString id = selectedId(ui->trainTable);
    if (id.isEmpty()) { QMessageBox::information(this,"Thông báo","Chọn tàu cần sửa."); return; }
    Train* t = system.findTrain(id.toStdString());
    if (!t) return;
    TrainDialog dlg(this, t);
    if (dlg.exec() == QDialog::Accepted) {
        auto d = dlg.getData();
        system.updateTrain(id.toStdString(), d.name, d.type, d.capacity, d.maxSpeed, d.status);
        refreshTrainTable();
    }
}
void MainWindow::onDeleteTrain()
{
    QString id = selectedId(ui->trainTable);
    if (id.isEmpty()) { QMessageBox::information(this,"Thông báo","Chọn tàu cần xóa."); return; }
    if (QMessageBox::question(this,"Xác nhận",QString("Xóa tàu [%1]?").arg(id)) == QMessageBox::Yes) {
        if (!system.removeTrain(id.toStdString()))
            QMessageBox::warning(this,"Lỗi","Không thể xóa — tàu đang có lịch chạy.");
        else refreshTrainTable();
    }
}

 
 
 

void MainWindow::onAddStation()
{
    StationDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        Station* s = dlg.getStation();
        if (system.addStation(s)) refreshStationTable();
        else { delete s; QMessageBox::warning(this,"Lỗi","Mã ga đã tồn tại."); }
    }
}
void MainWindow::onEditStation()
{
    QString id = selectedId(ui->stationTable);
    if (id.isEmpty()) { QMessageBox::information(this,"Thông báo","Chọn ga cần sửa."); return; }
    Station* s = system.findStation(id.toStdString());
    if (!s) return;
    StationDialog dlg(this, s);
    if (dlg.exec() == QDialog::Accepted) {
        auto d = dlg.getData();
        system.updateStation(id.toStdString(), d.name, d.location, d.tracks);
        refreshStationTable();
    }
}
void MainWindow::onDeleteStation()
{
    QString id = selectedId(ui->stationTable);
    if (id.isEmpty()) { QMessageBox::information(this,"Thông báo","Chọn ga cần xóa."); return; }
    if (QMessageBox::question(this,"Xác nhận",QString("Xóa ga [%1]?").arg(id)) == QMessageBox::Yes) {
        if (!system.removeStation(id.toStdString()))
            QMessageBox::warning(this,"Lỗi","Không thể xóa — ga đang được sử dụng.");
        else refreshStationTable();
    }
}

 
 
 

void MainWindow::onAddRoute()
{
    RouteDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        Route* r = dlg.getRoute();
        if (system.addRoute(r)) refreshRouteTable();
        else { delete r; QMessageBox::warning(this,"Lỗi","Thêm tuyến thất bại!\nKiểm tra mã trùng, ga không tồn tại, hoặc 2 ga giống nhau."); }
    }
}
void MainWindow::onEditRoute()
{
    QString id = selectedId(ui->routeTable);
    if (id.isEmpty()) { QMessageBox::information(this,"Thông báo","Chọn tuyến cần sửa."); return; }
    Route* r = system.findRoute(id.toStdString());
    if (!r) return;
    RouteDialog dlg(this, r);
    if (dlg.exec() == QDialog::Accepted) {
        auto d = dlg.getData();
        system.updateRoute(id.toStdString(), d.distance, d.travelTime, d.status);
        refreshRouteTable();
    }
}
void MainWindow::onDeleteRoute()
{
    QString id = selectedId(ui->routeTable);
    if (id.isEmpty()) { QMessageBox::information(this,"Thông báo","Chọn tuyến cần xóa."); return; }
    if (QMessageBox::question(this,"Xác nhận",QString("Xóa tuyến [%1]?").arg(id)) == QMessageBox::Yes) {
        if (!system.removeRoute(id.toStdString()))
            QMessageBox::warning(this,"Lỗi","Xóa tuyến thất bại.");
        else refreshRouteTable();
    }
}

 
 
 

void MainWindow::onAddSchedule()
{
    ScheduleDialog dlg(this, &system);    
    if (dlg.exec() == QDialog::Accepted) {
        Schedule* s = dlg.getSchedule();
        if (system.addSchedule(s)) refreshScheduleTable();
        else { delete s; QMessageBox::warning(this,"Lỗi","Thêm lịch thất bại!\n• Mã lịch trùng\n• Tàu/ga không tồn tại\n• Giờ đến ≤ giờ đi\n• Ga đi = ga đến"); }
    }
}
void MainWindow::onDeleteSchedule()
{
    QString id = selectedId(ui->scheduleTable);
    if (id.isEmpty()) { QMessageBox::information(this,"Thông báo","Chọn lịch cần xóa."); return; }
    if (QMessageBox::question(this,"Xác nhận",QString("Xóa lịch [%1]?").arg(id)) == QMessageBox::Yes) {
        if (!system.removeSchedule(id.toStdString()))
            QMessageBox::warning(this,"Lỗi","Xóa lịch thất bại.");
        else { refreshScheduleTable(); ui->stopTable->setRowCount(0); }
    }
}
void MainWindow::onViewStops()
{
    ui->stopTable->setRowCount(0);
    QString id = selectedId(ui->scheduleTable);
    if (id.isEmpty()) return;
    Schedule* s = system.findSchedule(id.toStdString());
    if (!s) return;
    const auto& stops = s->getStops();
    for (int i = 0; i < stops.getSize(); ++i) {
        const Stop* st = stops.get(i);
        if (!st) continue;
        int row = ui->stopTable->rowCount();
        ui->stopTable->insertRow(row);
        ui->stopTable->setItem(row, 0, new QTableWidgetItem(QString::number(st->getOrder())));
        ui->stopTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(st->getStationId())));
        ui->stopTable->setItem(row, 2, new QTableWidgetItem(
            QString::fromStdString(TimeUtils::minutesToTime(st->getArrivalTime()))));
        ui->stopTable->setItem(row, 3, new QTableWidgetItem(
            QString::fromStdString(TimeUtils::minutesToTime(st->getDepartureTime()))));
    }
}
void MainWindow::onAddStop()
{
    QString id = selectedId(ui->scheduleTable);
    if (id.isEmpty()) { QMessageBox::information(this,"Thông báo","Chọn lịch trước."); return; }
    Schedule* s = system.findSchedule(id.toStdString());
    if (!s) return;
    StopDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        Stop st = dlg.getStop();
        if (system.addStopToSchedule(id.toStdString(), st)) onViewStops();
        else QMessageBox::warning(this,"Lỗi","Kiểm tra mã ga, thứ tự, thời gian và lịch trình.");
    }
}
void MainWindow::onDeleteStop()
{
    QString id = selectedId(ui->scheduleTable);
    if (id.isEmpty()) { QMessageBox::information(this,"Thông báo","Chọn lịch trước."); return; }
    int row = ui->stopTable->currentRow();
    if (row < 0) { QMessageBox::information(this,"Thông báo","Chọn điểm dừng cần xóa."); return; }
    int order = ui->stopTable->item(row, 0)->text().toInt();
    Schedule* s = system.findSchedule(id.toStdString());
    if (!s) return;
    if (QMessageBox::question(this,"Xác nhận",QString("Xóa điểm dừng thứ tự [%1]?").arg(order)) == QMessageBox::Yes)
        { s->removeStopByOrder(order); onViewStops(); }
}
void MainWindow::onSortByTime()
{
    ui->scheduleTable->setRowCount(0);
    ScheduleBST bst;
    system.forEachSchedule([&bst](Schedule* s) { if (s) bst.insert(s->getDepartureTime(), s); });
    int capacity = system.getScheduleCount();
    Schedule** result = new Schedule*[capacity];
    int count = bst.getAscending(result, capacity);
    for (int i = 0; i < count; ++i) {
        fillScheduleRow(ui->scheduleTable, result[i]);
    }
    delete[] result;
}
void MainWindow::onSortByPriority()
{
    ui->scheduleTable->setRowCount(0);
    ScheduleBST bst;
    system.forEachSchedule([&bst](Schedule* s) { if (s) bst.insert(s->getPriority(), s); });
    int capacity = system.getScheduleCount();
    Schedule** result = new Schedule*[capacity];
    int count = bst.getDescending(result, capacity);
    for (int i = 0; i < count; ++i) {
        fillScheduleRow(ui->scheduleTable, result[i]);
    }
    delete[] result;
}

 
 
 

void MainWindow::onFindPath()
{
    QComboBox* cbStart = findChild<QComboBox*>("cbStart");
    QComboBox* cbDest  = findChild<QComboBox*>("cbDest");
    QComboBox* algo    = findChild<QComboBox*>("algoCombo");
    if (!cbStart || !cbDest || !algo) return;

    string start = cbStart->currentData().toString().trimmed().toUpper().toStdString();
    string dest  = cbDest->currentData().toString().trimmed().toUpper().toStdString();
    int    choice = algo->currentIndex();
    if (start.empty()) { QMessageBox::warning(this, QStringLiteral(u"Lỗi"), QStringLiteral(u"Vui lòng chọn ga bắt đầu. (Bấm Cập nhật ga nếu danh sách trống)")); return; }

    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());

    if (choice == 0)      { system.bfs(start); }
    else if (choice == 1) { system.dfs(start); }
    else {
        if (dest.empty()) { std::cout.rdbuf(old); QMessageBox::warning(this, QStringLiteral(u"Lỗi"), QStringLiteral(u"Vui lòng chọn ga đích để tìm đường ngắn/nhanh nhất.")); return; }
        PathResult r = system.shortestPath(start, dest, choice == 2);
        if (!r.found) {
            oss << "❌  Không tìm thấy đường từ [" << start << "] đến [" << dest << "].";
        } else {
            oss << "✅  Đường đi: ";
            for (int i = 0; i < r.path.getSize(); ++i) {
                const string* x = r.path.get(i);
                if (x) { oss << *x; if (i < r.path.getSize()-1) oss << " → "; }
            }
            oss << "\n📏  Khoảng cách: " << r.distance << " km\n";
            oss << "⏱  Thời gian   : " << r.travelTime << " phút\n";
        }
    }

    std::cout.rdbuf(old);
    ui->pathOutput->setText(QString::fromUtf8(oss.str().c_str()));
}

 
 
 

void MainWindow::onCheckConflict()
{
    QComboBox* cbCA = findChild<QComboBox*>("cbConflictA");
    QComboBox* cbCB = findChild<QComboBox*>("cbConflictB");
    if (!cbCA || !cbCB) return;

    string idA = cbCA->currentData().toString().trimmed().toStdString();
    string idB = cbCB->currentData().toString().trimmed().toStdString();

    if (idA.empty() || idB.empty()) {
        QMessageBox::warning(this, QStringLiteral(u"Lỗi"), QStringLiteral(u"Vui lòng chọn cả 2 lịch trình. (Bấm nút Cập nhật nếu danh sách trống)"));
        return;
    }

    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    
    string reason;
    if (system.hasConflict(idA, idB, reason)) {
        oss << "⚠️ Đã phát hiện xung đột: " << reason;
    } else {
        oss << "✅ Không có xung đột giữa 2 lịch trình này.";
    }
    
    std::cout.rdbuf(old);
    ui->conflictOutput->setText(QString::fromUtf8(oss.str().c_str()));
}

void MainWindow::onDispatch()
{
    QComboBox* cbDA = findChild<QComboBox*>("cbDispA");
    QComboBox* cbDB = findChild<QComboBox*>("cbDispB");
    if (!cbDA || !cbDB) return;

    string idA = cbDA->currentData().toString().trimmed().toStdString();
    string idB = cbDB->currentData().toString().trimmed().toStdString();

    if (idA.empty() || idB.empty()) {
        QMessageBox::warning(this, QStringLiteral(u"Lỗi"), QStringLiteral(u"Vui lòng chọn cả 2 lịch trình."));
        return;
    }

    string reason;
    if (!system.hasConflict(idA, idB, reason)) {
        ui->conflictOutput->setText(QStringLiteral(u"Hai lịch không xung đột nên không cần điều phối."));
        return;
    }

    bool resolved = system.dispatch(idA, idB);
    if (resolved) {
        ui->conflictOutput->setText(
            QStringLiteral(u"Điều phối thành công. Một lịch đã được đổi giờ để tránh xung đột."));
    } else {
        ui->conflictOutput->setText(
            QStringLiteral(u"Không thể đổi giờ trong ngày. Tàu có mức ưu tiên thấp hơn đã được đưa vào hàng chờ."));
    }
    refreshScheduleTable();
}

void MainWindow::onChangeStrategy()
{
    int type = (ui->strategyCombo->currentIndex() == 0) ? 1 : 2;
    system.setSchedulingStrategy(type);
    ui->conflictOutput->append(type == 1
        ? "💡  Đã đổi sang Chiến lược Theo mức ưu tiên"
        : "💡  Đã đổi sang Chiến lược Theo giờ xuất phát sớm");
}

 
 
 

void MainWindow::onShowQueue()
{
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    system.getDispatcher().showQueues();
    std::cout.rdbuf(old);
    ui->queueOutput->append(QString::fromStdString(oss.str()));
}
void MainWindow::onAddToQueue()
{
    bool ok;
    QString id = QInputDialog::getText(this,"Thêm vào hàng chờ","Mã tàu:",QLineEdit::Normal,"",&ok);
    if (!ok || id.trimmed().isEmpty()) return;
    if (system.findTrain(id.trimmed().toStdString())) {
        system.getDispatcher().addWaiting(id.trimmed().toStdString());
        ui->queueOutput->append(QString("✅  Đã thêm tàu [%1] vào hàng chờ.").arg(id));
    } else {
        QMessageBox::warning(this,"Lỗi",QString("Không tìm thấy tàu [%1].").arg(id));
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
    if (system.loadAllData()) {
        refreshTrainTable(); refreshStationTable();
        refreshRouteTable(); refreshScheduleTable();
        refreshStationSelectors(); refreshScheduleSelectors();
        QMessageBox::information(this,"Thành công","✅  Đọc dữ liệu thành công!");
    } else QMessageBox::warning(this,"Lỗi","Đọc dữ liệu thất bại!");
}
void MainWindow::onSave()
{
    if (system.saveAllData())
        QMessageBox::information(this,"Thành công","✅  Lưu dữ liệu thành công!");
    else
        QMessageBox::warning(this,"Lỗi","Lưu dữ liệu thất bại!");
}


