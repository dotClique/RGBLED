#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        14 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 300 // Popular NeoPixel ring size
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

#ifndef STASSID
#define STASSID "Kára 2.4GHz"
#define STAPSK  "SjokkAtPassordetErLangt"
#endif

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
const char* ssid     = STASSID;
const char* password = STAPSK;
uint8_t rgb[3] = {122,122,122};
uint8_t wave = 0;
int mode = 0;
int o1 = 0; //Option 1
int o2 = 0; //Option 2

ESP8266WebServer server(80);

const int led = LED_BUILTIN;

const String postForms = "<html>\
  <head>\
    <title>ESP8266 Web Server POST handling</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
      <h1>POST form data to mode</h1><br>\
    <form method=\"post\" enctype=\"application/x-www-form-urlencoded\"  action=\"/mode/\">\
      <input type=\"number\" name=\"mode\" value=\"world\"><br>\
      <input type=\"submit\" value=\"Submit\">\
    </form>\
    <h1>POST plain text to r</h1><br>\
    <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/r/\">\
      <input type=\"number\" name=\'r\'><br>\
      <input type=\"submit\" value=\"Submit\">\
    </form>\
    <h1>POST form data to g</h1><br>\
    <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/g/\">\
      <input type=\"number\" name=\"g\" value=\"world\"><br>\
      <input type=\"submit\" value=\"Submit\">\
    </form>\
    <h1>POST form data to b</h1><br>\
    <form method=\"post\" enctype=\"application/x-www-form-urlencoded\"  action=\"/b/\">\
      <input type=\"number\" name=\"b\" value=\"world\"><br>\
      <input type=\"submit\" value=\"Submit\">\
    </form>\
        <h1>POST option 1</h1><br>\
    <form method=\"post\" enctype=\"application/x-www-form-urlencoded\"  action=\"/o1/\">\
      <input type=\"number\" name=\"o1\" value=\"world\"><br>\
      <input type=\"submit\" value=\"Submit\">\
    </form>\
        <h1>POST option 2</h1><br>\
    <form method=\"post\" enctype=\"application/x-www-form-urlencoded\"  action=\"/o2/\">\
      <input type=\"number\" name=\"o2\" value=\"world\"><br>\
      <input type=\"submit\" value=\"Submit\">\
    </form>\
  </body>\
</html>";

void handleRoot() {
    digitalWrite(led, 1);
    server.send(200, "text/html", postForms);
    digitalWrite(led, 0);
}

void handleR() {
    if (server.method() != HTTP_POST) {
        digitalWrite(led, 1);
        server.send(405, "text/plain", "Method Not Allowed");
        digitalWrite(led, 0);
    } else {
        String temp = server.arg("plain");
        temp.remove(0,2);
        rgb[0] = temp.toInt();
        Serial.println(rgb[0]);
        Serial.println(temp);
        digitalWrite(led, 0);
    }
    server.send(200, "text/html", postForms);
}

void handleG() {
    if (server.method() != HTTP_POST) {
        digitalWrite(led, 1);
        server.send(405, "text/plain", "Method Not Allowed");
        digitalWrite(led, 0);
    } else {
        digitalWrite(led, 1);
        String temp = server.arg("plain");
        temp.remove(0,2);
        rgb[1] = temp.toInt();
        Serial.println(rgb[1]);
        Serial.println(temp);
        digitalWrite(led, 0);
    }
    server.send(200, "text/html", postForms);

}

void handleOption1() {
    if (server.method() != HTTP_POST) {
        digitalWrite(led, 1);
        server.send(405, "text/plain", "Method Not Allowed");
        digitalWrite(led, 0);
    } else {
        digitalWrite(led, 1);
        String temp = server.arg("plain");
        temp.remove(0,3);
        o1 = temp.toInt();
        Serial.println(o1);
        Serial.println(temp);
        digitalWrite(led, 0);
    }
    server.send(200, "text/html", postForms);

}

void handleOption2() {
    if (server.method() != HTTP_POST) {
        digitalWrite(led, 1);
        server.send(405, "text/plain", "Method Not Allowed");
        digitalWrite(led, 0);
    } else {
        digitalWrite(led, 1);
        String temp = server.arg("plain");
        temp.remove(0,3);
        o2 = temp.toInt();
        Serial.println(o2);
        Serial.println(temp);
        digitalWrite(led, 0);
    }
    server.send(200, "text/html", postForms);

}

void handleB() {
    if (server.method() != HTTP_POST) {
        digitalWrite(led, 1);
        server.send(405, "text/plain", "Method Not Allowed");
        digitalWrite(led, 0);
    } else {
        digitalWrite(led, 1);
        String temp = server.arg("plain");
        temp.remove(0,2);
        rgb[2] = temp.toInt();
        Serial.println(rgb[2]);
        Serial.println(temp);
        digitalWrite(led, 0);
    }
    server.send(200, "text/html", postForms);

}

void handleMode(){
    if (server.method() != HTTP_POST) {
        digitalWrite(led, 1);
        server.send(405, "text/plain", "Method Not Allowed");
        digitalWrite(led, 0);
    } else {
        String temp = server.arg("plain");
        temp.remove(0,5);
        mode = temp.toInt();
    }
    server.send(200, "text/html", postForms);
}

