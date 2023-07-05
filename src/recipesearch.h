#ifndef RECIPESEARCH_H
#define RECIPESEARCH_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDockWidget>
#include <QLineEdit>
#include <QListView>

#include "recipeitem.h"

namespace Ui {
class RecipeSearch;
}

class RecipeSearch : public QDockWidget
{
    Q_OBJECT

public:
    explicit RecipeSearch(QWidget *parent = nullptr);
    ~RecipeSearch();
    void handleAPIResponse(QNetworkReply* reply);

public slots:
    void search();
    void on_listView_clicked(const QModelIndex& index);

signals:
    void changeRecipe(RecipeItem* item);

private:
    Ui::RecipeSearch *ui;
    QLineEdit* searchLine;
    QListView* listView;
    QNetworkAccessManager networkManager;
};

#endif // RECIPESEARCH_H
