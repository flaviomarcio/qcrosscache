#ifndef Q_CROSSCACHE_InterfaceRedis_H
#define Q_CROSSCACHE_InterfaceRedis_H

#include "./qcrosscache_test_unit.h"
#include <QCrossCache>

namespace QCrossCache {

static Client*client=nullptr;

class Q_CROSSCACHE_InterfaceRedis : public SDKGoogleTestUnit {
public:
};

TEST_F(Q_CROSSCACHE_InterfaceRedis, connect)
{
    client=QCrossCache::clientForRedis();
    EXPECT_TRUE(client->connect())<<"fail on connect";
}

TEST_F(Q_CROSSCACHE_InterfaceRedis, put)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
}

TEST_F(Q_CROSSCACHE_InterfaceRedis, get)
{
    EXPECT_EQ(client->get("key"),"teste")<<"invalid get";
}

TEST_F(Q_CROSSCACHE_InterfaceRedis, remove)
{
    EXPECT_TRUE(client->remove("key"))<<"invalid remove";
    EXPECT_EQ(client->get("key"),"")<<"invalid get";
}

TEST_F(Q_CROSSCACHE_InterfaceRedis, take)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
    EXPECT_EQ(client->take("key"),"teste")<<"invalid take";
    EXPECT_EQ(client->get("key"),"")<<"invalid get";
}

TEST_F(Q_CROSSCACHE_InterfaceRedis, list)
{
//    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
//    EXPECT_EQ(client->list("key").size(),1)<<"invalid list";
//    EXPECT_EQ(client->take("key"),"teste")<<"invalid take";
//    EXPECT_EQ(client->list("key").size(),0)<<"invalid list";
}

TEST_F(Q_CROSSCACHE_InterfaceRedis, listKeys)
{
//    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
//    EXPECT_EQ(client->listKeys().size(),1)<<"invalid list";
//    EXPECT_EQ(client->take("key"),"teste")<<"invalid take";
//    EXPECT_EQ(client->listKeys().size(),0)<<"invalid list";
}

TEST_F(Q_CROSSCACHE_InterfaceRedis, clear)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
    //EXPECT_EQ(client->listKeys().size(),1)<<"invalid list";
    EXPECT_TRUE(client->clear())<<"invalid clear";
    EXPECT_EQ(client->listKeys().size(),0)<<"invalid list";
}

TEST_F(Q_CROSSCACHE_InterfaceRedis, disconnect)
{
    EXPECT_TRUE(client->disconnect())<<"fail on connect";
    delete client;
}

}


#endif
