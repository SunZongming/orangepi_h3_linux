/*
 * Copyright (C) 2011 Simon Guinot <sguinot@lacie.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef _CONFIG_NETSPACE_V2_H
#define _CONFIG_NETSPACE_V2_H

/*
 * Machine number definition
 */
#if defined(CONFIG_INETSPACE_V2)
#define CONFIG_MACH_TYPE		MACH_TYPE_INETSPACE_V2
#define CONFIG_IDENT_STRING		" IS v2"
#elif defined(CONFIG_NETSPACE_V2)
#define CONFIG_MACH_TYPE		MACH_TYPE_NETSPACE_V2
#define CONFIG_IDENT_STRING		" NS v2"
#elif defined(CONFIG_NETSPACE_MAX_V2)
#define CONFIG_MACH_TYPE		MACH_TYPE_NETSPACE_MAX_V2
#define CONFIG_IDENT_STRING		" NS Max v2"
#else
#error "Unknown board"
#endif

/*
 * High Level Configuration Options (easy to change)
 */
#define CONFIG_FEROCEON_88FR131		/* CPU Core subversion */
#define CONFIG_KIRKWOOD			/* SOC Family Name */
#define CONFIG_KW88F6281		/* SOC Name */
#define CONFIG_SKIP_LOWLEVEL_INIT	/* disable board lowlevel_init */

/*
 * Commands configuration
 */
#define CONFIG_SYS_NO_FLASH		/* Declare no flash (NOR/SPI) */
#include <config_cmd_default.h>
#define CONFIG_CMD_ENV
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_CMD_SF
#define CONFIG_CMD_I2C
#define CONFIG_CMD_IDE
#define CONFIG_CMD_USB

/*
 * Core clock definition.
 */
#define CONFIG_SYS_TCLK			166000000 /* 166MHz */

/*
 * mv-common.h should be defined after CMD configs since it used them
 * to enable certain macros
 */
#define CONFIG_NR_DRAM_BANKS		2
#include "mv-common.h"

/* Remove or override few declarations from mv-common.h */
#undef CONFIG_RBTREE
#undef CONFIG_ENV_SPI_MAX_HZ
#undef CONFIG_SYS_IDE_MAXBUS
#undef CONFIG_SYS_IDE_MAXDEVICE
#undef CONFIG_SYS_PROMPT
#define CONFIG_ENV_SPI_MAX_HZ           20000000 /* 20Mhz */
#define CONFIG_SYS_IDE_MAXBUS           1
#define CONFIG_SYS_IDE_MAXDEVICE        1
#define CONFIG_SYS_PROMPT		"ns2> "

/*
 * Ethernet Driver configuration
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_MVGBE_PORTS		{1, 0} /* enable port 0 only */
#define CONFIG_NETCONSOLE
#endif

/*
 * SATA Driver configuration
 */
#ifdef CONFIG_MVSATA_IDE
#define CONFIG_SYS_ATA_IDE0_OFFSET      MV_SATA_PORT0_OFFSET
/* Network Space Max v2 use 2 SATA ports */
#ifdef CONFIG_NETSPACE_MAX_V2
#define CONFIG_SYS_ATA_IDE1_OFFSET      MV_SATA_PORT1_OFFSET
#endif
#endif

/*
 * Enable GPI0 support
 */
#define CONFIG_KIRKWOOD_GPIO

/*
 * File systems support
 */
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT

/*
 * Use the HUSH parser
 */
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "

/*
 * Console configuration
 */
#define CONFIG_CONSOLE_MUX
#define CONFIG_SYS_CONSOLE_IS_IN_ENV

/*
 * Enable device tree support
 */
#define CONFIG_OF_LIBFDT

/*
 * Environment variables configurations
 */
#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_SECT_SIZE		0x10000	/* 64KB */
#define CONFIG_ENV_SIZE			0x1000	/* 4KB */
#define CONFIG_ENV_ADDR			0x70000
#define CONFIG_ENV_OFFSET		0x70000	/* env starts here */

/*
 * Default environment variables
 */
#define CONFIG_BOOTARGS "console=ttyS0,115200"

#define CONFIG_BOOTCOMMAND					\
	"dhcp && run netconsole; "				\
	"if run usbload || run diskload; then bootm; fi"

#define CONFIG_EXTRA_ENV_SETTINGS				\
	"stdin=serial\0"					\
	"stdout=serial\0"					\
	"stderr=serial\0"					\
	"bootfile=uImage\0"					\
	"loadaddr=0x800000\0"					\
	"autoload=no\0"						\
	"netconsole="						\
		"set stdin $stdin,nc; "				\
		"set stdout $stdout,nc; "			\
		"set stderr $stderr,nc;\0"			\
	"diskload=ide reset && "				\
		"ext2load ide 0:1 $loadaddr /boot/$bootfile\0"	\
	"usbload=usb start && "					\
		"fatload usb 0:1 $loadaddr /boot/$bootfile\0"

#endif /* _CONFIG_NETSPACE_V2_H */
