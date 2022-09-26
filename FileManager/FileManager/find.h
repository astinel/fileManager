#include <io.h>
#include "string.h"

//파일 정보 구조체
struct Data {
	string name;			//파일명
	string type;
	long long size;
};

class Find
{
	private:
		string path;
		Data data;
		_finddata_t file;
		int find;
		bool go;

		void getType(string name);
		void getSize();
		int folderSize(string name);


	public:
		Find() {

		}

		Find(char* path);

		//생성 될때 경로 설정
		Find(string path) {
			this->path = path;
			this->path.add("/*");

			find = _findfirst(this->path.str, &file);
		}

		Data getData();
		bool get();

		bool check(string name) {
			return name.length() == name.scan('.').length();
		}
};

//데이터 얻기
bool Find::get() {
	if (find == -1 || _findnext(find, &file) != 0)
		return false;

	getType(file.name);
	getSize();	

	return true;
}

Data Find::getData() {
	return data;
}

//파일 이름에서 파일 타입 분리
void Find::getType(string name) {
	int ind = name.length();
	char c = 0;

	data.name = name.str;
	data.type = (char*)"";
	if (file.attrib == 16) {
		data.type = (char*)"F";

		return;
	}

	while (c != '.')
		c = data.name.get(--ind);	

	data.name.set(ind, 0);
	data.type = name.str + ++ind;
}

void Find::getSize() {
	data.size = file.size;
	if (data.type.equal("F"))
		data.size = folderSize(data.name);
}

int Find::folderSize(string name) {
	string path = this->path.str;
	Find find;
	int size = 0;

	if (!check(name)) {
		path.set(-1, 0);
		path.set(-1, '\\');
		path.add(name);

		find = path;
		while (find.get())
			size += find.data.size;
	}
	return size;
}