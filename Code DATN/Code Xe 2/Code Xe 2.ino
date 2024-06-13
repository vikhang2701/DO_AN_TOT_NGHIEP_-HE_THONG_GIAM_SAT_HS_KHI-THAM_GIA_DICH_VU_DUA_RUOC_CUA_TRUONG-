//thư viện hình ảnh
#include "GPS_LOST.h"
#include "GPS_OK.h"
#include "truong.h" //hình nền đầu tiên
#include "HCMUTE2.h" //hình logo_trường
#include "tin.h"
#include "khang.h"
#include "nguyen.h"
#include "theanh.h"
#include "caominh.h"
#include "ngoctuong.h"
#include "tanloc.h"
#include "hungkiet.h"
#include "ngochai.h"
#include "ngocan.h"
#include "hanh.h"
#include "dinhhai.h"
#include "xeduaruoc.h" //hình màn hình hệ thống đã sẵn sàng
#include "warning.h"
#include "call_sos.h"
#include "tin_mother.h"
#include "logo_ute1.h"
#include "logo_ddt.h"
#include "all_father.h"
#include "goitaixe.h"
#include "pin_25.h"
#include "pin_50.h"
#include "pin_75.h"
#include "pin_100.h"
#include "xac.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <TFT_eSPI.h> 
TFT_eSPI tft = TFT_eSPI();
#include <MFRC522.h>  
#include<String.h>
#include <Wire.h>
#include "FirebaseESP32.h"
#define WIFI_SSID "Vĩ Khang" //OPPO Reno8 T
#define WIFI_PASSWORD "20161208@Hi" //a2wngyct
#define FIREBASE_HOST "doan2-38f4f-default-rtdb.firebaseio.com"  //doan2-38f4f-default-rtdb.firebaseio.com //doan2-6b2e3-default-rtdb.firebaseio.com
#define FIREBASE_AUTH "shVMs5GpDSanPw9Qz7PHqDOUcFLMcfxb62QIx0sf" //shVMs5GpDSanPw9Qz7PHqDOUcFLMcfxb62QIx0sf //6k3TFIg3ziGTC199U50UdZkvuA8zWmyWf0e9UUWH

FirebaseData firebaseData;
FirebaseJson json;
String path = "/"; 
#define RST_PIN         27
#define SS_PIN          5
#define MIN_USB_VOL 4.21
MFRC522 mfrc522(SS_PIN, RST_PIN);
SoftwareSerial mySerial(17,16); // These pins are connected to GSM module( TX, RX )

int RXPin = 4;
int TXPin = 2;
TinyGPSPlus gps;
SoftwareSerial neo6m(RXPin, TXPin);
String timeStr;
String dateStr;

bool nut = false;
int buttonPressCount = 0;
int buzzer = 12;
int buttonPin = 13;
int buttonMode = 25;
const int bt_ac =4; 
const int bt_rj = 0; 


String number_taixe= "0911417094";  //0987045339
String number_ph= "0987045339";  //0987045339 //0325146918
String h;
String SMS_Warning = "CANH BAO, CO HOC SINH DANG KET TRONG XE";
String SMS_Success1 = "BE TRAN TRUNG TIN DA TOI TRUONG";
String SMS_Success2 = "BE PHAM HOANG VI KHANG DA TOI TRUONG";
String SMS_Success3 = "BE VO PHAN TRI NGUYEN DA TOI TRUONG";
String SMS_Success4 = "BE PHAM NGUYEN THE ANH DA TOI TRUONG";
String SMS_Success5 = "BE VU CAO MINH DA TOI TRUONG";
String SMS_Success6 = "BE DOAN NGOC TUONG DA TOI TRUONG";
String SMS_Success7 = "BE NGUYEN TAN LOC DA TOI TRUONG";
String SMS_Success8 = "BE NGUYEN PHI HUNG KIET DA TOI TRUONG";
String SMS_Success9 = "BE TON THAT NGOC HAI DA TOI TRUONG ";
String SMS_Success10 = "BE DO NGOC AN DA TOI TRUONG";

String SMS_Success1n= "BE TRAN TRUNG TIN DA VE NHA";
String SMS_Success2n = "BE PHAM HOANG VI KHANG DA VE NHA";
String SMS_Success3n = "BE VO PHAN TRI NGUYEN DA VE NHA";
String SMS_Success4n = "BE PHAM NGUYEN THE ANH DA VE NHA";
String SMS_Success5n = "BE VU CAO MINH DA VE NHA";
String SMS_Success6n = "BE DOAN NGOC TUONG DA VE NHA";
String SMS_Success7n = "BE NGUYEN TAN LOC DA VE NHA";
String SMS_Success8n = "BE NGUYEN PHI HUNG KIET DA VE NHA";
String SMS_Success9n = "BE TON THAT NGOC HAI DA VE NHA ";
String SMS_Success10n = "BE DO NGOC AN DA VE NHA";
String action= "WT"; //String codes: RC =Receive call, RM= Receive msg, SC= Send calll, SM= Send message, WT= Wait

String SOS ="";
// Receive sms Strings
String Response ="";
String sms="";
String Type;
String Caller_id;
String Text;
String SP_name="";
char character;
char quote= 0x22;
 
// Global Flags
bool Send_m=false;
bool sms_Receive_mode_off=true;
bool Receive_mode=false;
bool msg_Receive=false;
bool time_registered=false;
bool msg_fetched=false;
bool on_call=false;
bool start_Receive=false;
bool flag=true;
bool flag_gps=true;
 
int sec,minutes; // Clock variables
long c_start;
long c_time;
 
 
int indexOfQuotes[10];
 
double time_start;
double time_current;
double operational_time;
char value;

int analogInPin = 36;    // Analog input pin
int numberOfReadings = 10; // Số lần đọc cho bộ lọc trung bình
int number_vol = 10; // Số lần đọc cho bộ lọc trung bình
float calibration = 0.82; // Check Battery voltage using multimeter & add/subtract the value
bool suddenIncrease = false; 

float total = 0; // Tổng các giá trị đọc analog
float voltage; 
int bat_percentage;

float voltageSum = 0;
float previousVoltage = 0; // Giá trị voltage trước đó
int validReadings = 0; // Số lượng giá trị đọc hợp lệ

//-------------------------------------------------------
int UID[4], i;
const int ID1[4] = {66, 9, 127, 76}; //Tín            //195 240 236 26 //66, 9, 127, 76
const int ID2[4] = {243, 93, 249, 149}; //Khang
const int ID3[4] = {42, 128, 103, 26}; //Nguyên
const int ID4[4] = {100, 55, 175, 36}; //Thế Anh
const int ID5[4] = {52, 209, 204, 114}; //Cao Minh
const int ID6[4] = {83, 203, 198, 237}; //Tường
const int ID7[4] = {131, 237, 174, 237}; //Lộc
const int ID8[4] = {179, 151, 195, 237}; //Kiệt
const int ID9[4] = {35, 184, 200, 237}; //Ngọc Hải
const int ID10[4] = {163, 150, 193, 237}; //Ngọc An

const int ID_tx1[4] = {227, 145, 15, 150}; //Hạnh
const int ID_tx2[4] = {121, 43, 219, 59}; //Đình Hải


int solanquettaixe1 = 0; //Hạnh
int solanquettaixe2 = 0; //Đình Hải


int dem1 = 0; //tin
int dem2 = 0; //khang
int dem3 = 0; //nguyen
int dem4 = 0; // the anh
int dem5 = 0; //cao minh
int dem6 = 0; //tuong
int dem7 = 0; //loc
int dem8 = 0; // kiet
int dem9 = 0; //ngoc hai
int dem10 = 0; //ngoc an
int demtx1 = 0; //hanh                   
int demtx2 = 0; //dinh hai

int tam1;
int tam2;
int tam3;
int tam4;
int tam5;
int tam6;
int tam7; 
int tam8;
int tam9;
int tam10;
int tamtx1;
int tamtx2;

int previousTam1 = -1; 
int previousTam2 = -1; 
int previousTam3 = -1; 
int previousTam4 = -1; 
int previousTam5 = -1;
int previousTam6 = -1; 
int previousTam7 = -1; 
int previousTam8 = -1; 
int previousTam9 = -1; 
int previousTam10 = -1;
int previousTamtx1 = -1; 
int previousTamtx2 = -1;  

void setup()
{ 
Serial.begin(9600);
SPI.begin();
tft.init();
tft.setRotation(3); //xác định góc quay màn hình 270 độ
mfrc522.PCD_Init();
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
Serial.begin(9600);
neo6m.begin(9600);
delay(1000);
pinMode(buttonPin, INPUT);
pinMode(buttonMode, INPUT);
h="no";
pinMode(bt_ac, INPUT);
pinMode(bt_rj, INPUT);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  while (WiFi.status() != WL_CONNECTED) { 
  delay(500);
  Serial.print(".");  
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true); 
  if (!Firebase.beginStream(firebaseData, path)) 
  {
     Serial.println("REASON: " + firebaseData.errorReason()); 
     Serial.println();
  }
  Serial.print("Connected with IP: "); 
  Serial.println(WiFi.localIP());
  Serial.println();   
  Serial.println("Firebase OK.");
  tft.fillScreen(TFT_BLACK); //chỉnh nền màu
  tft.setSwapBytes(true);
  tft.pushImage(0, 0, 480, 320, truong);   
  tft.pushImage(211, 12, 58, 58,HCMUTE2);
  tft.drawRect(0,80,480,30,TFT_WHITE);
  tft.fillRect(0,80,480,30,TFT_WHITE);
  
  tft.drawRect(0,120,480,53,TFT_WHITE);
  tft.fillRect(0,120,480,53,TFT_WHITE);
  
  tft.setCursor(150,89);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.println("DO AN TOT NGHIEP");  
  
  tft.setCursor(63,127);
  tft.setTextColor(TFT_RED);
  tft.setTextSize(2);
  tft.println("HE THONG GIAM SAT HOC SINH KHI");  
  
  tft.setCursor(25,152);
  tft.setTextColor(TFT_RED);
  tft.setTextSize(2);
  tft.printf("THAM GIA DICH VU DUA RUOC CUA TRUONG");

  tft.drawRect(0,182,480,130,TFT_WHITE);
  tft.fillRect(0,182,480,130,TFT_WHITE);
  tft.setCursor(120,189);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.printf("GIANG VIEN HUONG DAN");

  tft.setCursor(108,214);
  tft.setTextColor(TFT_RED);
  tft.setTextSize(2);
  tft.printf("TS. NGUYEN THANH NGHIA");

  tft.setCursor(125,239);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.printf("SINH VIEN THUC HIEN");
  
  tft.setCursor(102,264);
  tft.setTextColor(TFT_RED);
  tft.setTextSize(2);
  tft.printf("TRAN TRUNG TIN 20161270");

  tft.setCursor(70,289);
  tft.setTextColor(TFT_RED);
  tft.setTextSize(2);
  tft.printf("PHAM HOANG VI KHANG 20161208");  
  
  delay(2000);
  Serial.println("GSM startrd");
  mySerial.begin(9600);
  mySerial.setTimeout(2000);
  Serial.setTimeout(2000);
  get_SP();
  mySerial.print ("AT+CSMP=17,167,0,0\r");
  readySystem();
}

void readySystem(){
  tft.fillScreen(TFT_WHITE); //chỉnh nền màu    
  tft.pushImage(120, 131, 250, 177, xeduaruoc);  
  tft.pushImage(0, 0, 50, 50, logo_ute1);  
  tft.pushImage(419, 0, 61, 50, logo_ddt);
  tft.drawRoundRect(160,120,160, 35, 5, TFT_RED);  
  for(int i=0;i<150;i+=10){
  tft.fillRoundRect(165,130,10+i, 15,5, TFT_BLACK);
  tft.setCursor(170,80);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.printf("DANG TAI..."); 
  delay(100);    
  }
  tft.fillRect(170,80, 200, 30, TFT_WHITE);  
  tft.setCursor(120,80);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.printf("HE THONG DA SAN SANG");  
}

void kiemtra_sos()
{
  if(buttonPressCount == 3)
  {
    action = "SC";
  }  
}

