#include <stdio.h>
#include <math.h>
/*
Name: Jacob Wood
Section: 02
Date: 2/07/19
Description: This program uses various functions in order to create a calculator that can do the
following: take two addends and give a sum, take a minued and subtrahend and give a difference,
take a multiplicand and a multiplier and give a product, take a dividend and divisor and give a
quotient, take a dividend and divisor and return a remainder through the modulus function,
take a number and determine whether it is prime or not, take a number and return its factorial,
take a base and exponent and return its value, and take an integer and return the summation of
all integers less than it and greater than zero.  The calculator will run repeatedly until the
user wishes to exit.
*/
int selection, prime_init, prime_input, isprime, mod_num1, mod_num2, divis_by, factoriand,
factorial_init, factorial_result, summation_num, summation_init, summation_result;
//initializes integers used in later functions
float addend1, addend2, minuend, subtrahend, multiplicand, multiplier, dividend, divisor, base,
exponent;
//initializes floats used in later functions
void func_selection(int);
//selection function prototype
int addition();
//addition function prototype
int subtraction();
//subtraction function prototype
int multiplication();
//multiplication function prototype
int division();
//division function prototype
int modulus();
//modulus function prototype
int prime_test();
//prime_test funciton prototype
int factorialize();
//factorial function prototype
int exponential();
//exponential function prototype
int summation_function();
//summation function prototype
int exit_val = 0;
//sets exit value equal to 0, or false



void func_selection(int user_selection){
	switch(user_selection){
		case 1:
			addition();
			break;
		case 2:
			subraction();
			break;
		case 3:
			multiplication();
			break;
		case 4:
			division();
			break;
		case 5:
			modulus();
			break;
		case 6:
			prime_test();
			break;
		case 7:
			factorialize();
			break;
		case 8:
			exponential();
			break;
		case 9:
			summation_function();
			break;
		case 0:
			exit_val =1;
			break;
		default:
			exit_val = 1;
		break;
	}
	//switch statement embeded in function, used to execute other funcitons based on input or give exit value equal to 1 (or true)
}

int addition(){
	printf("Please give first addend:\n");
	//prompts for input
	scanf("%f", &addend1);
	//assigns input
	printf("Please give second addend:\n");
	//prompts for input
	scanf("%f", &addend2);
	//assigns input
	printf("The sum of %.2f and %.2f is %.2f\n", addend1, addend2, (addend1 + addend2));
	//displays the values and sum
	return 0;
}
//addition function definition

int subraction(){
	printf("Please give the minuend:\n");
	//prompts for input
	scanf("%f", &minuend);
	//assigns input
	printf("Please give the subtrahend:\n");
	//prompts for input
	scanf("%f", &subtrahend);
	//assigns input
	printf("Subrtacting %.2f from %.2f, yields a difference of %.2f\n", 
	subtrahend, minuend, minuend - subtrahend);
	//lists values and difference
	return 0;
}
//subtraction function definition

int multiplication(){
	printf("Please give the multiplicand:\n");
	//prompts for input
	scanf("%f", &multiplicand);
	//assigns input
	printf("Please give the multiplier:\n");
	//prompts for input
	scanf("%f", &multiplier);
	//assigns input
	printf("The product of %.2f and %.2f is %.2f\n",
	multiplicand, multiplier, multiplicand * multiplier);
	//lists values and product
	return 0;
}
//multiplication function definition

int division(){
	printf("Please give the dividend:\n");
	//prompts for input
	scanf("%f", &dividend);
	//assigns input
	printf("Please give the divisor:\n");
	//prompts for input
	scanf("%f", &divisor);
	//assigns input
	printf("Dividing %.2f by %.2f yields a dividend of %.2f\n", dividend, divisor, dividend / divisor);
	//lists values and dividend
	return 0;
}
//division function definition

int modulus(){
	printf("Please give the dividend:\n");
	//prompts for input
	scanf("%d", &mod_num1);
	//assigns input
	printf("Please give the divisor:\n");
	//prompts for input
	scanf("%d", &mod_num2);
	//assigns input
	printf("The remainder when dividing %d by %d is %d\n", mod_num1, mod_num2, (mod_num1 % mod_num2));
	//lists values and remainder
}
//modulus function definition

int prime_test(){
	printf("Please provide the number you wish to check is prime:\n");
	//prompts for input
	scanf("%d", &prime_input);
	//stores provided input
	isprime = 1;
	//initializes isprime value as 1
	if (prime_input <= 0){
		printf("%d is not a prime number.\n", prime_input);
		//tests if number is less than zero
	} else{
		for (prime_init = 2; prime_init <= prime_input/2; prime_init++){
			/*initializes prime_init as 2, repeats loop as long as prime_init is less than or equal
			to prime_input divided by 2, and increments the value of prime if the previous statement
			remains true*/
			if ((prime_input % prime_init) == 0){
				divis_by = prime_input / prime_init;
				isprime = 0;
				break;
				/*tests for no remainder when dividing prime_input by prime_init.  If equates to
				remainder, loop is broken and isprime returns as 0 or false.  Also gives what the
				number is divisible by.*/
			}
		} if (isprime == 1){
			printf("%d is prime.\n", prime_input);
			//prints if number is prime
		} else{
			printf("%d is not prime.  It is divisible by %d.\n", prime_input, divis_by);
			//prints if number is not prime and what it is divisible by
			}
			return 0;
		}
}
//prime_test function definition

int factorialize(){
	printf("Please provide the number you wish to factorialize:\n");
	//requests user input
	scanf("%d", &factoriand);
	//stores provided input
	factorial_result = factoriand;;
	for (factorial_init = factorial_result - 1; factorial_init > 0; factorial_init--){
		factorial_result = factorial_result * factorial_init;
	}
	//multiplies the number provided by each number under it as long as it is not zero
	printf("The factorial of %d is %d.\n", factoriand, factorial_result);
	//lists value and factorial                                                                          
	return 0;
}
//factorialize function definition

int exponential(){
	printf("Please give the base:\n");
	//prompts for input
	scanf("%f", &base);
	//stores input
	printf("Pleae give the exponent:\n");
	//prompts for input
	scanf("%f", &exponent);
	//stores input
	printf("%.2f raised to the power of %.2f, gives a result of: %.2f\n", base, exponent,
	powf(base,exponent));
	//lists values and result
	return 0;
}
//exponential function definition

int summation_function(){
	printf("This function takes any integer, n, and returns the sum of every integer in between it and zero.\n"
	"Please give a value for the summation:\n");
	//explains function and prompts for value
	scanf("%d", &summation_num);
	//stores input
	summation_result = summation_num;
	for(summation_init = summation_num - 1; summation_init>0; summation_init--){
		summation_result = summation_result + summation_init;
	}
	//adds all numbers betwen n and 0
	printf("The summation of all integers between n: %d, and 0 is %d.\n", summation_num, summation_result);
	//gives value and summation
	return 0;
}
//summation function definition

int main(){
	do{
		printf("This is a calculator menu.  Please type the number corresponding to the funciton you wish to perform.\n"
		"(This calculator is accurate to two decimal places.)"
		"\n(1) Addition\n(2) Subtraction\n(3) Multiplication\n(4) Division\n(5) Modulus (give remainder)"
		"\n(6) Test if number is prime\n(7) Factorial\n(8) Exponential\n(9) Summation function\n(0) Exit program\n");
		//Prompts user for input and lists menu
		scanf("%d", &selection);
		//Sets user input equal to selection
		func_selection(selection);
		//calls function
	} while(exit_val == 0);
	//performs code above as long as exit value is equal to zero, or false
	return 0;
}
