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
        printf(" 1. Take Doctor Serial / Appointment\n");
        printf(" 2. Doctor Checkup & Hospital Admit\n");
        printf(" 3. Add Test Bill\n");
        printf(" 4. Discharge Patient & Final Bill\n");
        printf(" 5. Exit Program\n");
        printf("-----------------------------------------\n");
        printf("Enter your choice (1-5): ");
        
        if (scanf("%d", &choice) != 1) {
            clearBuffer();
            printf("Invalid input! Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                takeDoctorSerial(); // Module 1
                break;
            case 2:
                doctorCheckup();    // Module 2
                break;
            case 3:
                addTestBill();      // Module 3
                break;
            case 4:
                dischargePatient(); // Module 4
                break;
            case 5:
                printf("\nExiting program. Goodbye!\n");
                exit(0);
            default:
                printf("\nInvalid option! Please try again.\n");
        }
    }

    return 0;
}