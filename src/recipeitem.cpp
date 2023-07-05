#include "recipeitem.h"

RecipeItem::RecipeItem(const QString &title,
                       const QString &ingredients,
                       const QString &instructions,
                       const QString &image)
    : QStandardItem(title)
{
    // Set additional data roles for ingredients and instructions
    setData(ingredients, IngredientsRole);
    setData(instructions, InstructionsRole);
    setData(image, ImageRole);
}

QVariant RecipeItem::data(int role) const
{
    if (role == Qt::DisplayRole)
    {
        // Return the title as the display data
        return QStandardItem::data(Qt::DisplayRole);
    }

    return QStandardItem::data(role);
}

QString RecipeItem::ingredients() const
{
    // Retrieve the ingredients data from the item
    return data(IngredientsRole).toString();
}
QString RecipeItem::instructions() const
{
    // Retrieve the instructions data from the item's role
    return data(InstructionsRole).toString();
}
QString RecipeItem::image() const {
    return data(ImageRole).toString();
}
