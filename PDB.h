/*
 * PDB.h
 *
 *  Created on: 7 may 2020
 *      Author: alber
 */

#ifndef PDB_H_
#define PDB_H_

#define SOURCE_CLK 60000000U
#define FREQ_MUESTR 8000U

void PDB_clk_gating(void);

void PDB_init_adc(void);

void PDB_init_dac(void);

void PDB_enable(void);

void PDB_desable(void);

#endif /* PDB_H_ */
