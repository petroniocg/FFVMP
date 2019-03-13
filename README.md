# The First Fit Algorithm for Virtual Machine Placement (FFVMP) with Oversubscription

This software makes the Virtual Machines (VM) placement considering the oversubscription of the Physical Machines (PM).

This FFVMP approach was developed to be compared with VMPOS (also available at https://github.com/petroniocg) another approach of VM placement, using the informations of Energy Consuption and a parameter called Dispersion.

The FFVMP receives a Datacenter (DC) text file as input with the resources of the machines (physical and virtual) and generates a positioning of all the VMs in the PMs, applying different levels of commitment (oversubscription). In addition, two different types of VMs are considered, both critical and non-critical.

To the placement, the FFVMP take the VMs in sequence and try to allocate them in sequence of the PMs. When the resources of one PM (considering the oversubscription applied) is not sufficient, the FFVMP try to allocate the VM in the next PM, and so on.

## Operation:

_a)_ The datacenter file, with settings of the PMs, as well as the requirements of the VMs, must be passed (here we have one example in **/input** folder) as input to the FFVMP.

The datacenter file must have the following structure (the text part, which separates PMs from VMs, is fixed and must exist):
<br>
<br>
PHYSICAL MACHINES
<br><br>
12	512	10000	1000<br>
16	1024	10000	1300<br>
10	512	10000	1000<br>
8	1024	10000	1300<br>
<br>
VIRTUAL MACHINES
<br><br>
4	15	80	1<br>
8	30	160	0<br>
2	4	32	1<br>
4	8	80	0<br>
8	15	160	1<br>
4	30	320	0<br>
2	60	640	1<br>
2	15	32	0<br>
<br>
<br>
Let's call this datacenter file of **4x8.vmp** that is a datacenter with 4 PMs and 8 VMs. The 4 existing lines in the PMs part indicate the resources values for each of the PMs in datacenter. And the sequence in each line represents, respectively: Number of Processors (in the example of the first line, 12), Memory Quantity (in the example of the first line, 512), Disk Capacity (in the example of the first line, 10000) and Energy Consumption (in the example of the first line, 1000). Each row is associated with the resources available from one PM.

The 4 columns in the lines of the VMs part indicate the possible values for required resources by each of VMs in the datacenter. The sequence of these 4 columns represents, respectively: Number of Virtual Processors (in the example of the first line, 4), Memory Amount (in the example of the first line, 15), Disk Capacity (in the example of the first line, 80) and the flag that indicates if the VM run critical services (1) or not (0).

If you want to try another datacenters configurations try to use the SIMULATOR software, available at https://github.com/petroniocg/simulator, that generates random datacenters with the number of PM and VMs you want.

_b)_ Executing: With the DC file ready, the FFVMP is executed as follows:


```sh
$ ./ffvmp input/4x8.vmp
```

where, **4x8.vmp** was the name given to the file with the datacenter configuration.

_c)_ The program will generate a file in the folder **/output** with the name **ffvmp_result** which has many informations about the results and, of course, the placement indication. With this example, the placement result is like this:

****** Solution P ******<br>
1 1 2 2 2 3 2 3<br>

In this result, the numbers (1, 2 and 3) are the PMs, so from the 4 PMs available the FFVMP placed the VMs in 3 PMs. The position of the number, from left to right, indicates which VM is allocated in which PM. So, the VMs 1 and 2 are in PM 1. The VMs 3, 4, 5 and 7 are in PM 2. And the VMs 6 and 8 are in the PM 3.

## Modifications:

If you want to adapt the code to your needs, the compilation command to be used is:

```sh
$ gcc -o ffvmp ffvmp.c initialization.c common.c commitment.c -g -lm
```

The oversubscription is applied on PMs through two constants, CL_CS (*Commitment Level for Critical Services*) and CL_NC (*Commitment Level for No Critical Services*) that are configured in in the *commitment.h* file. The current code is using CL_CS = 1.0 and CL_NC = 2.0.

This means that the resources available in the PMs will be multiplied by 1.0 (CL_CS) when it is hosting **at least one VM configured as with critical services**, and that the resources in the PMs will be multiplied by 2.0 (CL_NC) when is hosting **only VMs with non-critical services**.
