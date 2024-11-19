#include "app_simulator.h"
#include "logger.h"
#include "call_simulator.h"
#include "sms_simulator.h"
#include "network_simulator.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define APP_BUF_SIZE 200
static const char *current_app = NULL;
static int app_usage_time = 0;
static int app_start_time = 0;

void simulate_app_usage(int receiver_id, int simulation_time, int next_app_time) {
    static const char *apps[] = {"YouTube", "WhatsApp", "Instagram", "Facebook", "Twitter", "Spotify"};

    char details[APP_BUF_SIZE];

    // If no app is active, or simulation time has moved significantly, start a new app session
    if (current_app == NULL || simulation_time - app_start_time >= next_app_time) {
        // Log the end of the previous app usage session (if any)
        if (current_app != NULL) {
            int app_duration = simulation_time - app_start_time;
            app_usage_time = app_duration;
            if (is_call_ringing()) {
                snprintf(details, APP_BUF_SIZE,
                         "Foreground: Phone (Ringing for Receiver #%d). Background: %s used for %d seconds.",
                         receiver_id, current_app, app_duration);
            } else if (is_user_busy()) {
                snprintf(details, APP_BUF_SIZE,
                         "Foreground: Phone (Call with Receiver #%d). Background: %s used for %d seconds.",
                         receiver_id, current_app, app_duration);
            } else {
                snprintf(details, APP_BUF_SIZE,
                         "Foreground: %s used for %d seconds.",
                         current_app, app_duration);
            }
            log_event(EVENT_APP_USAGE, details);

            simulate_app_network_usage(app_usage_time);
        }

        // Switch to a new app
        current_app = apps[rand() % (sizeof(apps) / sizeof(apps[0]))];
        app_start_time = simulation_time;

        snprintf(details, APP_BUF_SIZE,
                 "Switched to app: %s at simulation time: %d seconds.",
                 current_app, simulation_time);
        log_event(EVENT_APP_USAGE, details);
    }   

    int sms_rec = rand() % 100 + 1;
    if(sms_rec % 3 == 0) {
        receive_sms();
    }

    if((strcmp(current_app, "WhatsApp") == 0) && (sms_rec % 2 == 0)) {
        send_sms();
    }
}

