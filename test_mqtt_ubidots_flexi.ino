/****************************************
 * Include Libraries
 ****************************************/
#include <WiFi.h>
#include <PubSubClient.h>

/****************************************
 * Define Constants
 ****************************************/
#define WIFISSID "Alfamidi" // Put your WifiSSID here
#define PASSWORD "kopat666" // Put your wifi password here
#define TOKEN "A1E-ORUSctDLWufCfBgQHzQw6tHQMTjhak" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "client_1" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 
                                           //it should be a random and unique ascii string and different from all other devices

//#define VARIABLE_LABEL "sensor" // Assing the variable label
#define DEVICE_LABEL "esp32" // Assig the device label

#define VARIABLE_LABEL1 "1" // Assing the variable label
#define VARIABLE_LABEL2 "2"
#define VARIABLE_LABEL3 "3"
#define VARIABLE_LABEL4 "4"

int flexiForcePin1= 2;
int flexiForcePin2= 4;
int flexiForcePin3= 13;
int flexiForcePin4= 14;

char mqttBroker[]  = "things.ubidots.com";
char payload[100];
char topic[150];
// Space to store values to send
char str_sensor[10];
char str_sensor2[10];
char str_sensor3[10];
char str_sensor4[10];

/****************************************
 * Auxiliar Functions
 ****************************************/
WiFiClient ubidots;
PubSubClient client(ubidots);

void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);
  Serial.write(payload, length);
  Serial.println(topic);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    
    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  // Assign the pin as INPUT 
  //pinMode(SENSOR, INPUT);

  Serial.println();
  Serial.print("Wait for WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);  
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL1,str_sensor); // Adds the variable label
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL2, str_sensor2);
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL3, str_sensor3);
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL4, str_sensor4);

  int flexiForceReading = analogRead(flexiForcePin1);
  int flexiForceReading2 = analogRead(flexiForcePin2);
  int flexiForceReading3 = analogRead(flexiForcePin3);
  int flexiForceReading4 = analogRead(flexiForcePin4);
  
  //float sensor = analogRead(SENSOR); 
  //float lat = 6.101;
  // float lng= -1.293;

  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(flexiForceReading, 4, 2, str_sensor);
  dtostrf(flexiForceReading2, 4, 2, str_sensor2);
  dtostrf(flexiForceReading3, 4, 2, str_sensor3);
  dtostrf(flexiForceReading4, 4, 2, str_sensor4);
  //dtostrf(lat, 4, 2, str_lat);
  //dtostrf(lng, 4, 2, str_lng);  
  
  sprintf(payload, "%s {\"value\": %s", payload, str_sensor); // Adds the value
  sprintf(payload, "%s {\"value\": %s", payload, str_sensor2);
  sprintf(payload, "%s {\"value\": %s", payload, str_sensor3);
  sprintf(payload, "%s {\"value\": %s", payload, str_sensor4);
  //sprintf(payload, "%s, \"context\":{\"lat\": %s, \"lng\": %s}", payload, str_lat, str_lng); // Adds coordinates
  sprintf(payload, "%s } }", payload); // Closes the dictionary brackets
  Serial.println("Publishing data to Ubidots Cloud");
  client.publish(topic, payload);
  client.loop();
  delay(1000);
}