void loop()
{
//Serial.println("Action: "+ action); //Reports it current mode of working
while(action=="WT") // Its wait for SMS and Calls in this loop
{
if(sms_Receive_mode_off) //So, This turns on the SMS recieve mode
{ delay(10);
On_sms_Receive_mode();
}
 
if(flag)
{
Serial.println("Receive_ready");
flag=false;
clear_Serial();
}
 
 
if(Receiving_on()) // FINALLY, the module is set to receive, Receive_on will beocome true in case msg or call arrives
{
Extract_type();
delay(10);
action="WT";
}
 
else
{ 
event(); // Or, check if user pressed any button for callling or SMS
if(flag_gps)
  {
  get_location();
  delay(0.01);
  GPS_Time1();
  delay(0.01);
  pin();
  delay(0.01);
  event();
  delay(0.01);  
  checkhs1();
  delay(0.01);
  checkhs2();
  delay(0.01);
  checkhs3();
  delay(0.01);
  checkhs4();
  delay(0.01);
  checkhs5();
  delay(0.01);
  checkhs6();
  delay(0.01);
  checkhs7();
  delay(0.01);
  checkhs8();
  delay(0.01);
  checkhs9();
  delay(0.01);
  checkhs10();
  delay(0.01);
  checktx1();
  delay(0.01);
  checktx2();
  delay(0.01);
  get_location();
  }
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  { 
    return; 
  }  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {  
    return;  
  }  
  Serial.print("UID của thẻ: ");     
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  { 
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");       
    UID[i] = mfrc522.uid.uidByte[i];    
    Serial.print(UID[i]); 
  }  
  Serial.println("   ");

if (nut){ 
  if (UID[i] == ID1[i])
  {   buttonPressCount = 3;
      SOS = "A";
      hocSinh1_Sos();
      action = "SC";
      nut = !nut;
  }
  else if (UID[i] == ID2[i])
  { 
      buttonPressCount = 3;
      SOS = "B";
      hocSinh2_Sos();
      action = "SC";
      nut = !nut;
  }
  else if (UID[i] == ID3[i])
  {   buttonPressCount = 3;
      SOS = "C";
      hocSinh3_Sos();
      action = "SC";
      nut = !nut;
  }
  else if (UID[i] == ID4[i])
  {   buttonPressCount = 3;
      SOS = "D";
      hocSinh4_Sos();
      action = "SC";
      nut = !nut;
  }
  else if (UID[i] == ID5[i])
  {   buttonPressCount = 3;
      SOS = "E";
      hocSinh5_Sos();
      action = "SC";
      nut = !nut;
  }
  else if (UID[i] == ID6[i])
  {   buttonPressCount = 3;
      SOS = "F";
      hocSinh6_Sos();
      action = "SC";
      nut = !nut;
  }
  else if (UID[i] == ID7[i])
  {   buttonPressCount = 3;
      SOS = "G";
      hocSinh7_Sos();
      action = "SC";
      nut = !nut;
  }
  else if (UID[i] == ID8[i])
  {   buttonPressCount = 3;
      SOS = "H";
      hocSinh8_Sos();
      action = "SC";
      nut = !nut;
  }
  else if (UID[i] == ID9[i])
  {   buttonPressCount = 3;
      SOS = "I";
      hocSinh9_Sos();
      action = "SC";
      nut = !nut;
  }
  else if (UID[i] == ID10[i])
  {   buttonPressCount = 3;
      SOS = "J";
      hocSinh10_Sos();
      action = "SC";
      nut = !nut;
  }
  else
  {
      maTheSai();
      nut = !nut;
  }
}
else{
  if (UID[i] == ID1[i])
  {
      hocSinh1();
  }
  else if (UID[i] == ID2[i])
  {
      hocSinh2();
  }
  else if (UID[i] == ID3[i])
  {
      hocSinh3();
  }
  else if (UID[i] == ID4[i])
  {
      hocSinh4();
  }
  else if (UID[i] == ID5[i])
  {
      hocSinh5();
  }
  else if (UID[i] == ID6[i])
  {
      hocSinh6();
  }
  else if (UID[i] == ID7[i])
  {
      hocSinh7();
  }
  else if (UID[i] == ID8[i])
  {
      hocSinh8();
  }
  else if (UID[i] == ID9[i])
  {
      hocSinh9();
  }
  else if (UID[i] == ID10[i])
  {
      hocSinh10();
  }
  else if (UID[i] == ID_tx1[i])
  {
      taiXe1();
  }
  else if (UID[i] == ID_tx2[i])
  {
      taiXe2();
  }
  else
  {
      maTheSai();
  }  
  } 
  mfrc522.PICC_HaltA();  
  mfrc522.PCD_StopCrypto1();
  
}
}
 
while(action=="SC") //Sending call action, similar process as above
{
Serial.println("Enter number to call");
delay(1000);
if (buttonPressCount <=2)
{send_call(number_taixe);}
else {send_call(number_ph);}

delay(1000);
if(on_call)
{terminate_call();} // Waits here till the user is on call

action="WT";
flag=true;
}
 

}
  
void get_SP (void)
{ 
  bool got_it=false;
delay(1000);
mySerial.println("AT");
delay(500);
while(!( SP_name.indexOf('"')>0))
{ if(GSM_operational())
{
mySerial.println("AT+COPS?"); //AT command for getting serivce provider name
mySerial.println();
}
 
delay(500);
 
while(mySerial.available())
{
char character=mySerial.read();
SP_name.concat(character);
}
 
}
// Extracton process
SP_name= (SP_name.substring(SP_name.indexOf('"')+1,SP_name.lastIndexOf('"')));
Serial.println("Connected to: "+ SP_name);
 
}
 
// Fuciton to print current signal strength on lcd
 
void update_signal_strength (void)
{ String Network;
long Strength;
mySerial.println("AT+CSQ");
mySerial.println();
 
delay(500);
while(mySerial.available())
{
char character=mySerial.read();
Network.concat(character);
}
 
Network=Network.substring(Network.indexOf(':')+2,Network.indexOf(','));
Strength= Network.toInt(); // Strength Int value here
 
Strength=(Strength*100/31); // MAX strength= 31
}
  
// Select the apt mode as per the input
void event() 
{
    if ((digitalRead(buttonPin) == LOW)) {
      if(h=="hanh"|| h=="dinhhai")
      {
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      flag_gps=false;
      buttonPressCount++;
      if (buttonPressCount ==1){
         goi_lan_1();
         action = "SC";
      }
      else if(buttonPressCount ==2 &&!nut){
        goi_lan_2();
        action = "SC"; // Send call
        nut = !nut;
      }
    } else if ((digitalRead(bt_ac) == LOW)) {
       // action = "RC"; // Send Message
    } else if ((digitalRead(bt_rj) == LOW)) {
        //action = "RC"; // Receive Call
    } else {
        action = "WT"; // Wait for response
    }}
}
 
bool send_call (String number)
{
 
mySerial.println("AT");
delay(500);
 
if(GSM_operational())
{
Serial.println("Calling to :" +number);
mySerial.println("ATD"+ number +";"); // AT command for dialing up the number
mySerial.println();
on_call=true;
return(true);
}
return(false);
}
 
// This is to switch on the messaging mode of Gsm
void On_sms_Receive_mode (void)
{
mySerial.print("ATE0");
delay(500);
 
if(GSM_operational())
mySerial.print("AT");
delay(500);
 
if(GSM_operational())
mySerial.print("AT+CMGF=1"); // Setup in msging mode
delay(500);
 
if (GSM_operational())
{
mySerial.print("AT+CNMI=2,2,0,0,0\r" ); //Prints the msg on serial as soon as it arrives
delay(500);
 
while(mySerial.available())
{
char response = mySerial.read();
Serial.println(response);
}
 
Serial.println("Receive mode On");
sms_Receive_mode_off=false; //turn it on off
}
}
 
bool Receiving_on (void)
{
bool Response_available=false;
 
if(mySerial.available())
{
while(!halt_fetch()) //In case of incoming recieve until halt_fetch() gives true
{
while(mySerial.available())
{
if(!time_registered) //Capture the time of start of message receiving
{
time_start=millis();
time_registered=true;
}
char character=mySerial.read();
Response.concat(character);
Serial.print(character); // Store as a string
}
 
}
 
Serial.println("Response Received"); //Looks like we got something
Response_available=true;
msg_fetched=false;
flag=true;
}
return (Response_available);
}
 
bool halt_fetch (void)
{
bool halt=false;
 
if(time_registered)
{
time_current=millis();
operational_time=time_current-time_start;
}
 
if(operational_time>3000 || Response.length()==200 ) // Halt condition
{
halt=true;
operational_time=0;
}
return halt;
}
 
 
void Extract_type (void)
{
if(valid_input())
{
Serial.println("Valid respone");
extract();
 
 
Serial.println(Response); //In case u want to see everything incoming
Serial.println("Type: ");
Serial.print(Type);
Serial.println("Caller id : ");
Serial.println(Caller_id);
Serial.println("Text: ");
Serial.println(Text);
callORsms();
Serial.print(Caller_id);
}
 
time_registered=false;
 
Response=""; //Clear string for refresh incoming
 
}
 
bool valid_input (void)
{
bool validity;
 
validity=(( Response.indexOf('+') > 0) && (Response.indexOf('"')>0 )); //If the reponse has these two thing that means it is a 'real' response
 
if(!validity)
{
Serial.println("invalid input");
 
}
 
return (validity);
 
}
 
// Find the indexes of all the quotes in the stirng and sets them up in gloablevariable: indexOfQuotes[index]
void extract(void)
{
int Length,i,index=0;
 
Length=Response.length();
for(i=0;i<=Length;i++)
{
if(Response.charAt(i)==quote)
{
indexOfQuotes[index]=i;
index++;
}
}
 
Type=Response.substring(1,indexOfQuotes[0]);
Caller_id=Response.substring(indexOfQuotes[0]+1,indexOfQuotes[1]);
Text=Response.substring(indexOfQuotes[5]+3);
Serial.println("Extracted");
}
 
// Determine weather the response is of call or sms
void callORsms (void)
{
if( Type.indexOf("LIP")>0) //Call string consist this( +CLIP)
{ action="RC";
Serial.println("Call from: ");}
else if(Type.indexOf("MT")>0 ) // Msg stirng consist (+CMT)
{ action="RM";
Serial.println("Message from: ");}
}
 
// Waits till customer press * or #
void WaitForPickup (void)
{
bool user_wait = true; //default state
while(user_wait)
{ user_wait=check_termination();
 
if (digitalRead(bt_ac) == LOW) //picking up reponse
{
mySerial.println("ATA");
mySerial.println();
Serial.println("Call picked up");
delay(1000);
user_wait=false;
on_call=true;
}
 
if (digitalRead(bt_rj) == LOW) //Termination action
{
mySerial.println("ATH");
mySerial.println();
Serial.println("Call Terminated");
delay(1000);
on_call=false;
user_wait=false;
}
 
}
 
}
 
 
void terminate_call (void)
{
bool user_wait = true; //default state
start_clock();
while(user_wait)
{
user_wait=check_termination(); 
if(digitalRead(bt_rj) == LOW)
{
mySerial.println("ATH"); //Termination action
mySerial.println();
Serial.println("Call Terminated");
delay(1000);
user_wait=false;
}
 
else
{
update_clock();
}
}
if(buttonPressCount == 0)
{
  tft.setCursor(210,130);
  tft.setTextSize(2);
  tft.printf("                                                                                                          "); 
}
else {tft.fillRect(200,130, 200, 20, TFT_WHITE);}
on_call=false;
}
 
// Function to start a clock
void start_clock (void)
{
tft.fillRect(200,130, 230, 30, TFT_WHITE);
c_start=millis();
sec=0;
minutes=0;
}
 
// Function to update the value as arduino internal clock
 
void update_clock (void)
{
long current= millis();
if(current-c_start>1000)
{
sec++;
c_start=current;
}
 
if(sec>59)
{
minutes++;
sec=-0;
}
tft.setCursor(210,130);
if(minutes<10)
{tft.printf("0");}
tft.println(minutes);
tft.setCursor(235,130);
tft.printf(":");
tft.setCursor(250,130);
if(sec<10)
{tft.printf("0");}
tft.println(sec);
}
 


//Check if 'NO CARRIER' is printer on Serial monitor
 
bool check_termination (void)
{
bool check=true;
String listen_no="";
//Serial.print(buttonPressCount);
while(mySerial.available())
{
char data= mySerial.read();
Serial.print(data);
delay(50);
listen_no.concat(data);
}
delay(50);
if(listen_no.indexOf("BUSY")>0) // I check for only CAR  
{ 
  if(buttonPressCount ==1)
  {
  flag_gps=false;
  goi_thatbai_1();
  delay(500);
  //GUI(number_taixe,SMS_Warning);
  }
  else if(buttonPressCount==2)
  {
   flag_gps=false;
   goi_thatbai_lan2();
   delay(500);
     //GUI(number_taixe,SMS_Warning);
   }
  else if(buttonPressCount == 3){
  flag_gps=true; 
  delay(500);
  buttonPressCount = 0;
  Serial.printf("hi");
  flag_gps=true;
  
  goithatbai_ph();
  delay(4000);
  action = "WT";
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  readySystem();
  //nut = !nut;
}
  
  delay(500);
  check=false;
   
  }
if(listen_no.indexOf("NO CARRIER")>0) // I check for only CAR
{ 
  if(buttonPressCount == 3){
  goithanhcong_ph();
  delay(5000);
  buttonPressCount = 0;
  flag_gps=true;
  readySystem();
  check=false;
  }
  else { 
   goithanhcong_1();
   delay(5000);
   flag_gps=true;
   if(buttonPressCount == 2)
   {
    nut = !nut;
   }
   buttonPressCount = 0;
   readySystem();
   check=false; 
  }
 }
if(listen_no.indexOf("CAR")>0) // I check for only CAR
{check=false;}
 
return check;
}
 
//Essential command to determine the state of GSM module
bool GSM_operational(void)
{
int count =0;
bool Status=false;
mySerial.println();
while(1)
{
if (mySerial.available()>0)
{
char data = mySerial.read();
if( data == 'O' || data == 'K') //Its working properly
{
Serial.println("OK");
Status=true;
break;
}
if( data == 'E' || data == 'R' || data== 'O') // Working yet busy with some thing else
{
Serial.println("GSM not functional");
Status=false;
break;
}
}
count++;
delay(10);
if (count == 100)
{
Serial.println("GSM not connected"); // No reponse for AT commands
Status=false;
break;
}
}
return Status;
}
 
void clear_Serial (void)
{
while(mySerial.available())
{
char character=mySerial.read();
Serial.print(character);
}
 
}
 

//-------------------------------------------------------------------
void GUI(String number,String SMS)
  {
    Serial.println ("Sending Message");
    mySerial.println("AT+CMGF=1");
    delay(500);
    Serial.println ("Set SMS Number");
    mySerial.println(("AT+CMGS=\"" + number + "\"\r"));
    delay(500);
    mySerial. println(SMS);
    delay(500);
    mySerial.println((char)26);
    delay(500);
    Serial.println ("Sent");
    //flag_gps=true;
    //
    action="WT";
  }
