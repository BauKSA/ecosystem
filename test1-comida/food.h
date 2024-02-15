#pragma once
#include<string>

class Food {
private:
	std::string body;
	int energy;
	int poison;
	int x, y;
public:
	Food(std::string _body, int _energy, int _poison, int _x = 0, int _y = 0) :
		body(_body), energy(_energy), poison(_poison), x(_x), y(_y) {
		draw();
	}

	void draw();
	void destroy();

	int getX() { return x; };
	int getY() { return y; };
	std::string getBody() { return body; };
	FoodInfoCollected getInfo() {
		FoodInfoCollected info;
		info.body = body;
		info.energy = energy;
		info.poison = poison;
		info.x = x;
		info.y = y;

		return info;
	}
};