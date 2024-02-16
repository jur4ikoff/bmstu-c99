#include <stdio.h>
#include <math.h>

int main(){
    float sum = 0.0, input_element;
    int count = 1;

    printf(">>Input numbers \n");

    while (1) {
        scanf("%f", &input_element);
        if (input_element <= 0)
            break;
        
        sum += input_element / count;
        count++;
    }

    float result = sqrt(sum);
    printf("Result:  %f\n", result);
}


/*
jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./9.exe
>>Input numbers
1
2
3
4
-1
Result:  2.00000

jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./9.exe
>>Input numbers
10 
10 10
210
2100
01
-1
Result:  22.158520

jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./9.exe
>>Input numbers
10 10
-1
Result:  3.872983

jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./9.exe
>>Input numbers
10 10 -10
Result:  3.872983
*/