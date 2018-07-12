// http://www.cnblogs.com/liangliangh/p/4219879.html
#include <cstdio>

// IF_
// ͨ��Ϊ�գ�����ƥ�������������ܺõĵ����ֶΣ������� bool ������ν�ˣ�
template<bool Cond, class Then, class Else>
class IF_  {};
template<class Then, class Else>
class IF_<true, Then, Else> { public: typedef Then reType; };
template<class Then, class Else>
class IF_<false, Then, Else> { public: typedef Else reType; };

// WHILE_
// ����Ҫ�� Condition ����ֵ ret��Statement ������ Next
template<template<typename> class Condition, class Statement>
class WHILE_
{
	template<class Stat_>
	class STOP { public: typedef Stat_ reType; };
public:
	typedef typename
		IF_<Condition<Statement>::ret,
		WHILE_<Condition, typename Statement::Next>,
		STOP<Statement>>::reType::reType
	reType;
};
// WHILE_ ���� 1^e + 2^e + ... + n^e
template<int n, int e>
class SumE
{
	template<int i_, int e_>
	class PowE { public: enum { ret = i_ * PowE<i_, e_ - 1>::ret }; };
	template<int i_>
	class PowE<i_, 0> { public: enum { ret = 1 }; };
	// ���� i^e��Ƕ����ʹ���ܹ�����Ƕ��ģ��Ԫ������private ���ʿ�������ʵ��ϸ��
	template<int i_>
	class Pow { public: enum { ret = PowE<i_, e>::ret }; };
	template<typename Stat_>
	class Cond { public: enum { ret = (Stat_::ri <= n) }; };
	template<int i_, int sum_>
	class Stat
	{
	public:
		typedef Stat<i_ + 1, sum_ + Pow<i_>::ret> Next; 
		enum { ri = i_, ret = sum_ };
	};	
public:
	enum { ret = WHILE_<Cond, Stat<1, 0>>::reType::ret };
};
// ģ��汾
template<int a, int b>
class lcm_T
{
    template<typename Stat_>
    class Cond { public: enum{ ret = (Stat_::div != 0) }; };
    template<int a_, int b_>
    class Stat { public: typedef Stat<b_, a_ % b_> Next; enum{ div = a_ % b_, ret = b_ }; };
    static const int gcd = WHILE_<Cond, Stat<a, b>>::reType::ret;
public:
    static const int ret = a * b / gcd;
};
// �ݹ�ģ��汾
template<int a, int b>
class lcm_T_r
{
    template<int a_, int b_> class gcd { public: enum { ret = gcd<b_, a_ % b_>::ret }; };
    template<int a_> class gcd<a_, 0> { public: enum { ret = a_ }; };
public:
    static const int ret = a * b / gcd<a, b>::ret;
};

int main()
{
#define out(x) printf(#x " = %lld\n", static_cast<long long>(x))
	// IF_
	int const len = 4;
	typedef
		IF_<sizeof(char) == len, char,
		IF_<sizeof(short) == len, short,
		IF_<sizeof(int) == len, int,
		IF_<sizeof(long) == len, long,
		IF_<sizeof(long long) == len, long long,
		void>::reType>::reType>::reType>::reType>::reType
	int_len; // ����һ��ָ���ֽ���������
	out(sizeof(int_len));
	
	// WHILE_
	// Ҫ��һ�����Ų��У���Ϊ���Żᱻ���������ָ���
	out((SumE<10, 5>::ret));
	out((lcm_T<100, 36>::ret));
	out((lcm_T_r<100,72>::ret));
	
	printf("Enter a 'q' to quit: ");
	while(getchar() != 'q');
	return 0;
}

