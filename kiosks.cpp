#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Initializes `customers` array of size `max_cust` to an appropriate default value
// Also intiailizes the first `n` entries of the `kiosks` array to an appropriate default value
void initArrays(int customers[], int max_cust, int kiosks[], int n);

// Finds and returns the size of the largest contiguous range of free kiosks
// Also prints out the first and last free kiosk index of the largest free range
// kiosks = array of kiosks
// n = size of used elements in the kiosks array
// return the number of kiosks in the largest contiguous free range
int getAndPrintMaxFreeRange(int kiosks[], int n);


// Returns true if `choice` is between 0 and `n`-1, inclusive,
// false otherwise.
bool isValidChoice(int choice, int n);

// Checks if the `choice`-th kiosk is free and then 
// updates the `choice`-th kiosk to contain customer with ID = `cust_id`.
// Also sets the starting time of the `cust_id`-th customer to `tick`.
// Does nothing if the `choice`-th kiosk is already in use.
void addCustomer(int customers[], int cust_id, int kiosks[], int choice, int tick);

// Checks if the `choice`-th kiosk is being used by a customer and then 
// sets the `choice`-th kiosk back to free/unoccupied.
// Also computes the elapsed time the customer was at that kiosk and sets
// the customer ID's entry in the customer array with that elapsed time.
// Does nothing if the `choice`-th kiosk was already free.
void removeCustomer(int customers[], int kiosks[], int choice, int tick);

// Scans the `num_cust` elements of the customers array to find and return
// the maximum time a customer used a kiosk
int maxTimeCustomer(int customers[], int num_cust);

// Scans through all the `n` kiosks and *ends* their usage as of the current
// time `tick` updating their usage time in the customers array (of size `num_cust`).  
void calculateTimesOfRemainingCustomers(int customers[], int kiosks[], int n, int tick);

int main()
{
    // You may add more variable declarations if desired
    int n, tick = 1, num_cust = 0;
    int kiosks[50];
    int customers[100];
    cin >> n; //read in kiosks

    // Initialize arrays to appropriate default values
    initArrays(customers, 100, kiosks, n);

    // stores the sum of the larges free range just before a new customer is added 
    int avgMaxFreeRange = 0;  

    bool quit = false; //flag to control exit of main loop

    while( !quit ) //main loop continues until quit = true or 100 customers
    {
      // Update the largest contiguous free range of kiosks if it has changed
      int maxFreeRange = getAndPrintMaxFreeRange(kiosks, n);

      char option;
      int choice;
      cout << "Enter event: 'a location', 'r location', or 't': " << endl;
      cin >> option;
      // Complete the rest of the body of this loop to get any additional
      // input and perform the appropriate processing based on the input
      // option. Each of the functions prototyped above must be called somewhere
      // in main() -- some are already called in the provided code.

      if(option == 'a'){
        avgMaxFreeRange += maxFreeRange; //record max free range before customer is added
        cin >> choice; 
        if(isValidChoice(choice, n)){
          addCustomer(customers, num_cust, kiosks, choice, tick);
          num_cust++;
        }
      } else if(option == 'r'){ //else if r then remove customer 
        cin >> choice;
        if (isValidChoice(choice, n)){
          removeCustomer(customers, kiosks, choice, tick);

        }
      } else if (option == 't') { //else if increment tick counter for time
        tick++;
      } else if (option == 'q'){ // else if quit the simulation
        quit=true;
      }

      if(num_cust>=100){ //max amount of customers to quit
        quit=true;
      }


    }

    // Do not change this code. It is necessary to meet the desired test format
    if(num_cust != 0){
      //calculate and update the time of all customers who are still using
        calculateTimesOfRemainingCustomers(customers, kiosks, n, tick);
        cout << "Max time: " << maxTimeCustomer(customers, num_cust) << endl;
        cout << setprecision(2) << fixed; //average of the largest free range
        cout << "Average Max Free Range: " <<  avgMaxFreeRange / (double) num_cust << endl;
    }
    return 0;
}

// Complete...Do not change
bool isValidChoice(int choice, int n)
{
    //return true if choice is within (0 to n-1)
    if(choice >= 0 && choice < n){
      return true; //isValidChoice
    } else {
      return false; //invalid
    }
}

// Complete...Do not change
void addCustomer(int customers[], int cust_id, int kiosks[], int choice, int tick)
{
    if(kiosks[choice] == -1){ //kiosk is free 
        customers[cust_id] = -tick; //mark arrival time (- for arrival)
        kiosks[choice] = cust_id; //assign customer to kiosk
    }
}

// Complete...Do not change
void removeCustomer(int customers[], int kiosks[], int choice, int tick)
{
    if(kiosks[choice] != -1) //if in use
    {
        int cust_id = kiosks[choice]; //get id
        customers[cust_id] = tick - (-customers[cust_id]); //calculate time spent
        kiosks[choice] = -1; //mark kiosk as free
    }
}

// You complete. (See description above prototype.)
// Do not change the prototype / signature.
void initArrays(int customers[], int max_cust, int kiosks[], int n)
{
  for(int i = 0; i<max_cust;i++){//initialize array to -1=no customers
    customers[i]=-1; //-1 means no customers yet
  }
  for (int i=0; i<n; i++){
    kiosks[i]=-1; //-1 means no kiosks free
  }
}

// You complete. (See description above prototype.)
// Do not change the prototype / signature.
int getAndPrintMaxFreeRange(int kiosks[], int n)
{
    int maxRange=0;
    int currentRange=0;
    int startIdx = -1;

    for(int i=0; i<n;i++){ //scan to find largest free range
      if(kiosks[i] == -1){
        if (currentRange==0){ //free kiosk
          startIdx=i; //start of new free range
        }
        currentRange++;
      } else { //kiosk in use
        if (currentRange > maxRange){
          maxRange = currentRange;
        }
        currentRange=0; //reset for next free range
      }
    }
    if (currentRange > maxRange){ //check the last free range in case it ended at the last k
      maxRange = currentRange;
    }
    if (maxRange > 0){
      cout << "max free range is between kiosk "<<startIdx<< " and "<< startIdx+maxRange-1 <<endl;
    }
    
    return maxRange;

    // Before returning perform a `cout` that prints a message like:
    //    Max free range is between kiosk 0 and 19
    // where 0 and 19 are replaced with the start and end of the largest free
    // contiguous kiosk range

     
    // return the size of the largest free range  
}

// You complete. (See description above prototype.)
// Do not change the prototype / signature.
void calculateTimesOfRemainingCustomers(int customers[], int kiosks[], int n, int tick)
{
  for (int i=0; i<n; i++){
    if (kiosks[i] != -1){ //if kiosk still in use 
      int cust_id = kiosks[i];
      customers[cust_id] = tick-(-customers[cust_id]);//update time
    }
  }
}

// You complete. (See description above prototype.)
// Do not change the prototype / signature.
int maxTimeCustomer(int customers[], int num_cust)
{
  int maxTime=0;
  for(int i=0; i<num_cust;i++){
    if (customers[i]>maxTime) {
      maxTime=customers[i];//find max tiem spent
    }
  }
  return maxTime;
}

