#ifndef Q_CROSSCACHE_InterfaceLocal_H
#define Q_CROSSCACHE_InterfaceLocal_H

#include "./qcrosscache_test_unit.h"

namespace QCrossCache {

class Q_CROSSCACHE_InterfaceLocal : public SDKGoogleTestUnit {
public:
};

TEST_F(Q_CROSSCACHE_InterfaceLocal, serviceStart)
{
    EXPECT_EQ(this->serviceStart(),true)<<"fail: service start";
}

TEST_F(Q_CROSSCACHE_InterfaceLocal, put)
{

}

TEST_F(Q_CROSSCACHE_InterfaceLocal, get)
{

}

TEST_F(Q_CROSSCACHE_InterfaceLocal, remove)
{

}

TEST_F(Q_CROSSCACHE_InterfaceLocal, take)
{

}

TEST_F(Q_CROSSCACHE_InterfaceLocal, list)
{

}

TEST_F(Q_CROSSCACHE_InterfaceLocal, listKey)
{

}

TEST_F(Q_CROSSCACHE_InterfaceLocal, serviceStop)
{
    EXPECT_EQ(this->serviceStop(),true)<<"fail: service stop";
}

}


#endif
