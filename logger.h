#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define LOG_BUF_SIZE 1024

// log_id_t can have only 3 values: LOG_ID_CALL for calling, LOG_ID_SMS for messaging and LOG_ID_APP_USAGE to track any app.
typedef enum {
    LOG_ID_CALL,
    LOG_ID_SMS,
    LOG_ID_APP_USAGE
} log_id_t;

// Similarly, event_type_t can have 3 values, EVENT_CALL, EVENT_SMS, EVENT_APP_USAGE for calling, messaging and app usage respectively.
typedef enum {
    EVENT_CALL,
    EVENT_SMS,
    EVENT_APP_USAGE
} event_type_t;

// Function declarations, implemented in logger.c
int write_log(log_id_t log_id, const char* tag, const char* msg);
int log_message(log_id_t log_id, const char* tag, const char* fmt, ...);
void log_event(event_type_t event, const char *details);

#endif 