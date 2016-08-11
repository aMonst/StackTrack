#pragma once

#include <windows.h>
#include <tchar.h>
#include <Dbghelp.h>
#include <stdio.h>
#include <stddef.h>

#pragma comment(lib, "Dbghelp.lib")

void InitTrack();
void StackTrack();
void UninitTrack();
extern HANDLE g_hHandle;
extern HANDLE g_hThread;
extern CONTEXT g_context;

#define OPEN_STACK_TRACK\
 HANDLE hThread = GetCurrentThread();\
GetThreadContext(hThread, &g_context);\
__asm{call $ + 5}\
__asm{pop eax}\
__asm{mov g_context.Eip, eax}\
__asm{mov g_context.Ebp, ebp}\
__asm{mov g_context.Esp, esp}\
InitTrack();\
StackTrack();\
UninitTrack();
