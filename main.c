#include "hospital.h"

void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    int choice;

    while (1) {
        printf("\n=========================================\n");
        printf("    HOSPITAL MANAGEMENT SYSTEM (C)      \n");
        printf("=========================================\n");
        printf(" 1. Take Doctor OPD Serial (Get Slip)\n");
        printf(" 2. Admit New Patient to Hospital\n");
        printf(" 3. Doctor Checkup (Admitted Patient)\n");
        printf(" 4. Add Test Bill\n");
        printf(" 5. Discharge Patient & Final Bill\n");
        printf(" 6. Exit Program\n");
        printf("-----------------------------------------\n");
        printf("Enter your choice (1-6): ");
        
        if (scanf("%d", &choice) != 1) {
            clearBuffer();
            printf("Invalid input! Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                takeDoctorSerial();
                break;
            case 2:
                admitPatient();    
                break;
            case 3:
                doctorCheckup();  
                break;
            case 4:
                addTestBill();    
                break;
            case 5:
                dischargePatient(); 
                break;
            case 6:
                printf("\nExiting program. Goodbye!\n");
                exit(0);
            default:
                printf("\nInvalid option! Please try again.\n");
        }
    }

    return 0;
}