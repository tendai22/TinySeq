/*
 * File:   main.c
 * Author: Norihiro Kumagai
 *
 * Created on 2022/07/31, 22:05
 */

// PIC32MX220F032B Configuration Bit Settings

// 'C' source line config statements

// DEVCFG3
#pragma config USERID = 0xFFFF          // Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = OFF             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = ON            // USB USID Selection (Controlled by the USB Module)
#pragma config FVBUSONIO = ON           // USB VBUS ON Selection (Controlled by USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2        // PLL Input Divider (12x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_12        // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_2       // System PLL Output Clock Divider (PLL Divide by 256)

// DEVCFG1
#pragma config FNOSC = FRCPLL           // Oscillator Selection Bits (Fast RC Osc w/Div-by-N (FRCDIV))
#pragma config FSOSCEN = OFF             // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_2           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window Size is 25%)

// DEVCFG0
#pragma config JTAGEN = ON              // JTAG Enable (JTAG Port Enabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <sys/attribs.h>
//#include <stdio.h>
#include <stdarg.h>
#include "zforth.h"
#include "xprintf.h"
#include "tinyseq.h"

void delay_us(volatile unsigned int usec)        //1?sec??
{
    volatile  int count;
    count = usec;
    do {
        asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP");
        asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP");
        asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP");
        asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP");
        asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP");
        asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP");
        asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP"); asm volatile ("NOP");
        asm volatile ("NOP"); //asm volatile ("NOP"); //asm volatile ("NOP"); asm volatile ("NOP");
        //asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");asm("NOP");
        //asm("NOP"); asm("NOP"); //asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
        count--;
    } while (count != 0);


}

void delay_ms(volatile unsigned int msec)        //1msec??
{
    volatile unsigned int i;
    for(i = 0; i < msec; i++) {
        delay_us(1000); 
    }
}

//
// GPIO/LED
//
void init_LED(void)
{
	TRISBbits.TRISB5 = 0;		// ??
	PORTBbits.RB5 = 0;		// low(LED off)
    
}

void test_LED(void)
{
    init_LED();
    
	while(1){
		PORTBbits.RB5 ^= 1;
        delay_ms(500);
    }
}

#define led_ON() (PORTBbits.RB5 = 1)
#define led_OFF() (PORTBbits.RB5 = 0)
#define toggle_led() (PORTBbits.RB5 ^= 1)

//
// UART1
//
void init_uart(void)
{
    
    ANSELB = 0x00;        // Analog function disabled

    // PIC32MX gpio pin assign configuration
    U1RXR = 0;   // UART1_RX -> RPA2
    RPA0R = 1;   // UART1_TX -> RPA0
    
    U1STAbits.UTXEN = 1;  // TX enable
    U1STAbits.URXEN = 1;  // RX enable
    U1BRG = 129;          // 9600bps [20M/(16*9600)-1]

    U1MODEbits.ON = 1;   // UART1 start
}

//
// _mon_getc/_mon_putc? bind to stdio.h
//
int _mon_getc(void)
{
   
    while (U1STAbits.URXDA == 0) {
        // not ready
        if (get_statusflag()) {
            do_ladder();
            clear_statusflag();
        }
        delay_us(10);
    }
    // data ready, return it
    return (char)U1RXREG;
}

void _mon_putc(int c)
{
    while(U1STAbits.UTXBF)  // buffer full?
        ;
    __builtin_disable_interrupts();
    U1TXREG = c;
    __builtin_enable_interrupts();
}

void test_UART(void)
{
    int c;
    init_uart();
	while(1){
        while ((c = _mon_getc()) == -1)
            ;
        _mon_putc(c);
	}
}

int zf_getline(char *buf, int siz)
{
  zf_cell cell;
  zf_uservar_get(ZF_USERVAR_NOECHO, &cell);
  int noecho = cell;
  xgets(buf, siz, noecho);
  return strlen(buf);
}

//
// I2C
//
#define SYSCLK	(40000000)
#define PBCLK  (SYSCLK/2)
//#pragma config FPBDIV = DIV_1				//Sets PBCLK to SYSCLK

#define Fsck	100000
#define BRG_VAL 	((PBCLK/2/Fsck)-2)

#define MCP_ADDR 0x40
#define MCP_CMD_RD (MCP_ADDR|0x1)
#define MCP_CMD_WR (MCP_ADDR|0x0)

void init_I2C(void)
{
    I2C1CON = 0;
        // I2C_ON: bit15
        // I2C_SLW_DIS: bit9
        // I2C_NACK: bit5
    I2C1CONbits.DISSLW = 1;
    I2C1CONbits.ACKDT = 1;
    I2C1BRG = BRG_VAL;
    I2C1CONbits.ON = 1;
//    printf("BRG_VAL=%d\r\n", BRG_VAL);
}

//
// I/O Expander MCP23017 I2C driver
//

void mcp_init(void);
unsigned char mcp_read(unsigned char, unsigned char);
void mcp_write(unsigned char, unsigned char, unsigned char);
void i2c_write(unsigned char);
void i2c_idle(void);

static char devAdd = MCP_ADDR;

void mcp_init (void)
{
    mcp_write(devAdd, 0x00, 0x00);   // IODIRA
    mcp_write(devAdd, 0x01, 0xFF);   // IODIRB
    mcp_write(devAdd, 0x02, 0x00);   // IPOLA
    mcp_write(devAdd, 0x03, 0x00);   // IPOLB
    mcp_write(devAdd, 0x0D, 0xFF);   // GPPUB
    mcp_write(devAdd, 0x0A, 0x00);   // IOCON/BANK0
}

void i2c_idle(void)
{
    while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN)
        ;
}

