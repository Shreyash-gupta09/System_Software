#ifndef EMPLOYEE_FUNCTION
#define EMPLOYEE_FUNCTION

void createCustomer(struct customer record, int sd)
{
        int fd;
        ssize_t bytesRead;
        struct customer lastcust;

        // Open the employee file (create if it doesn't exist)
        fd = open("./data/customer.data", O_RDWR | O_CREAT, 0644);
        if (fd < 0)
        {
                perror("Error opening customer file");
                return;
        }

        // Apply a write lock to prevent race conditions
        if (flock(fd, LOCK_EX) < 0)
        {
                perror("Error locking customer file");
                close(fd);
                return;
        }

        // Set file pointer to the end of the file
        lseek(fd, 0, SEEK_END);

        if (lseek(fd, 0, SEEK_CUR) == 0)
        {
                record.customerID = 1;
        }
        else
        {
                // Move the file pointer to the last record
                lseek(fd, -sizeof(struct customer), SEEK_END);
                
                bytesRead = read(fd, &lastcust, sizeof(struct customer));
                if (bytesRead == -1)
                {
                        perror("Error reading customer file");
                        close(fd);
                        return;
                }
                
                record.customerID = lastcust.customerID + 1;
        }

        
        record.status = true;

        // Write the new employee record at the end of the file
        if (write(fd, &record, sizeof(struct customer)) == -1)
        {
                perror("Error writing to customer file");
                close(fd);
                return;
        }

        // Unlock the file
        if (flock(fd, LOCK_UN) < 0)
        {
                perror("Error unlocking customer file");
                close(fd);
                return;
        }

        // Close the file
        close(fd);

        if (write(sd, &record.customerID, sizeof(record.customerID)) == -1)
        {
                perror("Error sending customer ID to client");
                return;
        }
}
bool addLoan(struct loan newLoan,int sd){
    int fd= open("./data/loan.data",O_RDWR | O_CREAT ,0744);
    if(fd==-1){
        perror("Error opening loan data file");
        return false;
    }

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    // Lock the file
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error locking the file");
        close(fd);
        return false;
    }

    //find the last loan id to assign a new one
    struct loan lastLoan;
    lseek(fd,-sizeof(struct loan),SEEK_END);
    if(read(fd,&lastLoan,sizeof(struct loan))>0){
        newLoan.loanID=lastLoan.loanID+1;
    }
    else{
        newLoan.loanID=1;
    }

    int j=write(fd,&newLoan,sizeof(struct loan));
    bool result= (j==sizeof(struct loan));

    // Unlock the file
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    write(sd,&newLoan.loanID,sizeof(newLoan.loanID));
    return result;
}

int checkNumberOfLoanApplications(){
    int fd = open("./data/loan.data", O_RDONLY, 0744);
    if (fd == -1) {
        perror("Error opening loan data file");
        return 0;
    }

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // Lock entire file
    lock.l_pid = getpid();

    // Lock the file for reading
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error locking the file");
        close(fd);
        return 0;
    }

    int count=0;

    struct loan loanRecord;
    lseek(fd, 0, SEEK_SET);
    while (read(fd, &loanRecord, sizeof(struct loan)) > 0) {
  
            count++;
        
    }

    // Unlock the file
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return count;

}
int checkNumberOfassignedLoanApplications(int id){
    int fd = open("./data/loan.data", O_RDONLY, 0744);
    if (fd == -1) {
        perror("Error opening loan data file");
        return 0;
    }

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // Lock entire file
    lock.l_pid = getpid();

    // Lock the file for reading
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error locking the file");
        close(fd);
        return 0;
    }

    int count=0;

    struct loan loanRecord;
    lseek(fd, 0, SEEK_SET);
    while (read(fd, &loanRecord, sizeof(struct loan)) > 0) {
            if(loanRecord.assignedEmployeeID==id)
            count++;
        
    }

    // Unlock the file
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return count;

}
void viewAssignedLoanApplications(struct loan currLoanRecord,int id,int sd){
    int fd = open("./data/loan.data", O_RDONLY, 0744);
    if (fd == -1) {
        perror("Error opening loan data file");
    }

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // Lock entire file
    lock.l_pid = getpid();

    // Lock the file for reading
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error locking the file");
        close(fd);
    }

    struct loan loanRecord;
    lseek(fd, 0, SEEK_SET);
    while (read(fd, &loanRecord, sizeof(struct loan)) > 0) {
        if (loanRecord.assignedEmployeeID == id) {
            currLoanRecord.loanID=loanRecord.loanID;
            currLoanRecord.amount=loanRecord.amount;
            currLoanRecord.customerID=loanRecord.customerID;
            currLoanRecord.status=loanRecord.status;
            currLoanRecord.duration=loanRecord.duration;
            write(sd,&currLoanRecord,sizeof(currLoanRecord));
        }
    }

    // Unlock the file
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);

    
}
bool processLoanApplication(int loanId,int id,int action){
    int fd = open("./data/loan.data", O_RDWR, 0744);
    if (fd == -1) {
        perror("Error opening loan data file");
        return false;
    }

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // Lock entire file
    lock.l_pid = getpid();

    // Lock the file for writing
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error locking the file");
        close(fd);
        return false;
    }

    struct loan loanRecord;
    bool found=false;

    lseek(fd,0,SEEK_SET);
    while(read(fd,&loanRecord,sizeof(struct loan))>0){
        if(loanRecord.loanID==loanId && loanRecord.assignedEmployeeID==id && loanRecord.status==0){
            loanRecord.status=action; //1 for approve -1 to reject
            if(action==1)
            {
                depositMoney(loanRecord.customerID,loanRecord.amount);
            }
            lseek(fd,-sizeof(struct loan),SEEK_CUR);
            int j=write(fd,&loanRecord,sizeof(loanRecord));
            found=(j==sizeof(struct loan));
            break;
        }
    }
     // Unlock the file
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return found;
}
bool empadminmodifyPassword(struct employee currUser, int id)
{
	int fd = open("./data/employee.data", O_RDWR, 0744);
	struct employee endUser;
	bool result = false;

	if (fd == -1)
	{
		perror("Error opening employee data file");
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

	
	while (read(fd, &endUser, sizeof(struct employee)) > 0)
	{
		if (endUser.employeeID == id)
		{
			
				if (strlen(currUser.password) > 0)
				{
					strcpy(endUser.password, currUser.password);
				}

			// Move the file pointer back to the position of this record
			lseek(fd, (-1) * sizeof(struct employee), SEEK_CUR);

			// Write the modified customer record back to the file
			int j = write(fd, &endUser, sizeof(struct employee));
			if (j != sizeof(struct employee))
			{
				printf("Error writing the updated password.\n");
				result = false;
			}
			else
			{
				result = true;
				printf("Employee password updated successfully.\n");
			}
			break;
		}
	}

	if (!result)
	{
		printf("Employee ID not found.\n");
	}

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);
	return result;
}

#endif