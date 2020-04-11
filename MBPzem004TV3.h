/*
  MBPzem004TV3 - Libreria Arduino para multiples modulos Pzem004TV3.0.
  Sebastian Ferraro  Copyright (c) 2020
  sebastian.ferraro.cerrutti@gmail.com
  https://github.com/SebaFerraro/MBPzem004TV3
  Bajo Licencia GPLV3
*/

#ifndef MBPzem004TV3_h
#define MBPzem004TV3_h

#include <ModbusMaster.h>

class MBPzem004TV3
{
  private:
    ModbusMaster _node;
    double _voltage_usage; 
    double _current_usage;
    double _active_power;
    double _active_energy;
    double _frequency;
    double _power_factor; 
    double _over_power_alarm;
    double _power_alarm_threshold;
    uint8_t _modbus_rtu_address;
    uint32_t _lasttimeV;
    uint32_t _lasttimeP;
    void _readvalues(void);
    uint8_t _readparameters(void);
    static const uint8_t TRefresh = 500;
    Stream* _serial;
    
  public:
    MBPzem004TV3(void);
    void begin(uint8_t addr, Stream &serial);
    double readvoltage(void);
    double readcurrent(void);
    double readpower(void);
    double readenergy(void);
    double readfrequency(void);
    double readpowerfactor(void);
    double readpoweralarm(void);
    double readpoweralarmthreshold(void);
    uint8_t readaddress(void);
    uint8_t setaddress(uint8_t addr);
    uint8_t setpoweralarmthreshold(uint16_t powert);
    void resetenergy(void);
    
};

#endif
