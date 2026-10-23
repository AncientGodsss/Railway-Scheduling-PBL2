#ifndef TRAINDIALOG_H
#define TRAINDIALOG_H
#include <QDialog>
#include "../../model/Train.h"
namespace Ui { class TrainDialog; }
struct TrainData { std::string name, type, status; int capacity; double maxSpeed; };
class TrainDialog : public QDialog {
    Q_OBJECT
public:
    explicit TrainDialog(QWidget* parent = nullptr);
    TrainDialog(QWidget* parent, Train* existing);
    ~TrainDialog();
    Train* getTrain() const;
    TrainData getData() const;
protected:
    void accept() override;
private:
    Ui::TrainDialog* ui;
    bool editMode;
};
#endif
