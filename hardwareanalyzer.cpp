#include <iostream>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")
#include <VersionHelpers.h>

/* 
 * author: Shawn M. Crawford 2018+
 *
 * Get Windows hardware and software information.
 * This version requires Windows 2000 or newer OS (for now).
 *
 */
using namespace std;

typedef BOOL (WINAPI *LPGetProductInfo)(DWORD dwOSMajorVersion, DWORD dwOSMinorVersion, DWORD dwSpMajorVersion, DWORD dwSpMinorVersion, PDWORD pdwReturnedProductType);

/* Many are already defined in winnt.h, so just define them if they are not found. */
#ifndef PRODUCT_BUSINESS
#define PRODUCT_BUSINESS 0x00000006
#endif
#ifndef PRODUCT_BUSINESS_N
#define PRODUCT_BUSINESS_N 0x00000010
#endif
#ifndef PRODUCT_CLUSTER_SERVER
#define PRODUCT_CLUSTER_SERVER 0x00000012
#endif
#ifndef PRODUCT_CLUSTER_SERVER_V
#define PRODUCT_CLUSTER_SERVER_V 0x00000040
#endif
#ifndef PRODUCT_CORE
#define PRODUCT_CORE 0x00000065
#endif
#ifndef PRODUCT_CORE_COUNTRYSPECIFIC
#define PRODUCT_CORE_COUNTRYSPECIFIC 0x00000063
#endif
#ifndef PRODUCT_CORE_N
#define PRODUCT_CORE_N 0x00000062
#endif
#ifndef PRODUCT_CORE_SINGLELANGUAGE
#define PRODUCT_CORE_SINGLELANGUAGE 0x00000064
#endif
#ifndef PRODUCT_DATACENTER_EVALUATION_SERVER
#define PRODUCT_DATACENTER_EVALUATION_SERVER 0x00000050
#endif
#ifndef PRODUCT_DATACENTER_SERVER
#define PRODUCT_DATACENTER_SERVER 0x00000008
#endif
#ifndef PRODUCT_DATACENTER_SERVER_CORE
#define PRODUCT_DATACENTER_SERVER_CORE 0x0000000C
#endif
#ifndef PRODUCT_DATACENTER_SERVER_CORE_V
#define PRODUCT_DATACENTER_SERVER_CORE_V 0x00000027
#endif
#ifndef PRODUCT_DATACENTER_SERVER_V
#define PRODUCT_DATACENTER_SERVER_V 0x00000025
#endif
#ifndef PRODUCT_EDUCATION
#define PRODUCT_EDUCATION 0x00000079
#define PRODUCT_EDUCATION_N 0x0000007A
#endif
#ifndef PRODUCT_ENTERPRISE
#define PRODUCT_ENTERPRISE 0x00000004
#endif
#ifndef PRODUCT_ENTERPRISE_E
#define PRODUCT_ENTERPRISE_E 0x00000046
#endif
#ifndef PRODUCT_ENTERPRISE_EVALUATION
#define PRODUCT_ENTERPRISE_EVALUATION 0x00000048
#endif
#ifndef PRODUCT_ENTERPRISE_N
#define PRODUCT_ENTERPRISE_N 0x0000001B
#endif
#ifndef PRODUCT_ENTERPRISE_N_EVALUATION
#define PRODUCT_ENTERPRISE_N_EVALUATION 0x00000054
#endif
#ifndef PRODUCT_ENTERPRISE_S
#define PRODUCT_ENTERPRISE_S 0x0000007D
#endif
#ifndef PRODUCT_ENTERPRISE_S_EVALUATION
#define PRODUCT_ENTERPRISE_S_EVALUATION 0x00000081
#endif
#ifndef PRODUCT_ENTERPRISE_S_N
#define PRODUCT_ENTERPRISE_S_N 0x0000007E
#endif
#ifndef PRODUCT_ENTERPRISE_S_N_EVALUATION
#define PRODUCT_ENTERPRISE_S_N_EVALUATION 0x00000082
#endif
#ifndef PRODUCT_ENTERPRISE_SERVER
#define PRODUCT_ENTERPRISE_SERVER 0x0000000A
#endif
#ifndef PRODUCT_ENTERPRISE_SERVER_CORE
#define PRODUCT_ENTERPRISE_SERVER_CORE 0x0000000E
#endif
#ifndef PRODUCT_ENTERPRISE_SERVER_CORE_V
#define PRODUCT_ENTERPRISE_SERVER_CORE_V 0x00000029
#endif
#ifndef PRODUCT_ENTERPRISE_SERVER_IA64
#define PRODUCT_ENTERPRISE_SERVER_IA64 0x0000000F
#endif
#ifndef PRODUCT_ENTERPRISE_SERVER_V
#define PRODUCT_ENTERPRISE_SERVER_V 0x00000026
#endif
#ifndef PRODUCT_ESSENTIALBUSINESS_SERVER_ADDL
#define PRODUCT_ESSENTIALBUSINESS_SERVER_ADDL 0x0000003C
#endif
#ifndef PRODUCT_ESSENTIALBUSINESS_SERVER_ADDLSVC
#define PRODUCT_ESSENTIALBUSINESS_SERVER_ADDLSVC 0x0000003E
#endif
#ifndef PRODUCT_ESSENTIALBUSINESS_SERVER_MGMT
#define PRODUCT_ESSENTIALBUSINESS_SERVER_MGMT 0x0000003B
#endif
#ifndef PRODUCT_ESSENTIALBUSINESS_SERVER_MGMTSVC
#define PRODUCT_ESSENTIALBUSINESS_SERVER_MGMTSVC 0x0000003D
#endif
#ifndef PRODUCT_HOME_BASIC
#define PRODUCT_HOME_BASIC 0x00000002
#endif
#ifndef PRODUCT_HOME_BASIC_E
#define PRODUCT_HOME_BASIC_E 0x00000043
#endif
#ifndef PRODUCT_HOME_BASIC_N
#define PRODUCT_HOME_BASIC_N 0x00000005
#endif
#ifndef PRODUCT_HOME_PREMIUM
#define PRODUCT_HOME_PREMIUM 0x00000003
#endif
#ifndef PRODUCT_HOME_PREMIUM_E
#define PRODUCT_HOME_PREMIUM_E 0x00000044
#endif
#ifndef PRODUCT_HOME_PREMIUM_N
#define PRODUCT_HOME_PREMIUM_N 0x0000001A
#endif
#ifndef PRODUCT_HOME_PREMIUM_SERVER
#define PRODUCT_HOME_PREMIUM_SERVER 0x00000022
#endif
#ifndef PRODUCT_HOME_SERVER
#define PRODUCT_HOME_SERVER 0x00000013
#endif
#ifndef PRODUCT_HYPERV
#define PRODUCT_HYPERV 0x0000002A
#endif
#ifndef PRODUCT_IOTUAP
#define PRODUCT_IOTUAP 0x0000007B
#endif
#ifndef PRODUCT_IOTUAPCOMMERCIAL
#define PRODUCT_IOTUAPCOMMERCIAL 0x00000083
#endif
#ifndef PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT
#define PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT 0x0000001E
#endif
#ifndef PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING
#define PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING 0x00000020
#endif
#ifndef PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY
#define PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY 0x0000001F
#endif
#ifndef PRODUCT_MOBILE_CORE
#define PRODUCT_MOBILE_CORE 0x00000068
#endif
#ifndef PRODUCT_MOBILE_ENTERPRISE
#define PRODUCT_MOBILE_ENTERPRISE 0x00000085
#endif
#ifndef PRODUCT_MULTIPOINT_PREMIUM_SERVER
#define PRODUCT_MULTIPOINT_PREMIUM_SERVER 0x0000004D
#endif
#ifndef PRODUCT_MULTIPOINT_STANDARD_SERVER
#define PRODUCT_MULTIPOINT_STANDARD_SERVER 0x0000004C
#endif
#ifndef PRODUCT_PRO_WORKSTATION
#define PRODUCT_PRO_WORKSTATION 0x000000A1
#endif
#ifndef PRODUCT_PRO_WORKSTATION_N
#define PRODUCT_PRO_WORKSTATION_N 0x000000A2
#endif
#ifndef PRODUCT_PROFESSIONAL
#define PRODUCT_PROFESSIONAL 0x00000030
#endif
#ifndef PRODUCT_PROFESSIONAL_E
#define PRODUCT_PROFESSIONAL_E 0x00000045
#endif
#ifndef PRODUCT_PROFESSIONAL_N
#define PRODUCT_PROFESSIONAL_N 0x00000031
#endif
#ifndef PRODUCT_PROFESSIONAL_WMC
#define PRODUCT_PROFESSIONAL_WMC 0x00000067
#endif
#ifndef PRODUCT_SB_SOLUTION_SERVER
#define PRODUCT_SB_SOLUTION_SERVER 0x00000032
#endif
#ifndef PRODUCT_SB_SOLUTION_SERVER_EM
#define PRODUCT_SB_SOLUTION_SERVER_EM 0x00000036
#endif
#ifndef PRODUCT_SERVER_FOR_SB_SOLUTIONS
#define PRODUCT_SERVER_FOR_SB_SOLUTIONS 0x00000033
#endif
#ifndef PRODUCT_SERVER_FOR_SB_SOLUTIONS_EM
#define PRODUCT_SERVER_FOR_SB_SOLUTIONS_EM 0x00000037
#endif
#ifndef PRODUCT_SERVER_FOR_SMALLBUSINESS
#define PRODUCT_SERVER_FOR_SMALLBUSINESS 0x00000018
#endif
#ifndef PRODUCT_SERVER_FOR_SMALLBUSINESS_V
#define PRODUCT_SERVER_FOR_SMALLBUSINESS_V 0x00000023
#endif
#ifndef PRODUCT_SERVER_FOUNDATION
#define PRODUCT_SERVER_FOUNDATION 0x00000021
#endif
#ifndef PRODUCT_SMALLBUSINESS_SERVER
#define PRODUCT_SMALLBUSINESS_SERVER 0x00000009
#endif
#ifndef PRODUCT_SMALLBUSINESS_SERVER_PREMIUM
#define PRODUCT_SMALLBUSINESS_SERVER_PREMIUM 0x00000019
#endif
#ifndef PRODUCT_SMALLBUSINESS_SERVER_PREMIUM_CORE
#define PRODUCT_SMALLBUSINESS_SERVER_PREMIUM_CORE 0x0000003F
#endif
#ifndef PRODUCT_SOLUTION_EMBEDDEDSERVER
#define PRODUCT_SOLUTION_EMBEDDEDSERVER 0x00000038
#endif
#ifndef PRODUCT_STANDARD_EVALUATION_SERVER
#define PRODUCT_STANDARD_EVALUATION_SERVER 0x0000004F
#endif
#ifndef PRODUCT_STANDARD_SERVER
#define PRODUCT_STANDARD_SERVER 0x00000007
#endif
#ifndef PRODUCT_STANDARD_SERVER_CORE
#define PRODUCT_STANDARD_SERVER_CORE 0x0000000D
#endif
#ifndef PRODUCT_STANDARD_SERVER_CORE_V
#define PRODUCT_STANDARD_SERVER_CORE_V 0x00000028
#endif
#ifndef PRODUCT_STANDARD_SERVER_V
#define PRODUCT_STANDARD_SERVER_V 0x00000024
#endif
#ifndef PRODUCT_STANDARD_SERVER_SOLUTIONS
#define PRODUCT_STANDARD_SERVER_SOLUTIONS 0x00000034
#endif
#ifndef PRODUCT_STANDARD_SERVER_SOLUTIONS_CORE
#define PRODUCT_STANDARD_SERVER_SOLUTIONS_CORE 0x00000035
#endif
#ifndef PRODUCT_STARTER
#define PRODUCT_STARTER 0x0000000B
#endif
#ifndef PRODUCT_STARTER_E
#define PRODUCT_STARTER_E 0x00000042
#endif
#ifndef PRODUCT_STARTER_N
#define PRODUCT_STARTER_N 0x0000002F
#endif
#ifndef PRODUCT_STORAGE_ENTERPRISE_SERVER
#define PRODUCT_STORAGE_ENTERPRISE_SERVER 0x00000017
#endif
#ifndef PRODUCT_STORAGE_ENTERPRISE_SERVER_CORE
#define PRODUCT_STORAGE_ENTERPRISE_SERVER_CORE 0x0000002E
#endif
#ifndef PRODUCT_STORAGE_EXPRESS_SERVER
#define PRODUCT_STORAGE_EXPRESS_SERVER 0x00000014
#endif
#ifndef PRODUCT_STORAGE_EXPRESS_SERVER_CORE
#define PRODUCT_STORAGE_EXPRESS_SERVER_CORE 0x0000002B
#endif
#ifndef PRODUCT_STORAGE_STANDARD_EVALUATION_SERVER
#define PRODUCT_STORAGE_STANDARD_EVALUATION_SERVER 0x00000060
#endif
#ifndef PRODUCT_STORAGE_STANDARD_SERVER
#define PRODUCT_STORAGE_STANDARD_SERVER 0x00000015
#endif
#ifndef PRODUCT_STORAGE_STANDARD_SERVER_CORE
#define PRODUCT_STORAGE_STANDARD_SERVER_CORE 0x0000002C
#endif
#ifndef PRODUCT_STORAGE_WORKGROUP_EVALUATION_SERVER
#define PRODUCT_STORAGE_WORKGROUP_EVALUATION_SERVER 0x0000005F
#endif
#ifndef PRODUCT_STORAGE_WORKGROUP_SERVER
#define PRODUCT_STORAGE_WORKGROUP_SERVER 0x00000016
#endif
#ifndef PRODUCT_STORAGE_WORKGROUP_SERVER_CORE
#define PRODUCT_STORAGE_WORKGROUP_SERVER_CORE 0x0000002D
#endif
#ifndef PRODUCT_ULTIMATE
#define PRODUCT_ULTIMATE 0x00000001
#endif
#ifndef PRODUCT_ULTIMATE_E
#define PRODUCT_ULTIMATE_E 0x00000047
#endif
#ifndef PRODUCT_ULTIMATE_N
#define PRODUCT_ULTIMATE_N 0x0000001C
#endif
#ifndef PRODUCT_UNDEFINED
#define PRODUCT_UNDEFINED 0x00000000
#endif
#ifndef PRODUCT_WEB_SERVER
#define PRODUCT_WEB_SERVER 0x00000011
#endif
#ifndef PRODUCT_WEB_SERVER_CORE
#define PRODUCT_WEB_SERVER_CORE 0x0000001D
#endif
#ifndef PRODUCT_UNLICENSED
#define PRODUCT_UNLICENSED 0xABCDABCD
#endif

