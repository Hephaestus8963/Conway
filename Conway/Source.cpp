#include "Config.h"
#include "App.h"

App* App::m_Instance = nullptr;

int main()
{
	App& app = *App::Initialize();
	while (app.IsRunning())
	{
		app.Update();
		app.Render();
	}
}