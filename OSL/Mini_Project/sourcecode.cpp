// Source code for OS Mini Project - Disk Scheduling Policies

#include <iostream>
#include <vector>

using namespace std;

int hardCodeRequestQueue[10] = {90, 120, 30, 40, 115, 130, 110, 80, 190, 25};

class DiskSchedulingPolicy
{

public:
    // hardcoded values should user choose not to manually enter them
    int *requestQueue;
    int globalCurrentHead;
    int queueLength;
    int *orderOfProcessing;
    int totalHeadMovement;

    // Method declarations
    void defInit();
    void manInit();
    void startDemo();
    void printAverageSeekTime(int totalHeadMovement, int totalLength);
    void FCFS();
    void SSTF();
    void SCAN();
    void CSCAN();
    void LOOK();
    void CLOOK();
};

void DiskSchedulingPolicy::defInit()
{

    requestQueue = hardCodeRequestQueue;
    orderOfProcessing = (int *)malloc(10 * sizeof(int));
    globalCurrentHead = 86;
    queueLength = 10;
    totalHeadMovement = 0;
}

void DiskSchedulingPolicy::manInit()
{

    cout << "\nEnter length of the request queue : ";
    cin >> queueLength;
    requestQueue = (int *)malloc(queueLength * sizeof(int));
    orderOfProcessing = (int *)malloc(queueLength * sizeof(int));
    cout << "\nEnter the request queue : ";
    for (int i = 0; i < queueLength; i++)
    {
        cout << "\nEnter element " << (i + 1) << ": ";
        cin >> requestQueue[i];
    }
    cout << "\nEnter the current head location : ";
    cin >> globalCurrentHead;
    totalHeadMovement = 0;
}

void DiskSchedulingPolicy::startDemo()
{

    cout << "\n\t\t Disk Scheduling Policies Demo \n\n";
    cout << "Do you want to input values or should we do it for you ? [1/0] : ";
    int choice;
    cin >> choice;

    // defaulting or user input
    if (choice)
        manInit();
    else
        defInit();

    while (true)
    {
        cout << "\n\nPolicies you can try out :";
        cout << "\n1. FCFS";
        cout << "\n2. SSTF";
        cout << "\n3. SCAN";
        cout << "\n4. C-SCAN";
        cout << "\n5. LOOK";
        cout << "\n6. C-LOOK";
        cout << "\n7. EXIT";
        cout << "\n\nWhat would you like [1-7] : ";

        cin >> choice;
        switch (choice)
        {
        case 1:
            FCFS();
            break;
        case 2:
            SSTF();
            break;
        case 3:
            SCAN();
            break;
        case 4:
            CSCAN();
            break;
        case 5:
            LOOK();
            break;
        case 6:
            CLOOK();
            break;
        case 7:
            cout << "\nThank you for using Disk Scheduling Policies Demo. Bye.\n\n";
            return;
            break;
        default:
            cout << "Unsupported choice. Please try again.";
        }
    }
}

void DiskSchedulingPolicy::printAverageSeekTime(int totalHeadMovement, int totalLength)
{

    double avgSeekTime = (double)totalHeadMovement / totalLength;
    cout << "\n\n\tAverage Seek Time : " << totalHeadMovement << " / " << totalLength << " = " << avgSeekTime;
}

void DiskSchedulingPolicy::FCFS() {}

void DiskSchedulingPolicy::SSTF() {}

void printAverageSeekTime(int totalHeadMovement, int totalLength)
{
    cout << "\n\n\tAverage Seek Time: " << (totalHeadMovement) << " / " << (totalLength) << " = " << ((double)totalHeadMovement / (double)totalLength) << endl;
}

