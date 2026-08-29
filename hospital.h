#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Doctor Structure
typedef struct {
    int id;
    char name[50];
    char specialty[30];
    int room_no; 
} Doctor;


typedef struct {
    int serial_no;
    char patient_name[50];
    int age;
    char phone[15];
    char doctor_name[50];
    int doctor_room;
    float fee;
} DoctorSerial;


typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    char assigned_doctor[50];
    int doctor_room_no;
    int hospital_room_no;
    float total_bill;
    int status; 
} Patient;

typedef struct {
    int patient_id;
    char test_name[50];
    float cost;
} TestBill;


extern Doctor DOCTORS[5];


void clearBuffer(void);
void displayDoctors(void);


void takeDoctorSerial(void);  
void admitPatient(void);       
void doctorCheckup(void);       
void addTestBill(void);        
void dischargePatient(void);    

#endif