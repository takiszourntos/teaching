/*
 * @brief SPI example
 * This example show how to use the SPI in 2 modes : Polling and Interrupt.
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "stdio.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
#define BUFFER_SIZE                         (0x100)

#define SPI_MASTER_MODE_SEL                 (0x31)
#define SPI_SLAVE_MODE_SEL                  (0x32)
#define SPI_MODE_SEL                        (SPI_MASTER_MODE_SEL)

#define SPI_POLLING_SEL                     (0x31)
#define SPI_INTERRUPT_SEL                   (0x32)
#if (SPI_MODE_SEL == SPI_SLAVE_MODE_SEL)
#define SPI_TRANSFER_MODE_SEL               (SPI_INTERRUPT_SEL)
#else
#define SPI_TRANSFER_MODE_SEL               (SPI_POLLING_SEL)
#endif

#define LPC_SSP                             LPC_SSP1
#define LPC_GPDMA_SSP_TX                    GPDMA_CONN_SSP1_Tx
#define LPC_GPDMA_SSP_RX                    GPDMA_CONN_SSP1_Rx

static uint8_t spi_tx_buf[BUFFER_SIZE];
static uint8_t spi_rx_buf[BUFFER_SIZE];
static SPI_CONFIG_FORMAT_T spi_format;
static SPI_DATA_SETUP_T spi_xf;
static volatile uint8_t  spi_xfer_completed = 0;

static uint8_t ssp_tx_buf[BUFFER_SIZE];
static uint8_t ssp_rx_buf[BUFFER_SIZE];
static SSP_ConfigFormat ssp_format;
static uint8_t ssp_dma_tx_ch, ssp_dma_rx_ch;
static volatile uint8_t ssp_dma_txf_completed = 0;
static volatile uint8_t ssp_dma_rxf_completed = 0;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Initialize buffer */
static void bufferInit(uint8_t *tx_buf, uint8_t *rx_buf)
{
	uint16_t i;
	uint8_t ch = 0;

	for (i = 0; i < BUFFER_SIZE; i++) {
		tx_buf[i] = ch++;
		rx_buf[i] = 0xAA;
	}
}

/* Verify buffer after transfer */
static uint8_t bufferVerify(uint8_t *tx_buf, uint8_t *rx_buf)
{
	uint16_t i;
	for ( i = 0; i < BUFFER_SIZE; i++ ) {
		if (tx_buf[i] != rx_buf[i]) {
			return 1;
		}
	}
	return 0;
}

/**
 * @brief	DMA interrupt handler sub-routine. Set the waiting flag when transfer is successful
 * @return	Nothing
 */
void DMA_IRQHandler(void)
{
	if (Chip_GPDMA_Interrupt(LPC_GPDMA, ssp_dma_tx_ch) == SUCCESS) {
		ssp_dma_txf_completed = 1;
	}

	if (Chip_GPDMA_Interrupt(LPC_GPDMA, ssp_dma_rx_ch) == SUCCESS) {
		ssp_dma_rxf_completed = 1;
	}
}

static void appSSPRun(void)
{
	bufferInit(ssp_tx_buf, ssp_rx_buf);
	ssp_dma_tx_ch = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, LPC_GPDMA_SSP_TX);
	ssp_dma_rx_ch = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, LPC_GPDMA_SSP_RX);
	ssp_dma_txf_completed = ssp_dma_rxf_completed = 0;
	Chip_SSP_DMA_Enable(LPC_SSP);
	/* data Tx_Buf --> SSP */
	Chip_GPDMA_Transfer(LPC_GPDMA, ssp_dma_tx_ch,
					  (uint32_t) &ssp_tx_buf[0],
					  LPC_GPDMA_SSP_TX,
					  GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA,
					  BUFFER_SIZE);
	/* data SSP --> Rx_Buf */
	Chip_GPDMA_Transfer(LPC_GPDMA, ssp_dma_rx_ch,
					  LPC_GPDMA_SSP_RX,
					  (uint32_t) &ssp_rx_buf[0],
					  GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA,
					  BUFFER_SIZE);
}

