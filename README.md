# Shellcode-analyzer

## requirements
OS:Linux (Unix-like)
Tkinter (python3-tk)

## Install on Arch Linux
sudo pacman -S python tk

## install on Fedora
sudo dnf install python3 python3-tkinter

## GUI mode
Python3 scgui.py 

![GUI Screenshot] https://github.com/3MPER0RR/Shellcode-analyzer/blob/b42cae0a69b539ba526be41e18d338c7363e52b0/scgui.png

## Cli mode
./sc_analyzer shellcodesample.bin
Supports .bin and .dat raw shellcode files


## Project structure:
├── sc_analyzer        # C core analyzer

├── scgui.py            # Python GUI frontend

└── samples/            # Example shellcode .bin files

## ⚠️​ The analyzer performs static analysis only.
## Shellcode is never executed.
