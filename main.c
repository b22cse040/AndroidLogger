#include "logger.h"
#include <time.h>
#include <stdlib.h>

void simulate_call();
void simulate_sms();
void simulate_app_usage();

int main() {
    srand(time(NULL));
    // log_message(LOG_ID_CALL, "Main", "Starting call simulation...");
    // log_message(LOG_ID_SMS, "Main", "Starting SMS simulation...");
    // log_message(LOG_ID_APP_USAGE, "Main", "Starting app usage simulation...");

    // Simulate a sequence of calls, SMS, and app usage
    for (int i = 0; i < 5; ++i) {
        int activity = rand() % 3;
        switch (activity) {
            case 0:
                simulate_call();
                break;
            case 1:
                simulate_sms();
                break;
            case 2:
                simulate_app_usage();
                break;
        }
    }
    return 0;
}
