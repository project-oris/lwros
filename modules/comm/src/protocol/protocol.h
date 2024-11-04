#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stddef.h>

typedef struct {
    int (*init)(void);
    int (*send)(const void *data, size_t size);
    int (*receive)(void *buffer, size_t size);
    int (*close)(void);
} protocol_t;

int register_protocol(const char *name, protocol_t *protocol, int priority);
int select_protocol(void);
void protocol_send(const void *data, size_t size);
void protocol_receive(void *buffer, size_t size);
void close_protocol(void);

// 콜백 함수 타입 정의
typedef void (*protocol_receive_callback_t)(const void *, size_t);

// 콜백 함수 설정 함수
void protocol_set_receive_callback(protocol_receive_callback_t callback);
void protocol_set_service_callback(protocol_receive_callback_t callback);
void protocol_set_action_feedback_callback(protocol_receive_callback_t callback);
void protocol_set_action_result_callback(protocol_receive_callback_t callback);

#endif // PROTOCOL_H
