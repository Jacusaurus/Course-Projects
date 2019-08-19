#include <stdio.h>
/*
Name: Jacob Wood
Section: 02
Date: 1/17/19
Description: This program will take a value and convert that into the value of different currencies, displaying them in a table.
*/
int main(){
	//Gives the value of one USD in foreign currencies.
	const float USD2RUB = 66.37;
	//to Russian rubles
	const float USD2GBP = .77;
	//to British Pounds Stirling
	const float USD2CAD = 1.33;
	//to Canadian dollars
	const float USD2EUR = .88;
	//to European Euros
	const float USD2AUD = 1.39;
	//to Australian dollars
	float basecurrency;
	//initializes base currency
	
	printf("Please give a value.  This value will be used to convert to various currencies.");
	//prompts user for input
	scanf("%f", &basecurrency);
	//assigns base currency
	
	
	/*
	float GBP3 = basecurrency;
	float CAD4 = basecurrency;
	float EUR5 = basecurrency;
	float AUD6 = basecurrency;
	*/
	//unimplemented code above.  Could exclude, however it exemplifies a method that could be utilized.
	
	
	float USD1 = basecurrency;
	float RUB1 = USD1 * USD2RUB;
	float GBP1 = USD1 * USD2GBP;
	float CAD1 = USD1 * USD2CAD;
	float EUR1 = USD1 * USD2EUR;
	float AUD1 = USD1 * USD2AUD;
	//initializes and assigns first column values with US Dollars set to base currency.
	
	float RUB2 = basecurrency;
	float USD2 = RUB2 / USD2RUB;
	float GBP2 = USD2 * USD2GBP;
	float CAD2 = USD2 * USD2CAD;
	float EUR2 = USD2 * USD2EUR;
	float AUD2 = USD2 * USD2AUD;
	//initializes and assigns second column with rubles set to base currency.
	
	float GBP3 = basecurrency;
	float USD3 = GBP3 / USD2GBP;
	float RUB3 = USD3 * USD2RUB;
	float CAD3 = USD3 * USD2CAD;
	float EUR3 = USD3 * USD2EUR;
	float AUD3 = USD3 * USD2AUD;
	//initializes and assigns third column values with pounds set to base currency.
	
	float CAD4 = basecurrency;
	float USD4 = CAD4 / USD2CAD;
	float RUB4 = USD4 * USD2RUB;
	float GBP4 = USD4 * USD2GBP;
	float EUR4 = USD4 * USD2EUR;
	float AUD4 = USD4 * USD2AUD;
	//initializes and assigns fourth column values with canadian dollars set to base currency.
	
	float EUR5 = basecurrency;
	float USD5 = EUR5 / USD2EUR;
	float RUB5 = USD5 * USD2RUB;
	float GBP5 = USD5 * USD2GBP;
	float CAD5 = USD5 * USD2CAD;
	float AUD5 = USD5 * USD2AUD;
	//initializes and assigns fifth column values with Euros set to base currency.
	
	float AUD6 = basecurrency;
	float USD6 = AUD6 / USD2AUD;
	float RUB6 = USD6 * USD2RUB;
	float GBP6 = USD6 * USD2GBP;
	float CAD6 = USD6 * USD2CAD;
	float EUR6 = USD6 * USD2EUR;
	//initializes and assigns sixth column values with Australian dollars set to base currency.
	
	
	//Table outputting values
	
	printf("\n[     |\t       USD |\t       RUB |\t       GBP |\t       CAD |\t       EUR |\t        AUD]");
	//prints first row which includes labels for the currencies
	printf("\n[ USD |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f ]", USD1, USD2, USD3, USD4, USD5, USD6);
	//prints the second row containing US dollars values and label
	printf("\n[ RUB |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f ]", RUB1, RUB2, RUB3, RUB4, RUB5, RUB6);
	//prints the third row containing ruble values and label
	printf("\n[ GBP |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f ]", GBP1, GBP2, GBP3, GBP4, GBP5, GBP6);
	//prints the fourth row containing pounds values and label
	printf("\n[ CAD |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f ]", CAD1, CAD2, CAD3, CAD4, CAD5, CAD6);
	//prints the fifth row containing Canadian values and label
	printf("\n[ EUR |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f ]", EUR1, EUR2, EUR3, EUR4, EUR5, EUR6);
	//prints the sixth row containing Euro values and label
	printf("\n[ AUD |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f |\t      %.2f ]", AUD1, AUD2, AUD3, AUD4, AUD5, AUD6);
	//prints the seventh row containing Australian dollars and label
	return 0;
}
