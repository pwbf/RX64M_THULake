THU THULake  
====  
## Frontend demo: THULake [>> Link](http://140.128.98.55:3000/d/QrAuefeWk/dong-hai-aiot-shui-zhi-bang-zi-lora?orgId=1&refresh=5s)  
  
#### Lastest Version: v2.patch201207A  
- [x] Status LED(PWR, LoRa join, LoRaTx, LoRaRx, SensTx, SensRx, EdgeCom, Error)  
- [x] LoRa publish(per 1min)  
- [x] Sensor read(per 10sec)  
- [x] Edge computing(every round)  
  
# Update Log>>  
> # Version 2
>> ## v2.patch201218A
>> #### Fixed: Water Temp floating 
>> ## v2.patch201207A
>> #### Fixed: Switching to new sensor not working properly(Overflow)  
>> #### Added: Mode switch  
```cpp  
//src/main_self.h
#define MODE_SEA_WATER (0)
// 0 for normal water, 1 for sea water
```  
>> ## v2.patch200915A
>> #### Fixed: Status LED  
>> ## v2.patch200914A
>> #### Fixed: Array addressing problem  
>> #### Fixed: WatchDog stop working  
>> #### Added: Pointer replace array  
>> #### Added: Tidy up source code  
>> #### Added: Accurate timing  
>> #### Added: Optimizing code performance  
> # Version 1
>> ## v1.patch200425A
>>> - [x] RX64M <- Sensor
>>> - [x] LoRa <- RX64M
>>> - [x] LoRa <- RX64M <- Sensor
>> ## v1.patch200423B
>>> - [x] RX64M <- Sensor
>>> - [x] LoRa <- RX64M
>>> - [ ] LoRa <- RX64M <- Sensor
>> ## v1.patch200423A
>>> - [x] RX64M <- Sensor
>>> - [ ] LoRa <- RX64M
>>> - [ ] LoRa <- RX64M <- Sensor