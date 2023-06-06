#include "BattleHeroClassSimulator.h"

int main() 
{
    // Welcome the user to the program
    std::cout << "Welcome to the Battle Hero Simulator!" << std::endl;
    std::cout << "Version: 3.0" << std::endl;
    std::cout << "Created by: Charalampos Thomaidis" << std::endl;

    int menuChoice;
    do 
    {
        //Main Menu
        diplayMenu();
        menuChoice = getPlayerChoice(1, 3);

        // If choice is 1 then display on console the help information for the program
        if (menuChoice == 1) 
        {
            std::cout << std::endl << "~Help: This program simulates a battle between two players. \n"
                "~Each player has a name, class, and weapon. \n"
                "~The battle proceeds with turns alternating between the players. \n"
                "~The player who reduces the other player's health to 0 wins the battle. \n"
                "~The player's attack power, defense rating and health are randomly generated \n"
                "~based on their class and weapon choices. \n"
                "~The program will always save the battles into a Score.dat file, \n"
                "~and also ask the user if he wants to print the score after the battle. \n";
        }

        // If choice is 2 start the round
        else if (menuChoice == 2) 
        {
            std::string player1Name;
            std::string player2Name;
            PlayerClass player1Class;
            PlayerClass player2Class;
            Item player1Item;
            Item player2Item;

            // Player 1 Name
            std::cout << std::endl << "~Enter Player 1 name: ";
            std::cin.ignore();
            getline(std::cin, player1Name);

            // Player 1 Class
            std::cout << std::endl << "~Choose your class for " << player1Name << "\n" << std::endl;
            std::cout << "1: Warrior" << std::endl << "2: Archer" << std::endl << "3: Rogue" << std::endl << "4: Mage \n" << std::endl;
            std::cout << "~Enter your choice: ";
            int player1ClassChoice = getPlayerChoice(1, 4);
            player1Class = static_cast<PlayerClass>(player1ClassChoice - 1);

            // Player 1 Weapon
            std::cout << std::endl << "~Choose your weapon for " << player1Name << "\n" << std::endl;
            std::cout << "1: Sword" << std::endl << "2: Bow" << std::endl << "3: Dagger" << std::endl << "4: Staff \n" << std::endl;
            std::cout << "~Enter your choice: ";
            int player1ItemChoice = getPlayerChoice(1, 4);
            player1Item = static_cast<Item>(player1ItemChoice - 1);

            // Player 2 Name
            std::cout << std::endl << "~Enter Player 2 name: ";
            std::cin.ignore();
            getline(std::cin, player2Name);

            // Player 2 Class
            std::cout << std::endl << "~Choose your class for " << player2Name << "\n" << std::endl;
            std::cout << "1: Warrior" << std::endl << "2: Archer" << std::endl << "3: Rogue" << std::endl << "4: Mage \n" << std::endl;
            std::cout << "~Enter your choice: ";
            int player2ClassChoice = getPlayerChoice(1, 4);
            player2Class = static_cast<PlayerClass>(player2ClassChoice - 1);

            // Player 2 Weapon
            std::cout << std::endl << "~Choose your weapon for " << player2Name << "\n" << std::endl;
            std::cout << "1: Sword" << std::endl << "2: Bow" << std::endl << "3: Dagger" << std::endl << "4: Staff \n" << std::endl;
            std::cout << "~Enter your choice: ";
            int player2ItemChoice = getPlayerChoice(1, 4);
            player2Item = static_cast<Item>(player2ItemChoice - 1);

            // Create players
            Player player1(player1Name, player1Class, player1Item);
            Player player2(player2Name, player2Class, player2Item);

            // Display player information
            std::cout << std::endl << "Player 1:" << std::endl;
            displayPlayer(player1);
            std::cout << "Player 2:" << std::endl;
            displayPlayer(player2);

            int turnNumber = 1;
            while (player1.getHealth() > 0 && player2.getHealth() > 0) 
            {
                std::cout << std::endl << "~Turn " << turnNumber << ":" << std::endl;

                // Randomly determine which player attacks first
                int firstPlayer = player1.getRandomNumber(1, 2);
                int secondPlayer = (firstPlayer == 1) ? 2 : 1;

                // Player 1 attacks
                if (firstPlayer == 1) 
                {
                    std::cout << player1.getName() << " (Player 1) attacks " << player2.getName() << " (Player 2)!" << std::endl;
                    int damage = player1.attack(player2);
                    std::cout << "Damage dealt: " << damage << std::endl;
                    std::cout << player2.getName() << "'s remaining health: " << player2.getHealth() << std::endl;
                }

                // Player 2 attacks
                else 
                {
                    std::cout << player2.getName() << " (Player 2) attacks " << player1.getName() << " (Player 1)!" << std::endl;
                    int damage = player2.attack(player1);
                    std::cout << "Damage dealt: " << damage << std::endl;
                    std::cout << player1.getName() << "'s remaining health: " << player1.getHealth() << std::endl;
                }

                turnNumber++;
            }

            // Determine the winner
            std::cout << std::endl << "~Battle is over!" << std::endl;
            std::string winner;

            if (player1.getHealth() > 0)
            {
                winner = player1.getName() + " (Player 1) " + player1.getClassString() + " (Class) " + player1.getItemString() + " (Weapon)";
                std::cout << winner << " wins the battle! \n" << std::endl;
            }
            else if (player2.getHealth() > 0)
            {
                winner = player2.getName() + " (Player 2) " + player2.getClassString() + " (Class) " + player2.getItemString() + " (Weapon) ";
                std::cout << winner << " wins the battle! \n" << std::endl;
            }
            else
            {
                winner = "It's a tie!";
                std::cout << winner << std::endl;
            }

            // Ask if the user wants to print the results to the console
            std::cout << "~Do you want to print the results to the console and save them on the file named 'Score.dat' ? (1: Yes / 2 : No) : \n" << std::endl;
            std::cout << "~Enter your choice: ";
            int printChoice = getPlayerChoice(1, 2);
            std::cout << std::endl;

            // Save the results on the file "Score.dat" and prints the results on the console
            if (printChoice == 1)
            {
                saveResultsToFile(player1.getName(), player2.getName(), winner);

                std::cout << "Player1: " << player1.getName() << std::endl;
                std::cout << "Player2: " << player2.getName() << std::endl;
                std::cout << "Winner: " << winner << std::endl;
            }
        }
    } 
    while (menuChoice != 3);

    return 0;
}