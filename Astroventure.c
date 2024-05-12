#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining a structure for connections between planets
typedef struct Connection Connection;

typedef struct Planet {
    char name[20];
    int number;
    struct Planet* next;
    Connection* connections;
} Planet;

struct Connection {
    struct Planet* destination;
    Connection* next;
};

// Function to create a new planet
Planet* createPlanet(char name[20], int number) {
    Planet* newPlanet = (Planet*)malloc(sizeof(Planet));
    strcpy(newPlanet->name, name);
    newPlanet->number = number;
    newPlanet->next = NULL;
    newPlanet->connections = NULL;
    return newPlanet;
}

// Function to create a new connection
Connection* createConnection(Planet* destination) {
    Connection* newConnection = (Connection*)malloc(sizeof(Connection));
    newConnection->destination = destination;
    newConnection->next = NULL;
    return newConnection;
}

// Function to add a connection to a planet's list of connections
void addConnection(Planet* planet, Connection* connection) {
    if (planet->connections == NULL) {
        planet->connections = connection;
    } else {
        Connection* current = planet->connections;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = connection;
    }
}

// Function to print the connections of a planet
void printConnections(Planet* planet) {
    Connection* current = planet->connections;
    while (current != NULL) {
        printf("-> %s ", current->destination->name);
        current = current->next;
    }
    printf("\n");
}

//Main, Game Logic
int main() {

    // Create planets and establish connections
    Planet* mercury = createPlanet("Mercury", 2);
    Planet* venus = createPlanet("Venus", 3);
    Planet* earth = createPlanet("Earth", 5);
    Planet* mars = createPlanet("Mars", 7);
    Planet* jupiter = createPlanet("Jupiter", 9);
    Planet* saturn = createPlanet("Saturn", 11);
    Planet* uranus = createPlanet("Uranus", 13);
    Planet* neptune = createPlanet("Neptune", 15);

    addConnection(mercury, createConnection(venus));
    addConnection(venus, createConnection(earth));
    addConnection(earth, createConnection(mars));
    addConnection(mars, createConnection(jupiter));
    addConnection(jupiter, createConnection(saturn));
    addConnection(saturn, createConnection(uranus));
    addConnection(uranus, createConnection(neptune));
    addConnection(neptune, createConnection(mercury));

    Planet* currentPlanet = mercury;  // Starting planet

    int totalTime = 100;
    int userScore = 0;
    int currentPlanetTime = 0;

    printf("\n\n---- Welcome to Astroventure: The Space Adventure Game ----\n\n");

    //Main Game Loop
    while (totalTime > 0) {
        printf("\nCurrent Planet: %s (%d)\n", currentPlanet->name, currentPlanet->number);
        printf("Connections: ");
        printConnections(currentPlanet);
        printf("Time Remaining: %d seconds\n", totalTime);
        printf("User Score: %d\n", userScore);

        int option;
        printf("\nSelect an option:\n");
        printf("1. Explore Planet\n");
        printf("2. Move to another Planet\n");
        printf("Your choice: ");
        scanf("%d", &option);

        if (option == 1) {
            int exploreTime;
            printf("Enter exploration time (at least 10, max %d seconds): ", totalTime);
            scanf("%d", &exploreTime);

            if (exploreTime >= 10 && exploreTime <= totalTime) {
                int explorationPoints = exploreTime * currentPlanet->number;
                userScore += explorationPoints;
                totalTime -= exploreTime;
                currentPlanetTime = exploreTime;
                printf("You explored %s for %d seconds and gained %d points!\n", currentPlanet->name, exploreTime, explorationPoints); 
                } else {
                printf("Invalid time. Please enter a time between 10 and %d seconds.\n", totalTime);
            }
        } else if (option == 2) {
            if (currentPlanetTime >= 10) {
                char choice[20];
                printf("Enter the name of the planet you want to travel to (or 'quit' to exit): ");
                scanf("%s", choice);

                if (strcmp(choice, "quit") == 0) {
                    break;
                }

                Connection* current = currentPlanet->connections;
                int found = 0;
                while (current != NULL) {
                    if (strcmp(choice, current->destination->name) == 0) {
                        currentPlanet = current->destination;
                        currentPlanetTime = 0;  // Reset time spent on new planet
                        found = 1;
                        break;
                    }
                    current = current->next;
                }

                if (!found) {
                    printf("Invalid planet. Please try again.\n");
                }else {
                    printf("You traveled to %s!\n", currentPlanet->name);
                }
            } else {
                printf("You must explore the planet for at least 10 seconds before moving.\n");
            }
        } else {
            printf("Invalid option. Please try again.\n");
        }
    }

    printf("\n\nGame Over!\n");
    printf("Final Score: %d\n", userScore);
    printf("Thanks for playing Astroventure: The Space Adventure Game!\n");

    // Free allocated memory
    free(mercury);
    free(venus);
    free(earth);
    free(mars);
    free(jupiter);
    free(saturn);
    free(uranus);
    free(neptune);
    
    return 0;
}
