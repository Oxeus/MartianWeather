#include "data_logger.h"
#include <iostream>
#include <iomanip>

using namespace std;

/**************************
***************************
***Weatherdata functions***
***************************
**************************/

//Constructor
weatherdata::weatherdata()
{
	timestamp = 0;
	temperature = 0;
	windspeed = 0;
}

//Destructor
weatherdata::~weatherdata()
{
	//Default Deconstructor, nothing to deallocate or destroy
}

//Setters to set timestamps, temperatures, and windspeeds
void weatherdata::set_timestamp(int atimestamp)
{
	timestamp = atimestamp;
}
void weatherdata::set_temperature(double atemperature)
{
	temperature = atemperature;
}
void weatherdata::set_windspeed(double awindspeed)
{
	windspeed = awindspeed;
}

//Getters to get timestamps, temperatures, and windspeeds
int weatherdata::get_timestamp()
{
	return timestamp;
}
double weatherdata::get_temperature()
{
	return temperature;
}
double weatherdata::get_windspeed()
{
	return windspeed;
}

/**************************
***************************
***datalogger functions****
***************************
**************************/

//Constructor and set heads nodes to NULL
linkedlist::linkedlist()
{
	timehead = NULL;
	temphead = NULL;
	windhead = NULL;
}

//Destructor and delete all nodes to clear memory
linkedlist::~linkedlist()
{
	node * curr = timehead;
	node * next = NULL;
	while (curr) {
		next = curr->nTime;
		delete curr;
		curr = next;
	}
}

//Add to linked list using values sent from datalogger
void linkedlist::addtoList(int timestamp, double temperature, double windspeed)
{
	node* temp = new node;
	temp->data.set_timestamp(timestamp);
	temp->data.set_temperature(temperature);
	temp->data.set_windspeed(windspeed);
	node* temp2 = timehead;
	node** temp3 = &timehead;
	while (temp2 != NULL && temp2->data.get_timestamp() < temp->data.get_timestamp())
	{
		temp3 = &temp2->nTime;
		temp2 = temp2->nTime;
	}
	*temp3 = temp;
	temp->nTime = temp2;
}

/*In datalogger, dupeCheck will run this function to find out if the value is already in 
the main linked list, if it is it will return true if not false.*/
bool linkedlist::search(int time)
{
	node * curr = timehead;
	while (curr)
	{
		if (curr->data.get_timestamp() == time)
		{
			return true;
		}
		curr = curr->nTime;
	}
	return false;
}

/*In datalogger, if dupeCheck finds either there is a value in the main linked 
list or in the dupe linked list then it will search for and delete it in the main list
if it is there*/
void linkedlist::dupeRemove(int time)
{
	while (timehead && timehead->data.get_timestamp() == time)
	{
		node * tmp = timehead;
		timehead = timehead->nTime;
		delete tmp;
	}

	for (node * current = timehead; current != NULL; current = current->nTime)
	{
		while (current->nTime != nullptr && current->nTime->data.get_timestamp() == time)
		{
			node * tmp = current->nTime;
			current->nTime = tmp->nTime;
			delete tmp;
		}
	}
}

//Sort the list from least to greatest based on temperature then based on windspeed using their respective heads and next node values
void linkedlist::sort()
{
	node * curr = timehead;
	while (curr)
	{
		node* temp2w = windhead;
		node** temp3w = &windhead;
		while (temp2w != NULL && temp2w->data.get_windspeed() < curr->data.get_windspeed())
		{
			temp3w = &temp2w->nWind;
			temp2w = temp2w->nWind;
		}
		*temp3w = curr;
		curr->nWind = temp2w;

		node* temp2t = temphead;
		node** temp3t = &temphead;
		while (temp2t != NULL && temp2t->data.get_temperature() <= curr->data.get_temperature())
		{
			temp3t = &temp2t->nTemp;
			temp2t = temp2t->nTemp;
		}
		*temp3t = curr;
		curr->nTemp = temp2t;
		curr = curr->nTime;
	}
}

