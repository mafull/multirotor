#ifndef __PID_HPP
#define __PID_HPP

typedef double PID_Type_t;

class PID
{
public:
    PID();
    ~PID();
    
    void setSetpoint(PID_Type_t setpoint);
    PID_Type_t update(PID_Type_t actual);
    PID_Type_t getOutput() const { return _output; }
    void reset();

protected:

private:
    PID_Type_t _actual;
    PID_Type_t _setpoint;
    
    PID_Type_t _output;

    PID_Type_t _kP;
    PID_Type_t _kI;
    PID_Type_t _kD;

    PID_Type_t _iLimit;
};

#endif  // __PID_HPP