int main (int argc, char *argv[])
{
	char ch;

    SYSTEM_INFO sysInfo;
	HW_PROFILE_INFO hwProfileInfo;
	// OSVERSIONINFOEX osVersionInfoEx;
	DWORD dwVersion = 0; 
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0; 
    DWORD dwBuild = 0;
	DWORD productInfo = 0;
 
    // Copy the hardware information to the SYSTEM_INFO structure. 
    GetSystemInfo(&sysInfo);
	GetCurrentHwProfile(&hwProfileInfo);
	// GetVersion(&osVersionInfoEx);
	dwVersion = GetVersion();
 
	// Get the Windows version.
    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

    // Get the build number.
    if (dwVersion < 0x80000000)
	{
        dwBuild = (DWORD)(HIWORD(dwVersion));
	}

	// productInfo = GetProductInfo(dwMajorVersion, dwMinorVersion, 0, 0);
	HMODULE kernel32 = GetModuleHandle("Kernel32.dll");
	LPGetProductInfo GetProductInfo = reinterpret_cast<LPGetProductInfo>(GetProcAddress(kernel32, "GetProductInfo"));

	GetProductInfo(dwMajorVersion, dwMinorVersion, 0, 0, &productInfo);

    printf("Hardware information: \n");
    printf("  OEM ID: %u\n", sysInfo.dwOemId);
    printf("  Number of processors: %u\n", sysInfo.dwNumberOfProcessors);
    printf("  Page size: %u\n", sysInfo.dwPageSize);
    printf("  Processor type: %u\n", sysInfo.dwProcessorType);
    printf("  Minimum application address: %lx\n", sysInfo.lpMinimumApplicationAddress);
    printf("  Maximum application address: %lx\n", sysInfo.lpMaximumApplicationAddress);
    printf("  Active processor mask: %u\n", sysInfo.dwActiveProcessorMask);
	printf("  Allocation Granularity: %u\n", sysInfo.dwAllocationGranularity);
	printf("  Processor Level: %u\n", sysInfo.wProcessorLevel);
	printf("  Processor Revision: %u\n", sysInfo.wProcessorRevision);
	printf("  Processor Architecture: %u\n", sysInfo.wProcessorArchitecture);
	printf("  Reserved: %u\n", sysInfo.wReserved);
    printf("\n");
	printf("  Dock Info: %d\n", hwProfileInfo.dwDockInfo);
	printf("  Profile Guid: %s\n", hwProfileInfo.szHwProfileGuid);
	printf("  Profile Name: %s\n", hwProfileInfo.szHwProfileName);
	printf("\n");
	// IsProcessorFeaturePresent requires Windows 2000+
	printf("Processor Features:\n");
	try {
		printf("  The 64-bit load/store atomic instructions are available: %s\n", IsProcessorFeaturePresent(PF_ARM_64BIT_LOADSTORE_ATOMIC) ? "true" : "false");
		printf("  The divide instructions are available: %s\n", IsProcessorFeaturePresent(PF_ARM_DIVIDE_INSTRUCTION_AVAILABLE) ? "true" : "false");
		printf("  The divide instructions are available: %s\n", IsProcessorFeaturePresent(PF_ARM_DIVIDE_INSTRUCTION_AVAILABLE) ? "true" : "false");
		printf("  The external cache is available: %s\n", IsProcessorFeaturePresent(PF_ARM_EXTERNAL_CACHE_AVAILABLE) ? "true" : "false");
		printf("  The floating-point multiply-accumulate instruction is available: %s\n", IsProcessorFeaturePresent(PF_ARM_FMAC_INSTRUCTIONS_AVAILABLE) ? "true" : "false");
		printf("  The VFP/Neon: 32 x 64bit register bank is present: %s\n", IsProcessorFeaturePresent(PF_ARM_VFP_32_REGISTERS_AVAILABLE) ? "true" : "false");
		printf("  The 3D-Now instruction set is available: %s\n", IsProcessorFeaturePresent(PF_3DNOW_INSTRUCTIONS_AVAILABLE) ? "true" : "false");
		printf("  The processor channels are enabled: %s\n", IsProcessorFeaturePresent(PF_CHANNELS_ENABLED) ? "true" : "false");
		printf("  The atomic compare and exchange operation (cmpxchg) is available: %s\n", IsProcessorFeaturePresent(PF_COMPARE_EXCHANGE_DOUBLE) ? "true" : "false");
		printf("  The atomic compare and exchange 128-bit operation (cmpxchg16b) is available: %s\n", IsProcessorFeaturePresent(PF_COMPARE_EXCHANGE128) ? "true" : "false");
		printf("  The atomic compare 64 and exchange 128-bit operation (cmp8xchg16) is available: %s\n", IsProcessorFeaturePresent(PF_COMPARE64_EXCHANGE128) ? "true" : "false");
		printf("  _fastfail() is available: %s\n", IsProcessorFeaturePresent(PF_FASTFAIL_AVAILABLE) ? "true" : "false");
		printf("  Floating-point operations are emulated using a software emulator: %s\n", IsProcessorFeaturePresent(PF_FLOATING_POINT_EMULATED) ? "true" : "false");
		printf("  On a Pentium, a floating-point precision error can occur in rare circumstances: %s\n", IsProcessorFeaturePresent(PF_FLOATING_POINT_PRECISION_ERRATA) ? "true" : "false");
		printf("  The MMX instruction set is available: %s\n", IsProcessorFeaturePresent(PF_MMX_INSTRUCTIONS_AVAILABLE) ? "true" : "false");
		printf("  Data execution prevention is enabled: %s\n", IsProcessorFeaturePresent(PF_NX_ENABLED) ? "true" : "false");
		printf("  The processor is PAE-enabled (Physical Address Extension): %s\n", IsProcessorFeaturePresent(PF_PAE_ENABLED) ? "true" : "false");
		printf("  The RDTSC instruction is available: %s\n", IsProcessorFeaturePresent(PF_RDTSC_INSTRUCTION_AVAILABLE) ? "true" : "false");
		printf("  RDFSBASE, RDGSBASE, WRFSBASE, and WRGSBASE instructions are available: %s\n", IsProcessorFeaturePresent(PF_RDWRFSGSBASE_AVAILABLE) ? "true" : "false");
		printf("  Second Level Address Translation is supported by the hardware: %s\n", IsProcessorFeaturePresent(PF_SECOND_LEVEL_ADDRESS_TRANSLATION) ? "true" : "false");
		printf("  The SSE3 instruction set is available: %s\n", IsProcessorFeaturePresent(PF_SSE3_INSTRUCTIONS_AVAILABLE) ? "true" : "false");
		printf("  Virtualization is enabled in the firmware: %s\n", IsProcessorFeaturePresent(PF_VIRT_FIRMWARE_ENABLED) ? "true" : "false");
		printf("  The SSE instruction set is available: %s\n", IsProcessorFeaturePresent(PF_XMMI_INSTRUCTIONS_AVAILABLE) ? "true" : "false");
		printf("  The SSE2 instruction set is available: %s\n", IsProcessorFeaturePresent(PF_XMMI64_INSTRUCTIONS_AVAILABLE) ? "true" : "false");
		printf("  The processor implements the XSAVE and XRSTOR instructions: %s\n", IsProcessorFeaturePresent(PF_XSAVE_ENABLED) ? "true" : "false");
	} catch (exception e) {
        // IsProcessorFeaturePresent requires Windows 2000+
	    printf("    Processor Features are not available on this Operating System (IsProcessorFeaturePresent requires Windows 2000+");
	}

	printf("\n");
	printf("Product Info:\n");
	try {
		printf("Version: %d.%d (%d)\n",
				dwMajorVersion,
				dwMinorVersion,
				dwBuild);
		printf("  Major Version: %d\n", dwMajorVersion);
		printf("  Minor Version: %d\n", dwMinorVersion);
		printf("  Build Number: %d\n", dwBuild);

		printf("  Operating System: ");
		if (dwMajorVersion == 3 && dwMinorVersion == 2 && (dwBuild == 28 || dwBuild == 33)) {
			printf("Windows 95 Pre-Chicago");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 00 && (dwBuild == 15 || dwBuild == 21 || dwBuild == 26 || dwBuild == 29 || dwBuild == 34
			|| dwBuild == 36 || dwBuild == 38 || dwBuild == 40 || dwBuild == 45 || dwBuild == 47 || dwBuild == 55 || dwBuild == 56 || dwBuild == 57
			|| dwBuild == 58)) { // 4.00.15b 21i 29s 40e 58g
			printf("Windows 95 Pre-Milestone 4");
		}
		else if (dwMajorVersion == 3 && dwMinorVersion == 2 && (dwBuild == 58 || dwBuild == 61 || dwBuild == 70)) { // 4.00.58s
			printf("Windows 95 Milestone 4");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 00 && (dwBuild == 73 || dwBuild == 78 || dwBuild == 81 || dwBuild == 86 || dwBuild == 87
			|| dwBuild == 90 || dwBuild == 92 || dwBuild == 99 || dwBuild == 103 || dwBuild == 105 || dwBuild == 108)) { // 4.00.73f 73g 90b 90c 90d
			printf("Windows 95 Milestone 5");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 00 && (dwBuild == 116 || dwBuild == 117 || dwBuild == 122 || dwBuild == 156 || dwBuild == 165
			|| dwBuild == 166 || dwBuild == 167 || dwBuild == 170 || dwBuild == 177 || dwBuild == 180 || dwBuild == 189 || dwBuild == 197)) {
			printf("Windows 95 Beta 1 Milestone 6");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 0 && dwBuild == 225) {
			printf("Windows 95 Chinese Beta 1 Milestone 7");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 0 && dwBuild == 323) {
			printf("Windows 95 Japanese Beta 1 Milestone 7");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 00 && (dwBuild == 213 || dwBuild == 216 || dwBuild == 222 || dwBuild == 224 || dwBuild == 265
			|| dwBuild == 267 || dwBuild == 275 || dwBuild == 285 || dwBuild == 286 || dwBuild == 302 || dwBuild == 304 || dwBuild == 305
			|| dwBuild == 306 || dwBuild == 311 || dwBuild == 314 || dwBuild == 318 || dwBuild == 324 || dwBuild == 331 || dwBuild == 337)) {
			printf("Windows 95 Beta 2 Milestone 7");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 00 && (dwBuild == 342 || dwBuild == 345 || dwBuild == 346 || dwBuild == 347 || dwBuild == 405
			|| dwBuild == 420 || dwBuild == 431 || dwBuild == 435 || dwBuild == 440 || dwBuild == 445 || dwBuild == 450 || dwBuild == 456
			|| dwBuild == 462 || dwBuild == 468 || dwBuild == 474)) {
			printf("Windows 95 Beta 3 Milestone 8");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 00 && (dwBuild == 480 || dwBuild == 484 || dwBuild == 490 || dwBuild == 499 || dwBuild == 501
			|| dwBuild == 502 || dwBuild == 852)) {
			printf("Windows 95 RC 1");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 00 && (dwBuild == 708 || dwBuild == 720)) {
			printf("Windows 95 Far East Beta");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 00 && (dwBuild == 810 || dwBuild == 812 || dwBuild == 842)) {
			printf("Windows 95 Middle East Beta");
		}
		// Pre-RTM 4.00.950r-2 -3 -4 -5
		// RTM 4.00.950r-6 -7
		else if (dwMajorVersion == 4 && dwMinorVersion == 0 && dwBuild == 950) { // 4.00.950a
			printf("Windows 95 OEM Service Release 1 (95A)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 00 && (dwBuild == 1009 || dwBuild == 1034 || dwBuild == 1043 || dwBuild == 1048 || dwBuild == 1054
			|| dwBuild == 1068 || dwBuild == 1078 || dwBuild == 1094)) {
			printf("Windows 95 OEM Service Release 2 (95B)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 0 && dwBuild == 1111) {
			printf("Windows 95 OEM Service Release 2 (95B) RTM");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 0 && dwBuild == 1175) {
			printf("Windows Cairo (Unreleased)");
		}
		else if ((dwMajorVersion == 4 && dwMinorVersion == 3 && (dwBuild == 1132 || dwBuild == 1154 || dwBuild == 1174))) {
			printf("Windows 98 Pre-Alpha (Detroit)");
		}
		else if ((dwMajorVersion == 4 && dwMinorVersion == 10 && (dwBuild == 1221 || dwBuild == 1233))) {
			printf("Windows 98 Pre-Alpha (Detroit)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 0 && dwBuild == 1107) {
			printf("Windows 95 OEM Service Release 2.1 Beta");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 3 && (dwBuild == 1212 || dwBuild == 1213)) {
			printf("Windows 95 OEM Service Release 2.1 / Windows 95 OEM Service Release 2.1 RTM");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 3 && dwBuild == 1214) {
			printf("Windows 95 OEM Service Release 2.1 RTM / Windows 95 OEM Service Release 2.5 C");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 3 && dwBuild == 1216) {
			printf("Windows 95 OEM Service Release 2.5");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && (dwBuild == 960 || dwBuild == 999 || dwBuild == 1000 || dwBuild == 1265)) {
			printf("Windows Nashville / Cleveland / Windows 96 (Unreleased)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && (dwBuild == 1351 || dwBuild == 1353 || dwBuild == 1381 || dwBuild == 1387 || dwBuild == 1397)) {
			printf("Windows 98 (Alpha)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && (dwBuild == 1400 || dwBuild == 1410 || dwBuild == 1411 || dwBuild == 1415 || dwBuild == 1425
			|| dwBuild == 1434 || dwBuild == 1488 || dwBuild == 1500 || dwBuild == 1511 || dwBuild == 1518 || dwBuild == 1525 || dwBuild == 1532 || dwBuild == 1538)) {
			printf("Windows 98 (Beta 1)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && dwBuild == 1423) {
			printf("Windows 98 (Beta 1) (Developer Release)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && (dwBuild == 1543 || dwBuild == 1544 || dwBuild == 1545 || dwBuild == 1546 || dwBuild == 1551
			|| dwBuild == 1556 || dwBuild == 1559 || dwBuild == 1564 || dwBuild == 1569 || dwBuild == 1576 || dwBuild == 1577 || dwBuild == 1581 || dwBuild == 1588
			|| dwBuild == 1593 || dwBuild == 1595 || dwBuild == 1596 || dwBuild == 1598)) {
			printf("Windows 98 (Beta 2)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && (dwBuild == 1602 || dwBuild == 1605 || dwBuild == 1611 || dwBuild == 1612 || dwBuild == 1614
			|| dwBuild == 1619 || dwBuild == 1624)) {
			printf("Windows 98 (Beta 2.1)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && (dwBuild == 1629 || dwBuild == 1633 || dwBuild == 1650 || dwBuild == 1658 || dwBuild == 1666
			|| dwBuild == 1671 || dwBuild == 1676 || dwBuild == 1677 || dwBuild == 1681)) {
			printf("Windows 98 (Beta 3)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && (dwBuild == 1687 || dwBuild == 1691)) {
			printf("Windows 98 (RC 0)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && (dwBuild == 1702 || dwBuild == 1708 || dwBuild == 1713 || dwBuild == 1720)) {
			printf("Windows 98 (Pre RC 1)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && dwBuild == 1721) {
			printf("Windows 98 (RC 1)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && dwBuild == 1723) {
			printf("Windows 98 (RC 2)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && dwBuild == 1900) { // 4.10.1900.5
			printf("Windows 98 (RC 3)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && dwBuild == 1910) { // 4.10.1900.4 1900.6
			printf("Windows 98 (Pre RC 1)");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && dwBuild == 1998) {
			printf("Windows 98 / Windows 98 RTM");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && dwBuild == 1999) {
			printf("Windows 99 (Mod) based off of Windows 98 / Windows 98 RTM");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && dwBuild == 2017) {
			printf("Windows 98 Multimedia Update");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && (dwBuild == 2088 || dwBuild == 2091)) {
			printf("Windows 98 Service Pack 1 Beta");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && (dwBuild == 2106 || dwBuild == 2120 || dwBuild == 2131 || dwBuild == 2136 || dwBuild == 2150
			|| dwBuild == 2183 || dwBuild == 2184 || dwBuild == 2185)) {
			printf("Windows 98 Second Edition Beta");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10 && dwBuild == 2222) { // 4.10.2222 A
			printf("Windows 98 Second Edition / Windows 98 Second Edition RTM");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 90 && (dwBuild == 2332 || dwBuild == 2346 || dwBuild == 2348 || dwBuild == 2350 || dwBuild == 2358
			|| dwBuild == 2363 || dwBuild == 2368 || dwBuild == 2374)) { // 4.90.2332.2 2350.3
			printf("Windows Millenium Developer Release");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 90 && (dwBuild == 2380 || dwBuild == 2394 || dwBuild == 2399)) { // 4.90.2380.2
			printf("Windows Millenium Beta 1");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 90 && (dwBuild == 2404 || dwBuild == 2416 || dwBuild == 2419 || dwBuild == 2429 || dwBuild == 2443
			|| dwBuild == 2452 || dwBuild == 2460 || dwBuild == 2465 || dwBuild == 2468 || dwBuild == 2470 || dwBuild == 2476 || dwBuild == 2481)) {
			printf("Windows Millenium Beta 2");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 90 && (dwBuild == 2491 || dwBuild == 2495 || dwBuild == 2499 || dwBuild == 2500 || dwBuild == 2509
			|| dwBuild == 2513 || dwBuild == 2516 || dwBuild == 2519)) { // 4.90.2499.3 4.90.2499.7 4.90.2500.1
			printf("Windows Millenium Beta 3");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 90 && dwBuild == 2525) { // 4.90.2525.6
			printf("Windows Millenium RC 0");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 90 && dwBuild == 2535) { // 4.90.2525.6
			printf("Windows Millenium RC 2");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 90 && dwBuild == 3000) {
			printf("Windows Millenium / Windows Millenium RTM");
		}
		else if (dwMajorVersion == 3 && dwMinorVersion == 10 && dwBuild == 528) {
			printf("Windows NT 3.1");
		}
		else if (dwMajorVersion == 3 && dwMinorVersion == 50 && dwBuild == 807) {
			printf("Windows NT 3.5");
		}
		else if (dwMajorVersion == 3 && dwMinorVersion == 50 && dwBuild == 841) {
			printf("Windows Cairo (Unreleased)");
		}
		else if (dwMajorVersion == 3 && dwMinorVersion == 51 && dwBuild == 1057) {
			printf("Windows NT 3.51");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 0 && dwBuild == 1381) {
			printf("Windows NT 4.00");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 0 && dwBuild == 1515) {
			printf("Windows NT 5.00 (Beta 2)");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 0 && dwBuild == 2031) {
			printf("Windows 2000 (Beta 3)");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 0 && dwBuild == 2128) {
			printf("Windows 2000 (Beta 3 RC2)");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 0 && dwBuild == 2183) {
			printf("Windows 2000 (Beta 3)");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 0 && dwBuild == 2195) {
			printf("Windows 2000");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 0 && dwBuild == 2197) {
			printf("Windows 2000 (main.000106-2102)");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 0 && dwBuild == 2202) {
			printf("Windows 2000 (ntvbl06.000202-1835)");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 1 && (dwBuild == 2202 || dwBuild == 2211 || dwBuild == 2222 || dwBuild == 2223 || dwBuild == 2225 )) {
			printf("Windows XP (Alpha) (2202.1.ntvbl06.000202-1835 2211.1.main.000309-1512 2222.1.Lab06_N.000407-1900 2223.1.main.000411-2307 2225.1.ntvbl06.0004?)?");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 1 && dwBuild == 2239) {
			printf("Windows XP Technical Beta, pre-Beta 1 (2239.1.idx01.000531-1103)?");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 1 && dwBuild == 2250) {
			printf("Whistler Server Preview / Windows XP Technical Beta, pre-Beta 1 (2250.1.main.000628-2110)?");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 1 && dwBuild == 2257) {
			printf("Whistler Server alpha / Windows XP Technical Beta, pre-Beta 1 (2257.1.idx01.000810-2103)?");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 1 && dwBuild == 2267) {
			printf("Whistler Server interim release / Windows XP Technical Beta, pre-Beta 1 (2267.1.idx01.000910-1316)?");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 1 && dwBuild == 2276) {
			printf("Windows XP Technical Beta, pre-Beta 1 (2276.1.Lab02_N.000928-2023)?");
		}
        else if (dwMajorVersion == 5 && dwMinorVersion == 1 && (dwBuild == 2285 || dwBuild == 2287 || dwBuild == 2296 || dwBuild == 2309 || dwBuild == 2317
            || dwBuild == 2400 || dwBuild == 2415 || dwBuild == 2416 || dwBuild == 2419 || dwBuild == 2422 || dwBuild == 2428 || dwBuild == 2430
            || dwBuild == 2432 || dwBuild == 2433 || dwBuild == 2438 || dwBuild == 2442 || dwBuild == 2446 || dwBuild == 2454 || dwBuild == 2455
            || dwBuild == 2457 || dwBuild == 2458 || dwBuild == 2459)) {
			printf("Windows XP Beta 1, post-Beta 1 (2285.beta1.001009-1544, 2287.1.beta1.001012-1643, 2296.1.beta1.001024-1157, 2309.prebeta2.001047-1279, 2317.main.001105-1214, 2400.1.Lab01_N.001022-2228, 2415.lab06_N.010102-1932, 2416.idx01.010104-1958, 2419.idx02.010113-1154, 2422.1.lab02_n.010201-1120, 2428.idx01.010129-1827, 2430.main.010130-1821, 2432.main.010203-1757, 2433.main.010206-1822, 2438.main.010212-1914, 2438.Lab06_N.010213-1700, 2442.main.010217-1630, 2446.main.010224-2228, 2454.main.010306-1653,2455.main.010307-1701, 2457.main.010309-1904, 2458.main.010310-1552, 2459.main.010312-1811 )?");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 1 && dwBuild == 2410) {
			printf("Whistler Server interim release / Windows XP Beta 1, post-Beta 1 (2410.main.001208-1937, 2410.1.idx02.001212-1507)?");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 1 && (dwBuild == 2462 || dwBuild == 2463 || dwBuild == 2464 || dwBuild == 2465 || dwBuild == 2467
			 || dwBuild == 2469 || dwBuild == 2474 || dwBuild == 2475 || dwBuild == 2481 || dwBuild == 2485 || dwBuild == 2486 || dwBuild == 2493
			 || dwBuild == 2494 || dwBuild == 2495 || dwBuild == 2498 || dwBuild == 2499 || dwBuild == 2501 || dwBuild == 2502 || dwBuild == 2504)) {
			printf("Windows XP Beta 2, post-Beta 2 (2462.main.010315-1739, 2463.main.010328-1824, 2464.main.010405-1517, 2465.main.010412-2007, 2467.main.010418-1202, 2469.idx02.010508-1228, 2474.main.010508-1907, 2475.idx01.010514-2023, 2481.main.010523-1905, 2485.main.010531-2130, 2486.main.010602-1927, 2493.main.010612-1737, 2494.main.010613-1739, 2495.main.010614-1724, 2498.main.010618-1744, 2499.main.010619-1834, 2501.main.010621-1759, 2502.main.010622-1750, 2504.main.010625-1923)?");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 1 && (dwBuild == 2505 || dwBuild == 2509 || dwBuild == 2517 || dwBuild == 2518 || dwBuild == 2520
			|| dwBuild == 2522 || dwBuild == 2525)) {
			printf("Windows XP RC1, post-RC1");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 1 && (dwBuild == 2526 || dwBuild == 2531 || dwBuild == 2532 || dwBuild == 2535 || dwBuild == 2542)) {
			printf("Windows XP RC2, post-RC2");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 1 && dwBuild == 2600) {
			printf("Windows XP / Windows XP Service Pack 1 / Windows XP Service Pack 2 / Windows XP Service Pack 3 / Windows XP Service Pack 1 Beta / Windows XP Service Pack 2 Beta / Windows XP Service Pack 3 Beta");
		}
		// else if (dwMajorVersion == 5 && dwMinorVersion == 1 && dwBuild == 2600) { // 5.1.2600.1105-1106
		//    printf("Windows XP Service Pack 1");
		// }
		// else if (dwMajorVersion == 5 && dwMinorVersion == 1 && dwBuild == 2600) { // 5.1.2600.2180
		//    printf("Windows XP Service Pack 2");
		// }
		// else if (dwMajorVersion == 5 && dwMinorVersion == 1 && dwBuild == 2600) { // 5.1.2600.???
		//    printf("Windows XP Service Pack 3");
		// }
		else if (dwMajorVersion == 5 && dwMinorVersion == 2 && dwBuild == 2893) {
			printf("Windows XP (bobcatsr1(bobld))");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 2 && dwBuild == 3541) {
			printf("Windows .NET Server interim");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 2 && dwBuild == 3590) {
			printf("Windows .NET Server Beta 3");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 2 && dwBuild == 3660) {
			printf("Windows .NET Server Release Candidate 1");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 2 && dwBuild == 3718) {
			printf("Windows .NET Server 2003 RC2");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 2 && dwBuild == 3763) {
			printf("Windows Server 2003 (Beta?)");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 1 && dwBuild == 3790) {
			printf("Windows XP Service Pack 1 beta (x64)");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 2 && dwBuild == 3790) {
			printf("Windows Server 2003");
		}
		// else if (dwMajorVersion == 5 && dwMinorVersion == 2 && dwBuild == 3790) { // 5.2.3790.1180
		//    printf("Windows Server 2003, Service Pack 1");
		// }
		// else if (dwMajorVersion == 5 && dwMinorVersion == 2 && dwBuild == 3790) { // 5.2.3790.1218
		//    printf("Windows Server 2003");
		// }
		else if (dwMajorVersion == 5 && dwMinorVersion == 5 && dwBuild == 3790) { // 5.5.5000, 5022, 5056, 5067, 5082, 5086, 5094, 5095, 5096, 5099, 5111, 5116, 5117, 5118, 5119, 5120, 5179
			printf("Windows Neptune (Unreleased)");
		}
		// else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == ????) {
		//    printf("Windows Home Server");
		// }
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5048) {
			printf("Windows Longhorn");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5112) {
			printf("Windows Vista, Beta 1");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5219) {
			printf("Windows Vista, Community Technology Preview");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5259) {
			printf("Windows Vista, TAP Preview");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && (dwBuild == 5270 || dwBuild == 5308)) {
			printf("Windows Vista, CTP");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5342) {
			printf("Windows Vista, CTP (Refresh)");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5365) {
			printf("Windows Vista, April EWD");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5381) {
			printf("Windows Vista, Beta 2 Preview");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5384) {
			printf("Windows Vista, Beta 2");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5456) {
			printf("Windows Vista, Pre-RC1");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5472) {
			printf("Windows Vista, Pre-RC1, Build 5472");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5536) {
			printf("Windows Vista, Pre-RC1, Build 5536");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5600) { // 6.0.5600.16384
			printf("Windows Vista, RC1");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5700) {
			printf("Windows Vista, Pre-RC2");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5728) {
			printf("Windows Vista, Pre-RC2, Build 5728");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5744) { // 6.0.5744.16384
			printf("Windows Vista, RC2");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5808) {
			printf("Windows Vista, Pre-RTM, Build 5808");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5824) {
			printf("Windows Vista, Pre-RTM, Build 5824");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 5840) {
			printf("Windows Vista, Pre-RTM, Build 5840");
		}
		// else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 6000) { // 6.0.6000.16386
		//    printf("Windows Vista, RTM");
		// }
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 6000) {
			printf("Windows Vista");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 6002) {
			printf("Windows Vista, Service Pack 2");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && dwBuild == 6001) {
			printf("Windows Vista, Service Pack 2 / Windows Server 2008");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && (dwBuild == 6429 || dwBuild == 6469 || dwBuild == 6471)) {
			printf("Windows 7, Pre-Milestone 1");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && dwBuild == 6519) {
			printf("Windows 7, Milestone 1");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && (dwBuild == 6568 || dwBuild == 6589 || dwBuild == 6608)) {
			printf("Windows 7, Milestone 2");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && (dwBuild == 6748 || dwBuild == 6730 || dwBuild == 6780 || dwBuild == 6801)) {
			printf("Windows 7, Milestone 3");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && (dwBuild == 6910 || dwBuild == 6931 || dwBuild == 6933 || dwBuild == 6936 || dwBuild == 6938 || dwBuild == 6941 || dwBuild == 6944 || dwBuild == 6948 || dwBuild == 6953 || dwBuild == 6956 || dwBuild == 6965)) {
			printf("Windows 7, Pre-Beta");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && dwBuild == 7000) {
			printf("Windows 7, Beta");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && (dwBuild == 7022 || dwBuild == 7032 || dwBuild == 7048 || dwBuild == 7051 || dwBuild == 7055 || dwBuild == 7057 || dwBuild == 7063 || dwBuild == 7068)) {
			printf("Windows 7, Pre-RC");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && (dwBuild == 7077 || dwBuild == 7100)) {
			printf("Windows 7, RTM Escrow");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && (dwBuild == 7106 || dwBuild == 7127 || dwBuild == 7137 || dwBuild == 7140 || dwBuild == 7201 || dwBuild == 7225 || dwBuild == 7227 || dwBuild == 7229 || dwBuild == 7231 || dwBuild == 7232 || dwBuild == 7233)) { // 6.1.7600.19384
			printf("Windows 7, Pre-RTM");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && (dwBuild == 7260 || dwBuild == 7264 || dwBuild == 7272)) { // 6.1.7600.19384
			printf("Windows 7, RTM Escrow");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && dwBuild == 7600) { // 6.1.7600.16385
			printf("Windows 7, RTM / Windows Server 2008 R2, RTM");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && dwBuild == 7601) {
			printf("Windows 7, SP1 / Windows Server 2008 R2, SP1");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && (dwBuild == 7650 || dwBuild == 7652 || dwBuild == 7700)) {
			printf("Windows 7, Post-RTM");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1 && dwBuild == 8400) {
			printf("Windows Home Server 2011");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 2 && dwBuild == 9200) {
			printf("Windows 8 / Windows Server 2012");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 2 && dwBuild == 10211) {
			printf("Windows Phone 8");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 3 && dwBuild == 9200) {
			printf("Windows 8.1 / Windows Server 2012 R2");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 3 && dwBuild == 9600) {
			printf("Windows 8.1, Update 1 / Windows Server 2012 R2");
		}
		else if (dwMajorVersion == 10 && dwMinorVersion == 0 && dwBuild == 10240) {
			printf("Windows 10 (1507) Threshold");
		}
		else if (dwMajorVersion == 10 && dwMinorVersion == 0 && dwBuild == 10586) {
			printf("Windows 10 (1511) Threshold 2");
		}
		else if (dwMajorVersion == 10 && dwMinorVersion == 0 && dwBuild == 14393) {
			printf("Windows 10 (1607) Redstone / Windows Server 2016 Redstone");
		}
		else if (dwMajorVersion == 10 && dwMinorVersion == 0 && dwBuild == 15063) {
			printf("Windows 10 (1703) Redstone 2");
		}
		else if (dwMajorVersion == 10 && dwMinorVersion == 0 && dwBuild == 16299) {
			printf("Windows 10 (1709) Redstone 3");
		}
		else if (dwMajorVersion == 10 && dwMinorVersion == 0 && dwBuild == 17133) { // TBA as of April 4th, 2018
			printf("Windows 10 (1803) Redstone 4");
		}
		else if (dwMajorVersion == 10 && dwMinorVersion == 0 && dwBuild == 17634) { // TBA as of April 4th, 2018
			printf("Windows 10 (1809) Redstone 5");
		}
		// Generic if not found above
		else if (dwMajorVersion == 4 && dwMinorVersion == 0) {
			printf("Windows 95 / Windows NT 4.0");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 3) {
			printf("Windows 95 OSR 2.x");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 10) {
			printf("Windows 98");
		}
		else if (dwMajorVersion == 4 && dwMinorVersion == 90) {
			printf("Windows Millenium");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 00) {
			printf("Windows 2000");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 01) {
			printf("Windows XP / Windows Whistler");
		}
		else if (dwMajorVersion == 5 && dwMinorVersion == 02) {
			printf("Windows Server 2003");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 00) {
			printf("Windows Vista / Windows Longhorn");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 1) {
			printf("Windows 7");
		}
		else if (dwMajorVersion == 6 && dwMinorVersion == 2) {
			printf("Windows 8 / Windows Server 2012");
		}
		else if (dwMajorVersion == 10) {
			printf("Windows 10");
		}
		else {
			printf("Unknown");
		}
	} catch (exception e) {
		printf("Product Information is not available on this Operating System (Requires GetProductInfo)");
	}

	try {
		switch (productInfo)
		{
		case PRODUCT_BUSINESS: printf(" Business\n");
			break;
		case PRODUCT_BUSINESS_N: printf(" Business N\n");
			break;
		case PRODUCT_CLUSTER_SERVER: printf(" HPC Edition\n");
			break;
		case PRODUCT_CLUSTER_SERVER_V: printf(" Server Hyper Core V\n");
			break;
		case PRODUCT_CORE: printf(" Home\n"); // printf("  Windows 10 Home\n");
			break;
		case PRODUCT_CORE_COUNTRYSPECIFIC: printf(" Home China\n"); // printf("  Windows 10 Home China\n");
			break;
		case PRODUCT_CORE_N: printf(" Home N\n"); // printf("  Windows 10 Home N\n");
			break;
		case PRODUCT_CORE_SINGLELANGUAGE: printf(" Home Single Language\n"); // printf("  Windows 10 Home Single Language\n");
			break;
		case PRODUCT_DATACENTER_EVALUATION_SERVER: printf(" Server Datacenter (evaluation installation)\n");
			break;
		case PRODUCT_DATACENTER_SERVER: printf(" Server Datacenter (full installation)\n");
			break;
		case PRODUCT_DATACENTER_SERVER_CORE: printf(" Server Datacenter (core installation)\n");
			break;
		case PRODUCT_DATACENTER_SERVER_CORE_V: printf(" Server Datacenter without Hyper-V (core installation)\n");
			break;
		case PRODUCT_DATACENTER_SERVER_V: printf(" Server Datacenter without Hyper-V (full installation)\n");
			break;
		case PRODUCT_EDUCATION: printf(" Education\n"); // printf("  Windows 10 Education\n");
			break;
		case PRODUCT_EDUCATION_N: printf(" Education N\n"); // printf("  Windows 10 Education N\n");
			break;
		case PRODUCT_ENTERPRISE: printf(" Enterprise\n"); // printf("  Windows 10 Enterprise\n");
			break;
		case PRODUCT_ENTERPRISE_E: printf(" Enterprise E\n"); // printf("  Windows 10 Enterprise E\n");
			break;
		case PRODUCT_ENTERPRISE_EVALUATION: printf(" Enterprise Evaluation\n"); // printf("  Windows 10 Enterprise Evaluation\n");
			break;
		case PRODUCT_ENTERPRISE_N: printf(" Enterprise N\n"); // printf("  Windows 10 Enterprise N\n");
			break;
		case PRODUCT_ENTERPRISE_N_EVALUATION: printf(" Enterprise N Evaluation\n"); // printf("  Windows 10 Enterprise N Evaluation\n");
			break;
		case PRODUCT_ENTERPRISE_S: printf(" Enterprise 2015 LTSB\n"); // printf("  Windows 10 Enterprise 2015 LTSB\n");
			break;
		case PRODUCT_ENTERPRISE_S_EVALUATION: printf(" Enterprise 2015 LTSB Evaluation\n"); // printf("  Windows 10 Enterprise 2015 LTSB Evaluation\n");
			break;
		case PRODUCT_ENTERPRISE_S_N: printf(" Enterprise 2015 LTSB N\n"); // printf("  Windows 10 Enterprise 2015 LTSB N\n");
			break;
		case PRODUCT_ENTERPRISE_S_N_EVALUATION: printf(" Enterprise 2015 LTSB N Evaluation\n"); // printf("  Windows 10 Enterprise 2015 LTSB N Evaluation\n");
			break;
		case PRODUCT_ENTERPRISE_SERVER: printf(" Server Enterprise (full installation)\n");
			break;
		case PRODUCT_ENTERPRISE_SERVER_CORE: printf(" Server Enterprise (core installation)\n");
			break;
		case PRODUCT_ENTERPRISE_SERVER_CORE_V: printf(" Server Enterprise without Hyper-V (core installation)\n");
			break;
		case PRODUCT_ENTERPRISE_SERVER_IA64: printf(" Server Enterprise for Itanium-based Systems\n");
			break;
		case PRODUCT_ENTERPRISE_SERVER_V: printf(" Server Enterprise without Hyper-V (full installation)\n");
			break;
		case PRODUCT_ESSENTIALBUSINESS_SERVER_ADDL: printf(" Windows Essential Server Solution Additional\n");
			break;
		case PRODUCT_ESSENTIALBUSINESS_SERVER_ADDLSVC: printf(" Windows Essential Server Solution Additional SVC\n");
			break;
		case PRODUCT_ESSENTIALBUSINESS_SERVER_MGMT: printf(" Windows Essential Server Solution Management\n");
			break;
		case PRODUCT_ESSENTIALBUSINESS_SERVER_MGMTSVC: printf(" Windows Essential Server Solution Management SVC\n");
			break;
		case PRODUCT_HOME_BASIC: printf(" Home Basic\n");
			break;
		case PRODUCT_HOME_BASIC_E: printf(" Not supported\n");
			break;
		case PRODUCT_HOME_BASIC_N: printf(" Home Basic N\n");
			break;
		case PRODUCT_HOME_PREMIUM: printf(" Home Premium\n");
			break;
		case PRODUCT_HOME_PREMIUM_E: printf(" Not supported\n");
			break;
		case PRODUCT_HOME_PREMIUM_N: printf(" Home Premium N\n");
			break;
		case PRODUCT_HOME_PREMIUM_SERVER: printf(" Windows Home Server 2011\n");
			break;
		case PRODUCT_HOME_SERVER: printf(" Windows Storage Server 2008 R2 Essentials\n");
			break;
		case PRODUCT_HYPERV: printf(" Microsoft Hyper-V Server\n");
			break;
		case PRODUCT_IOTUAP: printf(" IoT Core\n"); // printf("  Windows 10 IoT Core\n");
			break;
		case PRODUCT_IOTUAPCOMMERCIAL: printf(" IoT Core Commercial\n"); // printf("  Windows 10 IoT Core Commercial\n");
			break;
		case PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT: printf(" Windows Essential Business Server Management Server\n");
			break;
		case PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING: printf(" Windows Essential Business Server Messaging Server\n");
			break;
		case PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY: printf(" Windows Essential Business Server Security Server\n");
			break;
		case PRODUCT_MOBILE_CORE: printf(" Mobile\n"); // printf("  Windows 10 Mobile\n");
			break;
		case PRODUCT_MOBILE_ENTERPRISE: printf(" Mobile Enterprise\n"); // printf("  Windows 10 Mobile Enterprise\n");
			break;
		case PRODUCT_MULTIPOINT_PREMIUM_SERVER: printf(" Windows MultiPoint Server Premium (full installation)\n");
			break;
		case PRODUCT_MULTIPOINT_STANDARD_SERVER: printf(" Windows MultiPoint Server Standard (full installation)\n");
			break;
		case PRODUCT_PRO_WORKSTATION: printf(" Pro for Workstations\n"); // printf("  Windows 10 Pro for Workstations\n");
			break;
		case PRODUCT_PRO_WORKSTATION_N: printf(" Pro for Workstations N\n"); // printf("  Windows 10 Pro for Workstations N\n");
			break;
		case PRODUCT_PROFESSIONAL: printf(" Pro\n"); // printf("  Windows 10 Pro\n");
			break;
		case PRODUCT_PROFESSIONAL_E: printf(" Not supported\n");
			break;
		case PRODUCT_PROFESSIONAL_N: printf(" Pro N\n"); // printf("  Windows 10 Pro N\n");
			break;
		case PRODUCT_PROFESSIONAL_WMC: printf(" Professional with Media Center\n");
			break;
		case PRODUCT_SB_SOLUTION_SERVER: printf(" Windows Small Business Server 2011 Essentials\n");
			break;
		case PRODUCT_SB_SOLUTION_SERVER_EM: printf(" Server For SB Solutions EM\n");
			break;
		case PRODUCT_SERVER_FOR_SB_SOLUTIONS: printf(" Server For SB Solutions\n");
			break;
		case PRODUCT_SERVER_FOR_SB_SOLUTIONS_EM: printf(" Server For SB Solutions EM\n");
			break;
		case PRODUCT_SERVER_FOR_SMALLBUSINESS: printf(" Windows Server 2008 for Windows Essential Server Solutions\n");
			break;
		case PRODUCT_SERVER_FOR_SMALLBUSINESS_V: printf(" Windows Server 2008 without Hyper-V for Windows Essential Server Solutions\n");
			break;
		case PRODUCT_SERVER_FOUNDATION: printf(" Server Foundation\n");
			break;
		case PRODUCT_SMALLBUSINESS_SERVER: printf(" Windows Small Business Server\n");
			break;
		case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM: printf(" Small Business Server Premium\n");
			break;
		case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM_CORE: printf(" Small Business Server Premium (core installation)\n");
			break;
		case PRODUCT_SOLUTION_EMBEDDEDSERVER: printf(" Windows MultiPoint Server\n");
			break;
		case PRODUCT_STANDARD_EVALUATION_SERVER: printf(" Server Standard (evaluation installation)\n");
			break;
		case PRODUCT_STANDARD_SERVER: printf(" Server Standard\n");
			break;
		case PRODUCT_STANDARD_SERVER_CORE: printf(" Server Standard (core installation)\n");
			break;
		case PRODUCT_STANDARD_SERVER_CORE_V: printf(" Server Standard without Hyper-V (core installation)\n");
			break;
		case PRODUCT_STANDARD_SERVER_V: printf(" Server Standard without Hyper-V\n");
			break;
		case PRODUCT_STANDARD_SERVER_SOLUTIONS: printf(" Server Solutions Premium\n");
			break;
		case PRODUCT_STANDARD_SERVER_SOLUTIONS_CORE: printf(" Server Solutions Premium (core installation)\n");
			break;
		case PRODUCT_STARTER: printf(" Starter\n");
			break;
		case PRODUCT_STARTER_E: printf(" Not supported\n");
			break;
		case PRODUCT_STARTER_N: printf(" Starter N\n");
			break;
		case PRODUCT_STORAGE_ENTERPRISE_SERVER: printf(" Storage Server Enterprise\n");
			break;
		case PRODUCT_STORAGE_ENTERPRISE_SERVER_CORE: printf(" Storage Server Enterprise (core installation)\n");
			break;
		case PRODUCT_STORAGE_EXPRESS_SERVER: printf(" Storage Server Express\n");
			break;
		case PRODUCT_STORAGE_EXPRESS_SERVER_CORE: printf(" Storage Server Express (core installation)\n");
			break;
		case PRODUCT_STORAGE_STANDARD_EVALUATION_SERVER: printf(" Storage Server Standard (evaluation installation)\n");
			break;
		case PRODUCT_STORAGE_STANDARD_SERVER: printf(" Storage Server Standard\n");
			break;
		case PRODUCT_STORAGE_STANDARD_SERVER_CORE: printf(" Storage Server Standard (core installation)\n");
			break;
		case PRODUCT_STORAGE_WORKGROUP_EVALUATION_SERVER: printf(" Storage Server Workgroup (evaluation installation)\n");
			break;
		case PRODUCT_STORAGE_WORKGROUP_SERVER: printf(" Storage Server Workgroup\n");
			break;
		case PRODUCT_STORAGE_WORKGROUP_SERVER_CORE: printf(" Storage Server Workgroup (core installation)\n");
			break;
		case PRODUCT_ULTIMATE: printf(" Ultimate\n");
			break;
		case PRODUCT_ULTIMATE_E: printf(" Not supported\n");
			break;
		case PRODUCT_ULTIMATE_N: printf(" Ultimate N\n");
			break;
		case PRODUCT_UNDEFINED: printf(" An unknown product\n");
			break;
		case PRODUCT_WEB_SERVER: printf(" Web Server (full installation)\n");
			break;
		case PRODUCT_WEB_SERVER_CORE: printf(" Web Server (core installation)\n");
			break;
		default:
			printf("  Unknown\n");
			break;
		}			
	} catch (exception e) {
        printf("Product Information is not available on this Operating System (Requires GetProductInfo)");
	}

	std::cout << "Press any key to continue..." << std::endl;
    cin.get(ch);

	return(0);
}

