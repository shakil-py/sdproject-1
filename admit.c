#include "hospital.h"

void admitPatient(void) {
    FILE *fp = fopen("patients.dat", "ab");
    if (fp == NULL) {
        printf("\n[Error] Unable to open patients.dat file!\n");
        return;
    }

    Patient p;
    printf("\n=========================================\n");
    printf("     MODULE 1: ADMIT NEW PATIENT         \n");
    printf("=========================================\n");
    
    printf("Enter Patient ID: ");
    if (scanf("%d", &p.id) != 1) {
        clearBuffer();
        printf("Invalid ID format!\n");
        fclose(fp);
        return;
    }
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

    printf("Enter Primary Disease / Health Problem: ");
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;

    
    displayDoctors();
    int doc_choice = 0;
    printf("Select Primary Doctor (1-5): ");
    scanf("%d", &doc_choice);
    clearBuffer();

    if (doc_choice >= 1 && doc_choice <= 5) {
        strcpy(p.assigned_doctor, DOCTORS[doc_choice - 1].name);
        p.doctor_room_no = DOCTORS[doc_choice - 1].room_no;
    } else {
        printf("[Notice] Invalid choice. Defaulting to General Medicine.\n");
        strcpy(p.assigned_doctor, DOCTORS[4].name);
        p.doctor_room_no = DOCTORS[4].room_no;
    }

    
    printf("Enter Hospital Ward/Bed Room Number for Admission: ");
    scanf("%d", &p.hospital_room_no);
    clearBuffer();

    p.total_bill = 1000.0f; 
    p.status = 1;           

    fwrite(&p, sizeof(Patient), 1, fp);
    fclose(fp);

    printf("\n-----------------------------------------\n");
    printf(" [SUCCESS] PATIENT ADMITTED SUCCESSFULLY!\n");
    printf(" Patient ID       : %d\n", p.id);
    printf(" Patient Name     : %s\n", p.name);
    printf(" Primary Doctor   : %s (Chamber: Room %d)\n", p.assigned_doctor, p.doctor_room_no);
    printf(" Hospital Ward    : Room %d\n", p.hospital_room_no);
    printf(" Admission Fee    : %.2f Tk\n", p.total_bill);
    printf(" Status           : ADMITTED\n");
    printf("-----------------------------------------\n");
}