void DiskSchedulingPolicy::SCAN()
{

    vector<int> orderOfProcessing(queueLength + 1);
    int totalHeadMovement = 0;
    int currentHead = globalCurrentHead;

    vector<int> firstHalf;
    vector<int> secondHalf;

    for (int i = 0; i < queueLength; ++i)
    {
        if (currentHead > requestQueue[i])
            firstHalf.push_back(requestQueue[i]);
        else
            secondHalf.push_back(requestQueue[i]);
    }

    sort(firstHalf.begin(), firstHalf.end());
    sort(secondHalf.begin(), secondHalf.end());

    cout << "[ ";
    for (int i = 0; i < firstHalf.size(); i++)
        cout
            << firstHalf[i] << " ";
    cout << "]";

    cout << "[ ";
    for (int i = 0; i < secondHalf.size(); i++)
        cout
            << secondHalf[i] << " ";
    cout << "]";

    cout << "\nTraverse to the inner track or the outer track?\n[0] Inner Track\n[1] Outer Track \nYour Choice? ";
    int outer;
    cin >> outer;

    cout << endl;
    cout << "\t\t+--------------------------------------+" << endl;
    cout << "\t\t|Output for SCAN Disk Scheduling Policy|" << endl;
    cout << "\t\t+--------------------------------------+" << endl;
    cout << "\n\tHead currently at: " << currentHead << endl;

    cout << "\n     Iteration \t Current Head \t Disk Movement \t Total Disk Movement" << endl;
    cout << "------------------------------------------------------------------------" << endl;

    int j = 0;
    // inner track first
    if (outer == 0)
    {
        for (int i = firstHalf.size() - 1; i >= 0; --i)
        {

            int currentDiskMovement = abs(currentHead - firstHalf[i]);
            totalHeadMovement += currentDiskMovement;
            orderOfProcessing[j] = firstHalf[i];
            currentHead = firstHalf[i];

            cout << "\t" << (++j) << "\t\t" << currentHead << "\t\t" << currentDiskMovement << "\t\t" << totalHeadMovement << endl;
        }

        // going to 0;
        totalHeadMovement += (currentHead - 0);
        orderOfProcessing[j] = 0;
        cout << "\t" << (++j) << "\t\t"
             << "0"
             << "\t\t" << currentHead << "\t\t" << totalHeadMovement << endl;
        currentHead = 0;

        for (int i = 0; i < secondHalf.size(); i++)
        {
            int currentDiskMovement = abs(currentHead - secondHalf[i]);
            totalHeadMovement += currentDiskMovement;
            orderOfProcessing[j] = secondHalf[i];
            currentHead = secondHalf[i];

            cout << "\t" << (++j) << "\t\t" << currentHead << "\t\t" << currentDiskMovement << "\t\t" << totalHeadMovement << endl;
        }
    }
    else
    {
        for (int i = 0; i < secondHalf.size(); i++)
        {
            int currentDiskMovement = abs(currentHead - secondHalf[i]);
            totalHeadMovement += currentDiskMovement;
            orderOfProcessing[j] = secondHalf[i];
            currentHead = secondHalf[i];

            cout << "\t" << (++j) << "\t\t" << currentHead << "\t\t" << currentDiskMovement << "\t\t" << totalHeadMovement << endl;
        }

        // going to 199;
        totalHeadMovement += abs(currentHead - 199);
        orderOfProcessing[j] = 199;
        cout << "\t" << (++j) << "\t\t" << 199 << "\t\t" << abs(currentHead - 199) << "\t\t" << totalHeadMovement << endl;
        currentHead = 199;

        for (int i = firstHalf.size() - 1; i >= 0; --i)
        {
            int currentDiskMovement = abs(currentHead - firstHalf[i]);
            totalHeadMovement += currentDiskMovement;
            orderOfProcessing[j] = firstHalf[i];
            currentHead = firstHalf[i];

            cout << "\t" << (++j) << "\t\t" << currentHead << "\t\t" << currentDiskMovement << "\t\t" << totalHeadMovement << endl;
        }
    }
    cout << "------------------------------------------------------------------------" << endl;

    cout << "\n\tTotal Head Movement: " << totalHeadMovement << endl;
    cout << "\n\tOrder of Processing: " << (orderOfProcessing[0]);
    for (int i = 1; i < orderOfProcessing.size(); ++i)
    {
        cout << " -> " << orderOfProcessing[i];
    }
    printAverageSeekTime(totalHeadMovement, queueLength);
    cout << endl;
}

