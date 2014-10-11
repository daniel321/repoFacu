
all: 
	make memMap;

memMap:
	gcc memMap.c -o memMap;
	gcc memMap2.c -o memMap2;
	gcc memMap3.c -o memMap3;
	./memMap2&
	./memMap3&
	./memMap;
	rm memMap memMap2 memMap3;

