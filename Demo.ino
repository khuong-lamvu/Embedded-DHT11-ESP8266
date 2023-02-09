#include <ESP8266WebServer.h> //Thư viện ESP8266WebServer
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

#include "index.h" //Nhúng trang index.h 
//Thêm thư viện DHT11 và khai báo chân DHT
#include <DHT.h>
#define chan_dht D3 //Chân DHT
#define loai_dht DHT11  //Loại Module DHT11
DHT dht(chan_dht, loai_dht);
//Khởi tạo cổng cho WebServer
ESP8266WebServer Server(80);

float nhietdo = 0.0;
float doam = 0.0;

const String nameWifi = "KhuongLamVu"; // Tên Wifi
const String passWifi = "password"; // Mật khẩu Wifi

//Tạo 1 kết nối đến index page
void KetNoi() {
    Serial.println("You called index page");
    String s = MAIN_page; //index.h
    nhietdo = dht.readTemperature(); 
    doam = dht.readHumidity(); 
//Serial.println(s);
//String s = "<html><head><title>Main Page</title></head><body>Trang chu</body></html>";
    Server.send(200, "text/html", s); //Send to Web
}

//Đọc dữ liệu nhiệt độ
void readDataTemperature(){
  nhietdo = dht.readTemperature(); 
  String s_nhietdo = String(nhietdo);
  if(isnan(nhietdo)){
    Server.send(200,"text/plain","Sensor not working!");
    Serial.println("Sensor not working!");
  }
  else{
    Server.send(200,"text/plain",s_nhietdo);
    Serial.print("Nhiet do: ");
    Serial.print(String(nhietdo));
    Serial.println("*C");
  }
}

//Đọc dữ liệu độ ẩm
void readDataHumidity(){
  doam = dht.readHumidity();
  String s_doam = String(doam);
  if(isnan(doam)){
    Server.send(200,"text/plain","Sensor not working!");
    Serial.println("Sensor not working!");
  }
  else{
    Server.send(200,"text/plain",s_doam);
    Serial.print("Do am: ");
    Serial.print(String(doam));
    Serial.println("%");
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);
  pinMode(chan_dht, INPUT);
  dht.begin();
  Wire.begin(D2, D1);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(2,0);
  //Kết nối ESP8266 với WiFi cục bộ
  Serial.println("----------------------------------------------------------------");
  Serial.print("Connecting to WiFi: ");
  Serial.println(nameWifi);
  lcd.print("Connecting...");
  Serial.println("----------------------------------------------------------------");
  WiFi.begin(nameWifi, passWifi);
  while (WiFi.status() != WL_CONNECTED){ //Trạng thái kết nối
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print(".");
    Serial.print(".");    
  }
  Serial.println("");
  Serial.println("WiFi is Connected Successfully");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("HTTP Server started");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your IP Address");
  lcd.setCursor(1, 1);
  lcd.print(WiFi.localIP());
  delay(4000);

  //Khởi tạo đường link để truy cập trang Web Server
  Server.on("/", KetNoi);
  //Khởi tạo đường link để truy cập đọc dữ liệu nhiệt độ
  Server.on("/docnhietdo", readDataTemperature);
  //Khởi tạo đường link để truy cập đọc dữ liệu độ ẩm
  Server.on("/docdoam", readDataHumidity);
  //Khởi tạo Server
  Server.begin(); //Khởi động Server
}

void loop() {
  // put your main code here, to run repeatedly:
  // Thực hiện các yêu cầu từ Client bởi hàm handleClient()
  Server.handleClient();
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Monitor T & H");
  lcd.setCursor(0, 1);
  lcd.print(nhietdo);
  lcd.print("*C");
  lcd.print(" - ");
  lcd.print(doam);
  lcd.print("%");
  delay(1000);    
}
