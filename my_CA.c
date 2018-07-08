/* 
 * File: my_CA.c
 * 
 * Author: Albert Jozsa-Kiraly
 * 
 * Implementation of a one-dimensional cellular automaton (1dCA). 
 * It uses arrays, pointers, as well as dynamic memory allocation to manage 
 * the 1dCA, and prints successive generations. * 
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "memcheck.h"

/* Function declarations */
void update_a(int *generation, int length);
void update_p(int *generation, int length);

/**
 * update_a: Takes an array storing a generation of 1dCA, and the length. 
 *           Copies the generation, and, using array operations, it creates the 
 *           next generation which is printed to the screen.
 * 
 * Parameters:
 *        generation - the array storing a generation of 1dCA
 *        length - the length of the generation (number of cells)
 */
void update_a(int *generation, int length) 
{    
    int i, j, k; /* Loop control variables */
    
    /* Declare generation_copy and allocate memory for it */
    int *generation_copy; 
    generation_copy = (int*) calloc(length, sizeof (int));
    
    /* Check that the calloc call succeeded */
    if(generation_copy == NULL) {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1); 
    }

    /* First and last elements are always zero */
    generation_copy[0] = 0;
    generation_copy[length - 1] = 0;

    /* Copy the elements of generation to generation_copy 
   (except the first and last element). */
    for (i = 1; i < length - 1; i++) {
        generation_copy[i] = generation[i];
    }

    /* Loop and check the elements of the generation_copy array 
    (except the first and last element). */
    for (j = 1; j < length - 1; j++) {
        
        /* If the current cell of generation_copy is empty (0), and one (not both)
        of the two adjacent cells is full (1), set the current cell of the 
        generation array to be full.*/
        if ((generation_copy[j - 1] == 1 && generation_copy[j] == 0 &&
             generation_copy[j + 1] == 0) ||
            (generation_copy[j - 1] == 0 && generation_copy[j] == 0 &&
             generation_copy[j + 1] == 1)) {
            
            generation[j] = 1;
        } else { 
            /* Otherwise, the current cell of generation becomes empty. */
            generation[j] = 0; 
        }
    }

    /* Print the elements of generation_copy. 
    Print . if an element is 0, or * if an element is 1 */
    for (k = 0; k < length; k++) {
        if (generation_copy[k] == 0) {
            printf(".");
        } else {
            printf("*");
        }
    }
    printf("\n");

    /* Free the allocated memory */
    free(generation_copy);
}

/**
 * update_p: Takes an array storing a generation of 1dCA, and the length.  
 *           Copies the generation, and, using pointer arithmetic, it creates 
 *           the next generation which is printed to the screen.
 * 
 * Parameters:
 *        generation - the array storing a generation of 1dCA
 *        length - the length of the generation (number of cells)
 */
void update_p(int *generation, int length) 
{    
    int i; /* Loop control variable */

    /* The pointer p_gen points to the second element of generation because
    the first element is always zero. */
    int *p_gen = &generation[1];

    /* Declare generation_copy and allocate memory for it */
    int *generation_copy; 
    generation_copy = (int*) calloc(length, sizeof (int));
    
    /* Check that the calloc call succeeded */
    if(generation_copy == NULL) {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1); 
    }

    /* First and last elements of generation_copy are always zero */
    *generation_copy = 0;
    *(generation_copy + length - 1) = 0;

    /* Copy the elements of generation to generation_copy 
    (except the first and last elements). */
    for (i = 1; i < length - 1; i++) {
        *(generation_copy + i) = *(generation + i);
    }

    /* The pointer p_gen_copy points to the second element of generation_copy
    because the first element is always zero. */
    int *p_gen_copy = &generation_copy[1];

    /* Loop and check each element p_gen_copy is pointing to. */   
    while(p_gen_copy < &generation_copy[length]) {
        
        /* If the current element p_gen_copy is pointing to is empty (0), and 
        one (not both) of the two adjacent cells is full (1), set the current 
        cell p_gen is pointing to, to be full. */
        if (((*(p_gen_copy - 1) == 1) && (*p_gen_copy == 0) &&
             (*(p_gen_copy + 1) == 0)) ||
            ((*(p_gen_copy - 1) == 0) && (*p_gen_copy == 0) &&
             (*(p_gen_copy + 1) == 1))) {
            
            *p_gen = 1;
        } else { 
        /* Otherwise, the current cell p_gen is pointing to becomes empty. */
            *p_gen = 0;
        }

        /* Increment the pointers so they point to the next elements. */
        p_gen_copy++;
        p_gen++;
    }
    
    /* Print the values pointed to by p_gen_copy. 
    Print . if an element is 0, or * if an element is 1  */
    for(p_gen_copy = &generation_copy[0]; 
                        p_gen_copy < &generation_copy[length]; p_gen_copy++) {
        if (*p_gen_copy == 0) {
            printf(".");
        } else {
            printf("*");
        }
    }
    printf("\n");

    /* Free the allocated memory */
    free(generation_copy);
}

