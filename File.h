#include <cstdio>
#include <string>
using std::string;

inline string readFile(const char *const file) {
	FILE *fp = fopen(file, "rb+");
	string str = "";
	do {
		unsigned int ch = fgetc(fp);
		str.push_back(ch);
	} while(!feof(fp));
	fclose(fp);
	return str;
}

inline void writeFile(const char *const file, const string &str) {
	FILE *fp = fopen(file, "wb+");
	for(auto it = str.begin(); it != str.end(); ++it) {
        if(*it != EOF)  fputc(*it, fp);
	}
	fclose(fp);
}
