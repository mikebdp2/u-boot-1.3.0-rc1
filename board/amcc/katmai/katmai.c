/*
 * (C) Copyright 2007
 * Stefan Roese, DENX Software Engineering, sr@denx.de.
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
 *
 */

#include <common.h>
#include <ppc4xx.h>
#include <asm/processor.h>
#include <i2c.h>
#include <asm-ppc/io.h>
#include <asm-ppc/gpio.h>

#include "../cpu/ppc4xx/440spe_pcie.h"

#undef PCIE_ENDPOINT
/* #define PCIE_ENDPOINT 1 */

int ppc440spe_init_pcie_rootport(int port);
void ppc440spe_setup_pcie(struct pci_controller *hose, int port);

int board_early_init_f (void)
{
	unsigned long mfr;

	/*----------------------------------------------------------------------+
	 * Interrupt controller setup for the Katmai 440SPe Evaluation board.
	 *-----------------------------------------------------------------------+
	 *-----------------------------------------------------------------------+
	 * Interrupt | Source                            | Pol.  | Sensi.| Crit. |
	 *-----------+-----------------------------------+-------+-------+-------+
	 * IRQ 00    | UART0                             | High  | Level | Non   |
	 * IRQ 01    | UART1                             | High  | Level | Non   |
	 * IRQ 02    | IIC0                              | High  | Level | Non   |
	 * IRQ 03    | IIC1                              | High  | Level | Non   |
	 * IRQ 04    | PCI0X0 MSG IN                     | High  | Level | Non   |
	 * IRQ 05    | PCI0X0 CMD Write                  | High  | Level | Non   |
	 * IRQ 06    | PCI0X0 Power Mgt                  | High  | Level | Non   |
	 * IRQ 07    | PCI0X0 VPD Access                 | Rising| Edge  | Non   |
	 * IRQ 08    | PCI0X0 MSI level 0                | High  | Lvl/ed| Non   |
	 * IRQ 09    | External IRQ 15 - (PCI-Express)   | pgm H | Pgm   | Non   |
	 * IRQ 10    | UIC2 Non-critical Int.            | NA    | NA    | Non   |
	 * IRQ 11    | UIC2 Critical Interrupt           | NA    | NA    | Crit  |
	 * IRQ 12    | PCI Express MSI Level 0           | Rising| Edge  | Non   |
	 * IRQ 13    | PCI Express MSI Level 1           | Rising| Edge  | Non   |
	 * IRQ 14    | PCI Express MSI Level 2           | Rising| Edge  | Non   |
	 * IRQ 15    | PCI Express MSI Level 3           | Rising| Edge  | Non   |
	 * IRQ 16    | UIC3 Non-critical Int.            | NA    | NA    | Non   |
	 * IRQ 17    | UIC3 Critical Interrupt           | NA    | NA    | Crit  |
	 * IRQ 18    | External IRQ 14 - (PCI-Express)   | Pgm   | Pgm   | Non   |
	 * IRQ 19    | DMA Channel 0 FIFO Full           | High  | Level | Non   |
	 * IRQ 20    | DMA Channel 0 Stat FIFO           | High  | Level | Non   |
	 * IRQ 21    | DMA Channel 1 FIFO Full           | High  | Level | Non   |
	 * IRQ 22    | DMA Channel 1 Stat FIFO           | High  | Level | Non   |
	 * IRQ 23    | I2O Inbound Doorbell              | High  | Level | Non   |
	 * IRQ 24    | Inbound Post List FIFO Not Empt   | High  | Level | Non   |
	 * IRQ 25    | I2O Region 0 LL PLB Write         | High  | Level | Non   |
	 * IRQ 26    | I2O Region 1 LL PLB Write         | High  | Level | Non   |
	 * IRQ 27    | I2O Region 0 HB PLB Write         | High  | Level | Non   |
	 * IRQ 28    | I2O Region 1 HB PLB Write         | High  | Level | Non   |
	 * IRQ 29    | GPT Down Count Timer              | Rising| Edge  | Non   |
	 * IRQ 30    | UIC1 Non-critical Int.            | NA    | NA    | Non   |
	 * IRQ 31    | UIC1 Critical Interrupt           | NA    | NA    | Crit. |
	 *------------------------------------------------------------------------
	 * IRQ 32    | Ext. IRQ 13 - (PCI-Express)       |pgm (H)|pgm/Lvl| Non   |
	 * IRQ 33    | MAL Serr                          | High  | Level | Non   |
	 * IRQ 34    | MAL Txde                          | High  | Level | Non   |
	 * IRQ 35    | MAL Rxde                          | High  | Level | Non   |
	 * IRQ 36    | DMC CE or DMC UE                  | High  | Level | Non   |
	 * IRQ 37    | EBC or UART2                      | High  |Lvl Edg| Non   |
	 * IRQ 38    | MAL TX EOB                        | High  | Level | Non   |
	 * IRQ 39    | MAL RX EOB                        | High  | Level | Non   |
	 * IRQ 40    | PCIX0 MSI Level 1                 | High  |Lvl Edg| Non   |
	 * IRQ 41    | PCIX0 MSI level 2                 | High  |Lvl Edg| Non   |
	 * IRQ 42    | PCIX0 MSI level 3                 | High  |Lvl Edg| Non   |
	 * IRQ 43    | L2 Cache                          | Risin | Edge  | Non   |
	 * IRQ 44    | GPT Compare Timer 0               | Risin | Edge  | Non   |
	 * IRQ 45    | GPT Compare Timer 1               | Risin | Edge  | Non   |
	 * IRQ 46    | GPT Compare Timer 2               | Risin | Edge  | Non   |
	 * IRQ 47    | GPT Compare Timer 3               | Risin | Edge  | Non   |
	 * IRQ 48    | GPT Compare Timer 4               | Risin | Edge  | Non   |
	 * IRQ 49    | Ext. IRQ 12 - PCI-X               |pgm/Fal|pgm/Lvl| Non   |
	 * IRQ 50    | Ext. IRQ 11 -                     |pgm (H)|pgm/Lvl| Non   |
	 * IRQ 51    | Ext. IRQ 10 -                     |pgm (H)|pgm/Lvl| Non   |
	 * IRQ 52    | Ext. IRQ 9                        |pgm (H)|pgm/Lvl| Non   |
	 * IRQ 53    | Ext. IRQ 8                        |pgm (H)|pgm/Lvl| Non   |
	 * IRQ 54    | DMA Error                         | High  | Level | Non   |
	 * IRQ 55    | DMA I2O Error                     | High  | Level | Non   |
	 * IRQ 56    | Serial ROM                        | High  | Level | Non   |
	 * IRQ 57    | PCIX0 Error                       | High  | Edge  | Non   |
	 * IRQ 58    | Ext. IRQ 7-                       |pgm (H)|pgm/Lvl| Non   |
	 * IRQ 59    | Ext. IRQ 6-                       |pgm (H)|pgm/Lvl| Non   |
	 * IRQ 60    | EMAC0 Interrupt                   | High  | Level | Non   |
	 * IRQ 61    | EMAC0 Wake-up                     | High  | Level | Non   |
	 * IRQ 62    | Reserved                          | High  | Level | Non   |
	 * IRQ 63    | XOR                               | High  | Level | Non   |
	 *-----------------------------------------------------------------------
	 * IRQ 64    | PE0 AL                            | High  | Level | Non   |
	 * IRQ 65    | PE0 VPD Access                    | Risin | Edge  | Non   |
	 * IRQ 66    | PE0 Hot Reset Request             | Risin | Edge  | Non   |
	 * IRQ 67    | PE0 Hot Reset Request             | Falli | Edge  | Non   |
	 * IRQ 68    | PE0 TCR                           | High  | Level | Non   |
	 * IRQ 69    | PE0 BusMaster VCO                 | Falli | Edge  | Non   |
	 * IRQ 70    | PE0 DCR Error                     | High  | Level | Non   |
	 * IRQ 71    | Reserved                          | N/A   | N/A   | Non   |
	 * IRQ 72    | PE1 AL                            | High  | Level | Non   |
	 * IRQ 73    | PE1 VPD Access                    | Risin | Edge  | Non   |
	 * IRQ 74    | PE1 Hot Reset Request             | Risin | Edge  | Non   |
	 * IRQ 75    | PE1 Hot Reset Request             | Falli | Edge  | Non   |
	 * IRQ 76    | PE1 TCR                           | High  | Level | Non   |
	 * IRQ 77    | PE1 BusMaster VCO                 | Falli | Edge  | Non   |
	 * IRQ 78    | PE1 DCR Error                     | High  | Level | Non   |
	 * IRQ 79    | Reserved                          | N/A   | N/A   | Non   |
	 * IRQ 80    | PE2 AL                            | High  | Level | Non   |
	 * IRQ 81    | PE2 VPD Access                    | Risin | Edge  | Non   |
	 * IRQ 82    | PE2 Hot Reset Request             | Risin | Edge  | Non   |
	 * IRQ 83    | PE2 Hot Reset Request             | Falli | Edge  | Non   |
	 * IRQ 84    | PE2 TCR                           | High  | Level | Non   |
	 * IRQ 85    | PE2 BusMaster VCO                 | Falli | Edge  | Non   |
	 * IRQ 86    | PE2 DCR Error                     | High  | Level | Non   |
	 * IRQ 87    | Reserved                          | N/A   | N/A   | Non   |
	 * IRQ 88    | External IRQ(5)                   | Progr | Progr | Non   |
	 * IRQ 89    | External IRQ 4 - Ethernet         | Progr | Progr | Non   |
	 * IRQ 90    | External IRQ 3 - PCI-X            | Progr | Progr | Non   |
	 * IRQ 91    | External IRQ 2 - PCI-X            | Progr | Progr | Non   |
	 * IRQ 92    | External IRQ 1 - PCI-X            | Progr | Progr | Non   |
	 * IRQ 93    | External IRQ 0 - PCI-X            | Progr | Progr | Non   |
	 * IRQ 94    | Reserved                          | N/A   | N/A   | Non   |
	 * IRQ 95    | Reserved                          | N/A   | N/A   | Non   |
	 *-----------------------------------------------------------------------
	 * IRQ 96    | PE0 INTA                          | High  | Level | Non   |
	 * IRQ 97    | PE0 INTB                          | High  | Level | Non   |
	 * IRQ 98    | PE0 INTC                          | High  | Level | Non   |
	 * IRQ 99    | PE0 INTD                          | High  | Level | Non   |
	 * IRQ 100   | PE1 INTA                          | High  | Level | Non   |
	 * IRQ 101   | PE1 INTB                          | High  | Level | Non   |
	 * IRQ 102   | PE1 INTC                          | High  | Level | Non   |
	 * IRQ 103   | PE1 INTD                          | High  | Level | Non   |
	 * IRQ 104   | PE2 INTA                          | High  | Level | Non   |
	 * IRQ 105   | PE2 INTB                          | High  | Level | Non   |
	 * IRQ 106   | PE2 INTC                          | High  | Level | Non   |
	 * IRQ 107   | PE2 INTD                          | Risin | Edge  | Non   |
	 * IRQ 108   | PCI Express MSI Level 4           | Risin | Edge  | Non   |
	 * IRQ 109   | PCI Express MSI Level 5           | Risin | Edge  | Non   |
	 * IRQ 110   | PCI Express MSI Level 6           | Risin | Edge  | Non   |
	 * IRQ 111   | PCI Express MSI Level 7           | Risin | Edge  | Non   |
	 * IRQ 116   | PCI Express MSI Level 12          | Risin | Edge  | Non   |
	 * IRQ 112   | PCI Express MSI Level 8           | Risin | Edge  | Non   |
	 * IRQ 113   | PCI Express MSI Level 9           | Risin | Edge  | Non   |
	 * IRQ 114   | PCI Express MSI Level 10          | Risin | Edge  | Non   |
	 * IRQ 115   | PCI Express MSI Level 11          | Risin | Edge  | Non   |
	 * IRQ 117   | PCI Express MSI Level 13          | Risin | Edge  | Non   |
	 * IRQ 118   | PCI Express MSI Level 14          | Risin | Edge  | Non   |
	 * IRQ 119   | PCI Express MSI Level 15          | Risin | Edge  | Non   |
	 * IRQ 120   | PCI Express MSI Level 16          | Risin | Edge  | Non   |
	 * IRQ 121   | PCI Express MSI Level 17          | Risin | Edge  | Non   |
	 * IRQ 122   | PCI Express MSI Level 18          | Risin | Edge  | Non   |
	 * IRQ 123   | PCI Express MSI Level 19          | Risin | Edge  | Non   |
	 * IRQ 124   | PCI Express MSI Level 20          | Risin | Edge  | Non   |
	 * IRQ 125   | PCI Express MSI Level 21          | Risin | Edge  | Non   |
	 * IRQ 126   | PCI Express MSI Level 22          | Risin | Edge  | Non   |
	 * IRQ 127   | PCI Express MSI Level 23          | Risin | Edge  | Non   |
	 *-----------+-----------------------------------+-------+-------+-------+ */
	/*-------------------------------------------------------------------------+
	 * Put UICs in PowerPC440SPemode.
	 * Initialise UIC registers.  Clear all interrupts.  Disable all interrupts.
	 * Set critical interrupt values.  Set interrupt polarities.  Set interrupt
	 * trigger levels.  Make bit 0 High  priority.  Clear all interrupts again.
	 *------------------------------------------------------------------------*/
	mtdcr (uic3sr, 0xffffffff);	/* Clear all interrupts */
	mtdcr (uic3er, 0x00000000);	/* disable all interrupts */
	mtdcr (uic3cr, 0x00000000);	/* Set Critical / Non Critical interrupts: */
	mtdcr (uic3pr, 0xffffffff);	/* Set Interrupt Polarities*/
	mtdcr (uic3tr, 0x001fffff);	/* Set Interrupt Trigger Levels */
	mtdcr (uic3vr, 0x00000001);	/* Set Vect base=0,INT31 Highest priority */
	mtdcr (uic3sr, 0x00000000);	/* clear all  interrupts*/
	mtdcr (uic3sr, 0xffffffff);	/* clear all  interrupts*/


	mtdcr (uic2sr, 0xffffffff);	/* Clear all interrupts */
	mtdcr (uic2er, 0x00000000);	/* disable all interrupts*/
	mtdcr (uic2cr, 0x00000000);	/* Set Critical / Non Critical interrupts*/
	mtdcr (uic2pr, 0xebebebff);	/* Set Interrupt Polarities*/
	mtdcr (uic2tr, 0x74747400);	/* Set Interrupt Trigger Levels */
	mtdcr (uic2vr, 0x00000001);	/* Set Vect base=0,INT31 Highest priority */
	mtdcr (uic2sr, 0x00000000);	/* clear all interrupts */
	mtdcr (uic2sr, 0xffffffff);	/* clear all interrupts */

	mtdcr (uic1sr, 0xffffffff);	/* Clear all interrupts*/
	mtdcr (uic1er, 0x00000000);	/* disable all interrupts*/
	mtdcr (uic1cr, 0x00000000);	/* Set Critical / Non Critical interrupts*/
	mtdcr (uic1pr, 0xffffffff);	/* Set Interrupt Polarities */
	mtdcr (uic1tr, 0x001f8040);	/* Set Interrupt Trigger Levels*/
	mtdcr (uic1vr, 0x00000001);	/* Set Vect base=0,INT31 Highest priority */
	mtdcr (uic1sr, 0x00000000);	/* clear all interrupts*/
	mtdcr (uic1sr, 0xffffffff);	/* clear all interrupts*/

	mtdcr (uic0sr, 0xffffffff);	/* Clear all interrupts */
	mtdcr (uic0er, 0x00000000);	/* disable all interrupts excepted cascade    to be checked */
	mtdcr (uic0cr, 0x00104001);	/* Set Critical / Non Critical interrupts*/
	mtdcr (uic0pr, 0xffffffff);	/* Set Interrupt Polarities*/
	mtdcr (uic0tr, 0x010f0004);	/* Set Interrupt Trigger Levels */
	mtdcr (uic0vr, 0x00000001);	/* Set Vect base=0,INT31 Highest priority */
	mtdcr (uic0sr, 0x00000000);	/* clear all interrupts*/
	mtdcr (uic0sr, 0xffffffff);	/* clear all interrupts*/

/* SDR0_MFR should be part of Ethernet init */
	mfsdr (sdr_mfr, mfr);
	mfr &= ~SDR0_MFR_ECS_MASK;
/*	mtsdr(sdr_mfr, mfr); */

	mtsdr(SDR0_PFC0, CFG_PFC0);

	out32(GPIO0_OR, CFG_GPIO_OR);
	out32(GPIO0_ODR, CFG_GPIO_ODR);
	out32(GPIO0_TCR, CFG_GPIO_TCR);

	return 0;
}

