#include <locale> 
#include <iostream> 
#include <cstring> 

#define o(x) std::cout << #x " : " << x << std::endl

int main() 
{ 
	o(std::strcoll("ä", "z"));
	std::locale::global(std::locale("German")); 
	o(std::strcoll("ä", "z"));
	printf("Enter a 'q' to quit: ");
	while(getchar() != 'q');
	return 0;
} 