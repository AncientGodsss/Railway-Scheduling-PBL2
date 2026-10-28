#ifndef STOPDIALOG_H
#define STOPDIALOG_H
#include <QDialog>
#include "../../model/Stop.h"

class RailwaySystem;
class Schedule;

namespace Ui
{
class StopDialog;
}

class StopDialog : public QDialog
{
    Q_OBJECT
public:
    explicit StopDialog(QWidget* parent, RailwaySystem* system, Schedule* schedule, const Stop* editingStop = nullptr);
    ~StopDialog();
    Stop getStop() const;

protected:
    void accept() override;

private slots:
    void markArrivalAsOutdated();
    void recalculateArrival();

private:
    Ui::StopDialog* ui;
    RailwaySystem* system;
    Schedule* schedule;
    bool arrivalCalculated;
    bool editMode;
    int originalOrder;
    int stopDuration;
    int calculatedArrivalTime;

    bool calculateArrival(bool showError);
    int selectedDepartureTime() const;
};
#endif
