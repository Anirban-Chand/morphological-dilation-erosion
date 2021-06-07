"# morphological-dilation-erosion" 

These programs are command line programs.Steps to run ->
1. Go to the directory where your program resides
2. Open VScode in that directory or simply open CMD in that directory
3. If you opened cmd then run the commands ->
                                            1. g++ -o dil dilation.cpp
                                            2. dil.exe input_image.pbm output.pbm
4. If you opened VScode then in the 'Terminal Tab' click 'New Terminal'. Then run the previous line commands.


NOTE: 
If you are using GIMP for image processing, then you should be aware of few things. After exporting a PGM image file into PBM format one line is added within the pbm file. If you open the exported PBM file into notepad then you can see the line "Created with GIMP" or something like that. I haven't considered this line. So, better if you remove this from the text file and then use the the image for this programs.
