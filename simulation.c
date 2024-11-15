#include "logger.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void simulate_call() {
    int is_picked_up = rand() % 2; // Randomize: 0 for declined, 1 for picked up

    if (is_picked_up) {
        int duration = rand() % 10 + 1; // Call duration is set between 1 and 10 seconds
        char details[50];
        snprintf(details, sizeof(details), "Call picked up. Duration: %d seconds", duration);
        log_event(EVENT_CALL, details);
        sleep(duration); // Simulate call duration
    } else {
        char details[50];
        snprintf(details, sizeof(details), "Call declined.");
        log_event(EVENT_CALL, details);
    }
}

void simulate_sms() {
    int received = rand() % 2; // Randomize: 0 for Sending, 1 for receiving 

    if (received) {
        char details[50];
        snprintf(details, sizeof(details), "SMS received from contact number %d", rand() % 10000);
        log_event(EVENT_SMS, details);
        sleep(0.5); // Simulating that it takes 0.5 seconds to send or receive a message.
    } else {
        char details[50];
        snprintf(details, sizeof(details), "SMS sent to contact number %d", rand() % 10000);
        log_event(EVENT_SMS, details);
        sleep(0.5);
    }
}

void simulate_app_usage() {
    int duration = rand() % 10 + 1; // App usage between 1 and 10 seconds
    char details[50];
    snprintf(details, sizeof(details), "App open duration: %d seconds", duration);
    log_event(EVENT_APP_USAGE, details);
    sleep(duration); 
}
