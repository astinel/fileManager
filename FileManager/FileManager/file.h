#define _CRT_SECURE_NO_WARNINGS
#include "string.h"

class File
{
	private:
		FILE* file;			//파일 포인터
		string str;			//읽은 내용
		const short length(const char* str);

		const char* path;
		bool check(char* fileName);
		//const char* name;	//파일 이름

	public:
		File(const char* fileName);
		File(const char* fileName,const char* mode);
		~File();
		void open(const char* fileName);
		void close();
		FILE* getFile();
		const char* getName();
		bool read();

		int lineCount() {
			int count = 0;
			int cou = 0;
			char c;			

			for (; fscanf(file, "%c", &c) > 0; cou++) {
				if (c == '\n' && c != 0) {
					count++;
					cou = 0;
				}					
			}
			if (cou)		count++;

			return count;
		}

		string getStr() {
			return str;
		}

		char* read(char* str);
		
		void write(const char* str);
		void erase();
		void setPath(char* path);
		void find();
		void find(const char* fileName);
};

//파일 append 모드로 열기
File::File(const char* fileName) {
	open(fileName);
}

//파일 모드 선택해서 열기
File::File(const char* fileName,const char* mode) {
	file = fopen(fileName, mode);
	//name = fileName;
}

void File::open(const char* fileName) {
	file = fopen(fileName, "a+");
}

//파일 반환
FILE* File::getFile() {
	return file;
}

////파일 이름 반환
//const char* File::getName()
//{
//	return name;
//}

bool File::read() {
	short index = 0;
	char c;
	str = "";

	for (; fscanf(file, "%c", &c) > 0; index++) {
		str.add(c);
		if (c == '\n')
			break;
	}	

	return index > 0;
}

//데이터의 길이 반환
const short File::length(const char* str) {
	short length = 0;
	char c;

	do {
		c = str[length++];
	} while (c != 0);

	return length;
}


//파일 데이터 한행 읽기(X)
char* File::read(char* str) {	
	const short L = 30;
	bool go;

	go = fgets(str, L, file);
	if (!go)	return NULL;
	return str;
}

void File::write(const char* str)
{
	/*file = fopen(name, "a+");

	fprintf(file, str);
	fprintf(file, "\n");

	fclose(file);*/
}

void File::erase() {
	/*file = fopen(name,"w");

	fclose(file);*/
}

void File::setPath(char* path) {	
	//this->path = path;
}

void File::find(const char* fileName) {

}

bool File::check(char* fileName) {
	const char zip[] = "zip";
	int ind;
	char c = 1;
	
	for (ind = 0; c > 0 ; ind++) {
		c = fileName[ind];
	}
	ind--;
	for (int a = ind - 3, b = 0; a < ind; a++) {
		c = fileName[a];
		if (c != zip[b++]) {
			return false;
		}
	}
	return true;
}

void File::close() {
	if (file != NULL)
		fclose(file);
}

File::~File() {
	close();
}

/*
bool File::read(const short length) {
	this->str = new char[length];

	return fgets(str, length, file);
 }

//입력 받아서 줄 이어서 출력(사용 X)
void File::write() {
	char str[10];

	file = fopen(name, "a+");

	fgets(str, 10, stdin);

	fclose(file);
}*/