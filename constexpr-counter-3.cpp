// https://segmentfault.com/n/1330000008559854

template<class T, int Init = 0>
struct ConstExprCounter
{
	template<int N>
	struct Cnt
	{
		friend int constexpr is_instantialized(Cnt<N>);
		static int constexpr value = N;
	};
	
	template<int N>
	struct InstantializedCnt
	{
		friend int constexpr is_instantialized(Cnt<N>)
		{ return N; }
		static int constexpr value = N;
	};
	
	// increse ÿ�ε��õõ���ֵ����һ��������Ĭ�ϲ�������Ϊ�˱�֤������ÿ�ζ�����ֵ
	// ���д�ں������ڣ������������ֵ��ֱ�ӷ����ϴ���ֵ���
	// ��Ϊ���� constexpr ���������壬ÿ�ζ�Ӧ�÷���ͬ���Ľ��
	template<int N, int = is_instantialized(Cnt<N>{})>
	static int constexpr increse(int, Cnt<N>, int cnt = increse(N + 1, Cnt<N + 1>{}))
	{ return cnt; }
	
	template<int N>
	static int constexpr increse(float, Cnt<N>, int cnt = InstantializedCnt<N>::value)
	{ return cnt; }
	
	// ���Ӽ���
	template<int N = Init>
	static int constexpr count_up(int cnt = increse(N, Cnt<N>{}))
	{ return cnt; }
	
	template<int N, int = is_instantialized(Cnt<N>{})>
	static int constexpr _curCnt(int, Cnt<N>, int cur = _curCnt(N + 1, Cnt<N + 1>{}))
	{ return cur; }
	
	template<int N>
	static int constexpr _curCnt(float, Cnt<N>)
	{ return Cnt<N - 1>::value; }
	
	// ��ѯ����
	template<int N = Init>
	static int constexpr current_count(int cur = _curCnt(N, Cnt<N>{}))
	{ return cur; }
};


int main()
{
#define StaticAssert(x) static_assert(!!(x), #x)
	// 1
	using Counter1 = ConstExprCounter<class Cnt1>;
	StaticAssert(Counter1::current_count() == -1);
	
	int constexpr a = Counter1::count_up(); // 0
	int constexpr b = Counter1::count_up(); // 1
	int constexpr c = Counter1::count_up(); // 2

	// 2
	using Counter2 = ConstExprCounter<class Cnt2, 1>;
	StaticAssert(Counter2::current_count() == 0);
	
	int constexpr i = Counter2::count_up(); // 1
	int constexpr j = Counter2::count_up(); // 2
	int constexpr k = Counter2::count_up(); // 3
	int constexpr l = Counter2::count_up(); // 4
	int constexpr m = Counter2::count_up(); // 5

	// StaticAssert 1
	StaticAssert((a == 0) && (b == 1) && (c == 2));
	StaticAssert(Counter1::current_count() == 2);
	// StaticAssert 2
	StaticAssert((i == 1) && (j == 2) && (k == 3) && (l == 4) && (m == 5));
	StaticAssert(Counter2::current_count() == 5);
	
	// ��ѯ���������
	int constexpr d = Counter1::count_up(); // 3
	int constexpr n = Counter2::count_up(); // 6
	StaticAssert(d == 3);
	StaticAssert(n == 6);
	StaticAssert(Counter1::current_count() == 3);
	// 2 �β�ѯ
	StaticAssert(Counter2::current_count() == 6);
	StaticAssert(Counter2::current_count() == 6);
	
#undef StaticAssert	
}
