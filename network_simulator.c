#include "network_simulator.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int total_data_usage = 0;  // Total data usage in MB
#define APP_BUF_SIZE 200
#define CALL_BUF_SIZE 100

// Simulate network data usage during apps, calls, and SMS
void simulate_app_network_usage(int app_usage_duration) {
    int data_usage = 0;

    // App usage consumes data depending on the type of app (1MB per minute for non-streaming apps, 3MB for streaming apps)
    if (app_usage_duration > 0) {
        data_usage += (app_usage_duration / 60) * 1;  // 1MB for non-streaming apps (e.g., WhatsApp)
        if (rand() % 2 == 0) {  // Simulate streaming apps (e.g., YouTube)
            data_usage += (app_usage_duration / 60) * 3;  // 3MB for streaming apps
        }
    }

    total_data_usage += data_usage;  // Update total data usage

    // Log the data usage
    char details[APP_BUF_SIZE];
    snprintf(details, APP_BUF_SIZE, "Total data usage: %d MB", total_data_usage);
    log_event(EVENT_APP_USAGE, details);
}

void simulate_call_network_usage(int call_duration) {
    int data_usage = 0;
    // Call data usage (simulated as 0.5MB per minute of call)
    if (call_duration > 0) {
        data_usage += (call_duration / 60) * 0.5;  // 0.5MB per minute of call
    }
    total_data_usage += data_usage;  // Update total data usage

    // Log the data usage
    char details[CALL_BUF_SIZE];
    snprintf(details, CALL_BUF_SIZE, "Total data usage: %d MB", total_data_usage);
    log_event(EVENT_CALL, details);
}
int get_data_usage() {
    return total_data_usage;
}