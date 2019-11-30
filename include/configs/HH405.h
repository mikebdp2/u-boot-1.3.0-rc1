/*
 * (C) Copyright 2001-2004
 * Stefan Roese, esd gmbh germany, stefan.roese@esd-electronics.com
 *
 * (C) Copyright 2005
 * Stefan Roese, DENX Software Engineering, sr@denx.de.
 *
 * (C) Copyright 2006
 * Matthias Fuchs, esd GmbH, matthias.fuchs@esd-electronics.com
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * board/config.h - configuration options, board specific
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */

#define CONFIG_405EP		1	/* This is a PPC405 CPU		*/
#define CONFIG_4xx		1	/* ...member of PPC4xx family   */
#define CONFIG_HH405		1	/* ...on a HH405 board 	        */

#define CONFIG_BOARD_EARLY_INIT_F 1	/* call board_early_init_f()	*/
#define CONFIG_MISC_INIT_R      1       /* call misc_init_r()           */

#define CONFIG_SYS_CLK_FREQ     33333400 /* external frequency to pll   */

#define CONFIG_BOARD_TYPES	1	/* support board types		*/

#define CONFIG_BAUDRATE		9600
#define CONFIG_BOOTDELAY	3	/* autoboot after 3 seconds	*/

#undef	CONFIG_BOOTARGS
#undef	CONFIG_BOOTCOMMAND

#define CONFIG_PREBOOT	        "autoupd"

#define	CONFIG_EXTRA_ENV_SETTINGS					\
	"pciconfighost=1\0"						\
	""

#define CFG_LOADS_BAUD_CHANGE	1	/* allow baudrate change	*/

#define CONFIG_NET_MULTI	1
#undef  CONFIG_HAS_ETH1

#define CONFIG_MII		1	/* MII PHY management		*/
#define CONFIG_PHY_ADDR		0	/* PHY address			*/
#define CONFIG_LXT971_NO_SLEEP  1       /* disable sleep mode in LXT971 */
#define CONFIG_RESET_PHY_R      1       /* use reset_phy() to disable phy sleep mode */

#define CONFIG_PHY_CLK_FREQ	EMAC_STACR_CLK_66MHZ /* 66 MHz OPB clock*/

/*
 * Video console
 */
#define CONFIG_VIDEO			/* for sm501 video support	*/

#ifdef CONFIG_VIDEO
#define CONFIG_VIDEO_SM501
#if 0
#define CONFIG_VIDEO_SM501_32BPP
#else
#define CONFIG_VIDEO_SM501_16BPP
#endif
#define CONFIG_VIDEO_SM501_FBMEM_OFFSET 0x10000
#define CONFIG_CFB_CONSOLE
#define CONFIG_VIDEO_LOGO
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_CONSOLE_EXTRA_INFO
#define CONFIG_VIDEO_SW_CURSOR
#define CONFIG_SPLASH_SCREEN
#define CFG_CONSOLE_IS_IN_ENV
#define CONFIG_SPLASH_SCREEN
#define CONFIG_VIDEO_BMP_GZIP		/* gzip compressed bmp images	*/
#define CFG_VIDEO_LOGO_MAX_SIZE	(2 << 20)	/* for decompressed img */

#endif /* CONFIG_VIDEO */


/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


/*
 * Command line configuration.
 */
#include <config_cmd_default.h>

#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PCI
#define CONFIG_CMD_IRQ
#define CONFIG_CMD_IDE
#define CONFIG_CMD_FAT
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_ELF
#define CONFIG_CMD_NAND
#define CONFIG_CMD_I2C
#define CONFIG_CMD_DATE
#define CONFIG_CMD_MII
#define CONFIG_CMD_PING
#define CONFIG_CMD_EEPROM

#ifdef CONFIG_VIDEO
#define CONFIG_CMD_BMP
#endif

#define CONFIG_MAC_PARTITION
#define CONFIG_DOS_PARTITION

#define CONFIG_SUPPORT_VFAT

#define CONFIG_AUTO_UPDATE      1       /* autoupdate via compactflash  */
#undef CONFIG_AUTO_UPDATE_SHOW          /* use board show routine       */

