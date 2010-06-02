
/*
 *	math.h 
 *	contain constant of mathematics
 *	Written by Pham The Chung
 * */
/*
	usage:
		PI suitable for double type
		PI_32 is suitable for long double
		dont use float for PI.
		PI_38 is so long and I dont have any clue where it is 
		I forgot where I get it
*/
#define PI_38  3.1415926535897932384626433832795028842
#define PI_32  3.1415926535897932384626433832795
#define PI     3.14159265358979	//32384626433832795028842
#define PI_2   1.5707963267948966192313216916397514L  /* pi/2 */
#define PI_1_2 0.3183098861837906715377675267450287L /* 1/pi */

#define E_35   2.7182818284590452353602874713526625L
#define E 	2.71828182845904
#define SQRT_2 1.414213562373095048801688724297
#define SQRT_3 1.732050875688772935274463415059
/*	type defination	*/
typedef int v4si __attribute__((vector_size(16)));
/* calculate in degree */
double sin( double n );
double cos( double n );
double tan( double n );

double pow( double x,double y );

double sqrt( double x );
double hypot( double x, double y );
double cbrt( double x );
double root_of( double x,double y );



