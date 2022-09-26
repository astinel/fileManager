#pragma once
#include <malloc.h>
#include <stdio.h>

//���ڿ� Ŭ����
class string{
	public:
		char* str = nullptr;

		//�⺻ �����ڴ� �������� �ʱ�ȭ
		string() {
			str = cmalloc(1);
			str[0] = 0;
		}
		
		string(char c) {
			str = cmalloc(2);
			str[0] = c;
			str[1] = 0;
		}

		//�Ű� ������ ���� ���ڿ� ���� �� ����
		string(const char* str) {
			this->str = (char*)str;
			const int L = length();

			this->str = cmalloc(L);

			for (int a = 0; a < L; a++)
				this->str[a] = str[a];

			this->str[L] = 0;
		}

		//�Ҹ�� �� �޸� ����
		~string() {			
			str = nullptr;
		}

		//���ڿ� ���� ��ȯ
		int length() {
			int length = 0;

			if (str != nullptr) {
				while (str[length])
					length++;		//���� �Ѱ� ���� ���� ����
			}
			return length;
		}

		//�����ϰ� ���� ����
		char get(int index) {
			return str ? str[getIndex(index)] : 0;
		}

		//���ڿ� ��
		bool equal(string other) {
			const int L = length();			
			char* str2;

			if (L != other.length())
				return false;

			str2 = other.str;
			for (int a = 0; a < L; a++) {
				if (str[a] != str2[a])
					return false;
			}
			return true;
		}

		//�����ϰ� ���� ����
		void set(int index, char c) {
			str[getIndex(index)] = c;
		}

		//���ڿ� ����
		void copy(string origin, char* start) {
			const int L = origin.length();
			
			for (int a = 0; a <= L; a++)
				start[a] = origin.str[a];
		}

		string& add(string other) {
			const int L = length();
			char* str = cmalloc(L + other.length() + 1);

			copy(this->str, str);
			copy(other, str + L);
						
			this->str = str;

			return *this;
		}

		char scan() {
			char c = get(0);

			if (c != 0)		str++;

			return c;
		}

		string scan(char c) {
			const int L = length();
			string index;			

			for (int a = 0; a < L; a++) {
				if (c == str[a])
					index.add(a + '0');
			}

			return index;
		}

		void print(string string) {
			printf("%s\n", string.str);
		}

	private:
		int getIndex(int index) {
			const int L = length();

			if (L == 0)
				return L;
			index %= L;
			if (index < 0)
				index += L;

			return index;
		}

		char* cmalloc(int length) {
			return (char*)malloc(sizeof(char) * length);
		}
};

void print(string string) {
	printf("%s\n", string.str);
}

void print(string str, int format) {
	string form = "%";

	form.add(format);

	printf(form.str, str);
}

void print(const char* string) {
	printf("%s\n", string);
}

void print(int number) {
	printf("%d\n", number);
}

void print(char character) {
	printf("%c\n", character);
}

void print(bool boolean) {
	printf("%s\n", boolean ? "true" : "false");
}