void i2c_write(unsigned char data)
{
    I2C1TRN = data;
    while(I2C1STATbits.TBF);
    while(I2C1STATbits.TRSTAT);   // wait for TX complete and receive Ack/Nack
    i2c_idle();				      //
}

unsigned char mcp_read(unsigned char addr, unsigned char reg)
{
    unsigned char res;
    i2c_idle();                          // ??????
    I2C1CONbits.SEN = 1;               // ???????????
    while(I2C1CONbits.SEN)
        ;                   // wait for S complete
    i2c_write(addr);        // I2C device address for MCP23017
    i2c_write(reg);         // register address for MCP23017
    // I2C read
    I2C1CONbits.ACKDT = 1;  // send NAK for the last data
    I2C1CONbits.SEN = 1;    // restart
    while(I2C1CONbits.SEN)
        ;                   // wait for RS complete
    i2c_write(addr | 0x01);  // I2C device address with R bit
    I2C1CONbits.RCEN = 1;   // data receive start
    while(!I2C1STATbits.RBF)
        ;                   // wait for data receiving complete
    I2C1CONbits.ACKEN = 1;  // send ACK start
    i2c_idle();             // wait for its completion
    res = I2C1RCV;       // get received data
    I2C1CONbits.PEN = 1;    // start closing
    while(I2C1CONbits.PEN)
        ;                   // wait for its completion
    return res;
}

void mcp_write(unsigned char addr, unsigned char reg, unsigned char data)
{
    i2c_idle();
    I2C1CONbits.SEN = 1;
    while(I2C1CONbits.SEN)
        ;
    i2c_write(addr);        // I2C device addr
    i2c_write(reg);         // MCP23017 register addr
    i2c_write(data);        // byte to be written
    I2C1CONbits.PEN = 1;    // closing
    while(I2C1CONbits.PEN)
        ; // wait for its completion
}

unsigned char ledData[6] = {0x08,0x04,0x02,0x01,0x02,0x04};

void test_I2C(void)
{
    init_I2C();
    // mcp_init
    mcp_init();
    char i = 0;
    unsigned char recDATA, prevB;
    prevB = 0;
    xprintf("START\r\n");
    while(1){
        recDATA = mcp_read(devAdd, 0x13);      // MCP23017portB_Read
        if (recDATA != prevB) {
            xprintf("B:%02X\r\n", recDATA);                      // PORTA???
            prevB = recDATA;
        }
        mcp_write(devAdd, 0x12, ledData[i]);   // MCP23017portA_Write
        if(i == 5){
            i = 0;
        }else{
            i++;
        }
        delay_ms(100);
    }
}

//
// bit array to/from gpio, machine dependent, defined in each
// platform.
//

//
// put_outbits: gpio output interface for tinyseq
//
void put_outbits(const uint8_t *bits)
{
    // Y000-007 bit16-23 -> portA0-7
    mcp_write(devAdd, 0x12, bits[2]);   // MCP23017portA_Write
}

//
// get_inbits: gpio input interface for tinyseq
//
void get_inbits(uint8_t *bits)
{
    // portB0-7 bit0-7 --> X000-007
    bits[0] = mcp_read(devAdd, 0x13);      // MCP23017portB_Read
}

//
// Use timer1
//
static uint32_t usec_counter = 0;

uint32_t get_seq_clock(void)
{
    return usec_counter;
}

void init_timer(void)
{
    //
    // use Timer1
    //
    T1CON = 0x00000000;     //Clear
    T1CONbits.TON = 0;      //<15>Timer1_OFF
    T1CONbits.TSIDL = 1;    //<13>Stop In Idle Mode:SleepStop
    T1CONbits.TGATE = 0;    //<7>Gated Time Accumulation is disabled
    T1CONbits.TCKPS = 0;    //Prescale 1:1
    T1CONbits.TCS = 0;      //ClockSource:internal clock source
    IEC0bits.T1IE = 0;      //Interrupt:disable
    IPC1bits.T1IP = 0;      //InterruptLevel:0
    //== Interrupt ENABLE ===========================================
    //INTCONbits.MVEC   = 1;      //Multi_Vector
    //asm volatile("ei");         //Enable_Interrup
    //== preprocessing ==============================================
    //== while ======================================================
    //
    // start timer with 100us counter
    //

    TMR1 = 0;   //TMR1=0
    PR1 = (uint16_t)2000;   // 100us, possibly

    INTCONbits.MVEC = 1;

    IPC1bits.T1IP = 1;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    __builtin_enable_interrupts();
//    IFS0bits.T1IF = 0;
    T1CONbits.TON = 1;    //Timer1_start
}

//#pragma vector do_intr 12
//#pragma interrupt do_intr IPL1AUTO

void  __ISR(_TIMER_1_VECTOR, IPL1AUTO)do_intr(void)
{
    static uint32_t start = 0, now = 0;
    int flag = 0;
    // polling TIMER1
    if (IFS0bits.T1IF) {    // maybe, 100us
        IFS0bits.T1IF = 0;
        usec_counter++;
        now++;
        //set_statusflag(1);
        flag = 1;
    }
    flag = 0;
    if (now >= 10000) {   // maybe, 100ms
        now = 0;
        //xputc('x');
        flag = 1;
    }
}


char *argv[] = { "zforth", NULL };
//extern int zmain(int ac, char **av);

void main(void)
{
	DDPCONbits.JTAGEN = 0;	// disable JTAG port
    
//    test_LED();
//    test_UART();
//    init_LED();
    init_uart();
    xdev_out(_mon_putc);
    xdev_in(_mon_getc);
    int c;
    init_I2C();
    mcp_init();

    delay_us(10);
    init_timer();
	while(0){
        while ((c = _mon_getc()) == -1)
            ;
        _mon_putc(c);
	}

    zf_main (0, NULL);
    return;
}
