# Command line based interface for pco.1600

## Usage
To run the script with input parameters you need **PowerShell**.
Within it one can run the script in several ways, but two arguments should be given:
the first one is the path to a configuartion file,
the second is the path for output.
```sh
PS > .\GetImage_CamRun.exe C:\Users\muonbpm\cfg.txt C:\Users\muonbpm\test.bin
PS > "C:\Program Files (x86)\Digital Camera Toolbox\pco.sdk\bin64\GetImage_CamRun.exe" C:\Users\muonbpm\cfg.txt C:\Users\muonbpm\test.bin
```
Or you can make a link and use it:
```sh
PS > .\GetImage_CamRun.lnk C:\Users\muonbpm\cfg.txt C:\Users\muonbpm\test.bin
PS > .\GetImage_CamRun.lnk cfg.txt test.bin
```
The script reads the input configure file and tunes the CCD camera, and then takes image.
As an output at the end the script shows the time spend on data taking and the number of failed pictures.

As one can see the camera is manipulated by configuration files.


### Configuration file
A configuration file is a text file with several lines.
Each line contains a parameter's name and parameter's value separated by one space.
For example:
```txt
Exposure 8
ExposureBase 2
NumberOfPictures 1
```
If some parameter isn't specified in the configuration file then it will be set to default value.

The configuration can be written by hand or copied and modified.
Or the script *mkcfg.py* may be used.
*mkcfg.py* cosumes set of option--value(s) and produces a configuration file.
Example:
```sh
PS > python mkcfg.py texp 8 texpbase 2 npics 10 fout cfg_example.txt
```
To get help (two ways):

```sh
PS > python mkcfg.py texp 8 texpbase 2 npics 10 fout cfg_example.txt help
PS > python mkcfg.py help
```

### Output data
Output data a picture or set of pictures.
Each picture is represented by the sequence of pixel.
Each pixel corresponds to two bytes.
The **pco.1600** camera has a 14 bit range.
So,  from these two bytes,  two lowest bits are dumb.
There are not a header, spacing between pictures, or ending in the file body.
For example, if one takes one picture without additional binning,
*i. e.* the resolution is 1600 x 1200,
then the size of the file is 2 x 1600 x 1200 = 3840000 bytes.

To convert data one can use *raw2root.C*,
which used as:
```sh
$ root -b -q 'raw2root.C+(input, output, binning_X, binning_Y)'
```
In case of ROOT5 on Windows the following way of usage is recommended:
```sh
$ root
[] .L raw2root.C
[] raw2root("/path/to/in/file.bin", "out.root", 2, 2)
```


### Automatisation
Please look the example file _noise.py_.
It is built on usage of `os.system()`.


## How to build the project
To compile the program the **Visual Studio 2017** should be used.
We work on the poject _GetImage_CamRun.cpp_.
It is situated: `C:\Program Files (x86)\Digital Camera Toolbox\pco.sdk\sample\console\GetImage_CamRun\`.
To (re)build the project use menu *Build -> Rebuild GetImage_CamRun* and check output for absence for errors and fails.
