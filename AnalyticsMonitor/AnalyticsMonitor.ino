/* Analytics Monitor for NodeMcu
 by Alojz Jakob <http://jakobdesign.com>

 ******** Analytics Monitor for NodeMcu *********
 *      See your Website/FB page... stats       *
 ************************************************
 
*/

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>

#define OLED_RESET LED_BUILTIN//4
Adafruit_SSD1306 display(OLED_RESET);


#define sound 13
#define led 2

#define RANDOM_REG32  ESP8266_DREG(0x20E44)


#include <ArduinoJson.h>

/**
 * BUILT ONTO ( :) ):
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>



#include <DNSServer.h> //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h> //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>



#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

 

String json;



// monochrome bitmaps converted to code
//http://javl.github.io/image2cpp/


 // 'monitorLogo'
const unsigned char monitorLogo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 
  0x03, 0xe0, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x00, 0x20, 0x10, 0x00, 0x00, 0x18, 0x00, 0x00, 
  0x04, 0x16, 0xe0, 0xf1, 0xb1, 0xbc, 0x87, 0x87, 0x00, 0x60, 0x33, 0xc6, 0xe1, 0x3c, 0x78, 0xf8, 
  0x08, 0x17, 0x31, 0xb1, 0x33, 0x19, 0x8c, 0x99, 0x80, 0x60, 0x66, 0x67, 0x33, 0x18, 0xcc, 0xe0, 
  0x08, 0x16, 0x33, 0x1b, 0x33, 0x11, 0x98, 0xd8, 0xc0, 0x50, 0xec, 0x66, 0x33, 0x11, 0x8c, 0xc0, 
  0x08, 0x16, 0x30, 0x1b, 0x32, 0x31, 0x98, 0x1e, 0x00, 0x51, 0xac, 0x66, 0x33, 0x31, 0x8c, 0xc0, 
  0x1f, 0xf6, 0x31, 0xf3, 0x36, 0x31, 0x90, 0x0f, 0x00, 0x91, 0x28, 0x66, 0x33, 0x31, 0x0c, 0xc0, 
  0x10, 0x26, 0x23, 0x33, 0x14, 0x31, 0x90, 0x03, 0x80, 0x9a, 0x48, 0x66, 0x23, 0x31, 0x0c, 0xc0, 
  0x10, 0x2c, 0x66, 0x33, 0x1c, 0x31, 0x90, 0xb1, 0x80, 0x8c, 0x48, 0x6c, 0x63, 0x31, 0x0c, 0x80, 
  0x10, 0x2c, 0x66, 0x32, 0x18, 0x33, 0x19, 0xb1, 0x80, 0x88, 0x4c, 0xcc, 0x66, 0x31, 0x99, 0x80, 
  0x20, 0x6c, 0x63, 0xf6, 0x18, 0x1b, 0x0f, 0x1e, 0x01, 0x00, 0x47, 0x8c, 0x66, 0x18, 0xf1, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};




 // 'up'
const unsigned char uparr [] PROGMEM = {
  0x01, 0x80, 0x03, 0xc0, 0x07, 0xe0, 0x0f, 0xf0, 0x1d, 0xb8, 0x19, 0x98, 0x31, 0x8c, 0x21, 0x84, 
  0x01, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00
};
 // 'down'
const unsigned char downarr [] PROGMEM = {
  0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x01, 0x80, 
  0x21, 0x84, 0x31, 0x8c, 0x19, 0x98, 0x1d, 0xb8, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80
};




// PAGES DATA

// trampa znanja

const unsigned char trampaLogo [] PROGMEM = {
  0x00, 0x1f, 0xf8, 0x00, 0x00, 0xff, 0xfe, 0x00, 0x03, 0xff, 0xff, 0x80, 0x07, 0xff, 0xff, 0xc0, 
  0x0f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xfc, 
  0x3f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfe, 
  0x7f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xfc, 
  0x3f, 0xff, 0xff, 0xf8, 0x07, 0xff, 0xff, 0xf8, 0x00, 0xff, 0xff, 0xf8, 0x00, 0x7f, 0x3f, 0xf0, 
  0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0x8c, 0xdb, 0x8c, 0x22, 0x52, 0xaa, 0x52, 
  0x22, 0x52, 0xaa, 0x52, 0x23, 0x9e, 0x8b, 0x9e, 0x22, 0x52, 0x8a, 0x12, 0x22, 0x52, 0x8a, 0x12
};

 // 'tamaguino'
const unsigned char tamaguinoLogo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x30, 
  0x00, 0x0d, 0xf8, 0xf8, 0x00, 0x1f, 0xff, 0xdc, 0x00, 0x3f, 0xbf, 0xfe, 0x00, 0x7f, 0xff, 0xec, 
  0x01, 0xff, 0xff, 0xf0, 0x07, 0xdf, 0xfd, 0x00, 0x3f, 0xbc, 0x1e, 0x00, 0x00, 0x7a, 0x2f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x89, 0x48, 0x95, 0x52, 
  0xd5, 0xd5, 0x15, 0x55, 0x95, 0x55, 0x15, 0x55, 0x9d, 0x5d, 0x55, 0x75, 0x55, 0x54, 0xc9, 0x52, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};




// puzzle-mania

const unsigned char puzzleLogo [] PROGMEM = {
  0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x60, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 
  0xe7, 0xf0, 0x00, 0x00, 0xc3, 0x60, 0xff, 0x80, 0xc3, 0x00, 0xff, 0x80, 0xe7, 0x00, 0x9f, 0x80, 
  0x00, 0x18, 0x0f, 0x80, 0x00, 0x3c, 0x0f, 0x80, 0x00, 0x3c, 0x9f, 0x80, 0x00, 0x18, 0xff, 0x80, 
  0x00, 0x18, 0xff, 0x80, 0x01, 0xfe, 0x18, 0x00, 0x01, 0xfe, 0xdb, 0x80, 0x01, 0xf2, 0xbd, 0x80, 
  0x01, 0xec, 0xbd, 0x80, 0x01, 0xdf, 0xdb, 0x80, 0x01, 0xdf, 0xe7, 0x80, 0x01, 0xec, 0xff, 0x80, 
  0x01, 0xf2, 0xff, 0x80, 0x01, 0xfe, 0xff, 0x80, 0x01, 0xfe, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xe4, 0xbe, 0xfa, 0x1e, 0x94, 0x82, 0x0a, 0x10, 0x94, 0x84, 0x12, 0x10, 
  0xe4, 0x88, 0x22, 0x1c, 0x84, 0x90, 0x42, 0x10, 0x84, 0xa0, 0x82, 0x10, 0x83, 0x3e, 0xfb, 0xde
};

// scientific mind
const unsigned char scimindLogo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x32, 0xb4, 0xba, 0xd2, 0x44, 0xa4, 0x92, 0x94, 0x24, 0xb6, 0x92, 0xd4, 
  0x14, 0xa5, 0x92, 0x94, 0x62, 0xb4, 0x92, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0xb5, 0x2c, 0x00, 0x01, 0x55, 0x2a, 0x00, 0x01, 0x15, 0xaa, 0x01, 0x01, 0x15, 0x6a, 0x00, 
  0x01, 0x15, 0x2c, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x10, 0x00, 0x00, 0x80, 0x20, 
  0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x2e, 0x80, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x3f, 0x80, 
  0x02, 0x55, 0x60, 0x3f, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x1f, 0xf0, 0x00, 
  0x01, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

 // 'youtube'
const unsigned char youtubeLogo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf8, 
  0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x7f, 0xfb, 0xff, 0xfe, 
  0x7f, 0xf8, 0xff, 0xfe, 0x7f, 0xf8, 0x3f, 0xfe, 0x7f, 0xf8, 0x0f, 0xfe, 0x7f, 0xf8, 0x07, 0xfe, 
  0x7f, 0xf8, 0x0f, 0xfe, 0x7f, 0xf8, 0x3f, 0xfe, 0x7f, 0xf8, 0xff, 0xfe, 0x7f, 0xfb, 0xff, 0xfe, 
  0x7f, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 
  0x1f, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};




#define PAGES 9
const unsigned char* pageLogo[PAGES] = {
    trampaLogo,
    trampaLogo,
    tamaguinoLogo,
    puzzleLogo,
    puzzleLogo,
    scimindLogo,
    scimindLogo,
    youtubeLogo,
    youtubeLogo,
  };


// intro screen page logos, 4 logos fit on OLED :)
const unsigned char* pageLogoIntro[4] = {
    trampaLogo,
    tamaguinoLogo,
    puzzleLogo,
    scimindLogo,
  };



//Facebook Graph API to get likes
//https://graph.facebook.com/[PAGE_ID]?access_token=[APP_ID]|[APP_SECRET]&fields=likes

//YouTube API
//https://www.googleapis.com/youtube/v3/channels?part=statistics&id=[CHANNEL_ID]&key=[API_KEY]

//Google Analytics
//http://yourwebsite.com/path_to_your_script/analytics.php?secret=[SECRET_DEFINED_IN_PHP]&viewId=[ANALYTICS_VIEW_ID]



//facebook graph api ssl cert fingerprint
//E9 5D 7C 0D F3 E8 F2 05 A9 B5 A4 57 0C DD 20 B8 75 27 84 B1
// googleapis ssl cert fingerprint
//4A A4 1D CF B9 06 6C A4 E9 84 C0 96 DE 61 A8 BE 39 12 66 78
//...
// sometimes fingerprint changes, that is why we use alternate fingerprints array



const char* apiPageLink[PAGES] = {
  "https://graph.facebook.com/446047655602855?access_token=[TOKEN]&fields=likes",
  "http://yourwebsite.com/path_to_your_script/analytics.php?secret=[SECRET_DEFINED_IN_PHP]&viewId=106889041", //trampa
  "http://yourwebsite.com/path_to_your_script/analytics.php?secret=[SECRET_DEFINED_IN_PHP]&viewId=140836915", //tamaguino
  "https://graph.facebook.com/548493065201084?access_token=[TOKEN]&fields=likes", // puzzle
  "http://yourwebsite.com/path_to_your_script/analytics.php?secret=[SECRET_DEFINED_IN_PHP]&viewId=99311017", // puzzle
  "https://graph.facebook.com/341705772579133?access_token=[TOKEN]&fields=likes", //scimind
  "http://yourwebsite.com/path_to_your_script/analytics.php?secret=[SECRET_DEFINED_IN_PHP]&viewId=62448387", // scimind
  "https://www.googleapis.com/youtube/v3/channels?part=statistics&id=[CHANNEL_ID]&key=[API_KEY]",
  "https://www.googleapis.com/youtube/v3/channels?part=statistics&id=[CHANNEL_ID]&key=[API_KEY]",
};

const char* httpsFingerprints[PAGES] = {
  "E9 5D 7C 0D F3 E8 F2 05 A9 B5 A4 57 0C DD 20 B8 75 27 84 B1",
  "",
  "",
  "E9 5D 7C 0D F3 E8 F2 05 A9 B5 A4 57 0C DD 20 B8 75 27 84 B1",
  "",
  "E9 5D 7C 0D F3 E8 F2 05 A9 B5 A4 57 0C DD 20 B8 75 27 84 B1",
  "",
  "4A A4 1D CF B9 06 6C A4 E9 84 C0 96 DE 61 A8 BE 39 12 66 78",
  "4A A4 1D CF B9 06 6C A4 E9 84 C0 96 DE 61 A8 BE 39 12 66 78",
};

const char* httpsFingerprintsAlternate[PAGES] = {
  "E9 5D 7C 0D F3 E8 F2 05 A9 B5 A4 57 0C DD 20 B8 75 27 84 B1",
  "",
  "",
  "E9 5D 7C 0D F3 E8 F2 05 A9 B5 A4 57 0C DD 20 B8 75 27 84 B1",
  "",
  "E9 5D 7C 0D F3 E8 F2 05 A9 B5 A4 57 0C DD 20 B8 75 27 84 B1",
  "",
  "8F 6B 3C E4 C4 35 EA 66 C7 91 51 AC E0 AF 3B A6 B6 B2 4C 42",
  "8F 6B 3C E4 C4 35 EA 66 C7 91 51 AC E0 AF 3B A6 B6 B2 4C 42",
};

// alternate youtube fingerprint
// 8F 6B 3C E4 C4 35 EA 66 C7 91 51 AC E0 AF 3B A6 B6 B2 4C 42

const char* displayTitle[PAGES] = {
  "Likes",
  "Page Views",
  "Page Views",
  "Likes",
  "Page Views",
  "Likes",
  "Page Views",
  "Views",
  "Subscribers"
};



//1 - facebook graph json
//2 - youtube json - views
//3 - youtube json - views
//4 - analytics json
// used to switch display type in code, and perform different data extraction, since jsons are not the same for all calls!
const int responseType[PAGES]{
  1,
  4,
  4,
  1,
  4,
  1,
  4,
  2,
  3
};



int previousLikes[PAGES];
int currentLikes;
bool uparrow[PAGES];
bool downarrow[PAGES];
bool change[PAGES];



// END PAGES DATA



void setup() {

    //init temporary arrays
    
    for(int i=0;i<PAGES;i++){
      previousLikes[i]=0;
      uparrow[i]=false;
      downarrow[i]=false;
      change[i]=false;
    }

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    
    
    drawIntroChart();

    delay(2000);
    
    display.clearDisplay();
    
    display.setTextColor(WHITE);
    display.setCursor(0,0); 
    display.setTextSize(1);
    //display.println(" --- Like Monitor ---");
    //display.println("Connect to \"Like Monitor\" AP to configure");
    display.println("     Connect to");
    display.println(" ");
    display.println("  \"Like Monitor\" AP");
    display.println("  to configure WiFi");
    
    display.display();
    



    pinMode(sound, OUTPUT);
    pinMode(led, OUTPUT);
    digitalWrite(led,LOW);
    

    USE_SERIAL.begin(115200);
    USE_SERIAL.setDebugOutput(true);


    
    USE_SERIAL.println("test");
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFiManager wifiManager;
    //this sets your NodeMcu as AP if it cannot connect to WIFi
    //when connected, you will see captive portal to configure WiFi credentials!
    //first parameter is name of access point, second is the password
    wifiManager.autoConnect("Like Monitor", "monitor");

    
    //predefined APs
    WiFiMulti.addAP("MY-HOME-AP", "myWiFiPassword");
    WiFiMulti.addAP("My-OFFICE-AP", "anotherPassword");
    //...


    for(int i=0;i<10;i++){
      tone(sound, 1600,200);
      delay(300);
    }

    
                    


}

void loop() {

    for(int page=0;page<PAGES;page++){
      
      // wait for WiFi connection
      if((WiFiMulti.run() == WL_CONNECTED)) {
  
          HTTPClient http;
  
          USE_SERIAL.print("[HTTP] begin...\n");

          if(httpsFingerprints[page]!=""){
            http.begin(apiPageLink[page],httpsFingerprints[page]); //HTTPS
          }else{
            http.begin(apiPageLink[page]); //HTTP
          }
  
          USE_SERIAL.print("[HTTP] GET...\n");
          // start connection and send HTTP header
          int httpCode = http.GET();

          if(httpCode <= 0) {
            USE_SERIAL.print("[HTTP] GET alternate Fingerprint...\n");
            http.end();
            http.begin(apiPageLink[page],httpsFingerprintsAlternate[page]); //HTTP
            httpCode = http.GET();
          }
  
          // httpCode will be negative on error
          if(httpCode > 0) {
              // HTTP header has been send and Server response header has been handled
              USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
  
              // file found at server
              if(httpCode == HTTP_CODE_OK) {
                  json = http.getString();

                  
                  int graphDots[7];
                  
                  const char* likes = "";
                  if(responseType[page]==1){
                    StaticJsonBuffer<200> jsonBuffer;
                    JsonObject& root = jsonBuffer.parseObject(json);
                    likes = root["likes"];
                  }
                  if(responseType[page]==2){
                    const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 400;
                    DynamicJsonBuffer jsonBuffer(bufferSize);
                    JsonObject& root = jsonBuffer.parseObject(json);
                    JsonObject& items0 = root["items"][0];
                    JsonObject& items0_statistics = items0["statistics"];
                    likes = items0_statistics["viewCount"];
                  }
                  if(responseType[page]==3){
                    const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 400;
                    DynamicJsonBuffer jsonBuffer(bufferSize);
                    JsonObject& root = jsonBuffer.parseObject(json);
                    JsonObject& items0 = root["items"][0];
                    JsonObject& items0_statistics = items0["statistics"];
                    likes = items0_statistics["subscriberCount"];
                  }
                  //analytics pageviews
                  if(responseType[page]==4){
                    const size_t bufferSize = 8*JSON_ARRAY_SIZE(3) + JSON_ARRAY_SIZE(8) + 130;
                    DynamicJsonBuffer jsonBuffer(bufferSize);
                    JsonArray& root = jsonBuffer.parseArray(json);
                    likes=root[0][2];
                    for(int i=0;i<7;i++){
                      graphDots[i]=atoi(root[6-i][2]);
                    }
                  }
                  
                  USE_SERIAL.print("likes: ");
                  USE_SERIAL.println(likes);


                  int numLikes=atoi(likes);
                  //int numLikes=0;
                  if(previousLikes[page]>0 && previousLikes[page]!=numLikes){
                    
                    if(numLikes>previousLikes[page]){
                      uparrow[page]=true;
                      downarrow[page]=false;
                      change[page]=true;
                    }
                    if(numLikes<previousLikes[page]){
                      uparrow[page]=false;
                      downarrow[page]=true;
                      change[page]=true;
                    }
                    
                  }

                  previousLikes[page]=numLikes;
  
                  // all but analytics
                  if(responseType[page]!=4){

                    // DISPLAY
                    for(int i=24;i>=0;i=i-1){
                      
                      display.clearDisplay();
                      /*
                      if(change && i%4==1){
                        display.setTextColor(WHITE);
                      }else{
                        display.setTextColor(BLACK,WHITE);
                      }*/
    
                      if(change[page]){
                        display.fillRoundRect(19,-4,68,36,4,WHITE);
                        display.setTextColor(BLACK,WHITE);
                      }else{
                        display.drawRoundRect(19,-4,68,36,4,WHITE);
                        display.setTextColor(WHITE);
                      }
                      
                      display.setCursor(24,14); 
                      display.setTextSize(2);
                      display.print(likes);
      
                      if(uparrow[page]){
                        USE_SERIAL.println("up");
                        display.drawBitmap(0,15+i, uparr , 16, 16, WHITE);
                      }
                      if(downarrow[page]){
                        USE_SERIAL.println("down");
                        display.drawBitmap(0, 15-i, downarr , 16, 16, WHITE);
                      }
      
                      display.drawBitmap(96, 0, pageLogo[page] , 32, 32, WHITE);
                      
                      display.fillRoundRect(-8,-8,94,19,8,WHITE);
                      display.setTextSize(1);
                      display.setTextColor(BLACK,WHITE);
                      display.setCursor(2,2);
                      display.println(displayTitle[page]);
                      display.display();
                      
                    }
                    // END DISPLAY
                    
                  }

                  // Analytics specific
                  if(responseType[page]==4){
    
                    // DISPLAY

                    

                    int maxValue,minValue;
                    maxValue=graphDots[0];
                    minValue=graphDots[0];
                    for(int i=0;i<7;i++){
                      if(graphDots[i]>maxValue){
                        maxValue=graphDots[i];
                      }
                      if(graphDots[i]<minValue){
                        minValue=graphDots[i];
                      }
                    }
                    
                    

                    int origX=34;
                    int stepX=8;
                    int origY=20;
                    int axisY;
                    int axisYprev=origY;
                    int maxY=7;

                    for(int i=0;i<7;i++){

                      display.clearDisplay();
                      
                      //maxValue:14=graphDots[i]:x
                      //14*graphDots[i]=maxValue*x
                      //x=14*graphDots[i]/maxValue

                      display.fillRect(30,-4,57,40,WHITE);
                      
                      for(int j=0;j<i+1;j++){
                        axisY=round(maxY*graphDots[j]/maxValue);
                        if(j==0){
                          axisYprev=axisY;
                          display.fillCircle(origX+stepX*j,origY-axisY,2,BLACK);
                        }else{
                          display.drawLine(origX+stepX*(j-1),origY-axisYprev,origX+stepX*j,origY-axisY,BLACK);
                          display.fillCircle(origX+stepX*j,origY-axisY,2,BLACK);
                          axisYprev=axisY;
                        }
                      }

                      //display.drawRect(30,-4,57,40,WHITE);
                      
                      //display.fillRect(31,23,55,16,WHITE);
                      display.setTextColor(BLACK,WHITE);
                      display.setTextSize(1);
                      display.setCursor(32,24);
                      display.print(graphDots[i]);
                      
                      display.setTextColor(WHITE);
                      display.setTextSize(1);
                      
                      display.setCursor(0,14);
                      display.print(maxValue);
                      display.setCursor(0,24);
                      display.print(minValue);

                      
                      display.drawBitmap(96, 0, pageLogo[page] , 32, 32, WHITE);
                    
                      display.fillRoundRect(22,-8,65,20,8,BLACK);
                      display.fillRoundRect(-8,-8,94,19,8,WHITE);
                      display.setTextSize(1);
                      display.setTextColor(BLACK,WHITE);
                      display.setCursor(2,2);
                      display.println(displayTitle[page]);
                      display.display();
                      delay(500);


                      
                    }

                    
                    // END DISPLAY
                    
                  }


                  //flash LED and play tune
                  if(change[page]){
                    for(int i=0;i<10;i++){
                      digitalWrite(led,HIGH);
                      delay(100);
                      digitalWrite(led,LOW);  
                      delay(100);
                    }
                    for(int i=0;i<10;i++){
                      tone(sound, 1600,200);
                      delay(300);
                    }
                  }

                  change[page]=false;
                  
                  
                  delay(3000);
              }
          } else {
              USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }
  
          http.end();
      }
      
    
      //delay(3000);

    }

    
}


