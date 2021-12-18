#ifndef Q_CROSSCACHE_InterfaceMemcached_H
#define Q_CROSSCACHE_InterfaceMemcached_H

#include "./qcrosscache_test_unit.h"

namespace QCrossCache {

class Q_CROSSCACHE_InterfaceMemcached : public SDKGoogleTestUnit {
public:
};

TEST_F(Q_CROSSCACHE_InterfaceMemcached, serviceStart)
{
    EXPECT_EQ(this->serviceStart(),true)<<"fail: service start";
}


TEST_F(Q_CROSSCACHE_InterfaceMemcached, put)
{

}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, get)
{

}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, remove)
{

}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, take)
{

}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, list)
{

}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, listKey)
{

}

TEST_F(Q_CROSSCACHE_InterfaceMemcached, serviceStop)
{
    EXPECT_EQ(this->serviceStop(),true)<<"fail: service stop";
}

}


#endif
