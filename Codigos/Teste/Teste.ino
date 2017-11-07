 
#include <SoftwareSerial.h>
 
//RX pino 2, TX pino 3
//SoftwareSerial Serial1(19, 18);
 
#define DEBUG true
  
void setup() {
  // Inicializa ambas as portas
  Serial.begin(9600);
  Serial1.begin(115200);


  sendData("AT+RST\r\n", 2000, DEBUG);


  //------------ inicio
  Serial.println("Versao de firmware");
  sendData("AT+GMR\r\n", 2000, DEBUG); 
  sendData("AT+CIOBAUD=115200\r\n", 2000, DEBUG);


  sendData("AT+CWMODE=1\r\n", 2000, DEBUG);

 /* char login[]={'A','T','+','C','W','S','A','P','=','"','C','A','N','G','U','R','U','_','M','Ã','E','"',',','"','1','2','3','4','5','6','7','8','"',',','3',',','0','\r','\n'};
  
  sendData(login, 2000, DEBUG);
*/

  //char login2[]={'A','T','+','C','W','J','A','P','=','"','t','e','s','t','e','"',',','"','v','i','c','t','o','r','1','2','3','"','\r','\n'};
  //String login2 = "AT+CWJAP=\"teste\",\"victor123\"\r\n";
  //sendData(login2, 2000, DEBUG);

  String cmd1 = "AT+CWJAP=\"Clania\",\"A1B2C3D5E0\"\r\n";
 // sendData(cmd1, 2000, DEBUG);
  
  delay(5000);
  
  sendData("AT+CWLAPOPT=0,6\r\n", 2000, DEBUG);
  sendData("AT+CIPMUX=1\r\n", 2000, DEBUG);



  String cmd = "AT+CIPSTART=0,\"TCP\",\"104.41.45.141\",80\r\n";
  sendData(cmd, 2000, DEBUG);

  cmd ="GET /canguru/index.php?info=hello_from_arduino\r\n";
  String cmd2="AT+CIPSEND=0,";
  cmd2=cmd2+cmd.length()+"\r\n";
  sendData(cmd2, 2000, DEBUG);


  sendData(cmd, 5000, DEBUG);
  cmd ="Host: 104.41.45.141\r\n";
  sendData(cmd, 2000, DEBUG);
  



}
 
void loop() {
  // Ve se tem sinal na Serial1 e manda para a Serial
  /*
  if (Serial1.available()) {
    char inByte = Serial1.read();
    Serial.print(inByte);
  }
 
  // Analogamente, ve se tem sinal na Serial, e manda para Serial1
  if (Serial.available()) {
    char inByte = Serial.read();
    Serial1.write(inByte);
    //Serial1.print("AT\r\n");
  }

  */
   

  //String cmd = "AT+CIPSTART=0,\"TCP\",\"104.41.45.141\",80\r\n";
  //sendData(cmd, 2000, DEBUG); 
 // sendData("AT+CWLAP\r\n", 7000, DEBUG);
  
}



String sendData(String command, const int timeout, boolean debug)
{
  // Envio dos comandos AT para o modulo
  String response = "";
  Serial1.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial1.available())
    {
      // The esp has data so display its output to the serial window
      char c = Serial1.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
