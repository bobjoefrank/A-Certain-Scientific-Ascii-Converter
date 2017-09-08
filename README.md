# A Certain Scientific Ascii Converter

An extension to a video editing program. Takes a .yuv video file and outputs the ascii equivalent of each frame into a text file.
The file is opened in Microsoft Word and is played as an animation.

You can view a full sample video here: https://www.youtube.com/watch?v=BdwJfN3H1k0

This project was inspired by: http://www.bilibili.com/video/av8373756/?from=search&seid=12871251435183058499

## Foreword

The outputted text file is format specific to be opened in Microsoft word version 15 for Mac. I have not tried it in any other versions.
To display the file properly, please follow the exact format guidelines. 

## Usage

You will first need to download [ffmpeg](https://www.ffmpeg.org/) which is an program used for handling
multimedia data. 
After you have done that, we first need to render the video to a lower resolution on the command line using

```
ffmpeg -i videoname.mp4 -vf scale=170:66 outputname.mp4
```

Then we will convert it to our desired format yuv420p.

```
ffmpeg -i outputname.mp4 -c:v rawvideo -pix_fmt yuv420p someothername.yuv
```

After you create the .yuv file, make sure you write down the frame count that is outputted into the terminal as we will
need it later. Move the .yuv file to the same directory as the program and use the make command to generate the executable

```
make
```

Run the program using which will output a .yuv file and .txt file.

```
./MovieLab -i (file name without .yuv extension) -o (output file name) -f (frame count from earlier) -s 170x66 -ascii
```

Open the text file into Microsoft Word and format it accordingly:

```
font:consolas font_size:8 line_spacing:multiple_at:0.7 zoom:100% margins:0"0"0"0" orientation:landscape document_type:executive
```

Type into the Microsoft Word search bar for the "&" character and hold enter. You should see your document as a smooth, flowing animation.


