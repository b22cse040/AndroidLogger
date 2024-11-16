#include "call_simulator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    srand(time(NULL)); // Seed the random number generator

    int simulation_time = 1000; // Total simulation time in seconds
    int interval = 1;           // Interval between attempts to simulate a call (in seconds)
    int receiver_id = rand() % 1000 + 1;

    for (int t = 0; t < simulation_time; t += interval) {
        printf("Simulating at time %d seconds...\n", t);

        // Attempt to simulate a call
        if (t % 2 == 0) {
            simulate_call(receiver_id); // Simulate a call
        } else {
            simulate_sms(receiver_id); // Simulate an SMS
        }

        // Check and print the busy status
        int busy_status = is_user_busy();

        printf("Receiver ID: %d, Busy Status: %s\n",
               receiver_id,
               busy_status ? "Busy" : "Available");

        sleep(interval); // Wait for the next iteration
    }

    return 0;
}
