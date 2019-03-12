/* 
 * common.c: First Fit Algorithm for Virtual Machine Placement - Common Functions
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

/* include common header */
#include "common.h"
#include "commitment.h"

/* get_h_size: returns the number of physical machines
 * parameter: path to the datacenter file
 * returns: number of physical machines
*/
int get_h_size(char path_to_file[])
{
	/* datacenter file to read from */
	FILE *datacenter_file;
	/* line readed from file */
	char input_line[TAM_BUFFER];
	/* number of physical machines */
	int h_size = 0;
	/* 1 if reading the physical machines block in the file */
	int reading_physical = 0;
 	/* open the file for reading */ 
	datacenter_file = fopen(path_to_file,"r");
    /* if it is opened ok, we continue */    
	if (datacenter_file != NULL) 
	{ 
		/* read until the end */
		while(!feof(datacenter_file)) 
		{
			/* get line per line */
			fgets(input_line, TAM_BUFFER, datacenter_file);
			/* if the line is equal to H_HEADER, we begin the physical machines block in the file */
			if (strstr(input_line,H_HEADER) != NULL)
			{
				reading_physical = 1;
			}
			/* if the line is equal to V_HEADER, we end the physical machines block in the file */
			if (strstr(input_line,V_HEADER) != NULL) 
			{
				reading_physical = 0;
				break;
			}
			/* if it is the correct block in the file, it is not the header and it is not a blank line, we count */			
			if (reading_physical == 1 && strstr(input_line,H_HEADER) == NULL && strcmp(input_line, "\n") != 0)
			{
				h_size++;
			}
		}
	}
	/* close the file */
	fclose(datacenter_file);
	/* return the value */
	return h_size;
}

/* get_v_size: returns the number of virtual machines
 * parameter: path to the datacenter file
 * returns: number of virtual machines
 */
int get_v_size(char path_to_file[])
{
	/* datacenter file to read from */
	FILE *datacenter_file;
	/* line readed from file */
	char input_line[TAM_BUFFER];
	/* number of virtual machines */
	int v_size = 0;
	/* 1 if reading the virtual machines block in the file */
	int reading_virtual = 0;
 	/* open the file for reading */
	datacenter_file = fopen(path_to_file,"r");
    /* if it is opened ok, we continue */
	if (datacenter_file != NULL) 
	{ 
		/* read until the end */
		while(!feof(datacenter_file)) 
		{
			/* get line per line */
			fgets(input_line, TAM_BUFFER, datacenter_file);
			/* if the line is equal to V_HEADER, we begin the virtual machines block in the file */
			if (strstr(input_line,V_HEADER) != NULL)
			{
				reading_virtual = 1;
			}

			/* if we are in the correct block in the file, it is not the header and it is not a blank line, we count */
			if (reading_virtual == 1 && strstr(input_line,V_HEADER) == NULL && strcmp(input_line, "\n") != 0)
			{
				v_size++;
			}
		}
	}
	/* close the file */
	fclose(datacenter_file);
	/* return the value */
	return v_size;
}

/* print_int_matrix: prints on screen a integer matrix
 * parameter: matrix to print
 * parameter: number of individuals
 * parameter: number of virtual machines
 * returns: nothing, it's void
*/
void print_int_matrix(int **matrix, int rows, int columns)
{
	/* iterators */
	int iterator_row;
	int iterator_column;
	/* iterate on rows */	
	for (iterator_row=0; iterator_row < rows; iterator_row++)
	{
		printf("ROW %d:\t",iterator_row);	
		/* iterate on columns */
		for (iterator_column = 0; iterator_column < columns; iterator_column++)
		{
			printf("%d ",matrix[iterator_row][iterator_column]);	
		}
		printf("\n");
	}
}

/* print_int_matrix_file: prints on file a integer matrix
 * parameter: matrix to print
 * parameter: number of individuals
 * parameter: number of virtual machines
 * returns: nothing, it's void
*/
void print_int_matrix_file(int **matrix, int rows, int columns)
{

	FILE *ffvmp_result;

	ffvmp_result = fopen("results/ffvmp_result","a");
	fprintf(ffvmp_result,"Utilization\n");

	/* iterators */
	int iterator_row;
	int iterator_column;
	/* iterate on rows */	
	for (iterator_row=0; iterator_row < rows; iterator_row++)
	{
		if (matrix[iterator_row][0] > 0)
		{
			fprintf(ffvmp_result,"ROW %d:\t",iterator_row);	
			/* iterate on columns */
			for (iterator_column = 0; iterator_column < columns; iterator_column++)
			{
				fprintf(ffvmp_result,"%d ", matrix[iterator_row][iterator_column]);	
			}
			fprintf(ffvmp_result, "\n");
		}
	}
	fprintf(ffvmp_result,"\n");
	fclose(ffvmp_result);
}


