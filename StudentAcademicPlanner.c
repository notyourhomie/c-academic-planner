#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100
#define MAX_ATTEMPTS 3
#define FILENAME "planner.csv"

typedef struct {
    char studentID[20];
    char studentName[50];
    char courseName[50];
    char assignmentTitle[50];
    char dueDate[20];
    char status[20];
} PlannerEntry;

// Function prototypes
void loadEntries(PlannerEntry *entries, int *count);
void saveEntries(PlannerEntry *entries, int count);
void menu(PlannerEntry *entries, int *count);
int login();
void addEntry(PlannerEntry *entries, int *count);
void viewEntries(const PlannerEntry *entries, int count);
void deleteEntry(PlannerEntry *entries, int *count);
void searchEntry(const PlannerEntry *entries, int count);
void editEntry(PlannerEntry *entries, int count);
void clearInputBuffer();
int findEntryIndex(const PlannerEntry *entries, int count, const char *id);
void trimNewline(char *str);

// Main function
int main() {
    PlannerEntry *entries = (PlannerEntry *)malloc(MAX_ENTRIES * sizeof(PlannerEntry));
    int count = 0;

    loadEntries(entries, &count);

    printf("---------------------------------------------------\n");
    printf("|         STUDENT ACADEMIC PLANNER SYSTEM         |\n");
    printf("---------------------------------------------------\n");

    if (login()) {
        menu(entries, &count);
    }

    saveEntries(entries, count);
    free(entries);
    return 0;
}

// Function: Login system
int login() {
    char username[20], password[20];
    const char *correctUser = "student";
    const char *correctPass = "planner";
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        printf("\nUsername: ");
        scanf("%19s", username);
        clearInputBuffer();
        printf("Password: ");
        scanf("%19s", password);
        clearInputBuffer();

        if (strcmp(username, correctUser) == 0 && strcmp(password, correctPass) == 0) {
            printf("Login successful. Welcome!\n");
            return 1;
        }
        printf("Invalid credentials. Attempts left: %d\n", MAX_ATTEMPTS - attempts - 1);
        attempts++;
    }

    printf("Too many failed attempts. Exiting.\n");
    return 0;
}

// Menu loop
void menu(PlannerEntry *entries, int *count) {
    int choice;
    do {
        printf("\n--------- Main Menu ---------\n");
        printf("1. Add Entry\n");
        printf("2. View All Entries\n");
        printf("3. Delete Entry\n");
        printf("4. Search Entry\n");
        printf("5. Edit Entry\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Enter a number.\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: addEntry(entries, count); break;
            case 2: viewEntries(entries, *count); break;
            case 3: deleteEntry(entries, count); break;
            case 4: searchEntry(entries, *count); break;
            case 5: editEntry(entries, *count); break;
            case 6: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);
}

// Load data from file
void loadEntries(PlannerEntry *entries, int *count) {
    FILE *f = fopen(FILENAME, "r");
    if (!f) return;

    while (fscanf(f, "%19[^,],%49[^,],%49[^,],%49[^,],%19[^,],%19[^\n]\n",
                  entries[*count].studentID, entries[*count].studentName,
                  entries[*count].courseName, entries[*count].assignmentTitle,
                  entries[*count].dueDate, entries[*count].status) == 6) {
        (*count)++;
    }

    fclose(f);
}

// Save data to file
void saveEntries(PlannerEntry *entries, int count) {
    FILE *f = fopen(FILENAME, "w");
    if (!f) {
        perror("Error saving file");
        return;
    }

    for (int i = 0; i < count; ++i) {
        fprintf(f, "%s,%s,%s,%s,%s,%s\n",
                entries[i].studentID, entries[i].studentName,
                entries[i].courseName, entries[i].assignmentTitle,
                entries[i].dueDate, entries[i].status);
    }

    fclose(f);
}

// Add entry
void addEntry(PlannerEntry *entries, int *count) {
    if (*count >= MAX_ENTRIES) {
        printf("Planner is full.\n");
        return;
    }

    PlannerEntry *e = &entries[*count];

    printf("Student ID: ");
    fgets(e->studentID, sizeof(e->studentID), stdin); trimNewline(e->studentID);
    printf("Student Name: ");
    fgets(e->studentName, sizeof(e->studentName), stdin); trimNewline(e->studentName);
    printf("Course Name: ");
    fgets(e->courseName, sizeof(e->courseName), stdin); trimNewline(e->courseName);
    printf("Assignment Title: ");
    fgets(e->assignmentTitle, sizeof(e->assignmentTitle), stdin); trimNewline(e->assignmentTitle);
    printf("Due Date (DD/MM/YYYY): ");
    fgets(e->dueDate, sizeof(e->dueDate), stdin); trimNewline(e->dueDate);
    printf("Status (Pending/Done): ");
    fgets(e->status, sizeof(e->status), stdin); trimNewline(e->status);

    (*count)++;
    saveEntries(entries, *count);
    printf("Entry added successfully.\n");
}

// View entries
void viewEntries(const PlannerEntry *entries, int count) {
    printf("\n%-10s | %-15s | %-10s | %-15s | %-10s | %-10s\n", "ID", "Name", "Course", "Assignment", "Due Date", "Status");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < count; ++i) {
        printf("%-10s | %-15s | %-10s | %-15s | %-10s | %-10s\n",
               entries[i].studentID, entries[i].studentName,
               entries[i].courseName, entries[i].assignmentTitle,
               entries[i].dueDate, entries[i].status);
    }
}

