//#include <stdio.h>
/*
	-----------
	stdio
*/

#define NULL (0)
typedef struct {
	float a[4];
}v4f;

void putchar(char c){
	#define STDOUT 1
	write(STDOUT,&c,1);
}
int slen(char *s){
	int a=0;
	while( *s++!=NULL) a++;
}
void print(char *s){
	write(STDOUT,s,slen(s));
}

extern inline float usqrtf(float n); 
extern addvec(v4f *V,v4f *R);
inline float sqrtf(float n) {
	asm("sqrtss %xmm0,%xmm0");
}
void pp( v4f *V,v4f *r){
	V->a[0]=1986.1004;
}
int abc(int a,int b,int c,int d){
	return a+b+c+d;
}
int (*funp)(void *data);
int main(){
	float fp=3.14159;
	v4f T[]={{12.7,0.45,0.225,7.62},{1.0,2.0,3.0,4.0}};
	v4f R;
	addvec(T,&R);
	//printf("sqrt of pi= %f %f %f\n",usqrtf(fp),R.a[0],R.a[1]);
	return 0;
}
