#include <SPI.h>
#include "Arduino.h"
#include "NRF24L01.h"

// Define the chip select and chip enable pins
#define NRF24_CE_PIN    17  // Change to your CE pin
#define NRF24_CSN_PIN   5  // Change to your CSN pin

// Function to select the NRF24L01 device
void CS_Select() {
    digitalWrite(NRF24_CSN_PIN, LOW);  // Pull CSN LOW
}

// Function to unselect the NRF24L01 device
void CS_UnSelect() {
    digitalWrite(NRF24_CSN_PIN, HIGH); // Pull CSN HIGH
}

// Function to enable the CE pin
void CE_Enable() {
    digitalWrite(NRF24_CE_PIN, HIGH);
}

// Function to disable the CE pin
void CE_Disable() {
    digitalWrite(NRF24_CE_PIN, LOW);
}

// Write a single byte to a particular register
void nrf24_WriteReg(uint8_t Reg, uint8_t Data) {
    uint8_t buf[2];
    buf[0] = Reg | (1 << 5);
    buf[1] = Data;

    CS_Select(); // Select the device
    SPI.transfer(buf, 2); // Send the buffer
    CS_UnSelect(); // Release the device
}

// Write multiple bytes starting from a particular register
void nrf24_WriteRegMulti(uint8_t Reg, uint8_t *data, int size) {
    uint8_t buf[1];
    buf[0] = Reg | (1 << 5);

    CS_Select(); // Select the device
    SPI.transfer(buf, 1); // Send the register address
    SPI.transfer(data, size); // Send the data
    CS_UnSelect(); // Release the device
}

// Read a single byte from a register
uint8_t nrf24_ReadReg(uint8_t Reg) {
    uint8_t data = 0;

    CS_Select(); // Select the device
    SPI.transfer(&Reg, 1); // Send the register address
    SPI.transfer(&data, 1); // Read the data
    CS_UnSelect(); // Release the device

    return data;
}

// Read multiple bytes from a register
void nrf24_ReadReg_Multi(uint8_t Reg, uint8_t *data, int size) {
    CS_Select(); // Select the device
    SPI.transfer(&Reg, 1); // Send the register address
    SPI.transfer(data, size); // Read the data
    CS_UnSelect(); // Release the device
}

// Send a command to the NRF
void nrfsendCmd(uint8_t cmd) {
    CS_Select(); // Select the device
    SPI.transfer(&cmd, 1); // Send the command
    CS_UnSelect(); // Release the device
}

