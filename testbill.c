#include "hospital.h"

void addTestBill(void) {
    FILE *fp_patient = fopen("patients.dat", "rb+");
    if (fp_patient == NULL) {
        printf("No patient records found.\n");
        return;
    }

    int search_id, found = 0;
    Patient p;

    printf("\n--- Module 3: Test Bill ---\n");
    printf("Enter Patient ID: ");
    scanf("%d", &search_id);
    clearBuffer();

    while (fread(&p, sizeof(Patient), 1, fp_patient) == 1) {
        if (p.id == search_id && p.is_admitted == 1) {
            found = 1;

            TestBill tb;
            tb.patient_id = search_id;

            printf("Enter Test Name (e.g., Blood Test, MRI, X-Ray): ");
            fgets(tb.test_name, sizeof(tb.test_name), stdin);
            tb.test_name[strcspn(tb.test_name, "\n")] = 0;

            printf("Enter Test Cost: ");
            scanf("%f", &tb.cost);

            FILE *fp_test = fopen("test_bills.dat", "ab");
            if (fp_test != NULL) {
                fwrite(&tb, sizeof(TestBill), 1, fp_test);
                fclose(fp_test);
            }

            p.total_bill += tb.cost;

            fseek(fp_patient, -((long)sizeof(Patient)), SEEK_CUR);
            fwrite(&p, sizeof(Patient), 1, fp_patient);

            printf("\n[Success] Added '%s' (Cost: $%.2f) to Patient ID %d. New total: $%.2f\n", 
                   tb.test_name, tb.cost, p.id, p.total_bill);
            break;
        }
    }

    if (!found) {
        printf("Patient ID %d not found or not currently admitted.\n", search_id);
    }

    fclose(fp_patient);
}