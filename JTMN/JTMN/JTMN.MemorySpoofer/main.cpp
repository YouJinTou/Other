#include "Initializer.h"
#include "Spoofer.h"

int main()
{
	Spoofer spoofer = Initializer::Initialize();

	while (spoofer.Spoofing())
	{		
	}

	return 0;
}