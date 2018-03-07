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


### Automatisation
Please look the example file _noise.py_.
It is built on usage of `os.system()`.


## How to build the project
To compile the program the **Visual Studio 2017** should be used.
We work on the poject _GetImage_CamRun.cpp_.
It is situated: `C:\Program Files (x86)\Digital Camera Toolbox\pco.sdk\sample\console\GetImage_CamRun\`.
To (re)build the project use menu *Build -> Rebuild GetImage_CamRun* and check output for absence for errors and fails.
