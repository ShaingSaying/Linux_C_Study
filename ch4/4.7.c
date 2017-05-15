#include <stdio.h>
#include <float.h>

int main()
{
    double d = 1.0 / 3.0;
    float f = 1.0 / 3.0;

    printf("float f = 1.0 / 3.0:\n");
    printf("%.4f\n%.12f\n%.16f\n", f, f, f);
    printf("double d = 1.0 / 3.0:\n");
    printf("%.4f\n%.12f\n%.16f\n", d, d, d);

    printf("FLT_DIG:%d\nDBL_DIG:%d\n", FLT_DIG, DBL_DIG);
	//FLT_DIG和DBL_DIG，分别表示float和double类型的有效数字位数
    return 0;
}
