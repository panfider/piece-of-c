/*
	Written Pham The Chung
	iofile.c
	create March 1 2010
	gcc [-m32/64] -c iofile.c -I../include
*/
/*
	compile success 32/64
*/
#include <piece/kconnect.h>
#include <piece/piece_code.h>
#include <piece/code_macro.h>
#include <linux/stat.h>
#include <linux/fcntl.h>
#include <piece/dirent.h>
#include <piece/itype.h>
#include <piece/syscall64.h>

Public PIECE_IMPLE(long,sizeofFile)(const char *filename){
	struct stat fod;
	int s = CALL_SYS(stat,( filename,&fod ));
	if( s==0 ) return fod.st_size;
	return ERROR;
}
Public PIECE_IMPLE(long ,getMode)( const char *filename ){
	struct stat fod;
	int i = CALL_SYS(stat, ( filename,&fod ));
	if ( i==0 ) return fod.st_mode;
	return ERROR;
}
Public PIECE_IMPLE(int ,ifaccess)( const char *name,int n ){
	return CALL_SYS(access,(name,n));
}
/*
 *	copy must have absolutely path to file
 *	pathname is path to file name must come first with / root
 *	copy ( /path/to/A_file, /path/to/name2 );
 *	copy dont check file exist.
 *	return <0 if error
 	0 is success copy to exist file
 	FIXME
 		+it does not check valid data copy, lost byte
 			so may pass to return value
 		+it doesnt check mode of src what will it get
 * */

