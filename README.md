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

## Cli mode
./sc_analyzer shellcodesample.bin
Supports .bin and .dat raw shellcode files


## Project structure:
├── sc_analyzer        # C core analyzer

├── scgui.py            # Python GUI frontend

└── samples/            # Example shellcode .bin files

## ⚠️​ The analyzer performs static analysis only.
## Shellcode is never executed.
