#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int charSize(char* m){
    int digits = 0, total = 0, i = 0, power = 0;
    while(*m != '\0'){
        m++;
        digits++;
    }
    // Restore the pointer to the init point
    m = m - digits;
    for (i = 0;i < digits; i++){
        power = (int) pow(10,digits-i-1);           
        total += (*(m+i) - '0') * power;
    }
    // Now converting the digit to int
    return total;
}



int main(int args, char **argv){
    printf("------------------------\n");
    if (args != 2) {
        printf("Help: Missed parameter introduce an integer, eg: array 8\n");
        return -1;
    }
    // Otherwise parsing the parameter
    int i = 0; // This variables exist in the stack
    for (i=0;i<args;i++){
        printf("-> %s\n", argv[i]);
    }

    // Then allocating memory for argv[1] items
    int size = charSize(argv[1]);
    int *array = (int*) malloc (size * sizeof(int));

    if (!array){
        printf("%s :Fatal Error not available memory\n",argv[0]);
        return -1;
    }

    for (i=0;i<size;i++){
        printf("-> %p : %d \n", array+i,*(array+i));
    }
    
    // So what to do with that memory?
    free(array);

    return 0;
}