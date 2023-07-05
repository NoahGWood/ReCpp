#ifndef THEMETOOLS_H
#define THEMETOOLS_H

#include <QDockWidget>

namespace Ui {
class ThemeTools;
}

class ThemeTools : public QDockWidget
{
    Q_OBJECT

public:
    explicit ThemeTools(QWidget *parent = nullptr);
    ~ThemeTools();

public slots:
    void launchColorPicker();

private:
    Ui::ThemeTools *ui;
};

#endif // THEMETOOLS_H
