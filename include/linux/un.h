#ifndef	_SYS_UN_H
#define	_SYS_UN_H	1
#define PATH_LEN	108
struct sockaddr_un
  {
    unsigned short int sun_family;
    char sun_path[PATH_LEN];		/* Path name.  */
  };
  
  #endif
