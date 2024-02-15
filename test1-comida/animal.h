#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>

#include "enviroment.h"

struct EnviromentInfoCollected {
	int x;
	int y;
	std::string body;
};

struct FoodInfoCollected {
	bool known;
	int poison;
	int energy;
	std::string body;
	int x, y;
};

class Animal {
private:
	std::string body;
	int starvation;
	int x, y;
	int sight;
	std::string species;
	std::vector<FoodInfoCollected> tempFoodInSurroundings;
	std::string foodRegister;
	Enviroment* enviroment;
public:
	Animal(Enviroment* _enviroment, std::string _species, int _x = 0, int _y = 0):
		enviroment(_enviroment), body("■"), starvation(0), species(_species), x(_x), y(_y), sight(2){
		foodRegister = species + "/foodRegister.csv";
		std::ofstream foodRegisterFile(foodRegister, std::ios::app);
		if (!foodRegisterFile.is_open()) {
			std::cerr << "Error creating the animal" << std::endl;
			destroy();
		}

		foodRegisterFile << "body,energy,poison" << std::endl;

		foodRegisterFile.close();
	}

	void checkStarvation();
	void checkSurroundings();
	FoodInfoCollected checkFood(std::string body);
	void checkFoodSuitability();
	void eat(FoodInfoCollected food);
	void logFood(std::string log);
	void move();
	void draw();
	void live();
	void destroy();

	int getX() { return x; };
	int gety() { return y; };
};