//print the 1% top and 1% bottom values of temperature using the range from max-min
void linkedlist::printtemp(int num)
{
	node * curr = temphead;
	int max = maxTemp();
	int min = minTemp();
	int range = max - min;
	double singlePercent = range / 100;
	cout << endl << "Top 1% temperatures (>= " << (max - singlePercent)/10 << "): " << endl;
	curr = temphead;
	while(curr)
	{
		if (curr->data.get_temperature() >= (max - singlePercent))
		{
			cout << "Timestamp: " << curr->data.get_timestamp() << endl
				<< "Temperature: " << curr->data.get_temperature() / 10 << " C" << endl
				<< "Windspeed: " << curr->data.get_windspeed() / 100 << " m/s" << endl << endl;
		}
		curr = curr->nTemp;
	}

	cout << endl << "Bottom 1% temperatures (<= " << (min + singlePercent)/10 << "): " << endl;
	curr = temphead;
	while (curr)
	{
		if (curr->data.get_temperature() <= (min + singlePercent))
		{
			cout << "Timestamp: " << curr->data.get_timestamp() << endl
				<< "Temperature: " << curr->data.get_temperature() / 10 << " C" << endl
				<< "Windspeed: " << curr->data.get_windspeed() / 100 << " m/s" << endl << endl;
		}
		curr = curr->nTemp;
	}
}

//print the 1% top and 1% bottom values of windspeed using the range from max-min
void linkedlist::printwind(int num)
{
	node * curr = windhead;
	int max = maxWind();
	int min = minWind();
	int range = max - min;
	double singlePercent = range / 100;
	cout << endl << "Top 1% windspeeds (>= " << (max - singlePercent) / 100 << "): " << endl;
	curr = windhead;
	while (curr)
	{
		if (curr->data.get_windspeed() >= (max - singlePercent))
		{
			cout << "Timestamp: " << curr->data.get_timestamp() << endl
				<< "Temperature: " << curr->data.get_temperature() / 10 << " C" << endl
				<< "Windspeed: " << curr->data.get_windspeed() / 100 << " m/s" << endl << endl;
		}
		curr = curr->nWind;
	}

	cout << endl << "Bottom 1% windspeeds (<= " << (min + singlePercent) / 100 << "): " << endl;
	curr = windhead;
	while (curr)
	{
		if (curr->data.get_windspeed() <= (min + singlePercent))
		{
			cout << "Timestamp: " << curr->data.get_timestamp() << endl
				<< "Temperature: " << curr->data.get_temperature() / 10 << " C" << endl
				<< "Windspeed: " << curr->data.get_windspeed() / 100 << " m/s" << endl << endl;
		}
		curr = curr->nWind;
	}
}

//Function that allows other functions to get total number of nodes
int linkedlist::total()
{
	int num = 0;
	node * temp = timehead;
	while (temp != NULL)
	{
		num++;
		temp = temp->nTime;
	}
	return num;
}

//Function that allows other functions to know the max value of temperature
int linkedlist::maxTemp()
{
	node * curr = temphead;
	double max = temphead->data.get_temperature();
	while (curr != NULL)
	{
		if (curr->data.get_temperature() > max)
		{
			max = curr->data.get_temperature();
			curr = curr->nTemp;
		}
		else
		{
			curr = curr->nTemp;
		}
	}
	return max;
}

//Function that allows other functions to know the min value of temperature
int linkedlist::minTemp()
{
	node * curr = temphead;
	double min = temphead->data.get_temperature();
	while (curr != NULL)
	{
		if (curr->data.get_temperature() < min)
		{
			min = curr->data.get_temperature();
			curr = curr->nTemp;
		}
		else
		{
			curr = curr->nTemp;
		}
	}
	return min;
}

//Function that allows other functions to know the max value of windspeed
int linkedlist::maxWind()
{
	node * curr = windhead;
	double max = windhead->data.get_windspeed();
	while (curr != NULL)
	{
		if (curr->data.get_windspeed() > max)
		{
			max = curr->data.get_windspeed();
			curr = curr->nWind;
		}
		else
		{
			curr = curr->nWind;
		}
	}
	return max;
}

