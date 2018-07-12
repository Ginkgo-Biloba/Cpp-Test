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
	bool B = noexcept(flag(0)), // ��� flag(0) �ǳ������ʽ���� B ��Ϊ true��������Ϊ false
	int = sizeof(DependentWriter<B>)> // ��ʽ��ʵ���� dependent_writer<B> (sizeof ��Ҫ��������������)
int constexpr f() { return B; }

int main()
{
	// #define f() __LINE__ // ��������
#define StaticAssert(x) static_assert(!!(x), #x) 
	int constexpr a = f();
	int constexpr b = f();
	StaticAssert((a == 0) && (b == 1));
#undef StaticAssert
}
