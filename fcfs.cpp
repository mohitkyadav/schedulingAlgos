#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;

vector< vector <string> > fcfssortProcess(vector< vector<string> > process)
{

    int m = 0;
    for(int k = 0;k < process.size();k++) {
    	for(int i = 0;i<process.size()-k-1;i++) {
       	 if(process[i][1]>process[i+1][1]) {
            for(int j = 0; j < 6; j++) {
           	 string temp = process[i][j];
          	 process[i][j] = process[i+1][j];
           	 process[i+1][j] = temp;
            }
         }
         else if(process[i][1] == process[i+1][1]) {
                if(process[i][5]>=process[i+1][5]){
            for(int j = 0; j < 6; j++) {
           	 string temp = process[i][j];
          	 process[i][j] = process[i+1][j];
           	 process[i+1][j] = temp;
            }
         }
    	}

        }
    }
    return process;
}

void fcfsburstTime(float bTime[],vector< vector <string> > process , int s)
{
    float x = 0;
    for(int i=0;i<s;i++)
    {
        // object from the class stringstream
        stringstream stringTointeger(process[i][2]);

        // The object has the value 12345 and stream
        // it to the integer x
        x = 0;
        stringTointeger >> x;
        bTime[i] = x;
    }
}

void fcfsarrivalTime(float aTime[],vector< vector <string> > process,int s)
{
    float x = 0;
	//cout<<"            "<<"T1   T2   T3   T4   T5   T6   T7   T8   T9   T10"<<endl;
    for(int i=0;i<s;i++)
    {
        // object from the class stringstream
         stringstream geek(process[i][1]);

         // The object has the value 12345 and stream
        // it to the integer x
        x = 0;
        geek >> x;
        aTime[i] = x;
    }
}

void fcfsturnAroundTime(float taTime[],float wTime[], float bTime[],int s)
{

    for(int i = 0;i<s; i++)
    {
        taTime[i] = wTime[i] + bTime[i];
    }
}

void fcfswaitingTime(float wTime[] , float bTime[] , float aTime[] , int s)
{
    for(int i=1; i<s; i++)
    {
        wTime[i] = wTime[i-1] + bTime[i-1] - aTime[i];
        if(wTime[i]<0)
        {
            wTime[i] = 0;
        }
    }
}

float fcfscalAvgwTime(float wTime[],int s)
{
    float avg = 0;
    for(int i=0;i<s;i++)
    {
        avg += wTime[i];
    }

    avg /= s;

    return avg;
}

float fcfscalAvgTaTime(float taTime[],int s)
{
    float avg = 0;
    for(int i=0;i<s;i++)
    {
        avg += taTime[i];
    }

    avg /= s;

    return avg;
}

float calculateSD(float tat[] , int n)
{
	float sum = 0.0 , mean , standardDeviation = 0.0;
	int i=0;
	for(i=0;i<n;i++)
	{
		sum += tat[i];
	}
	mean  = sum/n;
	 for(i=0;i<n;i++)
	 {
		standardDeviation += pow(tat[i]-mean , 2);
	}
	return sqrt(standardDeviation/n);
}

void fcfs(vector< vector <string> > aray)
{
    int response = 0;
    cout<<"\nPress 1 for complex input and 0 for normal input\n";
    cin>>response;
    vector< vector<string> > newaray = fcfssortProcess(aray);
    int s = newaray.size();
    float wTime[s] , taTime[s] , aTime[s], bTime[s];
    float  avgwTime = 0 , avgtaTime = 0;
    float standardDeviation = 0.0;
    wTime[0] = 0;
    fcfsarrivalTime(aTime,newaray,s);
    fcfsburstTime(bTime,newaray,s);

    if (response == 1)
    {
        for(int i = 0;i < newaray.size();i++)
        {
            stringstream a(newaray[i][3]);  //interrupt time
            stringstream b(newaray[i][4]);   //extra waiting time
            //stringstream c(aray[i][2]);
            float x=0,y=0;
            a >> x;
            b >> y;

            bTime[i] += x + y;

        }
    }

    fcfswaitingTime(wTime,bTime,aTime,s);
    avgwTime = fcfscalAvgwTime(wTime,s);
    fcfsturnAroundTime(taTime,wTime,bTime,s);
    avgtaTime = fcfscalAvgTaTime(taTime,s);
    standardDeviation = calculateSD(taTime,s);
    cout<<"\n\n";
    // print out what was read in

    cout<<setw(9)<<left<<"PName"<<setw(9)<<left<<"ArTime"<<setw(9)<<left<<"BstTime"<<setw(9)<<left<<"Interrupt"<<setw(9)<<left<<" +wtime"<<setw(9)<<left<<"Priority"<<setw(9)<<left<<"WT"<<setw(9)<<left<<"TAT"<<setw(9)<<left<<"updated burst"<<endl;
    for (size_t i=0; i<newaray.size(); ++i)
    {
        for (size_t j=0; j<newaray[i].size(); ++j)
        {
         //   if(j == 2) {
         //   cout <<setw(8)<<left<<bTime[i]<<"|";
       // }
       // else {
            cout <<setw(8)<<left<<newaray[i][j]<<"|"; // (separate fields by |)
       // }
        }
        cout<<setw(8)<<left<<wTime[i]<<"|"<<setw(7)<<left<<taTime[i]<<"|";
        cout<<setw(8)<<left<<bTime[i];  //updated burst time
        cout << "\n";
    }

    cout<<"\n"<<"Average waiting time:"<<avgwTime;
    cout<<"\n"<<"Average Turn around time:"<<avgtaTime;
    cout<<"\nStandard Deviation is:"<<standardDeviation;

}
