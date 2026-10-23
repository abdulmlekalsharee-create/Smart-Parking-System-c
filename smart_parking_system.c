#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



#define MAX_SLOTS 100
#define NAME_LEN 50
#define PLATE_LEN 20




#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_CYAN    "\x1b[36m"





typedef enum {
    SEDAN = 1,
    SUV,
    TRUCK
} CarType;



typedef struct {
    unsigned int isOccupied : 1;
    unsigned int hasPaid : 1;
} Status;




typedef struct {
    char driverName[NAME_LEN];
    char plateNumber[PLATE_LEN];
    CarType type;
    time_t entryTime;
    Status status;
} ParkingSlot;



void clearScreen();
void printHeader();
void visualizeParking(ParkingSlot *parking, int size);
int parkCar(ParkingSlot *parking, int size);
int removeCar(ParkingSlot *parking, int size);
void saveReceipt(char *name, char *plate, double cost);
double calculateRevenueRecursive(ParkingSlot *parking, int index, int size); 
void generateWelcomeMessage(char *dest, const char *src);






int main() {
    int capacity, choice;
    ParkingSlot *myParking = NULL;

    clearScreen();
    printHeader();
    
    //  Memory Allocation (MALLOC)
    printf(ANSI_COLOR_CYAN "Enter Total Parking Capacity: " ANSI_COLOR_RESET);
    scanf("%d", &capacity);

    if (capacity <= 0 || capacity > MAX_SLOTS){
        printf(ANSI_COLOR_RED "Error : Parking Capacity must be between 1 and %d (physical space limit).\n" ANSI_COLOR_RESET, MAX_SLOTS);
        return 1;
    }

    myParking = (ParkingSlot *)malloc(capacity * sizeof(ParkingSlot));
    if (myParking == NULL) {
        printf("Memory Allocation Failed!\n");
        return 1;
    }

    for (int i = 0; i < capacity; i++) {
        myParking[i].status.isOccupied = 0;
        myParking[i].status.hasPaid = 0;
    }

    do {
        clearScreen();
        printHeader();
        



        visualizeParking(myParking, capacity);

        printf("\n" ANSI_COLOR_YELLOW "--- MENU ---" ANSI_COLOR_RESET "\n");
        printf("1. Park a Car (Add)\n");
        printf("2. Remove a Car (Exit & Pay)\n");
        printf("3. Show Total Potential Revenue (Recursive)\n");
        printf("4. Exit System\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                parkCar(myParking, capacity);
                break;
            case 2:
                removeCar(myParking, capacity);
                break;
            case 3:
                printf(ANSI_COLOR_GREEN "\nEstimated Revenue from current cars: $%.2f\n" ANSI_COLOR_RESET, 
                       calculateRevenueRecursive(myParking, 0, capacity));
                printf("Press Enter to continue...");
                getchar(); getchar();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }
    } while (choice != 4);

    free(myParking);
    return 0;
}


void visualizeParking(ParkingSlot *parking, int size) {
    printf("\n" ANSI_COLOR_BLUE "--- LIVE PARKING VIEW ---" ANSI_COLOR_RESET "\n");
    for (int i = 0; i < size; i++) {
        if (parking[i].status.isOccupied) {
            printf(ANSI_COLOR_RED "[ CAR %02d ] " ANSI_COLOR_RESET, i + 1);
        } else {
            printf(ANSI_COLOR_GREEN "[ FREE %02d ] " ANSI_COLOR_RESET, i + 1);
        }
        if ((i + 1) % 5 == 0) printf("\n");
    }
    printf("\n-------------------------\n");
}

int parkCar(ParkingSlot *parking, int size) {
    char tempPlate[PLATE_LEN];
    char tempName[NAME_LEN];
    int type;

    int foundIndex = -1;
    for (int i = 0; i < size; i++) {
        if (!parking[i].status.isOccupied) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf(ANSI_COLOR_RED "Parking is FULL!\n" ANSI_COLOR_RESET);
        getchar(); getchar();
        return 0;
    }

    printf("\nEnter Plate Number (must include '-'): \n");
    scanf("%s", tempPlate);

    if (strlen(tempPlate) < 3) {
        printf("Error: Plate number too short!\n");
        getchar(); getchar();
        return 0;
    }

    if (strchr(tempPlate, '-') == NULL) {
        printf("Error: Invalid format! Plate must contain '-'\n");
        getchar(); getchar();
        return 0;
    }

    printf("Enter Driver Name:\n ");
    scanf("%s", tempName);
    
    printf("Select Car Type (1.Sedan, 2.SUV, 3.Truck): ");
    scanf("%d", &type);


    strcpy(parking[foundIndex].plateNumber, tempPlate);
    strcpy(parking[foundIndex].driverName, tempName);
    parking[foundIndex].type = (CarType)type;
    parking[foundIndex].entryTime = time(NULL); 
    parking[foundIndex].status.isOccupied = 1;

    char welcomeMsg[100] = "Welcome, ";
    generateWelcomeMessage(welcomeMsg, tempName); 
    printf("%s\n", welcomeMsg);
    
    getchar(); getchar();
    return 1;
}

int removeCar(ParkingSlot *parking, int size) {
    char searchPlate[PLATE_LEN];
    printf("Enter Plate Number to Exit: ");
    scanf("%s", searchPlate);

    for (int i = 0; i < size; i++) {
      
        if (parking[i].status.isOccupied && strcmp(parking[i].plateNumber, searchPlate) == 0) {
            
         
            double cost = 10.0 * parking[i].type; 
            
            printf(ANSI_COLOR_GREEN "Car Found! Total Cost: $%.2f\n" ANSI_COLOR_RESET, cost);
            
            saveReceipt(parking[i].driverName, parking[i].plateNumber, cost);
            
            parking[i].status.isOccupied = 0;
            printf("Car Removed & Receipt Saved.\n");
            getchar(); getchar();
            return 1;
        }
    }
    printf("Car Not Found!\n");
    getchar(); getchar();
    return 0;
}

void generateWelcomeMessage(char *dest, const char *src) {
    strcat(dest, src);
    strcat(dest, " to our Smart Parking!");
}

double calculateRevenueRecursive(ParkingSlot *parking, int index, int size) {
    if (index >= size) return 0; 
    double currentVal = 0;
    if (parking[index].status.isOccupied) {
        currentVal = 10.0 * parking[index].type;
    }

    return currentVal + calculateRevenueRecursive(parking, index + 1, size);
}

void saveReceipt(char *name, char *plate, double cost) {
    FILE *file = fopen("receipt.txt", "a");
    if (file != NULL) {
        fprintf(file, "--- RECEIPT ---\nDriver: %s\nPlate: %s\nCost: $%.2f\n---------------\n", name, plate, cost);
        fclose(file);
    }
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader() {
    printf(ANSI_COLOR_CYAN);
    printf("==========================================\n");
    printf("      SMART PARKING SYSTEM                \n");
    printf("==========================================\n");
    printf(ANSI_COLOR_RESET);
}