#pragma once

#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDebug>
#include <QStringList>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLocale>
#include <QJsonDocument>
#include <gtest/gtest.h>

namespace QCrossCache {

class SDKGoogleTest : public testing::Test{
public:

    explicit SDKGoogleTest(){
        this->clear();
        QLocale::setDefault(QLocale(QLocale::Portuguese, QLocale::Brazil));
    }

    virtual bool clear(){
        return true;
    }

    virtual bool serviceStart(){
        return this->clear();
    }

    virtual bool serviceStop(){
        return this->clear();
    }

    virtual QStringList arguments(){
        return qApp->arguments();
    }

    static QByteArray toMd5(const QVariant&v){
        return QCryptographicHash::hash(v.toByteArray(), QCryptographicHash::Md5).toHex();
    }

    static QVariant toVar(const QVariant&v){
        return QJsonDocument::fromJson(v.toByteArray()).toVariant();
    }

    static void SetUpTestCase()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    static void TearDownTestCase()
    {
    }

public:

};

}


