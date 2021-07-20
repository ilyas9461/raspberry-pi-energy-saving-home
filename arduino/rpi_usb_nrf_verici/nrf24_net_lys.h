
#include <Arduino.h>

struct RF24NetworkHeader
{
  uint16_t kimden;
  uint16_t kime;
  uint16_t msg_id;
  String  msg_tip;
  uint16_t tam;
  uint16_t ondalik;
  String tagID;
  //String renk;
};

struct payload
{
  byte tagID[5];
  uint16_t tam;
  uint16_t ondalik;
  char tip;
};

//nrf kablosuz komut tanımları  
#define NRF_ACK 'A'                     
#define NRF_LAMBA_YAK 'Y'
#define NRF_LAMBA_SONDUR 'S'
#define LAMBA_MODUL 19

//Fonksiyon protipleri
RF24NetworkHeader msgToStruct(char *msg);
char *splitStr(char *input_string, char *separator, int segment_number);
String structToMsg(RF24NetworkHeader st);
