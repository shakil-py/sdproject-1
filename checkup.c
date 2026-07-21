#include "hospital.h"

void doctorCheckup(void) {
    FILE *fp = fopen("patients.dat", "rb+");
    if (fp == NULL) {
        printf("No patient records found (patients.dat does not exist).\n");
        return;
    }

    int search_id, found = 0;
    Patient p;

    printf("\n--- Module 2: Doctor Checkup ---\n");
    printf("Enter Patient ID for Checkup: ");
    scanf("%d", &search_id);
    clearBuffer();

    while (fread(&p, sizeof(Patient), 1, fp) == 1) {
        if (p.id == search_id && p.is_admitted == 1) {
            found = 1;
            printf("\nPatient Found:\n");
            printf(" Name: %s | Room: %d | Assigned Doctor: %s\n", p.name, p.room_no, p.assigned_doctor);
            printf(" Current Diagnosis: %s\n", p.disease);
            printf("-----------------------------------------\n");

            printf("Enter Updated / New Diagnosis: ");
            fgets(p.disease, sizeof(p.disease), stdin);
            p.disease[strcspn(p.disease, "\n")] = 0;

            printf("Enter New Assigned Doctor (or press Enter to keep '%s'): ", p.assigned_doctor);
            char new_doc[50];
            fgets(new_doc, sizeof(new_doc), stdin);
            new_doc[strcspn(new_doc, "\n")] = 0;
            if (strlen(new_doc) > 0) {
                strcpy(p.assigned_doctor, new_doc);
            }

            fseek(fp, -((long)sizeof(Patient)), SEEK_CUR);
            fwrite(&p, sizeof(Patient), 1, fp);
            
            printf("\n[Success] Doctor checkup notes updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Patient with ID %d is either not found or already discharged.\n", search_id);
    }

    fclose(fp);
}