#include "location_simulator.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define APP_BUF_SIZE 200
static float last_latitude = 0.0;  // Initial latitude (arbitrary value)
static float last_longitude = 0.0; // Initial longitude (arbitrary value)

// Simulate random location changes every minute
void simulate_location(int current_time) {
    if (current_time % 60 == 0) {  // Update location every minute
        last_latitude += (rand() % 200 - 100) / 1000.0;  // Simulate small latitude changes
        last_longitude += (rand() % 200 - 100) / 1000.0; // Simulate small longitude changes

        // Log the location update
        char details[APP_BUF_SIZE];
        snprintf(details, APP_BUF_SIZE, "New location: Latitude: %.4f, Longitude: %.4f", last_latitude, last_longitude);
        log_event(EVENT_APP_USAGE, details);
    }
}

void log_location(int receiver_id, const char *location) {
    char details[APP_BUF_SIZE];
    snprintf(details, APP_BUF_SIZE, "Receiver #%d Location: %s", receiver_id, location);
    log_event(EVENT_APP_USAGE, details);
}
