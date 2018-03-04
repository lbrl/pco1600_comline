import os
import sys


def check_binning_x(binx):
    if binx in [1, 2]:
        return binx
    else:
        print 'Wrong X binning: {}!  Possible values are 1 and 2.  Set the binning to 1.'.format(binx)
        return 1


def check_binning_y(biny):
    if biny in [1, 2, 4, 8]:
        return biny
    else:
        print 'Wrong Y binning: {}!  Possible values are 1, 2, 4 and 8.  Set the binning to 1.'.format(biny)
        return 1


def check_pixel_rate(x):
    if x in [10000000, 40000000]:
        return x
    else:
        print 'Wrong pixel rate: {}!  Possible values are 10000000 and 40000000.  Set the pixel rate to 10000000.'.format(x)
        return 10000000


def main():
	# Default values
	texp = 100
	tdelay = 0
	expbase = 2
	delaybase = 2
	binx = 1
	biny = 1
	trigmode = 0
	npic = 5
	foutname = 'cfg_by_mkcfg.txt'
    nadc = 1
    pixelrate = 10000000
    cooltemp = -150
	# Read input parameters
	narg = len(sys.argv)
	i = 0
	while i < narg:
		arg = sys.argv[i]
		if arg in ['texp', 'texposure']:
			texp = int(sys.argv[i+1])
			i += 1
		elif arg == ['tdel', 'tdelay']:
			tdelay = int(sys.argv[i+1])
			i += 1
		elif arg in ['expbase', 'texpbase']:
			expbase = int(sys.argv[i+1])
			i += 1
		elif arg in ['delbase', 'tdelbase', 'delaybase', 'delbase']:
			delaybase = int(sys.argv[i+1])
			i += 1
		elif arg in ['binx', 'binningx']:
			binx = int(sys.argv[i+1])
            binx = check_binning_x(binx)
			i += 1
		elif arg in ['biny', 'binningy']:
			biny = int(sys.argv[i+1])
            biny = check_binning_y(binx)
			i += 1
		elif arg in ['binxy', 'binningxy']:
			binx = int(sys.argv[i+1])
			biny = int(sys.argv[i+2])
            binx = check_binning_x(binx)
            biny = check_binning_y(binx)
			i += 2
		elif arg in ['trigmode', 'triggermode']:
			trigmode = int(sys.argv[i+1])
			i += 1
		elif arg in ['npic', 'numberofpic', 'npics', 'numberofpictures']:
			npic = int(sys.argv[i+1])
			i += 1
		elif arg in ['name', 'outname', 'outputname', 'fout', 'foutname']:
			foutname = sys.argv[i+1]
			i += 1
        elif arg in ['adc', 'adcoper', 'adcoperation']"
            nadc = int(sys.argv[i+1])
            i += 1
        elif arg in ['pixelrate']:
            pixelrate = int(sys.argv[i+1])
            pixelrate = check_pixel_rate(pixelrate)
            i += 1
        elif arg in ['coolset', 'coolingtemp', 'cooltemp', 'coolingtemperature']:
            cooltemp = int(sys.argv[i+1])
            i += 1
		else:
			print 'There is not a such option : ', arg
		i += 1
	# Make the cfg body
	out = 'Exposure {}\n'.format(texp)
	out += 'ExposureBase {}\n'.format(expbase)
	out += 'Delay {}\n'.format(tdelay)
	out += 'DelayBase {}\n'.format(delaybase)
	out += 'BinningX {}\n'.format(binx)
	out += 'BinningY {}\n'.format(biny)
	out += 'TriggerMode {}\n'.format(trigmode)
	out += 'NumberOfPictures {}\n'.format(npic)
    out += 'ADCOperation {}\n'.format(nadc)
    out += 'PixelRate {}\n'.format(pixelrate)
    out += 'CoolingTemperature {}\n'.format(cooltemp)
	print out
	fout = open(foutname, 'w')
	fout.write(out)
	fout.close()


def help():
    print '''Usage:\n\tmkcfg.py [option argumetns]'''
    print 'Usage:\n\tmkcfg.py fout cfg.txt texp 500 texpbase 0 binxy 2 2\n\n\n'
    print 'Possible options:\n'
    print '  texp\t\tGets one _int_ argument,  the exposure time in time'
    print '  \t\tunits specified with texpbase.\n'
    print '  texpbase\tGets one _int_ argument,  the time base for the'
    print '  \t\texposure time.  Can be 0 --- ns,  1 --- us,  2 --- ms.\n'
    print '  tdelay\t\tGet one _int_ argument,  the delay time in time'
    print '  \t\tunits specified with delaybase.\n'
    print '  delaybase\tGets one _int_ argument,  the time base for the'
    print '  \t\tdelay time.  Can be 0 --- ns,  1 --- us,  2 --- ms.\n'
    print '  npics\t\tGet one _int_ argument > 0,  the number of pictures'
    print '  \t\tto take.\n'
    print '  fout\t\tGet one _str_ argument.  The output file name.\n'
    print '  binx\t\tGet one _int_ argument.  The horizontal binning.\n'
    print '  biny\t\tGet one _int_ argument.  The vertical binning.\n'
    print '  binxy\t\tGet two _int_ arguments.  The horizontal and'
    print '  \t\tvertical binning.\n'
    print '  trigmode\tGet one _int_ argument.  The trigger mode:'
    print '  \t\t0 --- auto sequence,'
    print '  \t\t1 --- software trigger,'
    print '  \t\t2 --- external exposure start and software trigger.\n'
    print '  adc\t\tGet one _int_ argument.  The number of read out ADCs to be used.'
    print '  \t\tChoose between 1 and 2.\n'
    print '  pixelrate\tGet one _int_ argumetn.  The ADC operation frequency.'
    print '  \t\tCan be 10000000 or 40000000.\n'
    print '  \t\tcooltemp\tGet one _int_ argument.  CCD sensor cooling temperature.'
    print '  \t\tFor example -150 corresponds to -15.0 Celsius degree.\n'


if __name__ == '__main__':
    print 'Make a configuration file for the pco.1600.'
    print 'For help pass :  mktree help'
    if 'help' in sys.argv:
        help()
    else:
        main()
