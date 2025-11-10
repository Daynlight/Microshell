# Microshell – Specyfikacja Wymagań

**Przedmiot:** Systemy operacyjne  
**Projekt:** Microshell  
**Język programowania:** C (ANSI C, C99, C17 lub nowszy)  
**Plik źródłowy:** `microshell.c`  
**Dodatkowo:** opcjonalnie `Makefile`  

---

## Cel projektu

Stworzenie prostej powłoki systemu operacyjnego działającej pod Linuksem. Powłoka ma przyjmować od użytkownika polecenia, interpretować je oraz wykonywać odpowiednie działania.

Do zaliczenia wystarczy zdobyć **min. 18 punktów** – czyli zrealizować wszystkie elementy obowiązkowe.

---

## Wymagania funkcjonalne

| Punkty | Status       | Opis |
|--------|--------------|------|
| 2 pkt. | ✅ Obowiązkowe | Wyświetlanie znaku zachęty: `[{path}] $`, gdzie `{path}` to bieżący katalog roboczy. |
| 2 pkt. | ✅ Obowiązkowe | Obsługa polecenia `cd` (zmiana katalogu jak w `bash`). |
| 2 pkt. | ✅ Obowiązkowe | Obsługa polecenia `exit` (zakończenie działania powłoki). |
| 2 pkt. | ✅ Obowiązkowe | Obsługa polecenia `help` (informacje o autorze i funkcjach powłoki). |
| 6 pkt. | ❌ Opcjonalne | Implementacja dwóch *własnych*, bardziej zaawansowanych poleceń powłoki (np. `cp`). Proste komendy typu `echo` bez rozszerzeń nie są akceptowane. |
| 6 pkt. | ✅ Obowiązkowe | Obsługa programów i skryptów w `PATH`, umożliwiająca uruchomienie ich z argumentami (`fork()` + `execvp()`). |
| 4 pkt. | ✅ Obowiązkowe | Wyświetlanie komunikatu błędu, jeśli polecenie nie może zostać poprawnie zinterpretowane. |
| 6 pkt. | ❌ Opcjonalne | Dodatkowe funkcjonalności (tzw. „bajery”), np.: <ul><li>Kolorowanie tekstu</li><li>Wyświetlanie loginu użytkownika</li><li>Obsługa sygnałów (np. `Ctrl+Z`)</li><li>Historia poleceń (strzałki)</li><li>Uzupełnianie składni</li></ul> |

---

## TODO
- [x] Nazwa użytkownika
- [x] znak zachęty ```[{path}] $```
- [ ] cd 
- [ ] exit
- [ ] help: Info + Features
- [ ] kolorwaowanie tekstu dla parametrów i "", (), [], {}, etc.
- [ ] uruchamianie z **PATH** ```fork + exec*()```
- [ ] komunikat błędu gdy nie możliwe zinterpretowanie pol
- [ ] uzupełnianie komendy **leks sort**
- [ ] parametry komendy
- [ ] ```Ctrl + Z``` zatrzymanie procesu
- [ ] historia
- [ ] stzałki historii
- [ ] dwa inne wybrane polecenia
- [ ] render engine
- [ ] processing big files
- [ ] cp


## Najczęstsze błędy

1. Używanie `system()` do wykonywania poleceń — **niedozwolone**.
2. Brak wykorzystania `fork()` przy uruchamianiu zewnętrznych programów.
3. Zła obsługa błędów `exec*()` — program się blokuje.
4. Wymaganie specjalnych słów (np. `run`) przed poleceniem — **nieprawidłowe**.
5. Wymaganie podawania argumentów w osobnych liniach — wszystko ma być w jednej linii.
6. Użycie `execl()` z wieloma rozgałęzieniami zamiast `execvp()`.
7. Uruchamianie własnych poleceń w procesie potomnym — **bez potrzeby**.
8. Użycie `goto` — niezalecane.
9. Praca w Windows: unikanie Windows API (`windows.h`, `Conio.h`, `CreateProcess()`).

---

## Narzędzia i wskazówki

- Skompiluj program np. przy pomocy `Makefile` (`make`).
- Sprawdź wycieki pamięci: `valgrind`.
- Upewnij się, że kompilacja nie generuje ostrzeżeń: `-Wall`.
- Umieść projekt w repozytorium Git (np. na wydziałowym serwerze Gitea).
- Prezentację działania projektu wykonuj z poziomu terminala, np.:

```bash
$ cd ~/systemy-operacyjne-projekt/
$ make
$ ./microshell
```
