#include <stdio.h>
#include <stdlib.h>

// Binary search returning key comparison count
long long binary_search_cmp(int arr[], int l, int r, int x) {
    long long cmps = 0;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        
        // Base case
        if (arr[mid] == x) return ++cmps;
        
        cmps++;
        if (arr[mid] < x) l = mid + 1;
        else r = mid - 1;
    }
    return cmps;
}

// Ternary search returning key comparison count
long long ternary_search_cmp(int arr[], int l, int r, int x) {
    long long cmps = 0;
    while (l <= r) {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;
        
        // Base cases
        if (arr[mid1] == x) return ++cmps;
        
        if (arr[mid2] == x) return ++cmps;
        
        cmps++;
        if (x < arr[mid1]) {
            r = mid1 - 1;
        } else {
            cmps++;
            if (x > arr[mid2]) {
                l = mid2 + 1;
            } else {
                l = mid1 + 1;
                r = mid2 - 1;
            }
        }
    }
    return cmps;
}

int main() {
    FILE *fp = fopen("search_comps.csv", "w");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }
    
    fprintf(fp, "N, BinaryCmps, TernaryCmps\n");

    int start_n = 10000;
    int max_n = 5000000;
    int step = 100000;

    for (int n = start_n; n <= max_n; n += step) {
        int *arr = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) arr[i] = i;

        int target = n + 1;
        long long bin_cmps = binary_search_cmp(arr, 0, n - 1, target);
        long long ter_cmps = ternary_search_cmp(arr, 0, n - 1, target);

        fprintf(fp, "%d, %lld, %lld\n", n, bin_cmps, ter_cmps);
        free(arr);
    }

    fclose(fp);
    printf("Data successfully exported to 'search_comps.csv'.\n");
    return 0;
}