void handleNotFound() {
    digitalWrite(led, 1);
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
    digitalWrite(led, 0);
}

void setup(void) {
    pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    pinMode(led, OUTPUT);
    digitalWrite(led, 0);
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);

    server.on("/r/", handleR);

    server.on("/g/", handleG);

    server.on("/b/", handleB);

    server.on("/o1/", handleOption1);

    server.on("/o2/", handleOption2);

    server.on("/mode/",handleMode);


    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("HTTP server started");
}


int partition(int arr[],int low,int high) {
  int pivot = arr[high];
  int small = low;
  for (int i = low; i < high; i++) {
    if (arr[i]<pivot) {
        int sw = arr[i];
        arr[i] = arr[small];
        arr[small] = sw;
        small++;
        pixels.setPixelColor(i,pixels.ColorHSV(arr[i]));
        pixels.setPixelColor(small,pixels.ColorHSV(arr[small]));
        pixels.show();
              server.handleClient();
    }
  }
         int sw = arr[high];
        arr[high] = arr[small];
        arr[small] = sw;
                pixels.setPixelColor(high,pixels.ColorHSV(arr[high]));
        pixels.setPixelColor(small,pixels.ColorHSV(arr[small]));
        pixels.show();
              server.handleClient();
  return small;
}


int quicksort(int arr[], int low, int high) {
  if (low<high) {
    int pi = partition(arr,low,high);

    quicksort(arr,low,pi-1);
    quicksort(arr,pi+1,high);

  }
}

void shadertoy(double (*r)(double, double), double (*g)(double, double),double (*b)(double, double)) {
    for(uint16_t j = 0; j<2*NUMPIXELS;j++) {

      for(uint16_t i = 0; i<NUMPIXELS;i++){
        double i2 = double(i)/NUMPIXELS;
        double j2 = double(j)/NUMPIXELS;
        pixels.setPixelColor(i,int(255*((*r)(i2,j2))),int(255*((*g)(i2,j2))),int(255*((*b)(i2,j2))));
      }

      pixels.show();   // Send the updated pixel colors to the hardware.

      server.handleClient();
  }
}

double smod(double x,double m) {
  return fmod(m+fmod(x,m),m);
}

double step(double lim, double x) {
  return (x > lim) ? 1.:0.;
}
double right_light_pulse(double x,double t) {
    double combined = smod(x*30,1.)+t*5;
    combined = fabs(1.-2.*smod(combined,1.));
   return combined*combined;
}

double empty_light_pulse(double x, double t) {
   return 0.;
}

double left_light_pulse(double x, double t) {
      double combined = (smod(x*30,1.)-t*5);
      combined = fabs(1.-2.*smod(combined,1.));
   return combined*combined;
}

