#include "main.h"
#include "Application.h"



int main()
{
	Application application;
	if (!application.initialize())
		return EXIT_FAILURE;
	return application.execute();
}


