#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>

class Package {
public:
	explicit Package(const std::string& packagePath) noexcept;

	std::vector<std::string> textBlocks() const noexcept { return __textBlocks; };
	std::set<std::string> markers() const noexcept { return __markers; };

private:
	std::vector<std::string> __textBlocks;
	std::set<std::string> __markers;

	static std::vector<std::string> __unpack(const std::string& packagePath) noexcept;

	static std::set<std::string> __extractMarkers(const std::vector<std::string>& textBlocks) noexcept;
	static std::set<std::string> __extractMarkers(const std::string& textBlock) noexcept;
	static std::string __extractMarker(const std::string& textBlock, size_t& i) noexcept;

	inline static char __escapeSymbol() noexcept { return '/'; };
	inline static char __markerSymbol() noexcept { return '#'; };
};
