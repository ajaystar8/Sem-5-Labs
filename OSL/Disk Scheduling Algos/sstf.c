#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define LOCATIONS 8

int incomingSequence[LOCATIONS] = {176, 79, 34, 60, 92, 11, 41, 114};
int traversedLocation[LOCATIONS] = {0};
int currentHeadLocation = 50;
int accessSequence[LOCATIONS + 1] = {-1};
int seekDifference[LOCATIONS] = {-1};
int totalSeeks = 0;

void findDifference()
{
    for (int i = 0; i < LOCATIONS; i++)
        seekDifference[i] = abs(currentHeadLocation - incomingSequence[i]);
}

int findMinSeekLoc()
{
    // will return index of minimum seek location
    int minSeek = INT8_MAX;
    int minIndex = -1;
    for (int i = 0; i < LOCATIONS; i++)
    {
        if (!traversedLocation[i] && (seekDifference[i] < minSeek))
        {
            minSeek = seekDifference[i];
            minIndex = i;
        }
    }
    traversedLocation[minIndex] = 1;
    return minIndex;
}

void SSTF()
{
    for (int i = 0; i < LOCATIONS; i++)
    {
        accessSequence[i] = currentHeadLocation;
        findDifference();
        int nextSeekIndex = findMinSeekLoc();
        totalSeeks += abs(currentHeadLocation - incomingSequence[nextSeekIndex]);
        currentHeadLocation = incomingSequence[nextSeekIndex];
    }
    accessSequence[LOCATIONS] = currentHeadLocation;
}

int main()
{
    SSTF();
    printf("Seek sequence is: ");
    for (int i = 0; i < LOCATIONS + 1; i++)
        printf("%d ", accessSequence[i]);
    return 0;
}