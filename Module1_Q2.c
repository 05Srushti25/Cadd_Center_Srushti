#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    CARDIOLOGY = 1,
    ORTHOPEDIC,
    NEUROLOGY,
    GENERAL
} Department;

typedef struct {
    int id;
    char name[50];
    int age;
    char disease[50];
    char admissionDate[15];
    int roomNumber;
    Department dept;
} Patient;

void addPatient();
void displayPatient(Patient p);
void searchPatient();
void updatePatient();
void deletePatient();

int main() {
    int choice;

    do {
        printf("\n====== Hospital Management System ======\n");
        printf("1. Add New Patient\n");
        printf("2. Search Patient\n");
        printf("3. Update Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: searchPatient(); break;
            case 3: updatePatient(); break;
            case 4: deletePatient(); break;
            case 5: printf("Exiting program...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}

// ADD PATIENT 
void addPatient() {
    FILE *fp = fopen("patients.dat", "ab");
    Patient *p = (Patient *)malloc(sizeof(Patient));

    if (!fp || !p) {
        printf("Memory/File error!\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &p->id);
    getchar();

    printf("Enter Name: ");
    fgets(p->name, 50, stdin);
    p->name[strcspn(p->name, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &p->age);
    getchar();

    printf("Enter Disease: ");
    fgets(p->disease, 50, stdin);
    p->disease[strcspn(p->disease, "\n")] = '\0';

    printf("Enter Admission Date (DD/MM/YYYY): ");
    fgets(p->admissionDate, 15, stdin);
    p->admissionDate[strcspn(p->admissionDate, "\n")] = '\0';

    printf("Enter Room Number: ");
    scanf("%d", &p->roomNumber);

    printf("Department (1.CARDIOLOGY 2.ORTHOPEDIC 3.NEUROLOGY 4.GENERAL): ");
    scanf("%d", (int *)&p->dept);

    fwrite(p, sizeof(Patient), 1, fp);

    fclose(fp);
    free(p);

    printf("Patient added successfully!\n");
}

// DISPLAY PATIENT
void displayPatient(Patient p) {
    printf("\n---------------------------------\n");
    printf("ID            : %d\n", p.id);
    printf("Name          : %s\n", p.name);
    printf("Age           : %d\n", p.age);
    printf("Disease       : %s\n", p.disease);
    printf("Admission Date: %s\n", p.admissionDate);
    printf("Room Number   : %d\n", p.roomNumber);
    printf("Department    : %d\n", p.dept);
}

// SEARCH PATIENT 
void searchPatient() {
    FILE *fp = fopen("patients.dat", "rb");
    Patient p;
    int id, found = 0;

    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == id) {
            displayPatient(p);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("Patient not found!\n");
}

// UPDATE PATIENT 
void updatePatient() {
    FILE *fp = fopen("patients.dat", "rb+");
    Patient p;
    int id, found = 0;

    printf("Enter Patient ID to update: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == id) {
            printf("Enter new Disease: ");
            getchar();
            fgets(p.disease, 50, stdin);
            p.disease[strcspn(p.disease, "\n")] = '\0';

            fseek(fp, -sizeof(Patient), SEEK_CUR);
            fwrite(&p, sizeof(Patient), 1, fp);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found)
        printf("Patient record updated!\n");
    else
        printf("Patient not found!\n");
}

// DELETE PATIENT
void deletePatient() {
    FILE *fp = fopen("patients.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    Patient p;
    int id, found = 0;

    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id != id)
            fwrite(&p, sizeof(Patient), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("patients.dat");
    rename("temp.dat", "patients.dat");

    if (found)
        printf("Patient deleted successfully!\n");
    else
        printf("Patient not found!\n");
}


