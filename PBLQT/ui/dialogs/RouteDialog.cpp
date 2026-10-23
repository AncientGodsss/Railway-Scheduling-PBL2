#include "RouteDialog.h"
#include "ui_RouteDialog.h"
#include <QMessageBox>
RouteDialog::RouteDialog(QWidget* p) : QDialog(p), ui(new Ui::RouteDialog), editMode(false) { ui->setupUi(this); setWindowTitle("Thêm tuyến mới"); }
RouteDialog::RouteDialog(QWidget* p, Route* r) : QDialog(p), ui(new Ui::RouteDialog), editMode(true) {
    ui->setupUi(this); setWindowTitle("Sửa tuyến đường");
    ui->leId->setText(QString::fromStdString(r->getRouteId())); ui->leId->setReadOnly(true);
    ui->leFrom->setText(QString::fromStdString(r->getFromStationId())); ui->leFrom->setReadOnly(true);
    ui->leTo->setText(QString::fromStdString(r->getToStationId())); ui->leTo->setReadOnly(true);
    ui->dsbDist->setValue(r->getDistance()); ui->sbTime->setValue(r->getTravelTime()); ui->cbStatus->setCurrentText(QString::fromStdString(r->getStatus()));
}
RouteDialog::~RouteDialog() { delete ui; }
Route* RouteDialog::getRoute() const { return new Route(ui->leId->text().trimmed().toStdString(), ui->leFrom->text().trimmed().toUpper().toStdString(), ui->leTo->text().trimmed().toUpper().toStdString(), ui->dsbDist->value(), ui->sbTime->value(), ui->cbStatus->currentText().toStdString()); }
RouteData RouteDialog::getData() const { return {ui->dsbDist->value(), ui->sbTime->value(), ui->cbStatus->currentText().toStdString()}; }
void RouteDialog::accept() {
    if (!editMode && ui->leId->text().trimmed().isEmpty()) { QMessageBox::warning(this,"Lỗi","Vui lòng nhập mã tuyến."); return; }
    if (!editMode && (ui->leFrom->text().trimmed().isEmpty() || ui->leTo->text().trimmed().isEmpty())) { QMessageBox::warning(this,"Lỗi","Vui lòng nhập đủ mã ga đầu và ga cuối."); return; }
    QDialog::accept();
}
