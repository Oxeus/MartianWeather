/* weatherdata -- This class encapsulates the weather data (time, temperature,
  windspeed).*/
class weatherdata 
{
public:

	//Constructor and Destructor
	weatherdata();
	~weatherdata();

	//Setters
	void set_timestamp(int atimestamp);
	void set_temperature(double atemperature);
	void set_windspeed(double awindspeed);

	//Getters
	int get_timestamp();
	double get_temperature();
	double get_windspeed();

private:
	int timestamp;
	double temperature;
	double windspeed;
};

/* linkedlist -- This class should implement a linked list. This class should
  be distinct from the datalogger class (although I would expect datalogger to
  have a data member that is a linkedlist object).*/

class linkedlist 
{
public:

	//Constructor and Destructor
	linkedlist();
	~linkedlist();

	//Public member functions to add all timestamp non-duplicate nodes
	void addtoList(int ntimestamp, double ntemperature, double nwindspeed);
	bool search(int time);
	void dupeRemove(int time);
	
	//Sort list least to greatest
	void sort();

	//Public member functions ordered based on order in final printout.
	int total();
	int maxTemp();
	int minTemp();
	int maxWind();
	int minWind();
	int timestart();
	int timeend();
	void printtemp(int num);
	void printwind(int num);

private:
	struct node {			//Main Linked List
		weatherdata data;
		node *nTime;		//node that points to time value > current value
		node *nTemp;		//node that points to temp value > current value
		node *nWind;		//node that points to wind value > current value
	};
	node *timehead;			//Head node for timestamps
	node *temphead;			//head node for temperatures
	node *windhead;			//head node for windspeeds
};

/* datalogger -- This class represents the "business logic" of adding data to
the storage. This class also handles filtering out duplicate data items (see
the requirements listed below). This is the only class that weatherlog.cpp
knows about and it expects two methods: addData() and printReport().*/

class datalogger 
{
public:

	//Constructor and Destructor
	datalogger();
	~datalogger();

	//Public Member Functions to add and check if timestamp value is already in main list
	void addData(int timestamp, double temperature, double windspeed);
	bool searchDupe(int time);
	bool dupecheck(int time);
	
	//Prints out final report
	void printReport();

private:
	linkedlist list;		//Call to Main linked List Class
	struct dupe {           //Duplicate Linked List
		int time;
		dupe * next;
	};
	dupe * head;			//Head Node of dupe
};
