
# Makefile on this project


```make``` : build the project

```make clear```  :  remove .o files therefore clearing the project

```make debug``` is not available on this project because gdb uses a value (SIGRTMIN) we are using, therefore creating a conflict.

To run project do the following steps:
1) build the project using make
2) run the output by doing ```./output.o``` in the repository.