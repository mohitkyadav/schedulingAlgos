#include "bits/stdc++.h"
#include "round_robin.cpp"

using namespace std;

void call_round_robin()
{
	Process process[] = { { "P1", 0,20,1.5,5,2 }, { "P2", 2,15,2,6,1},
                    { "P3",6,27,1.8,3.5,4}, { "P4", 4,36,2.1,2.6,3} };
	int n = sizeof(process) / sizeof(process[0]);
    int x, time_slice=3;
    cout << "Enter 1 for Complex(interrupt) case and 0 for normal case(not considering interrupts) : ";
    cin >> x;
    if(x==0)
    {
        findavgTime(process, n, time_slice);
        for(int i=1;i<=10;i++)
        {
            drawgraph(process,n,i);
        }
    }
    else
	{
        for(int i=0;i<n;i++)
		{
            process[i].burst_time+=process[i].elapsed_time+process[i].wait_time;
        }

        findavgTime(process, n, time_slice);

		for(int i=1;i<=10;i++)
        {
            drawgraph(process,n,i);
        }
    }
}

int main()
{
	cout << "\n1. Shortest Job First (SJF)" << '\n';
	cout << "2. First Come First Serve (FCFS)" << '\n';
	cout << "3. Round-robin" << '\n';

	int decider;
	std::cin >> decider;

	if (decider == 3)
	{
		call_round_robin();
	}
	cout << "Succeed\n";
	return 0;
}
