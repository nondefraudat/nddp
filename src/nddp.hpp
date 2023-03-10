#pragma once

#include <vector>
#include <set>
#include <string>

class DocumentPackager {
public:
	static int execute(const int arumentCount, char* arguments[]) noexcept;
	
	static void dissectDocx(const char* path) noexcept;

private:
	DocumentPackager() = default;

	static std::vector<std::string> extractTexts(std::string& xml) noexcept;
	static std::string extractText(char* it, const char* target) noexcept;
	static bool contains(char* it, const char* target) noexcept;
};