/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//   ***Código retirado do Site Laboratório de Garajem e adaptado por: Marcelo | Webestufa //
//   http://www.webestufa.com.br/                                                          //
//                                                                                         //
//     http://labdegaragem.com/                                                            //
//                                                                                         //
//                                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////
#include <DHT.h>
#include <SPI.h>
#include <Ethernet.h> // Biblioteca utilizada para comunicação com o Arduino
#include <LiquidCrystal_I2C.h> //Biblioteca do LCD16x2 com modulo I2C
#include <Wire.h>
#include "RTClib.h" //Módulo do Relógio


#define DHTPIN A0 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

RTC_DS1307 RTC;


// A linha abaixo permite definir o endereço físico (MAC ADDRESS) da placa de rede.
byte mac[] = {
0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

byte ip[] = {
192, 168, 0, 99 }; // Define o endereço IP.

EthernetServer server(80); // Porta onde estará aberta para comunicação Internet e Arduino.

String readString;
/*const byte Rele1 = 9; // Pino digital onde será ligado o rele 1.
const byte Rele2 = 8; // Pino digital onde será ligado o rele 2.
const byte Rele3 = 7; // Pino digital onde será ligado o rele 3.
const byte Rele4 = 6; // Pino digital onde será ligado o rele 4.
const byte Rele5 = 5; // Pino digital onde será ligado o rele 5.
const byte Rele6 = 4; // Pino digital onde será ligado o rele 6.
const byte Rele7 = 3; // Pino digital onde será ligado o rele 7.
const byte Rele8 = 2; // Pino digital onde será ligado o rele 8.*/

void setup(){

  pinMode(53, OUTPUT);

  Wire.begin(); // Inicia el puerto I2C
  RTC.begin(); // Inicia la comunicación con el RTC
  RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
  
  Serial.begin(9600);
  lcd.begin(16,2); // Define o display com 16 colunas e 2 linhas
  delay(2000);

dht.begin();

pinMode(2, OUTPUT); // Define o Pino 2 como saída.
digitalWrite (2, HIGH);
pinMode(3, OUTPUT); // Define o Pino 3 como saída.
digitalWrite (3, HIGH);
pinMode(4, OUTPUT); // Define o Pino 4 como saída.
digitalWrite (4, HIGH);
pinMode(5, OUTPUT); // Define o Pino 5 como saída.
digitalWrite (5, HIGH);
pinMode(6, OUTPUT); // Define o Pino 6 como saída.
digitalWrite (6, HIGH);
pinMode(7, OUTPUT); // Define o Pino 7 como saída.
digitalWrite (7, HIGH);
pinMode(8, OUTPUT); // Define o Pino 8 como saída.
digitalWrite (8, HIGH);
pinMode(9, OUTPUT); // Define o Pino 9 como saída.
digitalWrite (9, HIGH);



Ethernet.begin(mac, ip); // Chama o MAC e o endereço IP da placa Ethernet.
server.begin(); // Inicia o servidor que esta inserido junto a placa Ethernet.
}

void loop(){
  
  DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC


int h = dht.readHumidity(); // Variável para receber a umidade
int t = dht.readTemperature();// Variável para receber a temperatura

EthernetClient client = server.available();
if (client) {
while (client.connected()) {
if (client.available()) {
char c = client.read();

if (readString.length() < 100) {
readString += c;
}

if (c == '\n') {
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println();

//INICIO DO CODIGO HTML

client.println("<HTML>");
client.println("<head><Webestufa</title></head>");
client.println("<BODY>");
client.println("<br><br><center><a href=\"http://www.webestufa.com.br\"> <img align=center width=350px heigh=150px  src=https://lh3.googleusercontent.com/-GGIuiX7uaG4/V5frN70j5cI/AAAAAAAAAh8/h7rBqeX_d_UEqC_EDjHDqFUOU_OcX6sLgCCo/s128/logowebestufa.gif></center></br></br>");
client.println("<H1><center>Arduino + Ethernet Shield + Modulo Rele + DHT11</center></H1>");


//LEITURA DE TEMPERATURA E UMIDADE

client.println("<h2><center>");
client.println("Temperatura:");
client.println(t);
client.println(" *C");
client.println(" - ");
client.println("Umidade:");
client.println(h);
client.println("%");
client.println("</center></h2>");
client.println("<br>");

//CONFIGURAÇÃO DOS RELES

client.println("<H2><center>Rele 1</center></H2>");
client.println("<a href=\"/9/On\"\"><center><button>Liga</button></a>");
client.println("<a href=\"/9/Off\"\"><button>Desliga</button></center></a><br />");

client.println("<H2><center>Rele 2</center></H2>");
client.println("<a href=\"/8/On\"\"><center><button>Liga</button></a>");
client.println("<a href=\"/8/Off\"\"><button>Desliga</button></center></a><br />");

/*client.println("<H2><center>Rele 3</center></H2>"); //----Conforme a necessidade, descomentar as 3 linhas ref ao Rele,  
client.println("<a href=\"/7/On\"\"><center><button>Liga</button></a>");
client.println("<a href=\"/7/Off\"\"><button>Desliga</button></center></a><br />");

client.println("<H2><center>Rele 4</center></H2>");
client.println("<a href=\"/6/On\"\"><center><button>Liga</button></a>");
client.println("<a href=\"/6/Off\"\"><button>Desliga</button></center></a><br />");

client.println("<H2><center>Rele 5</center></H2>");
client.println("<a href=\"/5/On\"\"><center><button>Liga</button></a>");
client.println("<a href=\"/5/Off\"\"><button>Desliga</button></center></a><br />");

client.println("<H2><center>Rele 6</center></H2>");
client.println("<a href=\"/4/On\"\"><center><button>Liga</button></a>");
client.println("<a href=\"/4/Off\"\"><button>Desliga</button></center></a><br />");

client.println("<H2><center>Rele 7</center></H2>");
client.println("<a href=\"/3/On\"\"><center><button>Liga</button></a>");
client.println("<a href=\"/3/Off\"\"><button>Desliga</button></center></a><br />");

client.println("<H2><center>Rele 8</center></H2>");
client.println("<a href=\"/2/On\"\"><center><button>Liga</button></a>");
client.println("<a href=\"/2/Off\"\"><button>Desliga</button></center></a><br />");
*/

client.println("</BODY>");
client.println("</HTML>");

delay(1);
client.stop();

if(readString.indexOf("9/On") > 0)
{
digitalWrite(9, LOW);
}
else {
if(readString.indexOf("9/Off") > 0)
{
digitalWrite(9, HIGH);
}
}

if(readString.indexOf("8/On") > 0)
{
digitalWrite(8, LOW);
}
else {
if(readString.indexOf("8/Off") > 0)
{
digitalWrite(8, HIGH);
}
}

if(readString.indexOf("7/On") > 0)
{
digitalWrite(7, LOW);
}
else {
if(readString.indexOf("7/Off") > 0)
{
digitalWrite(7, HIGH);
}
}

if(readString.indexOf("6/On") > 0)
{
digitalWrite(6, LOW);
}
else {
if(readString.indexOf("6/Off") > 0)
{
digitalWrite(6, HIGH);
}
}

if(readString.indexOf("5/On") > 0)
{
digitalWrite(5, LOW);
}
else {
if(readString.indexOf("5/Off") > 0)
{
digitalWrite(5, HIGH);
}
}

if(readString.indexOf("4/On") > 0)
{
digitalWrite(4, LOW);
}
else {
if(readString.indexOf("4/Off") > 0)
{
digitalWrite(4, HIGH);
}
}

if(readString.indexOf("3/On") > 0)
{
digitalWrite(3, LOW);
}
else {
if(readString.indexOf("3/Off") > 0)
{
digitalWrite(3, HIGH);
}
}
readString="";
}
}
}
}
}

