#include <cstdio>
#include <cstdlib>

int main()
{
	char str[20];
	char* pstr = static_cast<char*>(malloc(sizeof(char) * 16));
	printf("str = %s\npstr = %s\n", str, pstr);
	free(pstr);
	// 假设路径为
	// char const* path = "C:\\";
	// printf("path = %s\n", path);
	return 0;
}
