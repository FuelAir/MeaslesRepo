
# Projeto de Blockchain ED2

Projeto realizado para a disciplina de Estrutura de Dados 2, buscando simular uma Blockchain e permitir consultas solicitadas pelo Professor.

### 🔧 Instalação

É necessária a instalação da biblioteca ssl-dev, escrevendo o seguinte comando no terminal Linux:

```
sudo apt-get install libssl-dev
```

### ⚙️ Executando a compilação

Para a execução da compilação do código é necessário acessar a pasta onde se encontra este repositório e o arquivo "main.c" no terminal do Linux e executar o seguinte comando:

```
gcc main.c hashUtils.c mtwister.c -lcrypto -o bin/main
```

### ⌨️ Executando o programa para realizar as consultas

Para a execução do código é necessário acessar a pasta onde se encontraeste repositório e o arquivo "main.c" no terminal do Linux e executar o seguinte comando:

```
bin/main
```

Após isso aguarde o "Menu" aparecer para inserir inputs.