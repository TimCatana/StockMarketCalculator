#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*
 *   Program Name: stockCalculator.c
 *   Author: Tim Catana
 *   Last Update: December 18, 2019
 *   Function: A calculator designed to do stock market calculations for you
 *   Compilation: gcc -ansi -o stock stockCalculator.c
 *   Execution: ./stock  
 */

int getAndFormatInput(char *currentInput){
	fgets(currentInput, 100, stdin);
	sscanf(currentInput, "%s", currentInput);
	return(0);
}


bool searchDigit(char *currentInput, bool isLetterFound){
	int i;

	for(i = 0; i < strlen(currentInput); i++){
		if(isdigit(currentInput[i]) == 0 && (currentInput[i] != '.' && currentInput[i] != ',')){
			isLetterFound = true;
		}
	}

	return(isLetterFound);
}

bool assignFloat(char currentInput[100], float *number){
	bool isLetterFound = false;
	getAndFormatInput(currentInput);
	*number = atof(currentInput);

	system("clear");

	isLetterFound = searchDigit(currentInput, isLetterFound);

	if(!isLetterFound){
		return(false);
	} else {
		printf("please insert a valid statement or number\n");
		return(true);
	}
}

bool assignInt(char currentInput[100], int *number){
	bool isLetterFound = false;
	getAndFormatInput(currentInput);
	*number = atoi(currentInput);

	system("clear");

	isLetterFound = searchDigit(currentInput, isLetterFound);

	if(!isLetterFound){
		return(false);
	} else {
		printf("please insert a valid statement or number\n");
		return(true);
	}
}

int EOPQuestons(char *currentInput, bool *chooseTask, bool *setShareCost, bool *setQuantity, bool *setBuyP, bool *setBuyQ, bool *setSellP, bool *setSellQ, bool *terminate){
	int inputError = true;

	while(inputError == true){
		printf("\n\nDo you want to do another calculation? [Y or N]: ");
		getAndFormatInput(currentInput);
		system("clear");

		if(strcmp(currentInput, "Y") != 0 && strcmp(currentInput, "y") != 0 && strcmp(currentInput, "N") != 0 && strcmp(currentInput, "n") != 0){
			printf("Only the single characters Y or N are acceptable. \n");
		} else {
			inputError = false;
		}
	}

	if(strcmp(currentInput, "Y") == 0 || strcmp(currentInput, "y") == 0){
		*chooseTask = true; 
		*setShareCost = true; 
		*setQuantity = true;
		*setBuyP = true;
		*setBuyQ = true;
		*setSellP = true;
		*setSellQ = true;
	} else if (strcmp(currentInput, "N") == 0 || strcmp(currentInput, "n") == 0){
		*terminate = true;
		system("clear");
	}

	return(0);
}


int main ( int argc, char *argv[] ) {
	char currentInput[100];

	/* while loop variables (for error checking)*/
	int task;
	bool terminate = false, chooseTask = true, setShareCost = true, setQuantity = true, setBuyP = true, setBuyQ = true, setSellP = true, setSellQ = true;

	/* task 1 & 2 variables (purchaceCost is only a task 1 variable) */
	float shareCost, purchaseCost;
	int numOfShares;

	/* task 2 variables */
	float moneyInvested;

	/* task 3 variables */
	float buyP, sellP, totalBuyP, totalSellP;
	int buyQ, sellQ;
	float sellProfit, percentProfit;

	while(!terminate){
		system("clear");

		while(chooseTask){
			printf("do you want to: calculate the cost of purchasing a number of shares (1), see how many shares you can purchase with a sum of money (2), or calulate gains or losses (3)?: ");
			chooseTask = assignInt(currentInput, &task);

			if(task < 0 || task > 3){
				printf("only the numbers 1, 2 and 3 are valid\n");
				chooseTask = true;
			}
		}

		/* how much buying a certain quantity of shares would cost */
		if(task == 1){
			while(setShareCost){
				printf("cost of 1 share: ");
				setShareCost = assignFloat(currentInput, &shareCost);
			}

			while(setQuantity){
				printf("quantity you want to buy: ");
				setQuantity = assignInt(currentInput, &numOfShares);
			}

			purchaseCost = shareCost * numOfShares;

			printf("Share cost: $%0.2f\n", shareCost);
			printf("Quantity: %d\n", numOfShares);
			printf("Total cost: $%0.2f\n", purchaseCost);
		}

		/* how many shares can you buy with a specific quantity of money */
		if(task == 2){
			while(setShareCost){
				printf("cost of 1 share: ");
				setShareCost = assignFloat(currentInput, &shareCost);
			}

			while(setQuantity){
				printf("quantity invested ($): ");
				setQuantity = assignFloat(currentInput, &moneyInvested);
			}

			numOfShares = moneyInvested / shareCost;

			printf("Share cost: $%0.2f\n", shareCost);
			printf("$ invested: $%0.2f\n", moneyInvested);
			printf("Max quantity purchasable: %d\n", numOfShares);
		}


		/* calculate gains or losses */
		if(task == 3){
			while(setBuyP){
				printf("Buy price: ");
				setBuyP = assignFloat(currentInput, &buyP);
			}
			
			while(setBuyQ){
				printf("Buy quantity: ");
				setBuyQ = assignInt(currentInput, &buyQ);
			}

			while(setSellP){
				printf("sell price: ");
				setSellP = assignFloat(currentInput, &sellP);
			}

			while(setSellQ){
				printf("sell quantity: ");
				setSellQ = assignInt(currentInput, &sellQ);

				if(sellQ > buyQ){
					printf("sell quantity must be equal to or less than the buy quantity\n"); /* My decision is that I expect your buy quantity to be the only shares you own, if you want to change this go ahead */
					setSellQ = true;
				}
			}

			totalBuyP = buyP * buyQ;
			totalSellP = sellP * sellQ;
			sellProfit = totalSellP - totalBuyP;

			printf("Purchace price: $%0.2f\n", buyP);
			printf("Purchase Quantity: %d\n\n", buyQ);
			printf("sell price: $%0.2f\n", sellP);	
			printf("sell Quantity: %d\n\n", sellQ);
			printf("Incurred profit: $%0.2f\n", sellProfit);

			if( totalSellP > totalBuyP ){
				percentProfit = ((totalSellP - totalBuyP) / totalBuyP) * 100;
				printf("Percent gain of: %0.2f%%\n", percentProfit );
			} else if( totalSellP == totalBuyP ){
				printf("There was no percent gain or loss\n");
			} else {
				percentProfit = ((totalBuyP - totalSellP) / totalSellP) * 100;
				printf("Percent loss of: %0.2f%%\n", percentProfit );
			}
		}

		EOPQuestons(currentInput, &chooseTask, &setShareCost, &setQuantity, &setBuyP, &setBuyQ, &setSellP,  &setSellQ, &terminate);
	}

	printf("Thank you for using stockCalculator\n");
	return ( 0 );
}
