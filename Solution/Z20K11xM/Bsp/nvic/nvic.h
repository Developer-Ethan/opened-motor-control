#ifndef _NVIC_H
#define _NVIC_H

/** @} end of group HAL_Public_Types */
static inline void enable_all_interrupt() { __asm volatile("cpsie i"); }
static inline void disable_all_interrupt() { __asm volatile("cpsid i"); }

void Hal_SetupNvic(void);
void Hal_SetupInterrupts(isr_cb_t *PwmFaultIntCbf, isr_cb_t *StimIntCbf);
#endif