// Reset the NRF24L01 registers
void nrf24_reset(uint8_t REG) {
    if (REG == STATUS) {
        nrf24_WriteReg(STATUS, 0x00);
    } else if (REG == FIFO_STATUS) {
        nrf24_WriteReg(FIFO_STATUS, 0x11);
    } else {
        nrf24_WriteReg(CONFIG, 0x08);
        nrf24_WriteReg(EN_AA, 0x3F);
        nrf24_WriteReg(EN_RXADDR, 0x03);
        nrf24_WriteReg(SETUP_AW, 0x03);
        nrf24_WriteReg(SETUP_RETR, 0x03);
        nrf24_WriteReg(RF_CH, 0x02);
        nrf24_WriteReg(RF_SETUP, 0x0E);
        nrf24_WriteReg(STATUS, 0x00);
        nrf24_WriteReg(OBSERVE_TX, 0x00);
        nrf24_WriteReg(CD, 0x00);
        
        uint8_t rx_addr_p0_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
        nrf24_WriteRegMulti(RX_ADDR_P0, rx_addr_p0_def, 5);
        uint8_t rx_addr_p1_def[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
        nrf24_WriteRegMulti(RX_ADDR_P1, rx_addr_p1_def, 5);
        
        nrf24_WriteReg(RX_ADDR_P2, 0xC3);
        nrf24_WriteReg(RX_ADDR_P3, 0xC4);
        nrf24_WriteReg(RX_ADDR_P4, 0xC5);
        nrf24_WriteReg(RX_ADDR_P5, 0xC6);
        
        uint8_t tx_addr_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
        nrf24_WriteRegMulti(TX_ADDR, tx_addr_def, 5);
        nrf24_WriteReg(RX_PW_P0, 0);
        nrf24_WriteReg(RX_PW_P1, 0);
        nrf24_WriteReg(RX_PW_P2, 0);
        nrf24_WriteReg(RX_PW_P3, 0);
        nrf24_WriteReg(RX_PW_P4, 0);
        nrf24_WriteReg(RX_PW_P5, 0);
        nrf24_WriteReg(FIFO_STATUS, 0x11);
        nrf24_WriteReg(DYNPD, 0);
        nrf24_WriteReg(FEATURE, 0);
    }
}

// Initialize the NRF24L01
void NRF24_Init(void) {
    CE_Disable(); // Disable the chip before configuring
    nrf24_reset(0); // Reset everything

    nrf24_WriteReg(CONFIG, 0);  // Will be configured later
    nrf24_WriteReg(EN_AA, 0);  // No Auto ACK
    nrf24_WriteReg(EN_RXADDR, 0);  // Not enabling any data pipe right now
    nrf24_WriteReg(SETUP_AW, 0x03);  // 5 Bytes for the TX/RX address
    nrf24_WriteReg(SETUP_RETR, 0);   // No retransmission
    nrf24_WriteReg(RF_CH, 0);  // Will be set during Tx or Rx
    nrf24_WriteReg(RF_SETUP, 0x0E);   // Power = 0db, data rate = 2Mbps

    CE_Enable(); // Enable the chip after configuring
}

// Set up the Tx mode
void NRF24_TxMode(uint8_t *Address, uint8_t channel) {
    CE_Disable(); // Disable the chip before configuring
    nrf24_WriteReg(RF_CH, channel);  // Select the channel
    nrf24_WriteRegMulti(TX_ADDR, Address, 5);  // Write the TX address

    // Power up the device
    uint8_t config = nrf24_ReadReg(CONFIG);
    config = config & (0xF2);    // Write 0 in the PRIM_RX, and 1 in the PWR_UP, and mask other bits
    nrf24_WriteReg(CONFIG, config);

    CE_Enable(); // Enable the chip after configuring
}

// Transmit the data
uint8_t NRF24_Transmit(uint8_t *data) {
    uint8_t cmdtosend = 0;

    CS_Select(); // Select the device

    // Payload command
    cmdtosend = W_TX_PAYLOAD;
    SPI.transfer(&cmdtosend, 1); // Send the payload command

    // Send the payload
    SPI.transfer(data, 32); // Send the data

    CS_UnSelect(); // Unselect the device

    delay(1); // Delay for processing

    uint8_t fifostatus = nrf24_ReadReg(FIFO_STATUS);

    // Check the fourth bit of FIFO_STATUS to know if the TX fifo is empty
    if ((fifostatus & (1 << 4)) && !(fifostatus & (1 << 3))) {
        cmdtosend = FLUSH_TX;
        nrfsendCmd(cmdtosend);

        // Reset FIFO_STATUS
        nrf24_reset(FIFO_STATUS);
        return 1; // Transmission failed
    }

    return 0; // Transmission successful
}

// Set up the Rx mode
void NRF24_RxMode(uint8_t *Address, uint8_t channel) {
    CE_Disable(); // Disable the chip before configuring
    nrf24_reset(STATUS); // Reset the status register

    nrf24_WriteReg(RF_CH, channel);  // Select the channel

    // Select data pipe 2
    uint8_t en_rxaddr = nrf24_ReadReg(EN_RXADDR);
    en_rxaddr |= (1 << 2); // Enable data pipe 2
    nrf24_WriteReg(EN_RXADDR, en_rxaddr);

    // Write the Pipe1 address
    nrf24_WriteRegMulti(RX_ADDR_P1, Address, 5);  // Write the Pipe1 address
    nrf24_WriteReg(RX_ADDR_P2, 0xEE);  // Write the Pipe2 LSB address

    nrf24_WriteReg(RX_PW_P2, 32);   // 32-bit payload size for pipe 2

    // Power up the device in Rx mode
    uint8_t config = nrf24_ReadReg(CONFIG);
    config |= (1 << 1) | (1 << 0); // Set PWR_UP and PRIM_RX bits
    nrf24_WriteReg(CONFIG, config);

    CE_Enable(); // Enable the chip after configuring
}

// Check if data is available for reading
uint8_t isDataAvailable(int pipenum) {
    uint8_t status = nrf24_ReadReg(STATUS);

    if ((status & (1 << 6)) && (status & (pipenum << 1))) {
        nrf24_WriteReg(STATUS, (1 << 6)); // Clear the interrupt flag
        return 1; // Data is available
    }

    return 0; // No data available
}

// Receive the data
void NRF24_Receive(uint8_t *data) {
    uint8_t cmdtosend = 0;

    CS_Select(); // Select the device

    // Payload command
    cmdtosend = R_RX_PAYLOAD;
    SPI.transfer(&cmdtosend, 1); // Send the payload command

    // Receive the payload
    SPI.transfer(data, 32); // Read the data

    CS_UnSelect(); // Unselect the device

    delay(1); // Delay for processing

    cmdtosend = FLUSH_RX; // Flush the RX FIFO
    nrfsendCmd(cmdtosend);
}

// Read all the register data
void NRF24_ReadAll(uint8_t *data) {
    for (int i = 0; i < 10; i++) {
        *(data + i) = nrf24_ReadReg(i);
    }

    nrf24_ReadReg_Multi(RX_ADDR_P0, (data + 10), 5);
    nrf24_ReadReg_Multi(RX_ADDR_P1, (data + 15), 5);

    *(data + 20) = nrf24_ReadReg(RX_ADDR_P2);
    *(data + 21) = nrf24_ReadReg(RX_ADDR_P3);
    *(data + 22) = nrf24_ReadReg(RX_ADDR_P4);
    *(data + 23) = nrf24_ReadReg(RX_ADDR_P5);

    nrf24_ReadReg_Multi(RX_ADDR_P0, (data + 24), 5);

    for (int i = 29; i < 38; i++) {
        *(data + i) = nrf24_ReadReg(i - 12);
    }
}
