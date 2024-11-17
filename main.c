#include "call_simulator.h"
#include "sms_simulator.h"
#include "app_simulator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    srand(time(NULL)); // Seed the random number generator
    int receiver_id = rand() % 10000 + 1;

    int simulation_time = 600; // Total simulation time in seconds
    int interval = 1;           // Interval between events (in seconds)

    int next_app_time = rand() % 100 + 1; // Next scheduled app event

    for (int t = 0; t < simulation_time; t += interval) {
        printf("Simulating at time %d seconds...\n", t);

        // Handle call ringing logic based on simulation time
        simulate_call(receiver_id, t);

        // Simulate App Usage if it's time
        if (t >= next_app_time) {
            simulate_app_usage(receiver_id, t);
            next_app_time = t + (rand() % 100 + 1); // Schedule next app usage randomly within 1–100 seconds
        }

        // Print the receiver ID and busy status
        int busy_status = is_user_busy();

        printf("Receiver ID: %d, Busy Status: %s\n",
               receiver_id,
               busy_status ? "Busy" : "Available");

        sleep(interval); // Wait for the next iteration
    }

    return 0;
}