int checkboard (void)
{
	char *s = getenv("serial#");

	printf("Board: Katmai - AMCC 440SPe Evaluation Board");
	if (s != NULL) {
		puts(", serial# ");
		puts(s);
	}
	putc('\n');

	return 0;
}

#if defined(CFG_DRAM_TEST)
int testdram (void)
{
	uint *pstart = (uint *) 0x00000000;
	uint *pend = (uint *) 0x08000000;
	uint *p;

	for (p = pstart; p < pend; p++)
		*p = 0xaaaaaaaa;

	for (p = pstart; p < pend; p++) {
		if (*p != 0xaaaaaaaa) {
			printf ("SDRAM test fails at: %08x\n", (uint) p);
			return 1;
		}
	}

	for (p = pstart; p < pend; p++)
		*p = 0x55555555;

	for (p = pstart; p < pend; p++) {
		if (*p != 0x55555555) {
			printf ("SDRAM test fails at: %08x\n", (uint) p);
			return 1;
		}
	}
	return 0;
}
#endif

/*************************************************************************
 *  pci_pre_init
 *
 *  This routine is called just prior to registering the hose and gives
 *  the board the opportunity to check things. Returning a value of zero
 *  indicates that things are bad & PCI initialization should be aborted.
 *
 *	Different boards may wish to customize the pci controller structure
 *	(add regions, override default access routines, etc) or perform
 *	certain pre-initialization actions.
 *
 ************************************************************************/