void drawIntroChart(){

  // draw intro screen with animated random chart! how cool is that!

  int numDots=12;
  int graphDots[numDots]; //10 px per division 4px xstart

  randomSeed(RANDOM_REG32);
  
  for(int i=0;i<numDots;i++){
    graphDots[i]=random(0,100);
  }
  
  int maxValue,minValue;
  maxValue=graphDots[0];
  minValue=graphDots[0];
  for(int i=0;i<numDots;i++){
    if(graphDots[i]>maxValue){
      maxValue=graphDots[i];
    }
    if(graphDots[i]<minValue){
      minValue=graphDots[i];
    }
  }
  
  

  int origX=2;
  int stepX=11;
  int origY=15;
  int axisY;
  int axisYprev=origY;
  int maxY=13;

  for(int i=0;i<numDots;i++){

    display.clearDisplay();
    
    //maxValue:14=graphDots[i]:x
    //14*graphDots[i]=maxValue*x
    //x=14*graphDots[i]/maxValue

    display.drawBitmap(0, 0, monitorLogo , 128, 32, WHITE);
    
    for(int j=0;j<i+1;j++){
      axisY=round(maxY*graphDots[j]/maxValue);
      if(j==0){
        axisYprev=axisY;
        display.fillCircle(origX+stepX*j,origY-axisY,2,WHITE);
      }else{
        display.drawLine(origX+stepX*(j-1),origY-axisYprev,origX+stepX*j,origY-axisY,WHITE);
        display.fillCircle(origX+stepX*j,origY-axisY,2,WHITE);
        axisYprev=axisY;
      }
    }
  
    
    
    display.display();
    delay(100);
  }

  delay(2000);

  bool displayed[4]={false,false,false,false};

  for(int i=0;i<4;i++){
    for(int j=128;j>=i*32;j-=4){
      display.clearDisplay();
      display.drawBitmap(j, 0, pageLogoIntro[i] , 32, 32, WHITE);
      for(int k=0;k<4;k++){
        if(displayed[k]){
          display.drawBitmap(k*32, 0, pageLogoIntro[k] , 32, 32, WHITE);
        }
      }
      if(j==i*32){
        displayed[i]=true;
      }
      
      display.display();
      delay(5);
    }
  }
   
}


