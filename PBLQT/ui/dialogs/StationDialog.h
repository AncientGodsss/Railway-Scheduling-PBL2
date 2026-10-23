#ifndef STATIONDIALOG_H
#define STATIONDIALOG_H
#include <QDialog>
#include "../../model/Station.h"
namespace Ui { class StationDialog; }
struct StationData { std::string name, location; int tracks; };
class StationDialog : public QDialog {
    Q_OBJECT
public:
    explicit StationDialog(QWidget* parent = nullptr);
    StationDialog(QWidget* parent, Station* existing);
    ~StationDialog();
    Station* getStation() const;
    StationData getData() const;
protected:
    void accept() override;
private:
    Ui::StationDialog* ui;
    bool editMode;
};
#endif
