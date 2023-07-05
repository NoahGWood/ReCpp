#include "recipesearch.h"
#include "ui_recipesearch.h"

#include <QString>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QUrl>
#include <QObject>
#include <QStandardItemModel>

RecipeSearch::RecipeSearch(QWidget *parent) : QDockWidget(parent),
                                              ui(new Ui::RecipeSearch)
{
    ui->setupUi(this);
    searchLine = findChild<QLineEdit *>("lineEdit");
    listView = findChild<QListView *>("listView");
}

RecipeSearch::~RecipeSearch()
{
    delete ui;
}

QJsonArray Query(QString query)
{
    // Set the query
    QString requestData = QString("{\"statements\": [{\"statement\": \"%1\"}]}").arg(query);
    // Set up API
    QString apiUrl = "http://localhost:7474/db/neo4j/tx/commit";
    QNetworkRequest request;
    request.setUrl(apiUrl);
    // Set the headers
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QString username = "neo4j";
    QString password = "password";
    QString creds = QString("%1:%2").arg(username).arg(password).toLatin1().toBase64();
    QString authHeader = QString("Basic %1").arg(creds);
    request.setRawHeader("Authorization", authHeader.toLatin1());
    request.setRawHeader("Content-Type", "application/json");
    // Send the GET request
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(request, requestData.toUtf8());

    // Wait for the reply to finish
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonArray results;
    if (reply->error() == QNetworkReply::NoError)
    {
        // Read the response =
        QByteArray rd = reply->readAll();
        QJsonDocument doc;
        doc = QJsonDocument::fromJson(rd);
        results = doc.object()["results"].toArray().at(0).toObject()["data"].toArray();
    }

    reply->deleteLater(); // Clean up the reply object
    manager.deleteLater(); // Clean up the network manager object

    return results;
}

void RecipeSearch::search()
{
    QString q = searchLine->text();
    QString query = "CALL db.index.fulltext.queryNodes('recipeSearch','";
    query += q;
    query += "') YIELD node RETURN node LIMIT 10";
    // Query recipes
    QJsonArray jsonData = Query(query);
    QStandardItemModel *model = new QStandardItemModel();

    // Extract data from json response & parse models
    for (const QJsonValue &value : jsonData)
    {
        // Extract recipe information
        QString title;
        QString ingredients;
        QString instructions;
        // Get recipe object
        QJsonObject recipeObject = value.toObject()["row"].toArray().at(0).toObject();
        // Get recipe name
        title = recipeObject["name"].toString();
        // Get recipe properties
        QJsonObject props = recipeObject["properties"].toObject();
        // Get ingredients
        QJsonArray recipeIngredients = recipeObject["recipeIngredient"].toArray();
        for (const QJsonValue &ingVal : recipeIngredients)
        {
            QString ing = ingVal.toString();
            ing += "\n";
            ingredients += ing;
        }
        // Get instructions
        QJsonArray recipeInstructions = recipeObject["recipeInstruction"].toArray();
        for (const QJsonValue &insVal : recipeInstructions)
        {
            QString insQuery = "MATCH (n:RecipeInstruction {UUID:'" + insVal.toString() + "'}) RETURN n";
            QString ins = Query(insQuery).at(0).toObject()["row"].toArray().at(0).toObject()["text"].toString();
            ins += "\n";
            instructions += ins;
        }
        // Get images
        QString image_id = recipeObject["image"].toArray().at(0).toString();
        QString imgQuery = "MATCH (n:Image {UUID: '" + image_id + "'}) RETURN n";
        QString image = Query(imgQuery).at(0).toObject()["row"].toArray().at(0).toObject()["url"].toString();
        // TODO:
        // Get first image
        // Get keywords
        // Create a new recipe item
        RecipeItem *recipeItem = new RecipeItem(title, ingredients, instructions, image);
        // Add the recipe item to the model
        model->appendRow(recipeItem);
    }
    // Set the list view
    listView->setModel(model);
}

void RecipeSearch::on_listView_clicked(const QModelIndex &index)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(listView->model());
    if (model)
    {
        // Retrieve the selected RecipeItem
        RecipeItem *selectedRecipeItem = dynamic_cast<RecipeItem *>(model->itemFromIndex(index));

        if (selectedRecipeItem)
        {
            // Perform the desired action with the selected RecipeItem
            QString title = selectedRecipeItem->text();
            QString ingredients = selectedRecipeItem->ingredients();
            QString instructions = selectedRecipeItem->instructions();

            // Do something with the selected recipe data
            emit changeRecipe(selectedRecipeItem);
        }
    }
}
