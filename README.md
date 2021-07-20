### **Raspberry Pi Tasarruflu Ev**

<p>
<img src="./assets/20210720_164401_raspberry_pi_circuit_note_fig2a.jpg" width="60%" height="50%" border: 5px solid #555>
</p>

Bu amaçla bir odada Raspberry Pi (RPi) ile kamera modülü üzerinden yüz tanıma işlemi gerçekleştirilmiştir. Yüz tanıma sonucunda oda da hiç kimse yoksa ve belli bir süre bu durumda ise odanın ışığı lamba, priz modülüne kablosuz olarak gönderilen kapatma bilgisi ile odada bulunan lamba ve diğer çalışan elektronik cihazlar kapatılmaktadır.

Lamba modülü olarakta Arduino Leonardo ile birlikte NRF24L01 kablosuz modül ve röle modülü kullanılmıştır.

<p>
<img src="./assets/lamba_modul.jpg" width="70%" height="70%" border: 5px solid #555>
</p>

Hareket sensöründen veya RPi kamera üzerinden yüz tanıma bilgisi oluştuğunda ise lamba, priz modülüne açma bilgisi kablosuz olarak gönderilmektedir.

Böylece herhangi bir odada hiç kimse yokken o odada bulunan lambalar ve elektronik cihazlar gereksiz yere çalışmamaktadır. Bu durum da ev içersinde veya herhangi bir ofis benzeri ortamda elektrik tasarrufu sağlayacaktır.

Ayrıca bir ev içersinde düğmelere-butonlara gerek kalmadan bütün evdeki lambalar otomatik olarak kendiliğinden açılıp kapanabilecektir. Wifi özelliği olan bir RPi modülü kullanılırsa da evdeki durum web üzerinden izlenebilecek ve sistem ev güvenliği için de kullanılabilecektir.

Burada RPi kamera üzerinden yüz tanıma ve gerekirse web bağlantısı için kullanılmaktadır. Maliyet açısından bu temel özelliklere uygun RPi seçilebilir. Ayrıca RPi ile birlikte programlama kolaylığı açısında Arduino UNO bir NRF24L01 wifi modül ile kullanılmıştır. RPi kablosuz komutları Arduino-NRF modül üzerinden alıp göndermektedir.

RPi de işlemler (Yüz tanıma, USB-seri haberleşme vb.) Python dili ile gerçekleşirilirken Arduino kartlarda C++ dili kullnılmıştır.

### Kullanılan Teknolojiler :

- Raspberry  Pi 3B
- Python programlama dili
- NRF24L01 ve wifi haberleşme.
- Arduino programlama.
- Akıllı evler.
