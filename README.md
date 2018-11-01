# qsort-parallel

This project is for an assignement for the **Parallel and Distributed Computer Systems** lesson at the **Aristotle University of Thessaloniki**.
The goal is to write parallel programs that apply the quicksort algorithm, with `Cilk`, `openMP` and `pthread` and compare them with each other and with the sequnetial.

The results and the code explanation are in the Report.pdf

You can clone the project, to test the times for your system.
    - Cilk program was compiled with `icc`, so if it's not available you can change the compiler to `gcc` in the `Makefile`, but expect slower results.

There are 2 python scripts that run all the programs with different parameters. They use `python3` and the `pandas` and `numpy` libraries to export the data to `.csv`. 

There are also R script files, to read the `csv`s and create the plots, and Rmd (Rmarkdown) files to create the `pdf`
If you wish to run them, you should set the working directory `/path-the-project-was-cloned/qsort-parallel/Results/Rscripts/rmarkdown`.

As long as the folder structure remains intact, there shouldn't be any problems with the paths.