#ifndef NETWORK_SIMULATOR_H
#define NETWORK_SIMULATOR_H

void simulate_app_network_usage(int app_usage_duration);
void simulate_call_network_usage(int call_duration);
int get_data_usage();  // Returns total data usage in MB

#endif // NETWORK_SIMULATOR_H