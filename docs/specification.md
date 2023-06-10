# CWTrainer Spezifizierung 
## Ziele
Ziele dieses Dokuments ist zu spezifizieren wozu das Programm "cwtrainer" fähig sein sollte, welche Technologien es in Anspruch nimmt und wie es sich in normalen und ausnahmefällen verhalten sollte.
Dieses Dokument dient sowohl als Funktionsspezifizierung als auch als Technische.

## Grundidee
Das Programm dient zu ermöglichen und vereinfachen das Erlernen des sogenannten Morse-codes. Man kann dazu drei Schwierigkeitsstufen aussuchen, die sind in zunehmendem Schwierigkeitsniveau: die "easy", die "intermediate" und die "proficient" stufe. Diese werden in demselben Dokument noch weiter behandelt.

## Schnittstelle der Interaktion
Zwar eine grafische Benutzeroberfläche ist in der Zukunft nicht auszuschließen, am Anfang wird das Programm nur über eine Kommandozeilenschnittstelle verfügen (kurz CLI). Beim starten des Programms kann man mit den CLI-Argumenten erstens die Schwierigkeitsniveau auswählen, ohne dieses wird das intermediate Niveau automatisch ausgewählt.

Der Programmablauf sieht folgendermaßen aus: Der Benutzer wird mit Text präsentiert, den er mit Morse-Code zu eintippen hat. Fehler, und die korrekt eingetippten Buchstaben werden für den Benutzer visuell angezeigt.

## Konfigurationsmöglichkeiten und deren Implementierung
Konfiguriert werden kann das Programm mithilfe von einer Konfigurationsdatei namens cwtrainer.config, die im selben Ordner vorfindlich ist als die ausführbare Datei.
Folgende Einstellungen sind in dieser Datei enthalten:
- speed_dots - diese Einstellung bestimmt die Geschwindigkeit des kürzeren Zeichens in bpm
- speed_dashes - diese Einstellung bestimmt die Geschwindigkeit des längeren Zeichens in bpm
- dot_key - bestimmt die Taste für die dots
- dash_key - bestimmt die Taste für die dashes
- single_key - bestimmt die Taste für den single_key Modus
- mode - es gibt zwei unterschiedliche Modi mit man morsen kann:
    - single_key, wobei man nur eine Taste verwendet zu morsen
    - double_key, wobei man zwei Tasten verwendet, eine für die dots, eine für die dashes
- dynamic_timing - diese Einstellung hat nur eine Bedeutung in dem single_key Modus, und bestimmt ob die Geschwindigkeiten dynamisch approximiert werden sollten (in diesem Fall der Wert ist "true") von den Tastendrücken, oder die konfigurierten Werten berücksichtigt werden sollten bei der Zeichenerkennung ("false")
- log_location - wo die Logs gespeichert werden (der Wert ist ein Verzeichnispfad)

## Schwierigkeitsstufen
Die früher angesprochenen Schwierigkeitsstufen haben die folgenden Bedeutungen:
- Im easy Modus bekommt der Benutzer nur Buchstaben um einzutippen. Dieser Modus kann mit dem "-e" CLI-Argument gestartet werden.
- Im intermediate Modus bekommt der Benutzer einzelne Wörter um einzutippen. Dieser Modus kann mit dem "-i" CLI-Argument gestartet werden.
- Im proficient Modus bekommt der Benutzer einzelne Wörter um einzutippen. Dieser Modus kann mit dem "-p" CLI-Argument gestartet werden.

Jede Stufe (au$er der easy-Stufe) hat eine entsprechende Wörterbuchdatei, die neben dem ausführbaren File liegt, und hat eine ".dic" Dateierweiterung. In dieser sind die Wörter/Sätze enthalten, die der User begegnen kann.

## Hilfe option
Wenn der Benutzer die Hilfetaste drückt (H) 

## Unterstützte Betriebssysteme
Der Code kann sowohl für Windows, als auch für Linux kompiliert werden.

## Weiterentwicklungsmöglichkeiten
Die folgende Schritte könnten eingeleitet werden, um das Programm noch besser zu machen:
- Das Programm mit Unterstützung für dedizierte Hardwaretasten auszustatten.
- Dem Programm eine Grafikschnittstelle zu geben.

## Verwendete Technologien - steht unter Bearbeitung noch
- eine (zwei) Bibliothek(en), um Töne zu erzeugen
- eine Bibliothek um Logging zu betreiben
- eine Bibliothek um Konfigurationsdateien zu lesen

- eine Bibliothek um DI zu machen

- eine (eigene?) Bibliothek um flexible zu der CLI zu schreiben
    - diese kann mithilfe von Färbung, oder vielleicht Großschreibung gemacht werden?
- eine (eigene?) Bibliothek um plattformunabhängig Töne zu erzeugen
