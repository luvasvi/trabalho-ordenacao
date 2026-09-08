```markdown
# Análise de Algoritmos de Ordenação

Trabalho prático e teórico desenvolvido para a disciplina de **Análise de Complexidade de Algoritmos**, baseado no Capítulo 4 (*Ordenação*) do livro *Projeto de Algoritmos com Implementações em Pascal e C*, de Nivio Ziviani[cite: 1].

---

## 👥 Integrantes da Equipe

1. Integrante 1: Lucas Vieira Austregésilo
2. Integrante 2: Mailson Malaquias  
3. Integrante 3: Ingrid Flávia
4. Integrante 4: Robson Evangelista

---

## 📁 Estrutura do Repositório

```text
trabalho-ordenacao/
├── README.md
├── algoritmos/
│   ├── quicksort.c
│   ├── merge_sort.c
│   └── insertion_sort.c
└── experimentos/
    ├── main_benchmark.c
    ├── resultados.csv
    └── graficos/
        └── graficos_experimentos.png

```

### Descrição dos Diretórios:

* **`algoritmos/`**: Contém o código-fonte independente dos algoritmos implementados:


* `quicksort.c`: Implementação clássica com partição de Hoare e pivô no elemento central (Obrigatório).


* `merge_sort.c`: Algoritmo $\Theta(n \log n)$ estável implementado com buffer auxiliar único de intercalação.


* `insertion_sort.c`: Algoritmo elementar de inserção direta com melhor caso linear $\Theta(n)$ e pior caso $\Theta(n^2)$.




* **`experimentos/`**: Contém a infraestrutura de medição de desempenho e os artefatos gerados:


* `main_benchmark.c`: Script unificado em C para teste e cronometragem das entradas.


* `resultados.csv`: Tabela com as medições de tempo em milissegundos (ms) exportada pelo benchmark.


* `graficos/`: Imagens dos gráficos comparativos gerados para o relatório.





---

## ⚙️ Como Compilar e Executar

### 1. No Navegador (Sem Instalações)

1. Acesse o [OnlineGDB](https://www.onlinegdb.com/).
2. No canto superior direito, selecione a linguagem **C** (ou **C (gcc)**).
3. Copie o conteúdo de `experimentos/main_benchmark.c` e cole no editor.
4. Clique em **Run** (ou pressione `F9`).
5. Os tempos serão exibidos no console e o arquivo `resultados.csv` será gerado automaticamente.

### 2. Localmente via Terminal (GCC)

Para compilar com flags de otimização e executar:

```bash
# Navegar até a pasta de experimentos
cd experimentos

# Compilar o benchmark
gcc -O2 main_benchmark.c -o benchmark

# Executar
./benchmark

```

---

## 📊 Resultados dos Experimentos

Medições obtidas para entradas de tamanhos $100$, $1.000$, $10.000$ e $100.000$ elementos sob ordens **Aleatória**, **Ordenada** e **Inversa**:

| Algoritmo | Entrada | 100 | 1.000 | 10.000 | 100.000 | Unidade |
| --- | --- | --- | --- | --- | --- | --- |
| **Quicksort** | Aleatória | 0.009 | 0.101 | 1.186 | 13.962 | ms |
| **Quicksort** | Ordenada | 0.003 | 0.025 | 0.293 | 3.714 | ms |
| **Quicksort** | Inversa | 0.002 | 0.031 | 0.294 | 3.706 | ms |
| **Merge Sort** | Aleatória | 0.011 | 0.107 | 1.343 | 17.380 | ms |
| **Merge Sort** | Ordenada | 0.006 | 0.054 | 0.770 | 8.732 | ms |
| **Merge Sort** | Inversa | 0.005 | 0.055 | 0.729 | 9.381 | ms |
| **Insertion Sort** | Aleatória | 0.009 | 0.732 | 71.736 | TIMEOUT* | ms |
| **Insertion Sort** | Ordenada | 0.001 | 0.005 | 0.044 | 0.370 | ms |
| **Insertion Sort** | Inversa | 0.015 | 1.346 | 139.699 | TIMEOUT* | ms |

* **TIMEOUT:** Conforme permitido no roteiro da disciplina, os testes de $100.000$ elementos do Insertion Sort nas entradas aleatória e inversa foram interrompidos devido à expansão quadrática de tempo ($\Theta(n^2)$), estimada em mais de 14 segundos.

---

## 📈 Gráficos Comparativos

Os gráficos comparativos em escala logarítmica para os três tipos de entrada encontram-se em `experimentos/graficos/graficos_experimentos.png`:

```

```