// Find index by ID
int findEntryIndex(const PlannerEntry *entries, int count, const char *id) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(entries[i].studentID, id) == 0)
            return i;
    }
    return -1;
}

// Delete entry
void deleteEntry(PlannerEntry *entries, int *count) {
    char id[20];
    printf("Enter Student ID to delete: ");
    fgets(id, sizeof(id), stdin); trimNewline(id);

    int index = findEntryIndex(entries, *count, id);
    if (index == -1) {
        printf("Entry not found.\n");
        return;
    }

    for (int i = index; i < *count - 1; ++i) {
        entries[i] = entries[i + 1];
    }
    (*count)--;

    saveEntries(entries, *count);
    printf("Entry deleted.\n");
}

// Search entry
void searchEntry(const PlannerEntry *entries, int count) {
    char id[20];
    printf("Enter Student ID to search: ");
    fgets(id, sizeof(id), stdin); trimNewline(id);

    int index = findEntryIndex(entries, count, id);
    if (index == -1) {
        printf("Entry not found.\n");
        return;
    }

    PlannerEntry *e = (PlannerEntry *)&entries[index];
    printf("Student ID: %s\n", e->studentID);
    printf("Name: %s\n", e->studentName);
    printf("Course: %s\n", e->courseName);
    printf("Assignment: %s\n", e->assignmentTitle);
    printf("Due Date: %s\n", e->dueDate);
    printf("Status: %s\n", e->status);
}

// Edit entry
void editEntry(PlannerEntry *entries, int count) {
    char id[20];
    printf("Enter Student ID to edit: ");
    fgets(id, sizeof(id), stdin); trimNewline(id);

    int index = findEntryIndex(entries, count, id);
    if (index == -1) {
        printf("Entry not found.\n");
        return;
    }

    PlannerEntry *e = &entries[index];

    printf("New Student Name: ");
    fgets(e->studentName, sizeof(e->studentName), stdin); trimNewline(e->studentName);
    printf("New Course Name: ");
    fgets(e->courseName, sizeof(e->courseName), stdin); trimNewline(e->courseName);
    printf("New Assignment Title: ");
    fgets(e->assignmentTitle, sizeof(e->assignmentTitle), stdin); trimNewline(e->assignmentTitle);
    printf("New Due Date: ");
    fgets(e->dueDate, sizeof(e->dueDate), stdin); trimNewline(e->dueDate);
    printf("New Status: ");
    fgets(e->status, sizeof(e->status), stdin); trimNewline(e->status);

    saveEntries(entries, count);
    printf("Entry updated.\n");
}

// Utility: Clear input buffer
void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Utility: Trim newline from fgets
void trimNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}