//---------------------------------------------------------------------
String formatToTwoDigits(int value) {
  if (value < 10) {
    return "0" + String(value);
  } else {
    return String(value);
  }
}
//--------------------------------------
void GPS_Time()
  {
    while (neo6m.available() > 0) 
    {
      if (gps.encode(neo6m.read())) 
      { get_location();
        if (gps.time.isValid() && gps.date.isValid()) 
        { int adjustedHour = (gps.time.hour() + 7) % 24;
          timeStr = "'" + formatToTwoDigits(adjustedHour) + ":" + formatToTwoDigits(gps.time.minute()) + ":" + formatToTwoDigits(gps.time.second()) + "'";
          Serial.println(timeStr);
          dateStr = "'" + String(gps.date.day()) + "/" + String(gps.date.month()) + "/" + String(gps.date.year()) + "'";
          Serial.println(dateStr);
          pin();
          delay(500);  
        }
      }
    }
  }
void GPS_Time1()
  {
    while (neo6m.available() > 0) 
    {
      if (gps.encode(neo6m.read())) 
      { 
        if (gps.time.isValid() && gps.date.isValid()) 
        { int adjustedHour = (gps.time.hour() + 7) % 24;
          timeStr = "'" + formatToTwoDigits(adjustedHour) + ":" + formatToTwoDigits(gps.time.minute()) + ":" + formatToTwoDigits(gps.time.second()) + "'";
          dateStr = "'" + String(gps.date.day()) + "/" + String(gps.date.month()) + "/" + String(gps.date.year()) + "'";
          delay(10);  
        }
      }
    }
  }
 //---------------------------------------
 void get_location()
{
    if(gps.location.isValid())  
  { 
    GPS_check();
    float latitude = gps.location.lat(); 
    float longitude = gps.location.lng();   
    Firebase.setFloat(firebaseData, "/GPS/VIDOCUAXE2", latitude);
    Firebase.setFloat(firebaseData, "/GPS/KINHDOCUAXE2", longitude);
  }
  else {
    GPS_NO();
    Firebase.setString(firebaseData, path + "/GPS/KINHDOCUAXE2","'KHÔNG THẤY'"); 
    Firebase.setString(firebaseData, path + "/GPS/VIDOCUAXE2","'KHÔNG THẤY'"); 
      }
}

