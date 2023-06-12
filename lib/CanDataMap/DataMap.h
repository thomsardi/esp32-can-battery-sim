#ifndef CAN_DATA_MAP_H
#define CAN_DATA_MAP_H

#include <Arduino.h>

struct CANDataMap
{
    private :
    uint8_t _lowByte = 0x5E;
    uint8_t _highByte = 0x50;
    uint8_t _id = 0;
    public :
        CANDataMap(uint8_t id) {
            _lowByte = data[0][2];
            _highByte = data[0][3];
            _id = id;
            for (size_t i = 0; i < 11; i++)
            {
                frameId[i] = frameId[i] - _id;
            }
        } 
        
        /**
         * @param packVoltage packVoltage in 0.01V, for 51,60V packVoltage param should be 5160
        */
        void updatePackVoltage(uint16_t packVoltage)
        {
            int val = 25700 - packVoltage;
            _highByte = (val & 0xFF00) >> 8;
            _lowByte = val & 0xFF;

            if(_lowByte > 0x64) //device calibration, when the lowbyte higher than 100 (0x64), the highbyte decreased by 1
            {
                _highByte++;
            }

            data[0][2] = _lowByte;
            data[0][3] = _highByte;
        }

        /**
         * @param packCurrent packCurrent in 0.1V, for 51,6A packCurrent param should be 516
        */
        void updatePackCurrent(uint16_t packCurrent)
        {
            int val = 25700 - packCurrent;
            _highByte = (val & 0xFF00) >> 8;
            _lowByte = val & 0xFF;

            if(_lowByte > 0x64) //device calibration, when the lowbyte higher than 100 (0x64), the highbyte decreased by 1
            {
                _highByte++;
            }

            data[0][4] = _lowByte;
            data[0][5] = _highByte;
        }

        /**
         * @param packSoc packSoc in 0.1V, for 20,5% packSoc param should be 205
        */
        void updatePackSoc(uint16_t packSoc)
        {
            int val = 25700 - packSoc;
            _highByte = (val & 0xFF00) >> 8;
            _lowByte = val & 0xFF;

            if(_lowByte > 0x64) //device calibration, when the lowbyte higher than 100 (0x64), the highbyte decreased by 1
            {
                _highByte++;
            }

            data[0][6] = _lowByte;
            data[0][7] = _highByte;
        }

        uint32_t frameId[11] = {
            0x0764c864,
            0x0763c864,
            0x0762c864,
            0x0761c864,
            0x0760c864,
            0x075fc864,
            0x075ec864,
            0x075dc864,
            0x075cc864,
            0x075bc864,
            0x075ac864,
        };

        uint8_t data[11][8] = {
            // {0x56, 0x61, 0x5E, 0x50, 0x02, 0x64, 0x01, 0x64},
            {0x56, 0x61, 0x5E, 0x50, 0x02, 0x64, 0x01, 0x64},
            {0x31, 0x31, 0x49, 0x49, 0x49, 0x4b, 0x47, 0x45},
            {0x15, 0x56, 0x15, 0x56, 0x15, 0x56, 0x15, 0x56},
            {0x17, 0x56, 0x16, 0x56, 0x15, 0x56, 0x16, 0x56},
            {0x17, 0x56, 0x17, 0x56, 0x16, 0x56, 0x16, 0x56},
            {0x17, 0x56, 0x17, 0x56, 0x64, 0x64, 0x64, 0x5e},
            {0x15, 0x56, 0x17, 0x56, 0x49, 0x4b, 0x42, 0xfc},
            {0x64, 0x63, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64},
            {0x27, 0x5a, 0x64, 0x64, 0xe1, 0x6f, 0x61, 0x64},
            {0x0e, 0x57, 0x64, 0x64, 0xf4, 0x59, 0x64, 0x64},
            {0x52, 0x64, 0x59, 0x5f, 0x5a, 0x29, 0x64, 0x00}
        };
    
};


#endif