#include <stdio.h>

#define TOTAL_ITEMS 5
#define LATE_FEE_PER_DAY 10

typedef struct {
    int itemNumber;
    char name[30];
    int isBorrowed;       // 0 = available, 1 = borrowed
    int studentRollNumber;
} Equipment;

void showEquipment(const Equipment items[]) {
    printf("\n--- Lab Equipment ---\n");

    for (int i = 0; i < TOTAL_ITEMS; i++) {
        printf("%d. %-20s %s\n",
               items[i].itemNumber,
               items[i].name,
               items[i].isBorrowed ? "Borrowed" : "Available");
    }
}

void borrowEquipment(Equipment items[]) {
    int itemNumber;
    int rollNumber;

    printf("Enter item number to borrow: ");
    scanf("%d", &itemNumber);

    if (itemNumber < 1 || itemNumber > TOTAL_ITEMS) {
        printf("Invalid item number.\n");
        return;
    }

    int index = itemNumber - 1;

    if (items[index].isBorrowed) {
        printf("That item is already borrowed.\n");
        return;
    }

    printf("Enter your student roll number: ");
    scanf("%d", &rollNumber);

    if (rollNumber <= 0) {
        printf("Invalid roll number.\n");
        return;
    }

    items[index].isBorrowed = 1;
    items[index].studentRollNumber = rollNumber;

    printf("%s borrowed successfully.\n", items[index].name);
}

void returnEquipment(Equipment items[]) {
    int itemNumber;
    int rollNumber;

    printf("Enter item number to return: ");
    scanf("%d", &itemNumber);

    if (itemNumber < 1 || itemNumber > TOTAL_ITEMS) {
        printf("Invalid item number.\n");
        return;
    }

    int index = itemNumber - 1;

    if (!items[index].isBorrowed) {
        printf("That item is not currently borrowed.\n");
        return;
    }

    printf("Enter the borrowing student's roll number: ");
    scanf("%d", &rollNumber);

    if (rollNumber != items[index].studentRollNumber) {
        printf("Roll number does not match the checkout record.\n");
        return;
    }

    int overdueDays;
    printf("Enter overdue days (0 if returned on time): ");
    scanf("%d", &overdueDays);

    if (overdueDays < 0) {
        printf("Overdue days cannot be negative.\n");
        return;
    }

    int fee = overdueDays * LATE_FEE_PER_DAY;

    items[index].isBorrowed = 0;
    items[index].studentRollNumber = 0;

    printf("%s returned successfully.\n", items[index].name);
    printf("Late fee: Rs. %d\n", fee);
}

int main(void) {
    Equipment items[TOTAL_ITEMS] = {
        {1, "Multimeter", 0, 0},
        {2, "Calculator", 0, 0},
        {3, "HDMI Adapter", 0, 0},
        {4, "Soldering Iron", 0, 0},
        {5, "USB Cable", 0, 0}
    };

    int choice;

    do {
        printf("\n=== Campus Lab Equipment Checkout ===\n");
        printf("1. View equipment\n");
        printf("2. Borrow equipment\n");
        printf("3. Return equipment\n");
        printf("0. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1) {
            printf("Please enter a number.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                showEquipment(items);
                break;
            case 2:
                borrowEquipment(items);
                break;
            case 3:
                returnEquipment(items);
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}