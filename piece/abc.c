/*
 *	Copyright (c) clib Shift Code Technology  2010 Pham The Chung
 *	This file is under GPL license. Please read the term use by GPL license.
 * */
#include "abc.h"

/*
 * get size of identifier to copy string
 * any character out size a-z is terminate
 * return number of byte
 * */
int idsize( char *pt ){
	short count=0;
	while( ((*pt>='a'&&*pt<='z')||(*pt>='A'&&*pt<='Z')||(*pt>='0'&&*pt<='9')||*pt==0x5f) ){
		// inside of identifier defination
		count++;
		pt++;
	}
	return count;
}
long ifExistInHash( const char *key,hash_table *hpt,int howMany ){
	unsigned run=howMany,ret=0;
	while( run--!=0 ){
		if( !cmps(hpt[run].self->word,key ) ) {
			ret=1;break;
		}
	}
	return ret;
}
/* underconstruction ; incomplete
 * can run now to test
 */
Object FuncObj[1024];
Object_Pointer FuncObjPt=&FuncObj[1];
Object_Pointer tag_Func_Name( char* mem ) {
	unsigned p=0,nest1=0,nest2=0;
	char in=0,out=1,cin=0,cout=1,fix=0,inword=0;
	FuncObj[0].val=0;
	char temp[256];
	while( *(mem+p)!=NULL ){	
		if( (mem[p]>='a'&&mem[p]<='z')||(mem[p]>='A'&&mem[p]<='Z')||mem[p]==0x5f ){
			in=1;
			if( in==1&&out==1 ) {
				inword=1;
				if( fix==0 ) {
					cpyStringn( temp,mem+p,idsize(mem+p) );
				}
			}
			out=0;
		}
		if( !((mem[p]>='a'&&mem[p]<='z')||(mem[p] >='A'&&mem[p]<='Z')||(mem[p]>='0'&&mem[p]<='9')||mem[p]==0x5f) ) {
			in=0;
			if( in==0&&out==0 ) inword=0;
			out=1;
		}
		if( mem[p]==0x28 ) {
			fix=1;
			if( ppos1->level==0 ){
				ppos1->begin=p; ppos1->beginp=mem+p; 
				ppos1->level=1; 
			}
			if( ppos1->level==1 ) nest1++;
		}
		if( mem[p]==0x29 ) {
			if( ppos1->level==1&&nest1!=0 ) nest1--;
			if( ppos1->level==1&&nest1==0 ){
				ppos1->end=p;
				ppos1->endp=mem+p;fix=0;
				ppos1->level==0;
				if( searchList(temp,not_func)==NULL ){
					(FuncObj[0].val++);
					cpyString(FuncObjPt->name,temp);
					FuncObjPt++;
				}
			}

		}
		p++;
	}
	return FuncObj;
}
Object *getFuncList(void){
	return FuncObj;
}
int tag_word( char *mem ){
	char in=0,out=1,eword=-1,key_run=0;
	char *pt=buf_word;
	first_hash->key=0;
	while ( *mem!=NULL ){
		if( (*mem>='a'&&*mem<='z')||(*mem>='A'&&*mem<='Z')||*mem==0x5f )
		{
			in=1;
			if(in==1&&out==1) {
				eword=1;
				cpyStringn( buf_word,mem,idsize(mem));
				if( !searchList(buf_word,keyword) ) {
					hashPt->self=hashPt;	// init it's self of each element of id_table
					if( !ifExistInHash( buf_word,id_table,first_hash->key ) ){ 
						cpyString(hashPt->self->word,buf_word);
						++first_hash->key;
						hashPt++;
					}
				}
			}
			out=0;
		}
		if( !((*mem>='a'&&*mem<='z')||(*mem>='A'&&*mem<='Z')||(*mem>='0'&&*mem<='9')||*mem==0x5f) ){
			in=0;
			if( in==0&&out==0) eword=0;
			out=1;
		}
		mem++;
	}
	hashPt=id_table;
	return 0;
}

void init_brace(brace_t *bp){
	bp->type=-1;
	bp->level=0;
	bp->begin=0;
	bp->end=0;
}

