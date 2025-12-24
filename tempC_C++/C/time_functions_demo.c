#include <stdio.h>
#include <time.h>
#include <unistd.h> // For sleep()

// Helper function to print a struct tm in a standardized format.
void print_tm(const char* label, struct tm *time_info) {
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info);
    printf("%s: %s (Day of Week: %d, Day of Year: %d, DST: %d)\n",
           label, buffer, time_info->tm_wday, time_info->tm_yday, time_info->tm_isdst);
}

int main() {
    // time_t: A type to store calendar time. It's usually a long integer
    // representing the number of seconds since the Epoch (00:00:00 UTC, January 1, 1970).
    time_t now, future;
    struct tm *local_tm, *gm_tm, custom_tm;
    char buffer[128];

    // 1. time() - Get current calendar time
    // time(&now) is equivalent to now = time(NULL);
    time(&now);
    printf("--- 1. time() ---\n");
    printf("Current time_t value (seconds since Epoch): %ld\n\n", (long)now);

    // 2. ctime() - Convert time_t to a human-readable string
    // The string format is fixed, e.g., "Sat Nov 15 15:30:00 2025\n"
    // Note: ctime returns a pointer to a statically allocated string, which might be
    // overwritten by subsequent calls to ctime or asctime.
    printf("--- 2. ctime() ---\n");
    printf("ctime() output: %s\n", ctime(&now));

    // 3. localtime() - Convert time_t to a struct tm (local time)
    // struct tm holds time components like year, month, day, hour, etc.,
    // adjusted for the local timezone.
    local_tm = localtime(&now);
    printf("--- 3. localtime() ---\n");
    print_tm("Local time (from localtime)", local_tm);
    printf("\n");

    // 4. gmtime() - Convert time_t to a struct tm (UTC/GMT)
    // Similar to localtime, but the time is in Coordinated Universal Time (UTC).
    gm_tm = gmtime(&now);
    printf("--- 4. gmtime() ---\n");
    print_tm("UTC time (from gmtime)", gm_tm);
    printf("\n");

    // 5. asctime() - Convert struct tm to a human-readable string
    // The format is the same as ctime().
    printf("--- 5. asctime() ---\n");
    printf("asctime() with local_tm: %s", asctime(local_tm));
    printf("asctime() with gm_tm:   %s\n", asctime(gm_tm));

    // 6. strftime() - Format a struct tm into a custom string
    // This is the most flexible way to format date and time.
    printf("--- 6. strftime() ---\n");
    // Example 1: ISO 8601 format
    strftime(buffer, sizeof(buffer), "ISO 8601: %Y-%m-%dT%H:%M:%S%z", local_tm);
    puts(buffer);
    // Example 2: US format
    strftime(buffer, sizeof(buffer), "US Format: %m/%d/%Y %I:%M:%S %p", local_tm);
    puts(buffer);
    // Example 3: Full day and month name
    strftime(buffer, sizeof(buffer), "Full names: %A, %B %d, %Y", local_tm);
    puts(buffer);
    printf("\n");

    // 7. mktime() - Convert a struct tm back to a time_t
    // This is useful for date arithmetic. mktime also normalizes the struct tm.
    printf("--- 7. mktime() ---\n");
    // Let's create a custom time: 10:30:00 on Christmas Day 2025
    custom_tm = *local_tm; // Start with a copy of current local time
    custom_tm.tm_year = 2025 - 1900; // tm_year is years since 1900
    custom_tm.tm_mon = 11;           // tm_mon is 0-11 (December)
    custom_tm.tm_mday = 25;
    custom_tm.tm_hour = 10;
    custom_tm.tm_min = 30;
    custom_tm.tm_sec = 0;
    custom_tm.tm_isdst = -1; // Let mktime figure out DST

    time_t christmas_time = mktime(&custom_tm);
    printf("Original time_t: %ld\n", (long)now);
    printf("Christmas 2025 time_t: %ld\n", (long)christmas_time);
    printf("Christmas as string: %s\n", ctime(&christmas_time));

    // mktime also normalizes the fields. For example, let's set the day to 40.
    custom_tm.tm_mday = 40; // 40th of December
    mktime(&custom_tm); // This will normalize the date
    printf("After setting tm_mday=40, mktime() normalizes it to: %s\n", asctime(&custom_tm));

    // 8. difftime() - Calculate the difference in seconds between two time_t values
    // This is the portable way to find the difference.
    printf("--- 8. difftime() ---\n");
    printf("Waiting for 3 seconds...\n");
    sleep(3); // Pause execution for 3 seconds

    time(&future); // Get the time after the pause
    double diff_seconds = difftime(future, now);

    printf("Start time_t: %ld\n", (long)now);
    printf("End time_t:   %ld\n", (long)future);
    printf("Difference calculated by difftime(): %.2f seconds\n", diff_seconds);

    return 0;
}