#if defined(CONFIG_PCI)
int pci_pre_init(struct pci_controller * hose )
{
	unsigned long strap;

	/*-------------------------------------------------------------------+
	 *	The katmai board is always configured as the host & requires the
	 *	PCI arbiter to be enabled.
	 *-------------------------------------------------------------------*/
	mfsdr(sdr_sdstp1, strap);
	if( (strap & SDR0_SDSTP1_PAE_MASK) == 0 ) {
		printf("PCI: SDR0_STRP1[%08lX] - PCI Arbiter disabled.\n",strap);
		return 0;
	}

	return 1;
}
#endif	/* defined(CONFIG_PCI) */

/*************************************************************************
 *  pci_target_init
 *
 *	The bootstrap configuration provides default settings for the pci
 *	inbound map (PIM). But the bootstrap config choices are limited and
 *	may not be sufficient for a given board.
 *
 ************************************************************************/
#if defined(CONFIG_PCI) && defined(CFG_PCI_TARGET_INIT)
void pci_target_init(struct pci_controller * hose )
{
	DECLARE_GLOBAL_DATA_PTR;

	/*-------------------------------------------------------------------+
	 * Disable everything
	 *-------------------------------------------------------------------*/
	out32r( PCIX0_PIM0SA, 0 ); /* disable */
	out32r( PCIX0_PIM1SA, 0 ); /* disable */
	out32r( PCIX0_PIM2SA, 0 ); /* disable */
	out32r( PCIX0_EROMBA, 0 ); /* disable expansion rom */

	/*-------------------------------------------------------------------+
	 * Map all of SDRAM to PCI address 0x0000_0000. Note that the 440
	 * strapping options to not support sizes such as 128/256 MB.
	 *-------------------------------------------------------------------*/
	out32r( PCIX0_PIM0LAL, CFG_SDRAM_BASE );
	out32r( PCIX0_PIM0LAH, 0 );
	out32r( PCIX0_PIM0SA, ~(gd->ram_size - 1) | 1 );
	out32r( PCIX0_BAR0, 0 );

	/*-------------------------------------------------------------------+
	 * Program the board's subsystem id/vendor id
	 *-------------------------------------------------------------------*/
	out16r( PCIX0_SBSYSVID, CFG_PCI_SUBSYS_VENDORID );
	out16r( PCIX0_SBSYSID, CFG_PCI_SUBSYS_DEVICEID );

	out16r( PCIX0_CMD, in16r(PCIX0_CMD) | PCI_COMMAND_MEMORY );
}
#endif	/* defined(CONFIG_PCI) && defined(CFG_PCI_TARGET_INIT) */

