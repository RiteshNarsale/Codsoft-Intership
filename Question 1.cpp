#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
	std::srand(static_cast<unsigned>(std::time(0)));
	int number_to_guess = std::rand() % 100 + 1;
	int user_guess = 0;
	
	std::cout <<"Welcome to the Guess the Number Game!" << std::endl;
	std::cout<< "I'm thinking of number between 1 and 100. Can you guess what it is?\n";
	
	while (user_guess != number_to_guess) {
		std::cout << "Enter your guess: ";
		std::cin >> user_guess;
		
		if (user_guess < number_to_guess){
			 std::cout << "Too low! Try again.\n";
	    }   else if (user_guess > number_to_guess) {
	    	 std::cout << "Too high! Try again .\n";
        }   else {
        	 std:: cout << "Congratulations! You guessed the correct number.\n";
        }
    }
    
	return 0;
}