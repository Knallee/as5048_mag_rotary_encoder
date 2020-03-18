
#include "as5048a.h"


void normal_op() {
	uint16_t angle_data = as5048_read_angle();
	uint16_t agc_data = as5048_read_agc();
	uint16_t deg;
	uint8_t agc;

	if (( agc_data & ((1<< CORDIC_OF_BIT)|(1<< COMP_HIGH_BIT)|(1<< COMP_LOW_BIT)) ) == 0) {			/**< Check diagnostics bits for magnetic compensation and CORDIC overflow which tells if data is valid. */
		deg = angle_decode(angle_data);
		agc = (uint8_t) agc_data;
		// TODO: UART output deg value
		return;
	}
	// TODO: UART output COF, COMP_HIGH, COMP_LOW bits
	return;
}

