#pragma once

#include <string>
#include <vector>
#include <array>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

constexpr int Window_Width = 700;
constexpr int Window_Height = 500;

constexpr int Grid_Width = 60;
constexpr int Grid_Height = 40;

constexpr int Cell_Length = 10;

const sf::VideoMode WindowMode(Window_Width, Window_Height);
const std::string Window_Title = "App";
const std::uint32_t Window_Style = sf::Style::Close | sf::Style::Titlebar;

inline void PrintVectorf(sf::Vector2f v) {
	std::cout << v.x << ", " << v.y << '\n';
}
inline void PrintVectori(sf::Vector2i v) {
	std::cout << v.x << ", " << v.y << '\n';
}