Projekt zawiera wszystkie podstawowe wymagania oraz wymagania dodatkowe.
W ramach projektu podjąłem kilka kluczowych decyzji, któe tutaj podjąłem.

1. Skorzystanie z listy wiązanej dla orbit
Dzięki takiemu rozwiązaniu nie jest konieczny obiekt, który nadzorował by ruch między orbitami. 
W stworzonej grze, w samych założeniach, ruch odbywa się tylko w jednym kierunku, dlatego uznałem,
że lista wiązana będzie dobry wyborem.

2. Statki oparte o RotatingMovementComponent
Konstrukcja ruchu przeciwników oparta na RotatingMovement ma na celu:
- ułatwienie gładkich tranzycji między orbitami,
- intuicyjne używanie ruchu
- prostota
Alternatywne rozwiązania jak korzystanie z sił zostało odrzucone z powodu niepotrzebnego komplikwoania całego procesu. Wykorzystanie fizyki prowadziło by też do większego wykorzystania zasobów.
Inne rozwiązanie, polegające na orbitach, do których podczepiają się statki, zostało odrzucone przez problemy z tranzycją między poziomami oraz fakt,
że wtedy jednostka będąca specjalnym przeciwnikiem musiałaby mieć inaczej konstruowany system od pozostałych przeciwników. Wymagałoby to zbędnej pracy.

Dodatkowo pozwala to zrealizować ruch Gracza, Podstawowego Przeciwnika i Specialnego Przeciwnika, na tym samym komponencie.

3. Brak ograniczenia w strzelaniu
Po przeprowadzonych testach uznano, że ruch na okręgu sprawia, że trafianie we wrogów jest trudne, a cała miejscami zamienia się w bullet hell,
co sprawia, że duża liczba pocisków często tak naprawdę przydaje się jako obrona. Postanowiono pozostawić strzelanie bez żadnych ograniczeń.

4. Dystrybuoowana liczba strzałów
W podstawowym Space Invaders, pod koniec gry dochodziło do przyspieszania przeciwników wraz z kolejnymi poległymi. Sprawiało to, że konieczna była precyzja w wymierzaniu strzału.
W tym przypadku na orbicie, mocno przyspieszony ruch po orbicie sprawiałby więcej kłopotu, dlatego zdecydowano się, że elementem prezcyzji jaką musi wykazać się gracz na koniec,
to ciągłe ataki ze strony przeciwników, którzy znajdują się coraz bliżej. W ten sposób wciąż coraz trudniej zestrzelić przeciwników, ale w inny sposób.

5. Nazewnictwo w EnemyManager
Tutaj popełniłem błąd mieszając nazewnictwo Enemy z Ship, ale już nie było czasu na zmiane tego.

6. Object Pooling
Przydałby się on dla pocisków, ale też nie zdążył zostać zaimplementowany.

