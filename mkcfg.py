import os
import sys


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
			i += 1
		elif arg in ['biny', 'binningy']:
			biny = int(sys.argv[i+1])
			i += 1
		elif arg in ['binxy', 'binningxy']:
			binx = int(sys.argv[i+1])
			biny = int(sys.argv[i+2])
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
	print out
	fout = open(foutname, 'w')
	fout.write(out)
	fout.close()
		

if __name__ == '__main__':
	main()
