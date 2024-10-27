#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/file.h>
#include "./structures/customer.h"
#include "./structures/manager.h"
#include "./structures/employee.h"
#include "./structures/admin.h"
#include "./structures/feedback.h"
#include "./actions/customer_functions.h"
#include "./actions/employee_functions.h"
#include "./actions/admin_functions.h"
#include "./actions/manager_functions.h"
#include "./structures/feedback.h"
int option;
int id;

bool authenticate_customer(struct customer currUser)
{

    int i = currUser.customerID - 1;
    int fd = open("./data/customer.data", O_RDONLY, 0744);
    bool result;
    struct customer temp;

    int fl1;
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(struct customer);
    lock.l_len = sizeof(struct customer);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (i) * sizeof(struct customer), SEEK_SET);
    read(fd, &temp, sizeof(struct customer));
    if (!strcmp(temp.password, currUser.password) && temp.status == 1)
        result = true;
    else
        result = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return result;
}

bool authenticate_employee(struct employee currUser)
{

    int i = currUser.employeeID - 1;
    int fd = open("./data/employee.data", O_RDONLY, 0744);
    bool result;
    struct employee temp;

    int fl1;
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(struct employee);
    lock.l_len = sizeof(struct employee);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);
    lseek(fd, (i) * sizeof(struct employee), SEEK_SET);
    read(fd, &temp, sizeof(struct employee));

    if (!strcmp(temp.password, currUser.password) && temp.status == 1)
        result = true;
    else
        result = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return result;
}

bool authenticate_manager(struct manager currUser)
{

    int i = currUser.managerID - 1;
    int fd = open("./data/manager.data", O_RDONLY, 0744);
    bool result;
    struct manager temp;

    int fl1;
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(struct manager);
    lock.l_len = sizeof(struct manager);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (i) * sizeof(struct manager), SEEK_SET);
    read(fd, &temp, sizeof(struct manager));
    if (!strcmp(temp.password, currUser.password) && temp.status == 1)
        result = true;
    else
        result = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return result;
}

bool authenticate_admin(struct admin currUser)
{

    int i = currUser.adminID - 1;
    int fd = open("./data/admin.data", O_RDONLY, 0744);
    bool result;
    struct admin temp;

    int fl1;
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(struct admin);
    lock.l_len = sizeof(struct admin);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (i) * sizeof(struct admin), SEEK_SET);
    read(fd, &temp, sizeof(struct admin));
    if (!strcmp(temp.password, currUser.password))
        result = true;
    else
        result = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return result;
}