/* Select the Transfer mode : Polling or Interrupt */
static void appSPIRun(void)
{
	spi_xf.cnt = 0;
	spi_xf.length = BUFFER_SIZE;
	spi_xf.pTxData = spi_tx_buf;
	spi_xf.pRxData = spi_rx_buf;
	bufferInit(spi_tx_buf, spi_rx_buf);

#if (SPI_TRANSFER_MODE_SEL == SPI_POLLING_SEL)
	Chip_SPI_RWFrames_Blocking(LPC_SPI, &spi_xf);
#else
	spi_xfer_completed = 0;

	Chip_SPI_Int_FlushData(LPC_SPI);		/* flush dummy data from SPI FiFO */
	Chip_SPI_Int_RWFrames8Bits(LPC_SPI, &spi_xf);
	Chip_SPI_Int_Enable(LPC_SPI);			/* enable interrupt */
#endif
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/
#if (SPI_TRANSFER_MODE_SEL == SPI_INTERRUPT_SEL)
/**
 * @brief	SPI interrupt handler sub-routine
 * @return	Nothing
 */
void SPI_IRQHandler(void)
{
	Chip_SPI_Int_Disable(LPC_SPI);	/* Disable all interrupt */
	Chip_SPI_Int_RWFrames8Bits(LPC_SPI, &spi_xf);

	if (spi_xf.cnt < spi_xf.length) {
		Chip_SPI_Int_Enable(LPC_SPI);	/* enable all interrupts */
	}
	else {
		spi_xfer_completed = 1;
	}
}

#endif /*(SPI_TRANSFER_MODE_SEL == SPI_INTERRUPT_SEL)*/

/**
 * @brief	Main routine for SPI example
 * @return	Nothing
 */
int main(void)
{
	SystemCoreClockUpdate();
	Board_Init();

#if (SPI_MODE_SEL == SPI_MASTER_MODE_SEL)
	Board_SPI_Init(true);
#else
	Board_SPI_Init(false);
#endif
	Board_SSP_Init(LPC_SSP);

	/* SPI initialization */
	Chip_SPI_Init(LPC_SPI);
	spi_format.bits = SPI_BITS_8;
	spi_format.clockMode = SPI_CLOCK_MODE0;
	spi_format.dataOrder = SPI_DATA_MSB_FIRST;
	Chip_SPI_SetFormat(LPC_SPI, &spi_format);

	/* SSP initialization */
	Chip_SSP_Init(LPC_SSP);
	ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI;
	ssp_format.bits = SSP_BITS_8;
	ssp_format.clockMode = SSP_CLOCK_MODE0;
	Chip_SSP_SetFormat(LPC_SSP, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode);
	Chip_SSP_Enable(LPC_SSP);

	/* Initialize GPDMA controller */
	Chip_GPDMA_Init(LPC_GPDMA);

#if (SPI_MODE_SEL == SPI_MASTER_MODE_SEL)
	spi_xf.fnBefFrame =  Board_SPI_AssertSSEL;
	spi_xf.fnAftFrame =  Board_SPI_DeassertSSEL;
	spi_xf.fnBefTransfer = NULL;
	spi_xf.fnAftTransfer = NULL;
	Chip_SPI_SetMode(LPC_SPI, SPI_MODE_MASTER);
	Chip_SSP_SetMaster(LPC_SSP, 0);
#else
	spi_xf.fnBefFrame =  NULL;
	spi_xf.fnAftFrame =  NULL;
	spi_xf.fnBefTransfer = NULL;
	spi_xf.fnAftTransfer = NULL;
	Chip_SPI_SetMode(LPC_SPI, SPI_MODE_SLAVE);
	Chip_SSP_SetMaster(LPC_SSP, 1);
#endif

#if (SPI_TRANSFER_MODE_SEL == SPI_INTERRUPT_SEL)
	/* Setting SPI interrupt */
	NVIC_EnableIRQ(SPI_IRQn);
#endif
	NVIC_EnableIRQ(DMA_IRQn);

#if (SPI_MODE_SEL == SPI_MASTER_MODE_SEL)

	appSSPRun();
	appSPIRun();
#else
	appSPIRun();
	appSSPRun();
	while (!spi_xfer_completed) {}
#endif
	while (!ssp_dma_txf_completed || !ssp_dma_rxf_completed) {}
	Chip_SSP_DMA_Disable(LPC_SSP);

	if ((bufferVerify(spi_tx_buf, ssp_rx_buf) == 0) &&
		(bufferVerify(ssp_tx_buf, spi_rx_buf) == 0)) {
		/* Turn on the LED to show success. */
		Board_LED_Set(0, true);
	}
	else {
		/* Leave LED off on failure. */
		Board_LED_Set(0, false);
	}

	/* DeInitialize SPI peripheral */
	Chip_SPI_DeInit(LPC_SPI);

	/* DeInitialize SSP peripheral */
	Chip_SSP_DeInit(LPC_SSP);

	while (1) {}
	return 0;
}

/**
 * @}
 */
