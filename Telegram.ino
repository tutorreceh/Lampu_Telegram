
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define Output_Relay1   D3 // Pin D0 = GPIO16
#define Output_Relay2   D2 // Pin D1 = GPIO5
#define Output_Relay3   D1 // Pin D2 = GPIO4
#define Output_Relay4   D0 // Pin D3 = GPIO0


// Atur SSID Dan Password Wifi Router / Wifi Hotspot / Wifi Tethring Dari HP
char ssid[] = "HOTSPOT GURU 2";     // Masukan Nama SSID (Besar Kecil Pengaruh)
char password[] = "guru=tekindo";       // Masukan Password Yang Di Pakai Router


// Untuk Setting Perintah Pada Telegram Ganti Nama Dalam Tanda Kutip Sesuai Keinginan Anda 
const char* Perintah_On_1 = "/NyalakanLampuRuangTamu";
const char* Perintah_On_2 = "/NyalakanLampuRuangTengah";
const char* Perintah_On_3 = "/NyalakanLampuRuangDapur";
const char* Perintah_On_4 = "/NyalakanLampuKamar";

const char* Perintah_Off_1 = "/MatikanLampuRuangTamu";
const char* Perintah_Off_2 = "/MatikanLampuRuangTengah";
const char* Perintah_Off_3 = "/MatikanLampuRuangDapur";
const char* Perintah_Off_4 = "/MatikanLampuKamar";


const char* Perintah_1 = "/StatusLampuRuangTamu";
const char* Perintah_2 = "/StatusLampuRuangTengah";
const char* Perintah_3 = "/StatusLampuRuangDapur";
const char* Perintah_4 = "/StatusLampuKamar";
const char* Perintah_6 = "/MatikanSemuaSystem";


// Masukan Token Telegram BOT Kalian (JIka Lupa Token Bisa Lihat Pada BotFather Ketikan /token)
#define BOTtoken "1920866519:AAFy26hbc2LT56LJqHCzCXQXFA7nXKCN11E"  // Masukan Token Kalian (Silakan Copy Dari Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int ON = LOW, OFF = HIGH;
int Hidup = HIGH, Mati = LOW;

int Bot_mtbs = 1000; //mean time between Untuk Lamanya Scan Pesan Baru
long Bot_lasttime;   // Pesan Terakhir 
bool Start = false;

int ledStatus1 = OFF;
int ledStatus2 = OFF;
int ledStatus3 = OFF;
int ledStatus4 = OFF;


