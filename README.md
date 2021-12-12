# List - a cache friendly list data structure with good security

 This project has basic functions for working with lists and graph dump

## Setup and run
    
    1) Create an empty directory, for example buildDir
    2) cd into buildDir
    3) run cmake 
    4) run make
    ~ now you have static libs in it and examples of usage in tools

## Graph dump

    Using function dumpDotList fills the file with the name in args, let it be "dotShit.dot", with instructions for dot program of graphviz
    Create a .png file for dot with *touch YOUR_NAME.png* (you can use other formats)
    Run dot with following arguments:
        -Tpng ~ sets the format to png (you can change it)
        -o YOUR_NAME.png ~ the file in which dot writes the graphic data
        dotShit.dot ~ the file with instructions for dot
        
    Run smth like 
        display YOUR_NAME.png
