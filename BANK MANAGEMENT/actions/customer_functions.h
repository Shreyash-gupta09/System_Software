#ifndef CUSTOMER_FUNCTION
#define CUSTOMER_FUNCTION

float getBalance(int ID)
{
	int i = ID;
	float result;
	int fd = open("./data/customer.data", O_RDONLY, 0744);
	struct customer temp;

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (i - 1) * sizeof(struct customer);
	lock.l_len = sizeof(struct customer);
	lock.l_pid = getpid();

	fl1 = fcntl(fd, F_SETLKW, &lock);

	lseek(fd, (i-1) * sizeof(struct customer), SEEK_SET);
	read(fd, &temp, sizeof(struct customer));
	if (temp.status == true)
		result = temp.balance;
	else
		result = 0;

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);
	return result;
}

bool depositMoney(int id, float amount)
{
	int i = id;
	int fd = open("./data/customer.data", O_RDWR, 0744);
	bool result;
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (i-1) * sizeof(struct customer);
	lock.l_len = sizeof(struct customer);
	lock.l_pid = getpid();

	fl1 = fcntl(fd, F_SETLKW, &lock);

	struct customer currUser;
	lseek(fd, (i-1) * sizeof(struct customer), SEEK_SET);
	read(fd, &currUser, sizeof(struct customer));

	if (currUser.status == true)
	{
		currUser.balance += amount;
		lseek(fd, sizeof(struct customer) * (-1), SEEK_CUR);
		write(fd, &currUser, sizeof(struct customer));
		result = true;
	}
	else
		result = false;

	lock.l_type = F_UNLCK;

	fcntl(fd, F_SETLK, &lock);

	close(fd);
	return result;
}

bool withdrawMoney(int id, float amount)
{
	int i = id;
	int fd = open("./data/customer.data", O_RDWR, 0744);
	bool result;
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (i-1) * sizeof(struct customer);
	lock.l_len = sizeof(struct customer);
	lock.l_pid = getpid();

	fl1 = fcntl(fd, F_SETLKW, &lock);

	struct customer currUser;
	lseek(fd, (i-1) * sizeof(struct customer), SEEK_SET);
	read(fd, &currUser, sizeof(struct customer));

	if (currUser.status == true && currUser.balance >= amount)
	{
		currUser.balance -= amount;
		lseek(fd, sizeof(struct customer) * (-1), SEEK_CUR);
		write(fd, &currUser, sizeof(struct customer));
		result = true;
	}
	else
		result = false;
	lock.l_type = F_UNLCK;

	fcntl(fd, F_SETLK, &lock);

	close(fd);
	return result;
}
bool transferMoney(int fromID, int toID, float amount) {
    int fd = open("./data/customer.data", O_RDWR, 0744);
    bool result = false;

    struct customer fromUser, toUser;
    
    // Lock the file for the from-user account
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (fromID -1) * sizeof(struct customer);
    lock.l_len = sizeof(struct customer);
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, &lock);
    
    lseek(fd, (fromID-1 ) * sizeof(struct customer), SEEK_SET);
    read(fd, &fromUser, sizeof(struct customer));

    // Lock the file for the to-user account
    lock.l_start = (toID-1) * sizeof(struct customer);
    fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (toID -1) * sizeof(struct customer), SEEK_SET);
    read(fd, &toUser, sizeof(struct customer));

    // Perform the transfer if the from-user has enough balance and both accounts are active
    if (fromUser.status == true && toUser.status == true && fromUser.balance >= amount) {
        fromUser.balance -= amount;
        toUser.balance += amount;

        lseek(fd, (toID -1) * sizeof(struct customer), SEEK_SET);
        write(fd, &toUser, sizeof(struct customer));
        lseek(fd, (fromID-1 ) * sizeof(struct customer), SEEK_SET);
        write(fd, &fromUser, sizeof(struct customer));

        result = true;
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return result;
}
bool applyForLoan(int id, float amount) {
    int i = id;
    int fd = open("./data/loan.data", O_WRONLY | O_APPEND, 0744);
    bool result = false;

    struct loanApplication {
        int customerID;
        float amount;
        int status; // 0 = pending, 1 = approved, -1 = rejected
    } newLoan;

    newLoan.customerID = i;
    newLoan.amount = amount;
    newLoan.status = 0; // Loan is pending approval

    if (write(fd, &newLoan, sizeof(struct loanApplication)) > 0) {
        result = true;
    }

    close(fd);
    return result;
}
bool modifyPassword(struct customer currUser, int id)
{
	int fd = open("./data/customer.data", O_RDWR, 0744);
	struct customer endUser;
	bool result = false;

	if (fd == -1)
	{
		perror("Error opening customer data file");
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

	// Search for the customer by ID
	while (read(fd, &endUser, sizeof(struct customer)) > 0)
	{
		if (endUser.customerID == id)
		{
			// Customer found, update details based on the choice
				if (strlen(currUser.password) > 0)
				{
					strcpy(endUser.password, currUser.password);
				}

			// Move the file pointer back to the position of this record
			lseek(fd, (-1) * sizeof(struct customer), SEEK_CUR);

			// Write the modified customer record back to the file
			int j = write(fd, &endUser, sizeof(struct customer));
			if (j != sizeof(struct customer))
			{
				printf("Error writing the updated password.\n");
				result = false;
			}
			else
			{
				result = true;
				printf("Customer password updated successfully.\n");
			}
			break;
		}
	}

	if (!result)
	{
		printf("Customer ID not found.\n");
	}

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);
	return result;
}
bool addFeedbackToFile(struct feedback fb) {
    int fd = open("./data/feedback.data", O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return false;
    }

    // Lock the file
    if (flock(fd, LOCK_EX) == -1) {
        perror("Error locking file");
        close(fd);
        return false;
    }

    // Write the feedback to the end of the file
    ssize_t result = write(fd, &fb, sizeof(fb));
    if (result == -1) {
        perror("Error writing to file");
        flock(fd, LOCK_UN); // Unlock before closing
        close(fd);
        return false;
    }

    // Unlock the file
    if (flock(fd, LOCK_UN) == -1) {
        perror("Error unlocking file");
    }

    // Close the file
    close(fd);
    return true;
}


void viewloanid(int sd,int loanid,int id)
{
	struct loan temp;
	int n=-2;
	int fd = open("./data/loan.data", O_RDWR , 0644);
	struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (loanid -1) * sizeof(struct loan);
    lock.l_len = sizeof(struct loan);
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, &lock);

	lseek(fd, (loanid-1) * sizeof(struct loan), SEEK_SET);
	read(fd, &temp, sizeof(struct loan));
	if(temp.customerID==id)
	write(sd,&temp.status,sizeof(temp.status));
	else
	write(sd,&n,sizeof(n));
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);
}


#endif