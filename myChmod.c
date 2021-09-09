#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#include <bsd/unistd.h>

int main(int argc, char* argv[]){
    int new_mode;
    long omode;
    void* set;
    char *mode, *file, *eptr;
    struct stat st;    
    
    if(argc < 3){
    	printf("Insufficient Arguments!\n");
	exit(1);
    }

    argv++;
    mode = *argv;
    argv++;
    file = *argv;

    if(*mode >= '0' && *mode <= '7'){
	errno = 0;
	if(strlen(mode) != 3){
	    errno = ERANGE;
	}
    	omode = strtol(mode, &eptr, 8);
	if(errno || *eptr){
	    errx(1, "Invalid file mode: %s\n", mode);
	}
	new_mode = (int)omode;
    }else{
	set = setmode(mode);

	if(set == NULL){
	    errx(1, "Invalid Mode: %s\n", mode);
	}

    	if(stat(file, &st)){
	    err(1,"%s\n", file);
	}
	new_mode = getmode(set, st.st_mode);
	free(set);
    }

    if(chmod(file, new_mode)){
    	err(1, "%s\n", file);
    }

    return 0;
}
