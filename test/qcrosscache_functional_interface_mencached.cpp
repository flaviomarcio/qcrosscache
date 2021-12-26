#pragma once

#include "./qcrosscache_test_unit.h"
#include <QCrossCache>

namespace QCrossCache {

static Client*client=nullptr;

class Q_CROSSCACHE_InterfaceMemcached : public SDKGoogleTestUnit {
public:
};

TEST_F(Q_CROSSCACHE_InterfaceMemcached, connect)
{
    client=QCrossCache::clientForMemcached();
    EXPECT_TRUE(client->connect())<<"fail on connect";
}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, clear)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
    EXPECT_EQ(client->listKeys().size(),1)<<"invalid list";
    EXPECT_TRUE(client->clear())<<"invalid clear";
    EXPECT_EQ(client->listKeys().size(),0)<<"invalid list";
}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, put)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, get)
{
    EXPECT_EQ(client->get("key"),"teste")<<"invalid get";
}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, remove)
{
    EXPECT_TRUE(client->remove("key"))<<"invalid remove";
    EXPECT_EQ(client->get("key"),"")<<"invalid get";
}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, take)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
    EXPECT_EQ(client->take("key"),"teste")<<"invalid take";
    EXPECT_EQ(client->get("key"),"")<<"invalid get";
}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, list)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
    EXPECT_EQ(client->list("key").size(),1)<<"invalid list";
    EXPECT_EQ(client->take("key"),"teste")<<"invalid take";
    EXPECT_EQ(client->list("key").size(),0)<<"invalid list";
}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, listKeys)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
    EXPECT_EQ(client->listKeys().size(),1)<<"invalid list";
    EXPECT_EQ(client->take("key"),"teste")<<"invalid take";
    EXPECT_EQ(client->listKeys().size(),0)<<"invalid list";
}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, disconnect)
{
    EXPECT_TRUE(client->disconnect())<<"fail on connect";
    delete client;
}

}
