#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include "./structures/customer.h"
#include "./structures/manager.h"
#include "./structures/employee.h"
#include "./structures/admin.h"
#include "./structures/feedback.h"

int option;
void chooseOption(int);

void showMenu(int sd)
{
    if (option == 1)
    {       
            printf("============================================================\n");
            printf("1. View Balance\n");
            printf("2. Deposit Money\n");
            printf("3. Withdraw Money\n");
            printf("4. Transfer Money\n");
            printf("5. Apply for loan\n");
            printf("6. Change password\n");
            printf("7. View Transaction history\n");
            printf("8. Add Feedback\n");
            printf("9. View Loan Status\n");
            printf("10. Logout\n");
            printf("11. Exit\n");
            printf("============================================================\n");
            int choice;
            scanf("%d", &choice);
            write(sd, &choice, sizeof(choice));

            if (choice == 1)
            {
                float balance;
                read(sd, &balance, sizeof(balance));
                printf("The balance is:%f\n", balance);
            }

            else if (choice == 2)
            {
                printf("Enter the amount of money to deposit\n");
                float amount;
                scanf("%f", &amount);
                write(sd, &amount, sizeof(amount));
                bool result;
                read(sd, &result, sizeof(result));
                if (result)
                    printf("Money deposited succesfully\n");
                else
                    printf("Money not deposited\n");
            }
            else if (choice == 3)
            {
                printf("Enter the amount of money to withdraw\n");
                float amount;
                scanf("%f", &amount);
                write(sd, &amount, sizeof(amount));
                bool result;
                read(sd, &result, sizeof(result));
                if (result)
                    printf("Money withdrawn succesfully\n");
                else
                    printf("Insufficient balance\n");
            }
            else if (choice == 4)
            {
                int customerID;
                int toID;
                float amount;
                bool success;
                printf("Enter your Customer ID: ");
                scanf("%d", &customerID);
                printf("Enter recipient Customer ID: ");
                scanf("%d", &toID);
                printf("Enter amount to transfer: ");
                scanf("%f", &amount);
                write(sd, &customerID, sizeof(customerID));
                write(sd, &toID, sizeof(toID));
                write(sd, &amount, sizeof(amount));
                read(sd, &success, sizeof(success));
                if (success)
                    printf("Transfer successful.\n");
                else
                    printf("Transfer failed.\n");
            }
             else if(choice==5){
                struct loan newLoan;
                printf("Enter your customrID:\n");
                scanf("%d",&newLoan.customerID);

                printf("Enter Loan amount:\n");
                scanf("%f",&newLoan.amount);

                printf("Enter loan duration in months:\n");
                scanf("%d",&newLoan.duration);

                
                newLoan.status=0; //pending

                write(sd,&newLoan,sizeof(newLoan));
                int loanid;
                read(sd,&loanid,sizeof(loanid));
                bool result;
                read(sd,&result,sizeof(result));

                if(result) printf("Loan application submitted succesfully with id : %d\n",loanid);
                else printf("Failed to submit loan application\n");
                
            }
            else if (choice == 6)
            {
                struct customer currUser;
                printf("Enter the new password\n");
                char *newPass = getpass("");
                strcpy(currUser.password, newPass);
                write(sd, &currUser, sizeof(currUser));
                bool result;
                read(sd, &result, sizeof(result));
                if (result)
                    printf("Password modified succesfully\n");
                else
                    printf("Failure in updating password\n");
            }
            else if (choice == 8) {
    struct feedback currUser;
    printf("Enter customer ID: ");
    scanf("%d", &currUser.customerID);
    
    // Clear the input buffer
    getchar(); // To consume the leftover newline from the previous input
    
    printf("Enter the feedback (max 50 characters): ");
    fgets(currUser.feedbackText, sizeof(currUser.feedbackText), stdin);
    
    // Remove trailing newline if fgets captured it
    currUser.feedbackText[strcspn(currUser.feedbackText, "\n")] = '\0';
    
    // Send the feedback structure to the server
    write(sd, &currUser, sizeof(struct feedback));

    bool result;
    // Read the server's response
    if (read(sd, &result, sizeof(result)) > 0) {
        if (result) {
            printf("Feedback added successfully\n");
        } else {
            printf("Failed to add feedback\n");
        }
    } else {
        printf("Error reading server response\n");
    }
}
            else if(choice==9)
            {   
                int loanid;
                printf("Enter Loan ID you want to check staus of\n");   
                scanf("%d",&loanid);
                write(sd,&loanid,sizeof(loanid));
                int status;
                read(sd,&status,sizeof(status));
                if(status==-2)
                printf("No loans associated to you with this loan id\n");
                else
                printf("Status = %d\n",status);

            }
            else if (choice == 10)
            {
                chooseOption(sd);
            }
            else if (choice == 11)
            {
                write(sd, &choice, sizeof(int));
                printf("Bye Bye!\n");
                exit(0);
            }
            else
            {
                printf("Invalid option\n");
            }
        showMenu(sd);
        printf("\n");
    }
    else if (option == 2)
    {
        printf("============================================================\n");
        printf("1. Add new customer \n");
        printf("2. Modify Customer details\n");
        printf("3. Process loan applications\n");
        printf("4. View Assigned Loan appications\n");
        printf("5. View customer transactions\n");
        printf("6. Change password\n");
        printf("7. Logout\n");
        printf("8. Exit\n");
        printf("============================================================\n");
        int choice;
        scanf("%d", &choice);
        write(sd, &choice, sizeof(choice));

        if (choice == 1)
        {
            struct customer currUser;
            printf("Enter the name of customer\n");
            scanf("%s", currUser.name);
            printf("Enter the password\n");
            char *pass = getpass("");
            strcpy(currUser.password, pass);
            write(sd, &currUser, sizeof(currUser));

            int ID;
            read(sd, &ID, sizeof(ID));
            if (ID >= 0)
            {
                printf("Customer added succesfully\n");
                printf("ID of customer : %d\n", ID);
            }
            else
                printf("Failed to add customer\n");
        }
        else if(choice==2)
        {
            struct customer currUser;
                printf("Enter the customer ID to modify details:\n");
                scanf("%d", &currUser.customerID);

                printf("Enter the new value of Name:\n");
                scanf("%s", currUser.name);

                printf("Enter new password: ");
                char *newPass = getpass("");
                strcpy(currUser.password, newPass);

                printf("Enter the new status value :");
                scanf("%d", &currUser.status);

                write(sd, &currUser, sizeof(currUser));
                int result;
                read(sd, &result, sizeof(result));
                if (result)
                    printf("Details updated succesfully!\n");
                else
                    printf("Failure updating details\n");
        }
        else if(choice==3)
        {
            int loanId;
                int action;
                int iD;
                printf("Enter your Employee Id\n");
                scanf("%d",&iD);
                printf("Enter the loanID you want to work on:\n");
                scanf("%d",&loanId);
                printf("Enter 1 to accept the loan and -1 to reject the loan application\n");
                scanf("%d",&action);
                
                write(sd,&loanId,sizeof(loanId));
                write(sd,&action,sizeof(action));
                write(sd,&iD,sizeof(iD));
                
                bool result;
                read(sd,&result,sizeof(result));

                if(result) printf("Action performed succesfully!\n");
                else printf("Failure in performing action\n");
        }
        else if(choice==4)
        {
                int id;
                printf("Enter the your Employee ID:\n");
                scanf("%d",&id);
                write(sd,&id,sizeof(id));
                struct loan loanRecord;
                int numberOfLoanApplications;
                read(sd,&numberOfLoanApplications,sizeof(numberOfLoanApplications));
                
                int numberOfassLoanApplications;
                read(sd,&numberOfassLoanApplications,sizeof(numberOfassLoanApplications));

                if(numberOfassLoanApplications>0)
                {
                for(int i =0;i<numberOfassLoanApplications;i++){
                    read(sd,&loanRecord,sizeof(loanRecord));
                    printf("CustomerID for the assigned loan is: %d\n",loanRecord.customerID);
                    printf("LoanID of the assigned loan is:%d\n",loanRecord.loanID);
                    printf("Amount of the loan is: %f\n",loanRecord.amount);
                    printf("Duration of the loan: %d\n",loanRecord.duration);
                    printf("Status of the loan is:%d\n",loanRecord.status);
                    printf("=====================================================\n");
                }
                }
                else
                {
                    printf("No Loans assigned to you\n");
                }
                
        }
        else if(choice==6)
        {
            struct employee currUser;
            printf("Enter your id\n\n");
            int ID;
            scanf("%d", &ID);
            write(sd, &ID, sizeof(ID));
            printf("Enter the new password\n");
            char *newPass = getpass("");
            strcpy(currUser.password, newPass);
            write(sd, &currUser, sizeof(currUser));
            bool result;
            read(sd, &result, sizeof(result));
            if (result)
                printf("Password modified succesfully\n");
            else
                printf("Failure in updating password\n");
        }
        else if (choice == 7)
        {
            chooseOption(sd);
        }
        else if(choice==8)
        {
            exit(0);
        }

        else{
            printf("invaid chocie\n");
        }
        showMenu(sd);
        printf("\n");
    }
    else if (option == 3)
    {
        printf("============================================================\n");
        printf("1. Activate/deactivate customer account\n");
        printf("2. Assign Loan application process to employees\n");
        printf("3. Review customer feedback\n");
        printf("4. Change password\n");
        printf("5. Logout\n");
        printf("6. Exit\n");
        printf("============================================================\n");
        int choice;
        scanf("%d", &choice);
        write(sd, &choice, sizeof(choice));

        if (choice == 1)
        {
            printf("Enter the customer id you want to work on\n");
            int id;
            scanf("%d", &id);
            write(sd, &id, sizeof(id));
            printf("Enter 1 to activate account and 0 to deactivate account\n");
            int option;
            scanf("%d", &option);
            write(sd, &option, sizeof(option));
            bool result;
            read(sd, &result, sizeof(result));

            if (result)
                printf("Status updated succesfully!\n");
            else
                printf("Wrong customerID entered, please try again\n");
        }
        else if(choice==2)
        {
                int employeeID;
                int loanID;
                printf("Enter the loanID which you want to assign to this employee\n");
                scanf("%d",&loanID);
                
                printf("Enter the employeeID to which you want to assign the loan\n");
                scanf("%d",&employeeID);

                

                write(sd,&employeeID,sizeof(employeeID));
                write(sd,&loanID,sizeof(loanID));

                bool result;
                read(sd,&result,sizeof(result));

                if(result) printf("Loan asssigned to EmployeeId:%d succesfully!\n",employeeID);
                else printf("Failure in assigning loan\n");
        }
        else if (choice == 3)
        {
            struct feedback currUser;
                int count1;
                read(sd, &count1, sizeof(count1));
                for (int i = 0; i < count1; i++)
                {
                    read(sd, &currUser, sizeof(currUser));
                     printf("Customer ID is: %d\n", currUser.customerID);
                    printf("Customer's Feedback is: %s\n", currUser.feedbackText);
                    
                    printf("-------------------------\n");
                }

        }
        else if (choice == 4)
        {
            struct manager currUser;
            printf("Enter your id\n\n");
            int ID;
            scanf("%d", &ID);
            write(sd, &ID, sizeof(ID));
            printf("Enter the new password\n");
            char *newPass = getpass("");
            strcpy(currUser.password, newPass);
            write(sd, &currUser, sizeof(currUser));
            bool result;
            read(sd, &result, sizeof(result));
            if (result)
                printf("Password modified succesfully\n");
            else
                printf("Failure in updating password\n");
        }
        else if (choice == 5)
        {
            chooseOption(sd);
        }
        else if (choice == 6)
        {
            exit(0);
        }
        else{
            printf("Invalid choice\n");
        }
        showMenu(sd);
        printf("\n");
    }
    else if (option == 4)
    {
        printf("============================================================\n");
        printf("1. Add new bank employee\n");
        printf("2. Modify customer/employee details\n");
        printf("3. Manage user roles\n");
        printf("4. Change password\n");
        printf("5. View Details\n");
        printf("6. Add new bank manager\n");
        printf("7. Logout\n");
        printf("8. Exit\n");
        printf("============================================================\n");
        int choice;
        scanf("%d", &choice);
        write(sd, &choice, sizeof(choice));
        if (choice == 1)
        {
            struct employee emp;
            printf("Enter the name of Employee\n");
            scanf("%s", emp.name);
            printf("Enter the password\n");
            char *pass = getpass("");
            strcpy(emp.password, pass);

            write(sd, &emp, sizeof(emp));

            int ID;
            read(sd, &ID, sizeof(ID));
            if (ID >= 0)
            {
                printf("Employee added succesfully\n");
                printf("ID of employee : %d\n", ID);
            }
            else
                printf("Failed to add Employee\n");
        }

        else if (choice == 2)
        {
            printf("Enter the choice for which you want to modify the details\n");
            printf("1. Customer\n");
            printf("2. Employee\n");
            int opt;
            scanf("%d", &opt);
            write(sd, &opt, sizeof(opt));
            if (opt == 1)
            {
                struct customer currUser;
                printf("Enter the customer ID to modify details:\n");
                scanf("%d", &currUser.customerID);

                printf("Enter the new value of Name:\n");
                scanf("%s", currUser.name);

                printf("Enter new password: ");
                char *newPass = getpass("");
                strcpy(currUser.password, newPass);

                printf("Enter the new status value :");
                scanf("%d", &currUser.status);

                write(sd, &currUser, sizeof(currUser));
                int result;
                read(sd, &result, sizeof(result));
                if (result)
                    printf("Details updated succesfully!\n");
                else
                    printf("Failure updating details\n");
            }

            else if (opt == 2)
            {
                struct employee currUser;
                printf("Enter the Employee ID to modify details:\n");
                scanf("%d", &currUser.employeeID);

                printf("Enter the new value of Name:\n");
                scanf("%s", currUser.name);

                printf("Enter new password: ");
                char *newPass = getpass("");
                strcpy(currUser.password, newPass);

                printf("Enter the new status value :");
                scanf("%d", &currUser.status);

                write(sd, &currUser, sizeof(currUser));
                int result;
                read(sd, &result, sizeof(result));
                if (result)
                    printf("Details updated succesfully!\n");
                else
                    printf("Failure updating details\n");
            }
            else
            {
                printf("Invalid Option\n");
            }
        }
        else if (choice == 4)
        {
            struct admin currUser;
            printf("Enter your id\n\n");
            int ID;
            scanf("%d", &ID);
            write(sd, &ID, sizeof(ID));
            printf("Enter the new password\n");
            char *newPass = getpass("");
            strcpy(currUser.password, newPass);
            write(sd, &currUser, sizeof(currUser));
            bool result;
            read(sd, &result, sizeof(result));
            if (result)
                printf("Password modified succesfully\n");
            else
                printf("Failure in updating password\n");
        }
        else if (choice == 5)
        {
            printf("Enter the choice for which you want to view the details\n");
            printf("1. Customer\n");
            printf("2. Employee\n");
            printf("3. Manager\n");
            int option;
            scanf("%d", &option);
            write(sd, &option, sizeof(option));
            switch (option)
            {
            case 1:
                struct customer currUser;
                int count1;
                read(sd, &count1, sizeof(count1));
                for (int i = 0; i < count1; i++)
                {
                    read(sd, &currUser, sizeof(currUser));
                    printf("Customer ID is: %d\n", currUser.customerID);
                    printf("Customer's password is: %s\n", currUser.password);
                    printf("Customer Name is: %s\n", currUser.name);
                    printf("Customer's Balance is: %f\n", currUser.balance);
                    printf("Customer's status is: %d\n", currUser.status);
                    printf("-------------------------\n");
                }
                break;

            case 2:
                struct employee currEmp;
                int count2;
                read(sd, &count2, sizeof(count2));
                for (int i = 0; i < count2; i++)
                {
                    read(sd, &currEmp, sizeof(currEmp));
                    printf("Employee ID is: %d\n", currEmp.employeeID);
                    printf("Employee password is: %s\n", currEmp.password);
                    printf("Employee's Name is: %s\n", currEmp.name);
                    printf("Employee's status is: %d\n", currEmp.status);
                    printf("-------------------------\n");
                }
                break;

            case 3:
                struct manager currManager;
                int count3;
                read(sd, &count3, sizeof(count3));
                for (int i = 0; i < count3; i++)
                {
                    read(sd, &currManager, sizeof(currManager));
                    printf("Manager ID is: %d\n", currManager.managerID);
                    printf("Manager's password is: %s\n", currManager.password);
                    printf("Manager Name is: %s\n", currManager.name);
                    printf("Manager's status is: %d\n", currManager.status);
                    printf("-------------------------\n");
                }
                break;
            }
        }
        else if(choice==6)
        {
            struct manager emp;
            printf("Enter the name of Manager\n");
            scanf("%s", emp.name);
            printf("Enter the password\n");
            char *pass = getpass("");
            strcpy(emp.password, pass);

            write(sd, &emp, sizeof(emp));

            int ID;
            read(sd, &ID, sizeof(ID));
            if (ID >= 0)
            {
                printf("Manager added succesfully\n");
                printf("ID of Manager : %d\n", ID);
            }
            else
                printf("Failed to add Manager\n");
        }
        else if (choice == 7)
        {
            chooseOption(sd);
        }
        else if (choice == 8)
        {
            write(sd, &choice, sizeof(int));
            printf("Bye Bye!\n");
            exit(0);
        }
        else
        {
            printf("Invalid choice!\n");
        }

        showMenu(sd);
        printf("\n");
    }
}