PIECE_IMPLE(int,copyfile)( const char *src,const char *dst ) {
	#define CPSIZE (4096)
	if((src==NULL)||(dst==NULL) ) return -1;
	char buf[CPSIZE];
	int wr,wr2,rd,fd,fd2,creatmode=0660;
	long FileSize=0;
	struct stat fod;
        if(!CALL_SYS(stat,( src,&fod))) {
        	FileSize = fod.st_size;
        	creatmode = fod.st_mode;
        }
	else return -2;
	/*Have already check with stat*/
	fd  = CALL_SYS(open, ( src,O_RDONLY,0 ));
	fd2 = CALL_SYS(open,( dst,O_RDWR|O_CREAT,creatmode ));
	if(fd2<0) return -3;
	if(FileSize< CPSIZE){
		rd = CALL_SYS(read,( fd,buf,FileSize));
		wr = CALL_SYS(write,( fd2,buf,FileSize ));
	}
	else {
		unsigned int frag,byte,run;
		frag = FileSize/CPSIZE;
		byte = FileSize%CPSIZE;
		for (run=0;run<frag;run++) {
			/* I dont know but it auto seek to new fragment */
			rd = CALL_SYS(read,( fd,buf,CPSIZE));
			wr = CALL_SYS(write,( fd2,buf,CPSIZE ));
		}
		CALL_SYS(read, (fd, buf,byte ));/* write to file mod byte*/
		CALL_SYS(write, (fd2,buf,byte));
	}
	CALL_SYS(close,(fd));
	CALL_SYS(close,(fd2));
	return CALL_SYS(access,(dst,0));
}
#define get_bit(obj,th) (((obj&(1<<th))==(1<<th))?1:0)
static int ifdir( const char *name ) {
	if( name==NULL ) return 0;
	struct stat fod;
	int r,bit;
	if( CALL_SYS(stat,(name,&fod)) ) return 0;
	bit= fod.st_mode;
	return get_bit(bit,14);
}
/*
	TESTED
	copydir(from,to)
	guide address /path/to/from_dir/ /path/to/to_dir/
	to is directory contain copied from
	FIXME
		+return a value clear to user easy to check valid data
		has been copy
*/
#define NAME_LEN 256
PIECE_IMPLE(long, copydir)( const char *from,const char *to){
	if((from==NULL)||(to==NULL)) return -1;
	char **litem=PIECE_CALL(direntry,(from));
	if(litem==NULL) return -2;
	/*attemp to stat dir first*/
	struct stat fod;
	if(CALL_SYS(stat,(from,&fod))) return -3;
	int from_mode=fod.st_mode;
	if(ifdir(from)) return -4;
	/*form an address of to_dir*/
	int len_to=PIECE_CALL(strlen,(to));
	int len_from=PIECE_CALL(strlen,(from));
	char name1[len_from+NAME_LEN+2];
	char name2[len_to+NAME_LEN+2]; /*how can gcc do this ?*/
	/*prepare for name*/
	PIECE_CALL(strcpy,(name1,from));
	PIECE_CALL(strcpy,(name2,to));
	if( name1[len_from-1]!='/') {
		name1[len_from]='/';name1[len_from+1]=0;
		len_from++;
	}
	if(name2[len_to-1]!='/'){
		name2[len_to]='/';name2[len_to+1]=0;
		len_to++;
	}
	int run=0;
	if(CALL_SYS(mkdir,(to,from_mode))) return -5;
	while(litem[run]) {
		PIECE_CALL(cpyStringat,(name1,litem[run],len_from));
		PIECE_CALL(cpyStringat,(name2,litem[run],len_to));
		if(
			PIECE_CALL(strcmp,(litem[run],"."))&&
			PIECE_CALL(strcmp,(litem[run],"..")) )
		{
			if(ifdir(name1))
				PIECE_CALL(copydir,(name1,name2));
			else
				PIECE_CALL(copyfile,(name1,name2));
			/*printf("from %s ->%s %s\n",name1,name2,litem[run] );*/
		}
		run++;
	}
	return 0;
}
/*
	TESTED
	FIXME designed return mechanism to check progress of remove file and 
		check the remove of each file
*/
PIECE_IMPLE(long,removdir)( const char *dirname ){
	int ret;
	if(dirname==NULL) return -1;
	if(!ifdir(dirname)) return -2;
	int len=PIECE_CALL(strlen,(dirname));
	char name[len+NAME_LEN+2];
	if(len==0) return -3;
	char **litem=PIECE_CALL(direntry,(dirname));
	if(litem==NULL) return -4;
	/*prepare for remove dir*/
	PIECE_CALL(strcpy,(name,dirname));
	if(name[len-1]!='/') { name[len]='/';name[len+1]=0;len++; }
	int run=0;
	while(litem[run]){
		PIECE_CALL(cpyStringat,(name,litem[run],len));
		if(
			PIECE_CALL(strcmp,(litem[run],"."))&&
			PIECE_CALL(strcmp,(litem[run],"..")) ) {
			if(ifdir(name)) PIECE_CALL(removdir,(name));
			else PIECE_CALL(unlink,(name));
			/*printf("%s\n",name);*/
		}
		run++;
	}
	if(PIECE_CALL(ndentry,(dirname))==2) ret=PIECE_CALL(rmdir,(dirname));
	else ret=PIECE_CALL(ndentry,(dirname));
	return ret;
}
/*
	/path/to/dir1->/path2/to/dir2
	FIXME design return value to check valid data has been move
*/
PIECE_IMPLE(long,movdir)(const char *src,const char *dst){
	if((src==NULL)||(dst==NULL)) return -1;
	int ret,src_mode=0750;
	char **entp;
	int len_src=PIECE_CALL(strlen,(src));
	int len_dst=PIECE_CALL(strlen,(dst));
	char name1[len_src+NAME_LEN+2];	/*how can gcc do this?*/
	char name2[len_dst+NAME_LEN+2];
	/*check real directory*/
	struct stat fod;
	if( !ifdir(src) ) return -2;
	if(CALL_SYS(stat,(src,&fod))) return -3;
	src_mode=fod.st_mode;
	/*form a address of */
	PIECE_CALL(strcpy,(name1,src));
	PIECE_CALL(strcpy,(name2,dst));
	if( name1[len_src-1]!='/') {
		name1[len_src]='/';name1[len_src+1]=0;
		len_src++;
	}
	if(name2[len_dst-1]!='/'){
		name2[len_dst]='/';name2[len_dst+1]=0;
		len_dst++;
	}
	/*get directory entry*/
	entp=PIECE_CALL(direntry,(src));
	if(entp) return -4;
	/*make dst dir*/
	if(CALL_SYS(mkdir,(dst,src_mode))) return -5;
	int run=0;
	while(entp[run]){
		PIECE_CALL(cpyStringat,(name1,entp[run],len_src));
		if(
			PIECE_CALL(strcmp,(entp[run],"."))&&
			PIECE_CALL(strcmp,(entp[run],"..")) ) {
			if(ifdir(name1)) PIECE_CALL(movdir,(name1,name2));
			else {
				/*dont check unlink,still copying while error*/
				PIECE_CALL(copyfile,(name1,name2));
				CALL_SYS(unlink,(name1));
			}
		}
		run++;
	}
	if(PIECE_CALL(ndentry,(name1))==2) ret=CALL_SYS(rmdir,(name1));
	return ret;
}
/*this need dirent*/
PIECE_IMPLE(char *,ttyname) (long fd) {
	struct stat fod;
	Dir *dp;
	Dirent *entp;
	char *tname=(char *)malloc(301);
	if(CALL_SYS(fstat,(fd,&fod))) return NULL;
	long ino = fod.st_ino;
	dp=PIECE_CALL(fdopendir,(fd));
	while((entp=_PC(readdir,(dp)))){
		if(ino==entp->d_ino){
		  PIECE_CALL(strcp,(tname,entp->d_name));
		  return tname;
		}
	}
	return NULL;
}

