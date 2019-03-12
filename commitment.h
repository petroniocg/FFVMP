/* 
 * commitment.h: Initialization of The Commitment Matrix
 * Date: 27-04-2018
 * Author: Petrônio Carlos Bezerra (petroniocg@ifpb.edu.br) 
*/


float *calculates_commitment(int *population, int h_size, int v_size, int **V, int CRITICAL_SERVICES);

#define CL_CS 1.0  // Commitment Level for PMs with Critical Services
#define CL_NC 2.0  // Commitment Level for PMs with No Critical services
