#include <cstdio>

#define o(x) printf("%20s : %-2zd", #x, sizeof(x))
#define n printf("\n")

int main()
{
	o(char);o(unsigned char); n;
	o(bool); o(wchar_t); n;
	o(short); o(unsigned short); n;
	o(int); o(unsigned int); n;
	o(long); o(unsigned long); n;
	o(long long); o(unsigned long long); n;
	o(ptrdiff_t); o(size_t); n;
	o(intptr_t); o(uintptr_t); n;
	o(float); o(double); o(long double); n;
	printf("Enter a 'q' to quit: ");
	while(getchar() != 'q');
	return 0;
}
