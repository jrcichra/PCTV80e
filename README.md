## PCTV80e 2020

See my issue on patrick's page: https://github.com/patrickdickey52761/PCTV80e/issues/2

Essentially all you need to do for modern kernels is cd to /lib/firmware and run `sudo wget https://github.com/osmc/dvb-firmware-osmc/raw/master/dvb-fe-drxj-mc-1.0.8.fw`. There might be newer versions you can download from here: https://www.linuxtv.org/downloads/firmware/


## PCTV80e media_build with modifications included!

I am sharing this because newer versions of media_build augment the process to get the pinnacle working.

I can confirm this is working on a raspberry pi 3 model b and b+.

At one point I did install this on an x86 Ubuntu system.

This may not be the latest version of the media_build, this may be updated if there are significant improvements to the media_build system that warrants such an upgrade.

## Steps:

1. download this repo
2. follow the instructions inside the media_build_clean directory (essentially ./build && sudo make install should do it) 
3. reboot or modprobe it. Then you should have a /dev/dvb device, and you're ready to use something like tvheadend.

--Justin C.

--------------------------------------------


This is an updated version of Devin Heitmueller's patch for LinuxTV, which allows you to use the Pinnacle PCTV-80e USB Tuner.
You can find his posting about the tuner at http://www.kernellabs.com/blog/?p=1435 and his code at http://www.kernellabs.com/hg/~dheitmueller/v4l-dvb-80e
(use the last two commits-- the second one first, then the topmost (tip/master) second).

Essentially what you'll want to do is use git to download and build the media_build.git repository from linuxtv.org, and then patch it
with the files from my repository (the em28xx.* files and the drxj directory in the linux/drivers/media/frontends directory).

You can simply copy the drxj directory over to the appropriate location in your media_build directory, and then patch the em28xx files (copy/paste or diff
and patch -p1 ), then make and make install.  The files should compile on Debian/Ubuntu 11.04, but you will probably need to make changes to compile on 11.10 or later kernels.

The only files/folders that are included here are the ones that are specific to the pctv80e tuner. So you will definitely need to build this against
the media_build git repository at http://linuxtv.org.

============================================================
Steps for building the PCTV-80e video-4-linux drivers (note these were done on Ubuntu 11.10 so your steps may vary)
============================================================

1. Open a terminal.
2. Type the following commands to get the initial directories and basic files.

    $git clone git://linuxtv.org/media_build.git
    $git clone git@github.com:patrickdickey52761/PCTV80e
3. change to the media_build directory

	$cd media_build
    
4. Build the media_build git directory (you can try to use "git pull git://linuxtv.org/media_build.git" instead)

	$./build
    
5.  Change to the pctv80e directory (if you created them somewhere other than under your home, the command will be diferent)

    $cd ~/pctv80e

6.  Use the git pull command to pull down the files if they are not already there

    $git pull git@github.com:patrickdickey52761/PCTV80e

7.  run a diff program to compare the two directories. I'll list the things that you *should* need to fix, but you
may have other issues as well.  Note that by running ./build earlier, you already patched the files for your
specific kernel. So this should be a matter of moving the necessary files and directories over, and copying the 
specific lines over to the files in the media_build directory to make things work.

=====================
What needs to be "fixed" (note: I used meld to compare and fix the files, so you'll need to use your diff results
   as a guide.)
=====================

1.  Copy the linux/Documentation/video4linux/CARDLIST.em28xx file/directory structure over to media_build.
2.  Copy the linux/drivers/media/dvb/frontends/drx39xyj directory over to media_build.
3.  Change the following files:

a.  media_build/linux/drivers/media/dvb/frontends/Kconfig
    add the following to the end of the file:
         source "drivers/media/dvb/frontends/drx39xyj/Kconfig"

b.  media_build/linux/drivers/media/dvb/frontends/Makefile
    add the following line after line 88:
         obj-$(CONFIG_DVB_DRX39XYJ) += drx39xyj/

c.  media_build/linux/drivers/media/video/em28xx/em28xx-cards.c

    add the following after line 197:
           /* PCTV HD Mini (80e) GPIOs
   			  0-5: not used
   			  6:   demod reset, active low
   			  7:   LED on, active high */
			static struct em28xx_reg_seq em2874_pctv_80e_digital[] = {
					{EM28XX_R06_I2C_CLK,    0x45,   0xff,		  10}, /*400 KHz*/
					{EM2874_R80_GPIO,       0x80,   0xff,		  100},/*Demod reset*/
					{EM2874_R80_GPIO,       0xc0,   0xff,		  10},
					{  -1,			-1,	-1,		  -1},
			};

     add the following after line 208:
			[EM2874_BOARD_PCTV_HD_MINI_80E] = {
				.name         = "Pinnacle PCTV HD Mini",
				.tuner_type   = TUNER_ABSENT,
				.has_dvb      = 1,
				.dvb_gpio     = em2874_pctv_80e_digital,
				.decoder      = EM28XX_NODECODER,
			},

      add the following after line 1979:

			{ USB_DEVICE(0x2304, 0x023f),
					.driver_info = EM2874_BOARD_PCTV_HD_MINI_80E },

d.  media_build/linux/drivers/media/video/em28xx/em28xx-dvb.c

     add the following after line 38:

			#include "drx39xxj.h"

     add the following after line 312: (note the first line is a blank line)


		static struct tda18271_std_map drx_j_std_map = {
			.atsc_6   = { .if_freq = 5000, .agc_mode = 3, .std = 0, .if_lvl = 1,
				      .rfagc_top = 0x37, },
			.qam_6    = { .if_freq = 5380, .agc_mode = 3, .std = 3, .if_lvl = 1,
				      .rfagc_top = 0x37, },
		};

		static struct tda18271_config pinnacle_80e_dvb_config = {
			.std_map = &drx_j_std_map,
			.gate    = TDA18271_GATE_DIGITAL,
			.role    = TDA18271_MASTER,
		};

     add the following after line 642:

			struct dvb_frontend *fe;

     alter line 769, so it looks like this:

		}
		break;
	case EM2874_BOARD_PCTV_HD_MINI_80E:
		dvb->fe[0] = dvb_attach(drx39xxj_attach, &dev->i2c_adap);
		if (dvb->fe[0] != NULL) {
			fe = dvb_attach(tda18271_attach, dvb->fe[0], 0x60,
					&dev->i2c_adap,
					&pinnacle_80e_dvb_config);
			printk(KERN_ERR "dvb_attach tuner result=%p\n", fe);

e.  media_build/linux/drivers/media/video/em28xx/em28xx.h

    add the following after line 123:

		#define EM2874_BOARD_PCTV_HD_MINI_80E		  81

8.  make the media_build directory a second time, since you've changed things (depending on your version, you may 
have compilation errors, since it may need to patch some files again: specifically the use of atomic.h in some files.)

	$make

9.  After media_build makes successfully, run sudo make install (or su -i then make install depending on your distribution)

	$sudo make install

Enjoy your PCTV-80e on Linux.
