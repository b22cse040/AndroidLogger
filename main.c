#include "call_simulator.h"
#include "sms_simulator.h"
#include "app_simulator.h"
#include "notification_simulator.h"
#include "network_simulator.h"
#include "location_simulator.h"
#include "screen_lock_simulator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    srand(time(NULL)); // Seed the random number generator
    int receiver_id = rand() % 10000 + 1;

    int simulation_time = 300; // Total simulation time in seconds
    int interval = 1;          // Interval between events (in seconds)

    int call_duration = 0;
    int app_usage_duration = 0;
    int next_app_time = rand() % 100 + 1; // Next scheduled app event

    for (int t = 0; t < simulation_time; t += interval) {
        printf("Simulating at time %d seconds...\n", t);

        // Handle call ringing logic based on simulation time
        simulate_call(receiver_id, t);

        // Simulate App Usage if it's time
        simulate_app_usage(receiver_id, t, next_app_time); 
        next_app_time = t + (rand() % 100 + 1); // Schedule next app usage randomly within 1–100 seconds

        // Print the receiver ID and busy status
        simulate_notification(receiver_id, t);

        // Simulate location updates every minute
        simulate_location(t);

        // Simulate screen lock/unlock
        simulate_screen_lock(t);

        // Log encrypted event
        char log_message[512];
        snprintf(log_message, sizeof(log_message), "User ID: %d, Time: %d, App Usage Duration: %d, Call Duration: %d", receiver_id, t, app_usage_duration, call_duration);
        // log_encrypted_event(log_message);        // Encrypt and log the event

        // Print the receiver ID and busy status
        int busy_status = is_user_busy();  // Check if the receiver is busy (on a call)

        printf("USer ID: %d, Busy Status: %s\n",
               receiver_id,
               busy_status ? "Busy" : "Available");

        // Print the total data usage
        printf("Total Data Usage: %d MB\n", get_data_usage());

        // Print the screen lock status
        printf("Screen Lock Status: %s\n", is_screen_locked() ? "Locked" : "Unlocked");
        sleep(interval); // Wait for the next iteration
    }

    return 0;
}

