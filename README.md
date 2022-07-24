# UEFIStudy
Here is the code I wrote in the process of learning UEFI. My goal is to write a complete OS Loader to boot the operating system in the U disk.

At present, there is a preliminary graphical interactive interface for booting, and a simple elf file with input can be started. The next goal is to improve the interface and increase the functionality of the operating system.

Current OS Loader progress:
* Interface for boot service
* File Reader
* MemoryMap

Current OS development progress:
* Interface for Shell
* Can print single letter
  * Can print string, HEX and DEC number
* Get MemoryMap from OS Loader

This is the source code under UEFI specification and EDK2.
