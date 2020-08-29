#pragma once

#include <Windows.h>

/**
 * Hooks a specified function
 *
 * @param address	The address of the original function
 * @param length	The length of the function prologue
 * @param target	The target function
 *
 * @return			A pointer to the original function
 */
void* memory(DWORD address, int length, DWORD target);