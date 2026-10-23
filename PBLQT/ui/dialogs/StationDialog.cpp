#include "StationDialog.h"
#include "ui_StationDialog.h"
#include <QMessageBox>
StationDialog::StationDialog(QWidget* p) : QDialog(p), ui(new Ui::StationDialog), editMode(false) { ui->setupUi(this); setWindowTitle("Thêm ga mới"); }
StationDialog::StationDialog(QWidget* p, Station* s) : QDialog(p), ui(new Ui::StationDialog), editMode(true) {
    ui->setupUi(this); setWindowTitle("Sửa thông tin ga");
    ui->leId->setText(QString::fromStdString(s->getStationId())); ui->leId->setReadOnly(true);
    ui->leName->setText(QString::fromStdString(s->getStationName())); ui->leLocation->setText(QString::fromStdString(s->getLocation())); ui->sbTracks->setValue(s->getNumberOfTracks());
}
StationDialog::~StationDialog() { delete ui; }
Station* StationDialog::getStation() const { return new Station(ui->leId->text().trimmed().toUpper().toStdString(), ui->leName->text().trimmed().toStdString(), ui->leLocation->text().trimmed().toStdString(), ui->sbTracks->value()); }
StationData StationDialog::getData() const { return {ui->leName->text().trimmed().toStdString(), ui->leLocation->text().trimmed().toStdString(), ui->sbTracks->value()}; }
void StationDialog::accept() {
    if (!editMode && ui->leId->text().trimmed().isEmpty()) { QMessageBox::warning(this,"Lỗi","Vui lòng nhập mã ga."); return; }
    if (ui->leName->text().trimmed().isEmpty()) { QMessageBox::warning(this,"Lỗi","Vui lòng nhập tên ga."); return; }
    QDialog::accept();
}
