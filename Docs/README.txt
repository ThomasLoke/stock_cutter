README for stock_cutter
Author: Thomas Loke

//////////////////////////////////////////////////////////////////////////

1) Big picture

Howdy!! The purpose of this project is a simple one - given a *.csv (comma-separated file, viewable in Excel or any plain text editor) that specifies a list of cutting stock problems, the program stock_cutter.exe produces a corresponding file *-solution.csv, which outlines the solution (that is, the configuration that minimises wastage of stock material while supplying enough of each order as specified) to each of the cutting stock problems separately.

For the complete mathematical details, refer to Description.pdf.

//////////////////////////////////////////////////////////////////////////

2) Input *.csv file

This file specifies one or more cutting stock problems for the program to solve. Only the first two columns of the file are read. Each problem must follow the format shown (commas separate columns):

Length of stock material, <+ve integer value>
Order width, Order quantity
<+ve integer value less than length of stock material>, <+ve integer value>
...
<+ve integer value less than length of stock material>, <+ve integer value>
-,-

Refer to example.csv for a more concrete example of a two-problem input file.

//////////////////////////////////////////////////////////////////////////

3) stock_cutter program

The executable file requires you to input the name of the input *.csv file without the file extension (e.g. example.csv is entered as: example). The input *.csv file is required to be in the same directory as the executable file. Refer to section 5 for troubleshooting tips.

Once the program is done executing, it'll say so - then just type smth random and hit enter and it should close.

//////////////////////////////////////////////////////////////////////////

4) Output *-solution.csv file

This file reports all the relevant details regarding the solution to each of the cutting stock problems in the input file. Format is quite self-explainatory - see the example output file example-solution.csv for details.

//////////////////////////////////////////////////////////////////////////

5) Troubleshooting

- Oh noes! The program has missing libraries (.dll files)! What do??
-> You'll need to install the "Microsoft Visual C++ Redistributable Packages for Visual Studio 2015" - available from https://support.microsoft.com/en-us/kb/2977003

- Oh noes! The program can't open the input or output file! What do??
-> Check to make sure the input file is in the same directory as the program.
-> Check to make sure that the input and output files are not open in any other application before running the program.

- Oh noes! The program is still running after so many minutes! What do??
-> The runtime of the program still hasn't been properly measured yet. It is highly dependant on the ratio (Length of stock material) / (Smallest order width) - if this is too high, the runtime will be inflated (with no guarantee of finding a solution in a reasonable amount of time). However when the ratio is not unreasonably high, then it should be able to find a solution faster than you can say 'quack'!

- Oh noes! The program seems to crash when reading the input *.csv file! What do??
-> Check the formatting of your input *.csv file - and make sure you remember the '-' separators after each cutting stock problem!

- Oh noes! Woe is me - troubles beset me in life! What do??
-> Cast all your cares on Jesus, for His yoke is easy and His burden light.

//////////////////////////////////////////////////////////////////////////

6) Acknowledgements

Uses open-source linear programming libraries from http://www.coin-or.org/ - specifically CBC and its dependencies. Distributed under the Eclipse Public License.

Also thanks to internet for letting me rip off some text parsing functions.