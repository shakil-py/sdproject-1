#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Data Structures
typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    char assigned_doctor[50];
    int room_no;
    float total_bill;
    int is_admitted; // 1 = Admitted, 0 = Discharged
} Patient;

typedef struct {
    int patient_id;
    char test_name[50];
    float cost;
} TestBill;

// Helper function
void clearBuffer(void);

// Module Functions
void admitPatient(void);
void doctorCheckup(void);
void addTestBill(void);
void dischargePatient(void);

#endif