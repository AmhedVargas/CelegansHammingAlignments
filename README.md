# *C. elegans* Hamming Alignments
C++ code that allows the calculation of the hamming distance on a parallel schema.

# Structure of repository
* src/read_mRNA_hamming_omp.cpp `c++ code that takes query sequences and aligns them versus a dictionary. The program only reports the number of hits up to 5MM, i.e. a distance equal to 5`
* src/read_mRNA_hamming_omp_fm.cpp `c++ code that takes query sequences and aligns them versus a dictionary. The program reports the full matrix of alignements; please be conscious about RAM limitations`
* examples/queries.txt
* examples/dictionary.txt

# Compiling the code
Use any c++ compiler, e.g. [g++](https://man7.org/linux/man-pages/man1/g++.1.html), with the argument -fopenmp active; this indicates to the compiler that the openmp library should be used for the compilation.

# Running the code
Place in the same directory as the compiled program a text file named `queries.txt` that will contain the input sequences. Similarly, add one file named `dictionary.txt` containing the sequences to align to. Example files can be found in the `example` directory. 
