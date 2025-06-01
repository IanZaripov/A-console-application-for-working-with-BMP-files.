# A console application for working with BMP files
____
## OVERVIEW: 
A class is being created that reads the BMP format (24 or 32 bits, no other formats are needed) and outputs two colors to the console in two different characters: black RGB(0, 0, 0) and white (background) RGB(255, 255, 255). Only pictures containing these two colors, small in size, should be submitted to the entrance. The STL library is used to read the BMP file. When the application is launched, it requests the full path/name of the input BMP file.:Enter input BMP file name: 1.bmp After displaying the image in the console, the application draws an X (cross) on this image using the line drawing function, which draws at two points (x1, y1), (x2, y2). And the modified image is output to the console again, and then saved to a new BMP file (its name is also requested).
____

### BUILDING AND RUNNING THE APP: 
Build the project using the following 4-line script:

+ mkdir build
+ cd build
+ cmake ..
+ cmake --build .  
Then for running the app:
+ cd Debug
+ bmp_proccessor.exe
____

#### Screenshots 
![Image](https://github.com/user-attachments/assets/c68fa8b1-3113-47e2-b858-9f987df6ac2e)
![Image](https://github.com/user-attachments/assets/0148e137-7b41-4750-af11-443b7ae181d7)
