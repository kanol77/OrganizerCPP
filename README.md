# OrganizerCPP
**Aplikacja do zarządzania kontaktami i zadaniami. (CLI)**

Program umożliwiający zapisywanie, organizowanie oraz zarządzanie zaplanowanymi
zadaniami oraz kontaktami.

Kontakty są zapisane w pliku w następujący sposób:
<imię> <nazwisko> <adres email>

Przykładowy plik:
Adam Kowalski adam.kowalski@onet.pl
Jan Nowak jann123@wp.pl
Alicja Kokoszka kokoszka@gmail.com

Zadania są zapisane w pliku w następujący sposób:
<data> <typ zadania> <status> <opis>

Przykładowy plik:
2020.01.01 10:20 spotkanie Spotkanie noworoczne
2020.10.10 8:00 zajecia Zajęcia z programowania komputerow
2020.10.20 12:30 zajecia Zajęcia z fizyki
2020.10.30 8:30 wypoczynek Wycieczka w gory

Program umożliwia:
• dodanie nowego kontaktu,
• usunięcie istniejącego kontaktu,
• dodanie zadania,
• usunięcie zadania,
• wyświetlenie listy kontaktów (posortowanych wg wszystkich możliwych kryteriów),
• filtrowanie listy kontaktów (wg wszystkich możliwych kryteriów),
• wyświetlenie listy zadań,
• zmianę statusu zadania,
• wyświetlenie listy zadań (posortowanych wg wszystkich możliwych kryteriów),
• filtrowanie listy zadań (wg wszystkich możliwych kryteriów).
Zakończenie pracy z programem powoduje zapisanie na dysku w plikach tekstowych aktualnych danych (kontakty i
zadania).
Program uruchamiany jest z linii poleceń z wykorzystaniem następujących przełączników:
-k plik wejściowy z kontaktami
-z plik wejściowy z zadaniami.
