Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

Grille de correction des programmes:

Identification:
  Travail    : Mise en commun du code et formation de librairies
  Section #  : 3
  Équipe #   : 5180
  Correcteur : Claudia Onorato

Code:
– La qualités et le choix de vos portions de code choisies   (0/5)
– La qualités de vos modifications aux Makefiles             (2/5)

Le rapport:
– Explications cohérentes par rapport au code retenu
  pour former la librairie                                   (2/2)
– Explications cohérentes par rapport aux Makefiles modifiés (0/2)
– Explications claires avec un bon niveau de détails         (1/2)
– Bon français                                               (1/1)

Généralités:
– Bonne soumission de l'ensemble du code (compilation sans
  erreurs, …) et du rapport selon le format demandé          (2.5/3)

Total: 8.5/20

Commentaires du correcteur:
N'oubliez pas de merger la branche `codeCommun` dans `master`!

La qualités et le choix de vos portions de code choisies
- Je vous conseille de revoir vos noms de classe et de fonction...
  Par exemple, une classe devrait avoir un nom, sans verbe comme ce n'est pas une fonction et qu'une classe en soit ne fait pas d'action. Ce nom devrait illustrer le concept qui retache ses différentes fonctions et attributs.
  Les noms de fonction devraient commencer par un verbe, comme on y fait un action.
  Alors, si on regarde votre minuterie, la classe devrait se nommer `Timer` et sa fonction `start` (comme on appelle la fonction sur une instance de la classe, pas besoin de répéter "timer"). Une autre classe à revoir est `amber`... Le concept qui rattache ces fonctions sont évidemment la lumière, et non la couleur ambrée...
- Je vois que la plupart de vos classes n'ont pas d'attributs. Dans ce cas, il faut au moins mettre les méthodes statiques, ou sinon laisser tomber la classe pour ne garder que les fonctions.
- Mettez des include guards au début de vos fichiers d'en-tête. https://en.wikipedia.org/wiki/Include_guard#Use_of_%23include_guards
- Pourquoi faire `#include "../Lib/uart.h"` alors que vous pouvez faire `#include "uart.h"`?
- Quand vous incluez le fichier "header" (ex. `uart.h`) et que celui-ci incluait déjà les différents fichiers nécessaires (ex. <util/delay.h>), vous n'avez pas besoin de les inclure une deuxième fois dans le fichier d'implémentaiton (ex. `uart.cpp`).
- N'inclure que les fichiers nécessaires (ex. dans adjustmentPWM, pourquoi inclure delay_basic, delay, inttypes).
- Attention aux indentations!!!! (ex. `uart.cpp`)
- Le paramètre `duration` de `startTimer` n'a pas d'unité de mesure. Il est alors difficile d'utiliser la fonction sans regarder son implémentation, et de bien comprendre le fonctionnemnet des timers. Il aurait été mieux de passer un nombre de seconde, et de faire la conversion par la suite.
- Lorsque vous appelez la fonction `amber::red`, vous modifiez toutes les broches des ports A, B et C. Or, comme nous n'avons qu'une DEL sur le robot, et qu'on veut généralement contrôler une DEL à la fois, il est mieux de spécifier deux broches d'un seul port et de modifier la couleur seulement là.

La qualités de vos modifications aux Makefiles
- Certaines règles et variables sont inutiles dans le Makefile de la librairie (ex. `install` et `AVRDUDE`).
- Certaines variables sont dédoublées entre les deux Makefiles, et auraient pu être regroupées dans un makefile commun.
- Il est préférable d'utiliser `avr-ar` comme archiveur plutôt que `ar`, comme il est adapté pour les microcontrôleurs AVR.
- En ajoutant dans votre makefile l'option `-I ../Lib`, vous pouvez inclure vos headers en ne spécifiant pas le path. Vous pouvez alors faire `#include "adjustmentPWM.h"` plutôt que `#include "../Lib/adjustmentPWM.h"` dans votre main.cpp, ce qui est beaucoup mieux!

Explications cohérentes par rapport aux Makefiles modifiés
- Vos explications liées au Makefile de la librairie sont cohérentes avec ce que vous avez fait. Par contre, les explications liées au Makefile du code test ne reflète pas ce que vous avez fait:
> Voici les modifications apportées au Makefile du code (bidon) : [...]

