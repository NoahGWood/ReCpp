#ifndef RECIPECARD_H
#define RECIPECARD_H

#include <QDockWidget>

namespace Ui {
class RecipeCard;
}

class RecipeCard : public QDockWidget
{
    Q_OBJECT

public:
    explicit RecipeCard(QWidget *parent = nullptr);
    ~RecipeCard();

private:
    Ui::RecipeCard *ui;
};

#endif // RECIPECARD_H
