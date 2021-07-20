
#include "nrf24_net_lys.h"

//RF24NetworkHeader header;
payload msg;

RF24NetworkHeader msgToStruct(char *msg)
{
    RF24NetworkHeader header;

    String kimden = splitStr(msg, ",", 1);
    String kime = splitStr(msg, ",", 2);
    String msg_id = splitStr(msg, ",", 3);
    String msg_tip = splitStr(msg, ",", 4);
    String tam_sayi = splitStr(msg, ",", 5);
    String ondalik_sayi = splitStr(msg, ",", 6);
    String tag_ig = splitStr(msg, ",", 7);

    
    header.kimden=kimden.toInt();
    header.kime=kime.toInt();
    header.msg_id=msg_id.toInt();
    header.msg_tip=msg_tip;
    header.tam=tam_sayi.toInt();
    header.ondalik=ondalik_sayi.toInt();
    header.tagID=tag_ig;
    
    Serial.print(kimden);Serial.print("->");
    Serial.print(kime);Serial.print("->");
    Serial.print(msg_id);Serial.print("->");
    Serial.print(msg_tip);Serial.print("->");
    Serial.print(tam_sayi);Serial.print("->");
    Serial.print(ondalik_sayi);Serial.print("->");
    Serial.print(tag_ig);Serial.println("->");

    return header;


}
String structToMsg(RF24NetworkHeader st){
     String m = String(st.kimden)            
                 + ","+                 
                 String(st.kime)         
                 + "," +               
                 String(st.msg_id)                   
                 + "," +                
                 st.msg_tip                   
                 + "," +
                 st.tam                 
                 + "," +
                 st.ondalik                 
                 + "," +               
                 st.tagID ;

      return m;               

}

#define MAX_STRING_LEN 32
char *splitStr(char *input_string, char *separator, int segment_number) //index 1 den ba�l�yor (segment_number)
{
  //String ifadenin sonu her zaman '\0' karakteri olmal�d�r. Serial veri al�m�nda bu karakter string sonuna eklenmez.
  //Bir stringe �evirme i�leminde de eklenmeyebilir. String sonuna eklenmelidir.
  //Split i�leminde string bir daha b�l�necekse sonuna muhakkak '\0' eklenmelidir.

  char *act, *sub, *ptr;
  static char copy[MAX_STRING_LEN];
  int i;

  strcpy(copy, input_string);

  for (i = 1, act = copy; i <= segment_number; i++, act = NULL)
  {

    sub = strtok_r(act, separator, &ptr);
    if (sub == NULL)
      break;
  }
  return sub;
}