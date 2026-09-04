# Índice de Documentação - Simulação de Ecossistema

## 📚 Estrutura Geral da Documentação

Este projeto possui documentação técnica completa dividida em múltiplos documentos. Use este índice como ponto de partida.

---

## 🎯 Comece Aqui

### Para Novos Usuários
1. Leia [README.md](README.md) - Visão geral do projeto
2. Leia [docs/MECANICAS.md](docs/MECANICAS.md) - Entenda como a simulação funciona
3. Explore [CONSTANTES.md](CONSTANTES.md) - Valores e parâmetros configuráveis

### Para Novos Desenvolvedores
1. Leia [docs/GUIA_DESENVOLVIMENTO.md](docs/GUIA_DESENVOLVIMENTO.md) - Padrões e workflow
2. Leia [docs/ARQUITETURA.md](docs/ARQUITETURA.md) - Estrutura do código
3. Leia [docs/ESPECIFICACOES.md](docs/ESPECIFICACOES.md) - APIs e estruturas

### Para Investigadores/Pesquisadores
1. Leia [docs/ENTITIES.md](docs/ENTITIES.md) - Definição de entidades
2. Leia [docs/MECANICAS.md](docs/MECANICAS.md) - Fórmulas e dinâmicas
3. Consulte [CONSTANTES.md](CONSTANTES.md) - Parâmetros científicos

---

## 📄 Documentação por Tópico

### Visão Geral
- **[README.md](README.md)**
  - Objetivo do projeto
  - Estrutura de diretórios
  - Início rápido
  - Componentes principais
  - Estado do projeto

### Arquitetura e Design
- **[docs/ARQUITETURA.md](docs/ARQUITETURA.md)**
  - Padrões de design (ECS, Observer, Singleton, Strategy, Factory)
  - Fluxo de dados principal
  - Componentes principais
  - Interfaces e contatos
  - Princípios de design
  - Diagrama de classes
  - Fluxo de inicialização
  - Considerações de performance

### Entidades
- **[docs/ENTITIES.md](docs/ENTITIES.md)**
  - Classe Entity (base)
  - Classe Plant (plantas)
    - Tipos de plantas
    - Ciclo de vida
    - Fórmulas de simulação
  - Classe Human (humanos)
    - Estados básicos
    - Atributos físicos
    - Ciclo de vida
    - Fórmulas de simulação
  - Interações entre entidades
  - Hierarquia de classes
  - Propriedades de criação

### Mecânicas de Simulação
- **[docs/MECANICAS.md](docs/MECANICAS.md)**
  - Sistema de tempo
  - Ciclo dia/noite
  - Estações
  - Mecânicas de plantas
    - Fotossíntese
    - Absorção de recursos
    - Crescimento
    - Reprodução
    - Morte
  - Mecânicas de humanos
    - Necessidades básicas (fome, sede, cansaço)
    - Eficiência de trabalho
    - Comportamento e IA
    - Movimento e navegação
    - Construção
    - Reprodução
    - Morte
  - Mecânicas ambientais
    - Regeneração de recursos
    - Temperatura e clima
  - Resumo de fórmulas

### Especificações Técnicas
- **[docs/ESPECIFICACOES.md](docs/ESPECIFICACOES.md)**
  - Configuração do projeto (CMake)
  - Estruturas de dados principais
  - APIs principais
    - Environment API
    - SimulationEngine API
    - Entity API
    - Plant API
    - Human API
    - Sistemas API
  - Enumerações e constantes
  - Constantes de configuração
  - Configuração de simulação
  - Formatos de dados

### Guia de Desenvolvimento
- **[docs/GUIA_DESENVOLVIMENTO.md](docs/GUIA_DESENVOLVIMENTO.md)**
  - Ambiente de desenvolvimento
  - Padrões de código
  - Workflow de desenvolvimento
  - Branch strategy
  - Processo de contribuição
  - Formato de commits
  - Testes e debugging
  - Performance profiling
  - Recursos para desenvolvedores
  - Tarefas comuns
  - Checklist PR
  - Roadmap

