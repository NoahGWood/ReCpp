#ifndef THEMEEDITOR_H
#define THEMEEDITOR_H

#include <QDockWidget>
#include <QLineEdit>
#include <QTextEdit>

namespace Ui {
class ThemeEditor;
}

class ThemeEditor : public QDockWidget
{
    Q_OBJECT

public:
    explicit ThemeEditor(QWidget *parent = nullptr);
    ~ThemeEditor();

private:
    Ui::ThemeEditor *ui;
    QLineEdit* fileName;
    QTextEdit* fileEditor;
    void SetEditor(QString);

public slots:
    void saveTheme();
    void applyTheme();
    void cancelThemeEditor();

};

#endif // THEMEEDITOR_H
