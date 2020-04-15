#include "App.hpp"
#include <iostream>

using namespace std;

int main()
{
	if (App::Singleton().Init(200, 200, 2))
		App::Singleton().Run();

	return 0;
}