void customerLogin(int sd)
{
    write(sd, &option, sizeof(option));
    struct customer currUser;
    printf("Enter customer id:");
    scanf("%d", &currUser.customerID);
    printf("enter password:");
    char *pass = getpass("");
    strcpy(currUser.password, pass);

    write(sd, &currUser, sizeof(struct customer));
    bool result; // result from server
    read(sd, &result, sizeof(result));

    if (result)
    {
        printf("\nSuccessfully Logged in\n");
    }
    else
    {
        printf("\nError\n");
        chooseOption(sd);
    }
}

void employeeLogin(int sd)
{
    write(sd, &option, sizeof(option));
    struct employee currUser;
    printf("Enter employee id:");
    scanf("%d", &currUser.employeeID);
    printf("enter password:");
    char *pass = getpass("");
    strcpy(currUser.password, pass);

    write(sd, &currUser, sizeof(struct employee));
    bool result; // result from server
    read(sd, &result, sizeof(result));

    if (result)
    {
        printf("\nSuccessfully Logged in\n");
    }
    else
    {
        printf("\nError\n");
        chooseOption(sd);
    }
}

void managerLogin(int sd)
{
    write(sd, &option, sizeof(option));
    struct manager currUser;
    printf("Enter manager id:");
    scanf("%d", &currUser.managerID);
    printf("enter password:");
    char *pass = getpass("");
    strcpy(currUser.password, pass);

    write(sd, &currUser, sizeof(struct manager));
    bool result; // result from server
    read(sd, &result, sizeof(result));

    if (result)
    {
        printf("\nSuccessfully Logged in\n");
    }
    else
    {
        printf("\nError\n");
        chooseOption(sd);
    }
}

