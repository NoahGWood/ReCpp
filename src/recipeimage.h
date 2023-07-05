#ifndef RECIPEIMAGE_H
#define RECIPEIMAGE_H

#include <QDockWidget>
#include <QLabel>

namespace Ui {
class RecipeImage;
}

class RecipeImage : public QDockWidget
{
    Q_OBJECT

public:
    explicit RecipeImage(QWidget *parent = nullptr);
    ~RecipeImage();
    void loadImageFromUrl(const QUrl& url);
    QLabel* recipeImageLabel;


private:
    Ui::RecipeImage *ui;
};

#endif // RECIPEIMAGE_H
