I.
Am ignorat folder-ul .vscode pentru ca atunci cand vrei sa scri cod in vscode trebuie sa incluzi librariile cu care lucrezi, pentru ca intellisense-ul sa functioneze (adica sa ai autocomplete).

Exemplu:

Vrei sa folosesti o librarie care se afla in afara workspace-ului din vscode. Libraria se afla in "C:\Users\user\Documents\lib" si acolo ai niste headere care in mod normal vscode-ul nu ti le recunoaste. Pentru a avea autocomplete la header-ele alea, si pentru a le putea compila, trebuie sa:

1.Creezi un folder .vscode
2.Creezi un fisier "c_cpp_properties.json" in .vscode care va contine:

{
    "configurations": [
        {
            "name": "AVR",
            "includePath": [
                "${workspaceFolder}/**",
                "C:\Users\user\Documents\lib" <===== Aici incluzi cate path-uri vrei pentru ca ide-ul sa recunoasca fisierele
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "forcedInclude": [
                "C:\Users\user\Documents\lib\header.h" <===== Aici poti include fisiere individuale (optional*)
            ],
            "compilerPath": "path/to/compiler",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "gcc-x64"
        }
    ],
    "version": 4
}

3.Enjoy

And that's it for intellisense

II.
Sunt sanse mici ca Makefile-ul sa functioneze din prima deoarece tool-urile (compiler-ul, assembler-ul, linker-ul si flasher-ul) trebuie adaugate in environment variables. Daca ai deja instalat Arduino sau Atmel studio poti cauta in file explorer pentru "avr-gcc", "avr-obj" si "avr-dude". "avrasm2" vine doar cu Atmel Studio si nu am gasit un link pentru download (nu am cautat foarte mult).
Dupa ce ai pus toate tool-urile in env. var. poti folosi makefile-ul pentru fisiere C/C++, dara vrei sa scrii si cod in asamblare trebuie la flag-urile de -I sa adaugi si un path catre fisierele .inc (daca nu merge deja path-ul din makefile).

And that's it for the tools

III.
Te rog ca in template sa nu lucrii, poti face modificari daca gasesti un bug sau daca vrei sa faci un improvement pentru template.
Copiaza Template-ul si fa-ti un workspace cu un nume sugestiv (eg. Display_via_spi).