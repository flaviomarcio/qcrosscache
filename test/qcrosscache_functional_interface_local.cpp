#ifndef Q_CROSSCACHE_InterfaceLocal_H
#define Q_CROSSCACHE_InterfaceLocal_H

#include "./qcrosscache_test_unit.h"
#include <QCrossCache>

namespace QCrossCache {

class Q_CROSSCACHE_InterfaceLocal : public SDKGoogleTestUnit {
public:
    Client*client=nullptr;
    virtual void SetUp()
    {
        client=QCrossCache::clientForLocal();
    }

    virtual void TearDown()
    {
        delete client;
    }
};

TEST_F(Q_CROSSCACHE_InterfaceLocal, connect)
{
    EXPECT_TRUE(client->connect())<<"fail on connect";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, clear)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
    EXPECT_EQ(client->listKeys().size(),1)<<"invalid list";
    EXPECT_TRUE(client->clear())<<"invalid clear";
    EXPECT_EQ(client->listKeys().size(),0)<<"invalid list";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, put)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, get)
{
    EXPECT_EQ(client->get("key"),"teste")<<"invalid get";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, remove)
{
    EXPECT_TRUE(client->remove("key"))<<"invalid remove";
    EXPECT_EQ(client->get("key"),"")<<"invalid get";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, take)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
    EXPECT_EQ(client->take("key"),"teste")<<"invalid take";
    EXPECT_EQ(client->get("key"),"")<<"invalid get";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, list)
{
    EXPECT_TRUE(client->put("keyX","teste"))<<"invalid put";
    EXPECT_TRUE(client->put("keyY","teste"))<<"invalid put";
    EXPECT_EQ(client->list("key").size(),2)<<"invalid list";
    EXPECT_EQ(client->take("keyX"),"teste")<<"invalid take";
    EXPECT_EQ(client->take("keyY"),"teste")<<"invalid take";
    EXPECT_EQ(client->list("key").size(),0)<<"invalid list";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, listKeys)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
    EXPECT_EQ(client->listKeys().size(),1)<<"invalid list";
    EXPECT_EQ(client->take("key"),"teste")<<"invalid take";
    EXPECT_EQ(client->listKeys().size(),0)<<"invalid list";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, disconnect)
{
    EXPECT_TRUE(client->disconnect())<<"fail on connect";
}

}


#endif
