#ifndef LISTENER
#define LISTENER

#include <Windows.h>

class Listener
{
public:
	void Listen();
private:
	static constexpr unsigned long MaxTicks = 2000;
	static constexpr DWORD AmmoBaseAddress = 0x4637E9;
	static constexpr char* AmmoDefOpCode = "\xFF\x0E";
	static constexpr int AmmoDefOpCodeSize = 2;
	static constexpr char* AmmoTargetOpCode = "\xFF\x06";
	static constexpr int AmmoTargetOpCodeSize = 2;
private:
	unsigned long elapsed = 0;
	bool infiniteAmmoOn = false;
private:
	void HandleUserCommand();
	void HandleAmmoCommand();
	void WriteToMemory(
		const DWORD address, 
		const char* valueToWrite, 
		const int pageByteSize);
};

#endif // !LISTENER
