#include "Track.h"
HANDLE g_hHandle = NULL;
HANDLE g_hThread = NULL;
CONTEXT g_context = { CONTEXT_FULL };

void InitTrack()
{
	g_hHandle = GetCurrentProcess();

	SymInitialize(g_hHandle, NULL, TRUE);
}

void StackTrack()
{
	g_hThread = GetCurrentThread();
	STACKFRAME sf = { 0 };

	sf.AddrPC.Offset = g_context.Eip;
	sf.AddrPC.Mode = AddrModeFlat;
	
	sf.AddrFrame.Offset = g_context.Ebp;
	sf.AddrFrame.Mode = AddrModeFlat;
	
	sf.AddrStack.Offset = g_context.Esp;
	sf.AddrStack.Mode = AddrModeFlat;

	typedef struct tag_SYMBOL_INFO
	{
		IMAGEHLP_SYMBOL symInfo;
		TCHAR szBuffer[MAX_PATH];
	} SYMBOL_INFO, *LPSYMBOL_INFO;

	DWORD dwDisplament = 0;
	SYMBOL_INFO stack_info = { 0 };
	PIMAGEHLP_SYMBOL pSym = (PIMAGEHLP_SYMBOL)&stack_info;
	pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
	pSym->MaxNameLength = sizeof(SYMBOL_INFO) - offsetof(SYMBOL_INFO, symInfo.Name);
	IMAGEHLP_LINE ImageLine = { 0 };
	ImageLine.SizeOfStruct = sizeof(IMAGEHLP_LINE);

	while (StackWalk(IMAGE_FILE_MACHINE_I386, g_hHandle, g_hThread, &sf, &g_context, NULL, SymFunctionTableAccess, SymGetModuleBase, NULL))
	{
		SymGetSymFromAddr(g_hHandle, sf.AddrPC.Offset, &dwDisplament, pSym);
		SymGetLineFromAddr(g_hHandle, sf.AddrPC.Offset, &dwDisplament, &ImageLine);
		printf("当前调用函数 : %08x+%s(FILE[%s]LINE[%d])\n", pSym->Address, pSym->Name, ImageLine.FileName, ImageLine.LineNumber);
	}
	
}

void UninitTrack()
{
	HANDLE hProcess = GetCurrentProcess();
	SymCleanup(g_hHandle);
}