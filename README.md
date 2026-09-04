# Simulação de Ecossistema Realista

## 📋 Visão Geral

Projeto de simulação de um ecossistema completo e realista em C++, que incorpora entidades biológicas (plantas) e agentes inteligentes (seres humanos) que interagem, constroem e crescem em um ambiente dinâmico.

**Versão:** 1.0.0  
**Linguagem:** C++17  
**Status:** Em Desenvolvimento

---

## 🎯 Objetivos do Projeto

1. **Simular dinâmicas ecológicas realistas** entre plantas, recursos e seres humanos
2. **Implementar comportamentos autônomos** para entidades que interagem com o ambiente
3. **Modelar crescimento e evolução** das entidades ao longo do tempo
4. **Criar um sistema de construção** onde humanos podem modificar o ambiente
5. **Fornecer análise e visualização** dos dados de simulação em tempo real

---

## 🏗️ Estrutura do Projeto

```
asistente/
├── docs/                          # Documentação técnica
│   ├── ARQUITETURA.md            # Arquitetura do sistema
│   ├── ESPECIFICACOES.md         # Especificações técnicas
│   ├── ENTITIES.md               # Documentação de entidades
│   ├── MECANICAS.md              # Mecânicas de simulação
│   └── GUIA_DESENVOLVIMENTO.md   # Guia para desenvolvedores
├── src/                           # Código-fonte
│   ├── core/                     # Núcleo da simulação
│   │   ├── Environment.h         # Ambiente/Mundo
│   │   ├── Environment.cpp
│   │   ├── SimulationEngine.h    # Motor de simulação
│   │   └── SimulationEngine.cpp
│   ├── entities/                 # Definições de entidades
│   │   ├── Entity.h              # Classe base
│   │   ├── Entity.cpp
│   │   ├── Plant.h               # Plantas
│   │   ├── Plant.cpp
│   │   ├── Human.h               # Seres humanos
│   │   └── Human.cpp
│   ├── systems/                  # Sistemas auxiliares
│   │   ├── PhysicsSystem.h       # Física/colisões
│   │   ├── ResourceSystem.h      # Gestão de recursos
│   │   ├── GrowthSystem.h        # Sistema de crescimento
│   │   └── BuildingSystem.h      # Sistema de construção
│   ├── utils/                    # Utilidades
│   │   ├── Vector2D.h
│   │   ├── Constants.h
│   │   └── Logger.h
│   └── main.cpp
├── tests/                         # Testes unitários
│   ├── test_environment.cpp
│   ├── test_entities.cpp
│   └── test_systems.cpp
├── CMakeLists.txt                # Configuração de build
├── README.md                      # Este arquivo
└── .gitignore

```

---

## 🚀 Início Rápido

### Pré-requisitos

- CMake 3.15+
- C++17 ou superior
- Compilador: GCC 8+, Clang 10+ ou MSVC 2019+

### Compilação

```bash
mkdir build
cd build
cmake ..
make
```

### Execução

```bash
./asistente
```

---

## 📚 Documentação Técnica

A documentação completa está organizada da seguinte forma:

| Documento | Conteúdo |
|-----------|----------|
| [ARQUITETURA.md](docs/ARQUITETURA.md) | Estrutura geral, padrões de design, fluxo de dados |
| [ESPECIFICACOES.md](docs/ESPECIFICACOES.md) | Detalhes técnicos, APIs, formatos de dados |
| [ENTITIES.md](docs/ENTITIES.md) | Definição de todas as entidades e seus comportamentos |
| [MECANICAS.md](docs/MECANICAS.md) | Regras de simulação, fórmulas, algoritmos |
| [GUIA_DESENVOLVIMENTO.md](docs/GUIA_DESENVOLVIMENTO.md) | Como contribuir, padrões de código, workflow |

---

## 🔑 Componentes Principais

### Ambiente (Environment)
Gerencia o mundo da simulação, incluindo:
- Mapa/Grid onde as entidades existem
- Propriedades ambientais (temperatura, umidade, luz solar)
- Gestão de recursos globais
- Ciclo dia/noite

### Motor de Simulação (SimulationEngine)
Controla a lógica geral:
- Loop principal de simulação
- Coordenação entre sistemas
- Sincronização de tempo
- Gestão de estados de entidades

### Entidades
- **Plantas:** Consomem recursos (água, nutrientes), crescem, reproduzem-se
- **Humanos:** Agem autonomamente, constroem estruturas, consomem recursos, crescem

### Sistemas Especializados
- **Physics System:** Colisões, movimento, proximidade
- **Resource System:** Água, nutrientes, energia
- **Growth System:** Envelhecimento, desenvolvimento, reprodução
- **Building System:** Construção de estruturas, modificação de ambiente

---

## 🎮 Funcionalidades Principais

- ✅ Simulação de crescimento e reprodução de plantas
- ✅ Comportamento autônomo de humanos
- ✅ Sistema de construção e modificação ambiental
- ✅ Ciclos ecológicos (dia/noite, estações)
- ✅ Gestão de recursos
- ✅ Análise de dados em tempo real
- ✅ Visualização de estado da simulação

---

## 📊 Estado do Projeto

### Fase 1: Fundação ✅
- [x] Arquitetura base definida
- [x] Estrutura de diretórios criada
- [x] Documentação técnica completa

### Fase 2: Implementação 🔄
- [ ] Implementar classe Entity base
- [ ] Implementar classe Environment
- [ ] Implementar SimulationEngine
- [ ] Implementar Plant
- [ ] Implementar Human
- [ ] Implementar sistemas especializados

### Fase 3: Testes e Otimização
- [ ] Testes unitários
- [ ] Testes de integração
- [ ] Profiling e otimização
- [ ] Documentação de API

---

## 🤝 Contribuindo

Leia [GUIA_DESENVOLVIMENTO.md](docs/GUIA_DESENVOLVIMENTO.md) para informações sobre como contribuir, padrões de código e workflow de desenvolvimento.

---

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo LICENSE para detalhes.

---

## 👨‍💼 Autores

- **Markus** - Desenvolvedor Senior

---

## 📞 Suporte

Para dúvidas ou sugestões, consulte a documentação técnica ou abra uma issue no repositório.
