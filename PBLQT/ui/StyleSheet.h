#ifndef STYLESHEET_H
#define STYLESHEET_H
#include <QString>
inline QString appStyleSheet()
{
    return R"(
* {
    font-family: "Segoe UI";
    font-size: 13px;
    color: #1F3A2F;
}
QMainWindow, QWidget#centralwidget {
    background: #F6EFD8;
}
QMenuBar {
    background: #FEFAEE;
    border-bottom: 1px solid #E3DCC2;
    padding: 4px 8px;
}
QMenuBar::item {
    color: #1F3A2F;
    padding: 6px 12px;
    border-radius: 8px;
}
QMenuBar::item:selected {
    background: #DDE5D6;
}
QMenu {
    background: #FEFAEE;
    border: 1px solid #D8D0B4;
    padding: 6px;
}
QMenu::item {
    padding: 7px 28px 7px 12px;
    border-radius: 6px;
}
QMenu::item:selected {
    background: #DDE5D6;
    color: #1F3A2F;
}
QLabel#titleLabel {
    color: #1F3A2F;
    font-size: 24px;
    font-weight: 800;
    padding: 14px 8px 6px 8px;
}
QLabel#homeTitle {
    color: #1F3A2F;
    font-size: 28px;
    font-weight: 800;
}
QLabel#homeSubtitle {
    color: #6E7F6F;
    font-size: 16px;
    padding-top: 6px;
}
QFrame#homeInfoFrame {
    background: #E9EEDF;
    border: 2px dashed #5E7F66;
    border-radius: 16px;
    padding: 22px;
}
QLabel#homeWelcome {
    color: #B85C3C;
    font-size: 19px;
    font-weight: 800;
}
QLabel#homeDescription {
    color: #1F3A2F;
    font-size: 14px;
}
QLabel#homeHint {
    color: #6E7F6F;
    font-style: italic;
    padding-top: 8px;
}
QLabel#statTrain, QLabel#statStation, QLabel#statRoute, QLabel#statSchedule {
    border-radius: 18px;
    color: #1F3A2F;
    font-size: 15px;
    font-weight: 800;
    padding: 12px 20px;
    min-height: 42px;
}
QLabel#statTrain {
    background: #F8E6B8;
    border: 2px solid #E0A23A;
}
QLabel#statStation {
    background: #DDEFF2;
    border: 2px solid #8CCAD6;
}
QLabel#statRoute {
    background: #E3E8DA;
    border: 2px solid #8FA98F;
}
QLabel#statSchedule {
    background: #F3D9CF;
    border: 2px solid #C9785C;
}
QListWidget#navigationList {
    background: #FEFAEE;
    border: 1px solid #E3DCC2;
    border-radius: 18px;
    padding: 12px 10px;
    outline: none;
}
QListWidget#navigationList::item {
    color: #6B6A5C;
    border-radius: 12px;
    padding: 11px 14px;
    margin: 3px 0;
    font-weight: 700;
}
QListWidget#navigationList::item:hover {
    background: #EEF1E4;
    color: #1F3A2F;
}
QListWidget#navigationList::item:selected {
    background: #DDE5D6;
    color: #1F3A2F;
}
QStackedWidget#stackedWidget {
    background: #FEFAEE;
    border: 1px solid #E3DCC2;
    border-radius: 18px;
}
QStackedWidget#stackedWidget > QWidget {
    background: #FEFAEE;
}
QTableWidget {
    background: #FEFAEE;
    color: #1F3A2F;
    alternate-background-color: #F6F1DF;
    border: 1px solid #E3DCC2;
    border-radius: 12px;
    gridline-color: #EDE6CE;
    selection-background-color: #F8E6B8;
    selection-color: #1F3A2F;
    outline: none;
}
QTableWidget::item {
    color: #1F3A2F;
    padding: 7px 10px;
    border-bottom: 1px solid #EDE6CE;
}
QHeaderView::section {
    background: #234236;
    color: #F6EFD8;
    font-weight: 700;
    padding: 9px;
    border: none;
    border-right: 1px solid #36594B;
}
QTableCornerButton::section {
    background: #234236;
    border: none;
}
QPushButton {
    background: #D98E0B;
    color: #FFFFFF;
    border: none;
    border-radius: 10px;
    padding: 8px 17px;
    min-height: 20px;
    font-weight: 800;
}
QPushButton:hover {
    background: #BF7B05;
}
QPushButton:pressed {
    background: #A06503;
}
QPushButton#btnDeleteTrain, QPushButton#btnDeleteStation,
QPushButton#btnDeleteRoute, QPushButton#btnDeleteSchedule,
QPushButton#btnDeleteStop {
    background: #B85C3C;
    color: #FFFFFF;
}
QPushButton#btnDeleteTrain:hover, QPushButton#btnDeleteStation:hover,
QPushButton#btnDeleteRoute:hover, QPushButton#btnDeleteSchedule:hover,
QPushButton#btnDeleteStop:hover {
    background: #9C4A2D;
}
QPushButton#btnRefreshTrain, QPushButton#btnRefreshStation,
QPushButton#btnRefreshRoute, QPushButton#btnRefreshSchedule,
QPushButton#btnRefreshStations, QPushButton#btnRefreshSchedules,
QPushButton#btnSortTime, QPushButton#btnSortPriority,
QPushButton#btnViewStops, QPushButton#btnShowQueue,
QPushButton#btnShowHistory {
    background: #E3E8DA;
    color: #1F3A2F;
    border: 2px dashed #5E7F66;
}
QPushButton#btnRefreshTrain:hover, QPushButton#btnRefreshStation:hover,
QPushButton#btnRefreshRoute:hover, QPushButton#btnRefreshSchedule:hover,
QPushButton#btnRefreshStations:hover, QPushButton#btnRefreshSchedules:hover,
QPushButton#btnSortTime:hover, QPushButton#btnSortPriority:hover,
QPushButton#btnViewStops:hover, QPushButton#btnShowQueue:hover,
QPushButton#btnShowHistory:hover {
    background: #D2DCC6;
}
QLineEdit, QSpinBox, QDoubleSpinBox, QDateEdit, QTimeEdit, QComboBox {
    background: #FFFDF5;
    color: #1F3A2F;
    border: 2px solid #D8D0B4;
    border-radius: 10px;
    padding: 7px 10px;
    min-height: 22px;
}
QLineEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus,
QDateEdit:focus, QTimeEdit:focus, QComboBox:focus {
    border: 2px solid #D98E0B;
}
QComboBox::drop-down {
    border: none;
    width: 28px;
}
QComboBox QAbstractItemView {
    background: #FFFDF5;
    color: #1F3A2F;
    border: 1px solid #D8D0B4;
    selection-background-color: #DDE5D6;
    selection-color: #1F3A2F;
}
QTextEdit {
    background: #FFFDF5;
    color: #1F3A2F;
    border: 1px solid #E3DCC2;
    border-radius: 12px;
    padding: 9px;
}
QLabel#stopLabel {
    color: #B85C3C;
    font-size: 16px;
    font-weight: 800;
    padding-top: 5px;
}
QDialog, QMessageBox {
    background: #FEFAEE;
}
QDialog QLabel, QMessageBox QLabel {
    color: #1F3A2F;
}
QDialogButtonBox QPushButton {
    min-width: 90px;
}
QStatusBar {
    background: #234236;
    color: #F6EFD8;
}
QScrollBar:vertical {
    background: #F1EAD2;
    width: 10px;
    margin: 0;
}
QScrollBar::handle:vertical {
    background: #B9C7AE;
    border-radius: 5px;
    min-height: 30px;
}
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
    height: 0;
}
)";
}
#endif
