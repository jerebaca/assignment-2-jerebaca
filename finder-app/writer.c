#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    // Open syslog
    openlog("writer", LOG_PID, LOG_USER);

    // Check for correct number of arguments
    if (argc != 3)
    {
        syslog(LOG_ERR, "Invalid number of arguments: %d", argc);
        printf("Usage: %s <file> <string>\n", argv[0]);
        closelog();
        return 1;
    }

    char *file_path = argv[1];
    char *write_str = argv[2];

    // Log debug message
    syslog(LOG_DEBUG, "Writing %s to %s", write_str, file_path);

    // Open file (create if it doesn't exist, truncate if it does)
    int fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        syslog(LOG_ERR, "Error opening file %s: %s", file_path, strerror(errno));
        closelog();
        return 1;
    }

    // Write string to file
    ssize_t bytes_written = write(fd, write_str, strlen(write_str));
    if (bytes_written == -1)
    {
        syslog(LOG_ERR, "Error writing to file %s: %s", file_path, strerror(errno));
        close(fd);
        closelog();
        return 1;
    }

    // Close file
    if (close(fd) == -1)
    {
        syslog(LOG_ERR, "Error closing file %s: %s", file_path, strerror(errno));
        closelog();
        return 1;
    }

    // Close syslog
    closelog();

    return 0;
}