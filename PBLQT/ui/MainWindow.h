#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "../system/RailwaySystem.h"
#include "../data_structure/BST.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QTableWidget;
class Schedule;
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private slots:
    void onAddTrain(); void onEditTrain(); void onDeleteTrain(); void refreshTrainTable();
    void onAddStation(); void onEditStation(); void onDeleteStation(); void refreshStationTable();
    void onAddRoute(); void onEditRoute(); void onDeleteRoute(); void refreshRouteTable();
    void onAddSchedule(); void onDeleteSchedule(); void onViewStops(); void onAddStop(); void onDeleteStop();
    void onSortByTime(); void onSortByPriority(); void refreshScheduleTable();
    void onFindPath(); void onCheckConflict(); void onDispatch(); void onChangeStrategy();
    void onShowQueue(); void onAddToQueue(); void onShowHistory(); void onLoad(); void onSave();
private:
    Ui::MainWindow* ui;
    RailwaySystem system;
    void updateStats();
    void refreshStationSelectors();
    void refreshScheduleSelectors();
    QString selectedId(QTableWidget* table, int col = 0) const;
    void fillScheduleRow(QTableWidget* table, Schedule* schedule);
};
#endif
