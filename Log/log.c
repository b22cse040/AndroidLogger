#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define constants
#define DATABASE_NAME "UserLogs.db"
#define TABLE_NAME "ActivityLogs"

// Function to create the table
int create_table(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS " TABLE_NAME " ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "type TEXT NOT NULL, "
                      "details TEXT NOT NULL, "
                      "timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
                      ");";

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return rc;
    }
    return SQLITE_OK;
}

// Function to open the database
int open_database(sqlite3 **db) {
    int rc = sqlite3_open(DATABASE_NAME, db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        return rc;
    }
    return create_table(*db);
}

// Function to close the database
void close_database(sqlite3 *db) {
    if (db) {
        sqlite3_close(db);
    }
}

int insert_log(sqlite3 *db, const char *type, const char *details) {
    const char *sql = "INSERT INTO " TABLE_NAME " (type, details) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    // Prepare the SQL statement
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    // Bind the parameters to the SQL statement
    sqlite3_bind_text(stmt, 1, type, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, details, -1, SQLITE_STATIC);

    // Execute the SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    }

    // Finalize the SQL statement to release resources
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

int main() {
    sqlite3 *db;
    
    // Open the database
    if (open_database(&db) != SQLITE_OK) {
        return 1;
    }

    // Insert sample logs
    insert_log(db, "App Usage", "User opened app XYZ for 5 minutes.");
    insert_log(db, "Call Log", "Incoming call from +1234567890 for 2 minutes.");
    insert_log(db, "SMS", "Received SMS from +1234567890: Hello!");

    // Close the database
    close_database(db);
    printf("Logs have been inserted successfully.\n");

    return 0;
}
