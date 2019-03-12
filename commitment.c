/* 
 * commitment.c: Initialization of The Commitment Matrix
 * Date: 27-04-2018
 * Author: Petrônio Carlos Bezerra (petroniocg@ifpb.edu.br) 
*/

/* include libraries */
#include <stdio.h>
#include <stdlib.h>

/* include commitment header */
#include "commitment.h"

/* calculates_commitment: calculates the Commitment Matrix
 * parameter: population vector
 * parameter: number of physical machines
 * parameter: number of virtual machines
 * parameter: virtual machines requirements matrix
 * parameter: if the VM run Critical Services
 * returns: commitment matrix
*/
float *calculates_commitment(int *population, int h_size, int v_size, int **V, int CRITICAL_SERVICES)
{
	// iterators 
	int iterator_individual_position;
	int iterator_physical;

    //* commitment: initial Commitment Vector 
	float *commitment = (float *) malloc (h_size *sizeof (float));

	for (iterator_physical=0; iterator_physical < h_size; iterator_physical++)
	{
		//* Commitment Level of PMs initialized to 0 
		commitment[iterator_physical] = 0.0;
	}
	
	// iterate on positions of an individual
	for (iterator_individual_position = 0; iterator_individual_position < v_size; iterator_individual_position++)
	{
		// VM with indication of critical services != CRITICAL_SERVICES
		if (V[iterator_individual_position][3] != CRITICAL_SERVICES)
		{
			if (population[iterator_individual_position] != 0)
			{
				// Only change the Commitment Level if the PM was not set with Critical Services
				if (commitment[(population[iterator_individual_position])-1] != CL_CS)
					commitment[(population[iterator_individual_position])-1] = CL_NC;
			}
		}
		// VM with indication of critical services == CRITICAL_SERVICES
		else
		{
			if (population[iterator_individual_position] != 0)
				commitment[(population[iterator_individual_position])-1] = CL_CS;
		}
	}

	return commitment;
}
