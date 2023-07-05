#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include <QDockWidget>

namespace Ui {
class Ingredients;
}

class Ingredients : public QDockWidget
{
    Q_OBJECT

public:
    explicit Ingredients(QWidget *parent = nullptr);
    ~Ingredients();

private:
    Ui::Ingredients *ui;
};

#endif // INGREDIENTS_H
