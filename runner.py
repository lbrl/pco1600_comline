import os
import sys


def main():
	print 'Hi!'
	cmd = r'"C:\Program Files (x86)\Digital Camera Toolbox\pco.sdk\bin64\GetImage_CamRun.exe"'
	cfg = r'C:\Users\muonbpm\Desktop\test_img\cfg.txt'
	fout = r'C:\Users\muonbpm\Desktop\test_img\test_three.bin'
	os.system('{} {} {}'.format(cmd, cfg, fout))
	

if __name__ == '__main__':
	main()
