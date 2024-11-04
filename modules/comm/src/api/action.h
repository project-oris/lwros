
// int publish(const char *topic, const void *data, size_t size);
// int subscribe(const char *topic, void (*callback)(const void *, size_t));

// // Request/Response 패턴 함수
// int request(const char *service, const void *request_data, size_t request_size,
//             void *response_data, size_t response_size);
// int respond(const char *service, int (*handler)(const void *, size_t, void *, size_t));

// // Action 패턴 함수
// int send_goal(const char *action, const void *goal_data, size_t goal_size);
// int receive_feedback(const char *action, void (*feedback_callback)(const void *, size_t));
// int receive_result(const char *action, void (*result_callback)(const void *, size_t));

#ifndef USER_API_ACTION_H
#define USER_API_ACTION_H

#include <stddef.h>

void *create_action_server(const void *ctx, void *key, void (*callback)(const void *server, const void req*, void *res)); 
int free_action_server(void *server);

void *create_action_client(const void *ctx, void *key);
int free_action_client(void *client);

int action_send_goal_sync(void *client, const void *req, void *res, void (*feedback_callback)(const void *req, const void *feedbck));
int action_send_goal_async(void *client, const void *req, 
    void (*result_callback)(const void *req, const void *res),
    void (*feedback_callback)(const void *req, const void *feedbck));

int init_action_api(void *ctx, void *config);    // config에 따라 ctx의 action adapter를 설정
int free_action_api(void *ctx);

#endif // USER_API_ACTION_H
