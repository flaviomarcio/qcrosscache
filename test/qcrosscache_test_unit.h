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
#include <gtest/gtest.h>

namespace QCrossCache {

class SDKGoogleTest : public testing::Test{
public:

    explicit SDKGoogleTest()
    {
        QLocale::setDefault(QLocale(QLocale::Portuguese, QLocale::Brazil));
    }

    static QByteArray toMd5(const QVariant&v)
    {
        return QCryptographicHash::hash(v.toByteArray(), QCryptographicHash::Md5).toHex();
    }

    static QVariant toVar(const QVariant&v)
    {
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

class SDKGoogleTestUnit : public SDKGoogleTest{
public:

    explicit SDKGoogleTestUnit():SDKGoogleTest()
    {
    }

public:
};

}
