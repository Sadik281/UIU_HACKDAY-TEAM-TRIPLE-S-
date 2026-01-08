#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define PASSWORD "1234"
#define MAX_ATTEMPTS 3

int getShiftByChoice(int choice) {
    if (choice == 1) return 1;
    if (choice == 2) return 2;
    if (choice == 3) return 4;
    return 0;
}

void showSignalByChoice(int choice) {
    if (choice == 1)
        printf("Color: Blue | Frequency: 300Hz\n");
    else if (choice == 2)
        printf("Color: Yellow | Frequency: 600Hz\n");
    else if (choice == 3)
        printf("Color: Red | Frequency: 1000Hz\n");
}

const char* getEmotionName(int choice) {
    if (choice == 1) return "Calm";
    if (choice == 2) return "Alert";
    if (choice == 3) return "Danger";
    return "Unknown";
}

// Simple encryption
void encrypt(char text[], int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = text[i] - 32;

        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = ((text[i] - 'A' + shift) % 26) + 'A';
        }
    }
}

void decrypt(char text[], int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = ((text[i] - 'A' - shift + 26) % 26) + 'A';
        }
    }
}

void saveToFile(const char* encrypted, int choice, int shift, const char* username) {
    FILE *file = fopen("military_transmissions.txt", "a");
    if (file == NULL) {
        printf("Error: Unable to save to file!\n");
        return;
    }

    time_t now = time(NULL);
    char* timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0';

    fprintf(file, "========================================\n");
    fprintf(file, "Timestamp: %s\n", timestamp);
    fprintf(file, "User: %s\n", username);
    fprintf(file, "Emotion Level: %s\n", getEmotionName(choice));
    fprintf(file, "Shift Value: +%d\n", shift);
    fprintf(file, "Encrypted Message: %s\n", encrypted);
    fprintf(file, "========================================\n\n");

    fclose(file);
    printf("\n[SUCCESS] Message saved to 'military_transmissions.txt'\n");
}

void viewHistory(const char* username) {
    FILE *file = fopen("military_transmissions.txt", "r");
    if (file == NULL) {
        printf("\nNo transmission history found.\n");
        return;
    }

    printf("\n=== Your Transmission History ===\n");
    char line[500];
    int showEntry = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "User:") != NULL) {
            if (strstr(line, username) != NULL) {
                showEntry = 1;
            } else {
                showEntry = 0;
            }
        }

        if (showEntry) {
            printf("%s", line);
        }
    }

    fclose(file);
}

void decryptMode() {
    char message[200];
    int shift;

    printf("\n=== Decryption Mode ===\n");
    printf("Enter encrypted message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;

    printf("Enter shift value (1, 2, or 4): ");
    if (scanf("%d", &shift) != 1) {
        printf("[ERROR] Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    getchar();

    decrypt(message, shift);
    printf("Decrypted Message: %s\n", message);
}

void clearHistory(const char* username) {
    char confirm;
    printf("\nAre you sure you want to clear YOUR history? (y/n): ");
    scanf("%c", &confirm);
    getchar();

    if (confirm == 'y' || confirm == 'Y') {
        FILE *file = fopen("military_transmissions.txt", "r");
        FILE *temp = fopen("temp_transmissions.txt", "w");

        if (file == NULL) {
            printf("No history to clear.\n");
            return;
        }

        if (temp == NULL) {
            printf("Error: Unable to clear history.\n");
            fclose(file);
            return;
        }

        char line[500];
        int skipEntry = 0;

        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, "========================================") != NULL) {
                skipEntry = 0;
            }

            if (strstr(line, "User:") != NULL && strstr(line, username) != NULL) {
                skipEntry = 1;
            }

            if (!skipEntry) {
                fprintf(temp, "%s", line);
            }
        }

        fclose(file);
        fclose(temp);

        remove("military_transmissions.txt");
        rename("temp_transmissions.txt", "military_transmissions.txt");

        printf("[SUCCESS] Your history cleared successfully.\n");
    } else {
        printf("Operation cancelled.\n");
    }
}

void displayBanner() {
    printf("\n");
    printf("==========================================\n");
    printf("   SECURE MILITARY ENCRYPTION \n");
    printf("     Advanced Security Features\n");
    printf("==========================================\n");
}

int authenticate(char* username) {
    char password[50];
    int attempts = 0;

    printf("\n=== LOGIN REQUIRED ===\n");
    printf("Enter Username: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = 0;

    while (attempts < MAX_ATTEMPTS) {
        printf("Enter Password: ");

        // Simple password input
        int i = 0;
        char ch;
        while ((ch = getchar()) != '\n' && i < 49) {
            password[i++] = ch;
        }
        password[i] = '\0';

        if (strcmp(password, PASSWORD) == 0) {
            printf("\n[SUCCESS] Access Granted!\n");
            printf("Welcome, %s\n", username);

            // Clear password from memory
            memset(password, 0, sizeof(password));
            return 1;
        }

        attempts++;
        printf("[ERROR] Wrong Password! Attempts remaining: %d\n", MAX_ATTEMPTS - attempts);
    }

    printf("\n[SECURITY] Too many failed attempts. Access Denied!\n");
    return 0;
}

int main() {
     system("color 0A");
    int choice;
    char message[200];
    char username[50];

    displayBanner();

    // Authentication
    if (!authenticate(username)) {
        return 1;
    }

    while (1) {
        printf("\n=== Main Menu ===\n");
        printf("1. Calm (Low Priority)\n");
        printf("2. Alert (Medium Priority)\n");
        printf("3. Danger (High Priority)\n");
        printf("4. Decrypt Message\n");
        printf("5. View Your History\n");
        printf("6. Clear Your History\n");
        printf("7. Logout\n");
        printf("Enter choice (1-7): ");

        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Invalid input!\n");
            while(getchar() != '\n');
            continue;
        }
        getchar();

        if (choice == 7) {
            printf("\n==========================================\n");
            printf("  System Logout - Stay Safe Soldier!\n");
            printf("==========================================\n");
            break;
        }

        if (choice == 4) {
            decryptMode();
            continue;
        }

        if (choice == 5) {
            viewHistory(username);
            continue;
        }

        if (choice == 6) {
            clearHistory(username);
            continue;
        }

        if (choice < 1 || choice > 3) {
            printf("[ERROR] Invalid choice! Please select 1-7.\n");
            continue;
        }

        printf("Enter Military Message: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = 0;

        // Validate input
        if (strlen(message) == 0) {
            printf("[ERROR] Message cannot be empty!\n");
            continue;
        }

        int shift = getShiftByChoice(choice);

        printf("\n--- Signal Information ---\n");
        showSignalByChoice(choice);
        encrypt(message, shift);

        printf("Shift Used: +%d\n", shift);
        printf("Encrypted Transmission: %s\n", message);

        // Save to file
        saveToFile(message, choice, shift, username);

        printf("\n[SUCCESS] Transmission Complete!\n");

        // Clear sensitive data from memory
        memset(message, 0, sizeof(message));
    }

    return 0;
}

