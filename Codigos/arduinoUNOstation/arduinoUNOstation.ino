 
#include <SoftwareSerial.h>


 
//RX pino 2, TX pino 3
SoftwareSerial esp8266(2, 3);
 
#define DEBUG true
 
void setup()
{
  Serial.begin(9600);
  esp8266.begin(115200);
  sendData("AT+RST\r\n", 2000, DEBUG);


  //------------ inicio
  Serial.println("Versao de firmware");
  sendData("AT+GMR\r\n", 2000, DEBUG); 
  sendData("AT+CIOBAUD=74880\r\n", 2000, DEBUG);

  esp8266.begin(74880);

  sendData("AT+CWMODE=3\r\n", 2000, DEBUG);

  //sendData("AT+CWJAP="CANGURU","12345678"\r\n", 2000, DEBUG);

  char login[]={'A','T','+','C','W','S','A','P','=','"','C','A','N','G','U','R','U','_','2','"',',','"','1','2','3','4','5','6','7','8','"',',','3',',','0','\r','\n'};
  
  /*"AT+CWJAP=";
  login=login+'"'+"CANGURU"+'"'+","+'"'+"12345678"+'"';*/
  sendData(login, 2000, DEBUG);

  sendData("AT+CWJAP?\r\n", 2000, DEBUG);

  
  Serial.println("** Final **");
}
 
void loop() {
    if (esp8266.available()) {
    char inByte = esp8266.read();
    Serial.print(inByte);
  }
 
  // Analogamente, ve se tem sinal na Serial, e manda para Serial1
  if (Serial.available()) {
    char inByte = Serial.read();
    esp8266.write(inByte);
    //esp8266.print("AT\r\n");
  }



  //sendData("AT+CWJAP?\r\n", 2000, DEBUG);
  //delay(2000);
  }




 
String sendData(String command, const int timeout, boolean debug)
{
  // Envio dos comandos AT para o modulo
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
