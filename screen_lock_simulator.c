#include "screen_lock_simulator.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int screen_locked = 0;  // 0 means unlocked, 1 means locked
#define APP_BUF_SIZE 200

// Simulate screen lock/unlock based on time
void simulate_screen_lock(int current_time) {
    if (rand() % 5 == 0) {  // 20% chance to lock/unlock the screen
        screen_locked = !screen_locked;  // Toggle screen lock/unlock

        // Log the screen lock/unlock event
        char details[APP_BUF_SIZE];
        snprintf(details, APP_BUF_SIZE, "Screen %s at time %d", screen_locked ? "locked" : "unlocked", current_time);
        log_event(EVENT_APP_USAGE, details);
    }
}

int is_screen_locked() {
    return screen_locked;
}