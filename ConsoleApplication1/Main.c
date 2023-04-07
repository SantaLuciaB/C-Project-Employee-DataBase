#include <stdio.h>
#include <string.h>

// Include function prototypes
void Create(const char* nume);
void Display(const char* nume);
void Modify(const char* nume, int k);
void SortNameSurname(const char* nume);

int main() {
    const char* filename = "employees.dat"; // File name to use

    // Create some employee records
    printf("Creating employee records\n");
    Create(filename);

    // Display all employee records
    printf("\nDisplaying employee records:\n");
    Display(filename);

    // Modify a specific employee record
    int employee_id = 2;
    printf("\nModifying employee record with ID %d:\n", employee_id);
    Modify(filename, employee_id);

    // Display all employee records again to see the changes
    printf("\nDisplaying employee records after modification:\n");
    Display(filename);

    // Sort employee records by name and surname
    printf("\nSorting employee records by name and surname:\n");
    SortNameSurname(filename);

    // Display all employee records again to see the changes
    printf("\nDisplaying employee records after sorting:\n");
    Display(filename);

    return 0;
}
