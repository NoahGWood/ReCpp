#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "themeeditor.h"
#include "themetools.h"

#include <QDebug>
// File access
#include <QFile>
#include <QFileDialog>
// Page Components
#include <QString>
#include <QTextBrowser>
#include <QSettings>
#include <QByteArray>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Get settings
    QSettings settings("NoahGWood", "RecipesApp");
    bool hasSavedLayout = settings.value("hasSavedLayout").toBool();
    // Add a central widget
    QWidget* central = new QWidget;
    // Add splitter
    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(central);
    this->setCentralWidget(splitter);
    // Launch default layout
    ingredientDock = new Ingredients(this);
    stepsDock = new RecipeSteps(this);
    searchDock = new RecipeSearch(this);
    recipeImageDock = new RecipeImage(this);
    ingredientBrowser = ingredientDock->findChild<QTextBrowser*>("textBrowser");
    stepsBrowser = stepsDock->findChild<QTextBrowser*>("textBrowser");
    addDockWidget(Qt::LeftDockWidgetArea, ingredientDock);
    addDockWidget(Qt::RightDockWidgetArea, stepsDock);
    addDockWidget(Qt::TopDockWidgetArea, searchDock);
    addDockWidget(Qt::BottomDockWidgetArea, recipeImageDock);

    connect(searchDock, &RecipeSearch::changeRecipe, this, &MainWindow::changeRecipe);

    if(hasSavedLayout){
        QString encoded = settings.value("MainWindowState").toString();
        QByteArray state = QByteArray::fromBase64(encoded.toUtf8());

            this->restoreState(state);
    } else {
        defaultLayout();
    }
    settings.setValue("hasSavedLayout",true);

    // Set theme
    QString theme = settings.value("CurrentTheme").toString();
    if(theme == "Light"){
        setLightTheme();
    } else if(theme == "Custom"){
        loadTheme(settings.value("CustomThemeFile").toString());
    } else {
        setDarkTheme();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveLayoutSettings() {
    QSettings settings("NoahGWood", "RecipesApp");
    QByteArray state = this->saveState();
    QString out = state.toBase64();
    settings.setValue("MainWindowState", out);
}

// Theming
void MainWindow::setDarkTheme(){
    QSettings settings("NoahGWood", "RecipesApp");
    settings.setValue("CurrentTheme","Dark");
    loadTheme(":/themes/dark.css");
}

void MainWindow::setLightTheme(){
    QSettings settings("NoahGWood", "RecipesApp");
    settings.setValue("CurrentTheme","Light");
    loadTheme(":/themes/light.css");
}

void MainWindow::importCustomTheme(){
    QSettings settings("NoahGWood", "RecipesApp");
    settings.setValue("CurrentTheme","Custom");
    QString f = QFileDialog::getOpenFileName(this, "Select stylesheet", "", "CSS files (*.css);;QSS Files (*.qss);;Any (*)");
    loadTheme(f);
    settings.setValue("CustomThemeFile",f);
}

void MainWindow::editCurrentTheme(){
    ThemeEditor* th = new ThemeEditor(this);
    addDockWidget(Qt::TopDockWidgetArea, th);
    th->setFloating(true);
    ThemeTools* tt = new ThemeTools(this);
    addDockWidget(Qt::TopDockWidgetArea,  tt);
    tt->setFloating(true);
}

void MainWindow::loadTheme(QString f){
    QFile file(f);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "CSS File Opened";
        QString cssContent = file.readAll();
        qApp->setStyleSheet(cssContent);
        this->setStyleSheet(cssContent);
        file.close();
    }
}



void MainWindow::changeRecipe(const RecipeItem* item){
// Do something with the selected recipe data
    QString title = item->text();
    QString ingredients = item->ingredients();
    QString instructions = item->instructions();
    QString url = item->image();
    // Get image
    recipeImageDock->loadImageFromUrl(url);
    ingredientBrowser->setText(ingredients);
    stepsBrowser->setText(instructions);

}

// Layout options

void MainWindow::defaultLayout(){
    QByteArray s = QByteArray::fromBase64("AAAA/wAAAAD9AAAAAgAAAAEAAAKdAAABvfwCAAAAAfwAAAB6AAABvQAAAK0A/////AEAAAAC/AAAAAYAAADTAAAAXQD////8AgAAAAL7AAAAFgBSAGUAYwBpAHAAZQBJAG0AYQBnAGUBAAAAegAAAJcAAAAuAP////sAAAAWAEkAbgBnAHIAZQBkAGkAZQBuAHQAcwEAAAEXAAABIAAAAHkA////+wAAABYAUgBlAGMAaQBwAGUAUwB0AGUAcABzAQAAAN8AAAHEAAAAcgD///8AAAACAAACowAAAF78AQAAAAX7AAAAFgBUAGgAZQBtAGUARQBkAGkAdABvAHIDAAAAYQAAAJAAAAGdAAABx/sAAAAUAFQAaABlAG0AZQBUAG8AbwBsAHMDAAAATAAAAQsAAACIAAAAtPsAAAAYAFIAZQBjAGkAcABlAFMAZQBhAHIAYwBoAQAAAAAAAAKjAAAAOgD////7AAAAFgBUAGgAZQBtAGUARQBkAGkAdABvAHICAAAEfQAAAJ8AAAGQAAABLPsAAAAUAFQAaABlAG0AZQBUAG8AbwBsAHMCAAAEzgAAAd4AAACNAAAAWwAAAAAAAAG9AAAABAAAAAQAAAAIAAAACPwAAAAA");
    qDebug() << "DEFAULT: " << s;
    this->restoreState(s);
}
void MainWindow::saveLayout(){
//    settings.value("MainWindowState").toByteArray();
//    this->restoreState(state);
}
