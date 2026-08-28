#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Doctor Structure (নাম ও রুম নম্বর)
typedef struct {
    int id;
    char name[50];
    char specialty[30];
    int room_no; // ডাক্তারের চেম্বার নম্বর
} Doctor;

// Patient Structure
typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    char assigned_doctor[50];
    int doctor_room_no; // ডাক্তারের চেম্বার
    int hospital_room_no; // ভর্তি হলে ওয়ার্ডের রুম নম্বর
    float total_bill;
    int status; // 0 = Serial Taken, 1 = Admitted, 2 = Discharged
} Patient;

typedef struct {
    int patient_id;
    char test_name[50];
    float cost;
} TestBill;

// Global Doctors Array
extern Doctor DOCTORS[5];

// Helper Functions
void clearBuffer(void);
void displayDoctors(void);

// Module Functions
void takeDoctorSerial(void);   // Module 1: সিরিয়াল নেওয়া
void doctorCheckup(void);       // Module 2: চেকআপ ও অ্যাডমিট করা
void addTestBill(void);         // Module 3: টেস্ট বিল
void dischargePatient(void);    // Module 4: ডিসচার্জ

#endif