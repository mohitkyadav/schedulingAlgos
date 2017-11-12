#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

/*void swapProcess(vector< vector<string> > process, int row, int m) {
    for(int j = 0; j < 9; j++) {
            string temp = process[row][j];
            process[row][j] = process[m][j];
            process[m][j] = temp;
    }

}*/

vector< vector <string> > sortProcess(vector< vector<string> > process) {

    int m = 0;
    for(int k = 0;k < process.size()-1;k++) {
    for(int i = 0;i<process.size()-k-1;i++) {
        if(process[i][5]>process[i+1][5]) {
            for(int j = 0; j < 9; j++) {
            string temp = process[i][j];
            process[i][j] = process[i+1][j];
            process[i+1][j] = temp;
    }
        }

    }
    }
    return process;
}

void burstTime(int bTime[],vector< vector <string> > process , int s) {
    int x = 0;
    for(int i=0;i<s;i++) {
        // object from the class stringstream
    stringstream stringTointeger(process[i][6]);

    // The object has the value 12345 and stream
    // it to the integer x
    x = 0;
    stringTointeger >> x;
    bTime[i] = x;
    }
}

void arrivalTime(int aTime[],vector< vector <string> > process,int s) {
    int x = 0;
    for(int i=0;i<s;i++) {
        // object from the class stringstream
    stringstream geek(process[i][5]);

    // The object has the value 12345 and stream
    // it to the integer x
    x = 0;
    geek >> x;
    aTime[i] = x;
    }

}

void turnAroundTime(int taTime[],int wTime[], int bTime[],int s) {

        for(int i = 0;i<s; i++) {
            taTime[i] = wTime[i] + bTime[i];
        }

}

void waitingTime(int wTime[] , int bTime[] , int aTime[] , int s) {
      for(int i=1; i<s; i++) {
            wTime[i] = wTime[i-1] + bTime[i-1] - aTime[i];
            if(wTime[i]<0) {
                wTime[i] = 0;
            }
      }

}

float calAvgwTime(int wTime[],int s) {
    float avg = 0;
    for(int i=0;i<s;i++) {
        avg += wTime[i];
    }
    avg /= s;
    return avg;
}

float calAvgTaTime(int taTime[],int s) {
    float avg = 0;
    for(int i=0;i<s;i++) {
        avg += taTime[i];
    }
    avg /= s;
    return avg;
}
