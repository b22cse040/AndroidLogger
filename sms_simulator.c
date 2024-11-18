#include "sms_simulator.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void simulate_sms() {
    int is_send = rand() % 2;  // 0 (receive) or 1 (send)

    if (is_send) {
        log_event(EVENT_SMS, "SMS sent");
        send_sms();  
    } 
    else {
        log_event(EVENT_SMS, "SMS received");
        receive_sms();  
    }

    sleep(1);
}

// Function to simulate sending an SMS 
void send_sms() {
    printf("Sending SMS...\n");
}

// Function to simulate receiving an SMS
void receive_sms() {
    printf("Received SMS...\n");
}
