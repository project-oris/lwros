#ifndef LWROS_RCLAPI_H
#define LWROS_RCLAPI_H

#include <stddef.h>

typedef void *NodeHandle;
typedef void *PublisherHandle;
typedef void *SubscriptionHandle;

NodeHandle create_node(const char *nodename);
void destroy_node(NodeHandle node);
PublisherHandle create_publisher(NodeHandle node, const char *topicName, const char *typeName);
void destroy_publisher(NodeHandle node, PublisherHandle pub);
int publish_topic(PublisherHandle pub, const void *data, size_t size);
SubscriptionHandle create_subscription(NodeHandle node, const char *topicName, const char *typeName, int (*callback)(SubscriptionHandle sub, const void *msg, size_t msgsize));
void destroy_subscription(NodeHandle node, SubscriptionHandle sub);
void wait_for_stop(NodeHandle node);

#endif // LWROS_RCLAPI_H