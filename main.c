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
        printf(" 1. Admit Patient\n");
        printf(" 2. Doctor Checkup / Update Diagnosis\n");
        printf(" 3. Add Test Bill\n");
        printf(" 4. Discharge Patient & Generate Bill\n");
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
                admitPatient();
                break;
            case 2:
                doctorCheckup();
                break;
            case 3:
                addTestBill();
                break;
            case 4:
                dischargePatient();
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
