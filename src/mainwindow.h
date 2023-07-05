#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QTextBrowser>
#include "ingredients.h"
#include "recipeitem.h"
#include "recipesteps.h"
#include "recipesearch.h"
#include "recipeimage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void saveLayoutSettings();
    void loadTheme(QString f);
    Ingredients* ingredientDock;
    RecipeSteps* stepsDock;
    RecipeSearch* searchDock;
    RecipeImage* recipeImageDock;
    QTextBrowser* ingredientBrowser;
    QTextBrowser* stepsBrowser;

public slots:
    void setDarkTheme();
    void setLightTheme();
    void importCustomTheme();
    void editCurrentTheme();
    void changeRecipe(const RecipeItem* item);
    void defaultLayout();
    void saveLayout();

private:
    Ui::MainWindow *ui;

protected:
    void closeEvent(QCloseEvent* event) override {
        saveLayoutSettings();
        event->accept();
    }
};
#endif // MAINWINDOW_H
