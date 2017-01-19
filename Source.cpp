/*to run:
g++ -c -std=c++11 Source.cpp
g++ Source.o -o test
./test input.txt
*/

#include<fstream>
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<cassert>


using namespace std;

void openFile(ifstream& f);
void evolation();
void readFile(ifstream& f);
void output();

int lineCounter = 0;
int freenumber, total_resources;
int has[1000], max_request[1000], remaining_request[1000];
int executionOrder[1000];
bool may_not_finish[1000];
bool flag;
string fileName;


int main(int argc, char **argv) {
	ifstream f;
	
	fileName = argv[1];
	
	openFile(f);
	readFile(f);
	evolation();
	
}

void openFile(ifstream& f) {
	
	f.open(fileName);
	assert(f.is_open());
}

void readFile(ifstream& f) {
	string line;
	string value;
	stringstream lineStream;
	getline(f, line);
	total_resources = atoi(line.c_str());
	lineCounter++;
	while (f >> line >> value) {
		has[lineCounter] = atoi(line.c_str());
		max_request[lineCounter] = atoi(value.c_str());
		lineCounter++;
	}
	
}

void evolation() {
	int  j=0;
	
	freenumber = total_resources;
	
	for (int i = 1; i < lineCounter; i++) {
		freenumber = freenumber - has[i];
		may_not_finish[i] = true;
		remaining_request[i] = max_request[i] - has[i];
	}

	flag = true;
	while (flag) {
		flag = false;

		for (int i = 1; i < lineCounter; i++) {
			if ((may_not_finish[i]) && remaining_request[i] <= freenumber) {
				may_not_finish[i] = false;
				freenumber = freenumber + has[i];
				flag = true;
				executionOrder[j] = i - 1;
				j++;
			}
		}
	}
	
	if (freenumber == total_resources) {
		cout << "safe state" << endl;
		output();
	}

	else {
		cout << "unsafe state" << endl;
	}
}

void output() {
	string input;
	int process,resouces;
	
	cout << "Input state is SAFE. Enter E to execute, R to request, Q to quit." << endl;
	cin >> input;

	do {
		
		
		if (input.compare("E")==0 || input.compare("e")==0) {
			//evolation();
			
			cout << "A correct process execution order is ";
			
			for (int i = 0; i < lineCounter - 1; i++) {
				if (i == (lineCounter - 2)) {
					cout << executionOrder[i] << ". ";
				}
				else {
					cout << executionOrder[i] << "->";
				}
			}

			cout << "Enter E to execute, R to request, Q to quit." << endl;
			cin >> input;
		}
		else if (input.compare("R") == 0 || input.compare("r") == 0) {
			cout << "Which process requests the resource?" << endl;
			cin >> process;
			cout << "How many resources does process " << process << " request" << endl;
			cin >> resouces;

			if (resouces > remaining_request[process+1]) {
				cout << "Request CANNOT be granted. Enter E to execute, R to request, Q to quit." << endl;
				cin >> input;
			}
			else {
				cout << "Request CAN be granted. Enter E to execute, R to request, Q to quit." << endl;
				cin >> input;
			}

		}
		else {
			cout << "Input state is SAFE. Enter E to execute, R to request, Q to quit." << endl;
			cin >> input;
		}
	} while (input.compare("Q") != 0 && input.compare("q") != 0);
}