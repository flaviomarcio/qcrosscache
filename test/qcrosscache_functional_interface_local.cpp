#ifndef Q_CROSSCACHE_InterfaceLocal_H
#define Q_CROSSCACHE_InterfaceLocal_H

#include "./qcrosscache_test_unit.h"
#include <QCrossCache>

namespace QCrossCache {

class Q_CROSSCACHE_InterfaceLocal : public SDKGoogleTestUnit {
public:
    Client client;
};

TEST_F(Q_CROSSCACHE_InterfaceLocal, serviceStart)
{
    EXPECT_EQ(this->serviceStart(),true)<<"fail: service start";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, put)
{
    EXPECT_TRUE(client.put("key","teste"))<<"invalid put";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, get)
{
    EXPECT_EQ(client.get("key"),"teste")<<"invalid put";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, remove)
{
    EXPECT_TRUE(client.remove("key"))<<"invalid put";
    EXPECT_EQ(client.get("key"),"")<<"invalid put";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, take)
{
    EXPECT_TRUE(client.put("key","teste"))<<"invalid put";
    EXPECT_EQ(client.take("key"),"teste")<<"invalid put";
    EXPECT_EQ(client.get("key"),"")<<"invalid put";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, list)
{

}

TEST_F(Q_CROSSCACHE_InterfaceLocal, listKeys)
{
    EXPECT_TRUE(client.put("key","teste"))<<"invalid put";
    EXPECT_EQ(client.listKeys().size(),1)<<"invalid put";
    EXPECT_EQ(client.take("key"),"teste")<<"invalid put";
    EXPECT_EQ(client.listKeys().size(),0)<<"invalid put";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, serviceStop)
{
    EXPECT_EQ(this->serviceStop(),true)<<"fail: service stop";
}

}


#endif
