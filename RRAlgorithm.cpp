#include <iostream>
#include <queue>
#include <iomanip>
using namespace  std;

struct stProcess
{
	int ID;
	int ArrivalTime; //given
	int BurstTime; //given
	int RemainingTime; // after every iteration
	int CompletionTime; // time when process is fulfilled, when remaining time = 0
	int TurnaroundTime; // time after all processes are fulfilled
	int WaitingTime; //completion - burst
    bool InQueue; //flag
    bool IsCompleted; //flag
};

void PrintQueueUpdates(queue<int> Queue) {
    if (Queue.empty()) {
        cout << "[Empty]\n";
        return;
    }
    cout << "[";
    while (!Queue.empty()) {
        cout << "P" << Queue.front();
        Queue.pop();
        if (!Queue.empty()) cout << ", ";
    }
    cout << "]\n";
}

int main() 
{
    int TimeQuantum = 0, NumOfProcesses = 0, CurrentTime = 0;
    int CompletedCount = 0;

    cout << "Please enter the time quantum: ";
    cin >> TimeQuantum;
    cout << "How many Processes? ";
    cin >> NumOfProcesses;

    stProcess* AllProcesses = new stProcess[NumOfProcesses];

    cout << "===================================\n";
    for (int i = 0; i < NumOfProcesses; i++) 
    {
        AllProcesses[i].ID = i + 1;
        cout << "Arrival Time, Needed Time P" << AllProcesses[i].ID << ": ";
        cin >> AllProcesses[i].ArrivalTime >> AllProcesses[i].BurstTime;
        AllProcesses[i].RemainingTime = AllProcesses[i].BurstTime;
        AllProcesses[i].InQueue = false;
        AllProcesses[i].IsCompleted = false;
    }
    cout << "===================================\n";

    cout << "\nQueue updates:\n\n";

    queue<int> ReadyQueue;
    queue<stProcess> FulfilledQueue;
    stProcess* PreemptedProcess = nullptr;

    while (CompletedCount < NumOfProcesses)
    {
        for (int i = 0; i < NumOfProcesses; i++) 
        {
            if (AllProcesses[i].ArrivalTime <= CurrentTime && !AllProcesses[i].InQueue &&
                !AllProcesses[i].IsCompleted && &AllProcesses[i] != PreemptedProcess)
            {

                ReadyQueue.push(AllProcesses[i].ID);
                AllProcesses[i].InQueue = true;
            }
        }

        if (PreemptedProcess != nullptr)
        {
            ReadyQueue.push(PreemptedProcess->ID);
            PreemptedProcess->InQueue = true;
            PreemptedProcess = nullptr;
        }

        PrintQueueUpdates(ReadyQueue);

        if (ReadyQueue.empty()) 
        {
            int NextArrival = -1;
            for (int i = 0; i < NumOfProcesses; i++) 
            {
                if (!AllProcesses[i].IsCompleted) 
                {
                    if (NextArrival == -1 || AllProcesses[i].ArrivalTime < NextArrival) 
                    {
                        NextArrival = AllProcesses[i].ArrivalTime;
                    }
                }
            }
            if (NextArrival != -1) 
            {
                CurrentTime = NextArrival;
                continue;
            }
        }
        int CurrentProcessID = ReadyQueue.front();
        ReadyQueue.pop();

        stProcess& CurrentProcess = AllProcesses[CurrentProcessID - 1];
        CurrentProcess.InQueue = false;

        int ExecuteTime = min(TimeQuantum, CurrentProcess.RemainingTime);
        CurrentTime += ExecuteTime;
        CurrentProcess.RemainingTime -= ExecuteTime;

        //check if process is fullfilled or not
        if (CurrentProcess.RemainingTime == 0) 
        {
            CurrentProcess.IsCompleted = true;
            CurrentProcess.CompletionTime = CurrentTime;
            CurrentProcess.TurnaroundTime = CurrentProcess.CompletionTime - CurrentProcess.ArrivalTime;
            CurrentProcess.WaitingTime = CurrentProcess.TurnaroundTime - CurrentProcess.BurstTime;

            FulfilledQueue.push(CurrentProcess);
            CompletedCount++;
        }
        else
        {
            PreemptedProcess = &CurrentProcess;
        }
    }

    PrintQueueUpdates(ReadyQueue);
    int TotalWaitingTime = 0;
    cout << "\n=====================================================================\n";
    cout << "Process\t Completion time\t Turnaround time\t Waiting time\n";

    while (!FulfilledQueue.empty()) 
    {
        stProcess p = FulfilledQueue.front();
        cout << "p" << p.ID << "\t\t"
            << p.CompletionTime << "\t\t\t"
            << p.TurnaroundTime << "\t\t\t"
            << p.WaitingTime << "\n";

        TotalWaitingTime += p.WaitingTime;
        FulfilledQueue.pop();  
    }
    cout << "=====================================================================\n";

    cout << "\nAverage waiting time: " << fixed << setprecision(1) << (double)TotalWaitingTime / NumOfProcesses;

    delete[] AllProcesses;

    return 0;
}
