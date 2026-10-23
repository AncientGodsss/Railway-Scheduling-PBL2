#ifndef STOPDIALOG_H
#define STOPDIALOG_H
#include <QDialog>
#include "../../model/Stop.h"
namespace Ui { class StopDialog; }
class StopDialog : public QDialog {
    Q_OBJECT
public:
    explicit StopDialog(QWidget* parent = nullptr);
    ~StopDialog();
    Stop getStop() const;
private:
    Ui::StopDialog* ui;
};
#endif
