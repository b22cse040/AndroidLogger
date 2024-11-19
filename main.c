#include "call_simulator.h"
#include "sms_simulator.h"
#include "app_simulator.h"
#include "notification_simulator.h"
#include "screen_lock_simulator.h"
#include "network_simulator.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

// Function to check or create the log file
int check_or_create_log_file(const char *filename) {
    struct stat buffer;

    if (stat(filename, &buffer) == 0) {
        printf("Log file '%s' exists. Appending logs.\n", filename);
        return 1; // File exists
    }

    // Create a new file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating log file");
        return -1;
    }
    printf("Log file '%s' created.\n", filename);
    fclose(file);
    return 0;
}

int main() {
    const char *log_filename = "logger.txt";

    // Check or create the log file
    if (check_or_create_log_file(log_filename) == -1) {
        return EXIT_FAILURE; // Exit if the log file cannot be created
    }

    srand(time(NULL));
    int receiver_id = rand() % 10000 + 1;

    int simulation_time = 60; // Total simulation time in seconds
    int interval = 1;         // Interval between events (in seconds)

    for (int t = 0; t < simulation_time; t += interval) {
        clock_t start_time = clock(); // Start time of the iteration

        // Randomly decide which simulation to perform (0: Call, 1: SMS, 2: App, 3: Notification, 4: Screen Lock)
        int action = rand() % 5;

        char log_message[256];
        log_id_t log_id = t; // Using the current time as the log ID

        switch (action) {
            case 0:
                simulate_call(receiver_id, t);
                snprintf(log_message, sizeof(log_message),
                    "Time: %d seconds, Action: Call, Receiver ID: %d", t, receiver_id);
                write_log(LOG_CALL, "Simulation Event", log_message);
                break;

            case 1:
                if (rand() % 2 == 0) {
                    receive_sms();
                    snprintf(log_message, sizeof(log_message),
                        "Time: %d seconds, Action: SMS Received, Sender ID: %d", t, receiver_id);
                    } 
                else {
                    send_sms();
                    snprintf(log_message, sizeof(log_message),
                        "Time: %d seconds, Action: SMS Sent, Receiver ID: %d", t, receiver_id);
                    }
                write_log(LOG_SMS, "Simulation Event", log_message);
                break;

            case 2:
                simulate_app_usage(receiver_id, t);
                snprintf(log_message, sizeof(log_message),
                    "Time: %d seconds, Action: App Usage, Receiver ID: %d", t, receiver_id);
                write_log(LOG_APP_USAGE, "Simulation Event", log_message);
                break;

            case 3:
                simulate_notification(receiver_id, t);
                snprintf(log_message, sizeof(log_message),
                    "Time: %d seconds, Action: Notification, Receiver ID: %d", t, receiver_id);
                write_log(LOG_NOTIFICATION, "Simulation Event", log_message);
                break;

            case 4:
                simulate_screen_lock(t);
                snprintf(log_message, sizeof(log_message),
                    "Time: %d seconds, Action: Screen Lock Toggle, Status: %s",
                    t, is_screen_locked() ? "Locked" : "Unlocked");
                write_log(LOG_SCREEN_LOCK, "Simulation Event", log_message);
                break;
            }


        // Calculate elapsed time and log it
        clock_t end_time = clock();
        double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        snprintf(log_message, sizeof(log_message),
                 "Log ID: %d, Iteration completed in %.3f seconds", log_id, elapsed_time);
        write_log(log_id, "Performance", log_message);

        sleep(interval); // Wait for the next iteration
    }

    // Final summary
    int busy_status = is_user_busy();  // Check if the receiver is busy (on a call)
    printf("User ID: %d, Busy Status: %s\n",
           receiver_id,
           busy_status ? "Busy" : "Available");

    // Print the total data usage
    printf("Total Data Usage: %d MB\n", get_data_usage());

    // Print the screen lock status
    printf("Screen Lock Status: %s\n", is_screen_locked() ? "Locked" : "Unlocked");

    return 0;
}
