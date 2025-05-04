# Estrutura de Branches

## 🌿 1. Branch principal

- `main` → Versão final e estável do projeto.  
- `develop` → Onde se juntam as tarefas de cada sprint antes de ir para `main`.

---

## 📦 2. Branch por Sprint

Para cada sprint, crie uma branch baseada em `develop`:

- `sprint1`
- `sprint2`
- `sprint3`

---

## 👤 3. Branch por Tarefa dentro da Sprint

Cada pessoa cria sua branch com o nome da tarefa (ou identificação), baseada na branch da sprint:

- `sprint1/tarefa1`
- `sprint1/tarefa2`
- `sprint1/tarefa3`

---

## 🔁 Como Trabalhar

Cada integrante:

1. Cria sua branch a partir da `sprintX`.
2. Faz commits normalmente.
3. Ao terminar, abre um **Pull Request** para a branch da sprint (ex: `sprint1`).

---

Quando todas as tarefas forem entregues:

1. Junta tudo na branch da sprint (ex: `sprint1`).
2. Faz o merge de `sprint1` → `develop`.
3. E, no final de tudo, faz o merge de `develop` → `main`.
