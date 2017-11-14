#include "bits/stdc++.h"
#include <stdio.h>

#include "round_robin.cpp"
#include "fcfs.cpp"
#include "sjf.cpp"

using namespace std;

// splits the line into a vector of string
Process split(const string &text, char sep)
{
	Process commands;
	size_t start = 0, end = 0;

	end = text.find(sep, start);
	commands.pid = text.substr(start, end - start);
	start = end + 1;

	end = text.find(sep, start);
	stringstream ss;
	ss << (text.substr(start, end - start));
	ss >> commands.arrival_time;
	start = end + 1;

	end = text.find(sep, start);
	commands.burst_time = stof((text.substr(start, end - start)));
	start = end + 1;

	end = text.find(sep, start);
	commands.elapsed_time = stof((text.substr(start, end - start)));
	start = end + 1;

	end = text.find(sep, start);
	commands.wait_time = stof((text.substr(start, end - start)));
	start = end + 1;

	end = text.find(sep, start);
	commands.priority = stof((text.substr(start, end - start)));

	return commands;
}

void call_round_robin(Process *processes, int n)
{
	int x, time_slice = 3;
	cout << "Enter 1 for Complex(interrupt) case and 0 for normal case(not considering interrupts) : ";
	cin >> x;
	if(x == 0)
	{
		findavgTime(processes, n, time_slice);
		for(int i = 1; i <= 10; i++)
		{
			drawGraph(processes, n, i);
		}
		system("python graphAWT.py");
		remove("outAWT.txt");
		system("python graphTAT.py");
		remove("outTAT.txt");
	}
	else
	{
		for(int i = 0; i < n; i++)
		{
			processes[i].burst_time += processes[i].elapsed_time+processes[i].wait_time;
		}

		findavgTime(processes, n, time_slice);

		for(int i = 1; i <= 10; i++)
		{
			drawGraph(processes, n, i);
		}
		system("python graphAWT.py");
		remove("outAWT.txt");
		system("python graphTAT.py");
		remove("outTAT.txt");
	}
}

void call__fcfs(string input_file)
{
	ifstream in(input_file);

    string line, field;

    vector< vector<string> > aray;  // the 2D array
    vector<string> v;                // array of values for one line only

    while ( getline(in,line) )    // get next line in file
    {
        v.clear();
        stringstream ss(line);

        while (getline(ss,field,' '))  // break line into comma delimitted fields
        {
            v.push_back(field);  // add each field to the 1D array
        }

        aray.push_back(v);  // add the 1D array to the 2D array
    }
    fcfs(aray);
}

void call_sjf(Process *processes, int n)
{
	int x;
	cout << "Enter 1 for Complex(interrupt) case and 0 for normal case(not considering interrupts) : ";
	cin >> x;
	if(x==0)
		findavgTime(processes, n);
	else
	{
		for(int i=0;i<n;i++)
		{
			processes[i].burst_time += processes[i].elapsed_time + processes[i].wait_time;
		}
		findavgTime(processes, n);
	}
}

int main()
{
	string input_file_name, line;
	cout << "Please input the file name(including extension) : ";
	cin >> input_file_name;
	while(1)
	{
		ifstream input_file (input_file_name);
		int num = 4;

		Process processes[num];
		if (input_file.is_open())
		{
			int i = 0;
			while ( getline (input_file, line))
			{
				processes[i] = split(line, ' ');
				i++;
			}
			input_file.close();
		}
		for (size_t i = 0; i < num; i++)
		{
			cout << endl;
			cout << processes[i].pid << " " << processes[i].arrival_time  << " ";
			cout << processes[i].burst_time << " " << processes[i].elapsed_time  << " ";
			cout << processes[i].wait_time << " " << processes[i].priority;
			cout << endl;
		}
		cout << "\n1. Shortest Job First (SJF)" << '\n';
		cout << "2. First Come First Serve (FCFS)" << '\n';
		cout << "3. Round-robin" << '\n';

		int decider;
		cin >> decider;
		if(decider == 2)
		{
			call__fcfs(input_file_name);
		}
		else if (decider == 1)
		{
			call_sjf(processes, sizeof(processes)/sizeof(processes[0]));
		}
		else if (decider == 3)
		{
			call_round_robin(processes, sizeof(processes)/sizeof(processes[0]));
		}
	}
	return 0;
}
