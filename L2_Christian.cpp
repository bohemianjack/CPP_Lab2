#include <iostream>
#include <iomanip>		// manipulate output to format
#include <cctype>	    	// to use cin.fail() for validation
#include <limits>  		// to set max limit for cin.ignore()
#include <string>		// accepts string characters

using namespace std;

// Declaring constants
const double UNIT_SPOOL_CHARGE = 100.00, // 100.00 per spool
	       SHIPPING_CHARGE =  10.00; // Default shipping charge


// Function prototypes
void getOrderInfo (int &, int &, double &);			//Grabs order info
void processDisplayStatus(int, int, double = SHIPPING_CHARGE);	//Final output
void whileLoopValidationChecker(int &, int, string);		//Loops for numberChecker
void whileLoopValidationChecker(double &, int, string);		//Overload for doubles
bool numberChecker(int, int); 	 				//Function to handle ints
bool numberChecker(double, int); 				//Overloader for doubles

//EXECUTE MAIN FUNCTION
int main()
{
	//Initialize variables, which will be manipulated by passing by reference
	int        numOrdered =   0,        		// Number of spools ordered
                      instock =   0;        		// Number of spools in stock
    double     specialCharges = 0.0;    	        // Special charges (if any) to ship the spools
    
    	//Function to take information from user
	getOrderInfo(numOrdered, inStock, specialCharges);
	
	//Function to display messages
	processDisplayStatus(numOrdered, inStock, specialCharges);

	return 0;	
}

/*************************************************************
 *                        getOrderInfo                       *
 * This function is called by main to input and validate     *
 * the number of spools ordered, the number in stock, and    *
 * any special shipping charges. These values are stored in  *
 * reference parameters.                                     *
 *************************************************************/
void getOrderInfo (int &order, int &in_stock, double &special_charge)
{
	
	string question1 = "How many spools were ordered? ";
	string question2 = "How many spools are in stock? ";
	string question3 = "Amount of special shipping charges, per spool, above the regular $10.00 per spool rate (0 for none): ";
	
	//Runs a while loop function to check for validation
	whileLoopValidationChecker(order, 1, question1);
	whileLoopValidationChecker(in_stock, 1, question2);
	whileLoopValidationChecker(special_charge, 0, question3);
}



/***************************************************************
 *                       processDisplayStatus                  *
 * This function is called by main and passed as arguments the *
 * number of spools ordered, the number in stock, and the      *
 * shipping charge per spool. The default value for shipping   *
 * charge is $10.00. This information is used to display an    *
 * order status report.                                        *
 ***************************************************************/
void processDisplayStatus(int numOrdered, int inStock, double ShipChg)
{
	//Checks inStock against the number ordered
	int backStock = numOrdered - inStock; 
	//If there is more in stock, it sets the backstock to zero.
	if (numOrdered <= inStock)
	{
		backStock = 0;	
	}          		     
	
	//Equates how many spools are actually being shipped
	int       actualSpoolShipped   = numOrdered - backStock;
			   
	//Equations for display. Figure out shipping charge, special shipping charge, total spool charge, 
	//and the final total between them all.	          
	double     totalShippingCharge = actualSpoolShipped * SHIPPING_CHARGE,
		  totalSpecialShipping = actualSpoolShipped * ShipChg,
		      totalSpoolCharge = actualSpoolShipped * UNIT_SPOOL_CHARGE,
		            finalTotal = totalSpoolCharge + totalShippingCharge + totalSpecialShipping;			  

	//Grabbing information from customer
	cout << endl << endl;
	cout << "\t***Order Summary***" << endl;
	cout << left << setw(37) << "Spools ordered:" << right << setw(5) << numOrdered << endl;
	cout << left << setw(37) << "Spools in this shipment:" << right <<setw(5) << actualSpoolShipped << endl;
	cout << left << setw(37) << "Spools on backorder:" << right << setw(5) << backStock << endl;
	cout << endl << endl;
	
	//Set 100th's place for decimal value
	cout << fixed << showpoint << setprecision(2);
	
	//Displays user input along with price for each category
	cout << "\t***Total Charges***" << endl;
	cout << left  << setw(30) << "Spool Charges:" << "$ " << right << setw(10) << totalSpoolCharge << endl;
	cout << left  << setw(30) << "Shipping Charges:" << "$ "<< right << setw(10) << totalShippingCharge << endl;
	cout << left  << setw(30) << "Special Shipping Charges:" << "$" << right << setw(11) << totalSpecialShipping << endl;
	cout << right << setw(42) << "------------"  << endl;
	
	//Final Output
	cout << left  << setw(30) << "TOTAL:" << "$" << right << setw(11) << finalTotal;
	
	cout << endl << endl;
	
}

