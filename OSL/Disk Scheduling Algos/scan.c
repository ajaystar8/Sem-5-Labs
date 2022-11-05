#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define LOCATIONS 8

int incomingSequence[LOCATIONS] = {176, 79, 34, 60, 92, 11, 41, 114};
int traversedLocation[LOCATIONS] = {0};
int currentHeadLocation = 50;
int accessSequence[LOCATIONS + 2] = {-1};
int totalSeeks = 0;
int pageLimit = 199;

void sortRequests(int arr[100], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void SCAN()
{
    int firstHalf[100] = {0}, secondHalf[100] = {0};
    int firstHalfSize = 0, secondHalfSize = 0, cnt = 0;

    for (int i = 0; i < LOCATIONS; i++)
    {
        if (incomingSequence[i] <= currentHeadLocation)
            firstHalf[firstHalfSize++] = incomingSequence[i];
        else
            secondHalf[secondHalfSize++] = incomingSequence[i];
    }

    sortRequests(firstHalf, firstHalfSize);
    sortRequests(secondHalf, secondHalfSize);

    // first travel till 199
    for (int i = 0; i < secondHalfSize; i++)
    {
        accessSequence[cnt++] = currentHeadLocation;
        totalSeeks += abs(currentHeadLocation - secondHalf[i]);
        currentHeadLocation = secondHalf[i];
    }

    accessSequence[cnt] = currentHeadLocation;
    totalSeeks += abs(pageLimit - currentHeadLocation);
    currentHeadLocation = 199;

    for (int i = firstHalfSize - 1; i >= 0; i--)
    {
        accessSequence[++cnt] = currentHeadLocation;
        totalSeeks += abs(currentHeadLocation - firstHalf[i]);
        currentHeadLocation = firstHalf[i];
    }

    accessSequence[++cnt] = currentHeadLocation;
}

int main()
{
    SCAN();
    printf("Seek sequence is: ");
    for (int i = 0; i < LOCATIONS + 2; i++)
        printf("%d ", accessSequence[i]);
    return 0;
}