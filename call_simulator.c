#include "call_simulator.h"
#include "logger.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static int receiver_id = 0;   // Internal static variable to store receiver ID
static int is_busy = 0;       // Static variable to track call status

void simulate_call(int reciever_id) {
    // Randomize receiver ID if not already set
    if (receiver_id == 0) {
        receiver_id = rand() % 10000 + 1; // Random ID between 1 and 10000
    }

    if (is_busy) {
        // If the user is already on a call, print a busy message
        char busy_message[LOG_BUF_SIZE];
        snprintf(busy_message, LOG_BUF_SIZE, "Receiver #%d is currently busy.", receiver_id);
        log_event(EVENT_CALL, busy_message);
        return;
    }

    // Otherwise, proceed with call simulation
    is_busy = 1; // Mark user as busy
    int is_picked_up = rand() % 2; // Randomize: 0 for declined, 1 for picked up
    int caller_id = rand() % 1000 + 1; // Random caller ID
    char details[LOG_BUF_SIZE]; // Use the defined buffer size

    if (is_picked_up) {
        int duration = rand() % 30 + 1; // Call duration between 1 and 10 seconds
        snprintf(details, LOG_BUF_SIZE, "Call picked up by Receiver #%d from Caller #%d. Duration: %d seconds", receiver_id, caller_id, duration);
        log_event(EVENT_CALL, details);

        sleep(duration); // Simulate call duration

        // Generate post-call feedback
        const char *feedback_options[] = {"Good", "Average", "Bad"};
        const char *feedback = feedback_options[rand() % 3];
        snprintf(details, LOG_BUF_SIZE, "Post-call feedback: %s", feedback);
        log_event(EVENT_CALL, details);
    } else {
        // Generate a reason for declined call
        const char *decline_reasons[] = {"No answer", "Rejected"};
        const char *reason = decline_reasons[rand() % 2];
        snprintf(details, LOG_BUF_SIZE, "Call declined by Receiver #%d for Caller #%d. Reason: %s", receiver_id, caller_id, reason);
        log_event(EVENT_CALL, details);
    }

    is_busy = 0; // Mark user as free after the call
}
