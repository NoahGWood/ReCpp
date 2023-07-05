#include "themetools.h"
#include "ui_themetools.h"

#include <QColorDialog>
#include <QClipboard>

ThemeTools::ThemeTools(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::ThemeTools)
{
    ui->setupUi(this);
}

ThemeTools::~ThemeTools()
{
    delete ui;
}

void ThemeTools::launchColorPicker(){
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString clip = QColorDialog::getColor(Qt::white, this, "Color Picker", QColorDialog::DontUseNativeDialog).name();
    clipboard->setText(clip);
}
