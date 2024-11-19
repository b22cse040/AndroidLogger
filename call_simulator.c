#include "call_simulator.h"
#include "network_simulator.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define CALL_BUF_SIZE 100

// Static variables for call state
static int call_pickup_time = 0; //Time when phone is picked up
static int call_start_time = -1;  // Time when the phone starts ringing
static int call_timeout = 0;     // Ringing duration timeout
static int busy_status = 0;      // 0: not busy, 1: busy
static int call_ringing = 0;     // 0: not ringing, 1: ringing
static int call_end_time = 0;
static int caller_id = 0;

void simulate_call(int receiver_id, int current_time) {
    char details[CALL_BUF_SIZE];
    if(busy_status && call_end_time == current_time) {
        snprintf(details, CALL_BUF_SIZE,
                 "Call ended after %d duration.",
                 call_end_time - call_pickup_time);
        log_event(EVENT_CALL, details);
        busy_status = 0;

        simulate_call_network_usage(call_end_time - call_pickup_time);
    }

    // Check if the phone is currently ringing
    if (call_ringing) {
        // If the ringing has timed out
        if (current_time >= call_timeout) {
            snprintf(details, CALL_BUF_SIZE,
                     "Call rejected by Receiver #%d after %d seconds of ringing.",
                     receiver_id, call_timeout - call_start_time);
            log_event(EVENT_CALL, details);
            call_ringing = 0; // Stop ringing
        }
        return;
    }

    // If no call is currently ringing, decide randomly to start a new call
    if (rand() % 10 < 1) { // 10% chance to start a call
        call_ringing = 1;
        call_start_time = current_time; // Record the start time
        call_timeout = call_start_time + (rand() % 30 + 1); // Set ringing timeout (1–30 seconds)
        caller_id = rand() % 10000 + 1;

        snprintf(details, CALL_BUF_SIZE,
                 "Phone ringing from Caller #%d.",
                 caller_id);
        log_event(EVENT_CALL, details);

        if(busy_status) {
            snprintf(details, CALL_BUF_SIZE,
                     "User Already on Other Call. Phone Rejected");
            log_event(EVENT_CALL, details);
            call_ringing = 0;
        }
    }

    // Check if the call is picked up within the ringing period
    if (call_ringing && rand() % 10 < 6) { // 60% chance to pick up
        int call_duration = rand() % 10 + 1; // Call duration (1–10 seconds)
        snprintf(details, CALL_BUF_SIZE,
                 "Call picked up by Receiver #%d.",
                 receiver_id);
        call_pickup_time = current_time;
        call_end_time = current_time + call_duration;
        log_event(EVENT_CALL, details);

        call_ringing = 0;  // Stop ringing
        busy_status = 1;   // Set user as busy
    }

    return;
}

int is_user_busy() {
    return busy_status;
}

int is_call_ringing() {
    return call_ringing;
}