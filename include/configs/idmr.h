/*
 * Configuration settings for the iDMR board
 *
 * Based on MC5272C3, r5200  and M5271EVB board configs
 * (C) Copyright 2006 Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 * (C) Copyright 2006 Lab X Technologies <zachary.landau@labxtechnologies.com>
 * (C) Copyright 2003 Josef Baumgartner <josef.baumgartner@telex.de>
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

#ifndef _IDMR_H
#define _IDMR_H


/*
 * High Level Configuration Options (easy to change)
 */

#define CONFIG_MCF52x2		/* define processor family */
#define CONFIG_M5271		/* define processor type */
#define CONFIG_IDMR		/* define board type */

#undef CONFIG_WATCHDOG		/* disable watchdog */

/*
 * Default environment settings
 */
#define CONFIG_BOOTCOMMAND	"run net_nfs"
#define CONFIG_BOOTDELAY	5
#define CONFIG_MCFUART
#define CFG_UART_PORT		(0)
#define CONFIG_BAUDRATE		19200
#define CFG_BAUDRATE_TABLE	{ 9600 , 19200 , 38400 , 57600, 115200 }
#define CONFIG_ETHADDR		00:06:3b:01:41:55
#define CONFIG_ETHPRIME
#define CONFIG_IPADDR		192.168.30.1
#define CONFIG_SERVERIP		192.168.1.1
#define CONFIG_ROOTPATH
#define CONFIG_GATEWAYIP	192.168.1.1
#define CONFIG_NETMASK		255.255.0.0
#define CONFIG_HOSTNAME		idmr
#define CONFIG_BOOTFILE		/tftpboot/idmr/uImage
#define CONFIG_PREBOOT		"echo;echo Type \"run flash_nfs\" to mount root " \
				"filesystem over NFS; echo"

#define CONFIG_MCFTMR

#define CONFIG_EXTRA_ENV_SETTINGS					\
	"netdev=eth0\0"							\
	"ramargs=setenv bootargs root=/dev/ram rw\0"			\
	"addip=setenv bootargs $(bootargs) "				\
		"ip=$(ipaddr):$(serverip):$(gatewayip):"		\
		"$(netmask):$(hostname):$(netdev):off panic=1\0"	\
	"flash_nfs=run nfsargs addip;bootm $(kernel_addr)\0"		\
	"flash_self=run ramargs addip;bootm $(kernel_addr) "		\
		"$(ramdisk_addr)\0"					\
	"net_nfs=tftp 200000 $(bootfile);run nfsargs addip;bootm\0"	\
	"nfsargs=setenv bootargs root=/dev/nfs rw "			\
		"nfsroot=$(serverip):$(rootpath)\0"			\
	"ethact=FEC ETHERNET\0"						\
	"update=prot off ff800000 ff81ffff; era ff800000 ff81ffff; "	\
		"cp.b 200000 ff800000 $(filesize);"			\
		"prot on ff800000 ff81ffff\0"				\
	"load=tftp 200000 $(u-boot)\0"					\
	"u-boot=/tftpboot/idmr/u-boot.bin\0"				\
	""


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

#define CONFIG_CMD_PING
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_NET

#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_LOADB


/*
 * Low Level Configuration Settings
 * (address mappings, register initial values, etc.)
 * You should know what you are doing if you make changes here.
 */

/*
 * Configuration for environment, which occupies third sector in flash.
 */
#ifndef CONFIG_MONITOR_IS_IN_RAM
#define CFG_ENV_ADDR		0xff820000
#define CFG_ENV_SECT_SIZE	0x10000
#define CFG_ENV_SIZE		0x2000
#define CFG_ENV_IS_IN_FLASH
#else /* CONFIG_MONITOR_IS_IN_RAM */
#define CFG_ENV_OFFSET		0x4000
#define CFG_ENV_SECT_SIZE	0x2000
#define CFG_ENV_IS_IN_FLASH
#endif /* !CONFIG_MONITOR_IS_IN_RAM */

#define CFG_PROMPT		"=> "
#define CFG_LONGHELP				/* undef to save memory */

#if defined(CONFIG_CMD_KGDB)
#define CFG_CBSIZE		1024		/* Console I/O Buffer Size */
#else
#define CFG_CBSIZE		256		/* Console I/O Buffer Size */
#endif

