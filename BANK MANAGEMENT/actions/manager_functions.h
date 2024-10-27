#ifndef MANAGER_FUNCTION
#define MANAGER_FUNCTION

void changeCustomerStatus(int id1, int option)
{
        int fd = open("./data/customer.data", O_RDWR, 0744);
        struct customer temp;

        lseek(fd, (id1-1 ) * sizeof(struct customer), SEEK_SET);

        read(fd, &temp, sizeof(temp));
        temp.status = option;
        lseek(fd,(id1-1 ) * sizeof(struct customer), SEEK_SET);
        write(fd, &temp, sizeof(struct customer));
        close(fd);
}
int checknumberoffeedback()
{
    int fd = open("./data/feedback.data", O_RDWR, 0744);
        if (fd ==-1){
                return 0;
        }

        int count=lseek(fd,0,SEEK_END)/sizeof(struct feedback);
        return count;
}
struct feedback retrivefeedback(int i){
        int fd=open("./data/feedback.data",O_RDWR,0744);
        
        struct feedback temp;

        lseek(fd,i*sizeof(struct feedback),SEEK_SET);

        read(fd,&temp,sizeof(temp));
        close(fd);

        return temp;
}
bool assignLoanApplication(int employeeId, int loanId)
{
        int fd = open("./data/loan.data", O_RDWR, 0744);
        if (fd == -1)
        {
                perror("Error opening loan data file");
                return false;
        }

        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (loanId-1);
        lock.l_len = sizeof(struct loan);
        lock.l_pid = getpid();

        // Lock the file for writing
        if (fcntl(fd, F_SETLKW, &lock) == -1)
        {
                perror("Error locking the file");
                close(fd);
                return false;
        }

        struct loan loanRecord;
        bool found =false;
        lseek(fd,0 ,SEEK_SET);
        while(read(fd,&loanRecord,sizeof(struct loan))>0){
                if(loanRecord.loanID==loanId){
                        loanRecord.assignedEmployeeID=employeeId;
                        lseek(fd,-sizeof(struct loan),SEEK_CUR);
                        int j=write(fd,&loanRecord,sizeof(struct loan));
                        found=true;
                        break;
                }

        }
        // Unlock the file
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return found;

}


bool manadminmodifyPassword(struct manager currUser, int id)
{
	int fd = open("./data/manager.data", O_RDWR, 0744);
	struct manager endUser;
	bool result = false;

	if (fd == -1)
	{
		perror("Error opening manager data file");
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

	
	while (read(fd, &endUser, sizeof(struct manager)) > 0)
	{
		if (endUser.managerID == id)
		{
			
				if (strlen(currUser.password) > 0)
				{
					strcpy(endUser.password, currUser.password);
				}

			// Move the file pointer back to the position of this record
			lseek(fd, (-1) * sizeof(struct manager), SEEK_CUR);

			// Write the modified customer record back to the file
			int j = write(fd, &endUser, sizeof(struct manager));
			if (j != sizeof(struct manager))
			{
				printf("Error writing the updated password.\n");
				result = false;
			}
			else
			{
				result = true;
				printf("Manager password updated successfully.\n");
			}
			break;
		}
	}

	if (!result)
	{
		printf("Manager ID not found.\n");
	}

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);
	return result;
}


#endif