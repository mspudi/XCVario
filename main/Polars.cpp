/*
 * Polars.cpp
 *
 *  Created on: Mar 1, 2019
 *      Author: iltis
 *
 *      Class to deliver a library of default polars
 */

#include "Polars.h"

// Format per glider:  { GliderType, Wingload (kg/m2), speed1 (km/h), sink1 (m/s), speed2, sink2, speed3, sink3 },

static const t_polar polars_default_arr[] = {
	{"User Polar",34.40,80,-0.66,125,-0.97,175,-2.24},
	{"Antares 20E", 42.86,100,-0.53,140,-0.76,200,-1.79},
	{"ASK 21",31.30,80,-0.76,125,-1.21,175,-2.75},
	{"ASK 23",26.30,80,-0.69,125,-1.32,175,-2.93},
	{"ASK 13",21.71,70,-0.80,100,-1.20,150,-2.80},
	{"ASH 25e",43.00,80,-0.62,125,-0.72,175,-1.49},
	{"G-102 CS",30.00,80,-0.61,125,-1.07,175,-2.45},
	{"G-102 CS Top",34.75,80,-0.70,125,-1.18,175,-2.55},
	{"G-102 Club",29.00,80,-0.70,125,-1.18,175,-2.55},
	{"G-102 3B",27.60,80,-0.68,125,-1.34,175,-2.84},
	{"G-102 Twin",33.40,80,-0.78,125,-1.07,175,-2.17},
	{"G-103 Twin",27.60,80,-0.75,120,-1.0,200,-3.4},
	{"ASW 17",32.00,80,-0.55,125,-0.82,175,-1.78},
	{"ASW 17 S/21",32.10,80,-0.52,125,-0.78,175,-1.83},
	{"ASW 19",31.50,80,-0.63,125,-1.09,175,-2.44},
	{"ASW 20",33.60,80,-0.62,125,-0.92,175,-1.83},
	{"ASW 20A",35.90,80,-0.69,125,-1.05,175,-2.25},
	{"ASW 20C",33.25,80,-0.61,125,-0.94,175,-1.88},
	{"ASW 20L",32.30,80,-0.57,125,-0.93,175,-2.01},
	{"ASW 22/24",32.80,80,-0.43,125,-0.85,175,-1.77},
	{"ASW 22M",40.20,80,-0.51,125,-0.75,175,-1.60},
	{"ASW 24",35.0,108.82,-0.728,142.25,-1.213,167.4,-1.766},
	{"ASW 24WL",35.7,108.80,-0.635,156.40,-1.182,211,-2.540},
	{"ASW 28",31.42,90,-0.57,130,-1.05,170,-2.15},
	{"Calif A21S",39.20,80,-0.69,125,-0.93,175,-1.82},
	{"Cirrus",29.00,80,-0.63,125,-1.23,175,-2.87},
	{"DG 100",30.00,80,-0.62,125,-1.16,175,-2.68},
	{"DG 100G",30.48,80,-0.64,125,-1.13,175,-2.50},
	{"DG 200",34.00,80,-0.65,125,-0.97,175,-2.05},
	{"DG 300",33.20,80,-0.60,125,-1.02,175,-2.48},
	{"DG 400/17",38.40,80,-0.55,125,-1.01,175,-2.12},
	{"DG 800/15",43.82,133.90,-0.879,178.87,-1.528,223.59,-2.527},
	{"DG 800/18WL",39.96,106.00,-0.620,171.75,-1.466,214.83,-2.346},
	{"DG 1000S",28.00,80,-0.51,125,-0.93,175,-2.80},
	{"Discus A",29.67,80,-0.56,125,-1.00,175,-2.55},
	{"Discus 2B",51.7,100,-0.75,125,-0.80,175,-1.50},
	{"DUO Discus",30.5,80,-0.52,130,-1.00,177,-2.50},
	{"Elfe S4D",27.00,80,-0.69,125,-1.23,175,-2.76},
	{"Genesis II",33.54,94.00,-0.608,141.05,-1.178,172.40,-1.960},
	{"H-304/17",35.20,80,-0.53,125,-0.93,175,-1.93},
	{"H-304",35.80,80,-0.64,125,-0.96,175,-2.04},
	{"Hornet C",32.30,80,-0.63,125,-1.12,175,-2.55},
	{"Hornet H-206",32.05,80,-0.64,125,-1.12,175,-2.49},
	{"Jantar 2B",33.20,80,-0.51,125,-0.87,175,-2.02},
	{"Jantar Std ",33.50,80,-0.68,125,-1.07,175,-2.25},
	{"Jantar SZD 41A",30.90,80,-0.62,125,-1.10,175,-2.41},
	{"Janus",31.10,80,-0.69,125,-1.04,175,-2.08},
	{"Jeans Astir ",29.68,80,-0.73,125,-1.27,175,-2.78},
	{"K 21",31.30,80,-0.74,125,-1.23,175,-2.80},
	{"K 23",26.80,80,-0.68,125,-1.33,175,-3.00},
	{"Ka 6b R/S ",22.20,80,-0.76,125,-1.75,175,-4.30},
	{"Ka 7",26.60,80,-0.94,125,-1.80,175,-4.55},
	{"Ka 8",21.02,60,-0.65,120,-2.10,150,-3.80},
	{"Kestrel 17",31.70,80,-0.59,125,-0.98,175,-2.01},
	{"Kestrel 19",33.40,80,-0.57,125,-0.93,175,-2.03},
	{"Kestrel 22",35.80,80,-0.53,125,-0.81,175,-1.74},
	{"Standard Libelle",35.7,80,-0.68,120,-1.1,175,-2.6},
	{"Club Libelle 205",33.7,80,-0.66,124,-1.2,176,-2.77},
	{"LS 3a",32.60,80,-0.63,125,-0.96,175,-2.9},
	{"LS 1 f",35.50,80,-0.64,125,-1.07,175,-2.34},
	{"LS 3 15m",35.50,80,-0.63,125,-0.92,175,-1.87},
	{"LS 3 17m",33.00,80,-0.56,125,-0.94,175,-2.44},
	{"LS 4",34.40,80,-0.66,125,-0.97,175,-2.24},
	{"LS 6a",33.3,100,-0.67,155,-1.48,212,-3.00},
	{"LS 7 WL",35.97,103.77,-0.73,155.65,-1.47,180.00,-2.66},
	{"LS 8",34.28,100,-0.67,155,-1.45,185,-2.5},
	{"Mini Nimbus",34.20,80,-0.63,125,-0.96,175,-2.13},
	{"Mistral C",31.36,80,-0.67,125,-1.15,175,-2.64},
	{"Mosquito",36.20,80,-0.63,125,-0.92,175,-1.99},
	{"Mosquito B",34.00,80,-0.62,125,-0.93,175,-2.04},
	{"Nimbus 2",30.00,80,-0.50,125,-0.88,175,-2.00},
	{"Nimbus 3",29.50,80,-0.46,125,-0.88,175,-1.85},
	{"Nimbus 3/24.5",28.90,80,-0.39,125,-0.86,175,-1.87},
	{"Nimbus 4/26.5",33.42,85.1,-0.41,127.98,-0.75,162.74,-1.4},
	{"Pegase 101A",32.80,80,-0.63,125,-1.08,175,-2.54},
	{"Pik 20B",35.40,102.5,-0.69,157.76,-1.59,216.91,-3.6},
	{"Pik 20E",43.7,109.61,-0.83,166.68,-2,241.15,-4.7},
	{"Pik 20D",32.50,80,-0.66,125,-1.06,175,-2.20},
	{"Ventus C",33.00,80,-0.52,120,-0.75,180,-2.00},
	{"Salto 13,6m",31.60,80,-0.72,125,-1.32,175,-2.96},
	{"Salto 15m",31.20,80,-0.62,125,-1.24,175,-2.75},
	{"Salto 15,5m",34.00,80,-0.62,125,-1.21,175,-2.73},
	{"SB-10",36.70,80,-0.48,125,-0.82,175,-1.74},
	{"SB-11",36.90,80,-0.68,125,-0.91,175,-1.84},
	{"SB-12",33.20,80,-0.60,125,-0.99,175,-2.36},
	{"SF 27",26.00,74,-0.64,105,-1.00,175,-2.50},
	{"SF 27M",26.00,74,-0.64,105,-1.00,175,-2.50},
	{"SF 34",36.10,80,-0.90,125,-1.19,175,-2.54},
	{"Std Cirrus",30.60,80,-0.64,125,-1.18,175,-2.59},
	{"SZD51-1 Jun.",30.38,80,-0.65,125,-1.20,175,-2.80},
	{"SZD55",52.08,85,-0.9,125,-0.86,175,-1.50},
	{"Ventus A",35.00,80,-0.60,125,-0.87,175,-1.85},
	{"Ventus A/16.6",32.50,80,-0.53,125,-0.93,175,-1.97},
	{"Ventus B",35.00,80,-0.58,125,-0.88,175,-1.93} };

const t_polar Polars::getPolar( int x ) {
		return polars_default_arr[x];
}

int Polars::numPolars() {
	return(  sizeof( polars_default_arr ) / sizeof(t_polar) );
}

Polars::Polars(){ }

Polars::~Polars() {
	// TODO Auto-generated destructor stub
}
