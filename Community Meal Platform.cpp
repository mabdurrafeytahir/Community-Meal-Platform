#include <iostream>
#include <string>
using namespace std;

// ---------------- STRUCTURES ----------------

struct Meal {
    string name;
    int price;
};

struct Order {
    string mealName;
    int finalPrice;
    bool delivered;   // true = delivered, false = pending
};

// ---------------- GLOBAL DATA ----------------

Meal meals[50];
Order orders[50];

int mealCount = 0;
int orderCount = 0;

// Discount tracking
int activeDays = 0;
int skippedDays = 0;
int lockedDays = 0;
int discount = 10;
int recoveryDays = 0;

// ---------------- FUNCTIONS ----------------

void applyDiscountLogic(int skip) {

    // If discount is locked
    if (lockedDays > 0) {
        lockedDays--;
        discount = 10;
        return;
    }

    // If order is placed today
    if (skip == 0) {
        activeDays++;

        // Recover discount from 5% to 10%
        if (discount == 5) {
            recoveryDays++;
            if (recoveryDays == 2) {
                discount = 10;
                recoveryDays = 0;
            }
        }

        // Lock discount after 14 valid days
        if (activeDays == 14) {
            lockedDays = 10;
            cout << "\n Discount locked for next 10 days!\n";
        }
    }
    // If days are skipped
    else {
        skippedDays += skip;

        if (skip == 1) {
            discount = 5;
        }

        if (skippedDays >= 3) {
            activeDays = 0;
            skippedDays = 0;
            lockedDays = 0;
            discount = 10;
            recoveryDays = 0;
            cout << "\n Discount reset due to skipping 3 days.\n";
        }
    }
}

void providerMenu() {
    if (mealCount >= 50) {
        cout << "\n Meal list full.\n";
        return;
    }

    cout << "\nEnter meal name: ";
    cin.ignore();
    getline(cin, meals[mealCount].name);

    cout << "Enter price: ";
    cin >> meals[mealCount].price;

    mealCount++;
    cout << " Meal added successfully.\n";
}

void studentMenu() {
    if (mealCount == 0) {
        cout << "\n No meals available.\n";
        return;
    }

    cout << "\n Available Meals:\n";
    for (int i = 0; i < mealCount; i++) {
        cout << i + 1 << ". " << meals[i].name
             << " - Rs." << meals[i].price << endl;
    }

    int choice;
    cout << "\nSelect meal number: ";
    cin >> choice;

    int skip;
    cout << "Days skipped before order (0/1/2/3): ";
    cin >> skip;

    applyDiscountLogic(skip);

    int price = meals[choice - 1].price;
    int finalPrice = price - (price * discount / 100);

    orders[orderCount].mealName = meals[choice - 1].name;
    orders[orderCount].finalPrice = finalPrice;
    orders[orderCount].delivered = false;
    orderCount++;

    cout << "\n Order placed successfully!";
    cout << "\n Discount Applied: " << discount << "%";
    cout << "\n Final Price: Rs." << finalPrice << endl;
}

void riderMenu() {
    if (orderCount == 0) {
        cout << "\n No orders available.\n";
        return;
    }

    cout << "\n Pending Orders:\n";
    for (int i = 0; i < orderCount; i++) {
        if (!orders[i].delivered) {
            cout << i + 1 << ". " << orders[i].mealName
                 << " | Rs." << orders[i].finalPrice << endl;
        }
    }

    int num;
    cout << "\nEnter order number to deliver: ";
    cin >> num;

    orders[num - 1].delivered = true;
    cout << " Order delivered successfully.\n";
}

// ---------------- MAIN ----------------

int main() {
    int choice;

    do {
        cout << "\n==============================";
        cout << "\n COMMUNITY MEAL PLATFORM (C++)";
        cout << "\n==============================";
        cout << "\n1. Meal Provider";
        cout << "\n2. Student";
        cout << "\n3. Delivery Rider";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
            providerMenu();
        else if (choice == 2)
            studentMenu();
        else if (choice == 3)
            riderMenu();
        else if (choice == 4)
            cout << "\n Program Ended.\n";
        else
            cout << "\n Invalid choice.\n";

    } while (choice != 4);

    return 0;
}