/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************

File: CompassMenu.cpp

Class to handle compass data and actions.

Author: Axel Pauli, February 2021

Last update: 2021-02-26

 **************************************************************************/

#include <cstring>
#include <cstdlib>
#include <cmath>
#include "esp_log.h"
#include "esp_system.h"

#include "CompassMenu.h"
#include "MenuEntry.h"

SetupMenuSelect* CompassMenu::menuPtr = nullptr;

// Initialise static members
SetupNG<float>* CompassMenu::deviations[8] = { &compass_dev_0,
    &compass_dev_45,
		&compass_dev_90,
		&compass_dev_135,
		&compass_dev_180,
		&compass_dev_225,
		&compass_dev_270,
		&compass_dev_335 };
/**
 * Creates a compass menu instance with an active compass object.
 */
CompassMenu::CompassMenu( Compass& compassIn ) :
		 compass( compassIn ),
		 filter( 0.1 )
{
}

CompassMenu::~CompassMenu()
{
}

// Compass Menu Action Routine
int CompassMenu::deviationAction( SetupMenuSelect *p )
{
  ESP_LOGI( FNAME, "Compass deviation setup for direction '%s'",
            p->getEntry() );

	if( compass.haveSensor() == false )
	{
		p->clear();
		p->ucg->setFont( ucg_font_fur14_hf );
		p->ucg->setPrintPos( 1, 60 );
		p->ucg->printf( "No magnetic Sensor, Abort" );
		delay( 2000 );
		ESP_LOGI( FNAME, "Abort calibration, no sensor signal" );
		return 0;
	}

  short direction = strtol( p->getEntry(), nullptr, 10 );
  short diridx = direction / 45;

  // Calibration menu is requested
  const unsigned short skydirs[8] =
  { 0, 45, 90, 135, 180, 225, 270, 335 };

  p->clear();
  p->ucg->setFont( ucg_font_fur14_hf );
  p->ucg->setPrintPos( 1, 60 );
  p->ucg->printf( "Turn airplain to %s\260  ", p->getEntry() );
  p->ucg->setPrintPos( 1, 90 );
  p->ucg->printf( "and push button when done" );
  delay( 500 );

  float heading = 0.0;
  short hi = 0;
  short deviation = 0;

  while( !p->_rotary->readSwitch() )
  {
    bool ok = true;
    heading = Compass::magnHeading( &ok, false );

    if( ok == false )
      {
        // in case of error deviation is set to 0
        heading = static_cast<float>( skydirs[diridx] );
      }

    hi = static_cast<short>(rintf( heading ));

    if( hi >= 360 )
      hi -= 360;

    p->ucg->setFont( ucg_font_fur20_hf );
    p->ucg->setPrintPos( 1, 180 );
    p->ucg->printf( "Heading:   %d\260    ", hi );
    p->ucg->setPrintPos( 1, 230 );

    deviation = direction - hi;

    if( deviation < -180 )
      deviation += 360;

    p->ucg->printf( "Deviation: %d\260    ", deviation );
    delay( 100 );
  }

  while( p->_rotary->readSwitch() )
    {
      // wait so long while rotary is pressed to avoid unwanted actions
      delay( 50 );
      continue;
    }

  // Save deviation value
  deviations[diridx]->set( deviation );

  // Update compass interpolation data
  Compass::setupInterpolationData();

  ESP_LOGI( FNAME, "Compass deviation action for %s is finished",
            p->getEntry() );
  return 1;
}

/** Compass Menu Action method to reset all deviations to 0. */
int CompassMenu::resetDeviationAction( SetupMenuSelect *p )
{
  if( p->getSelect() == 0 )
    {
      // Cancel is selected
      return 0;
    }
  else if( p->getSelect() == 1 )
  {
    p->clear();
    p->ucg->setFont( ucg_font_fur14_hf );
    p->ucg->setPrintPos( 1, 60 );
    p->ucg->printf( "Reset all compass" );
    p->ucg->setPrintPos( 1, 90 );
    p->ucg->printf( "deviation data" );

    // Reset calibration
    for( int i = 0; i < 8; i++ )
    {
      deviations[i]->set( 0.0 );
    }

    ESP_LOGI( FNAME, "All compass deviations values were reset" );
    delay( 1000 );
  }

  // Reset compass interpolation data
  Compass::setupInterpolationData();

  p->clear();
  p->ucg->setFont( ucg_font_fur14_hf );
  p->ucg->setPrintPos( 1, 300 );
  p->ucg->printf( "Saved        " );
  delay( 2000 );
  return 0;
}

int CompassMenu::declinationAction( SetupMenuValFloat *p )
{
	ESP_LOGI( FNAME, "declinationAction()" );

	if( p->pressed )
	{
		ESP_LOGI( FNAME, "Compass declination set to valid" );
	}

	return 0;
}

int CompassMenu::sensorCalibrationAction( SetupMenuSelect *p )
{
	ESP_LOGI( FNAME, "sensorCalibrationAction()" );

	if( p->getSelect() == 1 )
	{
		// Cancel is requested
		ESP_LOGI( FNAME, "Cancel Button pressed" );
		return 0;
	}

	ESP_LOGI( FNAME, "Start magnetic sensor calibration" );

	if( compass.haveSensor() == false )
	{
		p->clear();
		p->ucg->setFont( ucg_font_fur14_hf );
		p->ucg->setPrintPos( 1, 60 );
		p->ucg->printf( "No magnetic Sensor, Abort" );
		delay( 2000 );
		ESP_LOGI( FNAME, "Abort calibration, no sensor signal" );
		return 0;
	}

	menuPtr = p;
	p->clear();
  p->ucg->setFont( ucg_font_fur14_hf );
  p->ucg->setPrintPos( 1, 40 );
  p->ucg->printf( "Calibration is running" );
  p->ucg->setPrintPos( 1, 220 );
  p->ucg->printf( "Press button to finish it" );

	compass.calibrate( calibrationReport );
  p->ucg->setPrintPos( 1, 250 );
  p->ucg->printf( "Press button to exit" );

  delay( 2000 );

  while( p->_rotary->readSwitch() == false )
    {
      delay( 100 );
    }

  menuPtr = nullptr;
	return 0;
}

/** Method for receiving intermediate calibration results. */
bool CompassMenu::calibrationReport( float xscale, float yscale, float zscale )
{
  if( menuPtr == nullptr )
    return false;

  menuPtr->ucg->setPrintPos( 1, 100 );
  menuPtr->ucg->printf( "X-Scale=%.1f       ", xscale * 100 );
  menuPtr->ucg->setPrintPos( 1, 130 );
  menuPtr->ucg->printf( "Y-Scale=%f.1       ", yscale * 100 );
  menuPtr->ucg->setPrintPos( 1, 160 );
  menuPtr->ucg->printf( "Z-Scale=%f.1       ", zscale * 100 );

  if( MenuEntry::_rotary->readSwitch() == false )
    {
      // further reports are welcome
      return true;
    }

  // Stop further reporting.
  return false;
}
