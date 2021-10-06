#ifndef UNITS_H
#define UNITS_H

#include "logdef.h"
#include "Setup.h"

class Units {
public:
	static inline float Airspeed( float as ){
		if( ias_unit.get() == SPEED_UNIT_KMH ) // km/h
			return( as );
		else if( ias_unit.get() == SPEED_UNIT_MPH ) // mph
			return( as*0.621371 );
		else if( ias_unit.get() == SPEED_UNIT_KNOTS ) // knots
			return( as*0.539957 );
		else
			ESP_LOGE(FNAME,"Wrong unit for AS");
		return 0;
	};

	static inline float kmh2knots( float kmh ){
			return( kmh / 1.852 );
	};

	static inline float kmh2ms( float kmh ){
			return( kmh * 0.277778 );
	};

	static inline float ms2kmh( float ms ){
			return( ms * 3.6 );
	};

	static inline float knots2kmh( float knots ){
				return( knots * 1.852 );
	};

	static inline float Airspeed2Kmh( float as ){
		if( ias_unit.get() == SPEED_UNIT_KMH ) // km/h
			return( as );
		else if( ias_unit.get() == SPEED_UNIT_MPH ) // mph
			return( as/0.621371 );
		else if( ias_unit.get() == SPEED_UNIT_KNOTS ) // knots
			return( as/0.539957 );
		else
			ESP_LOGE(FNAME,"Wrong unit for AS");
		return 0;
	};

	static inline float TemperatureUnit( float t ){
		if( temperature_unit.get() == T_CELCIUS ) // °C
			return( t );
		if( temperature_unit.get() == T_FAHRENHEIT ) // °C
			return( (t * 1.8) + 32 );
		if( temperature_unit.get() == T_KELVIN ) // °C
			return( t +  273.15 );
		else{
			return( t ); // default °C
		}
	}

	static inline const char * AirspeedUnit( int unit = -1 ){
		int u = unit;
		if( u == -1 )
			u=ias_unit.get();
		if( u == 0 ) // km/h
			return("kmh");
		if( u == 1 ) // mph
			return("mph");
		if( u == 2 ) // knots
			return("kt");
		else
			ESP_LOGE(FNAME,"Wrong unit for airspeed");
		return "nan";
	};

	static inline float Vario( float te ){   // standard is m/s
		if( vario_unit.get() == VARIO_UNIT_MS )
			return( te );
		else if(  vario_unit.get() == VARIO_UNIT_FPM )
			return( te*1.9685 );
		else if( vario_unit.get() == VARIO_UNIT_KNOTS )
			return( te*1.94384 );         // knots
		else
			ESP_LOGE(FNAME,"Wrong unit for Vario");
		return 0;
	};

	static inline float knots2ms( float knots ){   // if we got it in knots
			return( knots/1.94384 );
	};

	static inline float ms2knots( float knots ){   // if we got it in knots
			return( knots*1.94384 );
	};

	static inline float Vario2ms( float var ){
		if( vario_unit.get() == VARIO_UNIT_MS )
			return( var );
		else if(  vario_unit.get() == VARIO_UNIT_FPM )
			return( var/196.85 );
		else if( vario_unit.get() == VARIO_UNIT_KNOTS )
			return( var/1.94384 );         // knots
		else
			ESP_LOGE(FNAME,"Wrong unit for Vario");
		return 0;
	};

	static inline float mcval2knots( float mc ){   // returns MC, stored according to vario setting, in knots
		if( vario_unit.get() == VARIO_UNIT_MS )             // mc is in m/s
			return( mc*1.94384 );
		else if(  vario_unit.get() == VARIO_UNIT_FPM )       // mc is stored in feet per minute
			return( mc * 0.00987472 );
		else if( vario_unit.get() == VARIO_UNIT_KNOTS )        // knots we already have
			return( mc );
		else
			ESP_LOGE(FNAME,"Wrong unit for Vario");
		return 0;
	};


	static inline const char * VarioUnit(){
		if( vario_unit.get() == VARIO_UNIT_MS )
			return("m/s");
		else if( vario_unit.get() == VARIO_UNIT_FPM )
			return("cft/m");
		else if( vario_unit.get() == VARIO_UNIT_KNOTS )
			return("kt");
		else
			ESP_LOGE(FNAME,"Wrong unit for altitude");
		return "nan";
	};
	static inline const char * VarioUnitLong( int unit = -1 ){
		int u = unit;
		if( u == -1 )
			u=vario_unit.get();
		if( u == 0 )
			return("m/s");
		else if( u == 1 )
			return("x 100ft/m");
		else if( u == 2 )
			return("knots");
		else
			ESP_LOGE(FNAME,"Wrong unit for altitude");
		return "nan";
	};

	static inline float Altitude( float alt ){
		if( alt_unit.get() == 0 )  //m
			return( alt );
		else if( alt_unit.get() == 1 ) //feet
			return( alt*3.28084 );
		else if( alt_unit.get() == 2 ) //FL
			return( alt*0.0328084 );
		else
			ESP_LOGE(FNAME,"Wrong unit for altitude");
		return 0;
	};

	static inline float meters2feet( float m ){
			return( m*3.28084 );
	};

	static inline float feet2meters( float f ){
			return( f/3.28084 );
	};

	static inline const char * AltitudeUnit(){
		if( alt_unit.get() == 0 )  //m
			return( "m" );
		else if( alt_unit.get() == 1 ) //feet
			return( "ft" );
		else if( alt_unit.get() == 2 ) //FL
			return( "FL" );
		else
			ESP_LOGE(FNAME,"Wrong unit for altitude");
		return "nan";
	};

};

#endif
