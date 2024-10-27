#ifndef ADMIN_FUNCTION
#define ADMIN_FUNCTION



void createEmployee(struct employee record, int sd){
        int fd;
    ssize_t bytesRead;
    struct employee lastEmployee;
    
    // Open the employee file (create if it doesn't exist)
    fd = open("./data/employee.data", O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("Error opening employee file");
        return ;
    }

    // Apply a write lock to prevent race conditions
    if (flock(fd, LOCK_EX) < 0) {
        perror("Error locking employee file");
        close(fd);
        return ;
    }

    // Set file pointer to the end of the file
    lseek(fd, 0, SEEK_END);
    
    // Check if the file is empty, set first employeeID as 0
    if (lseek(fd, 0, SEEK_CUR) == 0) {
        record.employeeID = 1;
    } else {
        // Move the file pointer to the last record
        lseek(fd, -sizeof(struct employee), SEEK_END);
        // Read the last employee to get the last employeeID
        bytesRead = read(fd, &lastEmployee, sizeof(struct employee));
        if (bytesRead == -1) {
            perror("Error reading employee file");
            close(fd);
            return ;
        }
        // Increment employeeID for the new employee
        record.employeeID = lastEmployee.employeeID + 1;
    }

    // Set employee status to active (true)
    record.status = 1;

    // Write the new employee record at the end of the file
    if (write(fd, &record, sizeof(struct employee)) == -1) {
        perror("Error writing to employee file");
        close(fd);
        return ;
    }

    // Unlock the file
    if (flock(fd, LOCK_UN) < 0) {
        perror("Error unlocking employee file");
        close(fd);
        return ;
    }

    // Close the file
    close(fd);

    // Send the new employee ID to the client via the socket descriptor
    if (write(sd, &record.employeeID, sizeof(record.employeeID)) == -1) {
        perror("Error sending employee ID to client");
        return ;
    }

}
void createmanager(struct manager record, int sd){
        int fd;
    ssize_t bytesRead;
    struct manager lastEmployee;
    
    // Open the employee file (create if it doesn't exist)
    fd = open("./data/manager.data", O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("Error opening manager file");
        return ;
    }

    // Apply a write lock to prevent race conditions
    if (flock(fd, LOCK_EX) < 0) {
        perror("Error locking manager file");
        close(fd);
        return ;
    }

    // Set file pointer to the end of the file
    lseek(fd, 0, SEEK_END);
    
    if (lseek(fd, 0, SEEK_CUR) == 0) {
        record.managerID = 1;
    } else {
        // Move the file pointer to the last record
        lseek(fd, -sizeof(struct manager), SEEK_END);
        
        bytesRead = read(fd, &lastEmployee, sizeof(struct manager));
        if (bytesRead == -1) {
            perror("Error reading employee file");
            close(fd);
            return ;
        }
        
        record.managerID = lastEmployee.managerID+ 1;
    }

    
    record.status = 1;

    
    if (write(fd, &record, sizeof(struct manager)) == -1) {
        perror("Error writing to manager file");
        close(fd);
        return ;
    }

    // Unlock the file
    if (flock(fd, LOCK_UN) < 0) {
        perror("Error unlocking manager file");
        close(fd);
        return ;
    }

    // Close the file
    close(fd);

    // Send the new employee ID to the client via the socket descriptor
    if (write(sd, &record.managerID, sizeof(record.managerID)) == -1) {
        perror("Error sending manager ID to client");
        return ;
    }

}
int checkNumberOfCustomers()
{
        int fd = open("./data/customer.data", O_RDWR, 0744);
        if (fd ==-1){
                return 0;
        }

        int count=lseek(fd,0,SEEK_END)/sizeof(struct customer);
        return count;
}

struct customer retriveCustomer(int i){
        int fd=open("./data/customer.data",O_RDWR,0744);
        
        struct customer temp;

        lseek(fd,i*sizeof(struct customer),SEEK_SET);

        read(fd,&temp,sizeof(temp));
        close(fd);

        return temp;
}


int checkNumberOfEmployee()
{
        int fd = open("./data/employee.data", O_RDWR, 0744);
        if (fd ==-1){
                return 0;
        }

        int count=lseek(fd,0,SEEK_END)/sizeof(struct employee);
        return count;
}
struct employee retriveEmployee(int i){
        int fd=open("./data/employee.data",O_RDWR,0744);
        
        struct employee temp;

        lseek(fd,i*sizeof(struct employee),SEEK_SET);

        read(fd,&temp,sizeof(temp));
        close(fd);

        return temp;
}

