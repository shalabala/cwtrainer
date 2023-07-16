# CWTrainer coding conventions
## Ziel des Dokuments
Ziel dieses Dokuments ist, Anweisungen zu geben über die einheitlichen Kodierungsvorschriften dieses Projekts. Mit den Vorschriften wird ein einheitliches Code-Bild erzielt, das noch dazu möglichst Wartbar, Lesbar, und Ergänzbar ist. 

Das Dokument basiert auf einem anderen Dokument von Google, obwohl es ist möglich das Regeln geändert, oder gar nicht übernommen beziehungsweise empfohlen werden. Dieses Dokument ist verfügbar [hier](https://google.github.io/styleguide/cppguide.html).

## Kommentierung des Codes
Folgende Dinge müssen unbedingt mit Kommentaren ausgerüstet werden:
- Dokumentierung (d.H /***/ drei Sterne Kommentare)
    - Klassen und Strukturen
        - alle "public" Konstruktoren, Members, Methoden einer klasse
    - Enumtypen
        - Alle Werte der Enum
    - Alle, in einer Headerdatei angegebenen Funktionen

- Normale (// oder /**/) Kommentare
    - Komplexer Code

Die Kommentierung ist in der regel auf English, sowie die Namen der Typen und Variablen.

## Namenskonventionen
- Alle variablen, Enum-werte, Methoden sowie Funktionen und Konstante werden mit camelCase benannt.
- Typennamen verwenden PascalCase
    - Schnittstellen (pure virtual Klassen) haben einen 'I' als Prefix in ihren Namen (zB IName statt Name)
- Namen von Namespaces verwenden snake_case
- Compiler-direktiven verwenden CONSTANT_CASE


## Headerdateien
Jede Headerdatei verfügt über Guards im folgenden Stil:
```
#ifndef CWTRAINER_HEADER_FILE_NAME_H
#define CWTRAINER_HEADER_FILE_NAME_H

//Inhalt der Datei ..

#endif
```

## Exception safety
Die Verwendung von RAII ist überall vorgesehen, um sicher mit Exceptions umgehen zu können.



