// get_file_time.cpp : Defines the entry point for the console application.
//
/**
使用FILETIME、SYSTEMTIME
GetFileTime、FileTimeToSystemTime
_snwprintf_s

2013.4.5 test
*/
#include <stdio.h>
#include <tchar.h>

#include "utility\utility.h"
#include <iostream>
#include <windows.h>
#include <string>

void printData(const std::wstring& data_name, const SYSTEMTIME& sys_time)
{
	wchar_t wchBuf[ MAX_PATH ];
	::memset(wchBuf, 0, sizeof(wchBuf));
	::_snwprintf_s(wchBuf, 
		_countof(wchBuf), 
		MAX_PATH-1, 
		L"%4d年%2d月%2d日，%2d:%2d:%2d，%2d",
		sys_time.wYear,
		sys_time.wMonth,
		sys_time.wDay,
		sys_time.wHour,
		sys_time.wMinute,
		sys_time.wSecond,
		sys_time.wMilliseconds);
	std::wstring time_print_w = wchBuf;
	std::cout << utility::wstr2str(data_name, CP_ACP) << " : " << utility::wstr2str(time_print_w, CP_ACP) << std::endl;
}

bool CmpFileTime(const FILETIME& first, const FILETIME& second)
{
	int hight_test = first.dwHighDateTime - second.dwHighDateTime;
	if (hight_test != 0)
	{
		return hight_test > 0 ? true : false;
	}
	int low_test = first.dwLowDateTime - second.dwLowDateTime;
	return low_test > 0 ? true : false;
}

void getfile()
{
	//SYSTEMTIME sys_time;
	//::GetSystemTime(&sys_time);
	//FILETIME file_time_test;
	//::SystemTimeToFileTime(&sys_time, &file_time_test);
	//sys_time.wMilliseconds += 1;
	//FILETIME file_time_test_2;
	//::SystemTimeToFileTime(&sys_time, &file_time_test_2);
	//
	//SYSTEMTIME local_time;
	//::GetLocalTime(&local_time);

	std::wstring file_path = L"c:\\jsoncppfastwrite";
	HANDLE hFile = ::CreateFile(file_path.c_str(),
		GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL);

	FILETIME file_create_time;
	FILETIME file_access_time;
	FILETIME file_write_time;
	::GetFileTime(hFile, &file_create_time, &file_access_time, &file_write_time);
	
	SYSTEMTIME file_create_sys_time;
	::FileTimeToSystemTime(&file_create_time, &file_create_sys_time);
	SYSTEMTIME file_access_sys_time;
	::FileTimeToSystemTime(&file_access_time, &file_access_sys_time);
	SYSTEMTIME file_write_sys_time;
	::FileTimeToSystemTime(&file_write_time, &file_write_sys_time);

	CmpFileTime(file_create_time, file_access_time);

	std::wcout << std::endl;
	printData(L"file create time", file_create_sys_time);
	printData(L"file access time", file_access_sys_time);	
	printData(L"file write time", file_write_sys_time);
}

int _tmain(int argc, _TCHAR* argv[])
{
	getfile();
	::system("pause");
	return 0;
}

