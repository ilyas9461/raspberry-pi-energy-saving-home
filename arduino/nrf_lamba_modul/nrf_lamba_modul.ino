//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "nrf24_net_lys.h"

#define LAMBA_PIN 6

// sck  : 13
// miso : 12
// mosi : 11
// ss :   10

RF24 radio(9, 8); // CE, CSN

//adresler vericiler tarafından bakılarak düzenlendi.
const byte address_r[5] = "lys-r"; //  master yazdığı, vericilerin dinlediği adres...
const byte address_w[5] = "lys-w"; //  vericilerin yazdığı, master dinlediği, adres..

const int this_id = 19;
const uint16_t master_node = 0; //Master
char buf_rf24_rcv[32] = {0};
String str = "";
String sonMsg = "";
int say = 1;
char ser_rx = 0;
bool oyun_baslat = false;
bool led_13 = false;
long time_lamba = 0;
void setup()
{
  Serial.begin(9600);
  //while(!Serial);
  pinMode(13, OUTPUT);
  pinMode(LAMBA_PIN, OUTPUT);

  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(110);
  radio.setRetries(15, 15);
  //radio.setPALevel(RF24_PA_MAX);  //modüller yakın iken veri alma konusunda sorun oluştu antensiz modülde
  radio.setPALevel(RF24_PA_HIGH);
  //set the address
  radio.openReadingPipe(0, address_r); //RPi ardu yazdığı adres
  radio.openWritingPipe(address_w);   //Rpi ardu dinlediği adres
  //  radio.printDetails();
  //Set module as receiver
  radio.startListening();
  //radio.stopListening();
  Serial.println("basla..");
  digitalWrite(LAMBA_PIN, HIGH);
  delay(1000);
  digitalWrite(LAMBA_PIN, LOW);
  time_lamba = millis();
}
void loop()
{
  if (radio.available())
  {
    radio.read(&buf_rf24_rcv, sizeof(buf_rf24_rcv));
    //Serial.println(String(buf_rf24_rcv));

    //if (sonMsg != buf_rf24_rcv) 
    {
      RF24NetworkHeader mesaj = msgToStruct(buf_rf24_rcv);

      //Serial.println(String(buf_rf24_rcv));

      Serial.println(mesaj.msg_tip);
      if (mesaj.kime == this_id && mesaj.msg_tip == String(NRF_LAMBA_YAK))
      {
        digitalWrite(LAMBA_PIN, HIGH);
        delay(500);
        mesaj_gonder(NRF_ACK, mesaj.kimden);
      }

      if (mesaj.kime == this_id && mesaj.msg_tip == String(NRF_LAMBA_SONDUR)) {
        digitalWrite(LAMBA_PIN, LOW);
        delay(500);
        mesaj_gonder(NRF_ACK, mesaj.kimden);

      }
    }

    sonMsg = String(buf_rf24_rcv);
  }

  //  if(millis()-time_lamba>3000){
  //    digitalWrite(LAMBA_PIN,LOW);
  //    time_lamba=millis();
  //  }

  if (Serial.available())
  {
    ser_rx = Serial.read();
    if (ser_rx == 'b' || ser_rx == 'B')
    {
    }
  }
}

void mesaj_gonder(char tip, uint8_t kime) {
  radio.stopListening();

  RF24NetworkHeader msg;

  msg.kimden = this_id;
  msg.kime = kime;
  msg.msg_id = say++;
  msg.msg_tip = tip;
  msg.tam = say++;
  msg.ondalik = 0;
  msg.tagID = "1111111111";

  String msg_gon = structToMsg(msg);

  msg_gon.toCharArray(buf_rf24_rcv, sizeof(buf_rf24_rcv));

  for (int x = 0; x < 2; x++)
  {
    radio.write(buf_rf24_rcv, sizeof(buf_rf24_rcv));
  }

  Serial.println(String(buf_rf24_rcv));

  radio.startListening();
  if (say > 7) say = 1;
}

boolean runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}
//**************
