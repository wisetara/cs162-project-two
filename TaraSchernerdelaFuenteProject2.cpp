// Project 2 - Physical Exercise Recorder (TaraSchernerdelaFuenteProject2)
// Written by: Tara Scherner de la Fuente
// Date: 6 July 2017
// Sources: None.

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

const int SIZE = 128;
const int NOT_FOUND = -1;

struct exerciseData
{
    char name[SIZE];
    char date[SIZE];
    char note[SIZE];
    int time;
    int calories;
    int maxHeartRate;
};

int loadData(exerciseData exerciseList[]); // pass the array of structs, return total exercises read.
int search(exerciseData exerciseList[], int count); // pass the array and the number of items in the array.
void list(exerciseData exerciseList[], int count); // Print all data in the list.
void logThisYo(char record, double minutesNumber, double &totalMinutes, double caloriesNumber, double &totalCalories, int &indexCount);
void add(exerciseData exerciseList[], int count); // Add item to the list.
void dataCheck();

int main ()
{
	char another = 'Y';
	char answer = 'L';
	int indexCount = 0;
	int searchCount;
	exerciseData exerciseList[SIZE];

	cout << fixed << showpoint << setprecision(1);
	cout << endl << "Welcome to the exercise tracking program." << endl << endl;
	indexCount = loadData(exerciseList);

	while (answer != 'Q') {
		cout << "What would you like to do? (L)ist all, (S)earch by name, (A)dd an exercise, or (Q)uit?" << endl;
		// cin.clear();
		cin.get(answer);
		cin.ignore();
		answer = static_cast<char>(toupper(answer));
		switch (answer)
		{
			case 'L':
				list(exerciseList, indexCount);
				break;
			case 'S':
				searchCount = search(exerciseList, indexCount);
				cout << endl << "Found a total of " << searchCount << " entries." << endl;
				break;
			case 'A':
				add(exerciseList, indexCount);
				break;
			case 'Q':
				cout << "Thanks for using the Physical Exercise Recorder!" << endl;
				return 0;
		}
	}
}

int loadData(exerciseData exerciseList[SIZE]) // pass the array of structs, return total exercises read.
{
	int index;
	ifstream inFile;
	char filename[SIZE];
	char tempStr[SIZE];

	cout << "What is the name of the exercise data text file to load?" << endl;
	cin.getline(filename, SIZE);

	inFile.open(filename);

	while (!inFile.is_open()) {
     	cout << "I don't think it opened. Give me the file name again, please." << endl;
     	cin.clear();
     	cin.getline(filename, SIZE);
    	inFile.open(filename);
    }

	if (inFile.is_open())
	{
		while (!inFile.eof())
			// I'm using the tempStr[SIZE]/strcpy things to follow directions, but I'm
			// not sure why I'm not just going direct, like `inFile.getline(exerciseList[index].note, SIZE, ',');`
			// or something like that. I am trying to trust the process. :-)
		{
			inFile.getline(tempStr, SIZE, ',');
			strcpy(exerciseList[index].name, tempStr);
			inFile.getline(tempStr, SIZE, ',');
			strcpy(exerciseList[index].date, tempStr);
			inFile.getline(tempStr, SIZE, ',');
			strcpy(exerciseList[index].note, tempStr);
			inFile >> exerciseList[index].time;
			inFile.ignore();
			inFile >> exerciseList[index].calories;
			inFile.ignore();
			inFile >> exerciseList[index].maxHeartRate;
  			inFile.ignore();
  			index++;
		}
		inFile.close();
	}
	cout << endl << "Successfully loaded " << index << " activities." << endl << endl;
	return index;
}

