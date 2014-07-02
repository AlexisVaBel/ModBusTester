#ifndef MODBUSREGISTER_H
#define MODBUSREGISTER_H

#include <QObject>

class ModBusRegister : public QObject
{
    Q_OBJECT
public:
    explicit ModBusRegister(QObject *parent = 0,int iAddr=0,bool bWritable=false);

    void setVal(int iVal);
    void setAdr(int iAddr);
    void setReadState(bool bRead);
    void setWriteState(bool bWrite);

    int  getVal();


signals:

public slots:

private:
    int         m_iAdr;
    int         m_iVal;
    bool      m_bNeedRead;
    bool      m_bNeedWrite;
    bool      m_bWritable;
};

#endif // MODBUSREGISTER_H