### Constantes e Configuração
- **[CONSTANTES.md](CONSTANTES.md)**
  - Constantes de configuração do mundo
  - Dimensões
  - Sistema de tempo
  - Recursos globais
  - Parâmetros por tipo de planta
  - Parâmetros de humanos
  - Ambiente (temperatura, ciclo, estações)
  - Performance e limites
  - Cenários recomendados

---

## 🔍 Busca Rápida por Tópico

### "Como a fotossíntese funciona?"
→ [Mecânicas de Plantas - Fotossíntese](docs/MECANICAS.md#1-fotossíntese)

### "Qual é a estrutura de diretorios?"
→ [README.md - Estrutura do Projeto](README.md#-estrutura-do-projeto)

### "Como implemento uma nova feature?"
→ [Guia de Desenvolvimento - Workflow](docs/GUIA_DESENVOLVIMENTO.md#-workflow-de-desenvolvimento)

### "Quais são os padrões de código?"
→ [Guia de Desenvolvimento - Padrões](docs/GUIA_DESENVOLVIMENTO.md#-padrões-de-código)

### "Como funciona o comportamento dos humanos?"
→ [Entidades - Human API](docs/ENTITIES.md#-entidade-human-ser-humano)

### "Qual é a API do Environment?"
→ [Especificações - Environment API](docs/ESPECIFICACOES.md#environment-api)

### "Como adiciono um novo tipo de planta?"
→ [Guia de Desenvolvimento - Tarefas Comuns](docs/GUIA_DESENVOLVIMENTO.md#adicionar-novo-tipo-de-planta)

### "Quais são os valores padrão de constantes?"
→ [CONSTANTES.md](CONSTANTES.md)

---

## 🏗️ Hierarquia Recomendada de Leitura

### Fase 1: Aprendizado (1-2 horas)
```
1. README.md (5 min)
   ↓
2. MECANICAS.md - Sistema de Tempo (10 min)
   ↓
3. ENTITIES.md - Visão Geral (15 min)
   ↓
4. ARQUITETURA.md - Visão Geral da Arquitetura (20 min)
```

### Fase 2: Entendimento Profundo (2-4 horas)
```
5. ENTITIES.md - Completo (30 min)
   ↓
6. MECANICAS.md - Completo (45 min)
   ↓
7. ESPECIFICACOES.md - APIs (30 min)
   ↓
8. ARQUITETURA.md - Completo (30 min)
```

### Fase 3: Desenvolvimento (Contínuo)
```
9. GUIA_DESENVOLVIMENTO.md (1 hora)
   ↓
10. Consultar CONSTANTES.md conforme necessário
    ↓
11. Implementar features seguindo padrões
```

---

## 📊 Mapa Conceitual

```
┌─────────────────────────────────────────────┐
│  SIMULAÇÃO DE ECOSSISTEMA                   │
│                                             │
│  ┌───────────────────────────────────────┐ │
│  │ MUNDO (Environment)                   │ │
│  │ - Grid 1024x768                       │ │
│  │ - Recursos globais                    │ │
│  │ - Ciclo dia/noite                     │ │
│  └───────────────────────────────────────┘ │
│                    ▲                        │
│  ┌─────────┬──────┴──────┬──────────┐     │
│  │         │             │          │     │
│  ▼         ▼             ▼          ▼     │
│ PLANTS   HUMANS     CONSTRUÇÕES  RECURSOS│
│ ├─Grass  ├─Atributos ├─Shelter   ├─Água  │
│ ├─Shrub  ├─Necessid. ├─Storage   ├─Nutri.│
│ ├─Tree   ├─Comportam.├─Farm      └─Ener. │
│ ├─Flower ├─Construir ├─Well             │
│ └─Crop   └─Moviment. └─Wall             │
│                                             │
│  ┌───────────────────────────────────────┐ │
│  │ SISTEMAS (Systems)                    │ │
│  │ ├─Physics   ├─Growth                  │ │
│  │ ├─Resources ├─Building                │ │
│  └───────────────────────────────────────┘ │
│                    ▲                        │
│                    │                        │
│  ┌─────────────────┴────────────────────┐ │
│  │ MOTOR DE SIMULAÇÃO (Engine)          │ │
│  │ - Loop principal                     │ │
│  │ - Coordenação de sistemas            │ │
│  │ - Gerenciamento de ticks             │ │
│  └─────────────────────────────────────┘ │
└─────────────────────────────────────────────┘
```

---

## 🎯 Por Tipo de Usuário

### 👤 Gerenciador de Projeto
Leia: README.md → CONSTANTES.md → docs/GUIA_DESENVOLVIMENTO.md

### 🧑‍💻 Desenvolvedor Novo
Leia na ordem: GUIA_DESENVOLVIMENTO.md → ARQUITETURA.md → ESPECIFICACOES.md → ENTITIES.md

### 👨‍🔬 Pesquisador/Cientista
Leia na ordem: ENTITIES.md → MECANICAS.md → CONSTANTES.md → ESPECIFICACOES.md

### 🎮 Game Designer
Leia na ordem: README.md → MECANICAS.md → CONSTANTES.md → ENTITIES.md

### 🔧 DevOps/Infra
Leia: README.md → docs/GUIA_DESENVOLVIMENTO.md (seção de build)

---

## 📋 Checklist de Leitura

### Para Começar
- [ ] Li o README.md
- [ ] Entendi a estrutura de diretórios
- [ ] Entendi o objetivo do projeto

### Para Contribuir
- [ ] Li o GUIA_DESENVOLVIMENTO.md
- [ ] Entendi os padrões de código
- [ ] Entendi o workflow de contribuição
- [ ] Entendi como fazer commits

### Para Implementar
- [ ] Li ARQUITETURA.md
- [ ] Entendi a hierarquia de classes
- [ ] Entendi os padrões de design
- [ ] Consultei ESPECIFICACOES.md para APIs

### Para Balancear
- [ ] Li MECANICAS.md
- [ ] Entendi fórmulas de simulação
- [ ] Consultei CONSTANTES.md para valores

---

## 🔗 Referências Cruzadas

### Entidades (ENTITIES.md) ↔ Mecânicas (MECANICAS.md)
- Plant → Fotossíntese, Crescimento, Reprodução
- Human → Necessidades, Comportamento, Construção

### Arquitetura (ARQUITETURA.md) ↔ Especificações (ESPECIFICACOES.md)
- Componentes → APIs
- Sistemas → System API
- Fluxo → Update loop

### Guia (GUIA_DESENVOLVIMENTO.md) ↔ Especificações (ESPECIFICACOES.md)
- Tarefas Comuns → Consultar APIs
- Debugging → Usar estruturas de dados

---

## 📞 Como Usar Esta Documentação

1. **Para uma pergunta específica:** Use "Busca Rápida por Tópico" acima
2. **Para aprender do zero:** Siga "Hierarquia Recomendada de Leitura"
3. **Para seu tipo de usuário:** Vá direto em "Por Tipo de Usuário"
4. **Para implementar algo:** Consulte documento relevant + GUIA_DESENVOLVIMENTO.md

---

## 🚀 Próximos Passos

Depois de ler esta documentação:

1. **Familiarize-se** com a estrutura de código em `src/`
2. **Configure o ambiente** seguindo README.md
3. **Implemente o primeiro componente** seguindo GUIA_DESENVOLVIMENTO.md
4. **Consulte APIs** em ESPECIFICACOES.md conforme necessário
5. **Teste sua implementação** usando os exemplos em GUIA_DESENVOLVIMENTO.md

---

## 📝 Versão

- **Versão da Documentação:** 1.0.0
- **Data:** 2026-09-04
- **Status:** Completa

---

## ✅ Cobertura de Tópicos

- [x] Visão geral e objetivo
- [x] Arquitetura e design
- [x] Estruturas de dados
- [x] APIs e interfaces
- [x] Entidades e comportamentos
- [x] Mecânicas de simulação e fórmulas
- [x] Sistema de tempo e ciclos
- [x] Padrões de código
- [x] Workflow de desenvolvimento
- [x] Constantes e configuração
- [x] Debugging e performance
- [x] Exemplos de implementação

A documentação é **completa e pronta para desenvolvimento**! 🎉