/* print_float_matrix: prints on screen a float matrix
 * parameter: matrix to print
 * parameter: number of individuals
 * parameter: number of virtual machines
 * returns: nothing, it's void
*/
void print_float_matrix(float **matrix, int rows, int columns)
{
	/* iterators */
	int iterator_row;
	int iterator_column;
	/* iterate on rows */	
	for (iterator_row=0; iterator_row < rows; iterator_row++)
	{
		printf("ROW %d:\t",iterator_row);	
		/* iterate on columns */
		for (iterator_column = 0; iterator_column < columns; iterator_column++)
		{
			printf("%g\t\t",matrix[iterator_row][iterator_column]);
		}
		printf("\n");
	}
}


/* print_int_array_line: prints on screen a int array
 * parameter: array to print
 * parameter: number of virtual machines
 * returns: nothing, it's void
*/
void print_int_array_line(int *array, int columns)
{
	/* iterators */
	int iterator_column;
	/* iterate on columns */
	for (iterator_column = 0; iterator_column < columns; iterator_column++)
	{
		printf("%d ", array[iterator_column]);	
	}
	printf("\n");
}


/* print_int_array_line: prints on file a int array
 * parameter: array to print
 * parameter: number of virtual machines
 * returns: nothing, it's void
*/
void print_int_array_line_file(int *array, int columns)
{
	/* iterators */
	int iterator_column;

	FILE *ffvmp_result;

	ffvmp_result = fopen("results/ffvmp_result","a");
	fprintf(ffvmp_result,"\n****** Solution P ******\n");

	/* iterate on columns */
	for (iterator_column = 0; iterator_column < columns; iterator_column++)
	{
		fprintf(ffvmp_result,"%d ", array[iterator_column]);	
	}
	fprintf(ffvmp_result,"\n***********************\n");
	fclose(ffvmp_result);
}

/* print_float_array_line_file: prints on file a float array
 * parameter: array to print
 * parameter: number of virtual machines
 * returns: nothing, it's void
*/
void print_float_array_line_file(float *array, int columns)
{
	/* iterators */
	int iterator_column;

	FILE *ffvmp_result;

	ffvmp_result = fopen("results/ffvmp_result","a");

	/* iterate on columns */
	for (iterator_column = 0; iterator_column < columns; iterator_column++)
	{
		fprintf(ffvmp_result,"[%d]: %g\t",iterator_column, array[iterator_column]);	
	}

	fprintf(ffvmp_result,"\n\n\n");
	fclose(ffvmp_result);
}


/* print_float_array: prints on screen a float array
 * parameter: array to print
 * parameter: number of columns
 * returns: nothing, it's void
*/
void print_float_array(float *array, int columns)
{
	/* iterators */
	int iterator_column;
	/* iterate on columns */
	for (iterator_column = 0; iterator_column < columns; iterator_column++)
	{
		printf("[%d]: %g\t",iterator_column,array[iterator_column]);	
	}
	printf("\n\n");
}

/* load_H: load the values of H
 * parameter: number of physical machines
 * parameter: path to the datacenter file
 * returns: H matrix
*/
int** load_H(int h_size, char path_to_file[])
{
	/* datacenter file to read from */
	FILE *datacenter_file;
	/* line readed from file */
	char input_line[TAM_BUFFER];
	/* iterator */
	int iterator = 0;
	/* 1 if is reading the physical machines block in the file */
	int reading_physical = 0;
	/* memory reserve for h_size physical machines */
	int **H = (int **) malloc (h_size *sizeof (int *));
 	/* open the file for reading */ 
	datacenter_file = fopen(path_to_file,"r");
    /* if it is opened ok, we continue */    
	if (datacenter_file != NULL) 
	{ 
		/* read until the end */
		while(!feof(datacenter_file)) 
		{
			/* get line per line */
			fgets(input_line, TAM_BUFFER, datacenter_file);
			/* if the line is equal to H_HEADER, we begin the physical machines block in the file */
			if (strstr(input_line,H_HEADER) != NULL)
			{
				reading_physical = 1;
			}
			/* if the line is equal to V_HEADER, we end the physical machines block in the file */
			if (strstr(input_line,V_HEADER) != NULL) 
			{
				reading_physical = 0;
				break;
			}
			/* if it's the correct block in the file, it is not the header and it is not a blank line, we count */			
			if (reading_physical == 1 && strstr(input_line,H_HEADER) == NULL && strcmp(input_line, "\n") != 0)
			{
				/* reserve 4 columns for Processor, Memory, Storage and Power Consumption */
				H[iterator] = (int *) malloc (4 *sizeof (int));
				/* load on the matrix and increment iterator */
				sscanf(input_line,"%d %d %d %d\n",&H[iterator][0],&H[iterator][1],&H[iterator][2],&H[iterator][3]);
				iterator++;
			}
		}
	}
	fclose(datacenter_file);
	return H;
}

