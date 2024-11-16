#include "logger.h" // Calling LOGGER.H File 
#include <sys/time.h>
#include <stdarg.h>

static int write_log(log_id_t log_id, const char* tag, const char* msg) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    char buffer[LOG_BUF_SIZE];

    // Format log message with timestamp and tag
    snprintf(buffer, sizeof(buffer), "[%ld.%06ld] %s: %s\n", tv.tv_sec, tv.tv_usec, tag, msg);
    fputs(buffer, stdout);
    return 0;
}

int log_message(log_id_t log_id, const char* tag, const char* fmt, ...) {
    char msg[LOG_BUF_SIZE];
    va_list args;

    // Format the message
    va_start(args, fmt);
    vsnprintf(msg, LOG_BUF_SIZE, fmt, args);
    va_end(args);

    return write_log(log_id, tag, msg);
}

void log_event(event_type_t event, const char *details) {
    switch (event) {
        case EVENT_CALL:
            log_message(LOG_ID_CALL, "Call", details);
            break;
        case EVENT_SMS:
            log_message(LOG_ID_SMS, "SMS", details);
            break;
        case EVENT_APP_USAGE:
            log_message(LOG_ID_APP_USAGE, "App Usage", details);
            break;
    }
}