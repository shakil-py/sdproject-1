#include "hospital.h"

void takeDoctorSerial(void) {
    FILE *fp = fopen("patients.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file patients.dat!\n");
        return;
    }

    Patient p;
    printf("\n=========================================\n");
    printf("   MODULE 1: DOCTOR SERIAL / APPOINTMENT  \n");
    printf("=========================================\n");
    
    printf("Enter Serial / Patient ID: ");
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

    printf("Enter Problem / Symptoms: ");
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;

    // Doctor Selection
    displayDoctors();
    int doc_choice = 0;
    printf("Select Doctor Serial (1-5): ");
    scanf("%d", &doc_choice);
    clearBuffer();

    if (doc_choice >= 1 && doc_choice <= 5) {
        strcpy(p.assigned_doctor, DOCTORS[doc_choice - 1].name);
        p.doctor_room_no = DOCTORS[doc_choice - 1].room_no;
    } else {
        printf("[Notice] Invalid selection. Defaulting to General Medicine.\n");
        strcpy(p.assigned_doctor, DOCTORS[4].name);
        p.doctor_room_no = DOCTORS[4].room_no;
    }

    p.hospital_room_no = 0; // এখনো হাসপাতালে ভর্তি হয়নি
    p.total_bill = 500.0f;  // ডাক্তার দেখানোর প্রাথমিক ফি (Doctor Consultation Fee)
    p.status = 0;           // 0 = Serial Taken

    fwrite(&p, sizeof(Patient), 1, fp);
    fclose(fp);

    printf("\n-----------------------------------------\n");
    printf(" [SUCCESS] SERIAL CONFIRMED!\n");
    printf(" Patient Name  : %s (ID: %d)\n", p.name, p.id);
    printf(" Assigned Doctor: %s\n", p.assigned_doctor);
    printf(" Doctor Room No : Room %d\n", p.doctor_room_no);
    printf(" Initial Fee    : $%.2f\n", p.total_bill);
    printf(" Status         : Waiting for Checkup\n");
    printf("-----------------------------------------\n");
}