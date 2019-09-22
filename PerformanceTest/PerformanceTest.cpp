#include "pch.h"
#include "Lock.h"
#include <assert.h>
#include <mutex>
#include <utility>
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
class Base
{
public:
	void Func();
	int a;
};

class Derived : virtual public Base
{
public:
	void Func2();
	int b;
};

void Base::Func()
{
	std::cout << "Func\n";
}

void Derived::Func2()
{
	std::cout << "Func2\n";
}

void MyStrcpy(char* dest, char* src)
{
	while (*dest++ = *src++);
}

void MyStrcat(char* dest, char* src)
{
	while (1)
	{
		if (*dest++ == '\0')
		{
			dest--;
			break;
		}
	}

	while (*dest++ = *src++);
}

int strCmp(const char* s1, const char* s2)
{
	while (*s1 && (*s1 == *s2))
	{
		// 왜 위에서 하지 않느냐?
		// ++에 대한 평가가 위 식의 평가 다음에 모두 반영될지, 아닐지 알 수 없기에
		s1++;
		s2++;
	}
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}


class Vector
{
public:
	Vector(int a, int b)
	{
		mA = a;
		mB = b;
	}

	int mA;
	int mB;
};

int main() {
	locktest::StartInterlockedAdd(4);
	locktest::StartSRWLock(4);

	/*Vector v(10, 20);
	Vector* pV = &v;

	std::unique_ptr<Vector> uV = std::make_unique<Vector>(pV);
	std::unique_ptr<Vector> uV2 = std::make_unique<Vector>(pV);
*/
	//char src[10] = "efgh";
	//char dest[10]= "efgh";

	////MyStrcpy(dest, src);
	////MyStrcat(dest, src);
	//auto result = strcmp(src, dest);

	//// 파일 읽기 준비
	//std::ifstream in("test.txt");
	//std::string s;

	//if (in.is_open()) {
	//	// 위치 지정자를 파일 끝으로 옮긴다.
	//	in.seekg(0, std::ios::end);

	//	// 그리고 그 위치를 읽는다. (파일의 크기)
	//	int size = in.tellg();

	//	// 그 크기의 문자열을 할당한다.
	//	s.resize(size);

	//	// 위치 지정자를 다시 파일 맨 앞으로 옮긴다.
	//	in.seekg(0, std::ios::beg);

	//	// 파일 전체 내용을 읽어서 문자열에 저장한다.
	//	in.read(&s[0], size);
	//	std::cout << s << std::endl;
	//}
	//else {
	//	std::cout << "파일을 찾을 수 없습니다!" << std::endl;
	//}

	return 0;
}