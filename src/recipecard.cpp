#include "recipecard.h"
#include "ui_recipecard.h"

RecipeCard::RecipeCard(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::RecipeCard)
{
    ui->setupUi(this);
}

RecipeCard::~RecipeCard()
{
    delete ui;
}
