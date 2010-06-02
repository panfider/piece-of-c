
#define abc_h 1
#ifndef basetype_h
	#include "basetype.h"
#endif
#include "linkasm.h"
char buf_word[256];
/* I will have the shape of function	*/
typedef struct {
	byte what;
	dword begin,end;
	byte *beginpt,*endpt,*namept;
	byte namesize;
	word fsize;
}Fshape;
Fshape fshape,*fshapept;
/*	use directly to detemining the function	*/
typedef struct brace{
	byte what;
	sbyte type;
	byte level;
	dword begin,end;
	byte *beginp,*endp;
	word nbytes;
}brace_t;
brace_t pos1,pos2;
brace_t *ppos1=&pos1,*ppos2=&pos2;
brace_t com;
char *not_func[]={
	"while","if","for","switch",
	NULL
};
char *keyword[]={
	"auto",    "enum",   "restrict","unsigned",
	"break",   "extern", "return",  "void",
	"case",    "float",  "short",   "volatile",
	"char",    "for",    "signed",  "while",
	"const",   "goto",   "sizeof",  "__Bool",
	"continue","if",     "static",  "_Complex",
	"default" ,"inline", "struct",  "_Imaginary",
	"do",      "int",    "switch",
	"double",  "long",   "typedef",
	"else",    "register","union",
	NULL
};

typedef struct Hash_Object_type{
	int key;
	byte word[256];
	struct Hash_Object_type *self;
}Hash_Object;
Hash_Object track_hash,id_table[1024],*first_hash=&track_hash,*hashPt=&id_table[0];
char buf_word[256];

//reserve the line below
