#include <stdio.h>
#include <string.h>

#define MAX 100
#define SIZE 100

char backStack[MAX][SIZE];
char forwardStack[MAX][SIZE];

int backTop = -1;
int forwardTop = -1;

char current[SIZE];
int hasCurrent = 0;

// Push a website onto a stack
void push(char stack[MAX][SIZE], int *top, char site[]) {
    if (*top < MAX - 1) {
        (*top)++;
        strcpy(stack[*top], site);
    }
}

// Pop a website from a stack
void pop(char stack[MAX][SIZE], int *top, char site[]) {
    if (*top >= 0) {
        strcpy(site, stack[*top]);
        (*top)--;
    }
}

// Clear forward history
void clearForwardHistory() {
    forwardTop = -1;
}

// Visit a new website
void visitWebsite() {
    char site[SIZE];

    printf("Enter website URL: ");
    scanf("%99s", site);

    if (hasCurrent && strcmp(current, site) == 0) {
        printf("You are already on this website.\n");
        return;
    }

    if (hasCurrent && backTop == MAX - 1) {
        printf("Back history is full! Cannot visit a new website.\n");
        return;
    }

    if (hasCurrent) {
        push(backStack, &backTop, current);
    }

    strcpy(current, site);
    hasCurrent = 1;

    // A new visit clears forward history
    clearForwardHistory();

    printf("Website opened: %s\n", current);
}

// Go back to the previous website
void goBack() {
    if (backTop == -1) {
        printf("No previous website available.\n");
        return;
    }

    if (forwardTop == MAX - 1) {
        printf("Forward history is full!\n");
        return;
    }

    push(forwardStack, &forwardTop, current);
    pop(backStack, &backTop, current);

    printf("Moved back to: %s\n", current);
}

// Go forward to the next website
void goForward() {
    if (forwardTop == -1) {
        printf("No forward website available.\n");
        return;
    }

    if (backTop == MAX - 1) {
        printf("Back history is full!\n");
        return;
    }

    push(backStack, &backTop, current);
    pop(forwardStack, &forwardTop, current);

    printf("Moved forward to: %s\n", current);
}

// Display current website
void showCurrent() {
    if (!hasCurrent) {
        printf("No website is currently open.\n");
    } else {
        printf("Current website: %s\n", current);
    }
}

// Display complete navigation history
void displayHistory() {
    int i;

    if (!hasCurrent) {
        printf("Browsing history is empty.\n");
        return;
    }

    printf("\n--- Browsing History ---\n");

    printf("Previous websites:\n");
    if (backTop == -1) {
        printf("None\n");
    } else {
        for (i = 0; i <= backTop; i++) {
            printf("%s\n", backStack[i]);
        }
    }

    printf("Current website:\n%s\n", current);

    printf("Forward websites:\n");
    if (forwardTop == -1) {
        printf("None\n");
    } else {
        for (i = forwardTop; i >= 0; i--) {
            printf("%s\n", forwardStack[i]);
        }
    }
}

// Search all stored navigation history
void searchHistory() {
    char site[SIZE];
    int found = 0;
    int i;

    printf("Enter website URL to search: ");
    scanf("%99s", site);

    for (i = 0; i <= backTop; i++) {
        if (strcmp(backStack[i], site) == 0) {
            found = 1;
            break;
        }
    }

    if (hasCurrent && strcmp(current, site) == 0) {
        found = 1;
    }

    for (i = 0; i <= forwardTop; i++) {
        if (strcmp(forwardStack[i], site) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Website found in browsing history.\n");
    } else {
        printf("Website not found in browsing history.\n");
    }
}

// Main menu
int main() {
    int choice;

    do {
        printf("\n===== BROWSER HISTORY SIMULATOR =====\n");
        printf("1. Visit Website\n");
        printf("2. Go Back\n");
        printf("3. Go Forward\n");
        printf("4. Show Current Website\n");
        printf("5. Display Browsing History\n");
        printf("6. Search Browsing History\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                visitWebsite();
                break;

            case 2:
                goBack();
                break;

            case 3:
                goForward();
                break;

            case 4:
                showCurrent();
                break;

            case 5:
                displayHistory();
                break;

            case 6:
                searchHistory();
                break;

            case 7:
                printf("Browser simulator closed.\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 7);

    return 0;
}
