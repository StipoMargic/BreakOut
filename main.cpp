#include "App.hpp"

int main()
{
	App app;

	if (app.Init(200, 200, 2))
		app.Run();

	return 0;
}
