#pragma once
#include<vector>

#include "animal.h"
#include "food.h"

class Enviroment {
private:
	std::vector<Food*> foods;
public:
	//void createAnimal();
	void createFood(Food* food);
	FoodInfoCollected getFoodInfo(int x, int y);
	void deleteFood(int x, int y);
	std::vector<EnviromentInfoCollected> checkCollision(int x, int y, int sight);
};