#include "StopDialog.h"
#include "ui_StopDialog.h"
StopDialog::StopDialog(QWidget* parent) : QDialog(parent), ui(new Ui::StopDialog) {
    ui->setupUi(this); setWindowTitle("Thêm điểm dừng");
    ui->teArrival->setTime(QTime(9,0)); ui->teDeparture->setTime(QTime(9,15));
}
StopDialog::~StopDialog() { delete ui; }
Stop StopDialog::getStop() const {
    int arr=ui->teArrival->time().hour()*60+ui->teArrival->time().minute();
    int dep=ui->teDeparture->time().hour()*60+ui->teDeparture->time().minute();
    return Stop(ui->leStation->text().trimmed().toUpper().toStdString(),ui->sbOrder->value(),arr,dep);
}
