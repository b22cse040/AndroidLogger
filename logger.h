#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define LOG_BUF_SIZE 1024
#define LOG_DIR "/home/your_username/Desktop/OS_Course/Project/Logs" // Directory for log files

// Enum for log ID types, we have set LOG_ID_CALL for Calling, LOG_ID_SMS for Messaging and LOG_ID_APP_USAGE for using app.
typedef enum {
    LOG_ID_CALL,        
    LOG_ID_SMS,         
    LOG_ID_APP_USAGE    
} log_id_t;

// Enum for event types, we have set EVENT_CALL for Calling, EVENT_SMS for SMS, EVENT_APP_USAGE for App Usage
typedef enum {
    EVENT_CALL,         
    EVENT_SMS,          
    EVENT_APP_USAGE 
} event_type_t;

// Function declarations
int write_log(log_id_t log_id, const char *tag, const char *msg);  // Write a log to a file for a specific log ID
int log_message(log_id_t log_id, const char *tag, const char *fmt, ...);  // Format and write a log message with variable arguments
void log_event(event_type_t event, const char *details);  // Log an event of a specific type
void initialize_logger(void);  // Ensure the log directory exists
void get_log_file_path(int receiver_id, char *file_path, size_t size);  // Get the log file path for a specific receiver ID
void log_to_file(int receiver_id, const char *log_entry);  // Write a log entry to a file for a specific receiver
void upload_receiver_logs_to_dropbox(int receiver_id);  // Upload logs for a specific receiver ID to Dropbox
void upload_file_to_dropbox(const char *file_path, const char *dropbox_path);  // Upload a file to Dropbox
void load_env(void);  // Load environment variables from the .env file
int get_receiver_id();  // Placeholder for getting receiver ID (you need to implement your logic)

#endif
