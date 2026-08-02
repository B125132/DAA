#include <stdio.h>

int findPartition(int arr[], int n)
{
    int low = 0;
    int high = n - 1;
    int ans = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == 1)
        {
            ans = mid;
            high = mid - 1;   // Search for an earlier 1
        }
        else
        {
            low = mid + 1;
        }
    }

    return ans;
}

int main()
{
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter array elements (0s followed by 1s):\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int partition = findPartition(arr, n);

    if (partition == -1)
    {
        printf("No transition from 0 to 1 found.\n");
    }
    else if (partition == 0)
    {
        printf("Array starts with 1, so there is no 0-to-1 transition.\n");
    }
    else
    {
        printf("Transition occurs between index %d and %d.\n",
               partition - 1, partition);

        printf("First 1 is at index %d.\n", partition);
    }

    return 0;
}