#include "modbusregister.h"

ModBusRegister::ModBusRegister(QObject *parent, int iAddr, bool bWritable) :
    QObject(parent){
    m_iAdr=iAddr;
    m_bWritable   =bWritable;
    m_bNeedRead =true;
    m_bNeedWrite=false;
}

void ModBusRegister::setVal(int iVal){
    m_iVal=iVal;
}

void ModBusRegister::setAdr(int iAddr){
    m_iAdr=iAddr;
}

void ModBusRegister::setReadState(bool bRead){
    m_bNeedRead=bRead;
}

void ModBusRegister::setWriteState(bool bWrite){
    m_bNeedWrite=bWrite;
}

int ModBusRegister::getVal(){
    return m_iVal;
}
