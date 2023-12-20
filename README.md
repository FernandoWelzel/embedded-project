# embedded-project

In this project, students will develop a demonstrator based on a RISC-V softcore, implemented on a FPGA. To do so, the students will have to develop, test and integrate different software components, inspired by the practical work done on the Rocket Chip platform in the implemented softcore.

# Compilation

- Go to lowrisc_DATE2020 and source set_env.sh
- Go to TPSoC_Resources/TP3ANew and source sourceme.sh

# Technical description

- Bootloader: Jumps to the SD card, DDR or ...
- We need to make the code that goes into the SD only
- Interface with FPGA:
    - Right-Left: Switches images
    - Up-Down: Switches filter and CNN (image + label)
- FPGA Boards: A7-2; A7-3

# On - 25/01/2024 14h

- Report: 
  - Explaining each task, organization chosen, the files with README.md and the competences.
  - Put measurements of latency, etc... and the analysis that goes with. 
- Slides
- Live demo

# Project steps + Gannt

Until the Gannt diagram isn't ready consider the deadline of your individual functions to be 16/01/2024. 

- [ ] Individual
  - [ ] Reading images from the SD card (Fernando)
  - [ ] Image pre-processing (Ikram)
  - [ ] Image display ("bypass" filter) (Wissal) 
  - [ ] Development of the Sobel filter (Luca)
  - [ ] Development of the Convolutional Neural Network (CNN) CIFAR-10 (Melissa and Ayat) 
- [ ] Integration
  - [ ] Interruption via push button 
- [ ] Bonus

 # Instructions to modify

 The application.c file has been divided into a lot of different files that can all be found into `src/application/src/`. Please modify ONLY the files in this folder in order for our work not to affect the others dramatically. Put the function definitions into the `src/application/include/` directory in the respective file. 

 Until now, the complete Makefile is not working. For that reason, test your code by adding a test in the `test` directory and compiling it using `g++`. For example, run the following code with a few modifications:

'''sh
g++ test/application/test_display.c src/application/src/display.c
./a.out
'''

Try to delete the compiled executable that you've created before commiting.