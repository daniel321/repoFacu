#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "global.h"

int main(){
	int fd = open(FILEPATH, O_RDONLY);
	map = (char*)mmap(0, FILESIZE, PROT_READ, MAP_SHARED, fd, 0);

	int i;
	for (i = 0; i<NUMCHARS; i++){
		printf("\n%s", map);  // leo el mmap mientras lo modifico en el otro proceso
		sleep(DELAY);
	}
	return 0;

	munmap(map, FILESIZE);
	close(fd);
}

































