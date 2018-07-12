#include <cstdio>

class A
{
public:
	A (int) {}
	friend void f(A);
};

void g(A);

class B
{
	friend void f(A) { printf("hello, world!\n"); }
	class C
	{
		friend void g(A) { printf("!dlrow olleh\n"); }
	};
};

int main(int, char**)
{
	A a(0);
	f(a);
	g(1);
}