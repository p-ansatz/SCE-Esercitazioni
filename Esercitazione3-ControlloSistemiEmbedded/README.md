# Esercitazione 3
### Tecniche di Controllo per Sistemi Embedded

***
</br>

## Controllo on-off
Il più *naive* degli schemi di controllo è sicuramente il **controllo on-off**:

<p align="center">
  <img src="img/tex/onoff1.png">
</p>

in cui *e* è il valore assunto dall'*errore*, differenza tra il valore dell'uscita misurata del sistema e il riferimento.

Ovviamente il valore di ![u_{min}](https://render.githubusercontent.com/render/math?math=u_%7Bmin%7D) può essere anche pari a 0, e dunque il valore dell'ingresso di controllo varia tra un valore massimo e un valore 0 (effettivamente un valore di *off*). 

Si tratta di un controllo decisamente semplificato che non ha parametri da determinare, se non i valori limite che può assumere l'ingresso di controllo. La sua variazione può avvenire principalmente in accordo a tra logiche differenti, illustrate di seguito. Grazie all'utilizzo di una di queste è possibile anche definire cosa effettivamente deve succedere nel momento in cui il valore dell'errore è pari a 0.

<p align="center">
  <img src="img/on_off.png">
</p>

Nella figura A la caratteristica ideale, nella figura B una rappresentazione dello schema on-off con l'introduzione di una *banda morta* e nella figura C la rappresentazione dello schema di controllo on-off con *isteresi*.

</br>

## Regolatore Proporzionale-Integrale-Derivativo (PID)
Nella pratica industriale e generalmente del controllo automatico, molto spesso si utilizzano dei regolatori "standard" grazie ai quali è possibile ottenere le prestazioni desiderate tramite la taratura (*tuning*) di pochi parametri. Sicuramente il **PID** appartiene a questa famiglia di controllori: di fatto è il controllore più utilizzato nell'ambito industriale.

Il **PID** è un controllore dinamico che fornisce un'azione di controllo *proporzionale* all'errore ( *e(t)* ), al suo *integrale* ed alla sua *derivata*:

<p align="center">
  <img src="img/tex/pid01.png">
</p>

Inquadrato all'interno di un classico schema di retroazione, il **PID** si presenta in questa forma:
<p align="center">
  <img src="img/PID_scheme1.png" width="50%">
</p>

o, espandendolo e mettendo in evidenza le tre componenti che lo realizzano:
<p align="center">
  <img src="img/PID_scheme.png" width="50%">
</p>


I parametri *Kp* *Ti* e *Td* sono detti rispettivamente: *guadagno proporzionale*, *costante di tempo integrale* e *costante di tempo derivativa*; variando questi tre parametri è possibile modificare le prestazione del sistema di controllo, come schematizzato nella seguente tabella.

| | Stabilità|![e_{\infty}](https://render.githubusercontent.com/render/math?math=e_%7B%5Cinfty%7D) | ![T_a](https://render.githubusercontent.com/render/math?math=T_a) | ![S](https://render.githubusercontent.com/render/math?math=S) |
|:-:|:-:|:-:| :-: | :-: |
| ![K_p](https://render.githubusercontent.com/render/math?math=K_p):arrow_up: | diminuisce |diminuisce |diminuisce |aumenta|
|![T_i](https://render.githubusercontent.com/render/math?math=T_i) :arrow_down:| diminuisce |nullo |diminuisce |aumenta|
|![T_d](https://render.githubusercontent.com/render/math?math=T_d) :arrow_up:| migliora|non influente |non influente |diminuisce|

L'effetto generale dovuto alle tre distinte componenti del regolatore si può apprezzare simulando il funzionamento del **PID** implementato con diverse strutture, ad esempio in un classico problema di *asservimento a gradino*.

<p align="center">
  <img src="img/PID_compare.png">
</p>

Dai risultati si evince che l'azione combinata delle tre componenti permette di risolvere in maniera efficiente il problema di controllo; l'unica componente che in maniera sensata può essere utilizzata da sola è quella proporzionale, che però necessita di un qualche termine integrale per poter azzerare l'errore di asservimento a regime. Se tale componente non è già presente nel sistema da controllare è importante introdurre l'azione integrale, che matematicamente rappresenta l'area sottesa dalla curva espressa da ![e(t)](https://render.githubusercontent.com/render/math?math=e(t)) e fa sì che il controllore abbia memoria dei valori passati dell'errore.

Il termine derivativo invece permette al **PID** di avere una capacità di predizione grazie al quale è possibile ottenere uno *smoothing* della risposta del sistema controllato. Aumentando il parametro *Td* diminuisce infatti la sovraelongazione del sistema e si realizza una predizione lineare dell'errore di inseguimento, grazie alla quale è possibile "frenare" la risposta del sistema prima che si allontani troppo dal segnale di riferimento. Inoltre, grazie ad un aumento di fase del sistema in retroazione pari a 90 gradi, migliora la stabilità. Tuttavia, è importante notare che il termine derivativo tende ad amplificare i segnali ad alta frequenza e quindi anche i disturbi di misura. Queste considerazioni si ricavano dall'analisi frequenziale del regolatore e, come effetto finale, si potrebbe avere un'azione di controllo che risulta essere "nervosa". 

Inoltre, nel caso di segnali di riferimento a gradino, che presentano discontinuità di prima specie, l'azione di controllo dovuta al solo effetto derivativo sarebbe teoricamente di valore infinito ed il segnale di controllo assumerebbe quindi valori esagerati, di natura impulsiva. Ciò si traduce praticamente in un potenziale danneggiamento degli attuatori o dell'impianto.

Un'ultima considerazione riguarda la fisica realizzabilità del termine derivativo: se analizzato ci si accorge che si tratta di un sistema non causale, che richiede la conoscenza di segnali futuri. Per un'implementazione causale questo termine viene filtrato con un *filtro passa-basso* che svolge due funzioni importanti: rende il derivatore fisicamente realizzabile e compensa gli effetti del rumore di misura in alta frequenza.

La componente che riguarda solo la parte derivativa diventa dunque:

<p align="center">
  <img src="img/tex/pid_d01.png">
</p>

l'introduzione del filtro appare ancora più chiara se la formulazione viene espressa nel *dominio di Laplace*:

<p align="center">
  <img src="img/tex/pid_d02.png">
</p>

### Implementazione digitale di un regolatore PID

In un sistema di controllo embedded si lavora con segnali digitali ed un regolatore deve essere riformulato a tempo discreto, in modo da lavorare non con un segnale nel dominio del tempo ma con una sequenza di campioni ( ad esempio ![e_n](https://render.githubusercontent.com/render/math?math=e_n) per l'errore), conseguentemente il regolatore fornirà in input al sistema una sequenza di ingressi di controllo ( ![u_n](https://render.githubusercontent.com/render/math?math=u_n) ). Ciò che deve variare, nella formulazione classica di un **PID**, sono essenzialmente la parte integrale e quella derivativa.

Il termine integrale può essere approssimato, al tempo *n*, con la somma dei rettangoli aventi base pari al periodo di campionamento ![T_c](https://render.githubusercontent.com/render/math?math=T_c) e altezza pari al valore ![e_{kTc}](https://render.githubusercontent.com/render/math?math=e_%7BkTc%7D), con ![0 \leq k \leq n](https://render.githubusercontent.com/render/math?math=0%20%5Cleq%20k%20%5Cleq%20n). Il termine derivativo può essere approssimato al passo *n* con il rapporto incrementale tra i capioni ![e_{(n-1)Tc}](https://render.githubusercontent.com/render/math?math=e_%7B(n-1)Tc%7D) e ![e_{nTc}](https://render.githubusercontent.com/render/math?math=e_%7BnTc%7D). Si tratta dell'approssimazione più intuitiva e semplice, in realtà si può fare riferimento a tre principali metodi di discretizzazione in gergo indicati come *differenze in avanti*, *differenze all'indietro* e *metodo di Tustin* (o *trasformazione bilineare*).

<p align="center">
  <img src="img/discr_methods.png" width="80%">
</p>

Con le approssimazioni indicate, la formulazione del **PID** che si ottiene è la seguente (sostituendo per comodità di scrittura il pedice *n* al più preciso *nTc*):

<p align="center" >
  <img src="img/tex/pid02_color.png" width="50%" style="border: 1px solid #ccc!important; border-radius: 16px;">
</p>

Sebbene implementabile e funzionale, tale equazione è computazionalmente dispendiosa a causa della sommatoria usata per approssimare l'integrale: questa necessita della memorizzazione di tutti i campioni passati dell'errore. Per limitare tale peso computazionale e la quantità di informazioni da memorizzare è possibile praticare una riformulazione dell'equazione in termini di funzione ricorsiva, definendo lo scostamento tra l'azione di controllo al passo *n* e quella al passo *n-1*.

<p align="center">
  <img src="img/tex/pid03.png">
</p>

da cui l'azione di controllo ricorsiva:

<p align="center">
  <img src="img/tex/pid04.png">
</p>

che, richiedendo la memorizzazione di qualche variabile in più, si mostra comunque come una formulazione sicuramente implementabile. 

È possibile ricavare un'altra formulazione ricorsiva più interessante che utilizza i termini passati dell'ingresso solo nelle parti integrale e derivativa ed inoltre implementa quest'ultima in forma filtrata, con il filtro passa-basso mostrato in precedenza. Nelle seguenti equazioni vengono mostrate in maniera separata il contributo integrale ![u_n^i](https://render.githubusercontent.com/render/math?math=u_n%5Ei) e quello derivativo ![u_n^d](https://render.githubusercontent.com/render/math?math=u_n%5Ed).

<p align="center">
  <img src="img/tex/pid05_color.png" width="50%" style="border: 1px solid #ccc!important; border-radius: 16px;">
</p>

### Tecniche di desaturazione dell'azione integrale
La presenza dell'effetto integrale in un **PID**, ha come effetto collaterale quello di dare luogo ad un segnale che cresce indefinitamente in ampiezza se il valore dell'errore resta costante. Dal punto di vista pratico, questo si riflette negativamente su gli attuatori dell'impianto, che presentano inevitabilmente delle limitazioni fisiche per via delle quali non è possibile fornire un'azione superiore (o inferiore) a determinati limiti fisici. Per questo motivo è bene tenere conto di effetti di *saturazione* in fase di modellazione del segnale di controllo per gli attuatori.

Quando si lavora con attuatori che presentano, per ovvi motivi, una saturazione e l'effetto integrale non viene gestito opportunamente si ha il fenomeno note come *windup dell'azione integrale*. Per evitarlo (evitando anche deterioramenti fisici del sistema) si possono adottare diverse strategie dette *anti-windup*, con le quali è possibile saturare il controllore **PID** in modo che, quando l'attuatore entra in saturazione, l'integrazione dell'errore di controllo si blocchi o addirittura decrementi. 

<p align="center">
  <img src="img/pidsat_scheme.png" width="70%">
</p>


Considerando un attuatore con saturazione, si può determinare questa relazione, tra ingresso di controllo e segnale processato dall'attuatore:

<p align="center">
  <img src="img/tex/pid06.png">
</p>



Partendo da queste considerazioni è possibile strutturare il controllore, ad esempio un **PI**, con la seguente formulazione tempo continuo:

<p align="center">
  <img src="img/tex/pid07.png">
</p>

Si noti che l'ultimo termine contribuisce con un valore pari a 0 finché l'attuatore non va in saturazione e quindi finché opera in regione lineare con ![u_a(t) = u(t)](https://render.githubusercontent.com/render/math?math=u_a(t)%20%3D%20u(t)). Appena l'attuatore entra nel regime di saturazione si crea una discrepanza tra gli ingressi, che ha un effetto di "desaturazione dell'azione integrale" con peso determinato dal termine ![T_r](https://render.githubusercontent.com/render/math?math=T_r). 

Lo scopo di questa semplice strategia è di far diminuire il valore dell'ingresso di controllo appena si entra nei limiti di saturazione determinati dall'attuatore (informazione che comunque va ricavata da modello matematico o in maniera empirica). Ovviamente si potrebbe avere un peggioramento in termini di prestazioni, che si può arginare tarando opportunamente il parametro ![T_r](https://render.githubusercontent.com/render/math?math=T_r). 

Si noti che, un effetto simile si può ottenere anche sottraendo direttamente l'integrale dell'errore e non della discrepanza tra gli ingressi.

### Implementazione software
Partendo dalle formulazioni a tempo discreto, è possibile ricavare delle forme algoritmiche per un controllore **PID**. È importante tenere in considerazione l'intero schema di controllo nel quale si andrà ad inserire, nel contesto di un sistema di controllo embedded.

<p align="center">
  <img src="img/control_scheme.png">
</p>

Messo a punto l'intero sistema in termini di periferiche hardware da utilizzare, la parte di software che si occupa del **PID** si può pensare all'interno di una libreria dedicata che (in linguaggio **C**) sarà composta da un file *header* e una sua realizzazione. Le funzioni principali da esportare in questa libreria riguardano:
* L'inizializzazione del **PID** - che in maniera conveniente può essere pensato come una struttura contenente i parametri necessari al suo funzionamento;
* Il calcolo dell'azione di controllo - che grazie alla conoscenza dell'errore attuale determinerà l'azione di controllo *u(t)*;
* La gestione di un criterio di *anti-windup*;
* Il reset completo della struttura o l'aggiornamento dei suoi campi.

Il criterio che si può utilizzare nel `main` consiste nell'utilizzare un *timer* che scatta ogni *Tc* e comanda, nel ciclo di vita principale, il calcolo della legge di controllo da applicare sugli attuatori.
```c
while(1) {
  ...
  if(Tc_flag == 1) {
    r = get_reference();    // Reference Value
    y = get_measurement();  // Measurement value

    u = PID_calculate(r, y, &PID_struct); // Calculate input

    set_input(u);           // Set input to actuator

    Tc_flag = 0;
  }
}
```
La funzione `PID_calculate`, che si trova nella libreria per il controllore **PID**, si occuperà di implementare l'algoritmo di controllo in accordo ad una delle formulazioni mostrate, introducendo possibilmente un effetto *anti-windup* adeguato.

<p align="center">
  <img src="img/sequence.png" width="50%">
</p>

### Cenni alle principali Tecniche di Taratura 
La taratura di un **PID** è il processo cruciale grazie al quale questo regolatore può essere utilizzato in maniera efficace. Delineare delle regole ben precise e valide in maniera assoluta non è praticabile. Molto spesso infatti la taratura di questi regolatori viene effettuata per via empirica, a seguito di una prima regolazione che si avvale di una serie di tecniche basate, eventualmente, anche sul modello del sistema da controllare. 

Il primo metodo di taratura, ad oggi anche utilizzato, è stato sviluppato negli anni '40 e prende il nome di "metodo di Ziegler–Nichols". Si tratta di un metodo euristico molto semplice che non richiede necessariamente la conoscenza del modello del sistema e si basa sulla ricerca di un particolare valore detto "guadagno critico", dal quale si possono derivare gli altri parametri del **PID** in base a delle relazioni note. Il metodo si realizza secondo due possibili strade, una prima detta *ad anello chiuso* in quanto si mette in retroazione il sistema con un **PID** che contiene solo la componente proporzionale e questa si fa aumentare portando l'intero sistema al limite della stabilità, in una condizione di oscillazione permanente.

<p align="center">
  <img src="img/tuning01.png" width="60%">
</p>

A questo punto si determinano il periodo delle oscillazioni ed il guadagno per cui queste oscillazioni si verificano e si fa riferimento ad una nota tabella per ricavare i valori di *Kp*, *Td* e *Ti*.

|  | *Kp* | *Ti* | *Td* |
|:-:|:-:|:-:|:-:|
|**P**| 0.5 *Kcr* | - | - |
|**PI**|0.45 *Kcr* | *Tcr*/1.2 | - |
|**PD**| 0.8 *Kcr* | - | *Tcr*/8 |
|**PID**| 0.6 *Kcr* | *Tcr*/2 | *Tcr*/8 |


Come si può immaginare, il metodo non è sempre praticabile dal punto di vista fisico, più probabilmente da un punto di vista simulativo, il che richiede però la conoscenza del modello matematico del sistema da simulare. 

Questo metodo, ed altri simili, che riescono comunque a garantire la stabilità del sistema, non sempre permettono di ottenere risultati soddisfacenti ed è necessario fare ricorso a metodi di taratura più avanzati, spesso basati sul modello matematico del sistema da controllare. In questi casi, poiché la modellazione matematica non rispecchia mai realmente il sistema fisico, è bene eseguire una seconda fase di taratura empirica dei valori.

Nei casi in cui sia noto il modello del sistema è possibile effettuare una prima fase di taratura utilizzando *Matlab* ed in particolare lo strumento [PID Tuner](https://it.mathworks.com/help/slcontrol/ug/designing-controllers-with-the-pid-tuner.html), grazie al quale è possibile tarare visivamente il **PID** ed estrarre i parametri delle sue tre componenti.

Per la fase di taratura empirica è bene comunque fare ricorso alle principali relazioni che legano i parametri del **PID** agli effetti sul sistema controllato, accennate precedentemente in tabella. Tipicamente si progetta il controllore in accordo ai seguenti passaggi:
* Determinazione della risposta del sistema ad anello aperto (se possibile) per avere di un'idea di quali devono essere le modifiche da apportare con il controllo;
* Inserimento di un effetto proporzionale per diminuire il tempo di salita, aumentando la prontezza del sistema, ma tenendo in considerazione il fatto è che aumentandolo troppo si avrebbe un sistema meno stabile;
* Inserimento di un effetto integrale per eliminare gli errori a regime;
* Inserimento di un effetto derivativo per diminuire la sovraelongazione ed il tempo di assestamento, migliorando la stabilità ed offrendo la possibilità di un aumento dell'effetto proporzionale;
* Misurazione ripetuta della risposta del sistema controllato e *tuning* definitivo dei tre parametri caratteristici delle tre componenti, fino ad ottenere la risposta desiderata.

Infine, è importante tenere in considerazione che non è sempre necessario implementare un **PID** completo, con tutte e tre le componenti: a volte potrebbe bastare un **PD** (se il sistema da controllare presenta già degli effetti integrali internamente) o un **PI**, che generalmente è sufficiente per risolvere moltissimi problemi di controllo.


***