#undef  CONFIG_BZIP2	 /* include support for bzip2 compressed images */
#undef  CONFIG_WATCHDOG			/* watchdog disabled		*/

#define	CONFIG_SDRAM_BANK0	1	/* init onboard SDRAM bank 0	*/

/*
 * Miscellaneous configurable options
 */
#define CFG_LONGHELP			/* undef to save memory		*/
#define CFG_PROMPT	"=> "		/* Monitor Command Prompt	*/

#undef	CFG_HUSH_PARSER			/* use "hush" command parser	*/
#ifdef	CFG_HUSH_PARSER
#define	CFG_PROMPT_HUSH_PS2	"> "
#endif

#if defined(CONFIG_CMD_KGDB)
#define	CFG_CBSIZE	1024		/* Console I/O Buffer Size	*/
#else
#define	CFG_CBSIZE	256		/* Console I/O Buffer Size	*/
#endif
#define CFG_PBSIZE (CFG_CBSIZE+sizeof(CFG_PROMPT)+16) /* Print Buffer Size */
#define CFG_MAXARGS	16		/* max number of command args	*/
#define CFG_BARGSIZE	CFG_CBSIZE	/* Boot Argument Buffer Size	*/

#define CFG_DEVICE_NULLDEV      1       /* include nulldev device       */

#undef  CFG_CONSOLE_INFO_QUIET          /* print console @ startup	*/

#define CONFIG_AUTO_COMPLETE	1       /* add autocompletion support   */

#define CFG_MEMTEST_START	0x0400000	/* memtest works on	*/
#define CFG_MEMTEST_END		0x0C00000	/* 4 ... 12 MB in DRAM	*/

#undef  CFG_EXT_SERIAL_CLOCK           /* no external serial clock used */
#define CFG_IGNORE_405_UART_ERRATA_59   /* ignore ppc405gp errata #59   */
#define CFG_BASE_BAUD       691200
#define CONFIG_UART1_CONSOLE            /* define for uart1 as console  */

/* The following table includes the supported baudrates */
#define CFG_BAUDRATE_TABLE      \
	{ 300, 600, 1200, 2400, 4800, 9600, 19200, 38400,     \
	 57600, 115200, 230400, 460800, 921600 }

#define CFG_LOAD_ADDR	0x100000	/* default load address */
#define CFG_EXTBDINFO	1		/* To use extended board_into (bd_t) */

#define	CFG_HZ		1000		/* decrementer freq: 1 ms ticks	*/

#define CONFIG_ZERO_BOOTDELAY_CHECK	/* check for keypress on bootdelay==0 */

#define CONFIG_VERSION_VARIABLE	1       /* include version env variable */

#define CFG_RX_ETH_BUFFER	16      /* use 16 rx buffer on 405 emac */

/*-----------------------------------------------------------------------
 * RTC stuff
 *-----------------------------------------------------------------------
 */
#define CONFIG_RTC_DS1338
#define CFG_I2C_RTC_ADDR	0x68

/*-----------------------------------------------------------------------
 * NAND-FLASH stuff
 *-----------------------------------------------------------------------
 */
#define CFG_NAND_BASE_LIST	{ CFG_NAND_BASE }
#define NAND_MAX_CHIPS          1
#define CFG_MAX_NAND_DEVICE	1         /* Max number of NAND devices */
#define NAND_BIG_DELAY_US	25

#define CFG_NAND_CE             (0x80000000 >> 1)   /* our CE is GPIO1  */
#define CFG_NAND_RDY            (0x80000000 >> 4)   /* our RDY is GPIO4 */
#define CFG_NAND_CLE            (0x80000000 >> 2)   /* our CLE is GPIO2 */
#define CFG_NAND_ALE            (0x80000000 >> 3)   /* our ALE is GPIO3 */

#define CFG_NAND_SKIP_BAD_DOT_I      1  /* ".i" read skips bad blocks   */

/*-----------------------------------------------------------------------
 * PCI stuff
 *-----------------------------------------------------------------------
 */
#define PCI_HOST_ADAPTER 0              /* configure as pci adapter     */
#define PCI_HOST_FORCE  1               /* configure as pci host        */
#define PCI_HOST_AUTO   2               /* detected via arbiter enable  */

