# CWTrainer Spezifizierung 
## Ziele
Ziele dieses Dokuments ist zu spezifizieren wozu das Programm "cwtrainer" fähig sein sollte, welche Technologien es in Anspruch nimmt und wie es sich in normalen und ausnahmefällen verhalten sollte.
Dieses Dokument dient sowohl als Funktionsspezifizierung als auch als Technische.

## Grundidee
Das Programm dient zu ermöglichen und vereinfachen das Erlernen des sogenannten Morse-codes. Man kann dazu drei Schwierigkeitsstufen aussuchen, die sind in zunehmendem Schwierigkeitsniveau: die "easy", die "medium" und die "hard" stufe. Diese werden in demselben Dokument noch weiter behandelt.

## Schnittstelle der Interaktion
Das Programm wird mithilfe von einer grafische Schnittstelle bedient. Der Benutzer sieht beim starten des Programms zwei Textfelder. Nach oben ist ein mehrzeiliges Textfeld, hier sieht man die Wörter die man einzutippen hat. Nach unten ist ein einzeiliges Textfeld, hier erscheinen die schon eingetippten Morsezeichen.

Beim starten des Programms kann man mit den CLI-Argumenten erstens die Schwierigkeitsniveau auswählen, ohne dieses wird das intermediate Niveau automatisch ausgewählt. Später könnte diese Funktion mit einem Menü ersetzt werden.

Soll ein Fehler auftauchen, der User wird mit einem Dialogbox präsentiert, die beinhaltet die user-lesbare Fehlermeldung.

## Konfigurationsmöglichkeiten und deren Implementierung
Konfiguriert werden kann das Programm mithilfe von einer Konfigurationsdatei namens cwtrainer.config, die im selben Ordner vorfindlich ist als die ausführbare Datei.
Folgende Einstellungen sind in dieser Datei enthalten:
- dots_speed - diese Einstellung bestimmt die Geschwindigkeit des kürzeren Zeichens in Milliseconds
- dot_key - bestimmt die Taste für die dots
- dash_key - bestimmt die Taste für die dashes
- single_key - bestimmt die Taste für den single_key Modus
- dynamic_timing - diese Einstellung hat nur eine Bedeutung in dem single_key Modus, und bestimmt ob die Geschwindigkeiten dynamisch approximiert werden sollten (in diesem Fall der Wert ist "true") von den Tastendrücken, oder die konfigurierten Werten berücksichtigt werden sollten bei der Zeichenerkennung ("false")
- log_location - wo die Logs gespeichert werden (der Wert ist ein Verzeichnispfad)

## Schwierigkeitsstufen
Die früher angesprochenen Schwierigkeitsstufen haben die folgenden Bedeutungen:
- Im easy Modus bekommt der Benutzer nur Buchstaben um einzutippen. Dieser Modus kann mit dem "-e" CLI-Argument gestartet werden.
- Im intermediate Modus bekommt der Benutzer einzelne Wörter um einzutippen. Dieser Modus kann mit dem "-i" CLI-Argument gestartet werden.
- Im proficient Modus bekommt der Benutzer einzelne Wörter um einzutippen. Dieser Modus kann mit dem "-p" CLI-Argument gestartet werden.

Jede Stufe (außer der easy-Stufe) hat eine entsprechende Wörterbuchdatei, die neben dem ausführbaren File liegt, und hat eine ".dic" Dateierweiterung. In dieser sind die Wörter/Sätze enthalten, die der User begegnen kann.

## Hilfe option
Wenn der Benutzer die Hilfetaste drückt (H) wird das nächste Wort in Morse abgespielt.
? Hier könnten wir auch eine Funktion implementieren, wobei der Benutzer nur den nächsten Buchstaben abspielen kann.

## Unterstützte Betriebssysteme
Der Code kann sowohl für Windows, als auch für Linux kompiliert werden.

## Weiterentwicklungsmöglichkeiten
Die folgende Schritte könnten eingeleitet werden, um das Programm noch besser zu machen:
- Das Programm mit Unterstützung für dedizierte Hardwaretasten auszustatten.
- Dem Programm eine Grafikschnittstelle zu geben.

## Verwendete Technologien - steht unter Bearbeitung noch
- SDL2 um töne zu erzeugen
- SDL2 um keyboard Events abzufangen
- GoogleTests für Unit Testing

- eine Bibliothek um Logging zu betreiben
- eine Bibliothek um Konfigurationsdateien zu lesen

- eine Bibliothek um DI zu machen

- eine (eigene?) Bibliothek um flexible zu der CLI zu schreiben
    - diese kann mithilfe von Färbung, oder vielleicht Großschreibung gemacht werden?