void DiskSchedulingPolicy::CSCAN()
{
    // "requestQueue.length + 2" since, both the extra ends will be added to the queue;
    vector<int> orderOfProcessing(queueLength + 2);
    int totalHeadMovement = 0;
    int currentHead = globalCurrentHead;

    vector<int> firstHalf;
    vector<int> secondHalf;

    for (int i = 0; i < queueLength; ++i)
    {
        if (currentHead > requestQueue[i])
            firstHalf.push_back(requestQueue[i]);
        else
            secondHalf.push_back(requestQueue[i]);
    }
    sort(firstHalf.begin(), firstHalf.end());
    sort(secondHalf.begin(), secondHalf.end());

    cout << "[ ";
    for (int i = 0; i < firstHalf.size(); i++)
        cout << firstHalf[i] << " ";
    cout << "]";

    cout << "[";
    for (int i = 0; i < secondHalf.size(); i++)
        cout << secondHalf[i] << " ";
    cout << "]";

    cout << "\nTraverse to the inner track or the outer track? \n[0] Inner Track\n[1] Outer Track \nYour Choice? ";
    int outer;
    cin >> outer;

    cout << endl;
    cout << "\t\t+--------------------------------------+" << endl;
    cout << "\t\t|Output for C-SCAN Disk Scheduling Policy|" << endl;
    cout << "\t\t+--------------------------------------+" << endl;
    cout << "\n\tHead currently at: " << currentHead << endl;
    cout << "\n     Iteration \t Current Head \t Disk Movement \t Total Disk Movement" << endl;
    cout << "------------------------------------------------------------------------" << endl;

    int j = 0;
    // Inner Track First
    if (outer == 0)
    {
        for (int i = firstHalf.size() - 1; i >= 0; --i)
        {

            int currentDiskMovement = abs(currentHead - firstHalf[i]);
            totalHeadMovement += currentDiskMovement;
            orderOfProcessing[j] = firstHalf[i];
            currentHead = firstHalf[i];
            cout << "\t" << (++j) << "\t\t" << currentHead << "\t\t" << currentDiskMovement << "\t\t" << totalHeadMovement << endl;
        }

        // going to 0;
        totalHeadMovement += (currentHead - 0);
        orderOfProcessing[j] = 0;
        cout << "\t" << (++j) << "\t\t" << 0 << "\t\t" << (currentHead - 0) << "\t\t" << totalHeadMovement << endl;
        currentHead = 0;

        // going to 199;
        totalHeadMovement += abs(currentHead - 199);
        orderOfProcessing[j] = 199;
        cout << "\t" << (++j) << "\t\t" << 199 << "\t\t" << 199 << "\t\t" << totalHeadMovement << endl;
        currentHead = 199;

        for (int i = secondHalf.size() - 1; i >= 0; --i)
        {
            int currentDiskMovement = abs(currentHead - secondHalf[i]);
            totalHeadMovement += currentDiskMovement;
            orderOfProcessing[j] = secondHalf[i];
            currentHead = secondHalf[i];

            cout << "\t" << (++j) << "\t\t" << currentHead << "\t\t" << currentDiskMovement << "\t\t" << totalHeadMovement << endl;
        }
    }

    // Outer Track First;
    else
    {
        for (int i = 0; i < secondHalf.size(); i++)
        {
            int currentDiskMovement = abs(currentHead - secondHalf[i]);
            totalHeadMovement += currentDiskMovement;
            orderOfProcessing[j] = secondHalf[i];
            currentHead = secondHalf[i];

            cout << "\t" << (++j) << "\t\t" << currentHead << "\t\t" << currentDiskMovement << "\t\t" << totalHeadMovement << endl;
        }

        // going to 199;
        totalHeadMovement += abs(currentHead - 199);
        orderOfProcessing[j] = 199;
        cout << "\t" << (++j) << "\t\t" << 199 << "\t\t" << abs(currentHead - 199) << "\t\t" << totalHeadMovement << endl;
        currentHead = 199;

        // going to 0;
        totalHeadMovement += abs(currentHead - 0);
        orderOfProcessing[j] = 0;
        cout << "\t" << (++j) << "\t\t" << 0 << "\t\t" << 199 << "\t\t" << totalHeadMovement << endl;
        currentHead = 0;

        for (int i = 0; i < firstHalf.size(); i++)
        {
            int currentDiskMovement = abs(currentHead - firstHalf[i]);
            totalHeadMovement += currentDiskMovement;
            orderOfProcessing[j] = firstHalf[i];
            currentHead = firstHalf[i];

            cout << "\t" << (++j) << "\t\t" << currentHead << "\t\t" << currentDiskMovement << "\t\t" << totalHeadMovement << endl;
        }
    }
    cout << "------------------------------------------------------------------------" << endl;

    cout << "\n\tTotal Head Movement: " << totalHeadMovement << endl;
    cout << "\n\tOrder of Processing: " << (orderOfProcessing[0]);
    for (int i = 1; i < orderOfProcessing.size(); ++i)
        cout << " -> " << orderOfProcessing[i];
    printAverageSeekTime(totalHeadMovement, queueLength);
    cout << endl;
}

void DiskSchedulingPolicy::LOOK() {}

void DiskSchedulingPolicy::CLOOK() {}

int main(void)
{

    DiskSchedulingPolicy dsp;
    dsp.startDemo();
    return 0;
}