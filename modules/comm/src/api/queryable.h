#ifndef USER_API_QUERYABLE_H
#define USER_API_QUERYABLE_H

#include <stddef.h>

void *create_queryable(const void *ctx, void *key, void (*callback)(const void *queryable, const void *query, void *reply)) // service server role
int free_queryable(void *queryable);

void *create_query(const void *ctx, void *key)

void *get_query_result(void *queriest);
void *get_query_result_async(void *queriest, void (*callback)(const void *queriest, const void *query, void *reply))

int init_query_api(void *ctx, void *config);  // config에 따라 ctx의 pubsub adapter를 설정
int free_query_api(void *ctx);

#endif // USER_API_QUERYABLE_H