#define CONFIG_PCI			/* include pci support	        */
#define CONFIG_PCI_HOST	PCI_HOST_HOST   /* select pci host function     */
#define CONFIG_PCI_PNP			/* do pci plug-and-play         */
					/* resource configuration       */

#define CONFIG_PCI_SCAN_SHOW            /* print pci devices @ startup  */

#define CONFIG_PCI_CONFIG_HOST_BRIDGE 1 /* don't skip host bridge config*/

#define CFG_PCI_SUBSYS_VENDORID 0x12FE  /* PCI Vendor ID: esd gmbh      */
#define CFG_PCI_SUBSYS_DEVICEID 0x0405  /* PCI Device ID: CPCI-405      */
#define CFG_PCI_CLASSCODE       0x0b20  /* PCI Class Code: Processor/PPC*/
#define CFG_PCI_PTM1LA  0x00000000      /* point to sdram               */
#define CFG_PCI_PTM1MS  0xfc000001      /* 64MB, enable hard-wired to 1 */
#define CFG_PCI_PTM1PCI 0x00000000      /* Host: use this pci address   */
#define CFG_PCI_PTM2LA  0xffc00000      /* point to flash               */
#define CFG_PCI_PTM2MS  0xffc00001      /* 4MB, enable                  */
#define CFG_PCI_PTM2PCI 0x04000000      /* Host: use this pci address   */

/*-----------------------------------------------------------------------
 * IDE/ATA stuff
 *-----------------------------------------------------------------------
 */
#undef  CONFIG_IDE_8xx_DIRECT               /* no pcmcia interface required */
#undef  CONFIG_IDE_LED                  /* no led for ide supported     */
#define CONFIG_IDE_RESET	1	/* reset for ide supported	*/

#define	CFG_IDE_MAXBUS	        1		/* max. 1 IDE busses	*/
#define	CFG_IDE_MAXDEVICE	(CFG_IDE_MAXBUS*1) /* max. 1 drives per IDE bus */

#define	CFG_ATA_BASE_ADDR	0xF0100000
#define	CFG_ATA_IDE0_OFFSET	0x0000

#define CFG_ATA_DATA_OFFSET	0x0000	/* Offset for data I/O			*/
#define	CFG_ATA_REG_OFFSET	0x0000	/* Offset for normal register accesses	*/
#define CFG_ATA_ALT_OFFSET	0x0000	/* Offset for alternate registers	*/

/*
 * For booting Linux, the board info and command line data
 * have to be in the first 8 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization.
 */
#define CFG_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */
/*-----------------------------------------------------------------------
 * FLASH organization
 */
#define FLASH_BASE0_PRELIM	0xFFC00000	/* FLASH bank #0	*/

#define CFG_MAX_FLASH_BANKS	1	/* max number of memory banks		*/
#define CFG_MAX_FLASH_SECT	256	/* max number of sectors on one chip	*/

#define CFG_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase (in ms)	*/
#define CFG_FLASH_WRITE_TOUT	1000	/* Timeout for Flash Write (in ms)	*/

#define CFG_FLASH_WORD_SIZE     unsigned short  /* flash word size (width)      */
#define CFG_FLASH_ADDR0         0x5555  /* 1st address for flash config cycles  */
#define CFG_FLASH_ADDR1         0x2AAA  /* 2nd address for flash config cycles  */
/*
 * The following defines are added for buggy IOP480 byte interface.
 * All other boards should use the standard values (CPCI405 etc.)
 */
#define CFG_FLASH_READ0         0x0000  /* 0 is standard                        */
#define CFG_FLASH_READ1         0x0001  /* 1 is standard                        */
#define CFG_FLASH_READ2         0x0002  /* 2 is standard                        */

#define CFG_FLASH_EMPTY_INFO            /* print 'E' for empty sector on flinfo */

#if 0 /* test-only */
#define CFG_JFFS2_FIRST_BANK    0           /* use for JFFS2 */
#define CFG_JFFS2_NUM_BANKS     1           /* ! second bank contains U-Boot */
#endif

