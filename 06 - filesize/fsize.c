/*
 * 	Course:		    COMP-381 Systems Programming
 * 	Program:	    fsize.c
 * 	Description:    Walk through the directory displaying inode information on files.
 * 	Author:		    Simon Spivey
 * 	Date:		    03/28/21
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>  //*fcn --> file control options
#include <unistd.h> //opendir, closedir | unix equivalent of io.h
#include <sys/stat.h> //stat, S_IFMT, S_IFDIR
#include <dirent.h> //struct dirent, DIR

/*
 * 					DIRENT STRUCT DESC
 * ulong_t d_offset;                ctual offset of this entry
 * ino_t           d_ino;           inode number of entry/File serial number
 * ushort_t        d_reclen;        length of this entry
 * ushort_t        d_namlen;        length of string in d_name
 * char d_name[_D_NAME_MAX+1];      name of entry (filename)
 *
 * ONLY USING d_name and ino_t
*/

#define MAX_PATH 260

void dirwalk(char *dir, void (*fcn)(char *)) {
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	while((dfd = opendir(dir)) == NULL) {
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) { //if our pointer to the directory name is null, ignore
			continue;
		}
		if(strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) { //we add 2 because name length could be 2 char long ".."
			fprintf(stderr, "directory name %s %s is too long\n", dir, dp->d_name);
		}
		else {
			sprintf(name, "%s%s", dir, dp->d_name);
			(*fcn)(name); //fcn gets descriptors for file and ouputs it as a nice struct
		}
	}
	closedir(dfd);

}

void fsize(char *name) {
	struct stat stbuf; //initialize buffer for printing

	if(stat(name, &stbuf) == -1) { //if we can't find any info on our file
		fprintf(stderr, "Access denied or File not found: %s.\n", name);
		return;
	}
	if((stbuf.st_mode & S_IFMT) == S_IFDIR) { //if our 'file type' (S_IFMT) is a 'directory' (S_IFDIR)
		dirwalk(name, fsize);
	}
	printf("%81ld %s\n", stbuf.st_size, name); //print as (long unsigned int, string pointer)

}

int main(int argc, char **argv) {
	if(argc == 1) {
		fsize("."); //we got no input args :(
	}
	else {
		while(--argc > 0) {
			fsize(*++argv); //loop through them all >:D
		}
	}
	return 0;
}
