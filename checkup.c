// #include "hospital.h"

// // 5 Fixed Doctors Info with Room Numbers
// Doctor DOCTORS[5] = {
//     {1, "Dr. Rahim Ahmed (Cardiology)", "Cardiology", 101},
//     {2, "Dr. Nusrat Jahan (Neurology)", "Neurology", 102},
//     {3, "Dr. Tanvir Hossain (Orthopedics)", "Orthopedics", 201},
//     {4, "Dr. Farhana Islam (Pediatrics)", "Pediatrics", 202},
//     {5, "Dr. Kamrul Hasan (General Medicine)", "General Medicine", 301}
// };

// void displayDoctors(void) {
//     printf("\n--- Available Doctors & Chambers ---\n");
//     for (int i = 0; i < 5; i++) {
//         printf(" [%d] %-38s -> Room No: %d\n", i + 1, DOCTORS[i].name, DOCTORS[i].room_no);
//     }
//     printf("------------------------------------\n");
// }

// void doctorCheckup(void) {
//     FILE *fp = fopen("patients.dat", "rb+");
//     if (fp == NULL) {
//         printf("\n[Error] No patient records found.\n");
//         return;
//     }

//     int search_id, found = 0;
//     Patient p;

//     printf("\n=========================================\n");
//     printf("        MODULE 2: DOCTOR CHECKUP         \n");
//     printf("=========================================\n");
//     printf("Enter Patient ID / Serial: ");
//     if (scanf("%d", &search_id) != 1) {
//         clearBuffer();
//         printf("Invalid Input!\n");
//         fclose(fp);
//         return;
//     }
//     clearBuffer();

//     while (fread(&p, sizeof(Patient), 1, fp) == 1) {
//         // Patient can be in Serial (0) or already Admitted (1)
//         if (p.id == search_id && (p.status == 0 || p.status == 1)) {
//             found = 1;
//             printf("\n--- PATIENT INFORMATION ---\n");
//             printf(" Name            : %s (Age: %d)\n", p.name, p.age);
//             printf(" Doctor          : %s\n", p.assigned_doctor);
//             printf(" Doctor Chamber  : Room %d\n", p.doctor_room_no);
//             printf(" Initial Problem : %s\n", p.disease);
//             printf(" Current Status  : %s\n", p.status == 1 ? "Admitted" : "Not Admitted (Serial Taken)");
//             printf("----------------------------\n");

//             // 1. Update Prescription / Diagnosis
//             printf("Enter Updated Diagnosis / Doctor Notes: ");
//             fgets(p.disease, sizeof(p.disease), stdin);
//             p.disease[strcspn(p.disease, "\n")] = 0;

//             // 2. Recommend Hospital Admission
//             if (p.status == 0) {
//                 char admit_choice;
//                 printf("\nDoes this patient need Hospital Admission? (y/n): ");
//                 scanf(" %c", &admit_choice);
//                 clearBuffer();

//                 if (admit_choice == 'y' || admit_choice == 'Y') {
//                     p.status = 1; // Mark as Admitted
//                     printf("Enter Hospital Bed/Room Number to assign: ");
//                     scanf("%d", &p.hospital_room_no);
//                     clearBuffer();
//                     printf("\n[ALERT] Patient %s has been ADMITTED to Hospital Room %d!\n", p.name, p.hospital_room_no);
//                 } else {
//                     printf("\n[INFO] Patient checkup done. Prescribed regular medicine (No Admission required).\n");
//                 }
//             }

//             // Write back to file
//             fseek(fp, -((long)sizeof(Patient)), SEEK_CUR);
//             fwrite(&p, sizeof(Patient), 1, fp);
            
//             printf("\n[Success] Checkup record updated successfully!\n");
//             break;
//         }
//     }

//     if (!found) {
//         printf("\n[Notice] Patient ID %d not found or already discharged.\n", search_id);
//     }

//     fclose(fp);
// }
#include "hospital.h"

// 5 Fixed Doctors Info
Doctor DOCTORS[5] = {
    {1, "Dr. Rahim Ahmed (Cardiology)", "Cardiology", 101},
    {2, "Dr. Nusrat Jahan (Neurology)", "Neurology", 102},
    {3, "Dr. Tanvir Hossain (Orthopedics)", "Orthopedics", 201},
    {4, "Dr. Farhana Islam (Pediatrics)", "Pediatrics", 202},
    {5, "Dr. Kamrul Hasan (General Medicine)", "General Medicine", 301}
};

void displayDoctors(void) {
    printf("\n--- Available Doctors & Chambers ---\n");
    for (int i = 0; i < 5; i++) {
        printf(" [%d] %-38s -> Chamber: Room %d\n", i + 1, DOCTORS[i].name, DOCTORS[i].room_no);
    }
    printf("------------------------------------\n");
}

void doctorCheckup(void) {
    FILE *fp = fopen("patients.dat", "rb+");
    if (fp == NULL) {
        printf("\n[Error] No patient records found.\n");
        return;
    }

    int search_id, found = 0;
    Patient p;

    printf("\n=========================================\n");
    printf("        MODULE 2: DOCTOR CHECKUP         \n");
    printf("=========================================\n");
    printf("Enter Admitted Patient ID: ");
    if (scanf("%d", &search_id) != 1) {
        clearBuffer();
        printf("Invalid Input!\n");
        fclose(fp);
        return;
    }
    clearBuffer();

    while (fread(&p, sizeof(Patient), 1, fp) == 1) {
        // শুধু ভর্তি থাকা (status == 1) রোগীদের চেকআপ করা যাবে
        if (p.id == search_id && p.status == 1) {
            found = 1;
            printf("\n--- CURRENT PATIENT DETAILS ---\n");
            printf(" Name            : %s (Age: %d)\n", p.name, p.age);
            printf(" Doctor          : %s (Chamber Room %d)\n", p.assigned_doctor, p.doctor_room_no);
            printf(" Hospital Ward   : Room %d\n", p.hospital_room_no);
            printf(" Disease/Notes   : %s\n", p.disease);
            printf("--------------------------------\n");

            // Option to change doctor if needed
            char change_doc;
            printf("Do you want to change assigned Doctor? (y/n): ");
            scanf(" %c", &change_doc);
            clearBuffer();

            if (change_doc == 'y' || change_doc == 'Y') {
                displayDoctors();
                int doc_choice = 0;
                printf("Select New Doctor Serial (1-5): ");
                scanf("%d", &doc_choice);
                clearBuffer();
                if (doc_choice >= 1 && doc_choice <= 5) {
                    strcpy(p.assigned_doctor, DOCTORS[doc_choice - 1].name);
                    p.doctor_room_no = DOCTORS[doc_choice - 1].room_no;
                }
            }

            // Update Doctor Checkup Notes
            printf("Enter Updated Diagnosis / Treatment Notes: ");
            fgets(p.disease, sizeof(p.disease), stdin);
            p.disease[strcspn(p.disease, "\n")] = 0;

            // Save changes back to file
            fseek(fp, -((long)sizeof(Patient)), SEEK_CUR);
            fwrite(&p, sizeof(Patient), 1, fp);
            
            printf("\n[Success] Doctor checkup notes updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("\n[Notice] Patient ID %d was NOT found or is already Discharged.\n", search_id);
    }

    fclose(fp);
}