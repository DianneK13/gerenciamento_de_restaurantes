## ✅ Test Cases - GO Food

Caro monitor, este arquivo documenta testes automáticos simulados, usando arquivos de input.

---

#### 🟢 input_1.txt — Fluxo básico e feliz

- Cadastra restaurante.
- Lista restaurantes.
- Sai.

---

#### 🔴 input_2.txt — Erros e entradas inválidas

- Entrada inválida em código.
- Código duplicado.
- Tentativa de adicionar prato em restaurante inexistente.
- Lista final.

---

#### 🟡 input_3.txt — Atualização de restaurante

- Atualiza nome, descrição e tipo de cozinha.
- Verifica via listagem.

---

#### 🟣 input_4.txt — Operações em pratos

- Adiciona dois pratos.
- Lista menu.
- Remove prato.
- Lista menu final.

---

### 💬 Como executar
Dentro do `git bash`, cole estes comandos, ou, se preferir, rode os testes manualmente.
```bash
gcc mcra2_listaFunctions.c -o gofood

./gofood < testcases/input_1.txt
./gofood < testcases/input_2.txt
./gofood < testcases/input_3.txt
./gofood < testcases/input_4.txt