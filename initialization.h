/* 
 * initialization.h: Virtual Machine Placement Problem - Initialization Stage
 * Date: 14-09-2018
 * Author: Petrônio Carlos Bezerra (petroniocg@ifpb.edu.br)
 * 
 * This code is based in imavmp.c developed by Fabio Lopez Pires, as follows
 * imavmp.c: Interactive Memetic Algorithm for Virtual Machine Placement (IMAVMP)
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

extern int number_alocated_vms;

/* function headers definitions */
int* initialization(int h_size, int v_size, int **V);

/* function headers definitions */
int *allocate(int *population, int **utilization, float *cm, int ** H, int ** V, int h_size, int v_size, int CRITICAL_SERVICES);
int is_overloaded(int **H, int **utilization, float *cm, int physical);
