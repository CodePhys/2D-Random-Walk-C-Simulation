*********************************************yonacosta.com*********************************************************************************************************************************
# This C program is a simulation of a random walk in a two-dimensional space, with additional features to check the normality (gaussianity) of the distribution of the walkers (or particles).

# The main components of the program include:

# Header Files:

stdio.h for standard input/output functions.
stdlib.h for memory allocation, random number generation, and other utility functions.
math.h for mathematical operations like square root.
Macro Definitions:

EXP is defined as 10, which is used for calculating the number of histograms.
ERR is a macro for an error message used when file opening fails.
#Struct Definition:

struct vet is a simple structure holding x and y integer coordinates for the walkers' positions.
#Global Variables and Structures:

File pointers pfa, pfc, and pfd for various files to write data.
pos, an array of struct vet to store the positions of each walker.
Various other variables for managing seeds, the number of trajectories, time steps, histograms, and statistical calculations.
#Random Walk Simulation:

The program takes two arguments for the maximum time (tms) and the number of trajectories (ntm).
It allocates memory for an array to store positions and for file pointers to manage files for outputting histograms.
It initializes a random number generator with a seed from /dev/random.
A loop then simulates the random walk for each trajectory, updating the x or y position based on a randomly generated probability.
It computes the distance of each step and updates the sum for mean, sum of squares, and sum of the fourth powers to use in statistical calculations.
For each time step where tmp is a power of 10, it writes positions to files intended for histogram data.
#File Writing:

It opens multiple files for writing:
traiettorie.dat for trajectories.
momenti_per_tempo.dat for the moments in time, storing the mean, standard deviation, mean of squares, and their respective standard deviations.
A series of files within a directory pos_al_tempo for histogram data at specific time intervals.
#Statistical Analysis:

After each time step, the program calculates the mean distance, standard deviation of the mean, mean of the squared distances, and standard deviation of the squared distances.
These statistics are then written to momenti_per_tempo.dat.
File Closure:

The program closes all the file pointers before exiting.
This code effectively simulates a random walk and tracks the path of each walker, allowing for the analysis of their spread over time and their conformity to a Gaussian distribution. The output files contain detailed data that can be used to analyze the random walk and to create histograms and other graphical representations of the walkers' positions.
