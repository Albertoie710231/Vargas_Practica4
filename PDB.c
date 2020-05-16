/*
 * PDB.c
 *
 *  Created on: 7 may 2020
 *      Author: alber
 */

#include "MK64F12.h"

void PDB_init(void)
{
	SIM->SCGC6 |= SIM_SCGC6_PDB(1);
	/**1)Deshabilitar operación back-to-back pre-tiggrer
	 * 2)Activar la salidad del pre-trigger
	 * 3)Activar el pre-trigger
	 * 4)Utilizar modo continuo de operación
	 * 5)Seleccionar Software Trigger en trigger sourse
	 * 6)Escribir 1 en LDOK
	 * 7)Configurar Frecuencia de operación del PDB a 8 KHz
	 */
	PDB0->CH[0].C1 &= (~PDB_C1_BB_MASK);
	PDB0->CH[0].C1 |= PDB_C1_TOS_MASK;
	PDB0->CH[0].C1 |= PDB_C1_EN(1);
	PDB0->SC |= PDB_SC_CONT(1);
	PDB0->SC |= PDB_SC_TRGSEL(0x0F);
	PDB0->SC |= PDB_SC_LDOK(1);
	PDB0->MOD = ((6000000/8000)-1);//Frecuencia
	PDB0->IDLY = ((6000000/8000)-1);
	PDB0->SC |= PDB_SC_PDBEN(1);
}

void PDB_reset_counter(void)
{
	PDB0->SC |= PDB_SC_SWTRIG(1);
}
