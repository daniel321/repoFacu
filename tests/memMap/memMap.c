#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "global.h"

void writing();
void reading();

int main(){
	writing();
	reading();
	return 0;
}

void writing(){
	int fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC,(mode_t)0600);

	/* Stretch the file size to the size of the (mmapped) array of chars.*/
	int result = lseek(fd, FILESIZE-1, SEEK_SET);
	result = write(fd, "", 1);

	/* Now the file is ready to be mmapped.*/
	map = (char*)mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	   
	for (i = 0; i<NUMCHARS; i++)
    		map[i] = '&';
 
	sleep(DELAY);
	/* write chars's to the file as if it were memory.*/
	for (i = 0; i<NUMCHARS; i++){
		map[i] = 'A' + i; 
		sleep(DELAY);
	}		      
			
	/* free the mmapped memory,*/
	munmap(map, FILESIZE);
	close(fd);
}

void reading(){
	int fd = open(FILEPATH, O_RDONLY);
	map = (char*)mmap(0, FILESIZE, PROT_READ, MAP_SHARED, fd, 0);

	printf("\nTermno: %s\n\n", map);
	
	munmap(map, FILESIZE);
	close(fd);
}