//Function that allows other functions to know the min value of windspeed
int linkedlist::minWind()
{
	node * curr = windhead;
	double min = windhead->data.get_windspeed();
	while (curr != NULL)
	{
		if (curr->data.get_windspeed() < min)
		{
			min = curr->data.get_windspeed();
			curr = curr->nWind;
		}
		else
		{
			curr = curr->nWind;
		}
	}
	return min;
}

//Function that allows other functions to know the timestamp value in the first position of the linked list
int linkedlist::timestart()
{
	int timestart = 0;
	node * temp = timehead;
	timestart = timehead->data.get_timestamp();
	return timestart;
}

//Function that allows other functions to know the timestamp value in the last position of the linked list
int linkedlist::timeend()
{
	int timeend = 0;
	node * temp = timehead;
	while (temp != NULL)
	{
		timeend = temp->data.get_timestamp();
		temp = temp->nTime;
	}
	return timeend;
}

/**************************
***************************
***datalogger functions****
***************************
**************************/

//Constructor, sets dupe linked list head to NULL
datalogger::datalogger()
{
	//Default constructor
	head = NULL;
}

//Destructor, deletes dupe linked list from memory
datalogger::~datalogger()
{
	dupe * curr = head;
	dupe * next = NULL;
	while (curr) {
		next = curr->next;
		delete curr;
		curr = next;
	}
}

/*Function that searches through the dupe linked list and finds out if value being 
tested is an already a known duplicate value found earlier. For cases of 2+ duplicate time values*/
bool datalogger::searchDupe(int time)
{
	dupe * curr = head;
	while (curr)
	{
		if (curr->time == time)
		{
			return true;
		}
		curr = curr->next;
	}
	return false;
}

//Function that check if the time value being checked is already in the main list or in the dupe list
//returns True of it is found in either of them and false if it isnt.
bool datalogger::dupecheck(int time)
{
	if (list.search(time) || searchDupe(time))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

/*sends data values timestamp, temperature, and windspeed to linkedlist member addtoList
if dupecheck(time) returns false. If dupecheck(time) returns true then it will add the timestamp
value to the dupe linked list and then tell the linklist member dupeRemove to remove the time value
sent to it from the main linked list if it even there*/
void datalogger::addData(int ntimestamp, double ntemperature, double nwindspeed)
{
	if (dupecheck(ntimestamp))
	{
		dupe * temp = new dupe;
		temp->time = ntimestamp;
		dupe* temp2 = head;
		dupe** temp3 = &head;
		while (temp2 != NULL && temp2->time < temp->time)
		{
			temp3 = &temp2->next;
			temp2 = temp2->next;
		}
		*temp3 = temp;
		temp->next = temp2;
		list.dupeRemove(ntimestamp);
	}
	else
	{
		list.addtoList(ntimestamp, ntemperature, nwindspeed);
	}
	
}

//Function to print based on expected.txt
//Calls list.sort() then finds min and max values for temperature and windspeed
//Also finds timestart and timeend by calling their respective class members in linkedlist
//Prints out values time range, number of entries, then prints out min and max values of 
//temperature and windspeed. Also prints out results from printtemp and printwind
void datalogger::printReport()
{
	list.sort();
	int num = list.total();
	double maxTemp = list.maxTemp();
	double minTemp = list.minTemp();
	double maxWind = list.maxWind();
	double minWind = list.minWind();
	int timestart = list.timestart();
	int timeend = list.timeend();
	cout << " ---------------------------- Data Report -----------------------------" << endl << endl
		 << "Time range: " << timestart << " - " << timeend << endl
		 << "Number of Entries: " << num << endl <<
		 " ----------------------------------------------------------------------" << endl;
	cout << "TEMPERATURE" << endl;
	cout << setw(21) << left << "Min Temperature: " << minTemp/10 << " C" << endl;
	cout << setw(21) << left << "Max Temperature: " << maxTemp/10 << " C" << endl;
	list.printtemp(num);
	cout << " ----------------------------------------------------------------------" << endl;
	cout << "WINDSPEED" << endl;
	cout << setw(21) << left << "Min Windspeed: " << minWind/100 << "  m/s" << endl;
	cout << setw(21) << left << "Max Windspeed: " << maxWind/100 << "  m/s" << endl;
	list.printwind(num);
}
