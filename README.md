# Caro monitor! Acesse o arquivo `mcra2_listaFunctions.c` :))

## 🍽️ GO Food — Sistema de Gerenciamento de Restaurantes

### 💡 Sobre o projeto

O sistema foi desenvolvido como projeto acadêmico para treinar conceitos de:

- Alocação dinâmica de memória.
- Manipulação de structs.
- Uso de ponteiros.
- Organização modular de funções.
- Validação de entradas do usuário.

---

### ✨ Funcionalidades

:white_check_mark: Cadastrar restaurantes com nome, descrição, tipo de cozinha e código único.  
:white_check_mark: Listar restaurantes com ou sem filtros por tipo.  
:white_check_mark: Atualizar informações de restaurantes.  
:white_check_mark: Adicionar pratos ao menu de um restaurante.  
:white_check_mark: Listar cardápios completos.  
:white_check_mark: Remover pratos do cardápio.  
:white_check_mark: Validação robusta de entradas (evita crashes e entradas inválidas).  
:white_check_mark: Mensagens interativas, com uso de emojis para melhorar a UX.  

---

### 🗂️ Estrutura do repositório
```py
gerenciamento_de_restaurantes/
├── mcra2_listaFunctions.c     # Arquivo principal do sistema
├── testcases/
│   ├── input_1.txt            # Fluxo básico
│   ├── input_2.txt            # Casos de erro e entradas inválidas
│   ├── input_3.txt            # Atualização de restaurante
│   ├── input_4.txt            # Operações com pratos
│   └── TEST_CASE.md           # Documentação explicando os casos de teste
└── README.md                  # Este arquivo
```

---

### ⚙️ Como compilar

```bash
gcc mcra2_listaFunctions.c -o gofood
```

### Instruções de como executar com arquivos de teste automático estão no arquivo [TEST_CASE.md](https://github.com/DianneK13/gerenciamento_de_restaurantes/blob/main/testcases/TEST_CASE.md)

###### Obs.: Caso esteja no Windows e use PowerShell, o redirecionamento < não funciona. Utilize cmd.exe ou Git Bash.

---

### Casos de teste

Os arquivos de entrada estão na pasta `testcases/`, e o arquivo `TEST_CASE.md` explica o objetivo de cada um.

---

### Exemplos de execução

<details>
<summary> Exemplo de listagem de restaurantes</summary>

```c
==🍽️Listando restaurantes cadastrados...==
-------------------------------------------
📍 Restaurante
🧾 Nome:        Sushi Yama
📝 Descrição:   Culinaria japonesa
🏷️ Código:      101
🍽️ Tipo:        japonesa
-------------------------------------------

Total de restaurantes encontrados: 1

Voltando ao menu principal... 🍽️
```

</details>

<details>
<summary> Exemplo de listagem de menu</summary>

```c
===== Menu do restaurante Sushi Yama =====

Prato 1:
Nome: Sashimi
Descricao: Fatias frescas de salmao
Preco: R$35.50
---
===============================
```
</details>

---

### Inspiração
•    Parte da aplicação seguiu como o exemplo o [vídeo](https://youtu.be/Lf3ZV0UsnEo?si=tRTc9USU8iIJ3mlq) do [@FilipiDeschamps](https://github.com/FilipeDeschamps)

---

### Licença

Este projeto é de uso acadêmico e livre para estudo e evolução pessoal. Seria útil mesmo?

---

## Autor

| [<img src="https://avatars.githubusercontent.com/u/140253955?v=4" width=115><br><sub>@DianneK13</sub>](https://github.com/DianneK13) |
| :---: |
