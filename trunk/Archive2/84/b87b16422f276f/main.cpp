#include "skills.h"


skills::skills()
{


    QString falschen("FÄLSCHEN (LOGIK)\n"
                     "Fälschen ermöglicht die Herstellung gefälschter Gegenstän"
                     "de oder das Verändern existierender Gegenstände für eige"
                     "ne Zwecke. Je nach Art der Fälschung sind unterschiedliche"
                     "Werkzeuge,  Materialien  oder  Vorlagen  nötig.  Siehe  Einsatz"
                     "von Fälschen, S. 146.\n"
                     "Improvisieren: Ja\n"
                     "Fertigkeitsgruppe: Keine\n"
                     "Spezialisierungen:  Bildmanipulation,  Credstickfälschung,"
                     "Dokumentenfälschung, Falsche IDs, Produktfälschung");



    QString Hardware = ("HARDWARE (LOGIK)\n"
                        "Hardware steht für die Fähigkeit eines Charakters, elektroni"
                        "sche Geräte zu bauen und zu reparieren. Dazu sind ein Ar"
                        "beitsplatz,  Material,  Werkzeug  und  genügend  Zeit  notwen"
                        "dig. Siehe Bauen und Reparieren, S. 146. \n"
                        "Improvisieren: Nein \n"
                        "Fertigkeitsgruppe: Elektronik \n"
                        "Spezialisierungen:  Nach  Art  der  Hardware  (Cyberdecks,"
                        "Kommlinks, Smartguns usw.)");



    QString Computer = ("COMPUTER (LOGIK)\n"
                        "Die Fertigkeit Computer ist die Grundlage für die Interaktion"
                        "mit der Matrix. Sie steht für die Fähigkeit, Computer und ande"
                        "re mit der Matrix verbundene Geräte zu benutzen. Diese Fer"
                        "tigkeit konzentriert sich auf das Verständnis von verschiede"
                        "nen Betriebssystemen. Mit ihr kann ein Charakter keinen Code"
                        "ausnutzen  (wie  mit  Hacking)  und  auch  nicht  an  Mainframes"
                        "basteln (wie mit Hardware). Siehe Einsatz von Computer, S. 223.\n"
                        "Improvisieren: Ja\n"
                        "Fertigkeitsgruppe: Elektronik\n"
                        "Spezialisierungen: Nach  Handlung  (Datei  Editieren,  Mat-"
                        "rixsuche, Matrixwahrnehmung usw.\n ");


    QString SOFTWARE = ("SOFTWARE (LOGIK)\n"
                        "Software wird benutzt, um Programme zu schreiben und zu"
                        "manipulieren. Siehe Einsatz von Software, S. 223. Auch Tech"
                        "nomancer benutzen Software, um ihre Komplexen Formen zu"
                        "weben (s. Weben, S. 249).\n"
                        "Improvisieren: Nein\n"
                        "Fertigkeitsgruppe: Elektronik\n"
                        "Spezialisierungen:  Datenbomben  oder  nach  Komplexer"
                        "Form (Editor, Petze, Resonanzspike usw.\n");








    QString elKrieg = ("ELEKTRONISCHE KRIEGSFÜHRUNG (LOGIK)\n"
                       "Elektronische Kriegsführung bildet die Basis militärischer Si"
                       "gnalaufklärung.  Sie  umfasst  das  Verschlüsseln,  Stören,  Täu"
                       "schen und Entschlüsseln elektronischer Kommunikationssys"
                       "teme. Wenn der Charakter die richtige Ausrüstung hat, kann"
                       "er diese Fertigkeit nutzen, um Signale aus beliebigen Kommu"
                       "nikationssystemen zu manipulieren oder sogar zu überneh"
                       "men. Siehe Einsatz von Elektronischer Kriegsführung, S. 223.\n"
                       "Improvisieren: Nein\n"
                       "Fertigkeitsgruppe: Cracken\n"
                       "Spezialisierungen:  Kommunikation,  Sensoroperationen,"
                       "Stören, Verschlüsseln.\n");





    QString Hacking = ("HACKING (LOGIK)\n"
                       "Hacking  dient  zum  Entdecken  und  Ausnutzen  von  Sicher"
                       "heitslücken in Computern und anderer Elektronik. Genaueres"
                       "dazu finden Sie unter Einsatz von Hacking, S. 223.\n"
                       "Improvisieren: Ja\n"
                       "Fertigkeitsgruppe: Cracken\n"
                       "Spezialisierungen: Dateien, Geräte, Hosts, Personas\n");

    QString matrixkampf = ("MATRIXKAMPF (LOGIK)\n"
                           "Matrixkampf wird von Hackern für Kämpfe in der Matrix be"
                           "nutzt. Siehe Einsatz von Matrixkampf, S. 223.\n"
                           "Improvisieren: Ja\n"
                           "Fertigkeitsgruppe: Cracken\n"
                           "Spezialisierungen: Nach Ziel (Geräte, Gitter, IC, Personas,"
                           "Sprites usw.");



    QString mechanik = ("INDUSTRIEMECHANIK (LOGIK)\n"
                        "LUFTFAHRTMECHANIK (LOGIK)\n"
                        "SEEFAHRTMECHANIK (LOGIK)\n");



    QString gebrauche = ("GEBRÄUCHE (CHARISMA)\n"
                         "Gebräuche steht für das Verständnis und das Erkennen von an"
                         "gemessenem Sozialverhalten. Die Fertigkeit dient als eine Art"
                         "soziale Version von Schleichen und ermöglicht es, unerkannt"
                         "durch verschiedene soziale Situationen zu kommen. Außerdem"
                         "kann sie ein gesellschaftliches Sicherheitsnetz sein, wenn ein"
                         "Spieler eine soziale Situation verpatzt, die der Charakter aber"
                         "bewältigt hätte. Siehe Einsatz von Gebräuche, S. 141.\n"
                         "Improvisieren: Ja\n"
                         "Fertigkeitsgruppe: Einfluss\n"
                         "Spezialisierungen: Nach Kultur oder Subkultur (High Soci-"
                         "ety, Konzerne, Medienwelt, Söldner, Straße, Yakuza usw.");


    QString verhandlung = ("VERHANDLUNG (CHARISMA)\n"
                           "Verhandlung  steht  für  die  Fähigkeit,  Charisma,  Kommunika"
                           "tionstechniken und Psychologie bei Geschäften einzusetzen,"
                           "um sich in eine bessere Position zu bringen."
                           "Improvisieren: Ja\n"
                           "Fertigkeitsgruppe: Einfluss\n"
                           "Spezialisierungen: Diplomatie, Feilschen, Verträge");



    QString laufen = ("LAUFEN (STÄRKE)\n"
                      "Laufen  dient  dem  Überwinden  von  Entfernungen  in  kurzer"
                      "Zeit. Näheres dazu finden Sie unter Einsatz von Laufen, S. 136.\n"
                      "Improvisieren: Ja\n"
                      "Fertigkeitsgruppe: Athletik\n"
                      "Spezialisierungen: Langstrecke, Sprint, nach Terrain (Wüs-"
                      "te, Stadt, Wildnis usw.)");


    QString waffenlos = ("WAFFENLOSER KAMPF\n"
                         "Diese Fertigkeit steht für Selbstverteidigung und Angriffe, bei"
                         "denen der Körper die Hauptwaffe ist. Dazu gehören allerlei"
                         "Kampfkünste, der Einsatz von Cyberimplantatwaffen und die"
                         "Kampfstile, die sich für diese Waffen entwickelt haben.\n"
                         "Improvisieren: Ja\n"
                         "Fertigkeitsgruppe: Nahkampf\n"
                         "Spezialisierungen:  Blocken,  Cyberimplantatwaffen,  Fest-"
                         "haltekampf, spezielle Kampfkunst");



    QString pistolen = ("Pistolen: \nDiese Fertigkeit dient zum Schießen mit Handfeuerwaffen wie "
                        "Tasern, Einzelschusspistolen, Halbautomatiken und Revolvern. \n"
                        "Improvisieren: Ja \n"
                        "Fertigkeitsgruppe: Feuerwaffen \n"
                        "Spezialisierungen:  Halbautomatik,  Holdout-Pistolen,  Re"
                        "volver, Taser");



    QString gewehre = ("GEWEHRE\n"
                       "Die Fertigkeit Gewehre dient zur Benutzung von Langwaffen"
                       "wie  Jagd-  und  Scharfschützengewehren.  In  diese  Kategorie"
                       "fallen auch Waffen wie Schrotflinten, die im Schulteranschlag"
                       "abgefeuert werden.\n"
                       "Improvisieren: Ja\n"
                       "Fertigkeitsgruppe: Feuerwaffen\n"
                       "Spezialisierungen: Scharfschützengewehre, Schießen auf Lan"
                       "ge Entfernung, Schießen auf Maximale Entfernung, Schrotflinten");


    QString erstehilfe("ERSTE HILFE (LOGIK)\n"
                       "Erste Hilfe ist die Fähigkeit, Notfallmedizin wie ein Sanitäter"
                       "zu betreiben. Sie kann genutzt werden, um Verletzungen zu"
                       "behandeln  und  Charaktere  zu  stabilisieren,  damit  sie  nicht"
                       "sterben. Erste Hilfe kann nicht für chirurgische Eingriffe oder"
                       "zum  Reparieren  beschädigter  Implantate  benutzt  werden."
                       "Näheres dazu finden Sie unter Heilung ab S. 204.\n"
                       "Improvisieren: Ja\n"
                       "Fertigkeitsgruppe: Biotech\n"
                       "Spezialisierungen:  Nach  Behandlung  (Knochenbrüche,"
                       "Schussverletzungen, Verbrennungen, Wiederbelebung usw.\n");

    QString schleichen("SCHLEICHEN (GESCHICKLICHKEIT)\n"
                       "Sie müssen an einen Ort, an dem Sie nichts zu suchen haben?"
                       "Diese Fertigkeit erlaubt Ihnen, in verschiedenen Situationen"
                       "unauffällig zu bleiben. Siehe Einsatz von Heimlichkeitsfertigkei"
                       "ten, S. 135.\n"
                       "Improvisieren: Ja\n"
                       "Fertigkeitsgruppe: Heimlichkeit\n"
                       "Spezialisierungen:  Nach  Ort  (Dschungel,  Stadt,  Wüste"
                       "usw.)");

    QString schlosser("SCHLOSSER (GESCHICKLICHKEIT)\n"
                      "Diese Fertigkeit umfasst das Bauen, Reparieren, Manipulieren"
                      "und  Öffnen  von  mechanischen  und  elektronischen  Schlös"
                      "sern.  Meist  werden  mechanische  Schließsysteme  als  Anti"
                      "quitäten gesehen, aber als Ersatzsysteme oder Überraschung"
                      "findet man sie immer noch. Elektronische Schlösser sind viel"
                      "weiter verbreitet und lassen sich mit dieser Fertigkeit gut ma-"
                      "nipulieren. Siehe Türen, Fenster und Schlösser, S. 362.\n"
                      "Improvisieren: Nein\n"
                      "Fertigkeitsgruppe: Keine\n"
                      "Spezialisierungen: Nach Art des Schlosses (Kombinations"
                      "schloss, Magschloss, Schließzylinder, Stimmerkennung, Tas"
                      "tenfeld usw.)");

    QString bruteforce("BRUTE FORCE\n"
                       "(KOMPLEXE HANDLUNG)\n"
                       "Benötigte Marken: keine\n"
                       "Probe: Matrixkampf + Logik [Angriff] gegen Willenskraft + "
                       "Firewall");

    QString dateicracken("DATEI CRACKEN\n"
                         "(KOMPLEXE HANDLUNG)\n"
                         "Benötigte Marken: 1\n"
                         "Probe: Hacking + Logik [Angriff] gegen Schutzstufe x 2");

    QString progcrash("PROGRAMM ABSTÜRZEN LASSEN\n"
                      "(KOMPLEXE HANDLUNG)\n"
                      "Benötigte Marken: 1\n"
                      "Probe: Matrixkampf + Logik [Angriff] gegen Intuition + Fi"
                      "rewall");

    QString dataspike("DATENSPIKE\n"
                      "(KOMPLEXE HANDLUNG)\n"
                      "Benötigte Marken: Keine\n"
                      "Probe: Matrixkampf + Logik [Angriff] gegen Intuition + Fi"
                      "rewall");

    QString markeloschen("MARKE LÖSCHEN\n"
                         "(KOMPLEXE HANDLUNG)\n"
                         "Benötigte Marken: speziell\n"
                         "Probe: Computer + Logik [Angriff] gegen Willenskraft + Fi"
                         "rewall");

    QString signalstoren("SIGNAL STÖREN\n"
                         "(KOMPLEXE HANDLUNG)\n"
                         "Benötigte Marken: Besitzer\n"
                         "Probe: Elektronische Kriegsführung + Logik [Angriff]");

    QString iconwechseln("ICON AUFSPÜREN\n"
                         "(KOMPLEXE HANDLUNG)\n"
                         "Benötigte Marken: 2\n"
                         "Probe:  Computer  +  Intuition  [Datenverarbeitung]  gegen "
                         "Willenskraft + Schleicher");
    QString dateiedit("DATEI EDITIEREN\n"
                      "(KOMPLEXE HANDLUNG)\n"
                      "Benötigte Marken: 1\n"
                      "Probe: Computer + Logik [Datenverarbeitung] gegen Intu"
                      "ition + Firewall");

    QString hostbetret("HOST BETRETEN/VERLASSEN\n"
                       "(KOMPLEXE HANDLUNG)\n"
                       "Benötigte Marken: 1\n"
                       "Probe: keine");

    QString gitterwechsel("GITTERWECHSEL\n"
                          "(KOMPLEXE HANDLUNG)\n"
                          "Benötigte Marken: keine\n"
                          "Probe: keine (Datenverarbeitungshandlung)");

    QString markeeinladen("MARKE EINLADEN\n"
                          "(EINFACHE HANDLUNG)\n"
                          "Benötigte Marken: Besitzer\n"
                          "Probe: keine (Datenverarbeitungshandlung)\n");

    QString geratspringen("IN EIN GERÄT SPRINGEN\n"
                          "(KOMPLEXE HANDLUNG)\n"
                          "Benötigte Marken: 3\n"
                          "Probe:  Elektronische  Kriegsführung  +  Logik  [Datenverar"
                          "beitung] gegen Willenskraft + Firewall");

    QString matrixwahr("MATRIXWAHRNEHMUNG\n"
                       "(KOMPLEXE HANDLUNG)\n"
                       "Benötigte Marken: keine\n"
                       "Probe:  Computer  +  Intuition  [Datenverarbeitung]  (gegen"
                       "Logik + Schleicher)");

    QString matrixsuche("MATRIXSUCHE\n"
                        "(JE NACH HANDLUNG)\n"
                        "Benötigte Marken: keine\n"
                        "Probe: Computer + Intuition [Datenverarbeitung]");

    QString geratsteuer("GERÄT STEUERN\n"
                        "(JE NACH HANDLUNG)\n"
                        "Benötigte Marken: variabel\n"
                        "Probe: (je nach Handlung) [Datenverarbeitung (oder spezi-"
                        "ell)] gegen (je nach Handlung) oder Elektronische Kriegsfüh-"
                        "rung + Intuition [Schleicher] gegen Intuition + Firewall");

    QString nachrichtuber("NACHRICHT ÜBERMITTELN\n"
                          "(EINFACHE HANDLUNG)\n"
                          "Benötigte Marken: 1\n"
                          "Probe: keine (Datenverarbeitungshandlung)");

    QString interfaceModi("INTERFACEMODUS WECHSELN\n"
                          "(EINFACHE HANDLUNG)\n"
                          "Benötigte Marken: Besitzer\n"
                          "Probe: keine (Datenverarbeitungshandlung)");

    QString iconaufsp("ICON AUFSPÜREN\n"
                      "(KOMPLEXE HANDLUNG)\n"
                      "Benötigte Marken: 2\n"
                      "Probe:  Computer  +  Intuition  [Datenverarbeitung]  gegen "
                      "Willenskraft + Schleicher");


    QString befehlvortauschen("BEFEHL VORTÄUSCHEN\n"
                              "(KOMPLEXE HANDLUNG)\n"
                              "Benötigte Marken: 1 (siehe Beschreibung)\n"
                              "Probe: Hacking + Intuition [Schleicher] gegen Logik + Fi-"
                              "rewall");


    QString datenbombe("DATENBOMBE ENTSCHÄRFEN\n"
                       "(KOMPLEXE HANDLUNG)\n"
                       "Benötigte Marken: Keine\n"
                       "Probe: Software + Intuition [Firewall] gegen Stufe der Da-"
                       "tenbombe x 2");


    QString eiligeshacken("EILIGES HACKEN\n"
                          "(KOMPLEXE HANDLUNG)\n"
                          "Benötigte Marken: keine\n"
                          "Probe: Hacking + Logik [Schleicher] gegen Intuition + Fi-"
                          "rewall");


    QString geratformat("GERÄT FORMATIEREN\n"
                        "(KOMPLEXE HANDLUNG)\n"
                        "Benötigte Marken: 3\n"
                        "Probe:  Computer  +  Logik  [Schleicher]  gegen  Willenskraft "
                        "+ Firewall");


    QString overwatch("OVERWATCH-WERT BESTIMMEN\n"
                      "(EINFACHE HANDLUNG)\n"
                      "Benötigte Marken: Keine\n"
                      "Probe:  Elektronische  Kriegsführung  +  Logik  [Schleicher]"
                      "gegen 6 Würfel");


    QString ubertragabf("ÜBERTRAGUNG ABFANGEN\n"
                        "(KOMPLEXE HANDLUNG)\n"
                        "Benötigte Marken: 1\n"
                        "Probe: Elektronische Kriegsführung + Intuition [Schleicher]"
                        "gegen Logik + Firewall");

    QString verstecken("VERSTECKEN\n"
                       "(KOMPLEXE HANDLUNG)\n"
                       "Benötigte Marken: keine\n"
                       "Probe: Elektronische Kriegsführung + Intuition [Schleicher]"
                       "gegen Intuition + Datenverarbeitung");


    QString ausstopseln("AUSSTÖPSELN\n"
                        "(EINFACHE HANDLUNG)\n"
                        "Benötigte Marken: Besitzer\n"
                        "Probe:  Hardware  +  Willenskraft  [Firewall]  gegen  Logik  +"
                        "Angriff ");


    QString datenbombeEntsch("DATENBOMBE LEGEN\n"
                             "(KOMPLEXE HANDLUNG)\n"
                             "Benötigte Marken: 1\n"
                             "Probe: Software + Logik [Schleicher] gegen Gerätestufe x 2");



    QString vollmatrix("VOLLE MATRIXABWEHR\n"
                       "(UNTERBRECHUNGSHANDLUNG)\n"
                       "Benötigte Marken: Besitzer\n"
                       "Probe: keine (Firewallhandlung)");


    skillList.insert("Fälschen", falschen);
    skillList.insert("Hardware", Hardware);
    skillList.insert("Computer", Computer);
    skillList.insert("Software", SOFTWARE);
    skillList.insert("Elektronische Kriegsführung", elKrieg);
    skillList.insert("Hacking", Hacking);
    skillList.insert("Hacking - Hosts", Hacking);
    skillList.insert("Mechanik Gruppe", mechanik);
    skillList.insert("Gebräuche", gebrauche);
    skillList.insert("Verhandeln", verhandlung);
    skillList.insert("Laufen", laufen);
    skillList.insert("Waffenlos", waffenlos);
    skillList.insert("Gewehre", gewehre);
    skillList.insert("Gewehre - AR", gewehre);
    skillList.insert("Matrixkampf", matrixkampf);
    skillList.insert("Pistolen", pistolen);
    skillList.insert("Cyberdecks", Hardware);
    skillList.insert("Erste Hilfe", erstehilfe);
    skillList.insert("Schleichen", schleichen);
    skillList.insert("Schlosser", schlosser);
    skillList.insert("Brute Force", bruteforce);
    skillList.insert("Brute Force (Hosts)", bruteforce);
    skillList.insert("Datei Cracken", dateicracken);
    skillList.insert("Programm abstürzen lassen", progcrash);
    skillList.insert("Daten Spike", dataspike);
    skillList.insert("Marke Löschen", markeloschen);
    skillList.insert("Signal Stören", signalstoren);
    skillList.insert("Icon Ändern", iconwechseln);
    skillList.insert("Host betreten/verlassen", hostbetret);
    skillList.insert("Datei editieren", dateiedit);
    skillList.insert("Grid springen", gitterwechsel);
    skillList.insert("Marke einladen", markeeinladen);
    skillList.insert("Matrixwahrnehmung", matrixwahr);
    skillList.insert("Matrixsuche",matrixsuche);
    skillList.insert("Gerät neustarten",geratsteuer);
    skillList.insert("Nachricht senden",nachrichtuber);
    skillList.insert("Interfacemodus wechseln", interfaceModi);
    skillList.insert("Icon verfolgen", iconaufsp);
    skillList.insert("In ein Gerät springen", geratspringen);
    skillList.insert("Befehlvortäuschen", befehlvortauschen);
    skillList.insert("Datenbombe legen", datenbombe);
    skillList.insert("Eiliges Hacken", eiligeshacken);
    skillList.insert("Eiliges Hacken (Hosts)", eiligeshacken);
    skillList.insert("Gerät formatieren", geratformat);
    skillList.insert("Overwatch Wert bestimmen", overwatch);
    skillList.insert("Übertragung abfangen", ubertragabf);
    skillList.insert("Verstecken", verstecken);
    skillList.insert("Ausstöpseln", ausstopseln);
    skillList.insert("Datenbombe entschärfen", datenbombeEntsch);
    skillList.insert("Volle Matrixabwehr", vollmatrix);

}

QString skills::getSkillDescription(QString skill)
{
    return this->skillList.value(skill);

}

