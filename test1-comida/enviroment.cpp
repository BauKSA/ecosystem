#include<iostream>

#include "enviroment.h"
#include "functions.h"

void Enviroment::createFood(Food* food) {
	foods.push_back(food);
}

FoodInfoCollected Enviroment::getFoodInfo(int x, int y) {
	FoodInfoCollected foodInfo;
	for (size_t i = 0; i < foods.size(); i++) {
		if (foods.at(i)->getX() == x
			&& foods.at(i)->getY() == y) {
			foodInfo = foods.at(i)->getInfo();
		}
	}

	return foodInfo;
}

void Enviroment::deleteFood(int x, int y) {
	bool destroyed = false;
	for (size_t i = 0; i < foods.size(); i++) {
		if (foods.at(i)->getX() == x
			&& foods.at(i)->getY() == y) {
			foods.at(i)->destroy();
			destroyed = true;
		}
	}

	gotoxy(x, y);
	std::cout << " ";
}

std::vector<EnviromentInfoCollected> Enviroment::checkCollision(int x, int y, int sight) {
	std::vector<EnviromentInfoCollected> info;
	for (size_t i = 0; i < foods.size(); i++) {
		//check LEFT
		if (foods.at(i)->getX() == x + 1
			&& foods.at(i)->getY() == y) {
			EnviromentInfoCollected enviromentInfo;
			enviromentInfo.body = foods.at(i)->getBody();
			enviromentInfo.x = foods.at(i)->getX();
			enviromentInfo.y = foods.at(i)->getY();
			info.push_back(enviromentInfo);
		}
	}
}