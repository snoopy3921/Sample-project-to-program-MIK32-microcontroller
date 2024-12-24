# Sample project using makefile to develop application for MIK32-Mikron microcontroller.
Пример проекта с использованием make-файла для разработки приложений для микроконтроллера MIK32 - Микрон.

<img src="https://github.com/user-attachments/assets/b5e021a9-604f-45d6-a489-c911cb6e1dfc" width="200">


# Требования
Образец тестировался на плате Skrepka v1.0 с разъемом JTAG.

+ Linux Ubuntu 22.04 LTS. 
+ Toolchain for RISC-V architecture. (https://github.com/riscv-collab/riscv-gnu-toolchain)
+ Драйвер Jlink установлен.
+ OpenOCD установлен. (https://github.com/openocd-org/openocd)
+ Make установлен. 

В примере использованы HAL, компоновщик, файлы запуска от Микрона.

+ Mik32v2-shared (https://github.com/MikronMIK32/mik32v2-shared)
+ Mik32-hal (https://github.com/MikronMIK32/mik32-hal)
+ Mik32-uploader (https://github.com/MikronMIK32/mik32-uploader)

Для изменения параметры загрузки
Раскомментируйте и измените загрузочный контакт на плате.
```Makefile
  LDFILE 		= $(SHARED_DIR)/ldscripts/spifi.lds
  #LDFILE 		= $(SHARED_DIR)/ldscripts/eeprom.lds
  #LDFILE 		= $(SHARED_DIR)/ldscripts/ram.lds
```

Для компиляции проекта: 
```
  $ make
```


Загрузка кода в микроконтроллер:
```
  $ make upload
```
