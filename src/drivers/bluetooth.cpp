#include <string.h>

#include "drivers/bluetooth.h"
#include "utils/delay.h"

HC06::HC06(uint32_t usart_base):
_usart(usart_base)
{
    this->_init = false;

    memset(this->_pin, 0, sizeof(this->_pin));
    memset(this->_name, 0, sizeof(this->_name));
    memset(this->_rx_queue, 0, sizeof(this->_rx_queue));

    usart_setup(
        this->_usart, 
        HC06_DEFAULT_BAUD_RATE,
        8,
        USART_STOPBITS_1,
        USART_MODE_TX_RX,
        USART_PARITY_NONE,
        USART_FLOWCONTROL_NONE
    );
}

HC06::~HC06(void)
{

}

void HC06::start(void)
{
    this->write_blocking("AT", strlen("AT"));
    this->_init = true;
}

void HC06::reset(void)
{
    if (this->_init)
    {
        this->write_blocking("AT+RESET", strlen("AT+RESET"));
        this->_init = false;
    }
}

// There are two ways to do this
// 1. The "AT" command doesn't receive a response while connected
// 2. Use the LED on the module
// 3. We can also do nothing since the device itself is non-blocking
bool HC06::check_connect(void)
{
    this->write_blocking("AT", strlen("AT"));
    delay_ms(250);
    char read_check[3] = {'0'};

    uint16_t len = this->read_blocking(read_check);
    if (strncmp("OK", read_check, len) == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void HC06::write_blocking(const char * msg, uint16_t len)
{
    usart_send_buf(this->_usart, msg, len);
    delay_ms(HC06_WRITE_WAIT);
}

uint16_t HC06::read_blocking(char * msg)
{
    uint16_t len = 0;
    char new_byte = 'a';
    while (new_byte != '\0')
    {
        new_byte = (char) usart_recv_blocking(this->_usart);
        this->_rx_queue[len] = new_byte;
        len++;
    }

    memcpy(msg, this->_rx_queue, len);
    return len;

}

void HC06::set_pin(const char * pin)
{
    char cmd[HC06_MAX_CMD_LEN + HC06_PIN_LEN] = {'0'};
    strcpy(cmd, "AT+PIN");
    strcpy(this->_pin, pin);
    strcpy(cmd, pin);
    this->write_blocking(cmd, strlen(cmd));
}

void HC06::set_name(const char * name)
{
    char cmd[HC06_MAX_CMD_LEN + HC06_NAME_LEN] = {'0'};
    strcpy(cmd, "AT+NAME");
    strcpy(this->_name, name);
    strcpy(cmd, name);
    this->write_blocking(cmd, strlen(cmd));
}

void HC06::get_pin(char * pin)
{
    strcpy(pin, this->_pin);
}

void HC06::get_name(char * name)
{
    strcpy(name, this->_name);
}