void loop(void) {
    if(mode == 0){
        pixels.clear(); // Set all pixel colors to 'off'

        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        // Here we're using a moderately bright green color:
        pixels.fill(rgb[0]*256*256+rgb[1]*256+rgb[2]);
        pixels.show();   // Send the updated pixel colors to the hardware.
        server.handleClient();
    }else if(mode == 1){
        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        // Here we're using a moderately bright green color:
        for(uint16_t i = 0; i<NUMPIXELS;i++){
            pixels.setPixelColor(i,random(256),random(256),random(256));
            pixels.show();   // Send the updated pixel colors to the hardware.
            server.handleClient();
        }

    }else if(mode == 2){
        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        // Here we're using a moderately bright green color:
        for(uint16_t i = 0; i<NUMPIXELS;i++){
            pixels.setPixelColor(i,uint8_t(wave+i*255/NUMPIXELS),4*i,uint8_t(wave + 255-i*255/(NUMPIXELS)));
            server.handleClient();
        }
        wave++;
        delay(50);
        pixels.show();   // Send the updated pixel colors to the hardware.

    }else if(mode == 3){
        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        // Here we're using a moderately bright green color:
        for(uint16_t i = 0; i<NUMPIXELS;i++){
            pixels.setPixelColor(i,(i<60) ? 255:((i<120) ? (255-255*(i-60)/60):0),(i<60) ? 0: ((i<120) ? (255*(i-120)/60):((i<180)? 255: ((i<240)?(255-(255*(i-180)/60)):0))), (i>=180) ? ((i<240) ? (255*(i-180)/60):255) :0);
        }
        pixels.show();   // Send the updated pixel colors to the hardware.
        server.handleClient();

    }else if(mode == 4){
        uint16_t *cArray = new uint16_t[NUMPIXELS];
        for(int p = 0; p < NUMPIXELS; p++){
            cArray[p] = random(65536);
        }
        Serial.println("AWIMMAWE1");
        for(int i = 0; i < NUMPIXELS; i++){
            pixels.setPixelColor(i,pixels.ColorHSV(cArray[i]));
        }
        Serial.println("AWIMMAWE2");
        pixels.show();
        for(int i = 0; i < NUMPIXELS; i++){
            for(int j = i; j>0;j--){
                if(cArray[j-1] < cArray[j]) break;
                uint16_t temp;
                temp = cArray[j];
                cArray[j] = cArray[j-1];
                cArray[j-1] = temp;
                pixels.setPixelColor(j,pixels.ColorHSV(cArray[j]));
                pixels.setPixelColor(j-1,pixels.ColorHSV(cArray[j-1]));
                pixels.show();
                server.handleClient();
            }
            for(int k = 0; k < NUMPIXELS; k++){
                pixels.setPixelColor(k,pixels.ColorHSV(cArray[k]));
            }
            pixels.show();
            server.handleClient();

        }
    }else if(mode == 5){
        uint16_t *cArray = new uint16_t[NUMPIXELS];
        for(int p = 0; p < NUMPIXELS; p++){
            cArray[p] = random(65536);
        }
        Serial.println("AWIMMAWE1");
        for(int i = 0; i < NUMPIXELS; i++){
            pixels.setPixelColor(i,pixels.ColorHSV(cArray[i]));
        }
        Serial.println("AWIMMAWE2");
        pixels.show();
        int i, j;
        bool swapped = false;
        for (i = 0; i < NUMPIXELS; i++)
        {
            swapped = false;
            for (j = 1; j < NUMPIXELS; j++) {
                if (cArray[j-1] > cArray[j]) {
                    uint16_t temp = cArray[j];
                    cArray[j] = cArray[j - 1];
                    cArray[j - 1] = temp;
                    Serial.println("AWIMMAWE9");
                    swapped = true;
                    pixels.setPixelColor(j,pixels.ColorHSV(cArray[j]));
                    pixels.setPixelColor(j-1,pixels.ColorHSV(cArray[j-1]));
                    pixels.show();
                    server.handleClient();
                }
            }
            // IF no two elements were swapped by inner loop, then break
            for(int k = 0; k < NUMPIXELS; k++){
                pixels.setPixelColor(k,pixels.ColorHSV(cArray[k]));
            }
            pixels.show();
            server.handleClient();
            if (!swapped){
                delay(10000);
                break;}
        }
        delay(10000);
        server.handleClient();



    }else if(mode == 6) {
        uint16_t *cArray = new uint16_t[NUMPIXELS];
        bool StalinArray[NUMPIXELS] ;
        for(int p = 0; p < NUMPIXELS; p++){
            cArray[p] = random(65536);
            StalinArray[p]  = true;
        }
        Serial.println("AWIMMAWE1");
        for(int i = 0; i < NUMPIXELS; i++){
            pixels.setPixelColor(i,pixels.ColorHSV(cArray[i]));
        }
        pixels.show();
        Serial.println("AWIMMAWE2");
        for(int i = 0; i < NUMPIXELS-1;) {
            if(!StalinArray[i]) {
                i++;
                continue;
            }
            Serial.println("AWIMMAWE3");
            int next = 0;
            for(int b = i+1; b<NUMPIXELS;b++) {
                if(StalinArray[b]) {
                    next = b;
                    break;
                }
            }
            Serial.println("AWIMMAWE4");
            if((next == 0) or (cArray[i] < cArray[next])) {
                i++;
            }else {
                StalinArray[next] = false;
                pixels.setPixelColor(next, 0,0,0);
                pixels.show();
                server.handleClient();
            }
        }
        for(int i =0; i<NUMPIXELS; i++) {
            if(StalinArray[i]) {
                pixels.setPixelColor(i,pixels.ColorHSV(cArray[i]));
            }else {
                pixels.setPixelColor(i,0,0,0);
            }
            pixels.show();
            server.handleClient();
        }
        for(int i = 0; i < 10; i++){
            delay(1000);
            server.handleClient();
        }
    }else if(mode == 7) {
       double (*r)(double, double);
       double (*g)(double, double);
       double (*b)(double, double);
       r=  &empty_light_pulse;
       g = &empty_light_pulse;
       b = &empty_light_pulse;
      if (o1 == 0) {
        r = &right_light_pulse;
      } else if (o1 == 1) {
        g = &right_light_pulse;
      } else if (o1 == 2) {
        b = &right_light_pulse;
      }
      if (o2 == 0) {
        r = &left_light_pulse;
      } else if (o2 == 1) {
        g = &left_light_pulse;
      } else if (o2 == 2) {
        b = &left_light_pulse;
      }
      shadertoy(r,g,b);
    }else if(mode == 8) {
              int list_length = 300;//rgb[0];

       int *arr = new int[list_length];

       for (int i = 0; i < list_length; i++) {
        arr[i] = random(65536);
        pixels.setPixelColor(i,pixels.ColorHSV(arr[i]));
        pixels.show();
              server.handleClient();
       }


        quicksort(arr,0,list_length-1);
        server.handleClient();
    }else{
        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        // Here we're using a moderately bright green color:
        for(uint16_t i = 0; i<NUMPIXELS;i++){
            pixels.setPixelColor(i,rgb[0],rgb[1],rgb[2]);
            pixels.show();   // Send the updated pixel colors to the hardware.
            server.handleClient();
        }
    }
}