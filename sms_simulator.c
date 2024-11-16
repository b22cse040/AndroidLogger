#include "sms_simulator.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void receive_sms() {
    char details[50];
    snprintf(details, sizeof(details), "SMS received from contact number %d", rand() % 10000);
    log_event(EVENT_SMS, details);
    sleep(1); // Simulate SMS reception delay
}

void send_sms() {
    char details[50];
    snprintf(details, sizeof(details), "SMS sent to contact number %d", rand() % 10000);
    log_event(EVENT_SMS, details);
    sleep(1); // Simulate SMS sending delay
}
