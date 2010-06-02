/*
	blinkled.c cpyR 2010
	use for test nanosleep poll syscall
	Written by Pham The Chung
	gcc blinkled.c -o blink -I/media/Chung/chungd/start/clib/include/
*/
#include <stdio.h>
#include <string.h>
#include <linux/termios.h>
#include <linux/kd.h>
#include <linux/fcntl.h>
#include <piece/kconnect.h>
#include <linux/time.h>
#include <piece/code_macro.h>
#define 	MILISEC	400
#define CALL_FUNC(name,par) name par
const char *version="blink is sleep+blink ing version 1\n\
Written by Pham The Chung\n";
SYSCALL_DEFINE3(open, const char __user *, filename, int, flags, int, mode);
SYSCALL_DEFINE3(ioctl,long, fd, long, cmd, unsigned long, arg);
SYSCALL_DEFINE2(nanosleep, struct timespec __user *, rqtp,
		struct timespec __user *, rmtp);
SYSCALL_DEFINE3(poll,
	struct pollfd __user *, ufds, unsigned int, nfds,long, timeout_msecs);
SYSCALL_DEFINE1(alarm, unsigned int, seconds);
SYSCALL_DEFINE1(exit, int, error_code);
/*	*TESTED* convert string a to long
*/
long a2i( char*a ){
	if( a==NULL ) return 0;
	inline long _C_pow10__(char base,char len){
		long val=base;
		while(len--)	val *= 10;
		return val;
	}
	long i=0;
	char r=0,flag=0,tmp,len=0;
	while( a[len]!=NULL ) len++;
	if( *a=='-' ) {flag=1;r++;len--;}
	char e=len-1;
	while( len-- ){
		tmp = a[r++]- 0x30;
		i += _C_pow10__(tmp,e--);
	}
	if(flag==1) i=-i;
	return i;
}
int mili_sleep(int mili){
	CALL_SYS(poll,(NULL,0,mili));
}
int nano_sleep(long nano){
	struct timespec tsc;
	struct timespec rtsc;
	tsc.tv_sec=0;
	tsc.tv_nsec=nano;
	CALL_SYS(nanosleep,(&tsc,&rtsc));
}
int blink_led(int mili){
	char swit=0;
	int fd=CALL_SYS(open,( "/dev/tty0",O_RDONLY,0));
	if(fd<0) {
		CALL_FUNC(printf,("error:cant open /dev/tty0\n"));
		return -1;
	}
	while(1) {
		if(swit) swit=0;else swit=1;
		mili_sleep(mili);
		CALL_SYS(ioctl,
		(fd,KDSETLED,(swit==0?LED_SCR|LED_NUM|LED_CAP:0)));
	}
	return 0;
}
int main(const int argc,const char **argv){
	short pc=argc;
	char V=0,fi=0;
	if(argc>1){
	/*	check where is version */
		while(pc-->1){
			if( !CALL_FUNC(strncmp,(argv[pc],"--",2)) ){
				char *pt=argv[pc]+2;
				if( !CALL_FUNC(strncmp,(pt,"version",7)) )
					CALL_FUNC(printf,(version));
				CALL_SYS(exit,(0));
			}
		}
		/*if no then do blink_led*/
		int seconds=a2i(argv[1]);
		CALL_SYS(alarm,(seconds));
		blink_led(MILISEC);
	}else blink_led(MILISEC);
	CALL_SYS(exit,(0));
}
