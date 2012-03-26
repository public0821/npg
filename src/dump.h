#ifndef DUMP_H
#define DUMP_H
#include <Windows.h>
#include <DbgHelp.h>
#include <tchar.h>
#pragma comment(lib, "dbghelp.lib")  

void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)
{
	HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;

	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);

	CloseHandle(hDumpFile);
}

LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{	
	CreateDumpFile(_T("npg.dmp"), pException); 

	FatalAppExit(-1,  _T("Unhandled Exception"));

	return EXCEPTION_EXECUTE_HANDLER;
}
#endif
