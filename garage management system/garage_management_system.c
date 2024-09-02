#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SPOTS 10
#define HOURLY_RATE 4

typedef struct {
    int occupied;
    time_t check_in_time;
} ParkingSpot;

ParkingSpot garage[MAX_SPOTS];

void initializeGarage() {
    for (int i = 0; i < MAX_SPOTS; i++) {
        garage[i].occupied = 0;
        garage[i].check_in_time = 0;
    }
}

int findVacantSpot() {
    for (int i = 0; i < MAX_SPOTS; i++) {
        if (!(garage[i].occupied)) {
            return i;
        }
    }
    return -1;
}
int x = 1;
void checkInCar() {
    int spot = findVacantSpot();
    if (spot == -1) {
        printf("Garage is full.\n");
        return;
    }
    garage[spot].occupied = 1;
    garage[spot].check_in_time = time(NULL);
    printf("1.Car\n2.Bus\n3.Truck\n4.Motorcycle\nEnter your choice: ");
    scanf("%d", &x);
    if (x == 1) {
    printf("Car checked in at spot %d.\n", spot);
    } else if (x == 2) {
    printf("Bus checked in at spot %d.\n", spot);
    } else if (x == 3) {
    printf("Truck checked in at spot %d.\n", spot);
    } else if (x == 4) {
    printf("Motorcycle checked in at spot %d.\n", spot);
    }
    FILE *log = fopen("parking_log.txt", "a");
    if (x == 1) {
        fprintf(log, "Car checked in at spot %d at %s", spot, ctime(&garage[spot].check_in_time));
    } else if (x == 2) {
        fprintf(log, "Bus checked in at spot %d at %s", spot, ctime(&garage[spot].check_in_time));
    } else if (x == 3) {
        fprintf(log, "Truck checked in at spot %d at %s", spot, ctime(&garage[spot].check_in_time));
    } else if (x == 4) {
        fprintf(log, "Motorcycle checked in at spot %d at %s", spot, ctime(&garage[spot].check_in_time));
    }
    fclose(log);
}

void checkOutCar(int spot) {
    if (!garage[spot].occupied) {
        printf("Spot %d is already vacant.\n", spot);
        return;
    }
    time_t check_out_time = time(NULL);
    double hours_parked;
    if (x == 1) {
        hours_parked = difftime(check_out_time, garage[spot].check_in_time) / 120.0;
    } else if (x == 2) {
        hours_parked = difftime(check_out_time, garage[spot].check_in_time) / 50.0;
    } else if (x == 3) {
        hours_parked = difftime(check_out_time, garage[spot].check_in_time) / 10.0;
    } else if (x == 4) {
        hours_parked = difftime(check_out_time, garage[spot].check_in_time) / 1000.0;
    }
    double fee = hours_parked * HOURLY_RATE;
    if (x == 1) {
    printf("Car checked out from spot %d. Fee: $%.2f\n", spot, fee);
    } else if (x == 2) {
    printf("Bus checked out from spot %d. Fee: $%.2f\n", spot, fee);
    } else if (x == 3) {
    printf("Truck checked out from spot %d. Fee: $%.2f\n", spot, fee);
    } else if (x == 4) {
    printf("Motorcycle checked out from spot %d. Fee: $%.2f\n", spot, fee);
    }
    
    FILE *log = fopen("parking_log.txt", "a");
if (x == 1) {
   fprintf(log, "Car checked out from spot %d at %s. Hours parked: %.2f. Fee: $%.2f\n", 
            spot, ctime(&check_out_time), hours_parked, fee);    } 
    else if (x == 2) {
   fprintf(log, "Bus checked out from spot %d at %s. Hours parked: %.2f. Fee: $%.2f\n", 
            spot, ctime(&check_out_time), hours_parked, fee);    } 
    else if (x == 3) {
   fprintf(log, "Truck checked out from spot %d at %s. Hours parked: %.2f. Fee: $%.2f\n", 
            spot, ctime(&check_out_time), hours_parked, fee);    } 
    else if (x == 4) {
   fprintf(log, "Motorcycle checked out from spot %d at %s. Hours parked: %.2f. Fee: $%.2f\n", 
            spot, ctime(&check_out_time), hours_parked, fee);    }
    fclose(log);

    garage[spot].occupied = 0;
    garage[spot].check_in_time = 0;
}

void displayGarageStatus() {
    printf("Garage status:\n");
    for (int i = 0; i < MAX_SPOTS; i++) {
        printf("Spot %d: %s\n", i, garage[i].occupied ? "Occupied" : "Vacant");
    }
}

//Yossef Nasr (My part(116,163))
void printGarageRecords() {
    FILE *log = fopen("parking_log.txt", "r");
    if (log == NULL) {
        printf("No records found.\n");
        return;
    }
    char line[256];
    printf("Garage records:\n");
    while (fgets(line, sizeof(line), log)) {
        printf("%s", line);
    }
    fclose(log);
}

int main() {
    initializeGarage();
    int choice, spot;

    while (1) {
        printf("\n1. Check-in car\n2. Check-out car\n3. Display garage status\n4. Exit\n5. Records of the garage\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkInCar();
                break;
            case 2:
                printf("Enter spot number to check-out: ");
                scanf("%d", &spot);
                checkOutCar(spot);
                break;
            case 3:
                displayGarageStatus();
                break;
            case 4:
                exit(0);
            case 5:
                printGarageRecords();
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}