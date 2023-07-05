#ifndef RECIPESTEPS_H
#define RECIPESTEPS_H

#include <QDockWidget>

namespace Ui {
class RecipeSteps;
}

class RecipeSteps : public QDockWidget
{
    Q_OBJECT

public:
    explicit RecipeSteps(QWidget *parent = nullptr);
    ~RecipeSteps();

private:
    Ui::RecipeSteps *ui;
};

#endif // RECIPESTEPS_H
