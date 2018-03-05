import os
import sys


times = [
        [0, [500, 600, 700, 800, 900, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900]],
        [1, [2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100,
            150, 200, 250, 300, 350, 400, 450, 500, 600, 700, 800, 900]],
        [2, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
            150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 800, 900,
            1000, 2e3, 3e3, 4e3, 5e3, 6e3, 7e3, 8e3, 9e3,
            1e4, 2e4, 3e4, 4e4, 5e4, 6e4, 7e4, 8e4, 9e4,
            1e5, 2e5, 3e5, 4e5, 5e5, 6e5, 7e5, 8e5, 9e5]]
        ]


def get_name(base, time):
    name = 'cfg_npic_1_texp_{}_expbas_{}'.format(time, base)
    return name


def cfg():
    print 'Hi!'
    cmd = r'''python mkcfg.py'''
    for bt in times:
        for t in bt[1]:
            name = get_name(bt[0], int(t))+'.txt'
            out = '{} texp {} expbase {} cooltemp -20 npic 1 fout {}'.format(cmd,
                    int(t), bt[0], name)
            print out
            os.system(out)


def run():
    cmd = r'"C:\Program Files (x86)\Digital Camera Toolbox\pco.sdk\bin64\GetImage_CamRun.exe"'
    di = 'C:\\Users\\muonbpm\\Desktop\\test_img\\'
    for bt in times:
        for t in bt[1]:
            name = get_name(bt[0], int(t))
            name_cfg = di+name+'.txt'
            name_raw = di+name+'.bin'
            out = '{} {} {}'.format(cmd, name_cfg, name_raw)
            print out
            os.system(out)


if __name__ == '__main__':
    if 'cfg' in sys.argv:
        cfg()
    elif 'run' in sys.argv:
        run()
    else:
        print 'Choose one option: cfg or run.'