int search(exerciseData exerciseList[], int count) // pass the array and the number of items in the array.
{
	int i;
	char searchName[SIZE];
	int exCount = 0;

	cout << endl << "What activity would you like to search for?" << endl;
	cin.getline(searchName, SIZE);
	cout << endl << "Here are the activities matching " << searchName << endl << endl;

	cout << endl << left << setw(23) << "Name" << left << setw(12) << "Date"
	  	 << left << setw(12) << "Time(min)" << left << setw(11) << "Calories"
	 	 << left << setw(16) << "Max Heartrate" << left <<  "Note" << endl;
	cout << "--------------------   ----------  ---------   --------   -------------   --------------" << endl;

	for(i = 0; i < count; i++) {
		if(strcmp(searchName, exerciseList[i].name) == 0) {
			cout << left << setw(23) << exerciseList[i].name << left << setw(12) << exerciseList[i].date
			 	 << left << setw(12) << exerciseList[i].time << left << setw(11) << exerciseList[i].calories
			     << left << setw(16) << exerciseList[i].maxHeartRate << left << setw(SIZE) << exerciseList[i].note << endl;
			exCount++;
		}
    }
    return exCount;
}

void list(exerciseData exerciseList[], int count) // Print all data in the list.
{
	cout << endl << left << setw(23) << "Name" << left << setw(12) << "Date"
		 << left << setw(12) << "Time(min)" << left << setw(11) << "Calories"
		 << left << setw(16) << "Max Heartrate" << left <<  "Note" << endl;
	cout << "--------------------   ----------  ---------   --------   -------------   --------------" << endl;

	for (int i = 0; i < count; i++)
		cout << left << setw(23) << exerciseList[i].name << left << setw(12) << exerciseList[i].date
			 << left << setw(12) << exerciseList[i].time << left << setw(11) << exerciseList[i].calories
			 << left << setw(16) << exerciseList[i].maxHeartRate << left << setw(SIZE) << exerciseList[i].note << endl;
}

void logThisYo(char record, double minutesNumber, double& totalMinutes, double caloriesNumber, double& totalCalories, int &indexCount)
{
	if (record == 'Y')
	{
		totalMinutes = totalMinutes + minutesNumber;
		totalCalories = totalCalories + caloriesNumber;
		indexCount++;
		cout << endl << "Your activity info has been recorded." << endl;
	} else {
		cout << endl << "Your activity has not been recorded." << endl;
	}
}

void add(exerciseData exerciseList[], int indexCount)
{
	char another = 'Y';
	char activity[SIZE];
	double minutesNumber;
	double caloriesNumber;
	double totalMinutes = 0.0;
	double totalCalories = 0.0;
	char record;

	while (another != 'N')
	{
	  	if (indexCount >= SIZE)
	  	{
	    	cout << "Sorry, the array is full." << endl;
	  	} else {
	  		cout << endl << "What exercise activity did you do?" << endl;
			cin.getline(activity, 20);

			// Minutes Section
			cout << endl << "How many minutes?" << endl;
			cin >> minutesNumber;
			cin.ignore(5, '\n');
			while(cin.fail() || minutesNumber <= 0) {
		    	dataCheck();
		    	cout << endl << "How many minutes?" << endl;
				cin >> minutesNumber;
				cin.ignore(5, '\n');
			}

		    // Calories Section
			cout << endl << "How many calories did you burn?" << endl;
			cin >> caloriesNumber;
			cin.ignore(5, '\n');
			while(cin.fail() || caloriesNumber <= 0) {
		    	dataCheck();
		    	cout << endl << "How many calories did you burn?" << endl;
				cin >> caloriesNumber;
				cin.ignore(5, '\n');
		    }

			cout << endl << "OK, you did " << activity << " for " << minutesNumber << " minutes, and burned " << caloriesNumber << " calories." << endl;

			cout << endl << "Record the activity time and calories? (Y/N)" << endl;
			cin >> record;
			record = static_cast<char>(toupper(record));
			logThisYo(record, minutesNumber, totalMinutes, caloriesNumber, totalCalories, indexCount);
			cout << endl << "Would you like to enter another activity (Y/N)?" << endl;
			cin >> another;
			cin.ignore();
			another = static_cast<char>(toupper(another));
			if(another == 'N')
			{
				cout << endl << "Thank you for using the exercise tracking program. Here are your totals:\n" << endl;
				cout << "Total exercise minutes: " << totalMinutes << endl;
				cout << "Total exercise calories: " << totalCalories << endl << endl;
			}
		}
  	}
}

void dataCheck()
{
	cout << "That wasn't a number greater than zero, was it?" << endl;
	cin.clear();
}
