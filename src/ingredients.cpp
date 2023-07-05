#include "ingredients.h"
#include "ui_ingredients.h"

Ingredients::Ingredients(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Ingredients)
{
    ui->setupUi(this);
}

Ingredients::~Ingredients()
{
    delete ui;
}
