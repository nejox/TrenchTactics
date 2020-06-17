# Trench Tactics

### Inhaltsverzeichnis
- Spielidee und Ziele
- Vorbedingungen
- Gesamtuebrsicht
  - Framework
  - Gesamtuebersicht und Entscheidungsprozess
  - Architektur
  - Design Patterns
- Klassendiagramm
- Ablaeufe im Projekt
  - Wirtschaftssystem
  - EventManagement
  - EventGateway
  - GameField
  - Player
  - Renderer


## Spielidee und Ziele
In der Gamingindustrie geht der Trend hinzu Reboots/Remakes alter und vor allem erfolgreicher Spiele. Fast alle grossen Publisher sind auf diesen Zug augesprungen. Kuerzlich wurde Warcraft 3 Reforged veroeffentlicht, ein Reboot des von Blizzard gepublishtem RTS im Warcraft Universum.
Im Zuge der Suche nach einem geeigneten Thema fuer ein Programmierprojekt hat sich unsere Gruppe dazu entschieden in eine aehnlich Richtung aufzubrechen. Als Basis wurde AdvanceWars ausgewaehlt, ein Nintendo GameBoy Advance Spiel. AdvanceWars ist ein rundenbasiertes Strategiespiel in dem der Spieler verschiedene Militaerische Einheiten kontrollieren und diese taktisch klug bewegen um den Gegner zu besiegen.
Dieses Konzept wird quasi als Basis fuer TrenchTactics uebernommen. Zwei Spieler die auf einer Karte aggieren und Einheiten kaufen, bewegen und mit ihnen kaempfen koennen. Ziel des Spiels ist das gegnerische Hauptgebaeude zu zerstoeren. In unserer Version wird das Spiel als Hot-Seat Spiel entwickelt, dies bedeutet das die beiden Spieler abwecheselnd and einem Client spielen und ihre Aktionen durchfuehren.
Diese Basis wird dann in Gewissen Aspekten weiterentwickelt. Moderne Element sollen in das "alte" Spielkonzept mit einfliessen. Das "AutoBattler" Genre ist genau so ein modernes Spielkonzept das erst in den letzten Jahren gross geworden ist, aus eben diesem Genre werden zwei wichtige Konzepte mit in TrenchTactics einfliessen. 
Das erste Konzept ist die Mechanik das Einheiten, die dem Spieler zum Kaufen zur Verfuegung gestellt werden, per Zufall ausgewaehlt werden. Diese Zufallsauswahl kann dann von dem Spieler erneut ausgefuehrt werden um eine neue Auswahl an Einheiten zu bekommen.
Hierfuer wird entsprechend eine Waherung benoetigt um einen solchen "ReRoll" zu bezahlen. Deswegen wird hier, wieder aus dem AuoBattler Genre, die naechste Erweiterung geklaut und ein Wirtschaftsystem implementiert. Verschiedene Faktoren haben hier Auswirkung auf das Einkommmen das Runde fuer Runde an die Spieler ausbezahlt wird. Hierzu gibt es noch einen eigenen Abschnitt der das Wirtschaftssystem noch genauer erklaert.

## Vorbedingungen
Bisher wurde TrenchTactics nur fuer Windows compiled - den Versuch andere Betriebssysteme zu nutzen bitte nur auf eigene Gefahr!
Um das Projekt zum jetzigen Zeitpunkt benutzen zu koennen und zu debuggen werden folgende Frameworks und Software benoetigt:
- Visual Studio 2019
- SDL2.dll
- SDL2_tff.dll
- zlib1.dll
- libfreetype-6.dll

Alle dlls sind jedoch mit im Repository hinterlegt und muessen somit nicht manuell mit eingebunden werden, wenn die precompiled Version genutzt wird.

Derzeit wird TrenchTactics als Console Application compiled, um eine reine Executeable zu compilen muss eine kleine Codeveraenderung vorgenommen werden. Die rot unterstrichene Zeile muss entfernt werden:
![SDL Main Handled](Doku/SDL_Main_Handled.jpg "SDL Main Handled")

#### Folgende Einstellungen unter Project Properties muessen getroffen werden um TrenchTactics mit VisualStudio 2019 kompilieren zu koennen:

