#include "nddp.hpp"

#include <zip.hpp>

using namespace std;

int DocumentPackager::execute(const int arumentCount, char* arguments[]) noexcept {
	dissectDocx("foo.zip");
	return 0;
}

void DocumentPackager::dissectDocx(const char* path) noexcept {
	Zip zip(path);
	string documentContent = zip.entry("word/document.xml");
	vector<string> texts = extractTexts(documentContent);
	zip.insert(documentContent);
}

vector<string> DocumentPackager::extractTexts(string& xml) noexcept {
	vector<string> target;
	char* it = xml.data();
	char* in = it;
	while (*it) {
		// here
		if (contains(it, "<w:t>")) {
			for (const char digit : to_string(target.size())) {
				*in++ = digit;
			}
			target.push_back(extractText(it, "</w:t>"));
		}
		it += strlen("<w:t>");
		it += strlen("</w:t>");
	}
	*in = '\0';
	return target;
}

string DocumentPackager::extractText(char* it, const char* target) noexcept {
	string buffer;
	while (!contains(it, target)) {
		buffer.push_back(*it++);
	}
	return buffer;
}

bool DocumentPackager::contains(char* it, const char* target) noexcept {
	for (int i = 0; target[i]; i++) {
		if (it[i] != target[i]) {
			return false;
		}
	}
	return true;
}

