/* change the global variable confict    */

#ifndef VCSTDIO
#define spkey cpkey
#define	FAST	register    		/* register variable	   */
#define PFAST	register		/* register parameter	   */
#endif
#define	EXTERN	extern			/* External variable	   */
#define	GLOBAL	/* */			/* Global variable	   */
#define	LOCAL	static			/* Local to module	   */

#ifndef VCSTDIO
typedef short		COUNT;
typedef unsigned int	UCOUNT; 
typedef char		TEXT,BYTE;
typedef int		WORD,VOID,BOOL;
typedef long		LONG;
typedef unsigned long	ULONG;
typedef unsigned char	UTEXT;
typedef char	       *TEXTPTR;
#endif

typedef unsigned int    VRLEN;
typedef int             RNDFILE;
typedef long            POINTER,NODEPTR;
typedef long		DATET;

