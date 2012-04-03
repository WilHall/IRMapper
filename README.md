# About
IRMapper is an Arduino program to quickly map out the functions of IR devices. The program uses the serial monitor and an IR receiver component to generate parallel arrays of IR codes and button names.

# Dependencies
 * [http://www.arcfn.com/2009/08/multi-protocol-infrared-remote-library.html]()	

# Usage

 1. Open the *Serial Monitor*
 2. Turn on the sending of *newline* character
 3. Enter an arbitrary value to begin the interactive prompt

The prompt will bring you through the rest of the process. When asked for the number of buttons, enter the number of buttons, or IR codes, you want to map.

For example, if you're mapping a remote with 27 buttons, enter the integer 27. The program will then ask you to press each button, and give you the opportunity to enter a name for each button.

The output after all the buttons have been entered is two parallel C-style arrays, one for button names, and one for values, thus automating the process of mapping out IR devices by hand.