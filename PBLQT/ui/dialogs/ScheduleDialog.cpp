#include "ScheduleDialog.h"
#include "ui_ScheduleDialog.h"
#include <QMessageBox>
ScheduleDialog::ScheduleDialog(QWidget* parent, RailwaySystem* system) : QDialog(parent), ui(new Ui::ScheduleDialog), sys(system) {
    ui->setupUi(this); setWindowTitle("Thêm lịch chạy mới");
    ui->deDate->setDate(QDate::currentDate()); ui->teDep->setTime(QTime(8,0)); ui->teArr->setTime(QTime(16,0));
    ui->teArr->setReadOnly(sys != nullptr); ui->btnCalc->setVisible(sys != nullptr);
    if (sys) {
        connect(ui->btnCalc,&QPushButton::clicked,this,&ScheduleDialog::autoCalcArrival);
        connect(ui->leFrom,&QLineEdit::editingFinished,this,&ScheduleDialog::autoCalcArrival);
        connect(ui->leTo,&QLineEdit::editingFinished,this,&ScheduleDialog::autoCalcArrival);
        connect(ui->teDep,&QTimeEdit::timeChanged,this,&ScheduleDialog::autoCalcArrival);
    }
}
ScheduleDialog::~ScheduleDialog() { delete ui; }
void ScheduleDialog::autoCalcArrival() {
    if (!sys) return;
    QString from=ui->leFrom->text().trimmed().toUpper(), to=ui->leTo->text().trimmed().toUpper();
    if (from.isEmpty() || to.isEmpty()) return;
    PathResult result=sys->shortestPath(from.toStdString(),to.toStdString(),false);
    if (!result.found) { ui->lblCalcResult->setText("Không tìm thấy đường đi. Hãy kiểm tra mã ga."); ui->teArr->setReadOnly(false); return; }
    int dep=ui->teDep->time().hour()*60+ui->teDep->time().minute();
    int arr=(dep+result.travelTime)%1440; ui->teArr->setTime(QTime(arr/60,arr%60)); ui->teArr->setReadOnly(true);
    QString path;
    for (int i=0;i<result.path.getSize();++i) { const std::string* node=result.path.get(i); if (node) { if (!path.isEmpty()) path+=" -> "; path+=QString::fromStdString(*node); } }
    ui->lblCalcResult->setText(QString("%1\nThời gian: %2 phút, khoảng cách: %3 km").arg(path).arg(result.travelTime).arg(result.distance));
}
Schedule* ScheduleDialog::getSchedule() const {
    int dep=ui->teDep->time().hour()*60+ui->teDep->time().minute();
    int arr=ui->teArr->time().hour()*60+ui->teArr->time().minute();
    std::string start=ui->leFrom->text().trimmed().toUpper().toStdString(), dest=ui->leTo->text().trimmed().toUpper().toStdString();
    if (sys && ui->teArr->isReadOnly()) { PathResult r=sys->shortestPath(start,dest,false); if (r.found) arr=dep+r.travelTime; }
    return new Schedule(ui->leId->text().trimmed().toUpper().toStdString(),ui->leTrainId->text().trimmed().toUpper().toStdString(),start,dest,dep,arr,ui->sbPriority->value(),ui->cbStatus->currentText().toStdString(),ui->deDate->date().toString("dd/MM/yyyy").toStdString());
}
void ScheduleDialog::accept() {
    if (ui->leId->text().trimmed().isEmpty()) { QMessageBox::warning(this,"Lỗi","Vui lòng nhập mã lịch."); return; }
    if (ui->leTrainId->text().trimmed().isEmpty() || ui->leFrom->text().trimmed().isEmpty() || ui->leTo->text().trimmed().isEmpty()) { QMessageBox::warning(this,"Lỗi","Vui lòng nhập đầy đủ mã tàu, ga đi và ga đến."); return; }
    QDialog::accept();
}