/* load_V: load the values of V
 * parameter: number of virtual machines
 * parameter: path to the datacenter file
 * returns: V matrix
*/
int** load_V(int v_size, char path_to_file[], int CRITICAL_SERVICES)
{
	/* datacenter file to read from */
	FILE *datacenter_file;
	FILE *ffvmp_result;
	/* line readed from file */
	char input_line[TAM_BUFFER];
	/* iterator */
	int iterator = 0;
	/* 1 if is reading the virtual machines block in the file */
	int reading_virtual = 0;
	/* memory reserve for v_size virtual machines */
	int **V = (int **) malloc (v_size *sizeof (int *));
 	/* open the file for reading */ 
	datacenter_file = fopen(path_to_file,"r");
    /* if it is opened ok, we continue */    
	if (datacenter_file != NULL) 
	{ 
		/* read until the end */
		while(!feof(datacenter_file)) 
		{
			/* get line per line */
			fgets(input_line, TAM_BUFFER, datacenter_file);
			/* if the line is equal to V_HEADER, we begin the virtual machines block in the file */
			if (strstr(input_line,V_HEADER) != NULL)
			{
				reading_virtual = 1;
			}

			/* if it's the correct block in the file, it is not the header and it is not a blank line, we count */			
			if (reading_virtual == 1 && strstr(input_line,V_HEADER) == NULL && strcmp(input_line, "\n") != 0)
			{
				/* reserve 4 columns for Processor, Memory, Storage and Flag for Critical Service */
				V[iterator] = (int *) malloc (4 *sizeof (int));
				sscanf(input_line,"%d %d %d %d\n",&V[iterator][0],&V[iterator][1],&V[iterator][2],&V[iterator][3]);

				//Petronio: Nivel de Dispersao
				if (V[iterator][3] == CRITICAL_SERVICES)
					number_vms_sc++;

				iterator++;
			}
		}
	}
	fclose(datacenter_file);

	ffvmp_result = fopen("results/ffvmp_result","a");
	fprintf(ffvmp_result,"Number of CRITICAL VMs: %d (%.1f%%)\n", number_vms_sc, ((float)number_vms_sc / (float)v_size)*100.0);
	fclose(ffvmp_result);

	return V;
}

/* load_utilization: loads the utilization of the physical machines
 * parameter: population vector
 * parameter: physical machines matrix
 * parameter: virtual machines matrix
 * parameter: number of physical machines
 * parameter: number of virtual machines
 * returns: utilization matrix
*/
int **load_utilization(int *population, int **H, int **V, int h_size, int v_size)
{
	//* iterators 
	int iterator_virtual;
	int iterator_physical;
	
	//* utilization holds the physical machines utilization of Processor, Memory and Storage 
	int **utilization = (int **) malloc (h_size * sizeof (int *));

	//* requirements matrix, holds the sum of virtual machines requirements for each physical machine 
	int **requirements = (int **) malloc (h_size * sizeof (int *));


	for (iterator_physical=0; iterator_physical < h_size; iterator_physical++)
	{
		//* virtual machine requirements in Processor, Memory and Storage. Initialized to 0 
		requirements[iterator_physical] = (int *) malloc (3 * sizeof (int));
		requirements[iterator_physical][0] = requirements[iterator_physical][1] = requirements[iterator_physical][2] = 0;

		//* physical machine utilization of Processor, Memory and Storage. Initialized to 0 
		utilization[iterator_physical] = (int *) malloc (3 * sizeof (int));
		utilization[iterator_physical][0] = utilization[iterator_physical][1] = utilization[iterator_physical][2] = 0;
	}
	return utilization;
}


