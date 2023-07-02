#include <veil.h>
#include <cstdio>
#include <cstring>
#include <wchar.h>

#ifdef _M_ARM64EC
#define MACHINE_NAME L"ARM64EC"
#elif _M_AMD64
#define MACHINE_NAME L"x64"
#elif _M_IX86
#define MACHINE_NAME L"x86"
#elif _M_ARM64
#define MACHINE_NAME L"ARM64"
#elif _M_ARM
#define MACHINE_NAME L"ARM"
#else
#error "Can't detect arch"

#endif

int wmain(int argc, wchar_t **argv)
{
	const wchar_t KRNL_NAME[] = L"NT";
	const wchar_t OS_NAME[] = L"Windows";
	

	if (argc == 1) {
		_putws(KRNL_NAME);
		return EXIT_SUCCESS;
	}

	wchar_t szHostName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD nSize = sizeof(szHostName) / sizeof(szHostName[0]);
	GetComputerNameW(szHostName, &nSize);

	RTL_OSVERSIONINFOW SystemInfo{};
	SystemInfo.dwOSVersionInfoSize = sizeof(SystemInfo);
	RtlGetVersion(&SystemInfo);

	for (int i = 1; i < argc; i++) {
		if (wcscmp(argv[i], L"-a") == 0 || wcscmp(argv[i], L"--all") == 0) {
			wprintf(L"%ls %ls %d %d.%d.%d %ls %ls ",
				KRNL_NAME,
				szHostName,
				SystemInfo.dwMajorVersion,
				SystemInfo.dwMajorVersion,
				SystemInfo.dwMinorVersion,
				SystemInfo.dwBuildNumber,
				MACHINE_NAME,
				OS_NAME);
		}
		else if (wcscmp(argv[i], L"-s") == 0 || wcscmp(argv[i], L"--kernel-name") == 0) {
			wprintf(L"%ls ", KRNL_NAME);
		}
		else if (wcscmp(argv[i], L"-n") == 0 || wcscmp(argv[i], L"--nodename") == 0) {
			wprintf(L"%ls ", szHostName);
		}
		else if (wcscmp(argv[i], L"-r") == 0 || wcscmp(argv[i], L"--kernel-release") == 0) {
			wprintf(L"%d ", SystemInfo.dwMajorVersion);
		}
		else if (wcscmp(argv[i], L"-v") == 0 || wcscmp(argv[i], L"--kernel-version") == 0) {
			wprintf(L"%d.%d.%d ",
				SystemInfo.dwMajorVersion,
				SystemInfo.dwMinorVersion,
				SystemInfo.dwBuildNumber);
		}
		else if (wcscmp(argv[i], L"-m") == 0 || wcscmp(argv[i], L"--machine") == 0) {
			wprintf(L"%ls ", MACHINE_NAME);
		}
		else if (wcscmp(argv[i], L"-o") == 0 || wcscmp(argv[i], L"--operating-system") == 0) {
			wprintf(L"%ls ", OS_NAME);
		}
		/* else if (wcscmp(argv[i], L"-h") == 0 || wcscmp(argv[i], L"--help") == 0) {
		 * Need help and invalid parameter arghhh
		 */
	}
	putwchar(L'\n');
}