void serverTask(int sd)
{
    read(sd, &option, sizeof(option));

    while (1)
    {
        if (option == 1)
        {
            struct customer currUser;
            read(sd, &currUser, sizeof(struct customer));
            bool result1;
            result1 = authenticate_customer(currUser);
            write(sd, &result1, sizeof(result1)); // to client
            if (result1 == true)
            {
                id = currUser.customerID;
                break;
            }
        }

        else if (option == 2)
        {
            struct employee currEmployee;
            read(sd, &currEmployee, sizeof(struct employee));
            bool result2;
            result2 = authenticate_employee(currEmployee);
            write(sd, &result2, sizeof(result2)); // to client
            if (result2 == true)
            {
                id = currEmployee.employeeID;
                break;
            }
        }
        else if (option == 3)
        {
            struct manager currManager;
            read(sd, &currManager, sizeof(struct manager));
            bool result3;
            result3 = authenticate_manager(currManager);
            write(sd, &result3, sizeof(result3)); // to client
            if (result3 == true)
            {
                id = currManager.managerID;
                break;
            }
        }
        else if (option == 4)
        {
            struct admin currAdmin;
            read(sd, &currAdmin, sizeof(struct admin));
            bool result4;
            result4 = authenticate_admin(currAdmin);
            write(sd, &result4, sizeof(result4)); // to client
            if (result4 == true)
            {
                id = currAdmin.adminID;
                break;
            }
        }
    }
    while (1)
    {

        if (option == 1)
        {
            int choice;
            read(sd, &choice, sizeof(choice));
            if (choice == 1)
            {
                float balance = getBalance(id);
                write(sd, &balance, sizeof(balance));
            }
            else if (choice == 2)
            {
                float amount;
                read(sd, &amount, sizeof(amount));
                bool result = depositMoney(id, amount);
                write(sd, &result, sizeof(result));
            }
            else if (choice == 3)
            {
                float amount;
                read(sd, &amount, sizeof(amount));
                bool result = withdrawMoney(id, amount);
                write(sd, &result, sizeof(result));
            }
            else if (choice == 4)
            {
                int toID;
                int customerID;
                float amount;
                bool success;
                read(sd, &customerID, sizeof(customerID));
                read(sd, &toID, sizeof(toID));
                read(sd, &amount, sizeof(amount));
                success = transferMoney(customerID, toID, amount);
                write(sd, &success, sizeof(success));
            }
            else if(choice==5){
                struct loan newLoan;
                read(sd,&newLoan,sizeof(newLoan));

                bool result =addLoan(newLoan,sd);
                write(sd,&result,sizeof(result));
            }
            else if (choice == 6)
            {
                struct customer currUser;
                read(sd, &currUser, sizeof(currUser));
                bool result = modifyPassword(currUser, id);

                write(sd, &result, sizeof(result));
            }
            else if (choice == 8) {
    struct feedback fb;
    // Read the feedback structure sent by the client
    if (read(sd, &fb, sizeof(fb)) > 0) {
        bool result = addFeedbackToFile(fb);
        // Send the result of the operation to the client
        write(sd, &result, sizeof(result));
    } else {
        printf("Error reading feedback from client\n");
    }
}

            else if(choice==9)
            {
                int loanid;
                read(sd,&loanid,sizeof(loanid));
                viewloanid(sd,loanid,id);
            }
            else if (choice == 10)
            {
                serverTask(sd);
            }
            else if (choice == 11)
            {
                break;
            }
        }

        else if (option == 2)
        {
            int choice;
            read(sd, &choice, sizeof(choice));
            if (choice == 1)
            {
                struct customer currUser;
                read(sd, &currUser, sizeof(currUser));
                createCustomer(currUser, sd);
            }
            else if(choice==2)
            {
                struct customer currUser;
            
                
                read(sd, &currUser, sizeof(currUser));
                bool result = modifyCustomer(currUser, sd);
                write(sd, &result, sizeof(result));
            }
            else if(choice==3){
                int loanId;
                int action;
                int iD;

                read(sd,&loanId,sizeof(loanId));
                read(sd,&action,sizeof(action));
                read(sd,&iD,sizeof(iD));
                bool result= processLoanApplication(loanId,iD,action);

                write(sd,&result,sizeof(result));
            }

            else if(choice==4)
            {
                int ID;
                read(sd,&ID,sizeof(ID));
                int numberOfLoanApplications= checkNumberOfLoanApplications();
                write(sd,&numberOfLoanApplications,sizeof(numberOfLoanApplications));

                int numberOfassLoanApplications= checkNumberOfassignedLoanApplications(ID);
                write(sd,&numberOfassLoanApplications,sizeof(numberOfassLoanApplications));


                struct loan currLoanRecord;
                
                    if(numberOfassLoanApplications>0)
                    viewAssignedLoanApplications(currLoanRecord,ID,sd);
                    
                
                
            }
            else if(choice==6)
            {
                int ID;
                read(sd, &ID, sizeof(ID));
                struct employee currUser;
                read(sd, &currUser, sizeof(currUser));
                bool result = empadminmodifyPassword(currUser, ID);

                write(sd, &result, sizeof(result));
            }
            else if(choice==7)
            {
                serverTask(sd);
            }
            else if(choice==8)
            {
                break;
            }
        }
        else if(option==3)
        {
            int choice;
            read(sd, &choice, sizeof(choice));
            if(choice==1)
            {
                int id1;
                bool result = false;
                read(sd, &id1, sizeof(id1));

                int option;
                read(sd, &option, sizeof(option));
                int count = checkNumberOfCustomers();
                if (id1 <= count)
                {
                    changeCustomerStatus(id1, option);
                    result = true;
                }
                write(sd, &result, sizeof(result));
            }
            else if(choice==2)
            {
                int employeeId;
                int loanId;
                read(sd,&employeeId,sizeof(employeeId));
                read(sd,&loanId,sizeof(loanId));

                bool result= assignLoanApplication(employeeId,loanId);

                write(sd,&result,sizeof(result));
            }
            else if(choice==3)
            {
               struct feedback currUser;
                    int count1 = checknumberoffeedback();
                    write(sd, &count1, sizeof(count1));
                    for (int i = 0; i < count1; i++)
                    {
                        currUser = retrivefeedback(i);
                        write(sd, &currUser, sizeof(currUser));
                    }
            }
            else if(choice ==4)
            {
                int ID;
                read(sd, &ID, sizeof(ID));
                struct manager currUser;
                read(sd, &currUser, sizeof(currUser));
                bool result = manadminmodifyPassword(currUser, ID);

                write(sd, &result, sizeof(result));
            }
            else if(choice==5)
            {
            serverTask(sd);
            }
        }


        else if (option == 4)
        {
            int choice;
            read(sd, &choice, sizeof(choice));
            if (choice == 1)
            {
                struct employee currUser;
                read(sd, &currUser, sizeof(currUser));
                createEmployee(currUser, sd);
            }
            else if(choice==2)
            {
                int opt;
                read(sd, &opt, sizeof(opt));
                if(opt==1)
                {
                struct customer currUser;
            
                
                read(sd, &currUser, sizeof(currUser));
                bool result = modifyCustomer(currUser, sd);
                write(sd, &result, sizeof(result));
                }

                else if(opt==2)
                {
                    struct employee currUser;
            
                
                read(sd, &currUser, sizeof(currUser));
                bool result = modifyEmployee(currUser, sd);
                write(sd, &result, sizeof(result));
                }
            }
            else if (choice == 4)
            {
                int ID;
                read(sd, &ID, sizeof(ID));
                struct admin currUser;
                read(sd, &currUser, sizeof(currUser));
                bool result = adminmodifyPassword(currUser, ID);

                write(sd, &result, sizeof(result));
            }
            else if (choice == 5)
            {
                int option;
                read(sd, &option, sizeof(option));
                switch (option)
                {
                case 1:
                    struct customer currUser;
                    int count1 = checkNumberOfCustomers();
                    write(sd, &count1, sizeof(count1));
                    for (int i = 0; i < count1; i++)
                    {
                        currUser = retriveCustomer(i);
                        write(sd, &currUser, sizeof(currUser));
                    }
                    break;

                case 2:
                    struct employee currEmp;
                    int count2 = checkNumberOfEmployee();
                    write(sd, &count2, sizeof(count2));
                    for (int i = 0; i < count2; i++)
                    {
                        currEmp = retriveEmployee(i);
                        write(sd, &currEmp, sizeof(currEmp));
                    }
                    break;

                case 3:
                    struct manager currManager;
                    int count3 = checkNumberOfManager();
                    write(sd, &count3, sizeof(count3));
                    for (int i = 0; i < count3; i++)
                    {
                        currManager = retrieveManager(i);
                        write(sd, &currManager, sizeof(currManager));
                    }
                    break;
                }
            }
            else if(choice==6)
            {
                struct manager currUser;
                read(sd, &currUser, sizeof(currUser));
                createmanager(currUser, sd);
            }
            else if (choice == 7)
            {
                serverTask(sd);
            }
            else if (choice == 8)
            {
                exit(0);
            }
        }
    }
}
int main()
{
    struct sockaddr_in server, client;
    int sd, nsd, clientLen;
    bool result;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5555);
   
    bind(sd, (struct sockaddr *)&server, sizeof(server));

    listen(sd, 5);
    
    printf("Welcome to ");
    printf("IIITBank\n");

    printf("Waiting for Client to connect\n");
    while (1)
    {
        clientLen = sizeof(client);
        nsd = accept(sd, (struct sockaddr *)&client, &clientLen);

        write(1, "Connected to the client\n", sizeof("Connected to the client\n"));
        if (!fork())
        {
            close(sd);
            serverTask(nsd);
            exit(0);
        }
        else
        {
            close(nsd);
        }
    }
    return 0;
}