void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String Pesan = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (Pesan == (Perintah_On_1)) {
      digitalWrite(Output_Relay1, ON);  
      ledStatus1 = Hidup;
      bot.sendMessage(chat_id, "Lampu RuangTamu Sudah Menyala", "");
    }

    else if (Pesan == (Perintah_Off_1)) {
      ledStatus1 = Mati;
      digitalWrite(Output_Relay1, OFF); 
      bot.sendMessage(chat_id, "Lampu RuangTamu Sudah Di Matikan", "");
    }
      else  if (Pesan == (Perintah_On_2)) {
      digitalWrite(Output_Relay2, ON); 
      ledStatus2 = Hidup;
      bot.sendMessage(chat_id, "Lampu RuangTengah Sudah Di Nyalakan", "");
    }

   else if (Pesan == (Perintah_Off_2)) {
      ledStatus2 = Mati;
      digitalWrite(Output_Relay2, OFF);   
      bot.sendMessage(chat_id, "Lampu RuangTengah Berhasil Di Matikan", "");
    }
   else if (Pesan == (Perintah_On_3)) {
      digitalWrite(Output_Relay3, ON);  
      ledStatus3 = Hidup;
      bot.sendMessage(chat_id, "Lampu RuangDapur Rumah Berhasil Di Hidupkan", "");
    }

   else if (Pesan == (Perintah_Off_3)) {
      ledStatus3 = Mati;
      digitalWrite(Output_Relay3, OFF); 
      bot.sendMessage(chat_id, "Lampu RuangDapur Rumah Telah Di Matikan", "");
    }
   else if (Pesan == (Perintah_On_4)) {
      digitalWrite(Output_Relay4, ON);
      ledStatus4 = Hidup;
      bot.sendMessage(chat_id, "Lampu Kamar Rumah Telah Di Hidupkan", "");
    }

   else if (Pesan == (Perintah_Off_4)) {
      ledStatus4 = Mati;
      digitalWrite(Output_Relay4, OFF);  
      bot.sendMessage(chat_id, "Lampu Kamar Rumah Telah Di Matikan", "");
    }
    
   else if (Pesan == (Perintah_1)) {
        if(ledStatus1){
        bot.sendMessage(chat_id, "Lampu RuangTamu Saat Ini Sudah Menyala", "");
      } else {
        bot.sendMessage(chat_id, "Lampu RuangTamu Dalam Keadaan Mati", "");
      }
      }
        else if (Pesan == (Perintah_2)) {
        if(ledStatus2){
        bot.sendMessage(chat_id, "Lampu PJU Dalam Keadaan Aktif", "");
      } else {
        bot.sendMessage(chat_id, "Lampu PJU Saat Ini Mati", "");
      }
        }
        else if (Pesan == (Perintah_3)) {
        if(ledStatus3){
        bot.sendMessage(chat_id, "Lampu RuangDapur Rumah Dalam Keadaan Menyala", "");
      } else {
        bot.sendMessage(chat_id, "Lampu RuangDapur Rumah Saat Ini Dalam Keadaan Mati", "");
      }
      }
        else if (Pesan == (Perintah_4)) {
        if(ledStatus4){
        bot.sendMessage(chat_id, "Lampu Kamar Rumah Telah Di Hidupkan", "");
      } else {
        bot.sendMessage(chat_id, "Lampu Kamar Rumah Saat ini Dalam Keadaan Mati", "");
      }
      }
        else if (Pesan == (Perintah_6)) {
          ledStatus1 = OFF;
          ledStatus2 = OFF;
          ledStatus3 = OFF;
          ledStatus4 = OFF;

          digitalWrite(Output_Relay1, OFF);
          digitalWrite(Output_Relay2, OFF);
          digitalWrite(Output_Relay3, OFF);
          digitalWrite(Output_Relay4, OFF);
         bot.sendMessage(chat_id, "Semua Relay Sudah Mati, Sekarang Aman", "");
        }

    else if (Pesan == "/start") {
      String welcome = "Selamat Datang Di IOT , " + from_name + ".\n";
      welcome += "Pengontrolan Lampu Rumah Melalui Telegram\n";
      welcome += "Gunakan Kode Berikut Untuk Mengontrol Relay :\n\n";
      welcome += "# ON/OFF Lampu RuangTamu Depan Rumah:\n";
      welcome += (Perintah_On_1);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_1);
      welcome += " <- Tekan OFF\n\n";
      
      welcome += "# ON/OFF Lampu RuangTengah:\n";
      welcome += (Perintah_On_2);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_2);
      welcome += " <- Tekan OFF\n\n";
      
      welcome += "# ON/OFF Lampu RuangDapur Rumah:\n";
      welcome += (Perintah_On_3);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_3);
      welcome += " <- Tekan OFF\n\n";
      
      welcome += "# ON/OFF Kamar:\n";
      welcome += (Perintah_On_4);
      welcome += " <- Tekan ON\n";
      welcome += (Perintah_Off_4);
      welcome += " <- Tekan OFF\n\n";
      
      welcome += "# Chek Status Output Realtime:\n";
      welcome += (Perintah_1);
      welcome += " - Lampu RuangTamu\n";
      welcome += (Perintah_2);
      welcome += " - Lampu RuangTengah\n";
      welcome += (Perintah_3);
      welcome += " - Lampu RuangDapur\n";
      welcome += (Perintah_4);
      welcome += " - Kamar\n";

          
      welcome += "# Untuk Mematikan Semua Relay:\n";
      welcome += (Perintah_6);
      welcome += " - Emergency OFF \n\n\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}


void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  client.setInsecure();               // FIX NODEMCU Wajib Board esp8266 version 2.5.0

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.longPoll = 60;   // Panjang Polling

  pinMode(Output_Relay1, OUTPUT); 
  pinMode(Output_Relay2, OUTPUT);
  pinMode(Output_Relay3, OUTPUT);
  pinMode(Output_Relay4, OUTPUT);

  delay(10);
  digitalWrite(Output_Relay1, OFF);
  digitalWrite(Output_Relay2, OFF);
  digitalWrite(Output_Relay3, OFF);
  digitalWrite(Output_Relay4, OFF);

  
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      Serial.println(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}
