# HEPTrigger
Cálculo da eficiência de trigger.
# Setup
Baixe esse repositório com:

```bash
git clone https://github.com/DESY-CBPF-UERJ/HEPTrigger.git
```

# Modificações que devem ser feitas

O framework consiste de duas macros (conversion.C e TrigEffStudy.C), somente é necessário alterar o Conversion.C, na linha 62, onde é delcrado o char com o
diretório onde os datasets estão.

``` const char dirname[48] = "/home/matheus/Desktop/TChain/TTTo2L2Nu_16_files"; ```

Altere com o caminho dos seus dados. Quanto a macro TriEffStudy.C, é necessário alterar a linha 67 e 70

``` 
fChain->AddFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/MCttbar.root");      #file.root de MC
fChain->AddFile("/eos/home-c/ckoraka/for_running_trigger_SFs_with_lepton-PU/2017/converted/MET_2017.root"); #file.root de Data 
```
Coloque neles onde se encontram seus file.root que serão gerados pelo conversion.C.Feito essas alterações, as macros estão prontas para serem executadas.
# Executando as macros
Há uma ordem que deve ser seguida na execução das macros, sendo ela Conversion.C->TrigEffStudy.C. Para rodar a macro Conversion.C, execute no terminal a seguinte
linha``` root Conversion.C```
Os seguintes avisos são comuns
```Warning in <TFile::Init>: file Tree.root probably not closed, trying to recover
Warning in <TFile::Init>: no keys recovered, file has been made a Zombie
```
Ao final da execução você deve ter, além dos warnings, um output parecido com
```
95
Numero de eventos: 242422
```
No caso, passaram 95 files, que juntos contém 242422 entradas.
Para rodar a macro TrigEffStudy.C, execute os seguintes comandos
```
root -l
.L trigEffStudy.C++
trigEffStudy("", "false","", "true", YEAR) # for Data; YEAR = [2016, 2017, 2018]
trigEffStudy("", "true", "", "true", YEAR) # for MC;   YEAR = [2016, 2017, 2018]
```

# Explicação de cada macro
# Conversion.C
```Conversion.C``` basicamente acessa seus datasets, seleciona as variáveis, previamente declaradas no ```include/EventVar.h```, junta todas em uma nova tree, com formato específico, que será utilizada nas macros subsequentes.
# TrigEffStudy.C
```TrigEffStudy.C``` acessa o novo file.root, gerado pelo ```Conversion.C```, e separa os eventos em diferentes classificações, que são descritas a seguir.
```
HLT_allMET = Eventos que passaram por algum trigger de MET, definido no "src/jetMetHandler.C"

HLT_DoubleMu_OR = Eventos que passaram por algum trigger do canal mumu, o evento tem que ter dois múons, zero elétrons e pelo menos 1 jato.
HLT_DoubleEl_OR = Eventos que passaram por algum trigger do canal ee, o evento tem que ter dois elétrons, zero múons e pelo menos 1 jato.
HLT_EMu_OR = Eventos que passaram por algum trigger do canal emu, o evento tem que ter 1 múon, 1 elétron e pelo menos 1 jato.
DoubleMu_OR__X__allMET = Eventos que passaram por algum trigger de MET e do canal mumu, o evento tem que ter 2 múons, zero elétrons e pelo menos 1 jato.
DoubleEl_OR__X__allMET = Eventos que passaram por algum trigger do MET e do canal ee, o evento tem que ter 2 elérons, zero múons e pelo menos 1 jato.
EMu_OR__X__allMET = Eventos que passaram por algum trigger de MEt e do canal emu, o evento tem que ter 1 múon, 1 elétron e pelo menos 1 jato.

Possíveis primeiros sufixos, aplicados as classificações a cima (exceto a HLT_allMET), todos esses cortes são definidos no "src/JetMetHandler.C", entre as linhas 326 e 331:

_NJETSLOW = Eventos com menos de 3 jatos.
_NJETSHIGH = Eventos 3 ou mais jatos. 
_NPVSLOW = Eventos com menos de 30 vértices primários. 
_NPVHIGH = Eventos com 30 ou mais vértices primários.
_METSLOW = Eventos com 150 ou mais GeV no MET.
_METHIGH = Eventos com menos de 150 GeV no MET.

A macro cria diversos histogramas para cada classificação e suas possíveis combinações de sufixo, totalizando 42 possíveis classificações, o HLT_allMET vai ter uma versão para cada um desses 42, contudo ele não utiliza os mesmos sufixos. Ele também salva as seguintes variáveis para cada classificação:

_el0_pt = Momento do leading elétron
_el1_pt = Momento do subleading elétron
_mu0_pt = Momento do leading múon
_mu1_pt = Momento do subleading múon
_el0_eta = pseudo-rapidez do leading elétron
_el1_eta = pseudo-rapidez do subleading elétron
_mu0_eta = pseudo-rapidez do leading múon
_mu1_eta = pseudo-rapidez do subleading múon
_njets = número de jatos
_nbtags =  número de jatos de b
_mll = massa invariante do sistema de dois leptons do sistema
_met = energia transversal faltante do sistema
_nPV = número de vértices primários
_mu0_relIso = isolamento relativo do leading múon
_el0_relIso = isolamento relativo do leading elétron

Também há variáveis que representam os gráficos 2D entre algumas variáveis, sendo elas:

_mu0_pt_vs_eta = relação entre a distribuição do momento e da pseudo-rapidez do leading múon
_mu1_pt_vs_eta = relação entre a distribuição do momento e da pseudo-rapidez do subleading múon
_mu0_pt_vs_mu1_pt = relação entre a distribuição do momento do leading e subleading múon
_mu0_eta_vs_mu1_eta = relação entre a pseudo-rapidez do leading e subleading múon

_el0_pt_vs_eta = relação entre a distribuição do momento e da pseudo-rapidez do leading elétron
_el1_pt_vs_eta = relação entre a distribuição do momento e da pseudo-rapidez do subleading elétron
_el0_pt_vs_el1_pt = relação entre a distribuição do momento do leading e subleading elétron
_el0_eta_vs_el1_eta = relação entre a pseudo-rapidez do leading e subleading eletron
