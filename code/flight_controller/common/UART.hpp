#ifndef __UART_HPP
#define __UART_HPP

class UART : public Peripheral
{
public:
    virtual void initialise() = 0;
    virtual void write() = 0;

private:
    bool m_initialised;
};

#endif  // __UART_HPP
