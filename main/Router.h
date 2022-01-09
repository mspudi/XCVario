#ifndef __ROUTER_H__
#define __ROUTER_H__

#include "RingBufCPP.h"

#include "freertos/FreeRTOS.h"
#include <freertos/semphr.h>

#include <esp_log.h>
#include <string>

/*
 *   Router for XCVario, to interconnect wireless (Bluetooth or WLAN), XCVario and serial S1,S2 interfaces
 *
 *
 *
 */


#define QUEUE_SIZE 8

extern RingBufCPP<SString, QUEUE_SIZE> wl_vario_tx_q;
extern RingBufCPP<SString, QUEUE_SIZE> wl_flarm_tx_q;
extern RingBufCPP<SString, QUEUE_SIZE> wl_aux_tx_q;
extern RingBufCPP<SString, QUEUE_SIZE> wl_vario_rx_q;
extern RingBufCPP<SString, QUEUE_SIZE> wl_flarm_rx_q;
extern RingBufCPP<SString, QUEUE_SIZE> wl_aux_rx_q;

extern RingBufCPP<SString, QUEUE_SIZE> bt_tx_q;
extern RingBufCPP<SString, QUEUE_SIZE> bt_rx_q;

extern RingBufCPP<SString, QUEUE_SIZE> s1_tx_q;
extern RingBufCPP<SString, QUEUE_SIZE> s2_tx_q;

extern RingBufCPP<SString, QUEUE_SIZE> s1_rx_q;
extern RingBufCPP<SString, QUEUE_SIZE> s2_rx_q;

extern RingBufCPP<SString, QUEUE_SIZE> xcv_rx_q;
extern RingBufCPP<SString, QUEUE_SIZE> xcv_tx_q;

extern RingBufCPP<SString, QUEUE_SIZE> client_rx_q;  // for secondary variometer

extern RingBufCPP<SString, QUEUE_SIZE> client_tx_q;

extern portMUX_TYPE btmux;


class Router {

public:
  Router() { };
  // add message to queue and return true if succeeded
  static bool forwardMsg( SString &s, RingBufCPP<SString, QUEUE_SIZE>& q, bool nmea=false );
  // gets last message from ringbuffer FIFO, return true if succeeded
  static bool pullMsg( RingBufCPP<SString, QUEUE_SIZE>& q, SString& s );
  static int  pullMsg( RingBufCPP<SString, QUEUE_SIZE>& q, char * block );
  // get one big block max 512 byte
  static int pullBlock( RingBufCPP<SString, QUEUE_SIZE>& q, char * block, int size );
  // Route messages generated by XCVario core
  static void routeXCV();
  // Route messages coming in from serial interface S1
  static void routeS1();
  // Route messages coming in from serial interface S2
  static void routeS2();
  // route messages coming in from WLAN
  static void routeWLAN();
  // route messages coming in from Bluetooth
  static void routeBT();
  // route messages coming in from CAN interface
  static void routeClient();
  // add messages from XCVario to Router
  static void sendXCV(char * s);
  // add messages to WIFI AUX port 8882
  static void sendAUX(char * s);

  static void clearQueue( RingBufCPP<SString, QUEUE_SIZE>& q );

private:

};

#endif
