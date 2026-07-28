#include "hospital.h"

// 5 Fixed Doctors in the hospital
const char *DOCTORS[5] = {
    "Dr. Rahim Ahmed (Cardiology)",
    "Dr. Nusrat Jahan (Neurology)",
    "Dr. Tanvir Hossain (Orthopedics)",
    "Dr. Farhana Islam (Pediatrics)",
    "Dr. Kamrul Hasan (General Medicine)"
};

// Helper to display the list of 5 doctors
void displayDoctors(void) {
    printf("\n--- Available Doctors List ---\n");
    for (int i = 0; i < 5; i++) {
        printf(" [%d] %s\n", i + 1, DOCTORS[i]);
    }
    printf("------------------------------\n");
}

void doctorCheckup(void) {
    FILE *fp = fopen("patients.dat", "rb+");
    if (fp == NULL) {
        printf("\n[Error] No patient records found (patients.dat does not exist).\n");
        return;
    }

    int search_id, found = 0;
    Patient p;

    printf("\n--- Module 2: Doctor Checkup ---\n");
    printf("Enter Patient ID for Checkup: ");
    if (scanf("%d", &search_id) != 1) {
        clearBuffer();
        printf("Invalid ID input!\n");
        fclose(fp);
        return;
    }
    clearBuffer();

    while (fread(&p, sizeof(Patient), 1, fp) == 1) {
        if (p.id == search_id && p.is_admitted == 1) {
            found = 1;
            printf("\n=========================================\n");
            printf("            PATIENT DETAILS              \n");
            printf("=========================================\n");
            printf(" ID              : %d\n", p.id);
            printf(" Name            : %s\n", p.name);
            printf(" Current Doctor  : %s\n", strlen(p.assigned_doctor) > 0 ? p.assigned_doctor : "None");
            printf(" Current Disease : %s\n", p.disease);
            printf("-----------------------------------------\n");

            // 1. Select Doctor from Serial 1-5
            displayDoctors();
            int doc_choice = 0;
            printf("Select Doctor Serial (1-5) or 0 to keep current: ");
            scanf("%d", &doc_choice);
            clearBuffer();

            if (doc_choice >= 1 && doc_choice <= 5) {
                strcpy(p.assigned_doctor, DOCTORS[doc_choice - 1]);
            } else if (doc_choice != 0) {
                printf("[Warning] Invalid selection! Keeping previous doctor.\n");
            }

            // 2. Update Diagnosis
            printf("\nEnter Updated Diagnosis / Checkup Notes: ");
            fgets(p.disease, sizeof(p.disease), stdin);
            p.disease[strcspn(p.disease, "\n")] = 0;

            // Move file pointer back to update record
            fseek(fp, -((long)sizeof(Patient)), SEEK_CUR);
            fwrite(&p, sizeof(Patient), 1, fp);
            
            printf("\n[Success] Doctor Checkup completed for Patient ID %d!\n", p.id);
            printf(" Assigned Doctor : %s\n", p.assigned_doctor);
            printf(" New Diagnosis   : %s\n", p.disease);
            break;
        }
    }

    if (!found) {
        printf("\n[Notice] Patient ID %d was either not found or has already been discharged.\n", search_id);
    }

    fclose(fp);
}