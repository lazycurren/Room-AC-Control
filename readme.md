
### What this is:

#### An electronics project using ESP32 to apply a sophisticated and precise climate control algorithm on any Residential Air Conditioning Unit using Infrared Communication.

### Why it exists:

Residential air conditioning in India is usually standalone units that are separate for each room. These are of two types in most if not all cases: Mini-split or Window ACs. Every single model of both these types from every major manufacturer has always, in my experience, lacked a very essential characteristic: having the ability to maintain a pre-set level of air temperature and therefore comfort with a reasonable degree of precision. The remote controls for these units generally feature lots of buttons and supposed settings for the AC unit but in reality, however, the AC itself has 2-4 speed settings for the blower motor and 2 settings for the compressor unit itself; ON or OFF. The ability to translate these apparently intricate settings available on the remote-control rests solely on the control circuitry present in Air conditioning, which, in most cases is far too rudimentary to actually be able to achieve that. This results in poor comfort level; the room gets too cold or too warm without intermittent manual intervention. It was after years of enduring this stupidity that I resolved to fix this problem once and for all using science and my engineering skills. Once I built it, which was not easy, lots of troubles along the way, I was only left feeling I had done it sooner. Self-doubt is the greatest foe. This device works flawlessly for me, and I no longer wake up with a bad head cold every 3 days like I used to.

### How it works:

1. Basic infrared commands (like compressor ON/OFF, Fan Speed) from the remote control are first scanned and their codes are saved. 
2. An algorithm takes in accurate temperature data from sensitive, high quality weather sensors, placed in the room.
3. This algorithm then decides what commands to send to the AC unit based on this room temperature data using Infrared, emulating the remote control, thereby acting as a high-quality climate control circuitry for the AC present outside the AC unit, which the units themselves do not possess.

### Hardware 

#### (You may use similar components; they don’t have to be these exactly. I just used whatever I had access to):

- 1x Arduino Mega 2560 Rev3 (Basic Testing and IR Code Scanning Circuits)
- 1x NodeMCU ESP32-DOIT-DEV-KIT-v1 (Main Controller)
- 3x HTU21D (Weather Sensors. Use digital, accurate high-quality sensors only and more than one to increase redundancy and accuracy of measurement. HDC1080 is the best. BME280, HTU21D, SHT31 are good enough. DHT1x series, AM23xx series are trash.)
- 1x RPM-7240-H4 (Infrared Code Scanning Module)
- 1x 128x64 4pin I2C OLED Display (For Visual Output)
- 3x Generic Buttons (To control the Menu and feed settings into the EEPROM)
- 4x Generic IR LEDs (For IR Output. 4 for High Output)
- 1x BD139 (Generic Amplifying transistor for the IR LEDs)
