#include <iostream>
#include <queue>
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
};

stProcess ReadInfoProcess()
{
	stProcess Process;
	cout << "Please enter the arrival time: ";
	cin >> Process.ArrivalTime;
	cout << "Please enter the Burst time: ";
	cin >> Process.BurstTime;
	Process.RemainingTime = Process.BurstTime;
	return Process;
	
}

void PrintInfoQueue(queue <stProcess> FulfilledQueue)
{
	cout << "\n=====================================================================\n";
	cout << "Process\t Completion time\t Turnaround time\t Waiting time\n";
	while (!FulfilledQueue.empty())
	{
		cout << "p" << FulfilledQueue.front().ID << "\t\t" << FulfilledQueue.front().CompletionTime <<
			"\t\t\t" << FulfilledQueue.front().TurnaroundTime << "\t\t\t" << 
			FulfilledQueue.front().WaitingTime << endl;
		FulfilledQueue.pop();
	}
}

int main()
{
	int CurrentTime = 0, NumOfProcesses = 0, TimeQuantum = 0, WaitingTime = 0;
	queue <stProcess> AllProcessesQueue, ReadyQueue, FulfilledQueue;
	stProcess Process;

	cout << "Please enter the time quantum: ";
	cin >> TimeQuantum;
	cout << "How many Processes? ";
	cin >> NumOfProcesses;
	
	// manage ids
	queue <int> IDs;
	for (int i = 1; i <= NumOfProcesses; i++)
	{
		IDs.push(i);
	}

	cout << "===================================\n";
	// store processes info in queue and handle ids
	for (int i = 1; i <= NumOfProcesses; i++)
	{
		cout << "For Process " << i << " " << endl;
		AllProcessesQueue.push(ReadInfoProcess());
		AllProcessesQueue.back().ID = IDs.front();
		IDs.pop();
		cout << "===================================\n";
	}
	//logic of algorithm
	cout << "Queue updates:\n\n";
	while (!AllProcessesQueue.empty())
	{
		if (AllProcessesQueue.front().ArrivalTime <= CurrentTime)
		{
			Process = AllProcessesQueue.front();
			ReadyQueue.push(Process);
			cout << "[p" << ReadyQueue.front().ID << "]\n";
			for (int i = TimeQuantum; i > 0 && ReadyQueue.front().RemainingTime > 0; i--)
			{
				CurrentTime++;
				ReadyQueue.front().RemainingTime--;

				// for tracing step by step 
				/*cout << "\nCPU is processing p" << ReadyQueue.front().ID << endl;
				cout << "remaining time = " << ReadyQueue.front().RemainingTime << endl;
				cout << "current time = " << CurrentTime << endl;*/
			}
			//check if process is fulfilled or not
			if (ReadyQueue.front().RemainingTime > 0) 
			{
				Process = ReadyQueue.front();
				ReadyQueue.pop(), AllProcessesQueue.pop();
				ReadyQueue.push(Process), AllProcessesQueue.push(Process);
			}
			else
			{
				ReadyQueue.front().CompletionTime = CurrentTime;
				ReadyQueue.front().TurnaroundTime = ReadyQueue.front().CompletionTime - ReadyQueue.front().ArrivalTime;
				ReadyQueue.front().WaitingTime = ReadyQueue.front().TurnaroundTime - ReadyQueue.front().BurstTime;
				WaitingTime += ReadyQueue.front().WaitingTime;
				Process = ReadyQueue.front();

				ReadyQueue.pop(), AllProcessesQueue.pop();
				FulfilledQueue.push(Process);
			}
		}

		else
		{
			CurrentTime = AllProcessesQueue.front().ArrivalTime;
			cout << "[Empty]" << endl;
		}
	}
	cout << "[Empty]" << endl;
	PrintInfoQueue(FulfilledQueue);
	cout << "Average waiting time: " << (double)WaitingTime / NumOfProcesses;
}
