
// 
// tsh - A tiny shell program with job control
// 
// William Montgomery and B Becker
//

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string>

#include "globals.h"
#include "jobs.h"
#include "helper-routines.h"

//
// Needed global variable definitions
//

static char prompt[] = "tsh> ";
int verbose = 0;

//
// You need to implement the functions eval, builtin_cmd, do_bgfg,
// waitfg, sigchld_handler, sigstp_handler, sigint_handler
//
// The code below provides the "prototypes" for those functions
// so that earlier code can refer to them. You need to fill in the
// function bodies below.
// 

void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

//
// main - The shell's main routine 
//
int main(int argc, char **argv) 
{
  int emit_prompt = 1; // emit prompt (default)

  //
  // Redirect stderr to stdout (so that driver will get all output
  // on the pipe connected to stdout)
  //
  dup2(1, 2);

  /* Parse the command line */
  char c;
  while ((c = getopt(argc, argv, "hvp")) != EOF) {
    switch (c) {
    case 'h':             // print help message
      usage();
      break;
    case 'v':             // emit additional diagnostic info
      verbose = 1;
      break;
    case 'p':             // don't print a prompt
      emit_prompt = 0;  // handy for automatic testing
      break;
    default:
      usage();
    }
  }

  //
  // Install the signal handlers
  //

  //
  // These are the ones you will need to implement
  //
  Signal(SIGINT,  sigint_handler);   // ctrl-c
  Signal(SIGTSTP, sigtstp_handler);  // ctrl-z
  Signal(SIGCHLD, sigchld_handler);  // Terminated or stopped child

  //
  // This one provides a clean way to kill the shell
  //
  Signal(SIGQUIT, sigquit_handler); 

  //
  // Initialize the job list
  //
  initjobs(jobs);

  //
  // Execute the shell's read/eval loop
  //
  for(;;) {
    //
    // Read command line
    //
    if (emit_prompt) {
      printf("%s", prompt);
      fflush(stdout);
    }

    char cmdline[MAXLINE];

    if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
      app_error("fgets error");
    }
    //
    // End of file? (did user type ctrl-d?)
    //
    if (feof(stdin)) {
      fflush(stdout);
      exit(0);
    }

    //
    // Evaluate command line
    //
    eval(cmdline);
    fflush(stdout);
    fflush(stdout);
  } 

  exit(0); //control never reaches here
}
  
/////////////////////////////////////////////////////////////////////////////
//
// eval - Evaluate the command line that the user has just typed in
// 
// If the user has requested a built-in command (quit, jobs, bg or fg)
// then execute it immediately. Otherwise, fork a child process and
// run the job in the context of the child. If the job is running in
// the foreground, wait for it to terminate and then return.  Note:
// each child process must have a unique process group ID so that our
// background children don't receive SIGINT (SIGTSTP) from the kernel
// when we type ctrl-c (ctrl-z) at the keyboard.
//
void eval(char *cmdline) {
  /* Parse command line */
  //
  // The 'argv' vector is filled in by the parseline
  // routine below. It provides the arguments needed
  // for the execve() routine, which you'll need to
  // use below to launch a process.
  //
 	char *argv[MAXARGS];
	char buf [MAXLINE]; 
	int bg;
	pid_t pid;
	sigset_t mask;
	sigemptyset(&mask); //  empties mask in case of previous mask.
	sigaddset(&mask, SIGCHLD); // this defines the mask is for SIGCHLD	
	
	
  //
  // The 'bg' variable is TRUE if the job should run
  // in background mode or FALSE if it should run in FG
        bg = parseline(cmdline, argv);

	if (argv[0] == NULL) 
          	return; /* IGNORE EMPTY LINES */

	if (!builtin_cmd(argv)){	// forking and execing a child process

		sigprocmask(SIG_BLOCK, &mask, 0); // blocks sig, using &mask, and doesn't look at preivous mask (0). 
		
		if ((pid = fork()) < 0 ){ // fork the process
			unix_error("cannot fork");
			exit(0);
		}
		if (pid  == 0){ /*Child runs user job */ // need to: 1. set new process 2. run command
			
			setpgid(0,0); // adds this child to the parent process group. 

			if (execve(argv[0], argv, environ) < 0 ) {  // execvp allows you to not use /bin/ "p" uses default environment path
				printf("%s: Command not found. \n", argv[0]);
				exit(0);
			}
			
						
		}
		// Now to handle the parent: 1. add job 2.unblock signal 3. do job
		else { 		
			if (!bg){	   // running this program "alpha"
	     			addjob(jobs, pid, FG, cmdline); // add "alpha" to FG list	
				sigprocmask(SIG_UNBLOCK, &mask, 0); // unblock the sig so "alpha" can run
				waitfg(pid); 				// wait for "alpha" to stop. 
			}
			else {
				addjob(jobs, pid, BG, cmdline); // add to BG list
	     			printf("[%d] (%d) %s", pid2jid(pid), pid, cmdline);
			}
     		}
	}	
  return;
}


