/*
 * PDB.c
 *
 *  Created on: 7 may 2020
 *      Author: alber
 */

#include "MK64F12.h"
#include "PDB.h"

void PDB_clk_gating(void)
{
	SIM->SCGC6 |= SIM_SCGC6_PDB(1);
}

void PDB_init_adc(void)
{
	/**1)Deshabilitar operación back-to-back pre-tiggrer
	 * 2)Activar la salidad del pre-trigger
	 * 3)Activar el pre-trigger
	 * 4)Utilizar modo continuo de operación
	 * 5)Seleccionar Software Trigger en trigger sourse
	 * 6)Escribir 1 en LDOK
	 * 7)Configurar Frecuencia de operación del PDB a 8 KHz
	 */

	/** Deshabilita registros de PDB que controlan DMA **/
	PDB0->SC &= ~PDB_SC_DMAEN_MASK;

	PDB0->CH[0].C1 &= (~PDB_C1_BB_MASK);
	PDB0->CH[0].C1 |= PDB_C1_TOS_MASK;
	PDB0->CH[0].C1 |= PDB_C1_EN(1);
	PDB0->SC |= PDB_SC_CONT(1);
	PDB0->SC |= PDB_SC_TRGSEL(0x0F);
	PDB0->MOD = ((SOURCE_CLK/FREQ_MUESTR)-1);//Frecuencia
	PDB0->IDLY = ((SOURCE_CLK/FREQ_MUESTR)-1);
	PDB0->SC |= PDB_SC_PDBEN_MASK;
	PDB0->SC |= PDB_SC_LDOK(1);

	PDB0->SC |= PDB_SC_SWTRIG(1);
}

void PDB_init_dac(void)
{
/**
	1)Deshabilitar el PDB
	2)Deshabilitar el trigger por software (bit 16 SC)
	3)Configurar el trigger y periodo del DAC
	4)Habilitar el PDB y la carga en registros (ver bit LDOK)
	5)Habilitar el trigger por software (bit 16 SC)
*/

	PDB0->SC &= ~PDB_SC_PDBEN_MASK;
	PDB0->SC |= PDB_SC_SWTRIG(1);

/** Deshabilita registros de PDB que controlan ADC **/

	PDB0->CH[0].C1 &= (~PDB_C1_BB_MASK);
	PDB0->CH[0].C1 &= ~PDB_C1_TOS_MASK;
	PDB0->CH[0].C1 &= ~PDB_C1_EN(1);

	PDB0->SC |= PDB_SC_DMAEN_MASK;
	PDB0->MOD = ((SOURCE_CLK/FREQ_MUESTR)-1);//Frecuencia
	PDB0->IDLY = ((SOURCE_CLK/FREQ_MUESTR)-1);
	PDB0->SC |= PDB_SC_PDBEN_MASK;
	PDB0->SC |= PDB_SC_LDOK(1);
	PDB0->SC |= PDB_SC_SWTRIG(1);

}

void PDB_enable(void)
{
	PDB0->SC |= PDB_SC_PDBEN_MASK;
}

void PDB_desable(void)
{
	PDB0->SC &= ~PDB_SC_PDBEN_MASK;
}
