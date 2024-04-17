#include <iostream>
#include <vector>
using namespace std;

class Herbivore {
protected:
	int weight;
	bool live;
public:
	Herbivore(int weight) {
		setWeight(80);
		setLive(true);
	}
	void setWeight(int weight) {
		this->weight = weight;
	}
	void setLive(bool live) {
		this->live = live;
	}
	bool getLive() const {
		return live;
	}
	int getWeight() const {
		return weight;
	}
	void eatGrass() {
		weight += 10;
	}
};

class Carnivore {
protected:
	int power;
public:
	Carnivore(int power) {
		setWeight(100);
	}
	void setWeight(int power) {
		this->power = power;
	}
	virtual void eat(Herbivore& herbivore) {
		if (power > herbivore.getWeight()) {
			power += 10;
			herbivore.setLive(false);
		}
		else {
			power -= 10;
		}
	}
};

class Wildebeest : public Herbivore {
public:
	Wildebeest() : Herbivore(weight) {}
};

class Bison : public Herbivore {
public:
	Bison() : Herbivore(weight) {}
};

class Lion : public Carnivore {
public:
	Lion() : Carnivore(power) {}
	void eat(Wildebeest& wildebeest) {
		if (power > wildebeest.getWeight()) {
			power += 10;
			wildebeest.setLive(false);
		}
		else {
			power -= 10;
		}
	}
};

class Wolf : public Carnivore {
public:
	Wolf() : Carnivore(power) {}
	void eat(Bison& bison) {
		if (power > bison.getWeight()) {
			power += 10;
			bison.setLive(false);
		}
		else {
			power -= 10;
		}
	}
};

class Continent {
protected:
	string name;
	vector<Herbivore> herbivores;
	vector<Carnivore> carnivores;
public:
	Continent(string name) {
		setName("Continent");
	}
	void setName(string name) {
		this->name = name;
	}
	virtual void addHerbivore(Herbivore& herbivore) {
		herbivores.push_back(herbivore);
	}
	virtual void addCarnivore(Carnivore& carnivore) {
		carnivores.push_back(carnivore);
	}
	vector<Herbivore> getHerbivores() const {
		return herbivores;
	}
	vector<Carnivore> getCarnivores() const {
		return carnivores;
	}
};

class Africa : public Continent {
public:
	Africa() : Continent("Africa") {}

};

class NorthAmerica : public Continent {
public:
	NorthAmerica() : Continent("North America") {}
};

class AnimalWorld {
private:
	vector<Continent> continents;
public:
	void addContinent(Continent& continent) {
		continents.push_back(continent);
	}
	void mealsHerbivores() {
		for (auto continent : continents) {
			for (auto& herbivore : continent.getHerbivores()) {
				herbivore.eatGrass();
			}
		}
	}
	void nutritionCarnivores() {
		for (auto& continent : continents) {
			for (auto& carnivore : continent.getCarnivores()) {
				for (auto& herbivore : continent.getHerbivores()) {
					if (herbivore.getLive()) {
						carnivore.eat(herbivore);
						break;
					}
				}
			}
		}
	}
};

int main() {
	Africa africa;
	NorthAmerica northAmerica;

	Wildebeest wildebeest;
	Bison bison;
	Lion lion;
	Wolf wolf;

	africa.addHerbivore(wildebeest);
	africa.addCarnivore(lion);
	northAmerica.addHerbivore(bison);
	northAmerica.addCarnivore(wolf);

	AnimalWorld world;

	world.addContinent(africa);
	world.addContinent(northAmerica);

	world.mealsHerbivores();

	world.nutritionCarnivores();
}