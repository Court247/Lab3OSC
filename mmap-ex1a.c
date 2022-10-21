#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>

int main(){

uint N=0x80000000;
float sparsity = 0.00001;

uint *ptr = (uint *) mmap ( NULL, N*sizeof(int),
 PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS , 0, 0 );

if(ptr == MAP_FAILED){
    printf("Mapping Failed\n");
    return 1;
}

for(uint i=0; i<N; i++) {
    if ((random() % N) < sparsity*N)
    ptr[i] = i*10;
}

if (N<10)
for(uint i=0; i<N; i++)
    printf("[%d] ",ptr[i]);
else
    printf("[%d] ", ptr[N-1]);

printf("\n");
int err = munmap(ptr, 10*sizeof(int));
if(err != 0){
    printf("UnMapping Failed\n");
    return 1;
}

return 0;
}
