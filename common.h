/* 
 * common.h: First Fit Algorithm for Virtual Machine Placement - Common Functions
 * Date: 14-09-2018
 * Author: Petrônio Carlos Bezerra (petroniocg@ifpb.edu.br)
 * 
 * This code is based in imavmp.c developed by Fabio Lopez Pires, as follows
 * common.c: Virtual Machine Placement Problem - Common Functions
 * Date: 17-11-2014
 * Author: Fabio Lopez Pires (flopezpires@gmail.com)
 * Corresponding Conference Paper: A Many-Objective Optimization Framework for Virtualized Datacenters
 * Available at: https://github.com/flopezpires
*/

/* include libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* definitions */
#define H_HEADER "PHYSICAL MACHINES"
#define V_HEADER "VIRTUAL MACHINES"
#define TAM_BUFFER BUFSIZ

extern int number_vms_sc;

/* get the number of physical and virtual machines */
int get_h_size(char path_to_file[]);
int get_v_size(char path_to_file[]);

/* print matrix and array */
void print_int_matrix(int ** matrix, int rows, int columns);
void print_float_matrix(float ** matrix, int rows, int columns);
void print_int_array_line(int *array, int columns);
void print_float_array(float * array, int columns);
void print_int_array_line_file(int *array, int columns);
void print_float_array_line_file(float *array, int columns);
void print_int_matrix_file(int **matrix, int rows, int columns);

/* load datacenter physical resources and virtual requirements */
int** load_H(int h_size, char path_to_file[]);
int** load_V(int v_size, char path_to_file[], int CRITICAL_SERVICES);

/* load utilization of physical resources and costs of the considered objective functions */
int** load_utilization(int *population, int **H, int **V, int h_size, int v_size);
float *load_objectives(int *population, int **utilization, float *cm, int **H, int **V, int h_size, int v_size, int CRITICAL_SERVICES);
