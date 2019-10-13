#include <stdint.h>

typedef struct
{
  volatile uint32_t CR;         /*!< RCC clock control register,                                  Address offset: 0x00 */
  volatile uint32_t CFGR;       /*!< RCC clock configuration register,                            Address offset: 0x04 */
  volatile uint32_t CIR;        /*!< RCC clock interrupt register,                                Address offset: 0x08 */
  volatile uint32_t APB2RSTR;   /*!< RCC APB2 peripheral reset register,                          Address offset: 0x0C */
  volatile uint32_t APB1RSTR;   /*!< RCC APB1 peripheral reset register,                          Address offset: 0x10 */
  volatile uint32_t AHBENR;     /*!< RCC AHB peripheral clock register,                           Address offset: 0x14 */
  volatile uint32_t APB2ENR;    /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x18 */
  volatile uint32_t APB1ENR;    /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x1C */
  volatile uint32_t BDCR;       /*!< RCC Backup domain control register,                          Address offset: 0x20 */ 
  volatile uint32_t CSR;        /*!< RCC clock control & status register,                         Address offset: 0x24 */
} RCC_TypeDef;
#define FLASH_BASE            ((uint32_t)0x08000000) /*!< FLASH base address in the alias region */
#define SRAM_BASE             ((uint32_t)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE           ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */
#define RCC_BASE              0x40021000
#define RCC                   ((RCC_TypeDef *) RCC_BASE)
#define RCC_AHBENR_GPIOBEN    ((uint32_t)0x00040000)        /*!< GPIOB clock enable */
#define RCC_AHBENR_GPIOCEN    ((uint32_t)0x00080000)        /*!< GPIOC clock enable */
#define RCC_APB2ENR_IOPA      0x00000004
#define RCC_APB2ENR_IOPB      0x00000008
#define RCC_APB2ENR_IOPC      0x00000010
#define RCC_APB2ENR_IOPD      0x00000020
#define RCC_APB2ENR_IOPE      0x00000040
#define RCC_APB2ENR_IOPF      0x00000080
#define RCC_APB2ENR_IOPG      0x00000100

#define GPIOA_BASE            0x40010800
#define GPIOB_BASE            0x40010C00
#define GPIOC_BASE            0x40011000
#define GPIOD_BASE            0x40011400
#define GPIOE_BASE            0x40011800
#define GPIOF_BASE            0x40011C00
#define GPIOG_BASE            0x40012000

#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)

typedef struct
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
}GPIO_TypeDef;

#define STACK_TOP 0x20000800   // just a tiny stack for demo

static void nmi_handler(void);
static void hardfault_handler(void);
int main(void);

uint32_t *myvectors[4]
__attribute__ ((section("vectors"))) = {
	(uint32_t *) STACK_TOP,         // stack pointer
	0x0A000024,              // code entry point
	(uint32_t *) nmi_handler,       // NMI handler (not really)
	(uint32_t *) hardfault_handler  // hard fault handler
};

void nmi_handler(void)
{
	for (;;);
}

void hardfault_handler(void)
{
	for (;;);
}

int main()
{
    *(volatile uint32_t *)0x40021018 = 0x00000008;
    *(volatile uint32_t *)0x40010C04 = 0x44444422;

	while (1) {
        *(volatile uint32_t *)0x40010C0C = 0x00000100;
        for(uint32_t i=8000*100; i>0; i--)
            asm("nop");
        *(volatile uint32_t *)0x40010C0C = 0x00000200;
        for(uint32_t i=2000*100; i>0; i--)
            asm("nop");
	}

	return 0;
}
