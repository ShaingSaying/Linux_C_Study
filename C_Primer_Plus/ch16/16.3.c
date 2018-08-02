#include <stdio.h>
#include <math.h>
struct polar {
	double r;
	double theta; /* angle in degrees */
};
struct rect {
	double x;
	double y;
};
struct rect p_to_r(const struct polar * ppol);
int main(void)
{
	struct polar input;
	struct rect answer;
	printf("Enter magnitude and angle in degrees: ");
	while (scanf("%lf %lf", &input.r, &input.theta) == 2)
	{
		answer = p_to_r(&input);
		printf("polar coord: %g %f\n",input.r, input.theta);
		printf("rectangular coord: %g %g\n",answer.x, answer.y);
		printf("Enter magnitude and angle in degrees (q to quit): ");
	}
	puts("Bye");
	return 0;
}
struct rect p_to_r(const struct polar * ppol)
{
	static const double deg_rad = 3.141592654 / 180.0;
	struct rect res;
	double ang = deg_rad * ppol->theta; /* convert degrees to radians */
	res.x = ppol->r * sin(ang);
	res.y = ppol->r * cos(ang);
	return res;
}
