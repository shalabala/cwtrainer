# CWTrainer Spezifizierung 
## Ziele
Ziele dieses Dokuments ist zu spezifizieren wozu das Programm "cwtrainer" fähig sein sollte, welche Technologien es in Anspruch nimmt und wie es sich in normalen und ausnahmefällen verhalten sollte.
Dieses Dokument dient sowohl als Funktionsspezifizierung als auch als Technische.

## Grundidee
Das Programm dient zu ermöglichen und vereinfachen das Erlernen des Morse-codes. Man kann dazu drei Schwierigkeitsstufen aussuchen, die sind in zunehmendem Schwierigkeitsniveau: die "easy", die "medium" und die "hard" stufe. Diese werden in demselben Dokument noch weiter behandelt.

## Schnittstelle der Interaktion
Das Programm wird mithilfe von einer grafische Schnittstelle bedient. Der Benutzer sieht beim starten des Programms zwei Textfelder. Nach oben ist ein mehrzeiliges Textfeld, hier sieht man die Wörter die man einzutippen hat. Nach unten ist ein einzeiliges Textfeld, hier erscheinen die schon eingetippten Morsezeichen.

Beim starten des Programms kann man mit den CLI-Argumenten erstens die Schwierigkeitsniveau auswählen, ohne dieses wird das easy Niveau automatisch ausgewählt. Später könnte diese Funktion mit einem Menü ersetzt werden.

Soll ein Fehler auftauchen, der User wird mit einem Dialogbox präsentiert, die beinhaltet die user-lesbare Fehlermeldung.

## Konfigurationsmöglichkeiten und deren Implementierung
Konfiguriert werden kann das Programm mithilfe von einer Konfigurationsdatei namens cwtrainer.config.json, die im selben Ordner vorfindlich ist als die ausführbare Datei.
Folgende Einstellungen sind in dieser Datei enthalten:
- dots_speed - diese Einstellung bestimmt die Geschwindigkeit des kürzeren Zeichens in Milliseconds
- dot_key - bestimmt die Taste für die dots
- dash_key - bestimmt die Taste für die dashes
- single_key - bestimmt die Taste für den single_key Modus
- dotLength - diese Einstellung bestimmt die Geschwindigkeit des kürzeren Zeichens in Milliseconds
- defaultDifficulty - bestimmt die vorgegebene Schwierigkeitseinstellung
- beeperFrequency - Frequenz der Pfeiftöne
- beeperAmplitude - Amplitude der Pfeiftöne
- singleKeyScanCode - bestimmt die Taste für den Single-Key Modus
- dotKeyScanCode - bestimmt die Taste für die dots
- dashKeyScanCode - bestimmt die Taste für die dashes
- helpKeyScanCode  - bestimmt die Taste für die Hilfefunktion

## Schwierigkeitsstufen
Die früher angesprochenen Schwierigkeitsstufen haben die folgenden Bedeutungen:
- Im easy Modus bekommt der Benutzer nur Buchstaben um einzutippen. Dieser Modus kann mit dem "-e" CLI-Argument gestartet werden.
- Im intermediate Modus bekommt der Benutzer einzelne Wörter um einzutippen. Dieser Modus kann mit dem "-i" CLI-Argument gestartet werden.
- Im proficient Modus bekommt der Benutzer einzelne Wörter um einzutippen. Dieser Modus kann mit dem "-p" CLI-Argument gestartet werden.

Das Programm erinnert sich an die ausgewählte Einstellung beim Starten nächstes mal, so ist es nicht erforderlich jedes mal von CLI das Programm zu starten.
Jede Stufe (außer der easy-Stufe) hat eine entsprechende Wörterbuchdatei, die neben dem ausführbaren File liegt, und hat eine ".csv" Dateierweiterung. In dieser sind die Wörter/Sätze enthalten, denen der User begegnen kann.

## Hilfe option
Wenn der Benutzer die Hilfetaste drückt (H) wird das nächste Wort (oder mehrere Worte je nach Schwierigkeitsstufe) in Morse abgespielt.

## Unterstützte Betriebssysteme
Die unterstützte Betriebssysteme sind Windows oder Linux

## Weiterentwicklungsmöglichkeiten
Die folgende Schritte könnten eingeleitet werden, um das Programm noch besser zu machen:
- Das Programm mit Unterstützung für dedizierte Hardwaretasten auszustatten.

## Verwendete Technologien - steht unter Bearbeitung noch
- SDL2 um töne zu erzeugen
- SDL2 um keyboard Events abzufangen
- GoogleTests für Unit Testing
- boost::property_tree um Konfigurationsdateien zu lesen
- Qt für die Grafikschnittstelle

- eine Bibliothek um DI zu machen