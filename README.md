# CPP_Lab2
## Prompt:
### Challenge: The Middletown Wholesale Copper Wire Company sells spools of copper wiring for $100 each and ships them for $10 apiece. Write a program that displays the status of an order. It should use two functions which are described in comments below.

The first function asks the user for the data below and stores the input values in reference parameters.
Input data from user:
* \# of spools ordered,
* \# of spools in stock,
* any special shipping & handling charges above $10 rate.

The second function receives as arguments any values needed to compute and display the following information:
* \# of spools ready to ship from current stock,
* \# of ordered spools on backorder (if ordered > in stock),
* Total sales price of portion ready to ship (# of spools ready to ship X $100),
* Total shipping and handling charges on the portion ready to ship,
* Total of the order ready to ship.
        
Exception Handlings
* Input validation: Do not accept numbers < 1 for spools ordered,
* Do not accept numbers < 0 for spools in stock or for shipping & handling charges.
