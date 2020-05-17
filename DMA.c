/*
 * DMA.c
 *
 *  Created on: 3 may 2020
 *      Author: alber
 */

#include "DMA.h"
#include "Bits.h"
#include "MK64F12.h"
#include "DAC.h"
#include "ADC.h"
#include "PDB.h"
#include <stdint.h>
#include <stdio.h>

#define SIZE_ARRAY 40000
#define NUM_STEPS (SIZE_ARRAY)
#define DMA_SOURCE_PDB (48u)

void DMA0_IRQHandler(void)
{
	DMA0->TCD[0].SADDR = (uint32_t)(ADC_biffer_address());/*defines source data address*/
	DMA0->CINT = 0;
	PDB_desable();
}


void DMA_clock_gating(void)
{
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
}


void DMA_init(void)
{

	DMAMUX->CHCFG[0] = 0;
	DMAMUX->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK | /*enables DMA MUX channel*/
					   DMAMUX_CHCFG_SOURCE(DMA_SOURCE_PDB);/*110000..PDB_Signal*/

	DMA0->ERQ = 0x01;//enables DMA0 request

	DMA0->TCD[0].SADDR = (uint32_t)(ADC_biffer_address());/*defines source data address*/
	DMA0->TCD[0].SOFF = 1;/*Source address signed offset;it is expressed in number of bytes*/
	DMA0->TCD[0].DADDR = (uint32_t)(&DAC0->DAT);/*defines destination data address*/
	DMA0->TCD[0].DOFF = 0;/*destination address signed offset;it is expressed in number of bytes*/

	/*CITER represents the number of minor loops that compose a major loop, every time a minor loop is completed CITTER is decremented by one.
	 * Once CITTER is 0 the DMA copy BITTER into CITTER and adjust SADDR and DADDR with the values specified in SLAST and DLAST_SGA respectively
	 *  SADDR  = SADDR + SLAST and DADDR + DLAST_SGA*/
	DMA0->TCD[0].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(NUM_STEPS);
	/* Once a major loop is completed, BITTER is copy to CITTER*/
	DMA0->TCD[0].BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(NUM_STEPS);
	DMA0->TCD[0].NBYTES_MLNO = 1;/*byte number*/

	DMA0->TCD[0].ATTR = DMA_ATTR_SSIZE(0)|DMA_ATTR_DSIZE(0);/*8 bit transfer size, in order to transfer see Kinetis user manual*/
	DMA0->TCD[0].SLAST = -(SIZE_ARRAY);//restores the source address to the initial value, which is expressed in the amount of bytes to restore*/
	DMA0->TCD[0].DLAST_SGA = 0;/*restores the destination address to the initial value, which is expressed in the amount of bytes to restore*/
	DMA0->TCD[0].CSR = DMA_CSR_INTMAJOR_MASK;/*The end-of-major loop interrupt is enabled*/

}
