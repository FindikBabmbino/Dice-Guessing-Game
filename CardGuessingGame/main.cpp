#include<iostream>
#include<ctime>

float InitGame(float balance);
float GetBetMoney(float balance, float betMoney);
void GuessingGame(float betMoney,float& balance, const int DICE_FACES);
int GetGuessInput(int guess);
bool CompareGuess(int randomNumber,int guess);
bool PlayAgain();

int main()
{
	srand(time(0));

	const int DICE_FACES = 6;
	float balance = 0;
	float betMoney = 0;


	balance = InitGame(balance);
	betMoney = GetBetMoney(balance,betMoney);
	GuessingGame(betMoney,balance, DICE_FACES);
}


float InitGame(float balance)
{
	while (balance<=0)
	{
		std::cout << "##### DICE GUESSING GAME #####" << std::endl;
		std::cout << "Please enter your balance: ";
		std::cin >> balance;
		if (std::cin.fail() || balance <= 0)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "You got no money to play." << std::endl;
			std::cout << "Why don't you try again" << std::endl;
			continue;
		}
	}
	return balance;
}

float GetBetMoney(float balance,float betMoney)
{
	while (betMoney<=0)
	{
		std::cout << "Tell me how much you want to bet: ";
		std::cin >> betMoney;
		if(betMoney >= balance +1 || std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "You can't bet that much." << std::endl;
			std::cout << "Why don't you try again" << std::endl;
			betMoney = 0;
			continue;
		}
	}
	return betMoney;
}


void GuessingGame(float betMoney,float& balance,const int DICE_FACES)
{
	int randomNumber = 1 + rand() % DICE_FACES;
	int guess = 0;
	bool winState;
	while(balance > 0)
	{
		guess = GetGuessInput(guess);
		winState = CompareGuess(randomNumber, guess);
		if(winState)
		{
			balance += betMoney;
			std::cout << "Money has been added to your balance. Current balance: " << balance << std::endl;
			if(PlayAgain())
			{
				std::cout << "Sure let's play more, let me throw the dice again.(random number has been changed)" << std::endl;
				randomNumber = 1 + rand() % DICE_FACES;
			}
			else
			{
				std::cout << "See you again partner." << std::endl;
				break;
			}
		}
		else
		{
			balance -= betMoney;
			std::cout << "Money has been deducted from your balance. Current balance: " << balance << std::endl;
		}
	}
	if(balance <= 0)
	{std::cout << "I am sorry partner but you have no money left. Hope to see you again with better luck next time" << std::endl;}
	std::cout << "Your final balance is: " << balance << std::endl;
}

int GetGuessInput(int guess)
{
	bool failState;
	do
	{
		failState = false;

		std::cout << "Now, tell me the number on your mind partner(range is between: 1-6): ";
		std::cin >> guess;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Why don't you try that again, but this time get it right." << std::endl;
			failState = true;
		}
	} while (failState);
	return guess;
}

bool CompareGuess(int randomNumber, int guess)
{
	if(guess == randomNumber)
	{
		std::cout << "You got it right!" << std::endl;
		return true;
	}
	else
	{
		std::cout << "Shucks! I am sorry partner, better luck next time." << std::endl;
		return false;
	}
}

bool PlayAgain()
{
	bool failState;
	char choice = ' ';
	do 
	{
		failState = true;

		std::cout << "Do you wish to gamble more partner?(y(es)/n(o)): ";
		std::cin >> choice;
		choice = tolower(choice);
		if (choice == 'y') return true;
		else if (choice == 'n') return false;
		else 
		{
			std::cout << "What? Tell me that again" << std::endl;
			failState = true;
		}

	} while (failState);
}