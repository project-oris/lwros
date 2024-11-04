#ifndef USER_API_H
#define USER_API_H

#include <stddef.h>

// #include "pubsub.h"
// #include "service.h"
// #include "action.h"

void my_tests();

// // Publish/Subscribe 패턴 함수
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

// int user_api_init(void);
// void user_api_close(void);

#endif // USER_API_H
