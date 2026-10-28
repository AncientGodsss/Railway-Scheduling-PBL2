#include "StopDialog.h"
#include "ui_StopDialog.h"
#include "../../system/RailwaySystem.h"
#include <QMessageBox>

StopDialog::StopDialog(QWidget* parent, RailwaySystem* system, Schedule* schedule, const Stop* editingStop)
    : QDialog(parent), ui(new Ui::StopDialog), system(system), schedule(schedule), arrivalCalculated(false),
      editMode(editingStop != nullptr), originalOrder(0), stopDuration(15), calculatedArrivalTime(-1)
{
    ui->setupUi(this);
    if (editMode)
        setWindowTitle("Sửa điểm dừng");
    else
        setWindowTitle("Thêm điểm dừng");
    ui->teArrival->setReadOnly(true);
    ui->teArrival->setToolTip("Giờ đến được tự động tính từ ga liền trước");

    if (schedule)
    {
        ui->sbOrder->setMaximum(schedule->getStopCount() + 1);
        ui->sbOrder->setValue(schedule->getStopCount() + 1);
    }

    if (editingStop)
    {
        originalOrder = editingStop->getOrder();
        stopDuration = editingStop->getDepartureTime() - editingStop->getArrivalTime();
        ui->sbOrder->setValue(editingStop->getOrder());
        ui->sbOrder->setReadOnly(true);
        ui->leStation->setText(QString::fromStdString(editingStop->getStationId()));
    }

    connect(ui->leStation, &QLineEdit::textChanged, this, &StopDialog::markArrivalAsOutdated);
    connect(ui->leStation, &QLineEdit::editingFinished, this, &StopDialog::recalculateArrival);
    connect(ui->sbOrder, &QSpinBox::valueChanged, this, &StopDialog::recalculateArrival);

    if (editingStop)
        calculateArrival(false);
}

void StopDialog::markArrivalAsOutdated()
{
    arrivalCalculated = false;
}

void StopDialog::recalculateArrival()
{
    calculateArrival(false);
}

StopDialog::~StopDialog()
{
    delete ui;
}

bool StopDialog::calculateArrival(bool showError)
{
    arrivalCalculated = false;

    if (!system || !schedule)
        return false;

    string stationId = ui->leStation->text().trimmed().toUpper().toStdString();
    if (stationId.empty())
        return false;

    if (!system->findStation(stationId))
    {
        if (showError)
            QMessageBox::warning(this, "Lỗi", "Mã ga không tồn tại.");
        return false;
    }

    if (stationId == schedule->getDepartureStationId() || stationId == schedule->getDestinationStationId())
    {
        if (showError)
            QMessageBox::warning(this, "Lỗi", "Điểm dừng phải khác ga đi và ga đến của lịch.");
        return false;
    }

    int order = ui->sbOrder->value();
    string previousStationId = schedule->getDepartureStationId();
    int previousDepartureTime = schedule->getDepartureTime();

    const StopList& stops = schedule->getStops();
    for (int i = 0; i < stops.getSize(); ++i)
    {
        const Stop* s = stops.get(i);
        if (!s)
            continue;
        if (editMode && s->getOrder() == originalOrder)
            continue;
        if (s->getOrder() == order || s->getStationId() == stationId)
        {
            if (showError)
                QMessageBox::warning(this, "Lỗi", "Thứ tự dừng hoặc mã ga đã tồn tại trong lịch.");
            return false;
        }
        if (s->getOrder() < order)
        {
            previousStationId = s->getStationId();
            previousDepartureTime = s->getDepartureTime();
        }
    }

    PathResult path = system->shortestPath(previousStationId, stationId, false);
    if (!path.found)
    {
        if (showError)
            QMessageBox::warning(this, "Lỗi", "Không tìm thấy đường từ ga liền trước đến ga dừng này.");
        return false;
    }

    int arrivalTime = previousDepartureTime + path.travelTime;
    if (arrivalTime >= schedule->getArrivalTime())
    {
        if (showError)
            QMessageBox::warning(this, "Lỗi", "Không thể đến ga này trước giờ kết thúc của lịch.");
        return false;
    }

    calculatedArrivalTime = arrivalTime;
    ui->teArrival->setTime(QTime((arrivalTime / 60) % 24, arrivalTime % 60));
    ui->teArrival->setToolTip(QString::fromStdString(TimeUtils::minutesToDisplay(arrivalTime)));
    int departureTime = arrivalTime + stopDuration;
    ui->teDeparture->setTime(QTime((departureTime / 60) % 24, departureTime % 60));
    ui->teDeparture->setToolTip(QString::fromStdString(TimeUtils::minutesToDisplay(departureTime)));
    arrivalCalculated = true;
    return true;
}

void StopDialog::accept()
{
    if (!arrivalCalculated && !calculateArrival(true))
        return;

    int departureTime = selectedDepartureTime();
    if (departureTime < calculatedArrivalTime || departureTime > schedule->getArrivalTime())
    {
        QMessageBox::warning(this, "Lỗi", "Giờ tàu rời phải nằm sau giờ đến và trước giờ kết thúc lịch.");
        return;
    }

    QDialog::accept();
}

Stop StopDialog::getStop() const
{
    return Stop(ui->leStation->text().trimmed().toUpper().toStdString(), ui->sbOrder->value(), calculatedArrivalTime,
                selectedDepartureTime());
}

int StopDialog::selectedDepartureTime() const
{
    int departureTime = ui->teDeparture->time().hour() * 60 + ui->teDeparture->time().minute();
    while (departureTime < calculatedArrivalTime)
        departureTime += 24 * 60;
    return departureTime;
}
