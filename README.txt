This project is a command line tool for image encryption and decryption. It allows users to convert images into .txt files
which include the image data in an encrypted form using an encryption key, and also turn those .txt files back to the original
images.



How does the encryption work?

The user inputs an image path, and the program reads all of it's RGB values. The user also provides the program with
a key, which will be used later for the decryption.
The program then goes over every RGB value of the image, and formats this string:

[RGB VALUE]-[KEY]-{[Y],[X]}

RGB VALUE -> the current RGB value
KEY -> the encryption key
Y -> the current pixel's Y coordinates
X -> the current pixel's X coordinates

each of those strings, will be hashed and saved inside a new .txt file, in the same order of the RGB values in the original image.
That's it, the image data is now saved inside a .txt file, looking like straight gibberish - image is encrypted.



How does the decryption work?

The user inputs the encrypted image path (.txt) and also the encryption key. The program reads the whole text from the .txt file,
and goes over each hashed string one by one. (The hashed strings are separated by spaces, because a hashed string will never have
a space inside of it, which makes it a reliable separator).

The program then reformats the original string for each hashed string, hashes it, and compares the two hashed strings.
The program knows the key, since the user inputted it, and it also knows the X & Y coordinates - since the RGB values are saved inside the .txt file
in  the original order. The only thing left for the program to find out is the RGB value.
If the two hashed strings don't match, the program will increase the RGB value and try again, until the two strings will match, which will determine the
current correct RGB value.

If the program will go over all possible values (0 - 255) and not find any matches - it will give up on the decryption, as the given key is wrong.

Eventually, the program will find ALL of the RGB values, and simply create a new .png file.

In order to make the decryption more efficient, the program uses the Spatial Redundancy principle.
This principle says that in most images (especially natural images), the RGB values of two nearby pixels will most likely be very close to each other - which
can help us make the decryption way faster.

When the program will try to find the next RGB value, it wont start from 0, and go all the way up to 255, as it will probably take a lot of time and cause the program
to hash many strings. Instead, the program will check the last pixel's RGB values, and start trying from there, each failure going 1 value up, and then 1 value down.

This makes the decryption WAY faster. Imagine an image of a blue sky - yes the whole image together has different shades of blue inside of it, but when you look closely,
each pixel's RGB values, are almost the same as the pixel next to it (maybe with tiny changes). So when we decrypt the image, and we reach a certain pixel, we wont start
checking it's RGB values from 0, we will look at the pixel next to it (which we already decrypted), and start from it's RGB values - which can save us more then 100 hashes per RGB value,
which can save us more then 150,000,000 hashes per image (600 X 800). That saves us a lot of computing power, and time.

This trick also works well on cars, clothes, walls, screenshots and people too - those are all just large groups of pixels sitting next to each other, and having VERY close RGB values.





Even with all improvements to the algorithm, the encryption & decryption is still a bit slow - can take up to a few minutes.

Thanks for checking out this project.