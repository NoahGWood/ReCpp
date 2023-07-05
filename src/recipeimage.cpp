#include "recipeimage.h"
#include "ui_recipeimage.h"


#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QObject>
#include <QDebug>

RecipeImage::RecipeImage(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::RecipeImage)
{
    ui->setupUi(this);
    recipeImageLabel = findChild<QLabel*>("recipeImageLabel");
}

RecipeImage::~RecipeImage()
{
    delete ui;
}


void RecipeImage::loadImageFromUrl(const QUrl& url){
    QNetworkAccessManager* networkManager = new QNetworkAccessManager();
    QNetworkReply* reply = networkManager->get(QNetworkRequest(url));

    // Wait for reply to finish
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if(reply->error() == QNetworkReply::NoError){
        // read the image data
        QByteArray imageData = reply->readAll();
        // Create pixmap from image
        QPixmap pixmap;
        if(pixmap.loadFromData(imageData)){
            if(!pixmap.isNull() && recipeImageLabel){
                recipeImageLabel->setPixmap(pixmap);
            }
        }
    }
}