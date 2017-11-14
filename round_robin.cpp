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
	float a_time[n]={0};
	for (int i = 0 ; i < n ; i++)
		rem_bt[i] =  process[i].burst_time;

	int t = 0;

	// Keep traversing processes in round robin manner until all of them are not done.
	while (1)
	{
		int flag=1;
        	int i=0;
		// Traverse all processes one by one repeatedly
		while(i<n)
		{
			// If burst time of a process is greater than 0 then only need to process further
			if (rem_bt[i] > 0)
			{
				flag = 0 ; // There is a pending process
				if(a_time[i] == 0 && i > 0)
                	a_time[i]=t;

				if (rem_bt[i] > q)
                {
					// Increase the value of t i.e. shows
					// how much time a process has been processed
					t += q;

					// Decrease the burst_time of current process by quantum
					rem_bt[i] -= q;
				}

				// If burst time is smaller than or equal to quantum. Last cycle for this process
				else if(rem_bt[i] <= q)
				{
					// Increase the value of t i.e. shows how much time a process has been processed
					t = t + rem_bt[i];
                    rem_bt[i] = 0;
					// Waiting time is current time minus time used by this process
					wt[i] = t - process[i].burst_time-a_time[i];
                }
			}

           	 	if(process[i+1].arrival_time <= t && i < n - 1)
                	i++;

            	else if(process[i+1].arrival_time>t || i==n-1)
            	{
                	int point=0;
                	for(int j=0;j<=i;j++)
               		{
                   	 	if(rem_bt[j]>0)
                   		{
                     		point=1;
							i=j;
                        	break;
                    	}
                	}
               		if(point==0)
                	{
            			if(i==n-1)
            			{
							flag=1;
                    		break;
                    	}
                    	t=process[i+1].arrival_time;
                    	i++;
                	}

            	}
		}
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
	for(int i=1;i<n;i++)
   	{
    	process[i].arrival_time+=process[i-1].arrival_time;
    }
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
}
