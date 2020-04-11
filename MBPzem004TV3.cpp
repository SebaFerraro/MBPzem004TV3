/*
  MBPzem004TV3 - Libreria Arduino para multiples modulos Pzem004TV3.0.
  Sebastian Ferraro  Copyright (c) 2020
  sebastian.ferraro.cerrutti@gmail.com
  https://github.com/SebaFerraro/MBPzem004TV3
  Bajo Licencia GPLV3
*/

#include <ModbusMaster.h>
#include "MBPzem004TV3.h"

MBPzem004TV3::MBPzem004TV3(void)
{
  _voltage_usage = 0; 
  _current_usage = 0;
  _active_power = 0;
  _active_energy = 0;
  _frequency = 0;
  _power_factor = 0; 
  _over_power_alarm = 0;
  _power_alarm_threshold = 0;
  _lasttimeV = 0;
  _lasttimeP = 0;
}

void MBPzem004TV3::begin(uint8_t addr, Stream &serial)
{
  _modbus_rtu_address = addr;
  _serial=&serial; 
  _node.begin(_modbus_rtu_address,serial);
}

double MBPzem004TV3::readvoltage(void)
{
    uint32_t nowtime = millis();
    if (nowtime - _lasttimeV > TRefresh) {
        _readvalues();
    }
    return _voltage_usage;
}

double MBPzem004TV3::readcurrent(void)
{
    uint32_t nowtime = millis();
    if (nowtime - _lasttimeV > TRefresh) {
        _readvalues();
    }
    return _current_usage;
}

double MBPzem004TV3::readpower(void)
    {
    uint32_t nowtime = millis();
    if (nowtime - _lasttimeV > TRefresh) {
        _readvalues();
    }
    return _active_power;
}

double MBPzem004TV3::readenergy(void)
    {
    uint32_t nowtime = millis();
    if (nowtime - _lasttimeV > TRefresh) {
        _readvalues();
    }
    return _active_energy;
}

double MBPzem004TV3::readfrequency(void)
{
    uint32_t nowtime = millis();
    if (nowtime - _lasttimeV > TRefresh) {
        _readvalues();
    }
    return _frequency;
}

double MBPzem004TV3::readpowerfactor(void)
{
    uint32_t nowtime = millis();
    if (nowtime - _lasttimeV > TRefresh) {
        _readvalues();
    }
    return _power_factor;
}

double MBPzem004TV3::readpoweralarm(void)
{
    uint32_t nowtime = millis();
    if (nowtime - _lasttimeV > TRefresh) {
        _readvalues();
    }
    return _over_power_alarm;
}

double MBPzem004TV3::readpoweralarmthreshold(void)
{
    uint32_t nowtime = millis();
    if (nowtime - _lasttimeP > TRefresh) {
        _readparameters();
    }
    return (_power_alarm_threshold / 10.0f);
}

uint8_t MBPzem004TV3::readaddress(void)
{
    uint32_t nowtime = millis();
    if (nowtime - _lasttimeP > TRefresh) {
        _readparameters();
    }
    return _modbus_rtu_address;
}

uint8_t MBPzem004TV3::setaddress(uint8_t addr)
{
    uint8_t res;
    uint16_t addr16 = 0x00FF && addr; 
    ESP.wdtDisable();
    res = _node.writeSingleRegister(0x0002, addr16);
    ESP.wdtEnable(1);
    if (res == _node.ku8MBSuccess){
        _modbus_rtu_address=addr;
        Serial.println("SetAddress :"); Serial.println(_modbus_rtu_address);
    }else{
        Serial.print("Failed modbus setaddress() :");  Serial.println(res);
    }
  return res;
}

uint8_t MBPzem004TV3::setpoweralarmthreshold(uint16_t powert)
{
    uint8_t res;
    ESP.wdtDisable();
    res = _node.writeSingleRegister(0x0001, powert);
    ESP.wdtEnable(1);
    if (res == _node.ku8MBSuccess)   {
        _power_alarm_threshold=powert;
        Serial.println("SetPowerAlarmThreshold :"); Serial.println(_power_alarm_threshold);
    } else {
        Serial.print("Failed modbus setpoweralarmthreshold() :");  Serial.println(res);
    }
  return res;
}

void MBPzem004TV3::resetenergy(void)
{
  //_serial = &serial;
  uint16_t u16CRC = 0xFFFF;
  static uint8_t resetCommand = 0x42;
  u16CRC = crc16_update(u16CRC, _modbus_rtu_address);
  u16CRC = crc16_update(u16CRC, resetCommand);
  Serial.println("Resetting Energy");
  _serial->write(_modbus_rtu_address);
  _serial->write(resetCommand);
  _serial->write(lowByte(u16CRC));
  _serial->write(highByte(u16CRC));
}

void MBPzem004TV3::_readvalues(void)
{
  uint8_t res;
  ESP.wdtDisable();
  res = _node.readInputRegisters(0x0000, 10);
  ESP.wdtEnable(1);
  if (res == _node.ku8MBSuccess)
  {
    _voltage_usage = (_node.getResponseBuffer(0x00) / 10.0f);
    _current_usage = (_node.getResponseBuffer(0x01) / 1000.000f);
    _active_power = (_node.getResponseBuffer(0x03) / 10.0f);
    _active_energy = (_node.getResponseBuffer(0x05) / 1000.0f);
    _frequency = (_node.getResponseBuffer(0x07) / 10.0f);
    _power_factor = (_node.getResponseBuffer(0x08) / 100.0f);
    _over_power_alarm = (_node.getResponseBuffer(0x09));
    _lasttimeV = millis();
  }else{
    Serial.print("Failed modbus _readvalues() :");  Serial.println(res);
  }
  
}

uint8_t MBPzem004TV3::_readparameters(void)
{
  uint8_t res;
  ESP.wdtDisable();
  res = _node.readHoldingRegisters(0x0001, 2);
  ESP.wdtEnable(1);
  if (res == _node.ku8MBSuccess) {
    _power_alarm_threshold= (_node.getResponseBuffer(0x00));
    _modbus_rtu_address   = (_node.getResponseBuffer(0x01));
  }else{
    Serial.print("Failed modbus _readparameters() :");  Serial.println(res);
  }
}