###### General Settings
![General Settings Visual Studio](Doku/GeneralSettingsVisualStudio.jpg "General Settings Visual Studio")
###### VC++ Settings
![VC++ Visual Studio](Doku/VC++VisualStudio.jpg "VC++ Visual Studio")
###### Linker Input Settings
![Linker Input Settings Visual Studio](Doku/LinkerInputVisualStudio.jpg "Linker Input Settings Visual Studio")

## Gesamtuebersicht

### Framework
Das Framework das im Projekt TrenchTactics ist [SDL2](https://www.libsdl.org/). SDL2 stellt hauptsaechlich Grundfunktionalitaeten zur Verfuegung, in unserem Projekt speziell:
- Laden der einzelnen Sprites die im Spiel verwendet werden
- Darstellen der Sprites
- Animation der Sprites
- Annahme des UserInput per Maus (bisher ist kein Keyboard-Input moeglich)

### Architektur
![Architecture Big Picture](Doku/ArchitectureBigPicture.jpg "Architecture Big Picture")

In Oben zu sehenden Bild gibt es einen kurzen Ueberblick ueber die Architektur im Projekt was im folgenden Schritt fuer Schritt immer genauer erklaert werden soll.

Die Architektur kann grundsaetzlich grob in die fuenf deutlich zu sehenden Elemente unterteilt werden. 

User Input wird durch die erste Komponente entegegen genommen, dann in der grossen Komponente "Game", unter zuhilfenahme der Datenbasis, verarbeitet und dann dem User entsprechend wieder angezeigt. All diese Komponenten bauen auf verschiedenen Low-Level Funktionen von SDL2 auf und werden jetzt, Baustein fuer Baustein, erklaert.

Im gesamten Projekt wurde darauf geachtet die Verbindung zu SDL2 nicht zu starr zu implementieren. Nahezu jede SDL Funktion wurde hinter Interfaces "versteckt". Am besten zu sehen am Beispiel des EventManagers der den UserInput behandelt. (genauer zu sehen im spezifischen Kapitel)

#### Timer
TrenchTactics ist ein Timer bzw Tick based Spiel. Dies bedeutet das Aktionen jeweils pro Tick abgearbeitet werden.
Angenommen ein der User betaetigt einen Knopf wird diese Aktion (in diesem Fall von SDl2) gespeichert und nach jedem Tick durch die jeweilig zustaendigen Funktionen verarbeitet. (zu sehen im Kapitel EventManager: processEvents()) 
Dies hat den eindeutigen Vorteil das dadurch kein Gedanke an Threading verschwendet werden muss. Die Nachteile die sich dadurch ergeben wuerden, wie etwa Latenz, sind jedoch fuer TrenchTactics nicht allzu ausschlaggebend und werden somit gekonnt ignoriert.

In der Timer Klasse wird die letzte Zeit (Tick), bereits vergangene Zeit und jetztige Zeit gespeichert und durch aufrufen der Funktion Update aktualisiert.
Diese Funktion wird bei jedem GameTick aufgerufen, und in Folge dessen das komplette Spiel aktualisiert.
Ebenfalls ist hier zu sehen das die SDL Funktion GetTicks aufgerufen wird,die die Anzahl der bereits vergangenen Ticks zurueckgibt.
```c++
/**
 * updates timer data to the next tick.
 *
 */
void CTimer::Update()
{
	m_fCurTime = SDL_GetTicks() / 1000.0f;
	m_fElapsed = m_fCurTime - m_fLastTime;
	m_fLastTime = m_fCurTime;
}
```

#### UserInput
UserInput wurde komplett abstrakt auf die SDL2 Funktionen aufgebau. Das dazu definiert Interface wurde unter Verwendung des SingeltonPatterns implementiert und stellt lediglich die Funktion processEvents zur Verfuegung:
```c++
#pragma once
#include "IEventManager.h"

/**
 * EventManagerImpl class based on singelton pattern
 * for implementing the EventManager and handling events
 */
class EventManagerImpl :
	public IEventManager
{
public:
	EventManagerImpl(const EventManagerImpl&) = delete;
	EventManagerImpl& operator=(const EventManagerImpl&) = delete;
	EventManagerImpl(EventManagerImpl&&) = delete;
	EventManagerImpl& operator=(EventManagerImpl&&) = delete;

	~EventManagerImpl() {};
	void processEvents();

	static auto& instance() {
		static EventManagerImpl eventManager;
		return eventManager;
	}

private:
	EventManagerImpl() {};
};
```

Insgesamt ist das Spiel Timer bzw Tick basiert. Dies bedeutet das