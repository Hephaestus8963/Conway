#include "Grid.h"

Grid::Grid()
{
	m_Vertecis.resize(Grid_Height * Grid_Width * VertexCount);
	m_Vertecis.setPrimitiveType(sf::Triangles);

	for (int r = 0; r < Grid_Height; r++)
		for (int c = 0; c < Grid_Width; c++) {
			int v = GetCellIndex(sf::Vector2f(c, r));
			sf::Vertex* Rect = &m_Vertecis[0] + VertexCount * v;

			m_CellStates[v] = Dead;

			Rect[0].position = sf::Vector2f(c * Cell_Length, r * Cell_Length);
			Rect[1].position = sf::Vector2f(c * Cell_Length, (r + 1) * Cell_Length);
			Rect[2].position = sf::Vector2f((c + 1) * Cell_Length, r * Cell_Length);
			Rect[3].position = sf::Vector2f((c + 1) * Cell_Length, r * Cell_Length);
			Rect[4].position = sf::Vector2f(c * Cell_Length, (r + 1) * Cell_Length);
			Rect[5].position = sf::Vector2f((c + 1) * Cell_Length, (r + 1) * Cell_Length);

			SetCellColor(c, r, Cell_Colors[m_CellStates[v]]);

		}
}

void Grid::Update(sf::Event event, sf::RenderWindow& window)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
		OnHover(sf::Mouse::getPosition(window));
		break;
	case sf::Event::MouseButtonPressed:
		OnClick(sf::Mouse::getPosition(window));
		break;
	default:
		break;
	}
}

void Grid::Render(sf::RenderWindow& window)
{
	window.draw(m_Vertecis);
}

void Grid::SetCellColor(int x, int y, sf::Color c)
{
	int v = GetCellIndex(sf::Vector2f(x, y));
	if (v > Grid_Width * Grid_Width) std::cout << "V out of range\n";
	else {
		sf::Vertex* Rect = &m_Vertecis[0] + VertexCount * v;
		for (int i = 0; i < VertexCount; i++) Rect[i].color = c;

	}
}

void Grid::SetCellColor(sf::Vector2f pos, sf::Color c)
{
	SetCellColor(pos.x, pos.y, c);
}

void Grid::SetCellState(int x, int y, Cell_State st)
{
	int v = GetCellIndex(sf::Vector2f(x, y));
	if (v >= Grid_Height * Grid_Width) std::cout << "Cell index out of range\n";
	else m_CellStates[v] = st;
}

void Grid::SetCellState(sf::Vector2f pos, Cell_State st)
{
	SetCellState(pos.x, pos.y, st);
}

void Grid::OnHover(sf::Vector2i mouse)
{
	if (mouse.x < 0 || mouse.x >= Grid_Width * Cell_Length || mouse.y < 0 || mouse.y >= Grid_Height * Cell_Length) return;
	int v = GetCellIndex(MousePos);
	SetCellColor(MousePos, Cell_Colors[m_CellStates[v]]);
	MousePos = sf::Vector2f(mouse.x / 10, mouse.y / 10);
	v = GetCellIndex(MousePos);
	if (m_CellStates[v] == Alive) SetCellColor(MousePos, Cell_Colors[Dead]);
	else SetCellColor(MousePos, Cell_Colors[Alive]);
}

void Grid::OnClick(sf::Vector2i mouse)
{
	sf::Vector2f pos = sf::Vector2f(mouse.x/10, mouse.y/10);
	if (pos.x < 0 || pos.x >= Grid_Width || pos.y < 0 || pos.y >= Grid_Height) return;
	int v = GetCellIndex(pos);
	if (m_CellStates[v] == Alive) {
		m_CellStates[v] = Dead;
	}
	else m_CellStates[v] = Alive;
	SetCellColor(pos, Cell_Colors[m_CellStates[v]]);
}


int Grid::GetCellIndex(sf::Vector2f pos)
{
	return pos.y * Grid_Width + pos.x;
}

int Grid::CheckAlive(int v, int c, int r) {
	int aliveCounter = 0;
	for (int p = -1; p < 2; p++) {
		if (r + p < 0 || r + p >= Grid_Height) continue;
		for (int q = -1; q < 2; q++) {
			if (c + q < 0 || c + q >= Grid_Width) continue;
			if (r == 0 && c == 0) continue;
			int nV = v + p * Grid_Width + q;
			if (m_CellStates[nV] == Alive)
				aliveCounter++;
		}
	}
	return aliveCounter;
}

void Grid::StepSimulation()
{
	for (int r = 0; r < Grid_Height; r++)
		for (int c = 0; c < Grid_Width; c++) {
			int v = GetCellIndex(sf::Vector2f(c, r));
			//std::cout << "Checking cell " << v << '\n';
			int aliveCounter = CheckAlive(v, c, r);

			if (aliveCounter > 1) std::cout << "Cell at " << r << ", " << c << " has " << aliveCounter << " alive neighbors.\n";
 
			//if (m_CellStates[v] == Alive && (aliveCounter < 2 || aliveCounter > 3)) {
			//	m_CellStates[v] = Dead;
			//}
			//else if (m_CellStates[v] == Dead && aliveCounter == 3) {
			//	m_CellStates[v] = Alive;
			//}
			//SetCellColor(c, r, Cell_Colors[m_CellStates[v]]);
		}

}
