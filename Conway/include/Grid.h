#pragma once

#include "Config.h"

constexpr int VertexCount = 6;

enum Cell_State {
	Dead,
	Alive
};

const sf::Color Cell_Colors[2] = {
	sf::Color::White,
	sf::Color::Yellow
};

class Grid
{
public:
	Grid();
	~Grid() = default;

	void Update(sf::Event event, sf::RenderWindow& window);
	void Render(sf::RenderWindow& window);

	void StepSimulation();
private:
	void SetCellColor(int x, int y, sf::Color c);
	void SetCellColor(sf::Vector2f pos, sf::Color c);
	
	void SetCellState(int x, int y, Cell_State st);
	void SetCellState(sf::Vector2f pos, Cell_State st);

	void OnHover(sf::Vector2i mouse);
	void OnClick(sf::Vector2i mouse);

	int GetCellIndex(sf::Vector2f pos);

	int CheckAlive(int v, int c, int r);


	std::array<Cell_State, Grid_Height* Grid_Width> m_CellStates;
	sf::VertexArray m_Vertecis;

	sf::Vector2f MousePos = sf::Vector2f(0, 0);
};

