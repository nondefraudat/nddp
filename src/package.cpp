#include "package.hpp"

#include <filesystem>
#include <fstream>

using namespace std;

Package::Package(const string& packagePath) noexcept {
	__textBlocks = __unpack(packagePath);
	__markers = __extractMarkers(__textBlocks);
}

vector<string> Package::__unpack(const string& packagePath) noexcept {
	const filesystem::path& packageAbsolutePath = absolute(filesystem::path(packagePath));
	const string& packageName = packageAbsolutePath.stem().string();
	const string& targetDirectoryPath = "./.temp/unpack/" + packageName;
	const string& consoleCommand = "unzip " + packagePath + " -d " + targetDirectoryPath;
	if (system(consoleCommand.c_str()) != 0) {
		return vector<string>();
	}
	const string& entityPath = targetDirectoryPath + "/entity";
	
}

set<string> Package::__extractMarkers(const vector<string>& textBlocks) noexcept {
	set<string> markers;
	for (const string& textBlock : textBlocks) {
		markers.merge(__extractMarkers(textBlock));
	}
	return markers;
}

set<string> Package::__extractMarkers(const string& textBlock) noexcept {
	set<string> markers;
	size_t i = 0;
	while (i < textBlock.size()) {
		if (textBlock[i] == __escapeSymbol() 
				or textBlock[i] != __markerSymbol()) {
			i++; continue;
		}
		markers.insert(__extractMarker(textBlock, i));
	}
	return markers;
}

string Package::__extractMarker(const string& textBlock, size_t& i) noexcept {
	const int markerBegin = i;
	int markerLength = 0;
	while (i < textBlock.size() and textBlock[i] != __markerSymbol()) {
		i++; markerLength++;
	}
	return textBlock.substr(markerBegin, markerLength);
}