#if defined(CONFIG_PCI)
/*************************************************************************
 *  is_pci_host
 *
 *	This routine is called to determine if a pci scan should be
 *	performed. With various hardware environments (especially cPCI and
 *	PPMC) it's insufficient to depend on the state of the arbiter enable
 *	bit in the strap register, or generic host/adapter assumptions.
 *
 *	Rather than hard-code a bad assumption in the general 440 code, the
 *	440 pci code requires the board to decide at runtime.
 *
 *	Return 0 for adapter mode, non-zero for host (monarch) mode.
 *
 *
 ************************************************************************/
int is_pci_host(struct pci_controller *hose)
{
	/* The katmai board is always configured as host. */
	return 1;
}

int katmai_pcie_card_present(int port)
{
	u32 val;

	val = in32(GPIO0_IR);
	switch (port) {
	case 0:
		return !(val & GPIO_VAL(CFG_GPIO_PCIE_PRESENT0));
	case 1:
		return !(val & GPIO_VAL(CFG_GPIO_PCIE_PRESENT1));
	case 2:
		return !(val & GPIO_VAL(CFG_GPIO_PCIE_PRESENT2));
	default:
		return 0;
	}
}

static struct pci_controller pcie_hose[3] = {{0},{0},{0}};

void pcie_setup_hoses(void)
{
	struct pci_controller *hose;
	int i, bus;

	/*
	 * assume we're called after the PCIX hose is initialized, which takes
	 * bus ID 0 and therefore start numbering PCIe's from 1.
	 */
	bus = 1;
	for (i = 0; i <= 2; i++) {
		/* Check for katmai card presence */
		if (!katmai_pcie_card_present(i))
			continue;

#ifdef PCIE_ENDPOINT
 		if (ppc440spe_init_pcie_endport(i)) {
#else
		if (ppc440spe_init_pcie_rootport(i)) {
#endif
			printf("PCIE%d: initialization failed\n", i);
			continue;
		}

		hose = &pcie_hose[i];
		hose->first_busno = bus;
		hose->last_busno  = bus;
		bus++;

		/* setup mem resource */
		pci_set_region(hose->regions + 0,
			       CFG_PCIE_MEMBASE + i * CFG_PCIE_MEMSIZE,
			       CFG_PCIE_MEMBASE + i * CFG_PCIE_MEMSIZE,
			       CFG_PCIE_MEMSIZE,
			       PCI_REGION_MEM
			);
		hose->region_count = 1;
		pci_register_hose(hose);

#ifdef PCIE_ENDPOINT
		ppc440spe_setup_pcie_endpoint(hose, i);
		/*
		 * Reson for no scanning is endpoint can not generate
		 * upstream configuration accesses.
		 */
#else
		ppc440spe_setup_pcie_rootpoint(hose, i);
		/*
		 * Config access can only go down stream
		 */
		hose->last_busno = pci_hose_scan(hose);
#endif
	}
}
#endif	/* defined(CONFIG_PCI) */

int misc_init_f (void)
{
	uint reg;
#if defined(CONFIG_STRESS)
	uint i ;
	uint disp;
#endif

	/* minimal init for PCIe */
#if 0 /* test-only: test endpoint at some time, for now rootpoint only */
	/* pci express 0 Endpoint Mode */
	mfsdr(SDR0_PE0DLPSET, reg);
	reg &= (~0x00400000);
	mtsdr(SDR0_PE0DLPSET, reg);
#else
	/* pci express 0 Rootpoint  Mode */
	mfsdr(SDR0_PE0DLPSET, reg);
	reg |= 0x00400000;
	mtsdr(SDR0_PE0DLPSET, reg);
#endif
	/* pci express 1 Rootpoint  Mode */
	mfsdr(SDR0_PE1DLPSET, reg);
	reg |= 0x00400000;
	mtsdr(SDR0_PE1DLPSET, reg);
	/* pci express 2 Rootpoint  Mode */
	mfsdr(SDR0_PE2DLPSET, reg);
	reg |= 0x00400000;
	mtsdr(SDR0_PE2DLPSET, reg);

#if defined(CONFIG_STRESS)
	/*
	 * All this setting done by linux only needed by stress an charac. test
	 * procedure
	 * PCIe 1 Rootpoint PCIe2 Endpoint
	 * PCIe 0 FIR Pre-emphasis Filter Coefficients & Transmit Driver Power Level
	 */
	for (i=0,disp=0; i<8; i++,disp+=3) {
		mfsdr(SDR0_PE0HSSSET1L0+disp, reg);
		reg |= 0x33000000;
		mtsdr(SDR0_PE0HSSSET1L0+disp, reg);
	}

	/*PCIe 1 FIR Pre-emphasis Filter Coefficients & Transmit Driver Power Level */
	for (i=0,disp=0; i<4; i++,disp+=3) {
		mfsdr(SDR0_PE1HSSSET1L0+disp, reg);
		reg |= 0x33000000;
		mtsdr(SDR0_PE1HSSSET1L0+disp, reg);
	}

	/*PCIE 2 FIR Pre-emphasis Filter Coefficients & Transmit Driver Power Level */
	for (i=0,disp=0; i<4; i++,disp+=3) {
		mfsdr(SDR0_PE2HSSSET1L0+disp, reg);
		reg |= 0x33000000;
		mtsdr(SDR0_PE2HSSSET1L0+disp, reg);
	}

	reg = 0x21242222;
	mtsdr(SDR0_PE2UTLSET1, reg);
	reg = 0x11000000;
	mtsdr(SDR0_PE2UTLSET2, reg);
	/* pci express 1 Endpoint  Mode */
	reg = 0x00004000;
	mtsdr(SDR0_PE2DLPSET, reg);

	mtsdr(SDR0_UART1, 0x2080005a);	/* patch for TG */
#endif

	return 0;
}

#ifdef CONFIG_POST
/*
 * Returns 1 if keys pressed to start the power-on long-running tests
 * Called from board_init_f().
 */
int post_hotkeys_pressed(void)
{
	return (ctrlc());
}
#endif
