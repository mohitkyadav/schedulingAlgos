#include<iostream>

using namespace std;

struct Process
{
	// Process ID
	string pid;
	float arrival_time;
	float burst_time;
	// The elapsed time between I/O interrupts (system calls)
	float elapsed_time;
	// Time spent waiting and processing the I/O
	float wait_time;
	// The priority of the process as an integer (smaller values will have higher priority)
	int priority;
};

// Function to find the waiting time for all
// processes
void waitTime(Process process[], int n, int q,float wt[])
{
	float rem_bt[n];
	for (int i = 0 ; i < n ; i++)
		rem_bt[i] =  process[i].burst_time;

	int t = 0;

	// Keep traversing processes in round robin manner until all of them are not done.
	while (1)
	{
		int flag=1;

		// Traverse all processes one by one repeatedly
		for (int i = 0 ; i < n; i++)
		{
			// If burst time of a process is greater than 0 then only need to process further
			if (rem_bt[i] > 0)
			{
				flag = 0 ; // There is a pending process

				if (rem_bt[i] > q)
				{
					// Increase the value of t i.e. shows
					// how much time a process has been processed
					t += q;

					// Decrease the burst_time of current process by quantum
					rem_bt[i] -= q;
				}

				// If burst time is smaller than or equal to quantum. Last cycle for this process
				else
				{
					// Increase the value of t i.e. shows how much time a process has been processed
					t = t + rem_bt[i];

					// Waiting time is current time minus time used by this process
					wt[i] = t - process[i].burst_time;
					rem_bt[i] = 0;
				}
			}
		}

		// If all processes are done
		if (flag == 1)
		  break;
	}
}

// Function to calculate turn around time
findTurnAroundTime(Process process[], int n,float wt[], float tat[])
{


	for (int i = 0; i < n ; i++)
		tat[i] = process[i].burst_time + wt[i];
}

// Function to calculate average time
void findavgTime(Process process[], int n, int q)
{
	float wt[n], tat[n], total_wt = 0.0, total_tat = 0.0;

	// Function to find waiting time of all processes
	waitTime(process, n, q, wt);

	// Function to find turn around time for all processes
	findTurnAroundTime(process, n, wt, tat);

	// Display processes along with all details
	cout << "Processes "<< " Waiting time " << " Turn around time\n";

	// Calculate total waiting time and total turn
	// around time
	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		cout << " " << i+1 <<"\t\t "
			 << wt[i] <<"\t\t " << tat[i] <<endl;
	}

	cout << "Average waiting time = "
		 << total_wt / n;
	cout << "\nAverage turn around time = "
		 << total_tat / n;
}

void drawGraph(Process process[], int n, int q)
{
	float wt[n], tat[n], total_wt = 0.0, total_tat = 0.0;
	ofstream outAWT;
	outAWT.open( "outAWT.txt", ofstream::out | std::ofstream::app);
	ofstream outTAT;
	outTAT.open( "outTAT.txt", ofstream::out | std::ofstream::app);
	// Function to find waiting time of all processes
	waitTime(process, n, q, wt);

	// Function to find turn around time for all processes
	findTurnAroundTime(process, n, wt, tat);


	// Calculate total waiting time and total turnaround time
	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
	}
	float avg_wt = total_wt/n;
	outAWT << avg_wt << " ";
	outAWT.close();
	float avg_tat = total_tat/n;
	outTAT << avg_tat << " ";
	outTAT.close();

/*********************************************************************************************************************************/
		   /*   YHA PE 2 GRAPH DRAW KARNE KA FUNCTION DAAL DENA*/
		   /*   avg_wt Vs q ke beech graph banana h            */
		   /*   Aur dusra avg_tat Vs q ke beech                */
/*********************************************************************************************************************************/
}