> 2. Ar=ar cette ligne nous permet de déclarer le fichier comme une librairie statique.

> 3. -o par -crs Cette ligne nous permet de créer le .a au lieu du .out.

> 4. Nous avons enlevé le install puisqu’il est inutile pour une librairie statique.

Ces explications auraient plutôt dû être fait du côté de la librairie. Le dernier commentaire, disant que vous avez enlevé la règle install, n'a pas été fait du côté de la librairie non plus.

Bonne soumission de l'ensemble du code
- Plusieurs warnings lorsqu'on make la librairie (autre que memoire_24)!

# Basé sur le commit suivant
```
commit 1b2a6fdc629acea28d1672e5941d0912728eeb7f
Author: admin <gigl-technique@polymtl.ca>
Date:   Tue Sep 11 15:51:58 2012 -0400

    Commit administratif
```

# Fichiers indésirables
```

```

# Sortie de make dans les sous-répertoires
```
======================= Sortie de make dans tp/tp7/lib =============================
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions    -DDEBUG  -c InitInterrupt.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions    -DDEBUG  -c adjustmentPWM.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions    -DDEBUG  -c amber.cpp
amber.cpp: In member function 'void amber::Amber(long unsigned int)':
amber.cpp:28:21: warning: comparison of integer expressions of different signedness: 'long int' and 'long unsigned int' [-Wsign-compare]
   28 |   for( long i =0; i < s_count; i++)
      |                   ~~^~~~~~~~~
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions    -DDEBUG  -c can.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions    -DDEBUG  -c memoire_24.cpp
memoire_24.cpp:30:3: warning: #warning "F_CPU pas defini pour 'memoire_24.cpp'" [-Wcpp]
   30 | # warning "F_CPU pas defini pour 'memoire_24.cpp'"
      |   ^~~~~~~
In file included from memoire_24.cpp:34:
memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
memoire_24.cpp: In member function 'uint8_t Memoire24CXXX::lecture(uint16_t, uint8_t*, uint8_t)':
memoire_24.cpp:280:7: warning: this 'while' clause does not guard... [-Wmisleading-indentation]
  280 |       while ((TWCR & _BV(TWINT)) == 0) ; // Attente de fin de transmission
      |       ^~~~~
memoire_24.cpp:281:10: note: ...this statement, but the latter is misleadingly indented as if it were guarded by the 'while'
  281 |          *donnee++ = TWDR;               // Lecture
      |          ^
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions    -DDEBUG  -c startTimer.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions    -DDEBUG  -c uart.cpp
In file included from uart.cpp:4:
/usr/local/Cellar/avr-gcc/9.2.0_1/avr/include/util/delay.h:92:3: warning: #warning "F_CPU not defined for <util/delay.h>" [-Wcpp]
   92 | # warning "F_CPU not defined for <util/delay.h>"
      |   ^~~~~~~
In file included from ../Lib/uart.h:5,
                 from uart.cpp:6:
../Lib/memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
In file included from uart.cpp:6:
../Lib/uart.h:6: warning: "F_CPU" redefined
    6 | #define F_CPU 8000000UL
      | 
In file included from uart.cpp:4:
/usr/local/Cellar/avr-gcc/9.2.0_1/avr/include/util/delay.h:108: note: this is the location of the previous definition
  108 | # define F_CPU 1000000UL
      | 
avr-ar   -crs libstatique.a  InitInterrupt.o adjustmentPWM.o amber.o can.o memoire_24.o startTimer.o uart.o 
#on cc par ar et on doit utiliser crs pour créer le .a

======================= Sortie de make dans tp/tp7/exec =============================
make: *** hiver2020-correction_tp7/5180/tp/tp7/avr-gcc -I. -MMD -I ../Lib -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -DDEBUG  -c main.cpp
In file included from main.cpp:9:
../Lib/memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
In file included from ../Lib/Debug.h:4,
                 from main.cpp:12:
../Lib/memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
In file included from ../Lib/../Lib/uart.h:5,
                 from ../Lib/Debug.h:5,
                 from main.cpp:12:
../Lib/../Lib/memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
avr-gcc -Wl,-Map,Test.out.map -mmcu=atmega324pa -o Test.out  main.o \
        -lm -L ../Lib/ -lstatique


```