#ifndef USER_API_SRV_H
#define USER_API_SRV_H

#include <stddef.h>

void *create_srv_server(const void *ctx, void *key, void (*callback)(const void *server, const void req*, void *res)); 
int free_srv_server(void *server);

void *create_srv_client(const void *ctx, void *key);
int free_srv_client(void *client);

int srv_call_sync(void *client, const void *req, void *res);
int srv_call_async(void *client, const void *req, void (*callback)(const void *client, void *res));

int init_srv_api(void *ctx, void *config);  // config에 따라 ctx의 srv adapter를 설정
int free_srv_api(void *ctx);

#endif // USER_API_SRV_H
