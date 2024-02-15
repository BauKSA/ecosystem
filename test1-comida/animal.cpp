#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>

#include "animal.h"
#include "functions.h"

void Animal::checkStarvation() {
	if (starvation <= 0) {
		destroy();
		std::cout << "Dead";
	} else {
		starvation--;
	}
}

void Animal::checkSurroundings() {
	gotoxy(0, 0);
	std::cout << "Check Surroundings";
	std::vector<EnviromentInfoCollected> info = enviroment->checkCollision(x, y, sight);
	for (int i = 0; i < info.size(); i++) {
		FoodInfoCollected foodInfo = checkFood(info.at(i).body);
		foodInfo.x = info.at(i).x;
		foodInfo.y = info.at(i).y;
		tempFoodInSurroundings.push_back(foodInfo);
	}

	if (tempFoodInSurroundings.size() > 0) {
		checkFoodSuitability();
	}
}

FoodInfoCollected Animal::checkFood(std::string body) {
	std::ifstream foodRegisterFile(foodRegister);
	if (!foodRegisterFile.is_open()) {
		std::cout << "Error while open the file.";
		FoodInfoCollected info;
		info.known = false;
		return info;
	}

	std::vector<FoodInfoCollected> foodInfoCollected;
	std::string line;

	bool firstLine = true;
	while (std::getline(foodRegisterFile, line)) {
		if (firstLine) {
			firstLine = false;
		}
		else {
			std::istringstream ss(line);
			//pasamos linea como si fuese un flujo de entrada, para poder separar por campos
			std::string key;

			// Crear una persona para almacenar los datos de la línea
			FoodInfoCollected foodInfo;

			// Procesar cada campo de la línea
			std::getline(ss, foodInfo.body, ',');
			//acá agarramos una línea de ss hasta que llegue a la coma y la guardamos en dato.name

			std::getline(ss, key, ',');
			//acá agarramos una línea de ss hasta que llegue a la coma y la guardamos en campo

			foodInfo.energy = std::stoi(key);
			//string to int stoi

			std::getline(ss, key, ',');
			foodInfo.poison = std::stoi(key);

			// Almacenar la persona en el vector
			foodInfoCollected.push_back(foodInfo);
		}
	}

	FoodInfoCollected food;
	food.body = "";
	food.energy = 0;
	food.poison = 0;
	food.x = 0;
	food.y = 0;
	food.known = false;

	for (int i = 0; i < foodInfoCollected.size(); i++) {
		if (foodInfoCollected.at(i).body == body) {
			food.body = foodInfoCollected.at(i).body;
			food.energy = foodInfoCollected.at(i).energy;
			food.poison = foodInfoCollected.at(i).poison;
			food.known = true;
		}
	}

	return food;
}

void Animal::checkFoodSuitability() {
	int index = 0;
	int suitability = 0;
	int i = 0;
	for (auto food : tempFoodInSurroundings) {
		int suit = 0;
		if (!food.known) {
			suit -= 20;
		}

		suit += food.energy;
		suit -= food.poison;

		if (suit > suitability) {
			suitability = suit;
			index = i;
		}

		i++;
	}

	if (suitability <= 0 && starvation >= 85) {
		eat(tempFoodInSurroundings.at(i));
	} else if (suitability > 0 && starvation >= 25) {
		eat(tempFoodInSurroundings.at(i));
	}
}

void Animal::eat(FoodInfoCollected food) {
	enviroment->deleteFood(food.x, food.y);

	if (!food.known) {
		FoodInfoCollected foodInfo = enviroment->getFoodInfo(food.x, food.y);
		starvation -= foodInfo.energy;
		starvation += foodInfo.poison;
		std::string log = foodInfo.body + "," + std::to_string(foodInfo.energy) + "," + std::to_string(foodInfo.poison);
		logFood(log);
	} else {
		starvation -= food.energy;
		starvation += food.poison;
	}
}

void Animal::logFood(std::string log) {
	std::ofstream foodRegisterFile(foodRegister, std::ios::app);
	if (!foodRegisterFile.is_open()) {
		std::cerr << "No se pudo abrir el archivo" << std::endl;
	}

	foodRegisterFile << log << std::endl;

	foodRegisterFile.close();
}

void Animal::move() {
	gotoxy(x, y);
	checkSurroundings();
	std::cout << " ";
	x++;
	draw();
}

void Animal::draw() {
	gotoxy(x, y);
	std::cout << body;
}

void Animal::live() {
	while (starvation > 0) {
		_sleep(500);
		move();
	}

	destroy();
}

void Animal::destroy() {
	gotoxy(0, 0);
	std::cout << "Dead                    ";
	gotoxy(x, y);
	std::cout << " ";
	delete this;
}