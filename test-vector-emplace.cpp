#include <cstdio>
#include <vector>

#if defined _MSC_VER
	#define Compiler "MSVC" // #_MSC_VER // fix it
#elif defined __GNUC__
	#define Compiler "GNUC " __VERSION__
#else 
	#define Compiler "Unknow Compiler"
#endif

class X
{
public:
	int val;
	// ctor
	X(int _val, bool trigger = false) : val(_val)
	{
		printf("ctor: %d (%p)\n", _val, static_cast<void*>(this));
		if (trigger) throw -1;
	}
	// copy ctor
	X(X const& rhs) : val(rhs.val)
	{ printf ("copy ctor: %d (%p)\n", rhs.val, static_cast<void*>(this)); }
	// move ctor, -128 for mark
	X(X&& rhs) : val(rhs.val)
	{
		printf("move ctor: %d (%p) <- (%p)\n", this->val, \
			static_cast<void*>(this), static_cast<void*>(&rhs));
		rhs.val = -3;
	}
	// assign
	X& operator=(X const& rhs)
	{
		printf("assign: %d (%p) <= %d (%p)\n", \
			this->val, static_cast<void*>(this), rhs.val, static_cast<void const*>(&rhs));
		this->val = rhs.val;
		return *this;
	}
	// move assign, -129 for mark
	X& operator=(X&& rhs)
	{
		printf("move assign: %d (%p) <= %d (%p)\n", \
			this->val, static_cast<void*>(this), rhs.val, static_cast<void*>(&rhs));
		this->val = rhs.val; rhs.val = -5;
		return *this;
	}
	// dtor;
	~X() { printf("dtor: %d (%p)\n", this->val, static_cast<void*>(this)); }
};

int main(int argc, char**)
{
	printf("Compiler: %s\n", Compiler);
	printf("\n----- begin -----\n");
	// prepare
	std::vector<X> vx;
	vx.reserve(4u);
	vx.emplace_back(1); vx.emplace_back(2); vx.emplace_back(3);
	// trigger exception
	bool trigger = (argc > 1);
	try { vx.emplace(vx.begin() + 2u, 4, trigger); }
	catch (int e) { printf("----- exception (%d) -----\n", e); }
	// output
	printf("\n----- output -----\n");
	for (unsigned int i = 0u; i != 4u; i++)
		printf("output: %d\n", vx[i].val);
	// end
	printf("\n----- end -----\n");
	printf("Enter a 'q' to quit: ");
	while(getchar() != 'q');
	return 0;
}