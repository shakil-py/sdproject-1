#include "hospital.h"

void dischargePatient(void) {
    FILE *fp_patient = fopen("patients.dat", "rb+");
    if (fp_patient == NULL) {
        printf("No patient records found.\n");
        return;
    }

    int search_id, found = 0;
    Patient p;

    printf("\n--- Module 4: Discharge Patient & Final Bill ---\n");
    printf("Enter Patient ID to Discharge: ");
    scanf("%d", &search_id);

    while (fread(&p, sizeof(Patient), 1, fp_patient) == 1) {
        if (p.id == search_id && p.is_admitted == 1) {
            found = 1;

            float room_charge = 0.0f;
            printf("Enter Room / Stay Charges: ");
            scanf("%f", &room_charge);

            p.total_bill += room_charge;
            p.is_admitted = 0;

            fseek(fp_patient, -((long)sizeof(Patient)), SEEK_CUR);
            fwrite(&p, sizeof(Patient), 1, fp_patient);

            printf("\n=========================================\n");
            printf("         FINAL DISCHARGE INVOICE         \n");
            printf("=========================================\n");
            printf(" Patient ID      : %d\n", p.id);
            printf(" Name            : %s\n", p.name);
            printf(" Age / Gender    : %d / %s\n", p.age, p.gender);
            printf(" Final Diagnosis : %s\n", p.disease);
            printf(" Doctor          : %s\n", p.assigned_doctor);
            printf(" Room Number     : %d\n", p.room_no);
            printf("-----------------------------------------\n");
            printf(" Tests Breakdown:\n");

            FILE *fp_test = fopen("test_bills.dat", "rb");
            if (fp_test != NULL) {
                TestBill tb;
                int test_count = 0;
                while (fread(&tb, sizeof(TestBill), 1, fp_test) == 1) {
                    if (tb.patient_id == p.id) {
                        printf("  - %-25s: $%.2f\n", tb.test_name, tb.cost);
                        test_count++;
                    }
                }
                if (test_count == 0) {
                    printf("  (No extra tests recorded)\n");
                }
                fclose(fp_test);
            }

            printf(" Room & Service Charges   : $%.2f\n", room_charge);
            printf("-----------------------------------------\n");
            printf(" TOTAL AMOUNT PAYABLE     : $%.2f\n", p.total_bill);
            printf(" Status                   : DISCHARGED\n");
            printf("=========================================\n");

            break;
        }
    }

    if (!found) {
        printf("Patient ID %d is either invalid or already discharged.\n", search_id);
    }

    fclose(fp_patient);
}