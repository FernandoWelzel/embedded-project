# embedded-project

In this project, students will develop a demonstrator based on a RISC-V softcore, implemented on a FPGA. To do so, the students will have to develop, test and integrate different software components, inspired by the practical work done on the Rocket Chip platform in the implemented softcore.

# Project description

- Bootloader: Jumps to the SD card, DDR or ...
- We need to make the code that goes into the SD only
- Interface with FPGA:
    - Right-Left: Switches images
    - Up-Down: Switches filter and CNN (image + label)

# Project files

All files are in Project_SE.tar.gz. Compilation should be done in the virtual machine. The files that we have to change are mostly in lowric_DATE2020/fpga/bare_metal/examples. We have to change the application.c.

# Project steps

- [ ] Reading images from the SD card
- [ ] Image pre-processing
- [ ] Image display ("bypass" filter)
- [ ] Development of the Sobel filter
- [ ] Development of the Convolutional Neural Network (CNN) CIFAR-10
- [ ] Interruption via push button
- [ ] Bonus
