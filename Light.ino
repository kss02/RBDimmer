#include <RBDdimmer.h>//https://github.com/RobotDynOfficial/RBDDimmer//
#include <WiFi.h>// esp32 library
#include <ArduinoJson.h>
#include <IOXhop_FirebaseESP32.h> firebase library
// Firebase connection parameters
#define FIREBASE_HOST "ceilingfanregulation-default-rtdb.firebaseio.com"// URL
#define FIREBASE_AUTH "KyUyCT2zo45IWqxlt6lmL5tYDalrLxhva9SwLcw9"// secret token key
//Wifi Credentials
#define WIFI_SSID "SCRC_LAB"// SSID or Name
#define WIFI_PASSWORD "Scrciiith@123" // Password
//Parameters
const int zeroCrossPin  = 26;// Zerocross detection Pin
const int acdPin  = 13;//PWM Output Pin
String Resivedata="";// Recieve data from Firebase

//Variables
int power  = 0;// Power Output for Load

//Objects
dimmerLamp acd(acdPin,zeroCrossPin);

void setup(){

   //Init Serial USB
   Serial.begin(115200);//Begin Serial Monitor
   Serial.println(F("ESP32 System"));
   acd.begin(NORMAL_MODE, ON);// setting dimmer module to normal mode
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);// WiFi connection
   Serial.print("connecting");
   while (WiFi.status() != WL_CONNECTED)// checking if WiFi is connected or not
   {
        Serial.print(".");
        delay(500);
   }
   Serial.println();
   Serial.print("connected: ");
   Serial.println(WiFi.localIP());//Printing WiFi IP Address
   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);//Firebase Connection
}

void loop(){
  testDimmer();
}

void testDimmer(){/* function testDimmer */ 
////Sweep light power to test dimmer
  Resivedata = Firebase.getString("CeilingFanRegulator/Variable/Value");//recieving data from Firebase
  power=Resivedata.toInt();//converting String to Integer
  //power=map(Resivedata.toInt(), 15, 73, 0, 100);
  
   if(power ==15){
      acd.setState(OFF);
      Serial.println(power);
    }
    else 
    {
      acd.setState(ON);
      
      acd.setPower(power);//setting the power
      Serial.println(power);
    }//debuggging power value
   /* }
    else if(power>73)
    {
      power=100;
      acd.setPower(power);
    }
    else{
      acd.setState(OFF);
    }*/
  delay(100);
}