#define CFG_PBSIZE (CFG_CBSIZE+sizeof(CFG_PROMPT)+16) /* Print Buffer Size */
#define CFG_MAXARGS		16		/* max number of command args */
#define CFG_BARGSIZE		CFG_CBSIZE	/* Boot Argument Buffer Size */

#define CFG_LOAD_ADDR		0x00100000

#define CFG_MEMTEST_START	0x400
#define CFG_MEMTEST_END		0x380000

#define CFG_HZ			(50000000 / 64)
#define CFG_CLK			100000000

#define CFG_MBAR		0x40000000	/* Register Base Addrs */

/*
 * Ethernet
 */
#define CONFIG_MCFFEC
#ifdef CONFIG_MCFFEC
#	define CONFIG_NET_MULTI		1
#define CONFIG_MII		1
#	define CFG_DISCOVER_PHY
#	define CFG_RX_ETH_BUFFER	8
#	define CFG_FAULT_ECHO_LINK_DOWN

#	define CFG_FEC0_PINMUX		0
#	define CFG_FEC0_MIIBASE		CFG_FEC0_IOBASE
#	define MCFFEC_TOUT_LOOP 	50000
/* If CFG_DISCOVER_PHY is not defined - hardcoded */
#	ifndef CFG_DISCOVER_PHY
#		define FECDUPLEX	FULL
#		define FECSPEED		_100BASET
#	else
#		ifndef CFG_FAULT_ECHO_LINK_DOWN
#			define CFG_FAULT_ECHO_LINK_DOWN
#		endif
#	endif			/* CFG_DISCOVER_PHY */
#endif

/*
 * Definitions for initial stack pointer and data area (in DPRAM)
 */
#define CFG_INIT_RAM_ADDR	0x20000000
#define CFG_INIT_RAM_END	0x1000	/* End of used area in internal SRAM */
#define CFG_GBL_DATA_SIZE	64	/* size in bytes reserved for initial data */
#define CFG_GBL_DATA_OFFSET	(CFG_INIT_RAM_END - CFG_GBL_DATA_SIZE)
#define CFG_INIT_SP_OFFSET	CFG_GBL_DATA_OFFSET

/*
 * Start addresses for the final memory configuration
 * (Set up by the startup code)
 * Please note that CFG_SDRAM_BASE _must_ start at 0
 */
#define CFG_SDRAM_BASE		0x00000000
#define CFG_SDRAM_SIZE		16		/* SDRAM size in MB */
#define CFG_FLASH_BASE		0xff800000

#ifdef CONFIG_MONITOR_IS_IN_RAM
#define CFG_MONITOR_BASE	0x20000
#else /* !CONFIG_MONITOR_IS_IN_RAM */
#define CFG_MONITOR_BASE	(CFG_FLASH_BASE + 0x400)
#endif /* CONFIG_MONITOR_IS_IN_RAM */

#define CFG_MONITOR_LEN		0x20000
#define CFG_MALLOC_LEN		(256 << 10)
#define CFG_BOOTPARAMS_LEN	(64*1024)

/*
 * For booting Linux, the board info and command line data
 * have to be in the first 8 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization ??
 */
#define CFG_BOOTMAPSZ		(CFG_SDRAM_BASE + (CFG_SDRAM_SIZE << 20))

/* FLASH organization */
#define CFG_MAX_FLASH_BANKS	1	/* max number of memory banks */
#define CFG_MAX_FLASH_SECT	128	/* max number of sectors on one chip */
#define CFG_FLASH_ERASE_TOUT	1000

#define CFG_FLASH_SIZE		0x800000
/*
 * #define CFG_FLASH_USE_BUFFER_WRITE	1
 */

/* Cache Configuration */
#define CFG_CACHELINE_SIZE	16

/* Port configuration */
#define CFG_FECI2C		0xF0


/* Dynamic MTD partition support */
#define CONFIG_JFFS2_CMDLINE
#define MTDIDS_DEFAULT		"nor0=idmr-0"

#define MTDPARTS_DEFAULT	"mtdparts=idmr-0:128k(u-boot),"	\
						"64k(env),"	\
						"640k(kernel),"	\
						"2m(rootfs),"	\
						"-(user)";

#if defined(CONFIG_CMD_MII)
#error "MII commands don't work on iDMR board and should not be enabled."
#endif

#endif /* _IDMR_H */
