#ifndef BattleHeroClassSimulator_H
#define BattleHeroClassSimulator_H

#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <limits>

// Enumeration of player classes: Warrior, Archer, Rogue, Mage
enum class PlayerClass 
{
	Warrior,
	Archer,
	Rogue,
	Mage
};

// Enumeration of player items: Sword, Bow, Dagger, Staff
enum class Item 
{
	Sword,
	Bow,
	Dagger,
	Staff
};

// Class representing a player, storing and calculating various attributes such as name, class, weapon, health, attack power, and defense rating.
class Player 
{
public:
	// Constructor to initialize the player with a name, class, and item.
	Player(const std::string& playerName, PlayerClass playerClass, Item playerItem)
		: name(playerName), heroClass(playerClass), item(playerItem)
	{
		health = generateRandomNumber(800, 1000);
		attack_power = calculateAttackPower();
		defense_rating = calculateDefenseRating();
	}

	// Calculate the damage from the Player when attacks the otherPlayer
	int attack(Player& otherPlayer)
	{
		float r1 = generateRandomFloat(0.0f, 1.0f);
		float r2 = generateRandomFloat(0.0f, 1.0f);
		float a = attack_power * r1;
		float d = 1.0f - (otherPlayer.defense_rating * r2);
		int damage = static_cast<int>(a * d);
		otherPlayer.health -= damage;
		return damage;
	}

	std::string getName() const 
	{
		return name;
	}

	std::string getClassString() const
	{
		switch (heroClass)
		{
		case PlayerClass::Warrior:
			return "Warrior";
		case PlayerClass::Archer:
			return "Archer";
		case PlayerClass::Rogue:
			return "Rogue";
		case PlayerClass::Mage:
			return "Mage";
		}
	}

	std::string getItemString() const
	{
		switch (item)
		{
		case Item::Sword:
			return "Sword";
		case Item::Bow:
			return "Bow";
		case Item::Dagger:
			return "Dagger";
		case Item::Staff:
			return "Staff";
		}
	}

	int getHealth() const
	{
		return health;
	}

	int getAttackPower() const
	{
		return attack_power;
	}

	float getDefenseRating() const
	{
		return defense_rating;
	}

	int getRandomNumber(int min, int max)
	{
		return generateRandomNumber(min, max);
	}

private:
	std::string name;
	PlayerClass heroClass;
	Item item;
	int health;
	int attack_power;
	float defense_rating;

	int generateRandomNumber(int min, int max)
	{
		static std::random_device rd;
		static std::mt19937 rng(rd());
		std::uniform_int_distribution<int> distribution(min, max);
		return distribution(rng);
	}

	float generateRandomFloat(float min, float max)
	{
		static std::random_device rd;
		static std::mt19937 rng(rd());
		std::uniform_real_distribution<float> distribution(min, max);
		return distribution(rng);
	}

	// Calculate the attack power of the player depending which class
	int calculateAttackPower()
	{
		int baseAttackPower = 0;
		switch (heroClass)
		{
		case PlayerClass::Warrior:
			baseAttackPower = generateRandomNumber(150, 300);
			break;
		case PlayerClass::Archer:
			baseAttackPower = generateRandomNumber(100, 250);
			break;
		case PlayerClass::Rogue:
			baseAttackPower = generateRandomNumber(120, 280);
			break;
		case PlayerClass::Mage:
			baseAttackPower = generateRandomNumber(80, 200);
			break;
		}
		return static_cast<int>(baseAttackPower * getItemMultiplier());
	}

	// Calculate the defense rating of the player depending which class
	float calculateDefenseRating()
	{
		float baseDefenseRating = 0.0f;
		switch (heroClass)
		{
		case PlayerClass::Warrior:
			baseDefenseRating = generateRandomFloat(0.5f, 0.8f);
			break;
		case PlayerClass::Archer:
			baseDefenseRating = generateRandomFloat(0.3f, 0.6f);
			break;
		case PlayerClass::Rogue:
			baseDefenseRating = generateRandomFloat(0.4f, 0.7f);
			break;
		case PlayerClass::Mage:
			baseDefenseRating = generateRandomFloat(0.2f, 0.5f);
			break;
		}
		return baseDefenseRating;
	}

	// Get the item multiplier from the weapon to add to the attack power of the player
	float getItemMultiplier() const
	{
		float multiplier = 1.0f;
		switch (item)
		{
		case Item::Sword:
			multiplier = 1.2f;
			break;
		case Item::Bow:
			multiplier = 1.1f;
			break;
		case Item::Dagger:
			multiplier = 1.15f;
			break;
		case Item::Staff:
			multiplier = 1.05f;
			break;
		}
		return multiplier;
	}
};

// Function which displays the menu
void diplayMenu()
{
	std::cout << std::endl << "Main Menu: \n" << std::endl;
	std::cout << "1. Help \n";
	std::cout << "2. Start \n";
	std::cout << "3. Exit \n" << std::endl;
	std::cout << "~Enter your choice: ";
}

// Function which displays the stats of the player (name, class, weapon, health, attack and defense rate)
void displayPlayer(const Player& player)
{
	std::cout << "Name: " << player.getName() << std::endl;
	std::cout << "Class: " << player.getClassString() << std::endl;
	std::cout << "Item: " << player.getItemString() << std::endl;
	std::cout << "Health: " << player.getHealth() << std::endl;
	std::cout << "Attack Power: " << player.getAttackPower() << std::endl;
	std::cout << "Defense Rating: " << player.getDefenseRating() << std::endl;
	std::cout << std::endl;
}

// Function which gets the number choice of the player and checks for possible input errors
int getPlayerChoice(int min, int max)
{
	int choice;
	while (true)
	{
		if (std::cin >> choice)
		{

			// If user enters a space after the number, throw an invalid choice error
			if (choice >= min && choice <= max)
			{
				if (std::cin.peek() != '\n')
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << std::endl << "~Invalid choice. Please enter a single number. \n" << std::endl;
					std::cout << "~Enter your choice: ";
				}
				else
				{
					return choice;
				}
			}

			// If user enters a number but its not between min and max, throw an invalid choice error
			else
			{
				std::cout << std::endl << "~Invalid choice. Try selecting a value between " << min << " and " << max << ". \n" << std::endl;
				std::cout << "~Enter your choice: ";
			}
		}

		// If user enters a letter for choice instead of number throw, an invalid choice error
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl << "~Invalid choice. Please enter a number. \n" << std::endl;
			std::cout << "~Enter your choice: ";
		}
	}
}

// Function which saves the names , classes and weapons of both players but also who won the battle to a file named Score.dat
void saveResultsToFile(const std::string& player1Name, const std::string& player2Name, const std::string& winner)
{
	// Create a file named "Score.dat"
	std::ofstream file("Score.dat", std::ios::app);

	// If file is open then print the player's names and who won to the file "Score.dat"
	if (file.is_open())
	{
		file << "Player 1: " << player1Name << std::endl;
		file << "Player 2: " << player2Name << std::endl;
		file << "Winner: " << winner << std::endl;
		file << std::endl;
		file.close();
	}
	else
	{
		std::cout << "~Unable to open the file for saving the results." << std::endl;
	}
}

#endif // BattleHeroClassSimulator_H