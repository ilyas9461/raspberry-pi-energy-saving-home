//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "nrf24_net_lys.h"


// Tasarrfulu ev projesinde master RPi ye bağlı olan Ardu Uno

// sck  : 13
// miso : 12
// mosi : 11
// ss :   10

RF24 radio(9, 8); // CE, CSN

//adresler vericiler tarafından bakılarak düzenlendi.
const byte address_r[5] = "lys-r"; //  master yazdığı, vericilerin dinlediği adres...
const byte address_w[5] = "lys-w"; //  vericilerin yazdığı, master dinlediği, adres..

const uint8_t this_node = 32;
const uint8_t master_node = 0; //Master
char buf_rf24_rcv[32] = {0};
String str = "";
String sonMsg = "";
int say = 1;
char ser_rx = 0;

bool led_13 = false;

void setup()
{
  Serial.begin(9600);
  //while(!Serial);
  pinMode(13, OUTPUT);

  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(110);
  radio.setRetries(15, 15);
  //radio.setPALevel(RF24_PA_MAX);  //modüller yakın iken veri alma konusunda sorun oluştu antensiz modülde
  radio.setPALevel(RF24_PA_LOW);
  //set the address
  radio.openReadingPipe(0, address_w); //verici panoların gönderdiği mesajları almak için
  radio.openWritingPipe(address_r);   //vericilere mesaj göndermek için
  //  radio.printDetails();

  radio.startListening();
  //radio.stopListening();
  Serial.println("basla..");
}
void loop()
{
   if (Serial.available())
  {
    String ser_rx =Serial.readStringUntil('\n');
    
    if (ser_rx == "YAK" || ser_rx == "yak")
    {
      mesaj_gonder(NRF_LAMBA_YAK ,LAMBA_MODUL);
    }
    if (ser_rx == "SONDUR" || ser_rx == "sondur")
    {
      mesaj_gonder(NRF_LAMBA_SONDUR ,LAMBA_MODUL);
    }
  }
  
  if (radio.available())
  {
    radio.read(&buf_rf24_rcv, sizeof(buf_rf24_rcv));
    //Serial.println(String(buf_rf24_rcv));
    if (sonMsg != buf_rf24_rcv) {
      
      RF24NetworkHeader mesaj = msgToStruct(buf_rf24_rcv);

      Serial.println(String(buf_rf24_rcv));

      if (mesaj.msg_tip == String(NRF_ACK) )// Lamba yakıldı doğrulama mesajı
      {
          Serial.println("ACK");  //doğrulama mesajını Rpi gönder
      }
      if (mesaj.msg_tip == "S") {
       
      }
    }
    sonMsg = buf_rf24_rcv;
  }
  
 
}

void mesaj_gonder(char tip,uint8_t kime) {
  radio.stopListening();

  RF24NetworkHeader msg;

  msg.kimden = this_node;
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

//ornek kullanım :
 // if (runEvery(2000)) {
//    //mesaj_gonder();
//  }
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