void adminLogin(int sd)
{

    struct admin currUser;
    printf("Enter admin id:");
    scanf("%d", &currUser.adminID);
    printf("Enter password:");
    char *pass = getpass("");
    strcpy(currUser.password, pass);
    write(sd, &option, sizeof(option));
    write(sd, &currUser, sizeof(struct admin));
    bool result; // result from server
    read(sd, &result, sizeof(result));

    if (result)
    {
        printf("\nSuccessfully Logged in\n");
    }
    else
    {
        printf("\nError...! Invalid credentials\n");
        chooseOption(sd);
    }
}

void chooseOption(int sd)
{
    printf("============================================================\n");
    printf("Choose the Role:\n");
    printf("1 : Customer Login\n");
    printf("2 : Employee Login\n");
    printf("3 : Manager Login\n");
    printf("4 : Admin Login\n");
    printf("============================================================\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        customerLogin(sd);
        break;
    case 2:
        employeeLogin(sd);
        break;
    case 3:
        managerLogin(sd);
        break;
    case 4:
        adminLogin(sd);
        break;
    default:
        printf("Invalid option!\n\n");
        chooseOption(sd);
        break;
    }
}

int main()
{
    system("clear");
    printf("============================================================\n");
    printf("Welcome to ");
    printf("Online Bank Management System\n\n");
    printf("============================================================\n");
    struct sockaddr_in server;
    int sd, msgLength;
    char buff[50];
    char result;

    sd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(5555);

    connect(sd, (struct sockaddr *)&server, sizeof(server));
    chooseOption(sd);
    showMenu(sd);
    close(sd);
    return 0;
}