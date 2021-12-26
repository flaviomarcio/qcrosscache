#ifndef Q_CROSSCACHE_InterfaceMongoDb_H
#define Q_CROSSCACHE_InterfaceMongoDb_H

#include "./qcrosscache_test_unit.h"
#include <QCrossCache>

namespace QCrossCache {

static Client*client=nullptr;

class Q_CROSSCACHE_InterfaceMongoDb : public SDKGoogleTestUnit {
public:
};

TEST_F(Q_CROSSCACHE_InterfaceMongoDb, connect)
{
    client=QCrossCache::clientForMongoDb();
    EXPECT_TRUE(client->connect())<<"fail on connect";
}

TEST_F(Q_CROSSCACHE_InterfaceMongoDb, put)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
}

TEST_F(Q_CROSSCACHE_InterfaceMongoDb, get)
{
    EXPECT_EQ(client->get("key"),"teste")<<"invalid get";
}

TEST_F(Q_CROSSCACHE_InterfaceMongoDb, remove)
{
    EXPECT_TRUE(client->remove("key"))<<"invalid remove";
    EXPECT_EQ(client->get("key"),"")<<"invalid get";
}

TEST_F(Q_CROSSCACHE_InterfaceMongoDb, take)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
    EXPECT_EQ(client->take("key"),"teste")<<"invalid take";
    EXPECT_EQ(client->get("key"),"")<<"invalid get";
}

TEST_F(Q_CROSSCACHE_InterfaceMongoDb, list)
{
//    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
//    EXPECT_EQ(client->list("key").size(),1)<<"invalid list";
//    EXPECT_EQ(client->take("key"),"teste")<<"invalid take";
//    EXPECT_EQ(client->list("key").size(),0)<<"invalid list";
}

TEST_F(Q_CROSSCACHE_InterfaceMongoDb, listKeys)
{
//    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
//    EXPECT_EQ(client->listKeys().size(),1)<<"invalid list";
//    EXPECT_EQ(client->take("key"),"teste")<<"invalid take";
//    EXPECT_EQ(client->listKeys().size(),0)<<"invalid list";
}

TEST_F(Q_CROSSCACHE_InterfaceMongoDb, clear)
{
    EXPECT_TRUE(client->put("key","teste"))<<"invalid put";
    //EXPECT_EQ(client->listKeys().size(),1)<<"invalid list";
    EXPECT_TRUE(client->clear())<<"invalid clear";
    EXPECT_EQ(client->listKeys().size(),0)<<"invalid list";
}

TEST_F(Q_CROSSCACHE_InterfaceMongoDb, disconnect)
{
    EXPECT_TRUE(client->disconnect())<<"fail on connect";
    delete client;
}

}


#endif
