#include <iostream>
#include <windows.h>
#include <string.h>
#include <Lmcons.h>
#include <chrono>
#include <iomanip>	// not needed in C++20
#include <algorithm>	// not needed in C++20

#include <art.h>
#include <Registry.hpp>

#define setlght SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3)
#define setdflt SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7)
#define setbarc SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13)

// win10 ascii art terminal colour should be 3, default (for text) is 7
// you can modify these defines to customize the output colours!

std::wstring getusername() {
	
	TCHAR username[UNLEN + 1]{};
	DWORD size = UNLEN + 1;
	GetUserName((TCHAR*)username, &size);

	std::wstring userstring = username;

	return userstring;
}

std::wstring gethostname() {

	TCHAR hostname[UNLEN + 1]{};
	DWORD size = UNLEN + 1;
	GetComputerName((TCHAR*)hostname, &size);

	std::wstring userhost = hostname;
	return userhost;
}

std::wstring getwinver() {

	std::wstring car_bomb;
	using namespace m4x1m1l14n;

	try {
		auto key = Registry::LocalMachine->Open(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");

		car_bomb = key->GetString(L"ProductName");
		// don't ask


		std::wstring ws = key->GetString(L"CurrentBuild");

		// system is windows 11
		if (std::stoi(ws) > 21999) {
			car_bomb = L"Windows 11";
		}

		return car_bomb;
		
	}
	catch (const std::exception&) {
		car_bomb = L"Unknown";
		return car_bomb;
	}

}

//std::wstring getwinver2() {
//
//	using namespace m4x1m1l14n;
//
//	try {
//
//		auto key = Registry::LocalMachine->Open(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");
//
//		auto car_bomb = key->GetString(L"EditionId");
//
//		return car_bomb;
//	}
//	catch (const std::exception&)
//	{
//		std::wstring error = L"Unknown";
//		return error;
//	}
//
//}

std::wstring getwinbuild() {

	using namespace m4x1m1l14n;

	try {
		auto key = Registry::LocalMachine->Open(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");

		auto build = key->GetString(L"DisplayVersion");

		return build;
	}
	catch (const std::exception&) {
		std::wstring error = L"Unknown";
		return error;
	}
	
}

std::wstring getwinbuildnum() {

	using namespace m4x1m1l14n;

	try {
		auto key = Registry::LocalMachine->Open(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");

		auto buildnum = key->GetString(L"CurrentBuildNumber");

		return buildnum;
	}
	catch (const std::exception&) {
		std::wstring error = L"Unknown build number";
		return error;
	}
}

void getresolution(int& horizontal, int& vertical, int& hz) {
	DISPLAY_DEVICE dd{};
	dd.cb = sizeof(dd);
	
	EnumDisplayDevices(NULL, 0, &dd, 0);
	DEVMODE dm{};
	dm.dmSize = sizeof(dm);
	dm.dmDriverExtra = 0;
	
	EnumDisplaySettings(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm);
	
	horizontal = dm.dmPelsWidth;
	vertical = dm.dmPelsHeight;
	hz = dm.dmDisplayFrequency;
}

std::wstring getconsole() {

	std::setlocale(LC_ALL, "en_US.UTF-8");

	WCHAR console[UNLEN + 1]{};
	GetConsoleTitleW((WCHAR*)console, 256);

	std::wstring consolestring = console;

	return console; // consolestring?
}

std::chrono::milliseconds getuptime() {
	auto uptime = std::chrono::milliseconds(GetTickCount64());
	return uptime;
}

std::wstring getcpu() {
	using namespace m4x1m1l14n;

	try {
		auto key = Registry::LocalMachine->Open(L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");

		auto cpuname = key->GetString(L"ProcessorNameString");
		return cpuname;
	}
	catch (const std::exception&) {
		std::wstring error = L"Unknown processor";
		return error;
	}
}

std::wstring getgpu() {
	using namespace m4x1m1l14n;

	try {
		auto key = Registry::LocalMachine->Open(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\WinSAT");
		auto gpuname = key->GetString(L"PrimaryAdapterString");
		return gpuname;
	}
	catch (const std::exception&) {
		std::wstring error = L"Unknown (try running WinSAT to fix this)";
		return error;
	}

}



enum art_styles {
	WIN10,
	WIN11,
	UNKNOWN
};
art_styles artsel() {

	std::wstring win10 = L"Windows 10";
	std::wstring win11 = L"Windows 11";

	if (getwinver().find(win10) != std::string::npos) {
		return WIN10;
	}
	else if (getwinver().find(win11) != std::string::npos) {
		return WIN11;
	}
	else {
		return UNKNOWN;
	}
}

int getmem(int typesel) {

	MEMORYSTATUSEX mem{};

	mem.dwLength = sizeof(mem);

	GlobalMemoryStatusEx(&mem);

	int percent = mem.dwMemoryLoad;
	int total = mem.ullTotalPhys / 1024 / 1024;
	int used = total - mem.ullAvailPhys / 1024 / 1024;

	switch(typesel) {
	case 0:
		return percent;
		break;

	case 1:
		return total;
		break;

	default:
		return used;
	}
}

void getdisk() {
	ULARGE_INTEGER FreeBytesAvailableToCaller;
	ULARGE_INTEGER TotalNumberOfBytes;
	ULARGE_INTEGER TotalNumberOfFreeBytes;

	double total{};
	double free{};

	BOOL isKnownDisk = GetDiskFreeSpaceExA("C:\\", &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes);
	if (!isKnownDisk) {
		std::wcout << L"Disk info unknown";
		return;
	}
  /*printf("GB free: %llu\n", TotalNumberOfFreeBytes.QuadPart / (1024 * 1024));
	printf("GB total: %llu\n", TotalNumberOfBytes.QuadPart / (1024 * 1024));*/

	ULONGLONG totalspace = TotalNumberOfBytes.QuadPart / 1024 / 1024;
	if (totalspace <= INT_MAX) total = static_cast<double>(totalspace);

	ULONGLONG freespace = TotalNumberOfFreeBytes.QuadPart / 1024 / 1024;
	if (freespace <= INT_MAX) free = static_cast<double>(freespace);

	double totalgb = total / 1000;
	double freegb = free / 1000;

	totalgb = std::ceil(totalgb * 100.0) / 100.0;
	freegb = std::ceil(freegb * 100.0) / 100.0;

	std::wcout << LR"(C:\ )" << totalgb << L" GB (" << freegb << L" GB free)";
}

void drawbar(double input) {
	//bar colour define is at top of file

	std::cout << "-=[ ";

	int input1 = input / 5;

	setbarc;

	int i = 0;

	for (; i < input1; i++) {
		std::cout << "/";
	}
	
	setdflt;

	for (; i < 20; i++) {
		std::cout << "/";
	}

	std::cout << " ]=-";
}

void membar() {
	MEMORYSTATUSEX mem{};

	mem.dwLength = sizeof(mem);

	GlobalMemoryStatusEx(&mem);

	double percent = mem.dwMemoryLoad;
	int total = mem.ullTotalPhys / 1024 / 1024;
	int avail = mem.ullAvailPhys / 1024 / 1024;

	//std::wcout << percent;

	drawbar(percent);
}

void diskbar() {
	ULARGE_INTEGER FreeBytesAvailableToCaller;
	ULARGE_INTEGER TotalNumberOfBytes;
	ULARGE_INTEGER TotalNumberOfFreeBytes;

	double total{};
	double free{};

	BOOL canDrawDiskBar = GetDiskFreeSpaceExA("C:\\", &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes);
	if (!canDrawDiskBar) {
		std::wcout << L"Unable to draw disk bar";
		return;
	}

	ULONGLONG totalspace = TotalNumberOfBytes.QuadPart / 1024 / 1024;
	if (totalspace <= INT_MAX)
		total = static_cast<double>(totalspace);

	ULONGLONG freespace = TotalNumberOfFreeBytes.QuadPart / 1024 / 1024;
	if (freespace <= INT_MAX)
		free = static_cast<double>(freespace);

	double totalgb = total / 1000;
	double freegb = free / 1000;

	double percent = free / total;
	percent = 1.0 - percent;
	percent = percent * 100;

	//std::wcout << percent;

	drawbar(percent);
}

void color1() {
	// std::setlocale(LC_ALL, "en_US.UTF-16");

	// char sq = static_cast<char>(254);

	for (int i = 0; i < 127; i += 4) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
		std::wcout << " ";
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}

void color2() {

	int i = 128;
	int n = 0;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);

	for (; n < 4; n++) {
		std::wcout << " ";
	}

	for (; i < 254; i += 4) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
		std::wcout << " ";
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}

int debug() {

	// calling this function lists (almost) all vars in a list without labels or any fancy stuff

	std::wcout << getusername() << std::endl;
	std::wcout << gethostname() << std::endl;
	std::wcout << getwinver() << std::endl;
	//std::wcout << getwinver2() << std::endl;
	std::wcout << getwinbuild() << std::endl;

	int uptime = std::chrono::duration_cast<std::chrono::milliseconds>(getuptime()).count();

	/*int seconds = (int)(uptime / 1000) % 60;*/
	int minutes = (int)((uptime / (1000 * 60)) % 60);
	int hours = (int)((uptime / (1000 * 60 * 60)) % 24);

	//nevermind who needs seconds anyways

	/*while (seconds < 10)
	{
		std::string seconds = seconds;
		seconds = '0' + seconds;
		break;

	}*/

	std::string plural1;
	std::string plural2;

	if (hours == 1) { // todo : hours <= 1?
		plural1 = "hour";
	}
	else {
		plural1 = "hours";
	}

	if (minutes == 1) { // todo : minutes <= 1?
		plural2 = "minute";
	}
	else {
		plural2 = "minutes";
	}

	std::cout << hours <<" " << plural1 << ", " << minutes << " " << plural2 << std::endl;
	
	int horizontal = 0;
	int vertical = 0;
	int hz = 0;

	getresolution(horizontal, vertical, hz);
	std::cout << horizontal << 'x' << vertical << std::endl;

	std::wcout << getconsole() << std::endl;
	std::wcout << getcpu() << std::endl;
	std::wcout << getgpu() << std::endl;

	std::cout << getmem(2) << " MB / " << getmem(1) << " MB (" << getmem(0) << "% in use)";

	return 0;
}

void neofetch() {

	// actual render

	std::wstring wide0(getusername());

	std::string username;
	std::transform(wide0.begin(), wide0.end(), std::back_inserter(username), [](wchar_t c) {
		return (char)c;
		});

	//username = "Administrator";

	std::wstring wide1(gethostname());

	std::string hostname;
	std::transform(wide1.begin(), wide1.end(), std::back_inserter(hostname), [](wchar_t c) {
		return (char)c;
		});

	/*std::cout << username << std::endl;
	std::cout << hostname << std::endl;

	std::cout << username.length() << std::endl;
	std::cout << hostname.length() << std::endl;*/

	std::wstring divider = L"--------------";

	int uptime = std::chrono::duration_cast<std::chrono::seconds>(getuptime()).count();

	int minutes = (int)((uptime / (60)) % 60);
	int hours = (int)((uptime / (60 * 60)) % 24);
	int days = (int)(uptime / (60 * 60 * 24));
	//int months = (long)(uptime / (1000 * 60 * 60 * 24 * 30) % 12);
	// this WILL overflow

	std::string plural1 = (hours == 1) ? "hour" : "hours";
	std::string plural2 = (minutes == 1) ? "minute" : "minutes";
	std::string plural3 = (days == 1) ? "day" : "days";
	//std::string plural4 = (months == 1) ? "month" : "months";

	int horizontal = 0;
	int vertical = 0;
	int hz = 0;

	getresolution(horizontal, vertical, hz);

	art_styles selected_art = artsel(); // temporarily save arsel results
	if (selected_art == WIN10) {

		using namespace std;

		setlght; wcout << win10art[ 0] << setw(19) << endl;
		setlght; wcout << win10art[ 1] << setw(12 + username.length()) << right << getusername(); setdflt; cout << '@'; setlght;  wcout << gethostname() << endl; setdflt;
		setlght; wcout << win10art[ 2]; setdflt; wcout << setw(26) << right << divider << endl;
		setlght; wcout << win10art[ 3] << setw(16) << right << L"OS: "; setdflt; wcout << getwinver() << endl;
		setlght; wcout << win10art[ 4] << setw(19) << right << L"Build: "; setdflt; wcout << getwinbuild() << " (" << getwinbuildnum() << ')' << endl;
		setlght; wcout << win10art[ 5] << setw(20) << right << L"Uptime: "; setdflt; cout << days << " " << plural3 << ", " << hours << " " << plural1 << ", " << minutes << " " << plural2 << std::endl;
		setlght; wcout << win10art[ 6] << setw(24) << right << L"Resolution: "; setdflt; cout << horizontal << 'x' << vertical << " @" << hz << "Hz" << std::endl;
		setlght; wcout << win10art[ 7] << setw(22) << right << L"Terminal: "; setdflt; wcout << getconsole() << endl;
		setlght; wcout << win10art[ 8] << setw(17) << right << L"CPU: "; setdflt; wcout << getcpu() << endl;
		setlght; wcout << win10art[ 9] << setw(17) << right << L"GPU: "; setdflt; wcout << getgpu() << endl;
		setlght; wcout << win10art[10] << setw(20) << right << L"Memory: "; setdflt; cout << getmem(2) << " MB / " << getmem(1) << " MB (" << getmem(0) << "% in use)" << endl;
		setlght; wcout << win10art[11] << setw(18) << right << L"Disk: "; setdflt; getdisk(); std::cout << endl;
		setlght; wcout << win10art[12] << setw(17) << endl;
		setlght; wcout << win10art[13] << setw(19) << right << L"Mem%:  "; setdflt; membar(); std::cout << endl;
		setlght; wcout << win10art[14] << setw(19) << endl;
		setlght; wcout << win10art[15] << setw(19) << right << L"Disk%: "; setdflt; diskbar(); std::cout << endl;
		setlght; wcout << win10art[16] << setw(19) << endl;
		setlght; wcout << win10art[17] << setw(13) << right; color1(); cout << endl;
		setlght; wcout << win10art[18] << setw(9) << right; color2(); cout << endl;
		setlght; wcout << win10art[19] << setw(19) << endl;
		setdflt;
	}

	else if (selected_art == WIN11) {

		using namespace std;

		setlght; wcout << win11art[ 0] << setw(12 + username.length()) << right << getusername(); setdflt; cout << '@'; setlght;  wcout << gethostname() << endl; setdflt;
		setlght; wcout << win11art[ 1]; setdflt; wcout << setw(26) << right << divider << endl;
		setlght; wcout << win11art[ 2] << setw(16) << right << L"OS: "; setdflt; wcout << getwinver() << endl;
		setlght; wcout << win11art[ 3] << setw(19) << right << L"Build: "; setdflt; wcout << getwinbuild() << " (" << getwinbuildnum() << ')' << endl;
		setlght; wcout << win11art[ 4] << setw(20) << right << L"Uptime: "; setdflt; cout << days << " " << plural3 << ", " << hours << " " << plural1 << ", " << minutes << " " << plural2 << std::endl;
		setlght; wcout << win11art[ 5] << setw(24) << right << L"Resolution: "; setdflt; cout << horizontal << 'x' << vertical << " @" << hz << "Hz" << std::endl;
		setlght; wcout << win11art[ 6] << setw(22) << right << L"Terminal: "; setdflt; wcout << getconsole() << endl;
		setlght; wcout << win11art[ 7] << setw(17) << right << L"CPU: "; setdflt; wcout << getcpu() << endl;
		setlght; wcout << win11art[ 8] << setw(17) << right << L"GPU: "; setdflt; wcout << getgpu() << endl;
		setlght; wcout << win11art[ 9] << setw(20) << right << L"Memory: "; setdflt; cout << getmem(2) << " MB / " << getmem(1) << " MB (" << getmem(0) << "% in use)" << endl;
		setlght; wcout << win11art[10] << setw(18) << right << L"Disk: "; setdflt; getdisk(); std::cout << endl;
		setlght; wcout << win11art[11] << setw(19) << endl;
		setlght; wcout << win11art[12] << setw(19) << right << L"Mem%:  "; setdflt; membar(); std::cout << endl;
		setlght; wcout << win11art[13] << setw(19) << endl;
		setlght; wcout << win11art[14] << setw(19) << right << L"Disk%: "; setdflt; diskbar(); std::cout << endl;
		setlght; wcout << win11art[15] << setw(19) << endl;
		setlght; wcout << win11art[16] << setw(13) << right; color1(); cout << endl;
		setlght; wcout << win11art[17] << setw(9) << right; color2(); cout << endl;
		setlght; wcout << win11art[18] << setw(19) << endl;
		setdflt;
	}

	else if (selected_art == UNKNOWN) {

		using namespace std;

		setlght; wcout << unknownart[ 0] << setw(12 + username.length()) << right << getusername(); setdflt; cout << '@'; setlght;  wcout << gethostname() << endl; setdflt;
		setlght; wcout << unknownart[ 1]; setdflt; wcout << setw(26) << right << divider << endl;
		setlght; wcout << unknownart[ 2] << setw(16) << right << L"OS: "; setdflt; wcout << getwinver() << endl;
		setlght; wcout << unknownart[ 3] << setw(19) << right << L"Build: "; setdflt; wcout << getwinbuild() << " (" << getwinbuildnum() << ')' << endl;
		setlght; wcout << unknownart[ 4] << setw(20) << right << L"Uptime: "; setdflt; cout << days << " " << plural3 << ", " << hours << " " << plural1 << ", " << minutes << " " << plural2 << std::endl;
		setlght; wcout << unknownart[ 5] << setw(24) << right << L"Resolution: "; setdflt; cout << horizontal << 'x' << vertical << " @" << hz << "Hz" << std::endl;
		setlght; wcout << unknownart[ 6] << setw(22) << right << L"Terminal: "; setdflt; wcout << getconsole() << endl;
		setlght; wcout << unknownart[ 7] << setw(17) << right << L"CPU: "; setdflt; wcout << getcpu() << endl;
		setlght; wcout << unknownart[ 8] << setw(17) << right << L"GPU: "; setdflt; wcout << getgpu() << endl;
		setlght; wcout << unknownart[ 9] << setw(20) << right << L"Memory: "; setdflt; cout << getmem(2) << " MB / " << getmem(1) << " MB (" << getmem(0) << "% in use)" << endl;
		setlght; wcout << unknownart[10] << setw(18) << right << L"Disk: "; setdflt; getdisk(); std::cout << endl;
		setlght; wcout << unknownart[11] << setw(19) << endl;
		setlght; wcout << unknownart[12] << setw(19) << right << L"Mem%:  "; setdflt; membar(); std::cout << endl;
		setlght; wcout << unknownart[13] << setw(19) << endl;
		setlght; wcout << unknownart[14] << setw(19) << right << L"Disk%: "; setdflt; diskbar(); std::cout << endl;
		setlght; wcout << unknownart[15] << setw(19) << endl;
		setlght; wcout << unknownart[16] << setw(13) << right; color1(); cout << endl;
		setlght; wcout << unknownart[17] << setw(9) << right; color2(); cout << endl;
		setlght; wcout << unknownart[18] << setw(19) << endl;
		setdflt;
	}

	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // setdflt?
		std::cout << "Unable to determine Windows version." << std::endl;
		system("PAUSE");
	}
}

int main() {
	//debug();

	neofetch();
	return 0;
}