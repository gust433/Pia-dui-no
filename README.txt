ผู้พัฒนา:
	นายกฤษฎี ทองบ้านเกาะ
	นายชยพล กุลวงศ์วรพัฒน์
	นายประตินันท์ ชูชื่น
	นายสิรวิชญ์ นนทกนก
	
วิชาการพัฒนาฮาร์ดแวร์คอมพิวเตอร์เบื้องต้น ภาควิชาวิศวกรรมคอมพิวเตอร์ คณะวิศวกรรมศาสตร์ มหาวิทยาลัยเกษตรศาสตร์

ช้อมูลในโฟลเดอร์ :
- schematic
- Folder piano 
	- piano.ino (Arduino ของบอร์ดที่ 1)
	- config.h ของ piano.ino
	- Folder PlaySound
		- Folder Node-RED : flows.json
		- Folder not_use_note (ไฟล์เสียงไม่ใช้/สำรอง)
		- playnotesound.py (รันตัว python ธรรมดาได้เลย)
		- ไฟล์เสียง
- Folder board2
	- board2.ino (Arduino ของบอร์ดที่ 2)
	- config.h ของ board2.ino 

Libary :
	Arduino

	- Adafruit BusIO by Adafruit
	- Adafruit GFX Library by Adafruit
	- Adafruit SSD1306
	- PubSubClient by Nick O'Leary

	Python

	- pygame
	- Serial
	- Thread

Hardware : 
	- ESP32-S3 x2
	- OLED x1
	- LED x15 (7 ชิ้นสีเดียวกัน)
	- หมุดติดกระดาษ x12
	- กระดาษอัด x1
	- เทปอลูมิเนียม
	- เทปฟอยล์ทองแดง
	- Breadboard x2
	