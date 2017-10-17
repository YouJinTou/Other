#ifndef LISTENER
#define LISTENER

#include <Windows.h>

class Listener
{
public:
	Listener();
	void Listen();
private:
	static constexpr int DefaultOpCodeSize = 2;

	static constexpr DWORD AmmoBaseAddress = 0x004637E9;
	static constexpr char* AmmoTargetOpCode = "\xFF\x06";
	static constexpr char* AmmoDefOpCode = "\xFF\x0E";

	static constexpr DWORD RapidFireBaseAddress = 0x004637E4;
	static constexpr char* RapidFireTargetOpCode = "\x90\x90";
	static constexpr char* RapidFireDefOpCode = "\x89\x0A";

	static constexpr DWORD AutomaticBaseAddress = 0x00463716;
	static constexpr char* AutomaticTargetOpCode = "\x7D\x09";
	static constexpr char* AutomaticDefOpCode = "\xEB\x09";

	static constexpr int RecoilBaseAddressesCount = 7;
	static constexpr DWORD RecoilBaseAddresses[RecoilBaseAddressesCount] =
	{ 0x00463781, 0x00463783, 0x00463786, 0x00463787, 0x0046378B, 0x0046378C, 0x0046378E };
	static constexpr char* RecoilTargetOpCodes[RecoilBaseAddressesCount] =
	{ "\x90\x90", "\x90\x90\x90", "\x90", "\x90\x90\x90\x90", "\x90", "\x90\x90", "\x90\x90" };
	static constexpr int RecoilTargetOpCodeSizes[] = { 2, 3, 1, 4, 1, 2, 2 };
	static constexpr char* RecoilDefOpCodes[RecoilBaseAddressesCount] =
	{ "\x8B\x16", "\x8B\x52\x14", "\x50", "\x8D\x4C\x24\x1C", "\x51", "\x8B\xCE", "\xFF\xD2" };
	static constexpr int RecoilDefOpCodeSizes[RecoilBaseAddressesCount] = { 2, 3, 1, 4, 1, 2, 2 };

	static constexpr DWORD HealthBaseAddress = 0x00509B74;
	static constexpr DWORD HealthOffsets[] = { 0xF8 };
	static constexpr int HealthOffsetsCount = 1;
	static constexpr char* TargetHealth = "\x39\x5";
	static constexpr char* DefaultHealth = "\x64\x0";
private:
	const DWORD healthAddress;
	bool infiniteAmmoOn = false;
	bool rapidFireOn = false;
	bool antiRecoilOn = false;
	bool infiniteHealthOn = false;
private:
	void HandleUserCommand();
	void HandleAmmoCommand();
	void HandleRapidFireCommand();
	void HandleRecoilCommand();
	void HandleHealthCommand();
	void WriteToMemory(
		const DWORD address,
		const char* valueToWrite,
		const int pageByteSize);
	DWORD GetAddressFromOffsets(
		const DWORD baseAddress, 
		const DWORD offsets[], 
		const int offsetsCount) const;
};

#endif // !LISTENER