//---------------------------------------------
void goi_lan_1(){
  if(h=="hanh"){
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(65, 160, 150, 150, goitaixe);
  tft.pushImage(240, 160, 150, 150, hanh);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(45,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI TAI XE");

  tft.setCursor(192,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("LAN 1...");
  
  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00"); 
}
  else if(h=="dinhhai"){
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(65, 160, 150, 150, goitaixe); 
  tft.pushImage(240, 160, 150, 150, dinhhai);  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(45,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI TAI XE");

  tft.setCursor(192,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("LAN 1...");
  
  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00"); 
  }
   

}
//-------------------------------------------------------
void goi_thatbai_1(){
  if(h=="hanh"){
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(65, 160, 150, 150, goitaixe);
  tft.pushImage(240, 160, 150, 150, hanh);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(168,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("GOI THAT BAI");

  tft.setCursor(26,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("MOI BAN NHAN NUT DE GOI TAI XE LAN 2");
}
  else if(h=="dinhhai"){
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(65, 160, 150, 150, goitaixe);
  tft.pushImage(240, 160, 150, 150, dinhhai);
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(168,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("GOI THAT BAI");

  tft.setCursor(26,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("MOI BAN NHAN NUT DE GOI TAI XE LAN 2");    
  }

}

void goithanhcong_1(){
  if(h=="hanh"){
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(65, 160, 150, 150, goitaixe);
  tft.pushImage(240, 160, 150, 150, hanh);
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");
  tft.fillRect(45,60, 480, 30, TFT_WHITE);
  tft.setCursor(158,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("GOI THANH CONG");
  tft.setCursor(12,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("BINH TINH! VUI LONG DOI TRONG GIAY LAT");  
  }
  else if(h=="dinhhai"){
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(65, 160, 150, 150, goitaixe);
  tft.pushImage(240, 160, 150, 150, dinhhai);
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");
  tft.fillRect(45,60, 480, 30, TFT_WHITE);
  tft.setCursor(158,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("GOI THANH CONG");
  tft.setCursor(12,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("BINH TINH! VUI LONG DOI TRONG GIAY LAT");  
}

}

void goi_ph(){
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(190, 185, 100, 100, call_sos);
  tft.pushImage(20, 160, 150, 150, tin);
  tft.pushImage(310, 160, 150, 150, tin_mother);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(25,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI PHU HUYNH");

  tft.setCursor(157,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("TRAN TRUNG TIN");

}

void goi_lan_2(){
  if(h=="hanh"){
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(65, 160, 150, 150, goitaixe);
  tft.pushImage(240, 160, 150, 150, hanh);
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(45,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI TAI XE");

  tft.setCursor(192,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("LAN 2...");  

  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00");
  }
  else if(h=="dinhhai"){
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(65, 160, 150, 150, goitaixe);
  tft.pushImage(240, 160, 150, 150, dinhhai);
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(45,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI TAI XE");

  tft.setCursor(192,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("LAN 2...");  

  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00");
}  
}

void goi_thatbai_lan2(){
  if(h=="hanh"){
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(65, 160, 150, 150, goitaixe);
  tft.pushImage(240, 160, 150, 150, hanh);
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(168,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("GOI THAT BAI");

  tft.setCursor(12,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("MOI BAN QUET THE DE LIEN LAC PHU HUYNH");
  }
  else if(h=="dinhhai"){
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(65, 160, 150, 150, goitaixe);
  tft.pushImage(240, 160, 150, 150, dinhhai);
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(168,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("GOI THAT BAI");

  tft.setCursor(12,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("MOI BAN QUET THE DE LIEN LAC PHU HUYNH");
}  
}
//----------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//điểm danh học sinh lên xe, xuống xe
void hocSinh1(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW); 
  dem1++;
        tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
        tft.pushImage(165, 160, 150, 150, tin);   
        tft.setCursor(135,25);
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("DIEM DANH HOC SINH");

        tft.setCursor(160,50);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("TRAN TRUNG TIN");

        tft.setCursor(160,75);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("MSHS: 20161270");

        tft.setCursor(195,100);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("LOP: 1/1");  
                      
        if (tam1==0){
        tft.drawRect(96,120,290,30, TFT_YELLOW);
        tft.fillRect(96,120,290,30, TFT_YELLOW);
        tft.setCursor(103,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE DEN TRUONG");
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 1/Ho va ten", "'Trần Trung Tín'");    
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 1/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 1/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS1",dem1);   
        }
        else if (tam1==2)
        {
        tft.drawRect(121,120,240,30, TFT_YELLOW);
        tft.fillRect(121,120,240,30, TFT_YELLOW);
        tft.setCursor(128,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE VE NHA");    
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 1/Ho va ten", "'Trần Trung Tín'");    
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 1/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 1/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS1",dem1);  
        }              
        else if (tam1==1){
        tft.drawRect(84,120,310,30, TFT_YELLOW);
        tft.fillRect(84,120,310,30, TFT_YELLOW);
        tft.setCursor(90,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE DEN TRUONG"); 
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 1/Ho va ten", "'Trần Trung Tín'");    
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 1/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 1/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS1",dem1); 
        GUI(number_ph,SMS_Success1);     
        }
        else if (tam1==3)
        {
        tft.drawRect(109,120,265,30, TFT_YELLOW);
        tft.fillRect(109,120,265,30, TFT_YELLOW);
        tft.setCursor(115,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE VE NHA");
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 1/Ho va ten", "'Trần Trung Tín'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 1/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 1/date", dateStr);
        GUI(number_ph,SMS_Success1n);
        dem1=0;
        Firebase.setInt(firebaseData, path + "/CHECK/HS1",dem1);                    
      }
  delay(1000);
  readySystem();
}

void hocSinh2(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW); 
  dem2++;
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(165, 160, 150, 150, khang);   
  tft.setCursor(135,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("DIEM DANH HOC SINH");
  
  tft.setCursor(129,50);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("PHAM HOANG VI KHANG");

  tft.setCursor(160,75);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("MSHS: 20161208");

  tft.setCursor(195,100);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("LOP: 2/8");  
        
  if (tam2==0){
    tft.drawRect(96,120,290,30, TFT_YELLOW);
    tft.fillRect(96,120,290,30, TFT_YELLOW);
    tft.setCursor(103,127);
    tft.setTextColor(TFT_BLACK, TFT_YELLOW);
    tft.setTextSize(2);
    tft.printf("DA LEN XE DE DEN TRUONG");
    Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 2/Ho va ten", "'Phạm Hoàng Vĩ Khang'");
    Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 2/time", timeStr);
    Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 2/date", dateStr);
    Firebase.setInt(firebaseData, path + "/CHECK/HS2",dem2);          
    }
   else if (tam2==2)
    {
     tft.drawRect(121,120,240,30, TFT_YELLOW);
     tft.fillRect(121,120,240,30, TFT_YELLOW);
     tft.setCursor(128,127);
     tft.setTextColor(TFT_BLACK, TFT_YELLOW);
     tft.setTextSize(2);
     tft.printf("DA LEN XE DE VE NHA");
     Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 2/Ho va ten", "'Phạm Hoàng Vĩ Khang'");   
     Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 2/time", timeStr);
     Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 2/date", dateStr);
     Firebase.setInt(firebaseData, path + "/CHECK/HS2",dem2);         
    }       
     else if (tam2==1){
     tft.drawRect(84,120,310,30, TFT_YELLOW);
     tft.fillRect(84,120,310,30, TFT_YELLOW);
     tft.setCursor(90,127);
     tft.setTextColor(TFT_BLACK, TFT_YELLOW);
     tft.setTextSize(2);
     tft.printf("DA XUONG XE DE DEN TRUONG");    
     Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 2/Ho va ten", "'Phạm Hoàng Vĩ Khang'"); 
     Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 2/time", timeStr);
     Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 2/date", dateStr);
     GUI(number_ph,SMS_Success2);
     Firebase.setInt(firebaseData, path + "/CHECK/HS2",dem2);       
     }
     else if(tam2==3)
     {
        tft.drawRect(109,120,265,30, TFT_YELLOW);
        tft.fillRect(109,120,265,30, TFT_YELLOW);
        tft.setCursor(115,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE VE NHA");
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 2/Ho va ten", "'Phạm Hoàng Vĩ Khang'");     
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 2/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 2/date", dateStr);
        GUI(number_ph,SMS_Success2n);
        dem2=0;
        Firebase.setInt(firebaseData, path + "/CHECK/HS2",dem2);    
     }
  delay(1000);
  readySystem();
}

void hocSinh3(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW); 
  dem3++;
        tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
        tft.pushImage(165, 160, 150, 150, nguyen);   
        tft.setCursor(135,25);
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("DIEM DANH HOC SINH");

        tft.setCursor(135,50);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("VO PHAN TRI NGUYEN");

        tft.setCursor(160,75);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("MSHS: 20161238");

        tft.setCursor(195,100);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("LOP: 3/5");  
        
        if (tam3==0){
        tft.drawRect(96,120,290,30, TFT_YELLOW);
        tft.fillRect(96,120,290,30, TFT_YELLOW);
        tft.setCursor(103,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE DEN TRUONG");  
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 3/Ho va ten", "'Võ Phan Trí Nguyên'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 3/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 3/date", dateStr);  
        Firebase.setInt(firebaseData, path + "/CHECK/HS3",dem3);       
        }
        else if (tam3==2)
        {
        tft.drawRect(121,120,240,30, TFT_YELLOW);
        tft.fillRect(121,120,240,30, TFT_YELLOW);
        tft.setCursor(128,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE VE NHA");  
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 3/Ho va ten", "'Võ Phan Trí Nguyên'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 3/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 3/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS3",dem3);    
        }      
        else if (tam3==1){
        tft.drawRect(84,120,310,30, TFT_YELLOW);
        tft.fillRect(84,120,310,30, TFT_YELLOW);
        tft.setCursor(90,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE DEN TRUONG");
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 3/Ho va ten", "'Võ Phan Trí Nguyên'");     
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 3/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 3/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS3",dem3);
        GUI(number_ph,SMS_Success3);          
        }
        else if (tam3==3)
        {
        tft.drawRect(109,120,265,30, TFT_YELLOW);
        tft.fillRect(109,120,265,30, TFT_YELLOW);
        tft.setCursor(115,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE VE NHA"); 
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 3/Ho va ten", "'Võ Phan Trí Nguyên'");  
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 3/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 3/date", dateStr);
        GUI(number_ph,SMS_Success3n);
        dem3=0;
        Firebase.setInt(firebaseData, path + "/CHECK/HS3",dem3);       
        }     
  delay(1000);
  readySystem(); 
}

void hocSinh4(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW); 
  dem4++;
        tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
        tft.pushImage(165, 160, 150, 150, theanh);   
        tft.setCursor(135,25);
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("DIEM DANH HOC SINH");

        tft.setCursor(128,50);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("PHAM NGUYEN THE ANH");

        tft.setCursor(160,75);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("MSHS: 20161157");

        tft.setCursor(195,100);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("LOP: 4/7");   
        
        if (tam4==0){
        tft.drawRect(96,120,290,30, TFT_YELLOW);
        tft.fillRect(96,120,290,30, TFT_YELLOW);
        tft.setCursor(103,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE DEN TRUONG");  
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 4/Ho va ten", "'Phạm Nguyễn Thế Anh'");   
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 4/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 4/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS4",dem4);     
        }
        else if (tam4==2)
        {
        tft.drawRect(121,120,240,30, TFT_YELLOW);
        tft.fillRect(121,120,240,30, TFT_YELLOW);
        tft.setCursor(128,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE VE NHA"); 
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 4/Ho va ten", "'Phạm Nguyễn Thế Anh'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 4/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 4/date", dateStr);  
        Firebase.setInt(firebaseData, path + "/CHECK/HS4",dem4);          
        }             
        else if (tam4==1){
        tft.drawRect(84,120,310,30, TFT_YELLOW);
        tft.fillRect(84,120,310,30, TFT_YELLOW);
        tft.setCursor(90,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE DEN TRUONG");
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 4/Ho va ten", "'Phạm Nguyễn Thế Anh'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 4/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 4/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS4",dem4); 
        GUI(number_ph,SMS_Success4);          
        }
        else if(tam4==3)
        {
        tft.drawRect(109,120,265,30, TFT_YELLOW);
        tft.fillRect(109,120,265,30, TFT_YELLOW);
        tft.setCursor(115,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE VE NHA");
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 4/Ho va ten", "'Phạm Nguyễn Thế Anh'");   
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 4/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 4/date", dateStr);
        GUI(number_ph,SMS_Success4n);      
        dem4=0;
        Firebase.setInt(firebaseData, path + "/CHECK/HS4",dem4);   
        }
  delay(1000);
  readySystem(); 
}

void hocSinh5(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW); 
  dem5++;
        tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
        tft.pushImage(165, 160, 150, 150, caominh);   
        tft.setCursor(135,25);
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("DIEM DANH HOC SINH");

        tft.setCursor(175,50);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("VU CAO MINH");

        tft.setCursor(160,75);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("MSHS: 20161021");

        tft.setCursor(195,100);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("LOP: 5/9");  
        
        if (tam5==0){
        tft.drawRect(96,120,290,30, TFT_YELLOW);
        tft.fillRect(96,120,290,30, TFT_YELLOW);
        tft.setCursor(103,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE DEN TRUONG");   
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 5/Ho va ten", "'Vũ Cao Minh'");  
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 5/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 5/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS5",dem5);         
        }
        else if (tam5==2)
        {
        tft.drawRect(121,120,240,30, TFT_YELLOW);
        tft.fillRect(121,120,240,30, TFT_YELLOW);
        tft.setCursor(128,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE VE NHA");   
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 5/Ho va ten", "'Vũ Cao Minh'");  
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 5/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 5/date", dateStr);  
        Firebase.setInt(firebaseData, path + "/CHECK/HS5",dem5);     
      }     
      
        else if (tam5==1){
        tft.drawRect(84,120,310,30, TFT_YELLOW);
        tft.fillRect(84,120,310,30, TFT_YELLOW);
        tft.setCursor(90,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE DEN TRUONG");
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 5/Ho va ten", "'Vũ Cao Minh'");  
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 5/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 5/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS5",dem5);  
        GUI(number_ph,SMS_Success5);      
        }
        else if(tam5==3)
        {
        tft.drawRect(109,120,265,30, TFT_YELLOW);
        tft.fillRect(109,120,265,30, TFT_YELLOW);
        tft.setCursor(115,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE VE NHA"); 
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 5/Ho va ten", "'Vũ Cao Minh'");  
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 5/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 5/date", dateStr);
        GUI(number_ph,SMS_Success5n);
        dem5=0;
        Firebase.setInt(firebaseData, path + "/CHECK/HS5",dem5);       
        } 
  delay(1000);
  readySystem();  
}

void hocSinh6(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW); 
  dem6++;
        tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
        tft.pushImage(165, 160, 150, 150, ngoctuong);   
        tft.setCursor(135,25);
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("DIEM DANH HOC SINH");

        tft.setCursor(154,50);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("DOAN NGOC TUONG");

        tft.setCursor(160,75);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("MSHS: 20161279");

        tft.setCursor(195,100);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("LOP: 1/8");   
        
        if (tam6==0){
        tft.drawRect(96,120,290,30, TFT_YELLOW);
        tft.fillRect(96,120,290,30, TFT_YELLOW);
        tft.setCursor(103,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE DEN TRUONG"); 
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 6/Ho va ten", "'Đoàn Ngọc Tường'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 6/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 6/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS6",dem6);          
        }
        else if (tam6==2)
        {
        tft.drawRect(121,120,240,30, TFT_YELLOW);
        tft.fillRect(121,120,240,30, TFT_YELLOW);
        tft.setCursor(128,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE VE NHA");  
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 6/Ho va ten", "'Đoàn Ngọc Tường'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 6/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 6/date", dateStr);\
        Firebase.setInt(firebaseData, path + "/CHECK/HS6",dem6);          
        }          
        else if (tam6==1){
        tft.drawRect(84,120,310,30, TFT_YELLOW);
        tft.fillRect(84,120,310,30, TFT_YELLOW);
        tft.setCursor(90,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE DEN TRUONG");
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 6/Ho va ten", "'Đoàn Ngọc Tường'");     
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 6/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 6/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS6",dem6); 
        GUI(number_ph,SMS_Success6);  
        }
        else if(tam6==3)
        {
        tft.drawRect(109,120,265,30, TFT_YELLOW);
        tft.fillRect(109,120,265,30, TFT_YELLOW);
        tft.setCursor(115,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE VE NHA");   
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 6/Ho va ten", "'Đoàn Ngọc Tường'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 6/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 6/date", dateStr);
        GUI(number_ph,SMS_Success6n);
        dem6=0;
        Firebase.setInt(firebaseData, path + "/CHECK/HS6",dem6);      
        }
  delay(1000);
  readySystem();  
}

void hocSinh7(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW); 
  dem7++;
        tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
        tft.pushImage(165, 160, 150, 150, tanloc);   
        tft.setCursor(135,25);
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("DIEM DANH HOC SINH");

        tft.setCursor(160,50);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("NGUYEN TAN LOC");

        tft.setCursor(160,75);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("MSHS: 20161227");

        tft.setCursor(195,100);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("LOP: 2/9");
         
        if (tam7==0){
        tft.drawRect(96,120,290,30, TFT_YELLOW);
        tft.fillRect(96,120,290,30, TFT_YELLOW);
        tft.setCursor(103,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE DEN TRUONG"); 
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 7/Ho va ten", "'Nguyễn Tấn Lộc'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 7/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 7/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS7",dem7);          
        }
        else if (tam7==2)
        {
        tft.drawRect(121,120,240,30, TFT_YELLOW);
        tft.fillRect(121,120,240,30, TFT_YELLOW);
        tft.setCursor(128,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE VE NHA"); 
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 7/Ho va ten", "'Nguyễn Tấn Lộc'");   
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 7/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 7/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS7",dem7);   
        }      
      else if (tam7==1){ 
        tft.drawRect(84,120,310,30, TFT_YELLOW);
        tft.fillRect(84,120,310,30, TFT_YELLOW);
        tft.setCursor(90,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE DEN TRUONG");  
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 7/Ho va ten", "'Nguyễn Tấn Lộc'");   
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 7/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 7/date", dateStr);
        GUI(number_ph,SMS_Success7);
        Firebase.setInt(firebaseData, path + "/CHECK/HS7",dem7);     
        }
      else if(tam7==3)
        {
        tft.drawRect(109,120,265,30, TFT_YELLOW);
        tft.fillRect(109,120,265,30, TFT_YELLOW);
        tft.setCursor(115,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE VE NHA");
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 7/Ho va ten", "'Nguyễn Tấn Lộc'");   
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 7/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 7/date", dateStr);
        GUI(number_ph,SMS_Success7n);
        dem7=0;
        Firebase.setInt(firebaseData, path + "/CHECK/HS7",dem7);     
        }
  
  delay(1000);
  readySystem();  
}

void hocSinh8(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW); 
  dem8++;
        tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
        tft.pushImage(165, 160, 150, 150, hungkiet);   
        tft.setCursor(135,25);
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("DIEM DANH HOC SINH");

        tft.setCursor(122,50);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("NGUYEN PHI HUNG KIET");

        tft.setCursor(160,75);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("MSHS: 20161218");

        tft.setCursor(195,100);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("LOP: 3/4"); 
        
        if (tam8==0){
        tft.drawRect(96,120,290,30, TFT_YELLOW);
        tft.fillRect(96,120,290,30, TFT_YELLOW);
        tft.setCursor(103,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE DEN TRUONG");    
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 8/Ho va ten", "'Nguyễn Phi Hùng Kiệt'");  
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 8/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 8/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS8",dem8);     
        }
        else if (tam8==2)
        {
        tft.drawRect(121,120,240,30, TFT_YELLOW);
        tft.fillRect(121,120,240,30, TFT_YELLOW);
        tft.setCursor(128,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE VE NHA");    
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 8/Ho va ten", "'Nguyễn Phi Hùng Kiệt'");
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 8/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 8/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS8",dem8);   
        }         
        else if (tam8==1){
        tft.drawRect(84,120,310,30, TFT_YELLOW);
        tft.fillRect(84,120,310,30, TFT_YELLOW);
        tft.setCursor(90,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE DEN TRUONG"); 
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 8/Ho va ten", "'Nguyễn Phi Hùng Kiệt'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 8/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 8/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS8",dem8); 
        GUI(number_ph,SMS_Success8);         
        }
        else if(tam8==3)
        {
        tft.drawRect(109,120,265,30, TFT_YELLOW);
        tft.fillRect(109,120,265,30, TFT_YELLOW);
        tft.setCursor(115,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE VE NHA");  
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 8/Ho va ten", "'Nguyễn Phi Hùng Kiệt'");  
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 8/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 8/date", dateStr);
        GUI(number_ph,SMS_Success8n);
        dem8=0;
        Firebase.setInt(firebaseData, path + "/CHECK/HS8",dem8);         
        }
  delay(1000);
  readySystem(); 
}

void hocSinh9(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW); 
  dem9++;
        tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
        tft.pushImage(165, 160, 150, 150, ngochai);   
        tft.setCursor(135,25);
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("DIEM DANH HOC SINH");

        tft.setCursor(140,50);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("TON THAT NGOC HAI");

        tft.setCursor(160,75);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("MSHS: 20161186");

        tft.setCursor(195,100);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("LOP: 4/1"); 
        
        if (tam9==0){
        tft.drawRect(96,120,290,30, TFT_YELLOW);
        tft.fillRect(96,120,290,30, TFT_YELLOW);
        tft.setCursor(103,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE DEN TRUONG");  
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 9/Ho va ten", "'Tôn Thất Ngọc Hải'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 9/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 9/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS9",dem9);         
        }
        else if (tam9==2)
        {
        tft.drawRect(121,120,240,30, TFT_YELLOW);
        tft.fillRect(121,120,240,30, TFT_YELLOW);
        tft.setCursor(128,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE VE NHA");   
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 9/Ho va ten", "'Tôn Thất Ngọc Hải'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 9/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 9/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS9",dem9);   
        }      
        else if (tam9==1){
        tft.drawRect(84,120,310,30, TFT_YELLOW);
        tft.fillRect(84,120,310,30, TFT_YELLOW);
        tft.setCursor(90,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE DEN TRUONG");   
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 9/Ho va ten", "'Tôn Thất Ngọc Hải'");  
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 9/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 9/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS9",dem9);
        GUI(number_ph,SMS_Success9); 
        }
        else if (tam9==3)
        {
        tft.drawRect(109,120,265,30, TFT_YELLOW);
        tft.fillRect(109,120,265,30, TFT_YELLOW);
        tft.setCursor(115,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE VE NHA");   
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 9/Ho va ten", "'Tôn Thất Ngọc Hải'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 9/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 9/date", dateStr);
        GUI(number_ph,SMS_Success9n);    
        dem9=0;
        Firebase.setInt(firebaseData, path + "/CHECK/HS9",dem9);       
        }
  delay(1000);
  readySystem();  
}

void hocSinh10(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW); 
  dem10++;
        tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
        tft.pushImage(165, 160, 150, 150, ngocan);   
        tft.setCursor(135,25);
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("DIEM DANH HOC SINH");

        tft.setCursor(185,50);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("DO NGOC AN");

        tft.setCursor(160,75);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("MSHS: 20161153");

        tft.setCursor(195,100);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("LOP: 5/7"); 
        
        if (tam10==0){
        tft.drawRect(96,120,290,30, TFT_YELLOW);
        tft.fillRect(96,120,290,30, TFT_YELLOW);
        tft.setCursor(103,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE DEN TRUONG");  
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 10/Ho va ten", "'Đỗ Ngọc An'");  
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 10/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de den truong 2/Ten hoc sinh 10/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS10",dem10);        
        }
        else if (tam10==2)
        {
        tft.drawRect(121,120,240,30, TFT_YELLOW);
        tft.fillRect(121,120,240,30, TFT_YELLOW);
        tft.setCursor(128,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA LEN XE DE VE NHA");  
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 10/Ho va ten", "'Đỗ Ngọc An'");   
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 10/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh len xe de ve nha 2/Ten hoc sinh 10/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS10",dem10);  
        }          
        else if (tam10==1){
        tft.drawRect(84,120,310,30, TFT_YELLOW);
        tft.fillRect(84,120,310,30, TFT_YELLOW);
        tft.setCursor(90,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE DEN TRUONG");  
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 10/Ho va ten", "'Đỗ Ngọc An'"); 
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 10/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de den truong 2/Ten hoc sinh 10/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/HS10",dem10);
        GUI(number_ph,SMS_Success10);     
        }
        else if(tam10==3)
        {
        tft.drawRect(109,120,265,30, TFT_YELLOW);
        tft.fillRect(109,120,265,30, TFT_YELLOW);
        tft.setCursor(115,127);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("DA XUONG XE DE VE NHA"); 
        Firebase.setString(firebaseData, path + "Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 10/Ho va ten", "'Đỗ Ngọc An'");
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 10/time", timeStr);
        Firebase.setString(firebaseData, "/Danh sach hoc sinh xuong xe de ve nha 2/Ten hoc sinh 10/date", dateStr);
        GUI(number_ph,SMS_Success10n);       
        dem10=0;
        Firebase.setInt(firebaseData, path + "/CHECK/HS10",dem10);
        }
  delay(1000);
  readySystem();  
}
//---------------------------------------------------------------------------------------------------------------------------------
//điểm danh tài xế lên xe, xuống xe
void con_HS_TrenXe(){
    tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
    tft.pushImage(165, 140, 150, 150, warning); 
    tft.setCursor(200,50);
    tft.setTextColor(TFT_RED, TFT_WHITE);
    tft.setTextSize(2);
    tft.printf("CANH BAO");
    tft.setCursor(115,75);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextSize(2);
    tft.printf("HIEN TAI CON HOC SINH");
    tft.setCursor(155,100);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextSize(2);
    tft.printf("MAC KET TREN XE");
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(1000);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW); 
    if (UID[i] == ID_tx1[i]) {
    demtx1 =0;
    Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Ten tai xe", "'Ngô Văn Hạnh'");
    Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Bien so xe", "'15-C1 010.82'");           
    Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Loai xe", "HYUNDAI");
    Firebase.setString(firebaseData, path + "Thong tin cua xe 2/So dien thoai tai xe", "'0333617584'");   
    Firebase.setString(firebaseData, "/Thong tin cua xe 2/Thoi gian tai xe xuong xe/time", timeStr);
    Firebase.setString(firebaseData, "/Thong tin cua xe 2/Thoi gian tai xe xuong xe/date", dateStr);
    Firebase.setInt(firebaseData, path + "/CHECK/TX1",demtx1);
    }
    else if (UID[i] == ID_tx2[i]) {
    demtx2 =0;
    Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Ten tai xe", "'Vũ Đình Hải'");
    Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Bien so xe", "'15-C1 010.82'");           
    Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Loai xe", "HYUNDAI");
    Firebase.setString(firebaseData, path + "Thong tin cua xe 2/So dien thoai tai xe", "'0368403868'");      
    Firebase.setString(firebaseData, "/Thong tin cua xe 2/Thoi gian tai xe xuong xe/time", timeStr);
    Firebase.setString(firebaseData, "/Thong tin cua xe 2/Thoi gian tai xe xuong xe/date", dateStr);
    Firebase.setInt(firebaseData, path + "/CHECK/TX2",demtx2);
    }   
}

void taiXe_DuocPhepXuongXe(){
    tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD           
    tft.fillRect(125,120,225,30, TFT_YELLOW);
    tft.setCursor(146,25);
    tft.setTextColor(TFT_RED, TFT_WHITE);
    tft.setTextSize(2);
    tft.printf("DIEM DANH TAI XE");
    tft.setCursor(30,50);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextSize(2);
    tft.printf("HIEN TAI KHONG CON HOC SINH TREN XE");
    if (UID[i] == ID_tx1[i])
    { 
      demtx1 =0;
      tft.pushImage(165, 160, 150, 150, hanh); 
      tft.setCursor(170,75);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setTextSize(2);
      tft.printf("NGO VAN HANH");
      tft.setCursor(160,100);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setTextSize(2);
      tft.printf("MSTX: 20161188");
      Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Ten tai xe", "'Ngô Văn Hạnh'");
      Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Bien so xe", "'15-C1 010.82'");           
      Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Loai xe", "HYUNDAI");
      Firebase.setString(firebaseData, path + "Thong tin cua xe 2/So dien thoai tai xe", "'0333617584'");   
      Firebase.setString(firebaseData, "/Thong tin cua xe 2/Thoi gian tai xe xuong xe/time", timeStr);
      Firebase.setString(firebaseData, "/Thong tin cua xe 2/Thoi gian tai xe xuong xe/date", dateStr);
      Firebase.setInt(firebaseData, path + "/CHECK/TX1",demtx1);
    }
    else if (UID[i] == ID_tx2[i]) {
      demtx2 =0;
      tft.pushImage(165, 160, 150, 150, dinhhai); 
      tft.setCursor(177,75);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setTextSize(2);
      tft.printf("VU DINH HAI");
      tft.setCursor(160,100);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setTextSize(2);
      tft.printf("MSTX: 20161187");
      Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Ten tai xe", "'Vũ Đình Hải'");
      Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Bien so xe", "'15-C1 010.82'");           
      Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Loai xe", "HYUNDAI");
      Firebase.setString(firebaseData, path + "Thong tin cua xe 2/So dien thoai tai xe", "'0368403868'");   
      Firebase.setString(firebaseData, "/Thong tin cua xe 2/Thoi gian tai xe xuong xe/time", timeStr);
      Firebase.setString(firebaseData, "/Thong tin cua xe 2/Thoi gian tai xe xuong xe/date", dateStr);
      Firebase.setInt(firebaseData, path + "/CHECK/TX2",demtx2);             
    }
    tft.setCursor(130,127);
    tft.setTextColor(TFT_BLACK, TFT_YELLOW);
    tft.setTextSize(2);
    tft.printf("TAI XE DA XUONG XE");        
}

void taiXeXuongXe(){
    if (tam1 == 1 || tam1 == 3 || tam2 == 1 || tam2 == 3  || tam3 == 1 || tam3 == 3 || tam4 == 1 || tam4 == 3 || tam5 == 1 || tam5 == 3 || tam6 == 1 || tam6 == 3 || tam7 == 1 || tam7 == 3 || tam8 == 1 || tam8 == 3|| tam9 == 1 || tam9 == 3|| tam10 == 1 || tam10 == 3)
    {
       con_HS_TrenXe();
    }
  else{
      taiXe_DuocPhepXuongXe();              
    }  
}

void taiXe1() {
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  h="hanh"; 
  demtx1++;
  if (tamtx1 == 0){
        tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
        tft.pushImage(165, 148, 150, 150, hanh);   
        tft.fillRect(138,108,200,30, TFT_YELLOW);
        tft.setCursor(146,38);
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("DIEM DANH TAI XE");

        tft.setCursor(170,63);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("NGO VAN HANH");

        tft.setCursor(160,88);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("MSTX: 20161188");
        
        tft.setCursor(143,115);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("TAI XE DA LEN XE"); 
        Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Ten tai xe", "'Ngô Văn Hạnh'");
        Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Bien so xe", "'15-C1 010.82'");           
        Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Loai xe", "HYUNDAI");
        Firebase.setString(firebaseData, path + "Thong tin cua xe 2/So dien thoai tai xe", "'0333617584'");
        Firebase.setString(firebaseData, "/Thong tin cua xe 2/Thoi gian tai xe len xe/time", timeStr);
        Firebase.setString(firebaseData, "/Thong tin cua xe 2/Thoi gian tai xe len xe/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/TX1",demtx1);   
  }
  else if(tamtx1 == 1){
        taiXeXuongXe();      
  }
  delay(1000);
  readySystem();     
}

void taiXe2() {
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  h="dinhhai";
  demtx2++;
  if (tamtx2 == 0){
        tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
        tft.pushImage(165, 148, 150, 150, dinhhai);   
        tft.fillRect(138,108,200,30, TFT_YELLOW);
        tft.setCursor(146,38);
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("DIEM DANH TAI XE");

        tft.setCursor(177,63);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("VU DINH HAI");

        tft.setCursor(160,88);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(2);
        tft.printf("MSTX: 20161187");

        tft.setCursor(143,115);
        tft.setTextColor(TFT_BLACK, TFT_YELLOW);
        tft.setTextSize(2);
        tft.printf("TAI XE DA LEN XE"); 
        Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Ten tai xe", "'Vũ Đình Hải'");
        Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Bien so xe", "'15-C1 010.82'");           
        Firebase.setString(firebaseData, path + "Thong tin cua xe 2/Loai xe", "HYUNDAI");
        Firebase.setString(firebaseData, path + "Thong tin cua xe 2/So dien thoai tai xe", "'0368403868'");
        Firebase.setString(firebaseData, "/Thong tin cua xe 2/Thoi gian tai xe len xe/time", timeStr);
        Firebase.setString(firebaseData, "/Thong tin cua xe 2/Thoi gian tai xe len xe/date", dateStr);
        Firebase.setInt(firebaseData, path + "/CHECK/TX2",demtx2);     
  }
  else if(tamtx2 == 1){
        taiXeXuongXe();   
  }
  delay(1000);
  readySystem();   
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
//cuộc gọi khẩn cấp cho phụ huynh học sinh
void hocSinh1_Sos(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(190, 185, 100, 100, call_sos);
  tft.pushImage(20, 160, 150, 150, tin);
  tft.pushImage(310, 160, 150, 150, tin_mother);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(25,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI PHU HUYNH");

  tft.setCursor(157,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("TRAN TRUNG TIN");

  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00");
  
  delay(1000);
}

void hocSinh2_Sos(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(190, 185, 100, 100, call_sos);
  tft.pushImage(20, 160, 150, 150, khang);
  tft.pushImage(310, 160, 150, 150, tin_mother);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(25,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI PHU HUYNH");

  tft.setCursor(129,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("PHAM HOANG VI KHANG");

  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00");
  
  delay(1000);
}

void hocSinh3_Sos(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(190, 185, 100, 100, call_sos);
  tft.pushImage(20, 160, 150, 150, nguyen);
  tft.pushImage(310, 160, 150, 150, tin_mother);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(25,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI PHU HUYNH");

  tft.setCursor(135,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("VO PHAN TRI NGUYEN");

  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00");
  
  delay(1000);
}

void hocSinh4_Sos(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(190, 185, 100, 100, call_sos);
  tft.pushImage(20, 160, 150, 150, theanh);
  tft.pushImage(310, 160, 150, 150, tin_mother);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(25,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI PHU HUYNH");

  tft.setCursor(128,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("PHAM NGUYEN THE ANH");

  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00");
  
  delay(1000); 
}

void hocSinh5_Sos(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(190, 185, 100, 100, call_sos);
  tft.pushImage(20, 160, 150, 150, caominh);
  tft.pushImage(310, 160, 150, 150, tin_mother);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(25,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI PHU HUYNH");

  tft.setCursor(175,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("VU CAO MINH");

  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00");
  
  delay(1000);
}

void hocSinh6_Sos(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(190, 185, 100, 100, call_sos);
  tft.pushImage(20, 160, 150, 150, ngoctuong);
  tft.pushImage(310, 160, 150, 150, tin_mother);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(25,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI PHU HUYNH");

  tft.setCursor(154,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("DOAN NGOC TUONG");

  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00");
  
  delay(1000);

}

void hocSinh7_Sos(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(190, 185, 100, 100, call_sos);
  tft.pushImage(20, 160, 150, 150, tanloc);
  tft.pushImage(310, 160, 150, 150, tin_mother);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(25,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI PHU HUYNH");

  tft.setCursor(160,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("NGUYEN TAN LOC");

  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00");
  
  delay(1000);  
}

void hocSinh8_Sos(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(190, 185, 100, 100, call_sos);
  tft.pushImage(20, 160, 150, 150, hungkiet);
  tft.pushImage(310, 160, 150, 150, tin_mother);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(25,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI PHU HUYNH");

  tft.setCursor(122,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("NGUYEN PHI HUNG KIET");

  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00");
  
  delay(1000); 
}

void hocSinh9_Sos(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(190, 185, 100, 100, call_sos);
  tft.pushImage(20, 160, 150, 150, ngochai);
  tft.pushImage(310, 160, 150, 150, tin_mother);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(25,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI PHU HUYNH");

  tft.setCursor(140,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("TON THAT NGOC HAI");

  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00");
  
  delay(1000);  
}

void hocSinh10_Sos(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(190, 185, 100, 100, call_sos);
  tft.pushImage(20, 160, 150, 150, ngocan);
  tft.pushImage(310, 160, 150, 150, tin_mother);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(25,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI DANG LIEN LAC VOI PHU HUYNH");

  tft.setCursor(185,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("DO NGOC AN");

  tft.setCursor(210,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("00:00");
  
  delay(1000);  
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------
//mã thẻ sai, chưa đăng kí dịch vụ
void maTheSai(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(165, 140, 150, 150, warning);
  tft.setCursor(200,35);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CANH BAO");
  tft.setCursor(133,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("HIEN TAI MA THE NAY");
  tft.setCursor(125,85);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CHUA DANG KY DICH VU");
  tft.setCursor(130,110);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("DUA RUOC CUA TRUONG");
  delay(1000);
  readySystem(); 
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
void goithatbai_ph(){
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(190, 185, 100, 100, call_sos);
  if (SOS == "A")
  {
  tft.pushImage(20, 160, 150, 150, tin);
  }
  else if (SOS == "B")
  {
    tft.pushImage(20, 160, 150, 150, khang);
  }
  else if (SOS == "C")
  {
    tft.pushImage(20, 160, 150, 150, nguyen);
  }
    else if (SOS == "D")
  {
    tft.pushImage(20, 160, 150, 150, theanh);
  }
    else if (SOS == "E")
  {
    tft.pushImage(20, 160, 150, 150, caominh);
  }
    else if (SOS == "F")
  {
    tft.pushImage(20, 160, 150, 150, ngoctuong);
  }
    else if (SOS == "G")
  {
    tft.pushImage(20, 160, 150, 150, tanloc);
  }
    else if (SOS == "H")
  {
    tft.pushImage(20, 160, 150, 150, hungkiet);
  }
    else if (SOS == "I")
  {
    tft.pushImage(20, 160, 150, 150, ngochai);
  }
    else if (SOS == "J")
  {
    tft.pushImage(20, 160, 150, 150, ngocan);
  }
  tft.pushImage(310, 160, 150, 150, tin_mother);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(168,60);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("GOI THAT BAI");

  tft.setCursor(90,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("MOI BAN NHAN NUT KHAN CAP");

  tft.setCursor(60,130);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("DE LIEN LAC TAI XE LAI LAN NUA");
}

 void goithanhcong_ph()
 {
  tft.fillScreen(TFT_WHITE); //Thiết lập màu nền LCD
  tft.pushImage(190, 185, 100, 100, call_sos);
   if (SOS == "A")
  {
  tft.pushImage(20, 160, 150, 150, tin);
  }
  else if (SOS == "B")
  {
    tft.pushImage(20, 160, 150, 150, khang);
  }
  else if (SOS == "C")
  {
    tft.pushImage(20, 160, 150, 150, nguyen);
  }
    else if (SOS == "D")
  {
    tft.pushImage(20, 160, 150, 150, theanh);
  }
    else if (SOS == "E")
  {
    tft.pushImage(20, 160, 150, 150, caominh);
  }
    else if (SOS == "F")
  {
    tft.pushImage(20, 160, 150, 150, ngoctuong);
  }
    else if (SOS == "G")
  {
    tft.pushImage(20, 160, 150, 150, tanloc);
  }
    else if (SOS == "H")
  {
    tft.pushImage(20, 160, 150, 150, hungkiet);
  }
    else if (SOS == "I")
  {
    tft.pushImage(20, 160, 150, 150, ngochai);
  }
    else if (SOS == "J")
  {
    tft.pushImage(20, 160, 150, 150, ngocan);
  }
  tft.pushImage(310, 160, 150, 150, tin_mother);
  
  tft.setCursor(140,25);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("CUOC GOI KHAN CAP");

  tft.setCursor(158,95);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.printf("GOI THANH CONG");
 }

  void pin() 
 {
  // Đọc giá trị từ chân analog và tính tổng
  for (int i = 0; i < numberOfReadings; i++) {
    total += analogRead(analogInPin);
    delay(0.01); // Đợi một chút giữa các lần đọc
  }
  
  // Tính giá trị trung bình
  float filteredSensorValue = total / numberOfReadings;
  
  // Tính điện áp pin và tỉ lệ sạc dựa trên giá trị đã lọc
  for (int i = 0; i < number_vol; i++) {
    float newVoltage = (((filteredSensorValue) * 3.3 / 4096) * 2 + calibration);
    
    // Kiểm tra sai số và loại bỏ các giá trị nếu cần
    if (i > 0 && abs(newVoltage - previousVoltage) > 0.02) {
      // Bỏ qua giá trị
      continue;
    }
    
    // Lấy giá trị và cập nhật giá trị trước đó
    voltageSum += newVoltage;
    previousVoltage = newVoltage;
    validReadings++;
    delay(0.01); // Đợi một chút giữa các lần tính toán
  }
  
  // Tính giá trị trung bình của voltage
  if (validReadings > 0) {
    voltage = voltageSum / validReadings;
  } else {
    // Không có giá trị hợp lệ
    voltage = 0;
  }

  bat_percentage = mapfloat(voltage, 3.5, 4.1, 0, 100); //2.8V as Battery Cut off Voltage & 4.2V as Maximum Voltage
  if (bat_percentage >= 100) {
    bat_percentage = 100;
  }
  if (bat_percentage <= 0) {
    bat_percentage = 1;
  }

  // In giá trị điện áp và tỉ lệ sạc lên màn hình
    tft.fillRect(252,8, 100, 30, TFT_WHITE);
    tft.fillRect(170,30, 150, 30, TFT_WHITE);
    tft.setCursor(252,8);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(2);
    tft.println((String(bat_percentage) + "%"));
    delay(0.01);
   if (voltage > MIN_USB_VOL)
  { 
    tft.fillRect(252,8, 100, 30, TFT_WHITE);
    tft.pushImage(200, 0, 50, 29, xac);
  }
  else if (bat_percentage > 0 && bat_percentage <= 25)
  {
    tft.pushImage(200, 0, 50, 29, pin_25);
  }
  else if (bat_percentage > 25 && bat_percentage <= 50)
  {
    tft.pushImage(200, 0, 50, 29, pin_50);
  }
  else if (bat_percentage > 50 && bat_percentage <= 75)
  {
    tft.pushImage(200, 0, 50, 29, pin_75);
  }
  else
  {
    tft.pushImage(200, 0, 50, 29, pin_100);
  }  
  total = 0; // Đặt lại tổng về 0 để tính lại trong lần lặp tiếp theo
  delay(0.01); // Đợi 1 giây trước khi lặp lại
 }

 float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void checkhs1() {
    if (Firebase.getString(firebaseData,"/CHECK/HS1")) {
        int newTam1 = firebaseData.stringData().toInt();
        dem1 =  newTam1;
        if (newTam1 != previousTam1) { 
            tam1 = newTam1; 
            previousTam1 = tam1; 
            GPS_Time1();
            return;
        } else {
            GPS_Time1();
            if ( ! mfrc522.PICC_IsNewCardPresent()) 
            { 
              return; 
            }  
            if ( ! mfrc522.PICC_ReadCardSerial()) 
            {  
              return;  
            }  
            Serial.print("UID của thẻ: ");     
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            { 
              Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");       
              UID[i] = mfrc522.uid.uidByte[i];    
              Serial.print(UID[i]); 
            }  
            Serial.println("   ");
            if (nut){ 
            if (UID[i] == ID1[i])
            {   buttonPressCount = 3;
                SOS = "A";
                hocSinh1_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID2[i])
            { 
                buttonPressCount = 3;
                SOS = "B";
                hocSinh2_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID3[i])
            {   buttonPressCount = 3;
                SOS = "C";
                hocSinh3_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID4[i])
            {   buttonPressCount = 3;
                SOS = "D";
                hocSinh4_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID5[i])
            {   buttonPressCount = 3;
                SOS = "E";
                hocSinh5_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID6[i])
            {   buttonPressCount = 3;
                SOS = "F";
                hocSinh6_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID7[i])
            {   buttonPressCount = 3;
                SOS = "G";
                hocSinh7_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID8[i])
            {   buttonPressCount = 3;
                SOS = "H";
                hocSinh8_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID9[i])
            {   buttonPressCount = 3;
                SOS = "I";
                hocSinh9_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID10[i])
            {   buttonPressCount = 3;
                SOS = "J";
                hocSinh10_Sos();
                action = "SC";
                nut = !nut;
            }
            else
            {
                maTheSai();
                nut = !nut;
            }
          }
          else{
            if (UID[i] == ID1[i])
            {
                hocSinh1();
            }
            else if (UID[i] == ID2[i])
            {
                hocSinh2();
            }
            else if (UID[i] == ID3[i])
            {
                hocSinh3();
            }
            else if (UID[i] == ID4[i])
            {
                hocSinh4();
            }
            else if (UID[i] == ID5[i])
            {
                hocSinh5();
            }
            else if (UID[i] == ID6[i])
            {
                hocSinh6();
            }
            else if (UID[i] == ID7[i])
            {
                hocSinh7();
            }
            else if (UID[i] == ID8[i])
            {
                hocSinh8();
            }
            else if (UID[i] == ID9[i])
            {
                hocSinh9();
            }
            else if (UID[i] == ID10[i])
            {
                hocSinh10();
            }
            else if (UID[i] == ID_tx1[i])
            {
                taiXe1();
            }
            else if (UID[i] == ID_tx2[i])
            {
                taiXe2();
            }
            else
            {
                maTheSai();
            }  
            } 
            return;
        }
    }
}

void checkhs2() {
    if (Firebase.getString(firebaseData,"/CHECK/HS2")) {
        int newTam2 = firebaseData.stringData().toInt();
        dem2 =  newTam2;
        if (newTam2 != previousTam2) { 
            tam2 = newTam2; 
            previousTam2 = tam2; 
            GPS_Time1();
            return;
        } else {           
            GPS_Time1();
            if ( ! mfrc522.PICC_IsNewCardPresent()) 
            { 
              return; 
            }  
            if ( ! mfrc522.PICC_ReadCardSerial()) 
            {  
              return;  
            }  
            Serial.print("UID của thẻ: ");     
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            { 
              Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");       
              UID[i] = mfrc522.uid.uidByte[i];    
              Serial.print(UID[i]); 
            }  
            Serial.println("   ");
            if (nut){ 
            if (UID[i] == ID1[i])
            {   buttonPressCount = 3;
                SOS = "A";
                hocSinh1_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID2[i])
            { 
                buttonPressCount = 3;
                SOS = "B";
                hocSinh2_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID3[i])
            {   buttonPressCount = 3;
                SOS = "C";
                hocSinh3_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID4[i])
            {   buttonPressCount = 3;
                SOS = "D";
                hocSinh4_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID5[i])
            {   buttonPressCount = 3;
                SOS = "E";
                hocSinh5_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID6[i])
            {   buttonPressCount = 3;
                SOS = "F";
                hocSinh6_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID7[i])
            {   buttonPressCount = 3;
                SOS = "G";
                hocSinh7_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID8[i])
            {   buttonPressCount = 3;
                SOS = "H";
                hocSinh8_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID9[i])
            {   buttonPressCount = 3;
                SOS = "I";
                hocSinh9_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID10[i])
            {   buttonPressCount = 3;
                SOS = "J";
                hocSinh10_Sos();
                action = "SC";
                nut = !nut;
            }
            else
            {
                maTheSai();
                nut = !nut;
            }
          }
          else{
            if (UID[i] == ID1[i])
            {
                hocSinh1();
            }
            else if (UID[i] == ID2[i])
            {
                hocSinh2();
            }
            else if (UID[i] == ID3[i])
            {
                hocSinh3();
            }
            else if (UID[i] == ID4[i])
            {
                hocSinh4();
            }
            else if (UID[i] == ID5[i])
            {
                hocSinh5();
            }
            else if (UID[i] == ID6[i])
            {
                hocSinh6();
            }
            else if (UID[i] == ID7[i])
            {
                hocSinh7();
            }
            else if (UID[i] == ID8[i])
            {
                hocSinh8();
            }
            else if (UID[i] == ID9[i])
            {
                hocSinh9();
            }
            else if (UID[i] == ID10[i])
            {
                hocSinh10();
            }
            else if (UID[i] == ID_tx1[i])
            {
                taiXe1();
            }
            else if (UID[i] == ID_tx2[i])
            {
                taiXe2();
            }
            else
            {
                maTheSai();
            }  
            } 
            return;
        }
    }
}
void checkhs3() {
    if (Firebase.getString(firebaseData,"/CHECK/HS3")) {
        int newTam3 = firebaseData.stringData().toInt();
        dem3 =  newTam3;
        if (newTam3 != previousTam3) { 
            tam3 = newTam3; 
            previousTam3 = tam3; 
            GPS_Time1();
            return;
        } else {
            GPS_Time1();
            if ( ! mfrc522.PICC_IsNewCardPresent()) 
            { 
              return; 
            }  
            if ( ! mfrc522.PICC_ReadCardSerial()) 
            {  
              return;  
            }  
            Serial.print("UID của thẻ: ");     
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            { 
              Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");       
              UID[i] = mfrc522.uid.uidByte[i];    
              Serial.print(UID[i]); 
            }  
            Serial.println("   ");
            if (nut){ 
            if (UID[i] == ID1[i])
            {   buttonPressCount = 3;
                SOS = "A";
                hocSinh1_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID2[i])
            { 
                buttonPressCount = 3;
                SOS = "B";
                hocSinh2_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID3[i])
            {   buttonPressCount = 3;
                SOS = "C";
                hocSinh3_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID4[i])
            {   buttonPressCount = 3;
                SOS = "D";
                hocSinh4_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID5[i])
            {   buttonPressCount = 3;
                SOS = "E";
                hocSinh5_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID6[i])
            {   buttonPressCount = 3;
                SOS = "F";
                hocSinh6_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID7[i])
            {   buttonPressCount = 3;
                SOS = "G";
                hocSinh7_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID8[i])
            {   buttonPressCount = 3;
                SOS = "H";
                hocSinh8_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID9[i])
            {   buttonPressCount = 3;
                SOS = "I";
                hocSinh9_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID10[i])
            {   buttonPressCount = 3;
                SOS = "J";
                hocSinh10_Sos();
                action = "SC";
                nut = !nut;
            }
            else
            {
                maTheSai();
                nut = !nut;
            }
          }
          else{
            if (UID[i] == ID1[i])
            {
                hocSinh1();
            }
            else if (UID[i] == ID2[i])
            {
                hocSinh2();
            }
            else if (UID[i] == ID3[i])
            {
                hocSinh3();
            }
            else if (UID[i] == ID4[i])
            {
                hocSinh4();
            }
            else if (UID[i] == ID5[i])
            {
                hocSinh5();
            }
            else if (UID[i] == ID6[i])
            {
                hocSinh6();
            }
            else if (UID[i] == ID7[i])
            {
                hocSinh7();
            }
            else if (UID[i] == ID8[i])
            {
                hocSinh8();
            }
            else if (UID[i] == ID9[i])
            {
                hocSinh9();
            }
            else if (UID[i] == ID10[i])
            {
                hocSinh10();
            }
            else if (UID[i] == ID_tx1[i])
            {
                taiXe1();
            }
            else if (UID[i] == ID_tx2[i])
            {
                taiXe2();
            }
            else
            {
                maTheSai();
            }  
            } 
            return;
        }
    }
}

void checkhs4() {
    if (Firebase.getString(firebaseData,"/CHECK/HS4")) {
        int newTam4 = firebaseData.stringData().toInt();
        dem4 =  newTam4;
        if (newTam4 != previousTam4) { 
            tam4 = newTam4; 
            previousTam4 = tam4; 
            GPS_Time1();
            return;
        } else {
            GPS_Time1();
            if ( ! mfrc522.PICC_IsNewCardPresent()) 
            { 
              return; 
            }  
            if ( ! mfrc522.PICC_ReadCardSerial()) 
            {  
              return;  
            }  
            Serial.print("UID của thẻ: ");     
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            { 
              Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");       
              UID[i] = mfrc522.uid.uidByte[i];    
              Serial.print(UID[i]); 
            }  
            Serial.println("   ");
            if (nut){ 
            if (UID[i] == ID1[i])
            {   buttonPressCount = 3;
                SOS = "A";
                hocSinh1_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID2[i])
            { 
                buttonPressCount = 3;
                SOS = "B";
                hocSinh2_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID3[i])
            {   buttonPressCount = 3;
                SOS = "C";
                hocSinh3_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID4[i])
            {   buttonPressCount = 3;
                SOS = "D";
                hocSinh4_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID5[i])
            {   buttonPressCount = 3;
                SOS = "E";
                hocSinh5_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID6[i])
            {   buttonPressCount = 3;
                SOS = "F";
                hocSinh6_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID7[i])
            {   buttonPressCount = 3;
                SOS = "G";
                hocSinh7_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID8[i])
            {   buttonPressCount = 3;
                SOS = "H";
                hocSinh8_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID9[i])
            {   buttonPressCount = 3;
                SOS = "I";
                hocSinh9_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID10[i])
            {   buttonPressCount = 3;
                SOS = "J";
                hocSinh10_Sos();
                action = "SC";
                nut = !nut;
            }
            else
            {
                maTheSai();
                nut = !nut;
            }
          }
          else{
            if (UID[i] == ID1[i])
            {
                hocSinh1();
            }
            else if (UID[i] == ID2[i])
            {
                hocSinh2();
            }
            else if (UID[i] == ID3[i])
            {
                hocSinh3();
            }
            else if (UID[i] == ID4[i])
            {
                hocSinh4();
            }
            else if (UID[i] == ID5[i])
            {
                hocSinh5();
            }
            else if (UID[i] == ID6[i])
            {
                hocSinh6();
            }
            else if (UID[i] == ID7[i])
            {
                hocSinh7();
            }
            else if (UID[i] == ID8[i])
            {
                hocSinh8();
            }
            else if (UID[i] == ID9[i])
            {
                hocSinh9();
            }
            else if (UID[i] == ID10[i])
            {
                hocSinh10();
            }
            else if (UID[i] == ID_tx1[i])
            {
                taiXe1();
            }
            else if (UID[i] == ID_tx2[i])
            {
                taiXe2();
            }
            else
            {
                maTheSai();
            }  
            } 
            return;
        }
    }
}

void checkhs5() {
    if (Firebase.getString(firebaseData,"/CHECK/HS5")) {
        int newTam5 = firebaseData.stringData().toInt();
        dem5 =  newTam5;
        if (newTam5 != previousTam5) { 
            tam5 = newTam5; 
            previousTam5 = tam5; 
            GPS_Time1();
            return;
        } else {
            GPS_Time1();
            if ( ! mfrc522.PICC_IsNewCardPresent()) 
            { 
              return; 
            }  
            if ( ! mfrc522.PICC_ReadCardSerial()) 
            {  
              return;  
            }  
            Serial.print("UID của thẻ: ");     
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            { 
              Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");       
              UID[i] = mfrc522.uid.uidByte[i];    
              Serial.print(UID[i]); 
            }  
            Serial.println("   ");
            if (nut){ 
            if (UID[i] == ID1[i])
            {   buttonPressCount = 3;
                SOS = "A";
                hocSinh1_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID2[i])
            { 
                buttonPressCount = 3;
                SOS = "B";
                hocSinh2_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID3[i])
            {   buttonPressCount = 3;
                SOS = "C";
                hocSinh3_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID4[i])
            {   buttonPressCount = 3;
                SOS = "D";
                hocSinh4_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID5[i])
            {   buttonPressCount = 3;
                SOS = "E";
                hocSinh5_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID6[i])
            {   buttonPressCount = 3;
                SOS = "F";
                hocSinh6_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID7[i])
            {   buttonPressCount = 3;
                SOS = "G";
                hocSinh7_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID8[i])
            {   buttonPressCount = 3;
                SOS = "H";
                hocSinh8_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID9[i])
            {   buttonPressCount = 3;
                SOS = "I";
                hocSinh9_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID10[i])
            {   buttonPressCount = 3;
                SOS = "J";
                hocSinh10_Sos();
                action = "SC";
                nut = !nut;
            }
            else
            {
                maTheSai();
                nut = !nut;
            }
          }
          else{
            if (UID[i] == ID1[i])
            {
                hocSinh1();
            }
            else if (UID[i] == ID2[i])
            {
                hocSinh2();
            }
            else if (UID[i] == ID3[i])
            {
                hocSinh3();
            }
            else if (UID[i] == ID4[i])
            {
                hocSinh4();
            }
            else if (UID[i] == ID5[i])
            {
                hocSinh5();
            }
            else if (UID[i] == ID6[i])
            {
                hocSinh6();
            }
            else if (UID[i] == ID7[i])
            {
                hocSinh7();
            }
            else if (UID[i] == ID8[i])
            {
                hocSinh8();
            }
            else if (UID[i] == ID9[i])
            {
                hocSinh9();
            }
            else if (UID[i] == ID10[i])
            {
                hocSinh10();
            }
            else if (UID[i] == ID_tx1[i])
            {
                taiXe1();
            }
            else if (UID[i] == ID_tx2[i])
            {
                taiXe2();
            }
            else
            {
                maTheSai();
            }  
            } 
            return;
        }
    }
}

void checkhs6() {
    if (Firebase.getString(firebaseData,"/CHECK/HS6")) {
        int newTam6 = firebaseData.stringData().toInt();
        dem6 =  newTam6;
        if (newTam6 != previousTam6) { 
            tam6 = newTam6; 
            previousTam6 = tam6; 
            GPS_Time1();
            return;
        } else {
            GPS_Time1();
            if ( ! mfrc522.PICC_IsNewCardPresent()) 
            { 
              return; 
            }  
            if ( ! mfrc522.PICC_ReadCardSerial()) 
            {  
              return;  
            }  
            Serial.print("UID của thẻ: ");     
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            { 
              Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");       
              UID[i] = mfrc522.uid.uidByte[i];    
              Serial.print(UID[i]); 
            }  
            Serial.println("   ");
            if (nut){ 
            if (UID[i] == ID1[i])
            {   buttonPressCount = 3;
                SOS = "A";
                hocSinh1_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID2[i])
            { 
                buttonPressCount = 3;
                SOS = "B";
                hocSinh2_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID3[i])
            {   buttonPressCount = 3;
                SOS = "C";
                hocSinh3_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID4[i])
            {   buttonPressCount = 3;
                SOS = "D";
                hocSinh4_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID5[i])
            {   buttonPressCount = 3;
                SOS = "E";
                hocSinh5_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID6[i])
            {   buttonPressCount = 3;
                SOS = "F";
                hocSinh6_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID7[i])
            {   buttonPressCount = 3;
                SOS = "G";
                hocSinh7_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID8[i])
            {   buttonPressCount = 3;
                SOS = "H";
                hocSinh8_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID9[i])
            {   buttonPressCount = 3;
                SOS = "I";
                hocSinh9_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID10[i])
            {   buttonPressCount = 3;
                SOS = "J";
                hocSinh10_Sos();
                action = "SC";
                nut = !nut;
            }
            else
            {
                maTheSai();
                nut = !nut;
            }
          }
          else{
            if (UID[i] == ID1[i])
            {
                hocSinh1();
            }
            else if (UID[i] == ID2[i])
            {
                hocSinh2();
            }
            else if (UID[i] == ID3[i])
            {
                hocSinh3();
            }
            else if (UID[i] == ID4[i])
            {
                hocSinh4();
            }
            else if (UID[i] == ID5[i])
            {
                hocSinh5();
            }
            else if (UID[i] == ID6[i])
            {
                hocSinh6();
            }
            else if (UID[i] == ID7[i])
            {
                hocSinh7();
            }
            else if (UID[i] == ID8[i])
            {
                hocSinh8();
            }
            else if (UID[i] == ID9[i])
            {
                hocSinh9();
            }
            else if (UID[i] == ID10[i])
            {
                hocSinh10();
            }
            else if (UID[i] == ID_tx1[i])
            {
                taiXe1();
            }
            else if (UID[i] == ID_tx2[i])
            {
                taiXe2();
            }
            else
            {
                maTheSai();
            }  
            } 
            return;
        }
    }
}

void checkhs7() {
    if (Firebase.getString(firebaseData,"/CHECK/HS7")) {
        int newTam7 = firebaseData.stringData().toInt();
        dem7 =  newTam7;
        if (newTam7 != previousTam7) { 
            tam7 = newTam7; 
            previousTam7 = tam7; 
            GPS_Time1();
            return;
        } else {
            GPS_Time1();
            if ( ! mfrc522.PICC_IsNewCardPresent()) 
            { 
              return; 
            }  
            if ( ! mfrc522.PICC_ReadCardSerial()) 
            {  
              return;  
            }  
            Serial.print("UID của thẻ: ");     
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            { 
              Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");       
              UID[i] = mfrc522.uid.uidByte[i];    
              Serial.print(UID[i]); 
            }  
            Serial.println("   ");
            if (nut){ 
            if (UID[i] == ID1[i])
            {   buttonPressCount = 3;
                SOS = "A";
                hocSinh1_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID2[i])
            { 
                buttonPressCount = 3;
                SOS = "B";
                hocSinh2_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID3[i])
            {   buttonPressCount = 3;
                SOS = "C";
                hocSinh3_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID4[i])
            {   buttonPressCount = 3;
                SOS = "D";
                hocSinh4_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID5[i])
            {   buttonPressCount = 3;
                SOS = "E";
                hocSinh5_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID6[i])
            {   buttonPressCount = 3;
                SOS = "F";
                hocSinh6_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID7[i])
            {   buttonPressCount = 3;
                SOS = "G";
                hocSinh7_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID8[i])
            {   buttonPressCount = 3;
                SOS = "H";
                hocSinh8_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID9[i])
            {   buttonPressCount = 3;
                SOS = "I";
                hocSinh9_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID10[i])
            {   buttonPressCount = 3;
                SOS = "J";
                hocSinh10_Sos();
                action = "SC";
                nut = !nut;
            }
            else
            {
                maTheSai();
                nut = !nut;
            }
          }
          else{
            if (UID[i] == ID1[i])
            {
                hocSinh1();
            }
            else if (UID[i] == ID2[i])
            {
                hocSinh2();
            }
            else if (UID[i] == ID3[i])
            {
                hocSinh3();
            }
            else if (UID[i] == ID4[i])
            {
                hocSinh4();
            }
            else if (UID[i] == ID5[i])
            {
                hocSinh5();
            }
            else if (UID[i] == ID6[i])
            {
                hocSinh6();
            }
            else if (UID[i] == ID7[i])
            {
                hocSinh7();
            }
            else if (UID[i] == ID8[i])
            {
                hocSinh8();
            }
            else if (UID[i] == ID9[i])
            {
                hocSinh9();
            }
            else if (UID[i] == ID10[i])
            {
                hocSinh10();
            }
            else if (UID[i] == ID_tx1[i])
            {
                taiXe1();
            }
            else if (UID[i] == ID_tx2[i])
            {
                taiXe2();
            }
            else
            {
                maTheSai();
            }  
            } 
            return;
        }
    }
}

void checkhs8() {
    if (Firebase.getString(firebaseData,"/CHECK/HS8")) {
        int newTam8 = firebaseData.stringData().toInt();
        dem8 =  newTam8;
        if (newTam8 != previousTam8) { 
            tam8 = newTam8; 
            previousTam8 = tam8; 
            GPS_Time1();
            return;
        } else {
            GPS_Time1();
            if ( ! mfrc522.PICC_IsNewCardPresent()) 
            { 
              return; 
            }  
            if ( ! mfrc522.PICC_ReadCardSerial()) 
            {  
              return;  
            }  
            Serial.print("UID của thẻ: ");     
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            { 
              Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");       
              UID[i] = mfrc522.uid.uidByte[i];    
              Serial.print(UID[i]); 
            }  
            Serial.println("   ");
            if (nut){ 
            if (UID[i] == ID1[i])
            {   buttonPressCount = 3;
                SOS = "A";
                hocSinh1_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID2[i])
            { 
                buttonPressCount = 3;
                SOS = "B";
                hocSinh2_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID3[i])
            {   buttonPressCount = 3;
                SOS = "C";
                hocSinh3_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID4[i])
            {   buttonPressCount = 3;
                SOS = "D";
                hocSinh4_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID5[i])
            {   buttonPressCount = 3;
                SOS = "E";
                hocSinh5_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID6[i])
            {   buttonPressCount = 3;
                SOS = "F";
                hocSinh6_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID7[i])
            {   buttonPressCount = 3;
                SOS = "G";
                hocSinh7_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID8[i])
            {   buttonPressCount = 3;
                SOS = "H";
                hocSinh8_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID9[i])
            {   buttonPressCount = 3;
                SOS = "I";
                hocSinh9_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID10[i])
            {   buttonPressCount = 3;
                SOS = "J";
                hocSinh10_Sos();
                action = "SC";
                nut = !nut;
            }
            else
            {
                maTheSai();
                nut = !nut;
            }
          }
          else{
            if (UID[i] == ID1[i])
            {
                hocSinh1();
            }
            else if (UID[i] == ID2[i])
            {
                hocSinh2();
            }
            else if (UID[i] == ID3[i])
            {
                hocSinh3();
            }
            else if (UID[i] == ID4[i])
            {
                hocSinh4();
            }
            else if (UID[i] == ID5[i])
            {
                hocSinh5();
            }
            else if (UID[i] == ID6[i])
            {
                hocSinh6();
            }
            else if (UID[i] == ID7[i])
            {
                hocSinh7();
            }
            else if (UID[i] == ID8[i])
            {
                hocSinh8();
            }
            else if (UID[i] == ID9[i])
            {
                hocSinh9();
            }
            else if (UID[i] == ID10[i])
            {
                hocSinh10();
            }
            else if (UID[i] == ID_tx1[i])
            {
                taiXe1();
            }
            else if (UID[i] == ID_tx2[i])
            {
                taiXe2();
            }
            else
            {
                maTheSai();
            }  
            } 
            return;
        }
    }
}

void checkhs9() {
    if (Firebase.getString(firebaseData,"/CHECK/HS9")) {
        int newTam9 = firebaseData.stringData().toInt();
        dem9 =  newTam9;
        if (newTam9 != previousTam9) { 
            tam9 = newTam9; 
            previousTam9 = tam9; 
            GPS_Time1();
            return;
        } else {
            GPS_Time1();
            if ( ! mfrc522.PICC_IsNewCardPresent()) 
            { 
              return; 
            }  
            if ( ! mfrc522.PICC_ReadCardSerial()) 
            {  
              return;  
            }  
            Serial.print("UID của thẻ: ");     
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            { 
              Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");       
              UID[i] = mfrc522.uid.uidByte[i];    
              Serial.print(UID[i]); 
            }  
            Serial.println("   ");
            if (nut){ 
            if (UID[i] == ID1[i])
            {   buttonPressCount = 3;
                SOS = "A";
                hocSinh1_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID2[i])
            { 
                buttonPressCount = 3;
                SOS = "B";
                hocSinh2_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID3[i])
            {   buttonPressCount = 3;
                SOS = "C";
                hocSinh3_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID4[i])
            {   buttonPressCount = 3;
                SOS = "D";
                hocSinh4_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID5[i])
            {   buttonPressCount = 3;
                SOS = "E";
                hocSinh5_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID6[i])
            {   buttonPressCount = 3;
                SOS = "F";
                hocSinh6_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID7[i])
            {   buttonPressCount = 3;
                SOS = "G";
                hocSinh7_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID8[i])
            {   buttonPressCount = 3;
                SOS = "H";
                hocSinh8_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID9[i])
            {   buttonPressCount = 3;
                SOS = "I";
                hocSinh9_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID10[i])
            {   buttonPressCount = 3;
                SOS = "J";
                hocSinh10_Sos();
                action = "SC";
                nut = !nut;
            }
            else
            {
                maTheSai();
                nut = !nut;
            }
          }
          else{
            if (UID[i] == ID1[i])
            {
                hocSinh1();
            }
            else if (UID[i] == ID2[i])
            {
                hocSinh2();
            }
            else if (UID[i] == ID3[i])
            {
                hocSinh3();
            }
            else if (UID[i] == ID4[i])
            {
                hocSinh4();
            }
            else if (UID[i] == ID5[i])
            {
                hocSinh5();
            }
            else if (UID[i] == ID6[i])
            {
                hocSinh6();
            }
            else if (UID[i] == ID7[i])
            {
                hocSinh7();
            }
            else if (UID[i] == ID8[i])
            {
                hocSinh8();
            }
            else if (UID[i] == ID9[i])
            {
                hocSinh9();
            }
            else if (UID[i] == ID10[i])
            {
                hocSinh10();
            }
            else if (UID[i] == ID_tx1[i])
            {
                taiXe1();
            }
            else if (UID[i] == ID_tx2[i])
            {
                taiXe2();
            }
            else
            {
                maTheSai();
            }  
            } 
            return;
        }
    }
}

void checkhs10() {
    if (Firebase.getString(firebaseData,"/CHECK/HS10")) {
        int newTam10 = firebaseData.stringData().toInt();
            dem10 =  newTam10;
        if (newTam10 != previousTam10) { 
            tam10 = newTam10; 
            previousTam10 = tam10;
            GPS_Time1();
            return;
        } else {
            GPS_Time1();
            if ( ! mfrc522.PICC_IsNewCardPresent()) 
            { 
              return; 
            }  
            if ( ! mfrc522.PICC_ReadCardSerial()) 
            {  
              return;  
            }  
            Serial.print("UID của thẻ: ");     
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            { 
              Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");       
              UID[i] = mfrc522.uid.uidByte[i];    
              Serial.print(UID[i]); 
            }  
            Serial.println("   ");
            if (nut){ 
            if (UID[i] == ID1[i])
            {   buttonPressCount = 3;
                SOS = "A";
                hocSinh1_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID2[i])
            { 
                buttonPressCount = 3;
                SOS = "B";
                hocSinh2_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID3[i])
            {   buttonPressCount = 3;
                SOS = "C";
                hocSinh3_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID4[i])
            {   buttonPressCount = 3;
                SOS = "D";
                hocSinh4_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID5[i])
            {   buttonPressCount = 3;
                SOS = "E";
                hocSinh5_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID6[i])
            {   buttonPressCount = 3;
                SOS = "F";
                hocSinh6_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID7[i])
            {   buttonPressCount = 3;
                SOS = "G";
                hocSinh7_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID8[i])
            {   buttonPressCount = 3;
                SOS = "H";
                hocSinh8_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID9[i])
            {   buttonPressCount = 3;
                SOS = "I";
                hocSinh9_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID10[i])
            {   buttonPressCount = 3;
                SOS = "J";
                hocSinh10_Sos();
                action = "SC";
                nut = !nut;
            }
            else
            {
                maTheSai();
                nut = !nut;
            }
          }
          else{
            if (UID[i] == ID1[i])
            {
                hocSinh1();
            }
            else if (UID[i] == ID2[i])
            {
                hocSinh2();
            }
            else if (UID[i] == ID3[i])
            {
                hocSinh3();
            }
            else if (UID[i] == ID4[i])
            {
                hocSinh4();
            }
            else if (UID[i] == ID5[i])
            {
                hocSinh5();
            }
            else if (UID[i] == ID6[i])
            {
                hocSinh6();
            }
            else if (UID[i] == ID7[i])
            {
                hocSinh7();
            }
            else if (UID[i] == ID8[i])
            {
                hocSinh8();
            }
            else if (UID[i] == ID9[i])
            {
                hocSinh9();
            }
            else if (UID[i] == ID10[i])
            {
                hocSinh10();
            }
            else if (UID[i] == ID_tx1[i])
            {
                taiXe1();
            }
            else if (UID[i] == ID_tx2[i])
            {
                taiXe2();
            }
            else
            {
                maTheSai();
            }  
            } 
            return;
        }
    }
}


void checktx1() {
    if (Firebase.getString(firebaseData,"/CHECK/TX1")) {
        int newTam11 = firebaseData.stringData().toInt();
            demtx1 =  newTam11;
        if (newTam11 != previousTamtx1) {  
            tamtx1 = newTam11; 
            previousTamtx1 = tamtx1;
            GPS_Time1();
            return;
        } else {
            GPS_Time1();
            if ( ! mfrc522.PICC_IsNewCardPresent()) 
            { 
              return; 
            }  
            if ( ! mfrc522.PICC_ReadCardSerial()) 
            {  
              return;  
            }  
            Serial.print("UID của thẻ: ");     
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            { 
              Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");       
              UID[i] = mfrc522.uid.uidByte[i];    
              Serial.print(UID[i]); 
            }  
            Serial.println("   ");
            if (nut){ 
            if (UID[i] == ID1[i])
            {   buttonPressCount = 3;
                SOS = "A";
                hocSinh1_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID2[i])
            { 
                buttonPressCount = 3;
                SOS = "B";
                hocSinh2_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID3[i])
            {   buttonPressCount = 3;
                SOS = "C";
                hocSinh3_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID4[i])
            {   buttonPressCount = 3;
                SOS = "D";
                hocSinh4_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID5[i])
            {   buttonPressCount = 3;
                SOS = "E";
                hocSinh5_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID6[i])
            {   buttonPressCount = 3;
                SOS = "F";
                hocSinh6_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID7[i])
            {   buttonPressCount = 3;
                SOS = "G";
                hocSinh7_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID8[i])
            {   buttonPressCount = 3;
                SOS = "H";
                hocSinh8_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID9[i])
            {   buttonPressCount = 3;
                SOS = "I";
                hocSinh9_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID10[i])
            {   buttonPressCount = 3;
                SOS = "J";
                hocSinh10_Sos();
                action = "SC";
                nut = !nut;
            }
            else
            {
                maTheSai();
                nut = !nut;
            }
          }
          else{
            if (UID[i] == ID1[i])
            {
                hocSinh1();
            }
            else if (UID[i] == ID2[i])
            {
                hocSinh2();
            }
            else if (UID[i] == ID3[i])
            {
                hocSinh3();
            }
            else if (UID[i] == ID4[i])
            {
                hocSinh4();
            }
            else if (UID[i] == ID5[i])
            {
                hocSinh5();
            }
            else if (UID[i] == ID6[i])
            {
                hocSinh6();
            }
            else if (UID[i] == ID7[i])
            {
                hocSinh7();
            }
            else if (UID[i] == ID8[i])
            {
                hocSinh8();
            }
            else if (UID[i] == ID9[i])
            {
                hocSinh9();
            }
            else if (UID[i] == ID10[i])
            {
                hocSinh10();
            }
            else if (UID[i] == ID_tx1[i])
            {
                taiXe1();
            }
            else if (UID[i] == ID_tx2[i])
            {
                taiXe2();
            }
            else
            {
                maTheSai();
            }  
            } 
            return;
        }
    }
}

void checktx2() {
    if (Firebase.getString(firebaseData,"/CHECK/TX2")) {
        int newTam12 = firebaseData.stringData().toInt();
            demtx2 =  newTam12;
        if (newTam12 != previousTamtx2) {  
            tamtx2 = newTam12; 
            previousTamtx2 = tamtx2;
            GPS_Time1();
            return;
        } else {
            GPS_Time1();
            if ( ! mfrc522.PICC_IsNewCardPresent()) 
            { 
              return; 
            }  
            if ( ! mfrc522.PICC_ReadCardSerial()) 
            {  
              return;  
            }  
            Serial.print("UID của thẻ: ");     
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            { 
              Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");       
              UID[i] = mfrc522.uid.uidByte[i];    
              Serial.print(UID[i]); 
            }  
            Serial.println("   ");
            if (nut){ 
            if (UID[i] == ID1[i])
            {   buttonPressCount = 3;
                SOS = "A";
                hocSinh1_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID2[i])
            { 
                buttonPressCount = 3;
                SOS = "B";
                hocSinh2_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID3[i])
            {   buttonPressCount = 3;
                SOS = "C";
                hocSinh3_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID4[i])
            {   buttonPressCount = 3;
                SOS = "D";
                hocSinh4_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID5[i])
            {   buttonPressCount = 3;
                SOS = "E";
                hocSinh5_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID6[i])
            {   buttonPressCount = 3;
                SOS = "F";
                hocSinh6_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID7[i])
            {   buttonPressCount = 3;
                SOS = "G";
                hocSinh7_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID8[i])
            {   buttonPressCount = 3;
                SOS = "H";
                hocSinh8_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID9[i])
            {   buttonPressCount = 3;
                SOS = "I";
                hocSinh9_Sos();
                action = "SC";
                nut = !nut;
            }
            else if (UID[i] == ID10[i])
            {   buttonPressCount = 3;
                SOS = "J";
                hocSinh10_Sos();
                action = "SC";
                nut = !nut;
            }
            else
            {
                maTheSai();
                nut = !nut;
            }
          }
          else{
            if (UID[i] == ID1[i])
            {
                hocSinh1();
            }
            else if (UID[i] == ID2[i])
            {
                hocSinh2();
            }
            else if (UID[i] == ID3[i])
            {
                hocSinh3();
            }
            else if (UID[i] == ID4[i])
            {
                hocSinh4();
            }
            else if (UID[i] == ID5[i])
            {
                hocSinh5();
            }
            else if (UID[i] == ID6[i])
            {
                hocSinh6();
            }
            else if (UID[i] == ID7[i])
            {
                hocSinh7();
            }
            else if (UID[i] == ID8[i])
            {
                hocSinh8();
            }
            else if (UID[i] == ID9[i])
            {
                hocSinh9();
            }
            else if (UID[i] == ID10[i])
            {
                hocSinh10();
            }
            else if (UID[i] == ID_tx1[i])
            {
                taiXe1();
            }
            else if (UID[i] == ID_tx2[i])
            {
                taiXe2();
            }
            else
            {
                maTheSai();
            }  
            } 
            return;
        }
    }
}

void GPS_NO()
{
       for (int i = 0; i<frames_GPS_LOST; i++)
    {
    tft.pushImage(170,0,animation_width_GPS,animation_height_GPS, GPS_LOST[i]);
    }
}

void GPS_check()
{
       for (int i = 0;i<frames_GPS_OK; i++)
    {
    tft.pushImage(170,0,animation_width_GPS_OK,animation_height_GPS_OK, GPS_OK[i]); 
    }

}