/* load_objectives: calculates the cost of each objective of each solution
 * parameter: population vector
 * parameter: utilization matrix
 * parameter: commitment matrix
 * parameter: physical machines matrix
 * parameter: virtual machines matrix
 * parameter: number of physical machines
 * parameter: number of virtual machines
 * returns: cost of each objetive matrix
*/
float *load_objectives(int *population, int **utilization, float *cm, int **H, int **V, int h_size, int v_size, int CRITICAL_SERVICES)
{
	int iterator_virtual;
	int physical_position;
	int iterator_physical;
	int found_critical, found_no_critical;

	float power_consumption;

	/* utility of a physical machine */
	float utilidad, total_used_cpu, total_used_memory;
	float total_cpu, total_memory;

	int total_pm_CS, total_pm_NCS, total_pm_ON;

	/* value solution holds the cost of each solution of Energy and Dispersion */
	float *value_solution = (float *) malloc (2 *sizeof (float));

	power_consumption = 0.0;
	total_cpu = total_used_cpu = 0.0;
	total_memory = total_used_memory = 0.0;
	value_solution[0] = value_solution[1] = 0.0;

	total_pm_CS = total_pm_NCS = total_pm_ON = 0;

	FILE *ffvmp_result;

	/* Calculates the Energy Consumption of solution */
	/* iterate on physical machines */
	for (iterator_physical = 0 ; iterator_physical < h_size ; iterator_physical++)
	{
		if (utilization[iterator_physical][0] > 0)
		{
			/* calculates utility of a physical machine */
			utilidad = (float) utilization[iterator_physical][0] / (float) H[iterator_physical][0];

			/* calculates energy consumption of a physical machine */
			power_consumption += ( (float) H[iterator_physical][3] - ( (float) H[iterator_physical][3] * 0.6) ) * utilidad + 
			( (float) H[iterator_physical][3] * 0.6 );

			found_critical = found_no_critical = 0;
			total_pm_ON++;

			if (CL_CS == CL_NC)
			{
				for (iterator_virtual = 0; iterator_virtual < v_size; iterator_virtual++)
				{
					if (population[iterator_virtual]-1 == iterator_physical)
					{
						if ( V[iterator_virtual][3] == CRITICAL_SERVICES )
							found_critical++;
						else
							found_no_critical++;
					}
					if (found_critical > 0 && found_no_critical > 0)
						break;
				}

				if( found_critical > 0 )
					total_pm_CS++;
				if( found_no_critical > 0 )
					total_pm_NCS++;
			}

			else
			{
				if (cm[iterator_physical] == CL_CS)
				{
					total_pm_CS++;

					for (iterator_virtual = 0; iterator_virtual < v_size; iterator_virtual++)
					{
						// If there is VM with NCS in the PM, add +1 and break
						if ( (population[iterator_virtual]-1 == iterator_physical) && V[iterator_virtual][3] != CRITICAL_SERVICES)
						{
							total_pm_NCS++;
							break;
						}
					}

				}
				else
					total_pm_NCS++;
			}
		}
	}

	ffvmp_result = fopen("results/ffvmp_result","a");
	fprintf(ffvmp_result,"\nPM_CS = %d, PM_NCS = %d, PM_ON = %d, VMs_NCS = %d\n", total_pm_CS, total_pm_NCS, total_pm_ON, v_size - number_vms_sc);
	fprintf(ffvmp_result,"\nCL_CS = %.1f , CL_NCS = %.1f\n\n", CL_CS, CL_NC);
	fclose(ffvmp_result);

	/* loads energy consumption of each solution */
	value_solution[0] = power_consumption;

	/* Calculates the Dispersion Level of each solution */
	if (total_pm_CS != 0 && total_pm_NCS != 0)
		value_solution[1] = ( (float)total_pm_CS / ( ((float)number_vms_sc/(float)total_pm_CS) + ( ((float)v_size - (float)number_vms_sc) / total_pm_NCS ) ) );
	else
	{
		if (total_pm_CS == 0)
			value_solution[1] = ((float)(v_size - (float)number_vms_sc) / (float)total_pm_NCS);
		else
			value_solution[1] = ((float) number_vms_sc / (float)total_pm_CS);
	}

	return value_solution;
}

