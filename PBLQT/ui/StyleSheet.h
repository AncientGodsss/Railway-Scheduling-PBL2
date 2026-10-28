#ifndef STYLESHEET_H
#define STYLESHEET_H
#include <QString>
inline QString appStyleSheet()
{
    return R"(
* {
    font-family: "Segoe UI";
    font-size: 13px;
    color: #172033;
}
QMainWindow, QWidget#centralwidget {
    background: #F4F7FB;
}
QWidget#centralwidget {
    border: none;
}
QMenuBar {
    background: #FFFFFF;
    border-bottom: 1px solid #DDE5F0;
    padding: 4px 8px;
}
QMenuBar::item {
    padding: 6px 12px;
    border-radius: 6px;
}
QMenuBar::item:selected {
    background: #E8F0FF;
    color: #1957C2;
}
QMenu {
    background: #FFFFFF;
    border: 1px solid #DDE5F0;
    padding: 6px;
}
QMenu::item {
    padding: 7px 28px 7px 12px;
    border-radius: 5px;
}
QMenu::item:selected {
    background: #E8F0FF;
    color: #1957C2;
}
QLabel#titleLabel {
    color: #173B78;
    font-size: 23px;
    font-weight: 700;
    padding: 16px 8px 8px 8px;
}
QLabel#homeTitle {
    color: #173B78;
    font-size: 28px;
    font-weight: 700;
}
QLabel#homeSubtitle {
    color: #64748B;
    font-size: 16px;
    padding-top: 6px;
}
QFrame#homeInfoFrame {
    background: #F8FAFD;
    border: 1px solid #D7E1EE;
    border-radius: 14px;
    padding: 22px;
}
QLabel#homeWelcome {
    color: #1957C2;
    font-size: 18px;
    font-weight: 700;
}
QLabel#homeDescription {
    color: #334155;
    font-size: 14px;
}
QLabel#homeHint {
    color: #64748B;
    font-style: italic;
    padding-top: 8px;
}
QLabel#statTrain, QLabel#statStation, QLabel#statRoute, QLabel#statSchedule {
    background: #FFFFFF;
    border: 1px solid #DDE5F0;
    border-radius: 12px;
    color: #173B78;
    font-size: 15px;
    font-weight: 600;
    padding: 13px 18px;
    min-height: 42px;
}
QLabel#statTrain {
    border-left: 5px solid #246BFD;
}
QLabel#statStation {
    border-left: 5px solid #18A76F;
}
QLabel#statRoute {
    border-left: 5px solid #F59E0B;
}
QLabel#statSchedule {
    border-left: 5px solid #8B5CF6;
}
QTabWidget::pane {
    background: #FFFFFF;
    border: 1px solid #DDE5F0;
    border-radius: 12px;
    top: -1px;
}
QTabBar::tab {
    background: transparent;
    color: #64748B;
    border: none;
    padding: 11px 17px;
    margin-right: 3px;
    font-weight: 600;
}
QTabBar::tab:hover {
    color: #246BFD;
    background: #EDF4FF;
    border-radius: 8px 8px 0 0;
}
QTabBar::tab:selected {
    color: #1957C2;
    background: #FFFFFF;
    border-bottom: 3px solid #246BFD;
}
QListWidget#navigationList {
    background: #EAF2FF;
    border: 1px solid #CADAF2;
    border-radius: 7px;
    padding: 8px 5px;
    outline: none;
}
QListWidget#navigationList::item {
    color: #334155;
    border-radius: 5px;
    padding: 11px 10px;
    margin: 2px 1px;
    font-weight: 600;
}
QListWidget#navigationList::item:hover {
    background: #DDEAFF;
}
QListWidget#navigationList::item:selected {
    background: #FFFFFF;
    color: #1456A0;
    border-left: 3px solid #1677D2;
}
QStackedWidget#stackedWidget {
    background: #FFFFFF;
    border: 1px solid #D7E1EE;
    border-radius: 7px;
}
QStackedWidget#stackedWidget > QWidget {
    background: #FFFFFF;
}
QTableWidget {
    background: #FFFFFF;
    alternate-background-color: #F8FAFD;
    border: 1px solid #E2E8F0;
    border-radius: 9px;
    gridline-color: #E8EDF5;
    selection-background-color: #DCE9FF;
    selection-color: #173B78;
    outline: none;
}
QTableWidget::item {
    padding: 7px 10px;
    border-bottom: 1px solid #EDF1F6;
}
QHeaderView::section {
    background: #EEF3FA;
    color: #334155;
    font-weight: 700;
    padding: 9px;
    border: none;
    border-right: 1px solid #DDE5F0;
    border-bottom: 1px solid #D5DEEA;
}
QTableCornerButton::section {
    background: #EEF3FA;
    border: none;
}
QPushButton {
    background: #246BFD;
    color: #FFFFFF;
    border: none;
    border-radius: 8px;
    padding: 8px 17px;
    min-height: 20px;
    font-weight: 600;
}
QPushButton:hover {
    background: #1957D2;
}
QPushButton:pressed {
    background: #1245AA;
}
QPushButton#btnDeleteTrain, QPushButton#btnDeleteStation,
QPushButton#btnDeleteRoute, QPushButton#btnDeleteSchedule,
QPushButton#btnDeleteStop {
    background: #E5484D;
}
QPushButton#btnDeleteTrain:hover, QPushButton#btnDeleteStation:hover,
QPushButton#btnDeleteRoute:hover, QPushButton#btnDeleteSchedule:hover,
QPushButton#btnDeleteStop:hover {
    background: #C9363C;
}
QPushButton#btnRefreshTrain, QPushButton#btnRefreshStation,
QPushButton#btnRefreshRoute, QPushButton#btnRefreshSchedule,
QPushButton#btnRefreshStations, QPushButton#btnRefreshSchedules,
QPushButton#btnSortTime, QPushButton#btnSortPriority,
QPushButton#btnViewStops, QPushButton#btnShowQueue,
QPushButton#btnShowHistory {
    background: #E8EEF7;
    color: #334155;
}
QPushButton#btnRefreshTrain:hover, QPushButton#btnRefreshStation:hover,
QPushButton#btnRefreshRoute:hover, QPushButton#btnRefreshSchedule:hover,
QPushButton#btnRefreshStations:hover, QPushButton#btnRefreshSchedules:hover,
QPushButton#btnSortTime:hover, QPushButton#btnSortPriority:hover,
QPushButton#btnViewStops:hover, QPushButton#btnShowQueue:hover,
QPushButton#btnShowHistory:hover {
    background: #D9E3F1;
}
QLineEdit, QSpinBox, QDoubleSpinBox, QDateEdit, QTimeEdit, QComboBox {
    background: #FFFFFF;
    color: #172033;
    border: 1px solid #CBD5E1;
    border-radius: 8px;
    padding: 7px 10px;
    min-height: 22px;
}
QLineEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus,
QDateEdit:focus, QTimeEdit:focus, QComboBox:focus {
    border: 2px solid #5B8CFF;
}
QComboBox::drop-down {
    border: none;
    width: 28px;
}
QComboBox QAbstractItemView {
    background: #FFFFFF;
    color: #172033;
    border: 1px solid #CBD5E1;
    selection-background-color: #DCE9FF;
    selection-color: #173B78;
}
QTextEdit {
    background: #F8FAFD;
    color: #172033;
    border: 1px solid #DDE5F0;
    border-radius: 9px;
    padding: 9px;
}
QLabel#stopLabel {
    color: #173B78;
    font-size: 15px;
    font-weight: 700;
    padding-top: 5px;
}
QDialog {
    background: #F7F9FC;
}
QDialog QLabel {
    color: #334155;
}
QDialogButtonBox QPushButton {
    min-width: 90px;
}
QStatusBar {
    background: #173B78;
    color: #FFFFFF;
}
QScrollBar:vertical {
    background: #EEF2F7;
    width: 10px;
    margin: 0;
}
QScrollBar::handle:vertical {
    background: #B7C3D4;
    border-radius: 5px;
    min-height: 30px;
}
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
    height: 0;
}
)";
}
#endif
