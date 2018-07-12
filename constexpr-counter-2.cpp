// https://zhuanlan.zhihu.com/p/24928414

template<int N>
struct Flag
{
	friend int constexpr flag(Flag<N>);
};

template<int N>
struct Writer
{
	friend int constexpr flag(Flag<N>) { return 0; }
};

template<int N=0>
int constexpr reader(float, Flag<N> = {})
{
	return N;
}

template<int N=0, int = flag(Flag<N>{})>
int constexpr reader(int, Flag<N> = {}, int value = reader(0, Flag<N+1>{}))
{
	return value;
}

template<int N = reader(0), int = sizeof(Writer<N>)>
int constexpr next()
{
	return N;
}

int main()
{
#define StaticAssert(x) static_assert(!!(x), #x) 
	int constexpr a = next();
	int constexpr b = next();
	int constexpr c = next();
	StaticAssert((a == 0) && (b == 1) && (c == 2));
#undef StaticAssert	
}