/*-----------------------------------------------------------------------
 * Start addresses for the final memory configuration
 * (Set up by the startup code)
 * Please note that CFG_SDRAM_BASE _must_ start at 0
 */
#define CFG_SDRAM_BASE		0x00000000
#define CFG_FLASH_BASE		0xFFF80000
#define CFG_MONITOR_BASE	TEXT_BASE
#define CFG_MONITOR_LEN		(512 * 1024)	/* Reserve 512 kB for Monitor	*/
#define CFG_MALLOC_LEN		(4 << 20)	/* Reserve 4 MB for malloc()	*/

#if (CFG_MONITOR_BASE < FLASH_BASE0_PRELIM)
# define CFG_RAMBOOT		1
#else
# undef CFG_RAMBOOT
#endif

/*-----------------------------------------------------------------------
 * Environment Variable setup
 */
#define CFG_ENV_IS_IN_EEPROM    1       /* use EEPROM for environment vars */
#define CFG_ENV_OFFSET          0x100   /* environment starts at the beginning of the EEPROM */
#define CFG_ENV_SIZE            0x700   /* 2048 bytes may be used for env vars*/
				   /* total size of a CAT24WC16 is 2048 bytes */

#define CFG_NVRAM_BASE_ADDR	0xF4080000		/* NVRAM base address	*/
#define CFG_NVRAM_SIZE		0x8000		        /* NVRAM size		*/

/*-----------------------------------------------------------------------
 * I2C EEPROM (CAT24WC16) for environment
 */
#define CONFIG_HARD_I2C			/* I2c with hardware support */
#if 0 /* test-only */
#define CFG_I2C_SPEED		400000	/* I2C speed and slave address */
#else
#define CFG_I2C_SPEED		100000	/* I2C speed and slave address */
#endif
#define CFG_I2C_SLAVE		0x7F

#define CFG_I2C_EEPROM_ADDR	0x50	/* EEPROM CAT24WC08		*/
#define CFG_EEPROM_WREN         1

#if 1 /* test-only */
/* CAT24WC08/16... */
#define CFG_I2C_EEPROM_ADDR_LEN	1	/* Bytes of address		*/
/* mask of address bits that overflow into the "EEPROM chip address"    */
#define CFG_I2C_EEPROM_ADDR_OVERFLOW	0x07
#define CFG_EEPROM_PAGE_WRITE_BITS 4	/* The Catalyst CAT24WC08 has	*/
					/* 16 byte page write mode using*/
					/* last	4 bits of the address	*/
#else
/* CAT24WC32/64... */
#define CFG_I2C_EEPROM_ADDR_LEN	2	/* Bytes of address		*/
/* mask of address bits that overflow into the "EEPROM chip address"    */
#define CFG_I2C_EEPROM_ADDR_OVERFLOW	0x01
#define CFG_EEPROM_PAGE_WRITE_BITS 5	/* The Catalyst CAT24WC32 has	*/
					/* 32 byte page write mode using*/
					/* last	5 bits of the address	*/
#endif
#define CFG_EEPROM_PAGE_WRITE_DELAY_MS	10   /* and takes up to 10 msec */
#define CFG_EEPROM_PAGE_WRITE_ENABLE

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CFG_DCACHE_SIZE		16384	/* For AMCC 405 CPUs, older 405 ppc's    */
					/* have only 8kB, 16kB is save here     */
#define CFG_CACHELINE_SIZE	32	/* ...			*/
#if defined(CONFIG_CMD_KGDB)
#define CFG_CACHELINE_SHIFT	5	/* log base 2 of the above value	*/
#endif

/*-----------------------------------------------------------------------
 * External Bus Controller (EBC) Setup
 */

#define CAN_BA          0xF0000000          /* CAN Base Address                 */
#define LCD_BA          0xF1000000          /* Epson LCD Base Address           */
#define CFG_NAND_BASE   0xF4000000          /* NAND FLASH Base Address          */
#define CFG_NVRAM_BASE  0xF4080000          /* NVRAM Base Address               */

/* Memory Bank 0 (Flash Bank 0, NOR-FLASH) initialization                       */
#define CFG_EBC_PB0AP           0x92015480
#define CFG_EBC_PB0CR           0xFFC5A000  /* BAS=0xFFC,BS=4MB,BU=R/W,BW=16bit */

