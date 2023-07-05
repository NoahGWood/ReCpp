#include "recipesteps.h"
#include "ui_recipesteps.h"

RecipeSteps::RecipeSteps(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::RecipeSteps)
{
    ui->setupUi(this);
}

RecipeSteps::~RecipeSteps()
{
    delete ui;
}
