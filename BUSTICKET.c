#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to store bus information
struct Bus {
    int busNumber;
    char source[50];
    char destination[50];
    int totalSeats;
    int availableSeats;
    float fare;
    struct Bus* left;
    struct Bus* right;
};

// Define a structure to store user information
struct User {
    char username[50];
    char password[50];
};

// Define a structure to store passenger information
struct Passenger {
    char name[50];
    int age;
    int seatNumber;
    int busNumber;
};

// Function to create a new bus node
struct Bus* createBusNode(int busNumber, const char* source, const char* destination, int totalSeats, float fare) {
    struct Bus* newNode = (struct Bus*)malloc(sizeof(struct Bus));
    if (newNode != NULL) {
        newNode->busNumber = busNumber;
        strcpy(newNode->source, source);
        strcpy(newNode->destination, destination);
        newNode->totalSeats = totalSeats;
        newNode->availableSeats = totalSeats;
        newNode->fare = fare;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

// Function to insert a new bus into the BST
struct Bus* insertBus(struct Bus* root, struct Bus* newBus) {
    if (root == NULL) {
        return newBus;
    }

    if (newBus->busNumber < root->busNumber) {
        root->left = insertBus(root->left, newBus);
    } else if (newBus->busNumber > root->busNumber) {
        root->right = insertBus(root->right, newBus);
    }

    return root;
}

// Function to display available buses (inorder traversal of BST)
void displayBuses(struct Bus* root) {
    if (root != NULL) {
        displayBuses(root->left);
        printf("Bus Number: %d, Source: %s, Destination: %s, Available Seats: %d\n",
               root->busNumber, root->source, root->destination, root->availableSeats);
        displayBuses(root->right);
    }
}

// Function to search for a bus by bus number
struct Bus* searchBus(struct Bus* root, int busNumber) {
    if (root == NULL || root->busNumber == busNumber) {
        return root;
    }

    if (busNumber < root->busNumber) {
        return searchBus(root->left, busNumber);
    }

    return searchBus(root->right, busNumber);
}

// Function to perform user login
int loginUser(struct User users[], int numUsers, char username[], char password[]) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i; // Return the index of the logged-in user
        }
    }
    return -1; // Return -1 if login fails
}

// Function to book a ticket
struct Bus* bookTicket(struct Bus* root, int busNumber, struct Passenger passengers[], int* numPassengers) {
    struct Bus* current = searchBus(root, busNumber);

    if (current != NULL) {
        if (current->availableSeats > 0) {
            printf("\t\tEnter the name of Passenger: ");
            scanf("%s", passengers[*numPassengers].name);

            printf("\t\tEnter Passenger Age: ");
            scanf("%d", &passengers[*numPassengers].age);

            // Assign a seat number to the passenger
            passengers[*numPassengers].seatNumber = current->totalSeats - current->availableSeats + 1;

            // Update passenger's bus number
            passengers[*numPassengers].busNumber = busNumber;

            // Update available seats
            current->availableSeats--;

            printf("\n\n===>Ticket booked successfully! Seat Number: %d==\n", passengers[*numPassengers].seatNumber);
            printf("\nThank You For Using This System\n");
            (*numPassengers)++;
        } else {
            printf("\nSorry, the bus is fully booked.\n");
        }
    } else {
        printf("==Bus with Bus Number %d not found.==\n", busNumber);
    }

    return root;
}

// Function to cancel a ticket
struct Bus* cancelTicket(struct Bus* root, int busNumber, struct Passenger passengers[], int* numPassengers) {
    struct Bus* current = searchBus(root, busNumber);

    if (current != NULL) {
        printf("==Enter Passenger Name to Cancel: ==");
        char name[50];
        scanf("%s", name);

        for (int i = 0; i < *numPassengers; i++) {
            if (strcmp(passengers[i].name, name) == 0 && passengers[i].busNumber == busNumber) {
                // Increase available seats
                current->availableSeats++;

                // Remove the passenger entry
                for (int j = i; j < (*numPassengers) - 1; j++) {
                    passengers[j] = passengers[j + 1];
                }

                (*numPassengers)--;
                printf("==Ticket canceled successfully!==\n");
                return root;
            }
        }

        printf("^^Passenger with name %s not found on this bus.^^\n", name);
    } else {
        printf("^^Bus with Bus Number %d not found.^^\n", busNumber);
    }

    return root;
}

int main() {
    struct Bus* root = NULL;
    struct User users[3] = {{"user1", "pass1"}, {"user2", "pass2"}, {"user3", "pass3"}};
    int numUsers = 3;

    // Create and insert bus nodes into the BST
    root = insertBus(root, createBusNode(101, "City A", "City B", 50, 25.0));
    root = insertBus(root, createBusNode(102, "City C", "City D", 40, 20.0));
    root = insertBus(root, createBusNode(103, "City E", "City F", 30, 15.0));

    char enteredUsername[50];
    char enteredPassword[50];
    printf("\n  =========================  LOGIN FORM  =========================  ");
    printf("\n\n==>ENTER YOUR USER NAME:>");
    scanf("%s", enteredUsername);
    printf("==>ENTER YOUR PASSWORD:>");
    scanf("%s", enteredPassword);

    int loggedInUserId = loginUser(users, numUsers, enteredUsername, enteredPassword);

    if (loggedInUserId == -1) {
        printf("\n SORRY !!!!  LOGIN IS UNSUCESSFUL");
        return 1;
    } else {
        printf("\n\t\tWELCOME TO OUR SYSTEM !!!! LOGIN IS SUCCESSFUL");

    }

    int choice;
    struct Passenger passengers[500];
    int numPassengers = 0;

    do {
        // Display main menu
        printf("\n\n=====WELCOME TO BUS RESERVATION SYSTEM=====\n");
        printf("\t\t\t\t\t[1]=> Available Buses\n");
        printf("\n");
        printf("\t\t\t\t\t[2]=> Book Tickets\n");
        printf("\n");
        printf("\t\t\t\t\t[3]=> Cancle Booking\n");
        printf("\n");
        printf("\t\t\t\t\t[4]=>Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform actions based on user choice
        switch (choice) {
            case 1:
                displayBuses(root);
                break;
            case 2:
                printf("=>Enter the number of bus to Book a Ticket:>");
                int bookBusNumber;
                scanf("%d", &bookBusNumber);
                root = bookTicket(root, bookBusNumber, passengers, &numPassengers);
                break;
            case 3:
                printf("=>Enter the number of bus to Book a Ticket:---->");
                int cancelBusNumber;
                scanf("%d", &cancelBusNumber);
                root = cancelTicket(root, cancelBusNumber, passengers, &numPassengers);
                break;
            case 4:
                printf("==Exiting the program.==\n");
                break;
            default:
                printf("^=Invalid choice. Please try again.^=\n");
        }
    } while (choice != 4);

    // TODO: Free allocated memory before exiting

    return 0;
}