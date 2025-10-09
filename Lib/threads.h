#pragma once

#include <windows.h>
#include "utils.h"

DWORD WINAPI min_max(LPVOID);
DWORD WINAPI average(LPVOID);

void min_max_thread(ThreadData*);
void average_thread(ThreadData*);
