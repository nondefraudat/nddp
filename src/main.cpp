#include <iostream>

#include "nddp.hpp"

#ifndef _WIN32 // For Linux

int main(const int argumentCount, const char* arguments[]) {
	return DocumentPackager::execute(argumentCount, ansiArguments);;
}

#else // For Windows

#include <string>
#include <Windows.h>

char** recreateAsAnsi(const int count, const wchar_t* utf16[]) noexcept;
void release(const int count, char** targets) noexcept;
char* ansi(const wchar_t* utf16) noexcept;

int wmain(const int argumentCount, const wchar_t* arguments[]) {
	char** ansiArguments = recreateAsAnsi(argumentCount, arguments);
	int exitCode = DocumentPackager::execute(argumentCount, ansiArguments);
	release(argumentCount, ansiArguments);
	return exitCode;
}

char** recreateAsAnsi(const int count, const wchar_t* utf16[]) noexcept {
	char** target = new char*[count];
	for (int i = 0; i < count; i++) {
		target[i] = ansi(utf16[i]);
	}
	return target;
}

void release(const int count, char** targets) noexcept {
	for (int i = 0; i < count; i++) {
		delete[] targets[i];
	}
	delete[] targets;
}

char* ansi(const wchar_t* utf16) noexcept {
	const int targetSize = static_cast<int>(wcslen(utf16)) + 1; // + 1 for '\0'
	char* target = new char[targetSize];
	WideCharToMultiByte(CP_OEMCP, NULL, utf16, -1, target, targetSize, nullptr, nullptr);
	return target;
}

#endif