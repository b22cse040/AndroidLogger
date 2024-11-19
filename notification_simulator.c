#include "notification_simulator.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define APP_BUF_SIZE 200
static const char *apps[] = {"WhatsApp", "Facebook", "Instagram", "Twitter", "Spotify"};
static const char *notifications[] = {"New message", "App update available", "Friend request", "Liked your post"};

void simulate_notification(int receiver_id, int current_time) {
    // Simulate a random notification every 10–30 seconds
    if (rand() % 10 < 2) {  // 20% chance to simulate a notification
        const char *app = apps[rand() % (sizeof(apps) / sizeof(apps[0]))];
        const char *notification = notifications[rand() % (sizeof(notifications) / sizeof(notifications[0]))];

        // Log the notification event
        char details[APP_BUF_SIZE];
        snprintf(details, APP_BUF_SIZE, "Notification from %s: %s for User #%d at time %d", app, notification, receiver_id, current_time);
        log_event(EVENT_APP_USAGE, details);
    }
}
