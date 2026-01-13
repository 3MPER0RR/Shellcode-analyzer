# Shellcode-analyzer

## requirements
OS:Linux (Unix-like)
Tkinter (python3-tk)

## Tested on Linux Debian

## Install on Arch Linux
sudo pacman -S python tk

## install on Fedora
sudo dnf install python3 python3-tkinter

## Project structure:
├── sc_analyzer        # C core analyzer

├── scgui.py            # Python GUI frontend

└── samples/            # Example shellcode .bin files

## Cli mode
./sc_analyzer shellcodesample.bin
Supports .bin and .dat raw shellcode files

![Shellcode Analyzer CLI](sc_analyzer.png)

## GUI mode
Python3 scgui.py 

![Shellcode Analyzer GUI](scgui.png)


## ⚠️​ The analyzer performs static analysis only.
## Shellcode is never executed.
