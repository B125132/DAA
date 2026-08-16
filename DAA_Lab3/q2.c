#include <stdio.h>
#include <stdlib.h> // Added for malloc, free, rand, srand
#include <time.h>   // Added for time (to seed the random generator)

// Function to weigh two groups of coins
int weigh(int coins[], int left_start, int left_end, int right_start, int right_end) {
    int left_weight = 0;
    int right_weight = 0;

    for (int i = left_start; i <= left_end; i++) {
        left_weight += coins[i];
    }
    for (int i = right_start; i <= right_end; i++) {
        right_weight += coins[i];
    }

    if (left_weight < right_weight) return -1;
    if (left_weight > right_weight) return 1;
    return 0;
}

// Recursive Divide and Conquer function
int searchDefective(int coins[], int low, int high, int known_good) {
    int n = high - low + 1;

    // Base case: Only 1 coin left to check
    if (n == 1) {
        if (known_good != -1) {
            int res = weigh(coins, low, low, known_good, known_good);
            if (res < 0) {
                return low; 
            } else {
                return -1;  
            }
        }
        return -1; 
    }

    // Divide step: Split into two equal halves
    int half_size = n / 2;
    int mid = low + half_size - 1;
    
    int left_start = low;
    int left_end = mid;
    int right_start = mid + 1;
    int right_end = mid + half_size;

    // Weigh the two halves against each other
    int res = weigh(coins, left_start, left_end, right_start, right_end);

    if (res == 0) {
        known_good = left_start;
        if (n % 2 != 0) {
            return searchDefective(coins, high, high, known_good);
        } else {
            return -1;
        }
    } else if (res < 0) {
        known_good = right_start;
        return searchDefective(coins, left_start, left_end, known_good);
    } else {
        known_good = left_start;
        return searchDefective(coins, right_start, right_end, known_good);
    }
}

// Wrapper function for ease of use
int findDefectiveCoin(int coins[], int n) {
    if (n < 2) {
        printf("Need at least 2 coins to find a defective one by comparison.\n");
        return -1;
    }
    return searchDefective(coins, 0, n - 1, -1);
}

int main() {
    int n, choice;

    // Prompt user for the number of coins
    printf("Enter the number of coins: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (n < 2) {
        printf("Need at least 2 coins to find a defective one by comparison.\n");
        return 1;
    }

    // Ask user for input method
    printf("\nHow would you like to populate the array?\n");
    printf("1. Generate random array\n");
    printf("2. Enter weights manually\n");
    printf("Enter choice (1 or 2): ");
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Invalid choice.\n");
        return 1;
    }

    // Dynamically allocate memory for the array
    int *coins = (int *)malloc(n * sizeof(int));
    if (coins == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Populate the array based on user choice
    if (choice == 1) {
        // Seed the random number generator
        srand(time(NULL));
        int standard_weight = 10;
        
        for (int i = 0; i < n; i++) {
            coins[i] = standard_weight;
        }

        // Randomly choose an index for the defective coin (or none if index == n)
        int defective_index = rand() % (n + 1); 
        if (defective_index < n) {
            coins[defective_index] = standard_weight - 1; // Make it lighter
        }

        // Print the generated array so the user can verify the result
        printf("\nGenerated array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", coins[i]);
        }
        printf("\n");
    } else {
        printf("\nEnter the weights of the %d coins, separated by spaces:\n", n);
        for (int i = 0; i < n; i++) {
            if (scanf("%d", &coins[i]) != 1) {
                printf("Invalid weight input.\n");
                free(coins); 
                return 1;
            }
        }
    }

    // Find the defective coin
    int result = findDefectiveCoin(coins, n);
    
    // Output the result
    if (result != -1) {
        printf("Defective coin found at index %d (Weight: %d)\n", result, coins[result]);
    } else {
        printf("No defective coin found.\n");
    }

    free(coins);
    return 0;
}