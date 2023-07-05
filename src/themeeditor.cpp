#include "themeeditor.h"
#include "ui_themeeditor.h"

#include <QDockWidget>

#include <QSettings>
#include <QDebug>
#include <QFile>

ThemeEditor::ThemeEditor(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::ThemeEditor)
{
    ui->setupUi(this);
    fileName = this->findChild<QLineEdit*>("lineEdit");
    fileEditor = this->findChild<QTextEdit*>("textEdit");
    QSettings settings("NoahGWood", "RecipesApp");
    QString current = settings.value("CurrentTheme").toString();
    QString v;
    if(current=="Dark"){
        v=":/themes/dark.css";
    } else if (current=="Light"){
        v=":/themes/light.css";
    } else {
        v = settings.value("CustomThemeFile").toString();
    }
    SetEditor(v);
}


void ThemeEditor::SetEditor(QString v) {
    fileName->setText(v);
    QFile file(v);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString css = file.readAll();
        fileEditor->setText(css);
        file.close();
    }
}

ThemeEditor::~ThemeEditor()
{
    delete ui;
}


void ThemeEditor::applyTheme(){
    QString text = fileEditor->toPlainText();
    this->parentWidget()->setStyleSheet(text);
}

void ThemeEditor::saveTheme(){
    QFile file(fileName->text());
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "CSS File Saved";
        QString text = fileEditor->toPlainText();
        file.write(text.toUtf8());
        this->parentWidget()->setStyleSheet(text);
        file.close();
    }
    this->close();
}
void ThemeEditor::cancelThemeEditor(){
    this->close();
}