/* Memory Bank 1 (Flash Bank 1, NAND-FLASH & NVRAM) initialization              */
#define CFG_EBC_PB1AP           0x92015480
#define CFG_EBC_PB1CR           0xF4018000  /* BAS=0xF40,BS=1MB,BU=R/W,BW=8bit  */

/* Memory Bank 2 (8 Bit Peripheral: CAN, UART, RTC) initialization              */
#define CFG_EBC_PB2AP           0x010053C0  /* BWT=2,WBN=1,WBF=1,TH=1,RE=1,SOR=1,BEM=1 */
#define CFG_EBC_PB2CR           0xF0018000  /* BAS=0xF00,BS=1MB,BU=R/W,BW=8bit  */

/* Memory Bank 3 (16 Bit Peripheral: FPGA internal, dig. IO) initialization     */
#define CFG_EBC_PB3AP           0x010053C0  /* BWT=2,WBN=1,WBF=1,TH=1,RE=1,SOR=1,BEM=1 */
#define CFG_EBC_PB3CR           0xF011A000  /* BAS=0xF01,BS=1MB,BU=R/W,BW=16bit */

/* Memory Bank 4 (Epson LCD) initialization                                     */
#define CFG_EBC_PB4AP   0x03805380   /* BWT=2,WBN=1,WBF=1,TH=1,RE=1,SOR=1,BEM=0 */
#define CFG_EBC_PB4CR   LCD_BA | 0x7A000    /* BAS=0xF10,BS=8MB,BU=R/W,BW=16bit */

/*-----------------------------------------------------------------------
 * LCD Setup
 */

#define CFG_LCD_BIG_MEM         0xF1200000  /* Epson S1D13806 Mem Base Address  */
#define CFG_LCD_BIG_REG         0xF1000000  /* Epson S1D13806 Reg Base Address  */
#define CFG_LCD_SMALL_MEM       0xF1400000  /* Epson S1D13704 Mem Base Address  */
#define CFG_LCD_SMALL_REG       0xF140FFE0  /* Epson S1D13704 Reg Base Address  */

/*-----------------------------------------------------------------------
 * Universal Interrupt Controller (UIC) Setup
 */

/*
 * define UIC_EXT0 ... UIC_EXT6 if external interrupt is active high
 */
#define CFG_UIC0_POLARITY       (0xFFFFFF80 | UIC_EXT6)

/*-----------------------------------------------------------------------
 * FPGA stuff
 */

#define CFG_FPGA_BASE_ADDR 0xF0100100       /* FPGA internal Base Address       */

/* FPGA internal regs */
#define CFG_FPGA_CTRL           0x000

/* FPGA Control Reg */
#define CFG_FPGA_CTRL_REV0      0x0001
#define CFG_FPGA_CTRL_REV1      0x0002
#define CFG_FPGA_CTRL_VGA0_BL   0x0004
#define CFG_FPGA_CTRL_VGA0_BL_MODE 0x0008
#define CFG_FPGA_CTRL_CF_RESET  0x0040
#define CFG_FPGA_CTRL_PS2_PWR   0x0080
#define CFG_FPGA_CTRL_CF_PWRN   0x0100      /* low active                    */
#define CFG_FPGA_CTRL_CF_BUS_EN 0x0200
#define CFG_FPGA_CTRL_LCD_CLK   0x7000      /* Mask for lcd clock            */
#define CFG_FPGA_CTRL_OW_ENABLE 0x8000

#define CFG_FPGA_STATUS_CF_DETECT 0x8000

#define LCD_CLK_OFF             0x0000      /* Off                           */
#define LCD_CLK_02083           0x1000      /* 2.083 MHz                     */
#define LCD_CLK_03135           0x2000      /* 3.135 MHz                     */
#define LCD_CLK_04165           0x3000      /* 4.165 MHz                     */
#define LCD_CLK_06250           0x4000      /* 6.250 MHz                     */
#define LCD_CLK_08330           0x5000      /* 8.330 MHz                     */
#define LCD_CLK_12500           0x6000      /* 12.50 MHz                     */
#define LCD_CLK_25000           0x7000      /* 25.00 MHz                     */

