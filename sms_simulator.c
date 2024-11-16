#include "sms_simulator.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define SMS_BUF_SIZE 100

void simulate_sms(int reciever_id) {
    char details[SMS_BUF_SIZE];
    const char *sms_templates_incoming[] = {
        "Hey, are you free to talk?",
        "Meeting postponed to 3 PM.",
        "Your OTP is %06d.", // Placeholder for OTP
        "Let's catch up this weekend!"
    };
    const char *sms_templates_outgoing[] = {
        "I'll call you back in a bit.",
        "Meeting scheduled for 2 PM.",
        "Your appointment is confirmed.",
        "Can we reschedule our discussion?"
    };

    // Check if the user is busy
    if (is_user_busy()) {
        snprintf(details, SMS_BUF_SIZE, "SMS delayed as Receiver #%d is busy.", get_receiver_id());
        log_event(EVENT_SMS, details);
        sleep(1); // Wait before retrying
        return;
    }

    // Randomize SMS type: 0 for sent, 1 for received
    int received = rand() % 2;

    if (received) {
        int otp = rand() % 1000000; // Generate a random 6-digit OTP
        const char *message_template = sms_templates_incoming[rand() % 4];

        // If the selected template includes an OTP placeholder, insert the OTP
        if (strstr(message_template, "%06d") != NULL) {
            snprintf(details, SMS_BUF_SIZE, "SMS received from Receiver #%d: \"%06d\"", get_receiver_id(), otp);
        } else {
            snprintf(details, SMS_BUF_SIZE, "SMS received from Receiver #%d: \"%s\"", get_receiver_id(), message_template);
        }

        log_event(EVENT_SMS, details);
    } else {
        const char *message = sms_templates_outgoing[rand() % 4]; // Random outgoing template
        snprintf(details, SMS_BUF_SIZE, "SMS sent to Receiver #%d: \"%s\"", get_receiver_id(), message);
        log_event(EVENT_SMS, details);
    }

    sleep(1); // Simulate time taken to process the SMS
}
