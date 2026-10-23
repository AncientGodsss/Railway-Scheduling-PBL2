#ifndef SCHEDULEDIALOG_H
#define SCHEDULEDIALOG_H
#include <QDialog>
#include "../../model/Schedule.h"
#include "../../system/RailwaySystem.h"
namespace Ui { class ScheduleDialog; }
class ScheduleDialog : public QDialog {
    Q_OBJECT
public:
    explicit ScheduleDialog(QWidget* parent = nullptr, RailwaySystem* system = nullptr);
    ~ScheduleDialog();
    Schedule* getSchedule() const;
protected:
    void accept() override;
private slots:
    void autoCalcArrival();
private:
    Ui::ScheduleDialog* ui;
    RailwaySystem* sys;
};
#endif