/*************************************************************
*				whileLoopValidationChecker   *
* This function is a helper function for numberChecker. It   *
* It takes in 3 string questions, and takes in the input     *
* variable. Then, it will run a while loop and checks for    *
* validation through the numberChecker function. If it's     *
* true, it will exit the function. If false, numChecker will *
* inform the user, then run through the do-while loop until  *
* true.                                                      *
*************************************************************/

//Function to check integers
void whileLoopValidationChecker(int &input, int minNum, string question)
{
	do {
		cout << question;
		cin >> input;		
	} while(!numberChecker(input, minNum));
}

//Function to check double
void whileLoopValidationChecker(double &input, int minNum, string question)
{
	do {
		cout << question;
		cin  >> input;	
	} while(!numberChecker(input, minNum));
}
/***************************************************************
 *                       numberChecker                         *
 * 	This function is called by getOrderInfo and passed as      *
 * 	arguments the number the user enters, and the minimal      *
 * 	number needed to validate the order. It uses a boolean     *
 *  check to confirm that the number is greater than the       *
 *  number_floor, and is the proper data type (cin.fail() ).   *
 *  It also uses a numeric_limit to ignore to make sure that   * 
 *  if it does fail, then any buffer is removed and continued. *
 *  Otherwise, it will repeat the error message multiple times.*
 *  Below are two of the same functions, overloaded.           *
 ***************************************************************/

//Function to check for integers 
bool numberChecker(int value, int number_floor)
{
	bool validNumber = true;
	if (value < number_floor || cin.fail()) //cin.fail() sees if the data type is correct
	{
		cin.clear();
		cin.ignore(numeric_limits<int>::max(), '\n'); //numeric_limits<int> will ignore the buffer for the max lines. 
							      //This stops repeated error message.
		cout << "***Error, number out of range (less than " << number_floor << " ) or not a number. Please re-enter.***" << endl;
		validNumber = false;
	}
	return validNumber;
}

//Overload function to check for doubles
bool numberChecker(double value, int number_floor)
{
	bool validNumber = true;
	if (value < number_floor || cin.fail()) //cin.fail() sees if the data type is correct
	{
		cin.clear();
		cin.ignore(numeric_limits<int>::max(), '\n'); //numeric_limits<int> will ignore the buffer for the max lines. 
													  //This stops repeated error message.
		cout << "***Error, number out of range (less than " << number_floor << " ) or not a number. Please re-enter.***" << endl;
		
		validNumber = false;
	}
	return validNumber;
}









/* 							NOTES:
	1) The output has mutliple test cases to show the input validation is working. 
	2) I know this is more than what was requested, but I wanted to challenge myself a bit more and try out more things with the language.
	3) The hardest part, honestly, was trying to figure out how to loop all the while statements in getOrderInfo, but I'm not sure
	   how to mix a data type in an array.
	4) Figured out how to make the code cleaner by adding in an extra function which asks each question.
		4.1) Each string is 8 bytes long, and is efficient in storage.
		4.2) My compiler compiles it in 1.05s, which seems pretty quick. File size is 10kb, not sure if that's too big or not. 
	
							OUTPUT:
How many spools were ordered? aa
***Error, number out of range (less than 1 )or not a number. Please re-enter.***
How many spools were ordered? Hello my baby hello my honey
***Error, number out of range (less than 1 )or not a number. Please re-enter.***
How many spools were ordered? -55
***Error, number out of range (less than 1 )or not a number. Please re-enter.***
How many spools were ordered? 0
***Error, number out of range (less than 1 )or not a number. Please re-enter.***
How many spools were ordered? 567


How many spools are in stock? aa
***Error, number out of range (less than 1 )or not a number. Please re-enter.***
How many spools are in stock? Hello my baby Hello my honey
***Error, number out of range (less than 1 )or not a number. Please re-enter.***
How many spools are in stock? -44
***Error, number out of range (less than 1 )or not a number. Please re-enter.***
How many spools are in stock? 0
***Error, number out of range (less than 1 )or not a number. Please re-enter.***
How many spools are in stock? 532
Amount of special shipping charges, per spool, that
above the regular $10.00 per spool rate (0 for none): hello
***Error, number out of range (less than 0 )or not a number. Please re-enter.***
Amount of special shipping charges, per spool, that
above the regular $10.00 per spool rate (0 for none): 13.99


        ***Order Summary***
Spools ordered:                        567
Spools in this shipment:               532
Spools on backorder:                    35


        ***Total Charges***
Spool Charges:                $   53200.00
Shipping Charges:             $    5320.00
Special Shipping Charges:     $    7442.68
                              ------------
TOTAL:                        $   65962.68
*/
