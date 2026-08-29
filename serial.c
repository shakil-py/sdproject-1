#include "hospital.h"

void takeDoctorSerial(void) {

    clearBuffer(); 

    FILE *fp = fopen("serials.dat", "ab");
    if (fp == NULL) {
        printf("\n[Error] Unable to open serials.dat file!\n");
        return;
    }

    DoctorSerial s;
    
    
    FILE *fp_read = fopen("serials.dat", "rb");
    int count = 1;
    if (fp_read != NULL) {
        DoctorSerial temp;
        while (fread(&temp, sizeof(DoctorSerial), 1, fp_read) == 1) {
            count++;
        }
        fclose(fp_read);
    }
    s.serial_no = count;

    printf("\n=========================================\n");
    printf("     OPD DOCTOR APPOINTMENT / SERIAL     \n");
    printf("=========================================\n");
    
    printf("Enter Patient Name: ");
    fgets(s.patient_name, sizeof(s.patient_name), stdin);
    s.patient_name[strcspn(s.patient_name, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &s.age);
    clearBuffer();

    printf("Enter Phone Number: ");
    fgets(s.phone, sizeof(s.phone), stdin);
    s.phone[strcspn(s.phone, "\n")] = 0;

    // Doctor Selection
    displayDoctors();
    int doc_choice = 0;
    printf("Select Doctor Serial (1-5): ");
    scanf("%d", &doc_choice);
    clearBuffer();

    if (doc_choice >= 1 && doc_choice <= 5) {
        strcpy(s.doctor_name, DOCTORS[doc_choice - 1].name);
        s.doctor_room = DOCTORS[doc_choice - 1].room_no;
    } else {
        printf("[Notice] Invalid choice. Defaulting to General Medicine.\n");
        strcpy(s.doctor_name, DOCTORS[4].name);
        s.doctor_room = DOCTORS[4].room_no;
    }

    s.fee = 500.0f; 

    fwrite(&s, sizeof(DoctorSerial), 1, fp);
    fclose(fp);

    
    printf("\n");
    printf("*****************************************\n");
    printf("        OPD APPOINTMENT SLIP / BILL      \n");
    printf("*****************************************\n");
    printf(" SERIAL NUMBER  : #%03d\n", s.serial_no);
    printf(" Patient Name   : %s\n", s.patient_name);
    printf(" Age / Phone    : %d / %s\n", s.age, s.phone);
    printf("-----------------------------------------\n");
    printf(" Doctor Name    : %s\n", s.doctor_name);
    printf(" Chamber Room   : ROOM NO #%d\n", s.doctor_room);
    printf("-----------------------------------------\n");
    printf(" Consultation   : %.2f Tk (PAID)\n", s.fee);
    printf("*****************************************\n");
    printf(" Please wait outside Chamber Room #%d\n", s.doctor_room);
    printf("*****************************************\n");
}