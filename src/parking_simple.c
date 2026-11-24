#include <stdio.h>
#include <string.h>

#define MAX 100
#define LEN 32

char parked[MAX][LEN], waiting[MAX][LEN];
int top = -1, front = 0, rear = 0, count = 0, capacity;

void push(const char plate[]) {
    strcpy(parked[++top], plate);
}

void enqueue(const char plate[]) {
    strcpy(waiting[rear], plate);
    rear = (rear + 1) % MAX;
    count++;
}

int exists(const char plate[]) {
    for (int i = 0; i <= top; i++)
        if (strcmp(parked[i], plate) == 0) return 1;
    for (int i = 0; i < count; i++)
        if (strcmp(waiting[(front+i)%MAX], plate) == 0) return 1;
    return 0;
}

void entry(const char plate[]) {
    if (exists(plate)) {
        printf("Vehicle %s is already in the system.\n", plate);
    } else if (top + 1 < capacity) {
        push(plate);
        printf("Vehicle %s parked at slot %d.\n", plate, top+1);
    } else if (count < MAX) {
        enqueue(plate);
        printf("Parking full. %s waiting at position %d.\n", plate, count);
    } else {
        puts("Waiting queue is full.");
    }
}

void vehicleExit(void) {
    if (top == -1) {
        puts("Parking lot is empty.");
        return;
    }
    printf("Vehicle %s has left.\n", parked[top--]);
    if (count > 0) {
        push(waiting[front]);
        front = (front + 1) % MAX;
        count--;
        printf("%s parked automatically.\n", parked[top]);
    }
}

void display(void) {
    puts("Parked vehicles (top to bottom):");
    if (top == -1) puts("None");
    for (int i = top; i >= 0; i--)
        printf("Slot %d: %s%s\n", i+1, parked[i], i==top?" (TOP)":"");
    puts("Waiting vehicles (front to rear):");
    if (count == 0) puts("None");
    for (int i = 0; i < count; i++)
        printf("Position %d: %s%s\n", i+1, waiting[(front+i)%MAX],
               i==0?" (FRONT)":"");
}

void status(void) {
    printf("Capacity: %d | Parked: %d | Free: %d | Waiting: %d\n",
           capacity, top+1, capacity-top-1, count);
}

/* Read a bounded line; discard any excess input. */
int readLine(char line[], int size) {
    if (!fgets(line, size, stdin)) return 0;
    if (!strchr(line, '\n')) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        return -1;
    }
    return 1;
}

int readNumber(void) {
    char line[80], extra;
    int n, result = readLine(line, sizeof line);
    if (result == 0) return -2;
    if (result == 1 && sscanf(line, "%3d %c", &n, &extra) == 1 && n >= 0)
        return n;
    return -1;
}

int main(void) {
    int choice;
    char line[80], plate[LEN], extra;
    puts("===== SMART PARKING LOT MANAGEMENT SYSTEM =====");
    do {
        printf("Enter parking capacity (1-100): ");
        capacity = readNumber();
        if (capacity == -2) return 0;
    } while (capacity < 1 || capacity > MAX);

    do {
        puts("\n1. Vehicle Entry\n2. Vehicle Exit\n3. Display Vehicles"
             "\n4. Parking Status\n0. Exit Program");
        printf("Enter choice: ");
        choice = readNumber();
        switch (choice) {
            case 1:
                printf("Enter vehicle number: ");
                if (readLine(line, sizeof line) == 1 &&
                    sscanf(line, "%31s %c", plate, &extra) == 1)
                    entry(plate);
                else puts("Invalid vehicle number.");
                break;
            case 2: vehicleExit(); break;
            case 3: display(); break;
            case 4: status(); break;
            case 0: puts("Thank you for using the system."); break;
            case -2: return 0;
            default: puts("Invalid choice. Try again.");
        }
    } while (choice != 0);
    return 0;
}