/////////////////////////////////////////////////////////////////////////////
//
// builtin_cmd - If the user has typed a built-in command then execute
// it immediately. The command name would be in argv[0] and
// is a C string. We've cast this to a C++ string type to simplify
// string comparisons; however, the do_bgfg routine will need 
// to use the argv array as well to look for a job number.
//
int builtin_cmd(char **argv) {
// need quit bg fg and jobs. 
	

 	if (!strcmp(argv[0], "quit" ) )    // exits shell
		exit(0);

 	if (!strcmp(argv[0], "&" ) ) // ignores the singleton &
		return 1;

	if (!strcmp(argv[0], "fg" )       ||      !strcmp(argv[0], "bg"  ) ){
		do_bgfg(argv);
		return 1;
	}
	if (!strcmp(argv[0], "jobs" ) ) {
		listjobs (jobs);
		return 1;		
	}
 	return 0;     /* not a builtin command */
}

/////////////////////////////////////////////////////////////////////////////
//
// do_bgfg - Execute the builtin bg and fg commands
//
void do_bgfg(char **argv) 
{
  struct job_t *jobp=NULL;
    
  /* Ignore command if no argument */
  if (argv[1] == NULL) {
    printf("%s command requires PID or %%jobid argument\n", argv[0]);
    return;
  }
    
  /* Parse the required PID or %JID arg */
  if (isdigit(argv[1][0])) {
    pid_t pid = atoi(argv[1]);
    if (!(jobp = getjobpid(jobs, pid))) {
      printf("(%d): No such process\n", pid);
      return;
    }
  }
  else if (argv[1][0] == '%') {
    int jid = atoi(&argv[1][1]);
    if (!(jobp = getjobjid(jobs, jid))) {
      printf("%s: No such job\n", argv[1]);
      return;
    }
  }	    
  else {
    printf("%s: argument must be a PID or %%jobid\n", argv[0]);
    return;
  }

  //
  // You need to complete rest. At this point,
  // the variable 'jobp' is the job pointer
  // for the job ID specified as an argument.
  //
  // Your actions will depend on the specified command
  // so we've converted argv[0] to a string (cmd) for
  // your benefit.
  //
  string cmd(argv[0]);
 	if (!strcmp(argv[0],"fg")){
		
		jobp->state = FG; // changes state to FG
		kill(-(jobp->pid), SIGCONT); // sends the continue signal to the pid
		waitfg(jobp->pid);  // waits for this pid to finish before exiting dobgfg
	}
	if (!strcmp(argv[0], "bg")){

		jobp->state = BG; // changes state to BG
		kill(-(jobp->pid), SIGCONT); //sends the continue signal to the pid
	     	printf("[%d] (%d) %s", jobp->jid, jobp->pid, jobp->cmdline); //gotta tell tsh that it's in bg.
	}
 	 return;
}

/////////////////////////////////////////////////////////////////////////////
//
// waitfg - Block until process pid is no longer the foreground process
//
void waitfg(pid_t pid)
{
	while ( pid == fgpid(jobs)) // while fgpid in the jobs list is equal to "pid", it will sleep. 
		//printf("pid: %d fgpid: %d\n", pid, fgpid(jobs));
		sleep(0);
	return;
}

/////////////////////////////////////////////////////////////////////////////
//
// Signal handlers
//


/////////////////////////////////////////////////////////////////////////////
//
// sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
//     a child job terminates (becomes a zombie), or stops because it
//     received a SIGSTOP or SIGTSTP signal. The handler reaps all
//     available zombie children, but doesn't wait for any other
//     currently running children to terminate.  
//
void sigchld_handler(int sig) 
{

// nothing given :(	
// child ends in three ways: 1. Finishes without issue 2. signal terminated child 3. 

  int status;						
  pid_t pid;

	while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0 ) {
	
		if (WIFEXITED(status)) {   /*checks if child terminated normally */
			deletejob(jobs, pid);
		}

		if (WIFSIGNALED(status)) {  /*checks if child was terminated by a signal that was not caught */
			printf("Job [%d] (%d) terminated by signal %d\n", pid2jid(pid), pid, WTERMSIG(status));
	    		deletejob(jobs,pid);
		}

		if (WIFSTOPPED(status)) {     /*checks if child process that caused return is currently stopped */
	    		getjobpid(jobs, pid)->state = ST; // sets the state of the pid to stopped (not bg or fg). 
	    		printf("Job [%d] (%d) stopped by signal %d\n", pid2jid(pid), pid, WSTOPSIG(status));
		}

    }
    
  
    
    return;
}

/////////////////////////////////////////////////////////////////////////////
//
// sigint_handler - The kernel sends a SIGINT to the shell whenver the
//    user types ctrl-c at the keyboard.  Catch it and send it along
//    to the foreground job.  
//
void sigint_handler(int sig) 
{
	pid_t pid = fgpid(jobs);

  	if (pid != 0)
      		kill(-pid, sig);  
	return;
}

/////////////////////////////////////////////////////////////////////////////
//
// sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
//     the user types ctrl-z at the keyboard. Catch it and suspend the
//     foreground job by sending it a SIGTSTP.  
//
void sigtstp_handler(int sig) 
{
	pid_t pid = fgpid(jobs);
    
    	if (fgpid(jobs) != 0)
		kill(-pid, sig);    // negative sign sends to whole pgid. 
	return;
}

/*********************
 * End signal handlers
 *********************/



		
