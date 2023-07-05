#ifndef RECIPEITEM_H
#define RECIPEITEM_H

#include <QStandardItem>

class RecipeItem : public QStandardItem
{
public:
    explicit RecipeItem(const QString &title,
                        const QString &ingredients,
                        const QString &instructions,
                        const QString &image);

    QVariant data(int role) const override;
    QString ingredients() const;
    QString instructions() const;
    QString image() const;

private:
    static const int IngredientsRole = Qt::UserRole + 1;
    static const int InstructionsRole = Qt::UserRole + 2;
    static const int ImageRole = Qt::UserRole + 3;
};

#endif // RECIPEITEM_H
