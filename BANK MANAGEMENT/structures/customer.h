#ifndef CUSTOMER_STRUCT
#define CUSTOMER_STRUCT

struct customer{
    int customerID;
    char name[20];
    char password[10];
    float balance;
    int status;
   
};
struct loan {
    int loanID;
    int customerID; 
    float amount;
    int duration; 
    int status; // 0 = Pending, 1 = Approved, -1 = Rejected
    int assignedEmployeeID; 
};

#endif