/*
 * main: This is the main function which takes arguments from the command line,
 *       creates an array representation of a one-dimensional cellular automaton 
 *       with random numbers of 0 and 1, and uses array operations or 
 *       pointer arithmetic to produce further generations.
 * 
 * Parameters:
 *        argc - the number of command line arguments
 *        argv - the array storing the command line arguments
 * 
 * Returns: 0
 */
int main(int argc, char** argv) 
{
    if (argc != 4) {
        fprintf(stderr, "Usage:  %s [a|p] length generations\n"
                "  where:\n "
                "    a - execute with array operations\n "
                "    p - execute with pointer arithmetic\n "
                "    length - specify the number of cells in the 1dCA\n "
                "    generations - specify the number of generations to compute\n ",
                argv[0]);
        exit(EXIT_FAILURE);
    }

    int i, j, k; /* Loop control variables */

    /* Store the length (number of cells in a generation) */
    int length = atoi(argv[2]);

    /* Store the number of generations to compute */
    int generations = atoi(argv[3]);

    /* Declare one_d_ca and allocate memory for it */
    int *one_d_ca; 
    one_d_ca = (int*) calloc(length, sizeof (int));
    
    /* Check that the calloc call succeeded */
    if(one_d_ca == NULL) {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1); 
    }

    /* First and last elements of one_d_ca are always empty */
    one_d_ca[0] = 0;
    one_d_ca[length - 1] = 0;

    /* Seed the random number generator */
    srand(time(NULL));
    
    /* Generate random numbers between 0 and 1 and assign them as cell values */
    for (i = 1; i < length - 1; i++) {
        one_d_ca[i] = rand() % 2;
    }
    
    printf("This is the original 1dCA:\n");    
    for (j = 0; j < length; j++) {
        printf("%d", one_d_ca[j]);
    }
    printf("\n");

    /* Switch statement to choose between execution types. It is either array 
    operations or pointer arithmetic that is used. Print as many generations 
    as the user has asked for. */
    switch (argv[1][0]) {
        case 'a':
            printf("You asked for using array operations.\n"
                    "The original 1dCA and the next %d generations are printed "
                    "below.\n", generations);

            /* Loop until generations + 1, because we want to print the original
            one_d_ca and then the next generations. */
            for (k = 0; k < generations + 1; k++) {                
                update_a(one_d_ca, length); 
            }
            break;
        case 'p':
            printf("You asked for using pointer arithmetic.\n"
                    "The original 1dCA and the next %d generations are printed "
                    "below.\n", generations);

            /* Loop until generations + 1, because we want to print the original
            one_d_ca and then the next generations. */
            for (k = 0; k < generations + 1; k++) {                
                update_p(one_d_ca, length);
            }
            break;
        default:
            printf("Only 'a' for array operations or 'p' for pointer arithmetic"
                    " are allowed.\n");
            ;
    }
    /* Free the allocated memory for one_d_ca */
    free(one_d_ca);
    
    /* Check for memory leaks */
    print_memory_leaks(); 

    return 0;
}