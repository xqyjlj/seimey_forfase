#ifndef GDUT_FSAE_CRC_H
#define GDUT_FSAE_CRC_H

#include <QObject>

class gdut_fsae_crc : public QObject
{
    Q_OBJECT
public:
    explicit gdut_fsae_crc(QObject *parent = nullptr);
public:
    uint16_t crc16_modbus(uint8_t *msg, uint64_t len);
    uint16_t crc16_modbus_table(uint8_t *msg, uint64_t len);
    uint16_t crc16_ibm_table(uint8_t *msg, uint64_t len);
signals:

public slots:
};

#endif // GDUT_FSAE_CRC_H
