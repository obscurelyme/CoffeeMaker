#include "Game/PlayerEvents.hpp"

std::unique_ptr<CoffeeMaker::Event> incScore = std::make_unique<CoffeeMaker::Event>();
std::unique_ptr<CoffeeMaker::Event> decLife = std::make_unique<CoffeeMaker::Event>();
