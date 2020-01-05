#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>

/***********************************************************************
*******
  Demonstrating  how to crack an encrypted password using a simple
  "brute force" algorithm which works on passwords that consist  of 3
uppercase letters and a 2 digit integer. 

   To compile:
    cc -o CrackAZ99-With-Data CrackAZ99-With-Data.c -lcrypt -pthread

  To run the program:

    ./CrackAZ99-With-Data > results.txt

  
************************************************************************
******/
int n_passwords = 4;

char *encrypted_passwords[] = {
 "$6$KB$36REBSFzq1/dui1N6SgVpJNWbH7.H09nEmDF84hZhfeauI13ShDyaMT/d1tPMVh35NJKKkQrT6OIYDS9VLrIY0",
 "$6$KB$6KTEpYPrV1icVrMG2KG5eTSGzL5FsmSE1GDELpxrwVZR7Fq/CnE3qrX2hjYFTtnNUXi9EsM2E6zS7xWmNAlLL.",
 "$6$KB$fV8vnwDCivSwrIlyMYW2o.uwX6upgWi7snIIllfSEiAXbiCoD3F/Ld8E9ks7eI0I7XyABJ3fIx2SiyZrr8ovH1",
 "$6$KB$1XOuvrdjl2JYWtMyp.J0gJSEz8Q.p4ZrCCrGVD0FhvZnDWvFXRmuwpm/379fJfwf3Ug6LImgwfFESZWQRptSv0"
};

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the start of the line. Note that one of the most time consuming operations that
 it performs is the output of intermediate results, so performance experiments for this kind of program should not include this. i.e. comment out the
printfs.
*/

void crackpassthread()
{
  int i;
pthread_t t1, t2;

    void *kernel_function_1();
    void *kernel_function_2();
for(i=0;i<n_passwords;i<i++) {
   
    
    pthread_create(&t1, NULL,kernel_function_1, encrypted_passwords[i]);
    pthread_create(&t2, NULL,kernel_function_2, encrypted_passwords[i]);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
 }
}

void *kernel_function_1(char *salt_and_encrypted){
  int b, m, a;     // Loop counters
  char salt[7];    // String used in hahttps://www.youtube.com/watch?v=L8yJjIGleMwshing the password. Need space
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(b='A'; b<='M'; b++){
    for(m='A'; m<='Z'; m++){
      for(a=0; a<=99; a++){
        sprintf(plain, "%c%c%02d", b,m,a);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } 
      }
    }
  }
  printf("%d solutions explored\n", count);
}


void *kernel_function_2(char *salt_and_encrypted){
  int n, p, s;     // Loop counters
  char salt[7];    // String used in hahttps://www.youtube.com/watch?v=L8yJjIGleMwshing the password. Need space
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(n='N'; n<='Z'; n++){
    for(p='A'; p<='Z'; p++){
      for(s=0; s<=99; s++){
        sprintf(plain, "%c%c%02d", n,p,s);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}

//Calculating time

int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
 {
	  long long int ds =  finish->tv_sec - start->tv_sec; 
	  long long int dn =  finish->tv_nsec - start->tv_nsec; 

	  if(dn < 0 ) {
	    ds--;
	    dn += 1000000000; 
  } 
	  *difference = ds * 1000000000 + dn;
	  return !(*difference > 0);
}
int main(int argc, char *argv[])
{
  	
	struct timespec start, finish;   
  	long long int time_elapsed;

  	clock_gettime(CLOCK_MONOTONIC, &start);

  	
	
    		crackpassthread();
  	
	clock_gettime(CLOCK_MONOTONIC, &finish);
	  time_difference(&start, &finish, &time_elapsed);
	  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
		                                 (time_elapsed/1.0e9)); 
  return 0;
}