#define CFG_FPGA_SPARTAN2       1           /* using Xilinx Spartan 2 now    */
#define CFG_FPGA_MAX_SIZE       128*1024    /* 128kByte is enough for XC2S50E*/

/* FPGA program pin configuration */
#define CFG_FPGA_PRG            0x04000000  /* FPGA program pin (ppc output) */
#define CFG_FPGA_CLK            0x02000000  /* FPGA clk pin (ppc output)     */
#define CFG_FPGA_DATA           0x01000000  /* FPGA data pin (ppc output)    */
#define CFG_FPGA_INIT           0x00010000  /* FPGA init pin (ppc input)     */
#define CFG_FPGA_DONE           0x00008000  /* FPGA done pin (ppc input)     */

/*-----------------------------------------------------------------------
 * Definitions for initial stack pointer and data area (in data cache)
 */
/* use on chip memory ( OCM ) for temperary stack until sdram is tested */
#define CFG_TEMP_STACK_OCM        1

/* On Chip Memory location */
#define CFG_OCM_DATA_ADDR	0xF8000000
#define CFG_OCM_DATA_SIZE	0x1000
#define CFG_INIT_RAM_ADDR	CFG_OCM_DATA_ADDR /* inside of SDRAM		*/
#define CFG_INIT_RAM_END	CFG_OCM_DATA_SIZE /* End of used area in RAM	*/

#define CFG_GBL_DATA_SIZE      128  /* size in bytes reserved for initial data */
#define CFG_GBL_DATA_OFFSET    (CFG_INIT_RAM_END - CFG_GBL_DATA_SIZE)
#define CFG_INIT_SP_OFFSET      CFG_GBL_DATA_OFFSET

/*-----------------------------------------------------------------------
 * Definitions for GPIO setup (PPC405EP specific)
 *
 * GPIO0[0]     - External Bus Controller BLAST output
 * GPIO0[1-9]   - Instruction trace outputs -> GPIO
 * GPIO0[10-13] - External Bus Controller CS_1 - CS_4 outputs
 * GPIO0[14-16] - External Bus Controller ABUS3-ABUS5 outputs -> GPIO
 * GPIO0[17-23] - External Interrupts IRQ0 - IRQ6 inputs
 * GPIO0[24-27] - UART0 control signal inputs/outputs
 * GPIO0[28-29] - UART1 data signal input/output
 * GPIO0[30-31] - EMAC0 and EMAC1 reject packet inputs
 */
#define CFG_GPIO0_OSRH		0x40000550
#define CFG_GPIO0_OSRL		0x00000110
#define CFG_GPIO0_ISR1H		0x00000000
#define CFG_GPIO0_ISR1L		0x15555440
#define CFG_GPIO0_TSRH		0x00000000
#define CFG_GPIO0_TSRL		0x00000000
#define CFG_GPIO0_TCR		0xF7FE0017

#define CFG_LCD_ENDIAN		(0x80000000 >> 7)
#define CFG_EEPROM_WP		(0x80000000 >> 8)   /* GPIO8 */
#define CFG_TOUCH_RST		(0x80000000 >> 9)   /* GPIO9 */
#define CFG_LCD0_RST		(0x80000000 >> 30)
#define CFG_LCD1_RST		(0x80000000 >> 31)

/*
 * Internal Definitions
 *
 * Boot Flags
 */
#define BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM	0x02		/* Software reboot			*/

/*
 * Default speed selection (cpu_plb_opb_ebc) in mhz.
 * This value will be set if iic boot eprom is disabled.
 */
#if 0
#define PLLMR0_DEFAULT   PLLMR0_266_133_66_33
#define PLLMR1_DEFAULT   PLLMR1_266_133_66_33
#endif
#if 0
#define PLLMR0_DEFAULT   PLLMR0_200_100_50_33
#define PLLMR1_DEFAULT   PLLMR1_200_100_50_33
#endif
#if 1
#define PLLMR0_DEFAULT   PLLMR0_133_66_66_33
#define PLLMR1_DEFAULT   PLLMR1_133_66_66_33
#endif

#endif	/* __CONFIG_H */