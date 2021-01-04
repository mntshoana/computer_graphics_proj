#ifndef SELCTOR_CONSTANT
#define SELECTOR_CONSTANT

#include "Test.h"

class Item
{
public:
	std::string name;
	std::function<Test * ()> constructor;

	// Dynamically construct Tests using lambdas
	Item(std::string name, std::function<Test * ()> constructor)
		: name(name), constructor(constructor) {};
};


class Selector : public Test
{
public:
	Selector(Test*& test);
	void OnImGuiRender();

private:
	// Maintain a test menu
	Renderer renderer;
	Test*& currentTest;
	std::vector<Item> list;
public:
	template <typename T>
	void AddTest(const std::string& testName)
	{
		std::cout << "Adding test: " << testName << std::endl;
		list.push_back(Item(testName, []() { return new T(); }));
	}
};

#endif