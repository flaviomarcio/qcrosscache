#include <QCoreApplication>
#include <QCrossCache>
#include <QObject>
#include <QDebug>
#include "./your_customs_impl.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto client=new YourCustomClientImpl(nullptr);

    if(!client->connect())
        qDebug()<<"connection fail";

    if(!client->clear())
        qDebug()<<"clear fail";

    QByteArray keyName("key");
    QByteArray keyValue("value");

    if(!client->put(keyName, keyValue))
        qDebug()<<"put fail";

    if(client->get(keyName)!=keyValue)
        qDebug()<<"get fail";

    auto list=client->list("key");
    for(auto&key:list)
        qDebug()<<"list.key=="<<key;

    auto listKeys=client->listKeys();
    for(auto&key:listKeys)
        qDebug()<<"listAll.key=="<<key;

    if(client->take(keyName)!=keyValue)
        qDebug()<<"take fail";

    client->disconnect();
    delete client;

    return 0;
}

