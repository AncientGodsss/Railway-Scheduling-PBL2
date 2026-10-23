#include "TrainDialog.h"
#include "ui_TrainDialog.h"
#include <QMessageBox>
TrainDialog::TrainDialog(QWidget* parent) : QDialog(parent), ui(new Ui::TrainDialog), editMode(false) {
    ui->setupUi(this); setWindowTitle("Thêm tàu mới");
}
TrainDialog::TrainDialog(QWidget* parent, Train* t) : QDialog(parent), ui(new Ui::TrainDialog), editMode(true) {
    ui->setupUi(this); setWindowTitle("Sửa thông tin tàu");
    ui->leId->setText(QString::fromStdString(t->getTrainId())); ui->leId->setReadOnly(true);
    ui->leName->setText(QString::fromStdString(t->getTrainName()));
    ui->cbType->setCurrentText(QString::fromStdString(t->getTrainType()));
    ui->sbCapacity->setValue(t->getCapacity()); ui->dsbSpeed->setValue(t->getMaxSpeed());
    ui->cbStatus->setCurrentText(QString::fromStdString(t->getStatus()));
}
TrainDialog::~TrainDialog() { delete ui; }
Train* TrainDialog::getTrain() const { return new Train(ui->leId->text().trimmed().toStdString(), ui->leName->text().trimmed().toStdString(), ui->cbType->currentText().toStdString(), ui->sbCapacity->value(), ui->dsbSpeed->value(), ui->cbStatus->currentText().toStdString()); }
TrainData TrainDialog::getData() const { return {ui->leName->text().trimmed().toStdString(), ui->cbType->currentText().toStdString(), ui->cbStatus->currentText().toStdString(), ui->sbCapacity->value(), ui->dsbSpeed->value()}; }
void TrainDialog::accept() {
    if (!editMode && ui->leId->text().trimmed().isEmpty()) { QMessageBox::warning(this,"Lỗi","Vui lòng nhập mã tàu."); return; }
    if (ui->leName->text().trimmed().isEmpty()) { QMessageBox::warning(this,"Lỗi","Vui lòng nhập tên tàu."); return; }
    QDialog::accept();
}
