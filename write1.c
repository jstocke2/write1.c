#include	<stdio.h>
#include	<fcntl.h>
#include	<utmp.h>
#include        <time.h>
#include        <string.h>

/*
 * write1.c
 *
 *	purpose: send messages to another terminal
 *	 method: open the other terminal for output then
 *	 	 copy from stdin to that terminal
 *        usage: write1 username
 */

main( int ac, char *av[] )
{
	int	fd;
	char	buf[BUFSIZ];
	char	*get_tty(), *tty_for_user;

	if ( ac != 2 ){                                    /* check args */
		fprintf(stderr,"usage: write0 logname\n");
		exit(1);
	}
	
	tty_for_user = get_tty( av[1] );                  /* find user give warning if null */
	if ( tty_for_user == NULL )
	{
		printf("Warning:  User is not Logged in");
		exit(1);
	}
	

	sprintf(buf, "/dev/%s", tty_for_user);		/* open device */
	fd = open( buf, O_WRONLY );
	if ( fd == -1 ){
		perror(buf); exit(1);
	}

	while( fgets(buf, BUFSIZ, stdin) != NULL )       /* write to user */
		if ( write(fd, buf, strlen(buf)) == -1 )
			break;
	close( fd );
}

char *
get_tty( char *logname )
/*
 * purpose: find the tty at which 'logname' is logged in
 * returns: a string or NULL if not logged in
 *  errors: does not handle multiple logins 
 */
{
	static struct utmp utrec;
	int	      utfd;
	int	      namelen = sizeof( utrec.ut_name );
	static char	      *retval = NULL ;
	static char ttyLabel[15];
	time_t currentTerminal;
	time_t nextTerminal;
	int numberofTerminals = 0;
	double seconds;
	
	if ( (utfd = open( UTMP_FILE, O_RDONLY )) == -1 )   /* open utmp */
		return NULL;

	/* look for a line where the user is logged in */
	
	while( read( utfd, &utrec, sizeof(utrec)) == sizeof(utrec))
	{
		
		if ( strncmp(logname, utrec.ut_name, namelen ) == 0 )
		{
			//printf("Inside Found a Match");  //debug value
			
			
			
			if (numberofTerminals == 0)
			{
				currentTerminal = utrec.ut_time;
				strcpy(ttyLabel,utrec.ut_line);
				retval = ttyLabel;
				++numberofTerminals;
				
			
			}
			
			else 
			{
				nextTerminal = utrec.ut_time;
				seconds = difftime(currentTerminal,nextTerminal);
				++numberofTerminals;
				if (seconds <  0)
				{
					 strcpy(ttyLabel,utrec.ut_line);
					 retval = ttyLabel;
				}					
				
				
				
			}
			
			
			
		}
	
	}
	close(utfd); 	/* close & go */
	
	return retval;
	
}
