#include <cstdio>
#include <typeinfo>


template<class Base, int D>
class Discriminator : public Base {};

/* 直接从 4 个 Sets 继承是不行的
 * 否则当使用 Breader<> 时，所有模板参数都相同
 * 也就意味着 Breader 从 4 个完全相同的基类继承 */
template<class Sets1, class Sets2, class Sets3, class Sets4>
class Selector :
	public Discriminator<Sets1, 1>,
	public Discriminator<Sets2, 2>,
	public Discriminator<Sets3, 3>,
	public Discriminator<Sets4, 4>
{};


class DefaultSetsBase
{
public:
	typedef char Tp1;
	typedef char Tp2;
	typedef char Tp3;
	typedef char Tp4;
};
/* 必须有这个间接层，避免 AltSet<n> 的 二义性 */
class DefaultSets : virtual public DefaultSetsBase {};


template<class Tp>
class AltSet1 : virtual public DefaultSets
{
public: typedef Tp Tp1;
};

template<class Tp>
class AltSet2 : virtual public DefaultSets
{
public: typedef Tp Tp2;
};

template<class Tp>
class AltSet3 : virtual public DefaultSets
{
public: typedef Tp Tp3;
};

template<class Tp>
class AltSet4 : virtual public DefaultSets
{
public: typedef Tp Tp4;
};


template<
	class Args1 = DefaultSets,
	class Args2 = DefaultSets,
	class Args3 = DefaultSets,
	class Args4 = DefaultSets>
class Breader
{
public:
	typedef Selector<Args1, Args2, Args3, Args4> Args;

	void output()
	{
		printf("Breader<%s, %s, %s, %s>\n",
			typeid(typename Args::Tp1).name(), 
			typeid(typename Args::Tp2).name(),
			typeid(typename Args::Tp3).name(),
			typeid(typename Args::Tp4).name());
	}
};


int main()
{
	Breader<>().output();
	Breader<AltSet1<short>>().output();
	Breader<AltSet2<short>>().output();
	Breader<AltSet3<short>>().output();
	Breader<AltSet4<short>>().output();
	Breader<AltSet1<short>, AltSet2<int>>().output();
	Breader<AltSet2<short>, AltSet1<int>>().output();
	Breader<AltSet1<short>, AltSet2<int>, AltSet3<float>>().output();
	Breader<AltSet1<short>, AltSet2<int>, AltSet3<float>, AltSet4<double>>().output();
	Breader<AltSet4<short>, AltSet3<int>, AltSet2<float>, AltSet1<double>>().output();
	// 下面的会产生编译错误：对 Tp2 的访问不明确
	// Breader<AltSet2<short>, AltSet2<int>>().output();
}

