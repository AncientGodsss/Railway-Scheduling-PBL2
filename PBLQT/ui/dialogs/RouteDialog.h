#ifndef ROUTEDIALOG_H
#define ROUTEDIALOG_H
#include <QDialog>
#include "../../model/Route.h"
namespace Ui
{
class RouteDialog;
}
struct RouteData
{
    double distance;
    int travelTime;
    std::string status;
};
class RouteDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RouteDialog(QWidget* parent = nullptr);
    RouteDialog(QWidget* parent, Route* existing);
    ~RouteDialog();
    Route* getRoute() const;
    RouteData getData() const;

protected:
    void accept() override;

private:
    Ui::RouteDialog* ui;
    bool editMode;
};
#endif
