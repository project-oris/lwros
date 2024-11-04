
#include "rclapi/rclapi.h"

#include "dev_config.h"

#ifdef DEV_TEST_ZENOHPICO

NodeHandle create_node(const char *nodename)
{
    return NULL;
}

void destroy_node(NodeHandle node)
{
    
}
PublisherHandle create_publisher(NodeHandle node, const char *topicName, const char *typeName)
{
    return NULL;    
}
void destroy_publisher(NodeHandle node, PublisherHandle pub)
{
    
}
int publish_topic(PublisherHandle pub, const void *data, size_t size)
{
    return NULL;    
    
}
SubscriptionHandle create_subscription(NodeHandle node, const char *topicName, const char *typeName, int (*callback)(SubscriptionHandle sub, const void *msg, size_t msgsize))
{
    return NULL;        
}
void destroy_subscription(NodeHandle node, SubscriptionHandle sub)
{
    
}

void wait_for_stop(NodeHandle node)
{

}

#elif defined(DEV_TEST_LWCOMMON)
#endif