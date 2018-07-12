// https://zhuanlan.zhihu.com/p/24835482

int constexpr flag(int);

template<class Tag>
struct Writer
{
	friend int constexpr flag(Tag) { return 0; }
};

template<bool B, class Tag = int>
struct DependentWriter : Writer<Tag> {};

template<
	bool B = noexcept(flag(0)), // 如果 flag(0) 是常量表达式，则将 B 设为 true，否则设为 false
	int = sizeof(DependentWriter<B>)> // 隐式地实例化 dependent_writer<B> (sizeof 需要定义完整的类型)
int constexpr f() { return B; }

int main()
{
	// #define f() __LINE__ // 哈哈哈哈
#define StaticAssert(x) static_assert(!!(x), #x) 
	int constexpr a = f();
	int constexpr b = f();
	StaticAssert((a == 0) && (b == 1));
#undef StaticAssert
}
