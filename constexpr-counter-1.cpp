// https://zhuanlan.zhihu.com/p/24910829

template <int N>
struct Flag
{
	friend int constexpr adl_flag(Flag<N>);
};

template<int N>
struct Writer
{
	friend int constexpr adl_flag(Flag<N>) { return N; }
	static int constexpr value = N;
};

template<int N, int = adl_flag(Flag<N>{})>
int constexpr reader(int, Flag<N>)
{
	return N;
}

template<int N>
int constexpr reader(float, Flag<N>, int R = reader(0, Flag<N - 1>{}))
{
	return R;
}

int constexpr reader(float, Flag<0>)
{
	return 0;
}

template<int N = 1>
int constexpr next(int R = Writer<reader(0, Flag<32>{}) + N>::value)
{
	return R;
}

int main()
{
#define StaticAssert(x) static_assert(!!(x), #x) 
	int constexpr a = next();
	int constexpr b = next();
	int constexpr c = next();
	StaticAssert((a == 1) && (b == 2) && (c == 3));
#undef StaticAssert
}
