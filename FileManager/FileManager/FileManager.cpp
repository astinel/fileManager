#include "file.h"
#include "find.h"
#include "string.h"

#define PATH "path.txt"
#define LIST "fileList.txt"
#define TYPE "type.txt"
#define FORMAT "%-40s\t%-4s\t%10I64d\tByte\n"

string* types = nullptr;
int typeCount;
long long size;
string name;
string type;
Data data;

void setData(Data data) {
	name = data.name;
	size = data.size;
	type = data.type;
}

bool check() {
	for (int a = 0; a < typeCount; a++)
		if (type.equal(types[a]))
			return true;	
	return false;
}

void cut(string str) {
	if (str.get(-1) == '\n')
		str.set(-1, 0);
}

void setFilter() {
	File type = TYPE;
	typeCount = type.lineCount();

	types = (string*)malloc(sizeof(string) * typeCount);
	type.close();
	type.open(TYPE);
	
	if (types == NULL)	return;

	for (int a = 0; a < typeCount; a++) {
		type.read();
		types[a] = type.getStr();
		cut(types[a]);
	}
	type.close();
}

int main() {
	Find find;
	File file = PATH;
	File list(LIST, "w");
	string path;
		
	setFilter();			//필터 설정

	while (file.read()) {
		path = file.getStr();
		printf("\n%s\n\n", path.str);

		cut(path);
		find = path;

		while (find.get()) {
			setData(find.getData());
			if (!check())	continue;
			printf(FORMAT, name.str, type.str, size);
			fprintf(list.getFile(), FORMAT, name.str, type.str, size);
		}
		fprintf(list.getFile(), "\n");
	}

	file.close();
	list.close();

	print("\n\n종료");
	int a = getchar();	

	return 0;
}