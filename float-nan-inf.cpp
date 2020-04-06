#include <cstdio>
#include <cmath>

#define out(expr) printf(#expr " = %f (%a)\n", (expr), (expr))

int main()
{
	out(+1.0 / 0.0); out(-1.0 / 0.0);
	out(+0.0 / 0.0); out(-0.0 / 0.0);
	double inf = INFINITY;
	out(+1.0 / inf); out(-1.0 / inf);
	out(+1.0 * inf); out(-1.0 * inf);
	out(+0.0 / inf); out(-0.0 / inf);
	out(+0.0 * inf); out(-0.0 * inf);
}

/// gcc 5.1.0 输出
// +1.0 / 0.0 = inf (inf)
// -1.0 / 0.0 = -inf (-inf)
// +0.0 / 0.0 = -nan (-nan)
// -0.0 / 0.0 = -nan (-nan)
// +1.0 / inf = 0.000000 (0x0p+0)
// -1.0 / inf = -0.000000 (-0x0p+0)
// +1.0 * inf = inf (inf)
// -1.0 * inf = -inf (-inf)
// +0.0 / inf = 0.000000 (0x0p+0)
// -0.0 / inf = -0.000000 (-0x0p+0)
// +0.0 * inf = -nan (-nan)
// -0.0 * inf = -nan (-nan)

/// clang 4.0.0 输出
// +1.0 / 0.0 = inf (inf)
// -1.0 / 0.0 = -inf (-inf)
// +0.0 / 0.0 = nan (nan)
// -0.0 / 0.0 = nan (nan)
// +1.0 / inf = 0.000000 (0x0p+0)
// -1.0 / inf = -0.000000 (-0x0p+0)
// +1.0 * inf = inf (inf)
// -1.0 * inf = -inf (-inf)
// +0.0 / inf = 0.000000 (0x0p+0)
// -0.0 / inf = -0.000000 (-0x0p+0)
// +0.0 * inf = -nan (-nan)
// -0.0 * inf = -nan (-nan)

/// vc++ 19.0 (vs140) 编译错误 C2124: 被零除或对零求模
