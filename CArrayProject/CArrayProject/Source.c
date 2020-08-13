#pragma warning(disable : 4996)
#include <stdio.h>

int main() {
    // Initial prompt
    printf("%s", "How many elements are we saving?\n");

    // Get response. Let's not worry about type checking
    int count;
    scanf("%i", &count);

    // Create the array
    int* arr = calloc(count, sizeof(int));
    for (int i = 0; i < count; i++)
        arr[i] = i * 10;

    // Print array
    printf("%i", arr[0]);
    for (int i = 1; i < count; i++)
        printf(", %i", arr[i]);

    // Recreate the array, but bigger
    count += 1;
    realloc(arr, count * sizeof(int));
    arr[count - 1] = (count - 1) * 10;

    // Print the array again
    print("%s", "Now again, but bigger!\n");
    printf("\n%i", arr[0]);
    for (int i = 1; i < count; i++)
        printf(", %i", arr[i]);

    // Pause
    printf("\n");
    system("pause");

    // Free our memory. Technically, Visual Studio will for us, but whatever
    free(arr);

    return 0;
}