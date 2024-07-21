Hello AVR este un proiect menit a servi drept introducere în lumea sistemelor incorporate și a arhitecturii AVR. Acesta se bazeaza pe cursul de Interfete si Protocoale de Comunicatie oferit de Facultatea de Inginerie din Universitatea Lucian Blaga din Sibiu  
Proiectul a pornit din initiativa lui Neag Mihai si Saldorfean Andrei

Structura:
|__asamblare     cod scris in AVR assembly
|__c             cod scris in C
|__configurare   folosit pentru a inlesni procesul de configurare a proiectelor
|__documentatie  documentatie ce cuprinde informatii despre hardware/software si proces(sistem       
|                versionare,make ...)
|__template      sablon al unui proiect
|_schematic.pdf  diagrama a circuitului electric folosit la laboratorul de  Interfete si Protocoale de 
                 Comunicatie

Conventii:
    HW/SW: Hardware/Software
    _old: proiecte create folosind aplicatia AtmelStudio

Configurare:
    Pentru a creea aplicatii exista doua abordari.Fie se poate folosi ATmelStudio (numit acum MicrochipStudio) cu toate utilitarele configurate (in afara de avrdude; vezi configurare>setup_ATmelStudio.txt), fie se pot folosi direct cu acele utilitare in combinatie cu un makefile (vezi configurare>setup_toolchain.txt).

Creare proiect:
    Pentru aceasta s-a pus la dispozitia programatorului un script menit a automatiza acest proces (create_proj.py).

Compilare/Asamblare proiect:
    In cadrul fiecarui proiect va fi prezent fisierul 'Makefile' menit a automatiza procesele de compilare,asamblare,link-editare....
    Sunt oferite programatorului urmatoarele comenzi:
        make: compilare/asamblare proiect
        make clean: curatare proiect
        make com: initializare comunicare cu PC-ul pe portul serial 