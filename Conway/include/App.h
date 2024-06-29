#pragma once

#include "Config.h"
#include "Grid.h"

class App
{
public:
	static App* Initialize();

	void Update();
	void Render();

	bool IsRunning() const;

private:
	bool k_IsRunning;

	bool k_Simulating;

	sf::RenderWindow m_Window;
	sf::Font m_Fira;

	Grid m_Grid;

private:
	App();
	~App() = default;

	static App* m_Instance;
};
