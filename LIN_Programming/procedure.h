#pragma once

#include "stdafx.h"

#include <vector>
#include <iterator>

#include  <stdio.h>
#include  <string.h>
#include  <commctrl.h>
#include  <conio.h>
#include  <math.h>
#include  <vector>
#include  <iterator>

#include "CTest_State.h"


DWORD WINAPI Thread_MainCmd_Test	(LPVOID temp);
DWORD WINAPI Thread_waitTestSignal	(LPVOID temp);
DWORD WINAPI Thread_saveData		(LPVOID temp);

int ThreadFunction_MainCmd_Test		(LPVOID pView);
int set_test_handler_thread			(unsigned int state);

void system_initialize				(CTest_State *ts);
/*
int  test_procedure_main_process	(CTest_State *ts);
void test_procedure_start_process	(CTest_State *ts); 
void test_procedure_end_process		(CTest_State *ts); 

void system_shutdown	(CTest_State *ts);

*/