#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

#include "time.h"

#define RXD2 13
#define TXD2 12

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "" 
#define WIFI_PASSWORD "" 

// Insert Firebase project API Key
#define API_KEY ""

/* Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL ""
#define USER_PASSWORD ""

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://thermostat-c1685-default-rtdb.firebaseio.com"

/* Define the project ID */
#define FIREBASE_PROJECT_ID "thermostat-c1685"

// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;
char buf[80];
char buf1[80];

// CHEMIN DATE & HORAIRES...
String databasePath;
String dataHourPath;

// CHEMIN DES CONSIGNES
String dataC1Path;
String dataC2Path;
String dataC3Path;
String dataC4Path;
String dataC5Path;

uint8_t tableconsi[7];
uint8_t endline=13;
uint8_t compteur=0;

// VARIABLES POUR CONSIGNES
int consigne1 = 0;
int consigne2 = 0;
int consigne3 = 0;
int consigne4 = 0;
int consigne5 = 0;

bool sendtoserver=false;

FirebaseJson json;
 
const char* ntpServer = "pool.ntp.org"; //europe.pool.ntp.org
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 0; //3600


unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false; 



void printLocalTime(){
  time_t now;
  struct tm timeinfo;

  // Get current time
    time(&now);

  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time!");
    return;
  }
  //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  //Serial.println(&timeinfo, "%Y, %B, %d");
  //Serial.println(&timeinfo, "%Y-%B-%d");

// Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
    timeinfo = *localtime(&now);
    //strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &timeinfo);
    strftime(buf, sizeof(buf), "%d-%m-%Y", &timeinfo);
    strftime(buf1, sizeof(buf1), "%H:%M", &timeinfo);
    printf("%s\n", buf);
    printf("%s\n", buf1);
}


void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println(); 


// Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();



  /* Assign the api key (required) */
  config.api_key = API_KEY; //"" 

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL; //"https://thermostat-c1685-default-rtdb.firebaseio.com"

  /* Sign up
  if (Firebase.signUp(&config, &auth, "", ""))
  {
    Serial.println("ok");
    signupOK = true;
  }
  else
  {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }*/

  // Assign the user sign in credentials 
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "")
  {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.print(uid);

   // Update database path
  databasePath = "thermolit/date";
  dataHourPath = "thermolit/horaire";

  // renouvel chemin pour les consignes
  dataC1Path = "thermolit/consigne1";
  dataC2Path = "thermolit/consigne2";
  dataC3Path = "thermolit/consigne3";
  dataC4Path = "thermolit/consigne4";
  dataC5Path = "thermolit/consigne5";

  tableconsi[0]=20;
  tableconsi[1]=15;
  tableconsi[2]=27;
  tableconsi[3]=22;
  tableconsi[4]=26;
  sendtoserver=true;

}


void loop()
{
  while (Serial2.available())
  {
    
    uint8_t vlor=Serial2.read();
    Serial.println(vlor);
    if(vlor==endline){
      compteur=0;
      sendtoserver=true;
    }
    else
    {
      if(vlor!=100)
      {
        tableconsi[compteur]=vlor;
         compteur++;
      }
       }
  }
  if(sendtoserver==true  && Firebase.ready() ){
     //consigne1
    if (Firebase.RTDB.setInt(&fbdo, "thermolit/consigne1", tableconsi[0]))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

  //consigne2
    if (Firebase.RTDB.setInt(&fbdo, "thermolit/consigne2", tableconsi[1]))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //consigne3
    if (Firebase.RTDB.setInt(&fbdo, "thermolit/consigne3", tableconsi[2]))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //consigne4
    if (Firebase.RTDB.setInt(&fbdo, "thermolit/consigne4", tableconsi[3]))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //consigne5
    if (Firebase.RTDB.setInt(&fbdo, "thermolit/consigne5", tableconsi[4]))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    sendtoserver=false;
  }
  
  if (Firebase.ready() /*&& signupOK*/ && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
  
    delay(500);
    printLocalTime();

    //Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, "test/int", count))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    count++;

    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "test/float", 0.01 + random(0, 100)))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
      
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }


    // DATE
    const char* databasePath = "thermolit/date";
    int annee;
    sscanf(databasePath, "", &annee);
    printf("", annee);

    // HORAIRE
    const char* dataHourPath = "thermolit/horaire";
    int horaire;
    sscanf(dataHourPath, "", &horaire);
    printf("", horaire);


    // AFFICHER DATE
    //database path thermolit/date
     printLocalTime();
    if (Firebase.RTDB.setString(&fbdo, "thermolit/date", buf))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

     // AFFICHER HORAIRE
    //database path thermolit/horaire
     printLocalTime();
    if (Firebase.RTDB.setString(&fbdo, "thermolit/horaire", buf1))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }


   
   


    }
  }

