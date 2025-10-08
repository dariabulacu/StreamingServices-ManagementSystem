# StreamingServices-ManagementSystem

Un proiect C++ pentru gestionarea simplă a serviciilor de streaming și a abonamentelor asociate. Proiectul este construit ca aplicație console (text-based) și folosește fișiere text ca stocare de date, fiind potrivit pentru exerciții didactice, prototipuri și învățare C++.

## Scopul proiectului

Scopul este de a oferi o aplicație minimalistă care permite simularea funcționalităților de bază ale unui sistem de management al serviciilor de streaming:

- definire și listare servicii de streaming (de ex. Netflix, HBO)
- gestionare abonamente (creare, modificare, anulare)
- gestionare programe/episoade asociate serviciilor
- interfață de tip meniu în consolă pentru operații CRUD simple

Proiectul este util pentru a demonstra lucrul cu fișiere în C++, separarea logicii în module (header + sursă), și pentru a exersa compilarea în mediul Windows.

## Funcționalități principale

- Meniu principal cu opțiuni pentru: vizualizare servicii, adăugare serviciu, vizualizare abonamente, adăugare abonament, vizualizare programe, adăugare program, salvare/încărcare date.
- Stocare simplă în fișiere text (format liniar), fără bază de date.
- Modularizare de cod: `main.cpp` + `Menu` (header + impl)

## Structura proiect

- `main.cpp` — punctul de intrare al aplicației
- `include/Menu.h` — declarațiile claselor/funcțiilor pentru meniuri
- `src/Menu.cpp` — implementarea funcționalităților meniu
- `abonament.txt` — fișier pentru stocarea abonamentelor
- `programe.txt` — fișier pentru stocarea programelor/episoadelor
- `streaming_services.txt` — fișier pentru lista serviciilor
- `proiect.cbp` — fișier proiect Code::Blocks (opțional)
- `bin/Debug/` și `obj/Debug/` — directoare generate la build

> Notă: structura reală a proiectului poate conține și alte fișiere generate automat (executable, obiecte). Păstrează copia surselor (`.cpp`, `.h`) în controlul versiunilor.

## Exemplu — fluxuri de utilizare (user stories)

1. Ca utilizator, pot vedea lista serviciilor disponibile.
2. Ca administrator, pot adăuga un nou serviciu de streaming.
3. Ca utilizator, pot crea un abonament pentru un serviciu.
4. Ca administrator, pot adăuga un program/episod asociat unui serviciu.

Aceste fluxuri sunt accesibile din meniul aplicației.

## Formate sugerate pentru fișierele `.txt`

Fișierele pot avea un format simplu pe linii, de exemplu (aceasta este doar o convenție; codul proiectului poate folosi un format propriu — verifică `src/Menu.cpp` pentru exactitate):

- `streaming_services.txt` (fiecare linie):

  serviciu_id|nume_serviciu|descriere

  Exemplu:

  1|Netflix|Serviciu de streaming filme și seriale
  2|HBO|Seriale și filme premium

- `abonament.txt` (fiecare linie):

  abonament_id|serviciu_id|nume_utilizator|tip_abonament|data_inceput|data_sfarsit

  Exemplu:

  1|1|Ion Popescu|Lunar|2025-01-10|2025-02-10

- `programe.txt` (fiecare linie):

  program_id|serviciu_id|titlu|durata_min|gen

  Exemplu:

  1|1|Stranger Things - S1E1|50|Sci-Fi

Dacă vrei, pot adapta README să reflecte formatul exact folosit de cod (pot parsa `src/Menu.cpp` și deduce structurile folosite).

## Cerințe și mediu de dezvoltare

- OS: Windows (instrucțiuni pentru PowerShell)
- Compiler: MinGW/g++ recomandat sau Code::Blocks
- Standard C++: C++11 (sau versiune ulterior specificată în proiect)

## Compilare (MinGW/g++)

Deschide PowerShell în directorul proiectului și rulează unul dintre comenzile de mai jos:

```powershell
# Build în folderul bin\Debug
g++ -std=c++11 -Iinclude main.cpp src/Menu.cpp -O2 -o bin\Debug\proiect.exe

# Build în directorul curent (proiect.exe)
g++ -std=c++11 -Iinclude main.cpp src/Menu.cpp -O2 -o proiect.exe
```

Dacă folosești un layout diferit al fișierelor sursă, ajustează lista de fișiere din comandă.

## Rulare

După build, pornește executabilul din PowerShell:

```powershell
bin\Debug\proiect.exe
# sau
.\proiect.exe
```

Programul va afișa meniul în consolă. Urmează instrucțiunile din meniu pentru adăugare/listare/modificare.

## Debugging & dezvoltare

- Dacă apar erori legate de include-uri, verifică calea `-Iinclude` și existența fișierului `include/Menu.h`.
- Folosește un IDE (Code::Blocks) pentru depanare pas-cu-pas.
- Curăță binarele vechi când faci schimbări majore: șterge `bin/` și `obj/` și recompilează.

