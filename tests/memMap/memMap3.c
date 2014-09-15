#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "global.h"

int main(){
	int fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC,(mode_t)0600);
	int result = lseek(fd, FILESIZE-1, SEEK_SET);
	result = write(fd, "", 1);

	map = (char*)mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	sleep(DELAY);	
	for (i = NUMCHARS-1; i>=0; i--){ 
		map[i] = 'a'+ i;	// modifico concurrentemente el mmap a ver que pasa 
		sleep(DELAY);
	}		      
			
	munmap(map, FILESIZE);
	close(fd);
	return 0;
}