int checkNumberOfManager()
{
        int fd = open("./data/manager.data", O_RDWR, 0744);
        if (fd ==-1){
                return 0;
        }

        int count=lseek(fd,0,SEEK_END)/sizeof(struct manager);
        return count;
}


struct manager retrieveManager(int i){
        int fd=open("./data/manager.data",O_RDWR,0744);
        
        struct manager temp;

        lseek(fd,i*sizeof(struct manager),SEEK_SET);

        read(fd,&temp,sizeof(temp));
        close(fd);

        return temp;
}
bool adminmodifyPassword(struct admin currUser, int id)
{
	int fd = open("./data/admin.data", O_RDWR, 0744);
	struct admin endUser;
	bool result = false;

	if (fd == -1)
	{
		perror("Error opening admin data file");
		return false;
	}

	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0; // Lock the entire file
	lock.l_pid = getpid();

	// Lock the file for writing
	if (fcntl(fd, F_SETLKW, &lock) == -1)
	{
		perror("Error locking the file");
		close(fd);
		return false;
	}

	
	while (read(fd, &endUser, sizeof(struct admin)) > 0)
	{
		if (endUser.adminID == id)
		{
			
				if (strlen(currUser.password) > 0)
				{
					strcpy(endUser.password, currUser.password);
				}

			// Move the file pointer back to the position of this record
			lseek(fd, (-1) * sizeof(struct admin), SEEK_CUR);

			// Write the modified customer record back to the file
			int j = write(fd, &endUser, sizeof(struct admin));
			if (j != sizeof(struct admin))
			{
				printf("Error writing the updated password.\n");
				result = false;
			}
			else
			{
				result = true;
				printf("Admin password updated successfully.\n");
			}
			break;
		}
	}

	if (!result)
	{
		printf("Admin ID not found.\n");
	}

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);
	return result;
}

bool modifyCustomer(struct customer currUser, int sd) {
    int fd = open("./data/customer.data", O_RDWR, 0744);
    struct customer endUser;
    bool result = false;

    if (fd == -1) {
        perror("Error opening customer data file");
        return false;
    }
    int i=currUser.customerID;
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i-1) * sizeof(struct customer);;
    lock.l_len = sizeof(struct customer);
    lock.l_pid = getpid();

    // Lock the file for writing
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error locking the file");
        close(fd);
        return false;
    }

    // Search for the customer by ID
    while (read(fd, &endUser, sizeof(struct customer)) > 0) {
        
        if (endUser.customerID == i) {
            
            
                    if (strlen(currUser.name) > 0) {
                        strcpy(endUser.name, currUser.name);
                    }
                 
                
                    if (strlen(currUser.password) > 0) {
                        strcpy(endUser.password, currUser.password);
                    
                    

   
                    endUser.status = currUser.status;
                  
                
            }

            // Move the file pointer back to the position of this record
            lseek(fd, (-1) * sizeof(struct customer), SEEK_CUR);

            // Write the modified customer record back to the file
            int j = write(fd, &endUser, sizeof(struct customer));
            if (j != sizeof(struct customer)) {
                printf("Error writing the updated customer details.\n");
                result = false;
            } else {
                result = true;
                printf("Customer details updated successfully.\n");
            }
            break;
        }
    }

    if (!result) {
        printf("Customer ID not found.\n");
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return result;
}
bool modifyEmployee(struct employee currUser, int sd) {
    int fd = open("./data/employee.data", O_RDWR, 0744);
    struct employee endUser;
    bool result = false;

    if (fd == -1) {
        perror("Error opening customer data file");
        return false;
    }
    int i=currUser.employeeID;
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i-1) * sizeof(struct employee);;
    lock.l_len = sizeof(struct employee);
    lock.l_pid = getpid();

    // Lock the file for writing
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error locking the file");
        close(fd);
        return false;
    }

    while (read(fd, &endUser, sizeof(struct employee)) > 0) {
        
        if (endUser.employeeID == i) {
            
            
                    if (strlen(currUser.name) > 0) {
                        strcpy(endUser.name, currUser.name);
                    }
                 
                
                    if (strlen(currUser.password) > 0) {
                        strcpy(endUser.password, currUser.password);
                    
                    

   
                    endUser.status = currUser.status;
                  
                
            }

            // Move the file pointer back to the position of this record
            lseek(fd, (-1) * sizeof(struct employee), SEEK_CUR);

            
            int j = write(fd, &endUser, sizeof(struct employee));
            if (j != sizeof(struct employee)) {
                printf("Error writing the updated customer details.\n");
                result = false;
            } else {
                result = true;
                printf("Employee details updated successfully.\n");
            }
            break;
        }
    }

    if (!result) {
        printf("Employee ID not found.\n");
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return result;
}

#endif