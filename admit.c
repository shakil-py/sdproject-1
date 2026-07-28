#include "hospital.h"

void admitPatient(void) {
    FILE *fp = fopen("patients.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file patients.dat!\n");
        return;
    }

    Patient p;
    printf("\n--- Module 1: Admit Patient ---\n");
    
    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    clearBuffer();

    printf("Enter Patient Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &p.age);
    clearBuffer();

    printf("Enter Gender: ");
    fgets(p.gender, sizeof(p.gender), stdin);
    p.gender[strcspn(p.gender, "\n")] = 0;

    printf("Enter Primary Disease / Complaint: ");
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;

    // Inside module1_admit.c — replaces manual doctor text input:

displayDoctors();
int doc_choice = 0;
printf("Select Assigned Doctor Serial (1-5): ");
scanf("%d", &doc_choice);
clearBuffer();

if (doc_choice >= 1 && doc_choice <= 5) {
    strcpy(p.assigned_doctor, DOCTORS[doc_choice - 1]);
} else {
    strcpy(p.assigned_doctor, "Dr. Kamrul Hasan (General Medicine)"); // Default fallback
}

    printf("Enter Room Number: ");
    scanf("%d", &p.room_no);

    p.total_bill = 0.0f;
    p.is_admitted = 1;

    fwrite(&p, sizeof(Patient), 1, fp);
    fclose(fp);

    printf("\n[Success] Patient '%s' (ID: %d) admitted successfully!\n", p.name, p.id);
}