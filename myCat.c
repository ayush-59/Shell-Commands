#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

//function to copy content of one file to another
void cat(int rfd, int wfd){
    
    static char *buf;
    static size_t bsize;
    struct stat sbuf;

    // create buffer if not already created
    if (!buf) {
        if (fstat(wfd, &sbuf)) {
            err(1, "stdout");
        }
        bsize = sbuf.st_blksize;    // get the block size of file to be written
        buf = malloc(bsize);

        if (!buf) {
            err(1, 0);
        }
    }

    ssize_t nr, nw;
    int offset = 0;
    nr = read(rfd, buf, bsize);

    while (nr > 0) {
	// keep writing in file until everything is written
	// in case write fails 
        for (offset = 0; nr > 0; nr -= offset += nw) {
            nw = write(wfd, buf+offset, nr);
            if (nw < 0) {
                err(1, "stdout3");
            }
        }
         nr = read(rfd, buf, bsize);
    }
}

int main(int argc, char *argv[]){
    
    char *rf, *wf;
    int rfd, wfd;
    argv++;

    if(argc < 2)
	errx(1, "Insufficient arguments!");

    if(argc > 2){
    	if(**argv == '>'){
	    //create new file
	    ++argv;
    	    rfd = fileno(stdin);
    	    wfd = open(*argv, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR |
			    S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH );
	    if(rfd < 0){
	    	err(1, "stdin");
	    }
	    if(wfd < 0){
	    	err(1, "%s", *argv);
	    }

	    cat(rfd, wfd);


	}else if(strcmp(*(argv+1), ">") == 0 || strcmp(*(argv+1), ">>") == 0){
	    //copy content of one file to another
	    ++argv;
	    rf = *(argv - 1);
	    wf = *(argv + 1);
	    
	    //in case of >> open file in append mode
	    //and create mode in case file does not exist
	    //else open in trunc mode
	    if(strcmp(*argv, ">>") == 0)
    	    wfd = open(wf, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR |
			    S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH );
	    else
    	    wfd = open(wf, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR |
			    S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH );
	    
    	    rfd = open(rf, O_RDONLY);

	    if(rfd < 0){
	    	err(1, "%s", rf);
	    }
	    if(wfd < 0){
	    	err(1, "%s", wf);
	    }

	    cat(rfd, wfd);
    	   

	}else{
	    // display contents of all files on stdout
	    while(*argv){
		//if filename == '-' read from stdin
		if(strcmp(*argv, "-") == 0)  
		    rfd = fileno(stdin);
		else
    	            rfd = open(*argv, O_RDONLY);

    	        wfd = fileno(stdout);
	    	
	    	if(rfd < 0){
	    	    err(1, "%s", *argv);
	    	}
	    	if(wfd < 0){
	    	    err(1, "stdout");
	    	}
		cat(rfd, wfd);
		++argv;
	    }	
	}
    }else{
	// in case of 1 file display its contents to stdout
	if(strcmp(*argv, "-") == 0)
	    rfd = fileno(stdin);
	else
    	    rfd = open(*argv, O_RDONLY);
        wfd = fileno(stdout);

	if(rfd < 0){
	    err(1, "%s", *argv);
	}
	if(wfd < 0){
	     err(1, "stdout");
	}

	cat(rfd, wfd);
    } 
    
    //close files
    if(rfd != fileno(stdin))
	close(rfd);
    if(wfd != fileno(stdout))
	close(wfd);

    return 0;
    
}
