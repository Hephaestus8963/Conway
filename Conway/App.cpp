#include "App.h"

App* App::Initialize()
{
    if (m_Instance == nullptr) m_Instance = new App();
    return m_Instance;
}

void App::Update()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            m_Window.close();
            k_IsRunning = m_Window.isOpen();
        }
        else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) k_Simulating = !k_Simulating;
        if (!k_Simulating) m_Grid.Update(event, m_Window);
    }
    if (k_Simulating) m_Grid.StepSimulation();
}

void App::Render()
{
    m_Window.clear();
    m_Grid.Render(m_Window);
    m_Window.display();
}

bool App::IsRunning() const
{
    return k_IsRunning;
}

App::App()
{
    m_Window.create(WindowMode, Window_Title, Window_Style);
    k_IsRunning = m_Window.isOpen();
    k_Simulating = false;
}
