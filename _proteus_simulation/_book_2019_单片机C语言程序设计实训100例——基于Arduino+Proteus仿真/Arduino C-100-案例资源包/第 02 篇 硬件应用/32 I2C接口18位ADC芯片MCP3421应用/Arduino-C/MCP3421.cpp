/* MCP3421  18-Bit Analog-to-Digital Converter with I2C Interface and On-Board Reference
 * Lab3 3/2012 Nawrath
 * Kunsthochschule fuer Medien Koeln
 * Academy of Media Arts Cologne
 * http://interface.khm.de
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
	SR = Sample Rate Selection 
	sr = 0  ; 00 = 240 SPS	(12 bits)
	sr = 1  ; 01 = 60 SPS	(14 bits)
	sr = 2  ; 10 = 15 SPS	(16 bits)
	sr = 3  ; 11 = 3.75 SPS (18 bits)
	PGA = PGA Gain Selector 
	0 = 1 V/V,
	1 = 2 V/V,
	2 = 4 V/V,
	3 = 8 V/V
*/
#include "MCP3421.h"
#include <Arduino.h>
#include <Wire.h>
MCP3421::MCP3421() {  }
//**********************************************
int MCP3421::init(int address, uint8_t sr, uint8_t pga) {
	_adr = address;				// set device address to 0x68 for MCP3421
	_sr=sr & 3;					// Sample Rate
	_pga=pga & 3;				// PGA ampification Factor
	Wire.beginTransmission(_adr);
	_confWrite=0;    
	_confWrite=_confWrite | ( _sr  << 2 );     
	_confWrite=_confWrite | _pga;     
	bitWrite(_confWrite,7,1);	// RDY    
	bitWrite(_confWrite,4,1);	// O/C 1    
	Wire.write(_confWrite);		// config register %1000 1000
	Serial.println(_confWrite,BIN);     
	Wire.endTransmission();
}
//**********************************************
uint32_t MCP3421::getLong() {
	if (_sr < 3) {
		Wire.requestFrom(_adr, 3);
		_b2 = Wire.read();
		_b3 = Wire.read();
		_confRead = Wire.read();
		Wire.endTransmission();
		_l1= 256 * _b2 +_b3;
	} else {
		Wire.requestFrom(_adr, 4);
		_b2 = Wire.read();
		_b3 = Wire.read();
		_b4 = Wire.read();
		_confRead = Wire.read();
		Wire.endTransmission();
		_l1 =  ((uint32_t)_b2) << 16;
		_l1 |= ((uint32_t)_b3) << 8;
		_l1 |= _b4;
	}
	//根据_sr取值0、1、2、3,分别根据11、13、15、17补齐符号位MMM...MMM
	switch (_sr) {
		case 0:if ( _l1 & ((uint32_t)1<<11)) _l1 |= 0xFFFF0000;break;
		case 1:if ( _l1 & ((uint32_t)1<<13)) _l1 |= 0xFFFF0000;break;
		case 2:if ( _l1 & ((uint32_t)1<<15)) _l1 |= 0xFFFF0000;break;
		case 3:if ( _l1 & ((uint32_t)1<<17)) _l1 |= 0xFF000000;break;
	}
	return( _l1);
}
//**********************************************
double MCP3421::getDouble() {
	getLong();
	_db1 = (signed long)_l1 *  1e-3 / (1 << _sr*2 ) ; //参照所讨论的简化版精度公式计算
	_db1 /= (1 <<_pga);				 //除增益
	return( _db1);
}
//**********************************************
int MCP3421::ready() {
	getLong();
	return(!bitRead(_confRead,7));
}