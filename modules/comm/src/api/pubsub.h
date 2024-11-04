#ifndef USER_API_PUBSUB_H
#define USER_API_PUBSUB_H

#include <stddef.h>

// ctx is session, publihser is publihser handle, key is target selelctor
//int create_publisher(const void *ctx, void *publisher, void *key);
void *create_publisher(const void *ctx, void *key); // return publisher handle
int free_publisher(void *publihser);

int publish(void *publihser, const void *data, size_t size);

//int create_subscriber(const void *ctx, void *subsciber, void *key, void (*callback)(const void *subscriber, const void *, size_t));
void *create_subscriber(const void *ctx, void *key, void (*callback)(const void *subscriber, const void *, size_t));
int free_subscriber(void *subsciber);

int init_pubsub_api(void *ctx, void *config);  // config에 따라 ctx의 pubsub adapter를 설정
int free_pubsub_api(void *ctx);










#endif // USER_API_PUBSUB_H
