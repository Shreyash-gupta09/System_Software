#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/file.h>
#include "./structures/admin.h"


int main() {
    struct admin newAdmin;
    int fd;
    ssize_t bytesRead;
    struct admin lastAdmin;

    // Open the file (create if it doesn't exist)
    fd = open("./data/admin.data", O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Apply a write lock on the file
    if (flock(fd, LOCK_EX) < 0) {
        perror("Error locking file");
        close(fd);
        return 1;
    }

    // Set the file position to the end
    lseek(fd, 0, SEEK_END);
    
    // Check if file is empty to assign first adminID as 0
    if (lseek(fd, 0, SEEK_CUR) == 0) {
        newAdmin.adminID = 1;
    } else {
        // Move the pointer to the last record
        lseek(fd, -sizeof(struct admin), SEEK_END);
        // Read the last admin to get the last adminID
        bytesRead = read(fd, &lastAdmin, sizeof(struct admin));
        if (bytesRead == -1) {
            perror("Error reading file");
            close(fd);
            return 1;
        }
        // Increment adminID for the new admin
        newAdmin.adminID = lastAdmin.adminID + 1;
    }

    // Input new admin details
    printf("Enter Admin Name: ");
    scanf("%s", newAdmin.name);
    printf("Enter Admin Password: ");
    scanf("%s", newAdmin.password);

    // Write the new admin record at the end of the file
    if (write(fd, &newAdmin, sizeof(struct admin)) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // Unlock the file
    if (flock(fd, LOCK_UN) < 0) {
        perror("Error unlocking file");
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);

    // Print the new Admin ID
    printf("New Admin ID: %d\n", newAdmin.adminID);

    return 0;
}
